
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "support.h"
#include "callbacks.h"

#include "globals.h"
#include "poi.h"
#include "converter.h"
#include "interface.h"
#include "util.h"
#include "tile_management.h"

#include <glib.h>
#include <glib/gprintf.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <glib/gstdio.h>

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define POI_DB "poi.db"

GtkListStore *list_store;

gchar *my_strescape_back (const gchar *source,  const gchar *exceptions);

enum {
	COLUMN_STRING,
	COLUMN_INT,
	COLUMN_BOOLEAN,
	N_COLUMNS
};


static GtkWidget *combobox_subcat = NULL;
static gboolean new_dialog = TRUE;



#define POI_DB_CREATE  "CREATE TABLE poi (	\
		idmd5 TEXT, lat REAL, lon REAL, visibility REAL, cat REAL, subcat REAL, \
		keywords TEXT, desc TEXT, price_range REAL, extended_open REAL,	\
		creator TEXT, bookmarked REAL, user_rating REAL, rating REAL, user_comment TEXT);"



double
parse_degrees(const char *s)
{
	float deg, min, sec;
	
	
	if (3 == sscanf(s, "%f %f %f", &deg, &min, &sec))
		return deg + min/60 + sec/3600;
	else if (3 == sscanf(s, "%f° %f' %f\"", &deg, &min, &sec))
		return deg + min/60 + sec/3600;
	else if (3 == sscanf(s, "%f°%f'%f\"", &deg, &min, &sec))
		return deg + min/60 + sec/3600;
		
	else if (2 == sscanf(s, "%f %f", &deg, &min))
		return deg + min/60;
 	else if (2 == sscanf(s, "%f° %f'", &deg, &min))
		return deg + min/60;
	else if (2 == sscanf(s, "%f°%f'", &deg, &min))
		return deg + min/60;
		
	else if (1 == sscanf(s, "%f", &deg))
		return deg;

	return atof(s);
}


static int
sql_cb__poi_get(void *unused, int colc, char **colv, char **col_names)
{
	poi_t *poi = g_new0(poi_t,1);

	poi->idmd5		= g_strdup(colv[0]);
	poi->lat_deg		= atof(colv[1]);
	poi->lon_deg		= atof(colv[2]);
	poi->visibility		= atoi(colv[3]);
	poi->category		= atoi(colv[4]);
	poi->subcategory	= atoi(colv[5]);
	poi->keywords		= g_strdup(colv[6]);
	poi->desc		= g_strdup(colv[7]);
	poi->price_range	= atoi(colv[8]);
	poi->extended_open	= atoi(colv[9]);
	
	poi_list = g_slist_prepend(poi_list, poi);

	return 0;
}

static GdkPixbuf *
get_poi_icon (poi_t *poi)
{
	GdkPixbuf *icon;

	static GHashTable *icon_cache = NULL;
	static GdkPixbuf *poi_icon_default = NULL;

	if (!icon_cache) {
		/* Initialise icon-cache: */
		icon_cache = g_hash_table_new (g_str_hash, g_str_equal);
	}

	if (!poi_icon_default) {
		/* Initialise the default POI icon: */
		poi_icon_default = gdk_pixbuf_new_from_file_at_size
			(PACKAGE_PIXMAPS_DIR "/" PACKAGE "-poi.png",
			 25, 25,
			 NULL);
	}


	icon = g_hash_table_lookup (icon_cache, poi->keywords);

	if (!icon) {
		char *icon_dir =
			g_build_filename (foxtrotgps_dir, "poi-icons", NULL);

		/* Not all characters that might be in a POI's name
		   are suitable for use in icon-filenames, e.g.: 
		   path-separators need to be escaped so that
		   a POI named something like "../../evil"
		   doesn't result in us reading/writing a file
		   somewhere where we shouldn't, and a number of
		   characters need to be escaped to allow files
		   to be stored on some filesystems like FAT.
		 */
		char *icon_basename =
			g_uri_escape_string (poi->keywords, NULL, TRUE);

		char *icon_path =
			g_build_filename (icon_dir, icon_basename, NULL);

		g_free (icon_basename);

		g_mkdir (icon_dir, 0777);
		g_free (icon_dir);

		if (!g_file_test (icon_path, G_FILE_TEST_EXISTS)) {
			pid_t mkvisualid_pid;
			int mkvisualid_status;
	
			char *autocache_dir =
				g_build_filename (global_home_dir,
				                  ".VisualIDs",
				                  PACKAGE, "poi-icons",
				                  NULL);

			g_mkdir_with_parents (autocache_dir, 0777);
			/* Free autocache_dir later--we need to pass it
			   to mkvisualid, below... */
	
			mkvisualid_pid = fork();
	
			switch (mkvisualid_pid) {
			case 0:
				execlp ("mkvisualid", "mkvisualid",
				        "--autocache",
				        "--autocache-dir", autocache_dir,
				        "--output", icon_path,
				        "--linewidth=.1",
				        "--outline-width=.2",

				        /* Don't use glyph-types that are
				           easily confused with streets: */
				        "--line=0",
				        "--path=0",

				        poi->keywords,

				        NULL);

				_exit (1); /* execlp failed */
			default:
				waitpid (mkvisualid_pid, &mkvisualid_status, 0);
				/* Fall through to cleanup... */
			case -1:
				g_free (autocache_dir);
			}
		}
	
		icon = gdk_pixbuf_new_from_file_at_size
			(icon_path, 32, 32, NULL);
		/*^Note that this is slightly bigger than
		   the `generic POI star' fallback-icon:
		   we budget an additional 25% of the icon-radius
		   for a border in case the icon needs one,
		   e.g.: to ensure contrast against the map.
		 */

		g_free (icon_path);

		if (icon) {
			g_hash_table_insert (icon_cache,
			                     poi->keywords,
			                     icon);
		}
	}

	if (!icon)
	{
		icon = poi_icon_default;
	}

	return icon;
}


void
paint_pois()
{
	
	
	int pixel_x, pixel_y, x, y;
	float lat, lon;
	GSList *list;
	GdkColor color;
	static GdkGC *gc;
	

	if (!gc)
		gc = gdk_gc_new(pixmap); 
	color.green = 0;
	color.blue = 60000;
	color.red = 0;
	gdk_gc_set_rgb_fg_color(gc, &color);
	

	if(global_show_pois)
	{
		get_pois();
		
		for(list = poi_list; list != NULL; list = list->next)
		{
			poi_t *p = list->data;

			GdkPixbuf *photo_icon = get_poi_icon (p);
			int icon_width = gdk_pixbuf_get_width (photo_icon);
			int icon_height = gdk_pixbuf_get_width (photo_icon);
		
			lat = deg2rad(p->lat_deg);
			lon = deg2rad(p->lon_deg);
			
			
			
			pixel_x = lon2pixel(global_zoom, lon);
			pixel_y = lat2pixel(global_zoom, lat);
			
			x = pixel_x - global_x;
			y = pixel_y - global_y;
			
			p->screen_x = x;
			p->screen_y = y;
			
			
			
			if(!photo_icon)
			{
				gdk_draw_arc (
					pixmap,
					
					gc,
					TRUE,			
					x-4, y-4,		
					8,8,			
					0,23040);		
			}
			else
			{
				gdk_draw_pixbuf (
					pixmap,
					NULL,
					photo_icon,
					0,0,
					x - icon_width/2, y - icon_height/2,
					-1, -1,
					GDK_RGB_DITHER_NONE, 0, 0);
				
			}
			
			gtk_widget_queue_draw_area (
					map_drawable, 
					x - icon_width/2, y - icon_height/2,
					icon_width, icon_height);
		}
	}
}




GtkListStore *
create_combobox_list_store(char *list)
{
	GtkListStore	*list_store;
	GtkTreeIter	iter;
	int		i=0;
	char		**array;
	
	list_store = gtk_list_store_new (N_COLUMNS,
				   G_TYPE_STRING,
				   G_TYPE_INT,
				   G_TYPE_BOOLEAN);

	array = g_strsplit(list,"|",-1);
	
	while(array[i])
	{		
		
		
		gtk_list_store_append (list_store, &iter);
		gtk_list_store_set (list_store, &iter,
				  COLUMN_STRING, array[i],
				  COLUMN_INT, i,
				  COLUMN_BOOLEAN,  FALSE,
				  -1);
		
		i++;
	}
	
	g_strfreev(array);
	return list_store;
}	



void
on_combobox_subcat_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	
	
	
	GtkTreeIter iter;
	gchar *str_data;
	gint   int_data;

	gtk_combo_box_get_active_iter(combobox, &iter);
	
	gtk_tree_model_get (GTK_TREE_MODEL(list_store), &iter, 
                          COLUMN_STRING, &str_data,
                          COLUMN_INT, &int_data,
                          -1);
}


void set_combobox_subcat(GtkWidget *widget, int choice)
{
	
	GtkCellRenderer *renderer;
	GtkWidget *vbox;
	char *subcat_lists[16];

	subcat_lists[0] = "---"; 
	subcat_lists[1] = _("- Please choose -|Hotel|Motel|B&B|Hostel|Camping");
	subcat_lists[2] = _("- Please choose -|Bank / Exchange / ATM|Post Office|Real Estate Agency|Travel Agency|Other");
	subcat_lists[3] = _("- Please choose -|Parking|Gas Station|Repair Shop|Rental|Sharing|Dealer|Radar - Speed Trap|My Car");
	subcat_lists[4] = _("- Please choose -|Cinema|Theatre|Concert Hall|Opera|Casino");
	subcat_lists[5] = _("- Please choose -|Pharmacy|Hospital|Doctor");
	subcat_lists[6] = _("- Please choose -|Cafe|Pub|Lounge Bar|Club|Dancing|Internet Cafe|Wifi Hot Spot");
	subcat_lists[7] = _("- Please choose -|Church|Mosque|Synagogue|Temple|Cemetery");
	subcat_lists[8] = _("- Please choose -|Bus|Metro|Tram|Taxi|Train Station|Bike|Port|Airport");
	subcat_lists[9] = _("- Please choose -|Local Food|European|Asian|American|African|Pizza|Fast Food|Take Away|Barbecue|Italian|Mexican|Indian|Japanese|French");
	subcat_lists[10] = _("- Please choose -|Wifi Hotspot|ATM-Money Dispenser|Post Office/Letter Box|Laundry|Hairdresser|Other");
	subcat_lists[11] = _("- Please choose -|Tourist Info|Monument|Museum|Zoo|Viewpoint|Relief Map|Other");
	subcat_lists[12] = _("- Please choose -|Supermarket|Shopping Center|Clothes|Shoes|Food|Baker|Butcher|DoItYourself|Other");
	subcat_lists[13] = _("- Please choose -|Arena/Stadium|Swimming Pool|Freeclimbing|Ice Skating|Golf|Geo Cache|Other");
	subcat_lists[14] = _("- Please choose -|Friend|Other Cool Place");
	subcat_lists[15] = _("- Please choose -|Traditional|Multi|Virtual|Letterbox Hybrid|Event|Unknown|Project Ape|Webcam|Cache In Trash Out|Earthcache|Mega-Event|GPS Adventures|Wherigo|Other");
	/*
         * NOTE: for geocaching, should also be:
         * subsubcat[] = "- Please choose -|Micro|Small|Regular|Large|Virtual|Unknown|Other|";
         */

	vbox = lookup_widget(widget, "vbox28");
	list_store = create_combobox_list_store(subcat_lists[choice]);
	
	
	if((!combobox_subcat || new_dialog ) && choice)
	{
		combobox_subcat = gtk_combo_box_new_with_model (GTK_TREE_MODEL(list_store));
		gtk_widget_show (combobox_subcat);
		gtk_box_pack_start (GTK_BOX (vbox),combobox_subcat, FALSE, TRUE, 0);
		renderer = gtk_cell_renderer_text_new();
		gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combobox_subcat), renderer, TRUE);
		gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combobox_subcat), renderer, "text", 0, NULL);
		g_signal_connect ((gpointer) combobox_subcat, "changed",
					G_CALLBACK (on_combobox_subcat_changed),
					NULL);
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_subcat), 0);
		gtk_box_reorder_child(GTK_BOX(vbox),combobox_subcat,6);
		new_dialog = FALSE;
	}
	else if (choice)
	{
		gtk_combo_box_set_model(GTK_COMBO_BOX(combobox_subcat), GTK_TREE_MODEL(list_store));
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_subcat), 0);
	}
	

}


void
on_combobox_cat_changed(GtkComboBox     *combobox)
{
	int choice;

	choice = gtk_combo_box_get_active(combobox);
	
	
	set_combobox_subcat(GTK_WIDGET(combobox),choice);
	
}


void
show_window6()
{
	GladeXML *gladexml;
	GtkWidget *dialog;
	GtkWidget *entry14, *entry15, *combobox2;

	double lat, lon, lat_deg, lon_deg;
	char buf[64];

	gladexml = glade_xml_new (gladefile, "window6", GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	dialog = glade_xml_get_widget (gladexml, "window6");
	g_signal_connect_swapped (dialog, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);
	gtk_widget_show(dialog);
	new_dialog = TRUE;
	
	
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);
	entry14 = lookup_widget(dialog, "entry14");
	entry15 = lookup_widget(dialog, "entry15");
	
	g_sprintf(buf, "%f", lat_deg);
	gtk_entry_set_text(GTK_ENTRY(entry14), buf);
	g_sprintf(buf, "%f", lon_deg);
	gtk_entry_set_text(GTK_ENTRY(entry15), buf);
	
	
	combobox2 = lookup_widget(dialog, "combobox2");
	gtk_combo_box_set_active(GTK_COMBO_BOX(combobox2), 0);

}



void
set_poi(GtkWidget *dialog)
{
	GtkComboBox *combo_box;
	GtkTextView *text_view;
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	GtkWidget *entry, *radiobutton;

	const char *keyword;
	char *desc;
	char *sql;
	char *db;
	int visibility, price_range = 0, extended_open;
	int category, subcategory;
	double lat_deg, lon_deg;
	int res;
	double rand1, rand2;

	entry = lookup_widget(dialog, "entry14");
	
	lat_deg = parse_degrees(gtk_entry_get_text(GTK_ENTRY(entry)));
	entry = lookup_widget(dialog, "entry15");
	
	lon_deg = parse_degrees(gtk_entry_get_text(GTK_ENTRY(entry)));
	radiobutton = lookup_widget(dialog, "radiobutton11");
	visibility = (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton))) ? 1 : 0;	
	combo_box = GTK_COMBO_BOX(lookup_widget(dialog, "combobox2"));
	category = gtk_combo_box_get_active(combo_box);
	subcategory = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox_subcat));
	entry = lookup_widget(dialog, "entry13");
	keyword = gtk_entry_get_text(GTK_ENTRY(entry));
	text_view = GTK_TEXT_VIEW(lookup_widget(dialog, "textview1"));
	buffer = gtk_text_view_get_buffer(text_view);
	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);
	desc = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
	radiobutton = lookup_widget(dialog, "radiobutton8");
	price_range = (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton))) ? 1 : price_range;
	radiobutton = lookup_widget(dialog, "radiobutton9");
	price_range = (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton))) ? 3 : price_range;
	radiobutton = lookup_widget(dialog, "radiobutton10");
	price_range = (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton))) ? 5 : price_range;
	radiobutton = lookup_widget(dialog, "checkbutton10");
	extended_open = (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton))) ? 1 : 0;

	
	rand1 = g_random_double_range (100000000,1000000000);
	rand2 = g_random_double_range (100000000,1000000000);

	
	db = g_strconcat(foxtrotgps_dir, "/", POI_DB, NULL);	
	
	sql = sqlite3_mprintf ( 	
			"INSERT INTO poi "
			"(idmd5, lat, lon, visibility, cat, subcat, keywords, desc, price_range, extended_open) "
			"VALUES ('%.0f%.0f',%f,%f,%d,%d,%d,%Q,%Q,%d,%d)",
			rand1, rand2, lat_deg, lon_deg, visibility, category, subcategory, 
			keyword, desc, price_range, extended_open);

	res = sql_execute(db, sql, NULL);
	
	if(res==1)
	{
		sql_execute(db, POI_DB_CREATE, NULL);
		sql_execute(db, sql, NULL);
	}

	g_free(desc);
	sqlite3_free (sql);
	gtk_widget_destroy(dialog);
	
	
	global_poi_cat = category;
}


void
update_poi(GtkWidget *dialog)
{

	GtkTextView *text_view;
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	GtkWidget *entry, *widget; 

	const char *keyword, *idmd5;
	char *desc;
	char *sql;
	char *db;


	double lat_deg, lon_deg;
	int res;


	widget = lookup_widget(dialog, "label126");
	idmd5 = gtk_label_get_text(GTK_LABEL(widget));
	
	entry = lookup_widget(dialog, "entry17");
	
	lat_deg = parse_degrees(gtk_entry_get_text(GTK_ENTRY(entry)));
	entry = lookup_widget(dialog, "entry18");
	
	lon_deg = parse_degrees(gtk_entry_get_text(GTK_ENTRY(entry)));



	



	entry = lookup_widget(dialog, "entry19");
	keyword = gtk_entry_get_text(GTK_ENTRY(entry));
	text_view = GTK_TEXT_VIEW(lookup_widget(dialog, "textview2"));
	buffer = gtk_text_view_get_buffer(text_view);
	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);
	desc = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);


	db = g_strconcat(foxtrotgps_dir, "/", POI_DB, NULL);	
	


	sql = sqlite3_mprintf ( 	
			"UPDATE "
				"poi "
			"SET "
				"lat=%f,"
				"lon=%f,"
				"keywords=%Q,"
				"desc=%Q"
			"WHERE "
				"idmd5='%s'" 
			,
			lat_deg, lon_deg, 
			keyword, desc, idmd5);

	res = sql_execute(db, sql, NULL);
	
	if(res==1)
	{
		sql_execute(db, POI_DB_CREATE, NULL);
		sql_execute(db, sql, NULL);
	}

	g_free(desc);
	sqlite3_free (sql);
	
	gtk_widget_destroy(dialog);
	
	

}





void
delete_poi(poi_t *p)
{
	char *db;
	char *sql;
	int res;

	db = g_strconcat(foxtrotgps_dir, "/", POI_DB, NULL);	
	
	sql = g_strdup_printf( 	
			"DELETE FROM "
				"poi "
			"WHERE "
				"idmd5='%s'" 
			, p->idmd5);

	res = sql_execute(db, sql, NULL);
	

	repaint_all();

	
	
}





void
get_pois()
{
	char sql[256];
	char *db;
	bbox_t bbox;

	bbox = get_bbox_deg();

	db = g_strconcat(foxtrotgps_dir, "/", POI_DB, NULL);

	
	if(poi_list) g_slist_free(poi_list);
	poi_list = NULL;
	
	
	
	if(global_poi_cat==0)
	{
		g_snprintf(sql, 256, 
				"SELECT * FROM poi "
				"WHERE lat<%f AND lat>%f AND lon>%f AND lon<%f "
				"LIMIT 1000;",
				bbox.lat1,bbox.lat2,
				bbox.lon1, bbox.lon2
				);
	}
	else if(global_poi_cat>=1)
	{

		g_snprintf(sql, 256, 
				"SELECT * FROM poi "
				"WHERE  cat=%d AND lat<%f AND lat>%f AND lon>%f AND lon<%f "
				"LIMIT 1000;",
				global_poi_cat,
				bbox.lat1,bbox.lat2,
				bbox.lon1, bbox.lon2
				);		
		
	}
	


	
	if(poi_list)
	{
		g_slist_free(poi_list);
		poi_list = NULL;
	}
	sql_execute(db, sql, sql_cb__poi_get);	
	
	
	global_show_pois = TRUE;
	
}

void
show_poi_detail()
{
	GtkWidget *window, *widget;
	GtkWidget *label;
	GSList *list;
	gchar *buffer = NULL, *buffer2 = NULL;
	gboolean poi_found = FALSE;
	float lat, lon,lat_deg,lon_deg;
	float distance=0;
	waypoint_t *wp = g_new0(waypoint_t, 1);
	poi_t *p, *this_poi = NULL;
	
	GladeXML *gladexml = glade_xml_new (gladefile,
					    "window5",
					    GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	window = glade_xml_get_widget (gladexml, "window5");
	g_signal_connect_swapped (window, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);

	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	

	
	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);

	if(gpsdata !=NULL && !global_myposition.lat && !global_myposition.lon)
	{
		distance = 	6371.0 *  
				acos(sin(deg2rad(gpsdata->fix.latitude)) * 
				sin(lat) +
		
				cos(deg2rad(gpsdata->fix.latitude)) * 
				cos(lat) * 
				cos(lon - deg2rad(gpsdata->fix.longitude)) );
	}
	else if(global_myposition.lat && global_myposition.lon)
	{
		distance = 	6371.0 *  
				acos(sin(deg2rad(global_myposition.lat)) * 
				sin(lat) +
		
				cos(deg2rad(global_myposition.lat)) * 
				cos(lat) * 
				cos(lon - deg2rad(global_myposition.lon)) );
				
	}
	
	label = lookup_widget(window,"label110");
	
	

	
	
	
	for(list = poi_list; list != NULL; list = list->next)
	{
		p = list->data;

		if(abs(p->screen_x - mouse_x) < 12 &&
		   abs(p->screen_y - mouse_y) < 12 )
		   
		{
			buffer = g_strdup_printf( 
				"<b>%s</b> ",
				my_strescape_back(p->keywords,NULL));
			buffer2 = g_strdup_printf (_("%s\n\nDistance: %.3fkm"),
				my_strescape_back(p->desc,NULL), distance);
			poi_found = TRUE;
			
			wp->lat = deg2rad(p->lat_deg);
			wp->lon = deg2rad(p->lon_deg);
			
			this_poi = list->data;
		}
	
	}
	
	if(!poi_found)
		buffer = g_strdup (_("<b>No POI found</b>\n"));
	
	gtk_label_set_label(GTK_LABEL(label),buffer);
	
	label = lookup_widget(window,"label111");
	gtk_label_set_label(GTK_LABEL(label), buffer2);

	widget = lookup_widget(window, "button27");
	g_signal_connect (	(gpointer) widget, "clicked",
				G_CALLBACK (on_button27_clicked),
				(gpointer) wp);
	
	if (this_poi != NULL)
	{
		this_poi->widget = window;

		widget = lookup_widget(window, "button33");
		g_signal_connect (	(gpointer) widget, "clicked",
					G_CALLBACK (on_button33_clicked),
					(gpointer) this_poi);
		
		widget = lookup_widget(window, "button34");
		g_signal_connect (	(gpointer) widget, "clicked",
					G_CALLBACK (on_button34_clicked),
					(gpointer) this_poi);
	}
	
	gtk_widget_show(window);
	

}


gchar *
my_strescape_back (const gchar *source,
	     const gchar *exceptions)
{
  const guchar *p;
  gchar *dest;
  gchar *q;
  guchar excmap[256];

  g_return_val_if_fail (source != NULL, NULL);

  p = (guchar *) source;
  
  q = dest = g_malloc (strlen (source) * 4 + 1);

  memset (excmap, 0, 256);
  if (exceptions)
    {
      guchar *e = (guchar *) exceptions;

      while (*e)
	{
	  excmap[*e] = 1;
	  e++;
	}
    }

  while (*p)
    {

	  switch (*p)
	    {

	    case '&':
		    *q++ = '&';
		*q++ = 'a';
	    	*q++ = 'm';
	    	*q++ = 'p';
	    	*q++ = ';';
	    	break;
	    default:
		*q++ = *p;
	      break;
	    }
	
      p++;
    }
  *q = 0;
  return dest;
}
