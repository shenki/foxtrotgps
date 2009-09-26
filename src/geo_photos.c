
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "globals.h"
#include "geo_photos.h"
#include "converter.h"
#include "util.h"
#include "support.h"
#include "interface.h"
#include "exif.h"
#include "tracks.h"
#include "tile_management.h"

#include <glib.h>
#include <gio/gio.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <libexif/exif-data.h>
#include <time.h>


#define PHOTO_DB "geophoto.db"

GList *geocode_photo_list;
GtkWidget *dialog_image_data = NULL;
GtkWidget *dialog_photo_correlate = NULL;
GtkWidget *dialog_geocode_result = NULL;

char *geocode_photodir	= NULL;
char *geocode_trackname	= NULL;
int geocode_correction = 0;
int geocode_timezone = 0;
gboolean add_to_database = TRUE;
struct tm tm_photo;


void geocode_set_photodir (char *dirname,   GtkWidget *widget);
void geocode_set_trackname(char *trackname, GtkWidget *widget);

char     *get_basename(char *file);
GList   *get_entries_from_dir(char *dirname);
gboolean  file_type_test(const char *file, char *type);

void update_gps_time_label();
gpointer geocode_thread(gpointer user_data);
void prepare_perl();





static int
sql_cb__photo(void *unused, int colc, char **colv, char **col_names)
{
	photo_t *photo = g_new0(photo_t,1);

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	photo->filename = g_strdup(colv[0]);
	photo->name	= g_strdup(colv[1]);
	photo->lat	= atof(colv[2]);
	photo->lon	= atof(colv[3]);
	photo->desc	= g_strdup(colv[4]);
	
	photo_list = g_slist_prepend(photo_list, photo);

	return 0;
}







void
paint_photos()
{
	
	
	int pixel_x, pixel_y, x, y;
	float lat, lon;
	GSList *list;
	GdkColor color;
	GError	*error = NULL;
	static GdkPixbuf *photo_icon = NULL;
	static GdkGC *gc;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);


	
	if (!gc)
		gc = gdk_gc_new(pixmap); 
	color.green = 0;
	color.blue = 60000;
	color.red = 0;
	gdk_gc_set_rgb_fg_color(gc, &color);
	

	if(!photo_icon)
	{
		photo_icon = gdk_pixbuf_new_from_file_at_size (
			PACKAGE_PIXMAPS_DIR "/tangogps-photo.png", 24,24,
			&error);
	}

	if(global_show_photos)
	{
		get_photos();
		
		for(list = photo_list; list != NULL; list = list->next)
		{
			photo_t *p = list->data;
			GdkPixbuf *thumb = NULL, *pixbuf_ptr;
		
			lat = deg2rad(p->lat);
			lon = deg2rad(p->lon);
			
			
			
			pixel_x = lon2pixel(global_zoom, lon);
			pixel_y = lat2pixel(global_zoom, lat);
			
			x = pixel_x - global_x;
			y = pixel_y - global_y;
			
			p->screen_x = x;
			p->screen_y = y;
			
			
			
			if(global_zoom >= 17)
			{
				thumb = gdk_pixbuf_new_from_file_at_scale (p->filename, 48, 48, FALSE, &error);
				if(!thumb)
					printf("could not open %s \n", p->filename);
				else
					printf("loading thumb %s okay \n", p->filename);
			}
			
			if(!photo_icon && !thumb)
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
				int icon_size;
				
				if(global_zoom >= 17 && thumb)
				{
					pixbuf_ptr = thumb;
					icon_size = 48;
				}	
				else
				{
					pixbuf_ptr = photo_icon;
					icon_size = 24;
				}
				gdk_draw_pixbuf (
					pixmap,
					NULL,
					pixbuf_ptr,
					0,0,
					x-icon_size/2,y-icon_size/2,
					icon_size,icon_size,
					GDK_RGB_DITHER_NONE, 0, 0);
				
			}
			
			gtk_widget_queue_draw_area (
					map_drawable, 
					x-18, y-18,
					36,36);
			
			printf("PHOTO: %s lat %f - lon %f\n",p->name,p->lat, p->lon);
		}	
	}
}


void
get_photos()
{
	char *sql, *db;
	bbox_t bbox = get_bbox_deg();
	
	db = g_strconcat(tangogps_dir,"/", PHOTO_DB, NULL);
	
	
	
	if(photo_list)
		g_slist_free(photo_list);
	photo_list = NULL;
	
	
	
	sql = g_strdup_printf(	
			"SELECT * FROM photo "
			"WHERE lat<%f AND lat>%f AND lon>%f AND lon<%f "
			"LIMIT 500;",
			bbox.lat1,bbox.lat2,
			bbox.lon1, bbox.lon2	);
printf("%s \n",sql);
	
	sql_execute(db, sql, sql_cb__photo);	
	
	
	
}

void
geo_photos_open_dialog_photo_correlate()
{		
	GtkWidget *label1, *label2;
	char *label_txt;
	int tmp;
printf("%s\n",__PRETTY_FUNCTION__);	
	if(!dialog_photo_correlate)
	{
		dialog_photo_correlate = create_dialog_geocode();
		
		
		tmp   = gconf_client_get_int(global_gconfclient, GCONF"/geocode_timezone", NULL);
		geocode_timezone = (tmp) ? tmp - 13 : 0 ;
		geocode_correction = gconf_client_get_int(global_gconfclient, GCONF"/geocode_correction", NULL);
		
		
		label1 = lookup_widget(dialog_photo_correlate, "label172");
		label2 = lookup_widget(dialog_photo_correlate, "label174");
		
		label_txt = g_strdup_printf("  %d seconds", geocode_correction);
		gtk_label_set_label(GTK_LABEL(label2), label_txt);
		
		label_txt = g_strdup_printf("  %d:00h", geocode_timezone);
		gtk_label_set_label(GTK_LABEL(label1), label_txt);
		
	}

	gtk_widget_show(dialog_photo_correlate);

}

void
geo_photos_open_dialog_image_data()
{
	GtkWidget *combobox, *entry;

	if(!dialog_image_data)
	{
		dialog_image_data = create_dialog_image_data();
		gtk_widget_show(dialog_image_data);
		
		combobox = lookup_widget(dialog_image_data, "combobox7");
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), geocode_timezone + 12);
		entry = lookup_widget(dialog_image_data, "entry28");
		gtk_entry_set_text(GTK_ENTRY(entry), g_strdup_printf("%d", geocode_correction));

		geo_photo_dialog_image_data_next(dialog_image_data, NULL, GEOPHOTO_FIRST);
	}
	
	gtk_widget_show(dialog_image_data);
	gtk_widget_hide(dialog_photo_correlate);
}

	

void
geo_photos_geocode_track_select_dialog (GtkButton       *button,
					gpointer         user_data)
{
	GtkWidget *widget;
	GtkFileFilter *filter;



	
	widget = gtk_file_chooser_dialog_new (
			"Select a GPS track log",
			NULL,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			NULL);

	
	gtk_file_chooser_set_action (GTK_FILE_CHOOSER(widget), GTK_FILE_CHOOSER_ACTION_OPEN );  
	gtk_file_chooser_set_select_multiple  (GTK_FILE_CHOOSER(widget), FALSE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(widget),global_track_dir);
	
	
	filter = gtk_file_filter_new ();
	gtk_file_filter_add_pattern (filter, "*.gpx");
	gtk_file_filter_add_pattern (filter, "*.GPX");
	gtk_file_filter_set_name (filter, "GPX trace log files (*.gpx)");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(widget), filter);
	

	filter = gtk_file_filter_new ();
	gtk_file_filter_add_pattern (filter, "*.log");
	gtk_file_filter_set_name (filter, "tangoGPS log files (*.log)");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(widget), filter);

	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER(widget), filter);


	
	if (gtk_dialog_run (GTK_DIALOG (widget)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget));
		printf ("%s \n",filename);
		
		
		geocode_set_trackname(filename, GTK_WIDGET(button));
		
		if(file_type_test(filename, "log"))
			tracks_on_file_button_release_event(NULL, NULL, filename);
		else
			printf("There is no GPX importer yet :-( \n");
		
		g_free (filename);
	}
	else
		printf("%s(): file dialog cancelled \n", __PRETTY_FUNCTION__);
	
	gtk_widget_destroy (widget);
	
}


void
geo_photos_geocode_dir_select_dialog (GtkButton       *button,
                               	   gpointer         user_data)
{
	GtkWidget *widget;


	
	widget = gtk_file_chooser_dialog_new (
			"Choose the directory containing your photos",
			NULL,
			GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, 
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			NULL);

	
	gtk_file_chooser_set_select_multiple  (GTK_FILE_CHOOSER(widget), FALSE);
	


	
	if (gtk_dialog_run (GTK_DIALOG (widget)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget));
		printf ("%s \n",filename);
		
		
		geocode_set_photodir(filename, GTK_WIDGET(button));
		
		g_free (filename);
	}
	else
		printf("%s(): file dialog cancelled \n", __PRETTY_FUNCTION__);
	
	gtk_widget_destroy (widget);
}



void
geocode_set_trackname(char *trackname, GtkWidget *widget)
{
	GtkWidget *label, *image, *button;
	
	geocode_trackname = g_strdup(trackname);
	
	image = gtk_image_new_from_stock("gtk-open", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_image(GTK_BUTTON(widget), image);
	label = lookup_widget(widget, "label154");
	gtk_label_set_label(GTK_LABEL(label), "<span color=\"#090\"><b>ok</b></span>");
	gtk_button_set_label(GTK_BUTTON(widget), get_basename(geocode_trackname));
	
	button = lookup_widget(widget, "okbutton8");
	if(geocode_photodir)
		gtk_widget_set_sensitive(button, TRUE);
}


void
geocode_set_photodir(char *photodir, GtkWidget *widget)
{
	GtkWidget *label, *image, *button;
	
	geocode_photodir = g_strdup(photodir);
	
	if(geocode_photo_list)
	{
		g_list_free(geocode_photo_list);
		geocode_photo_list = NULL;
		gtk_widget_destroy(dialog_image_data);
		dialog_image_data = NULL;
	}
	
	geocode_photo_list = get_entries_from_dir(geocode_photodir);
	
	image = gtk_image_new_from_stock("gtk-open", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_image(GTK_BUTTON(widget), image);
	label = lookup_widget(widget, "label155");
	gtk_label_set_label(GTK_LABEL(label), "<span color=\"#090\"><b>ok</b></span>");
	gtk_button_set_label(GTK_BUTTON(widget), get_basename(geocode_photodir));
	
	button = lookup_widget(widget, "button44");
	gtk_widget_set_sensitive(button, TRUE);
		
	
	button = lookup_widget(widget, "okbutton8");
	if(geocode_trackname)
		gtk_widget_set_sensitive(button, TRUE);

		

}


void
geo_photos_dialog_image_data_next()
{
	
}

char *
get_basename(char *file)
{
	char **array;
	char *basename;
	int i = 0;
	
	array = g_strsplit(file, "/", -1);
	while (array[i]) i++;
		
	basename = g_strdup(array[i-1]);
	g_strfreev(array);
	
	return basename;
}

GList *
get_entries_from_dir(char *dirname)
{
	GDir *dir;
	const char *file;
	GList *list = NULL;
	gboolean isfile;
	GError *error;
	
	dir = g_dir_open(dirname, 0, &error);
	if(!dir)
		return NULL;
	
	file = g_dir_read_name(dir);
	
	while (file)
	{
		char *fullfile = g_strconcat(dirname,"/",file,NULL);
		
		isfile = g_file_test(fullfile, G_FILE_TEST_IS_REGULAR);
		if(isfile &&
		   (file_type_test(fullfile,"jpg") || file_type_test(fullfile,"JPG") ||
		    file_type_test(fullfile,"jpeg")  || file_type_test(fullfile,"JPEG"))	
		)
		{		
			printf("pic: %s/%s \n", dirname, file);
			list = g_list_insert_sorted(list, g_strconcat(dirname, "/", file, NULL), (GCompareFunc)g_strcmp0);
		}
		file = g_dir_read_name(dir);
	}
	
	g_dir_close(dir);

	return list;
}


gboolean
file_type_test(const char *file, char *type)
{
	char **arr;
	int i = 0;
	
	arr = g_strsplit(file, ".", -1);
	while (arr[i]) i++;
	
	if (g_strcmp0(arr[i-1], type))
		return FALSE;
	
	return TRUE;
}




void
geo_photo_dialog_image_data_next(GtkWidget *widget, gpointer user_data, geo_photo_move_e move)
{
	GtkWidget *image, *viewport, *label, *forward_button, *back_button, *first_button, *last_button, *zoom_button;
	static GdkPixbuf *pixbuf = NULL;
	GError *err = NULL;
	int height, img_width;
	gboolean fullsize = FALSE;
	char *datetime;
	ExifData *ed;
	
	image = lookup_widget(widget, "image5");
	viewport = lookup_widget(widget, "viewport8");
	label = lookup_widget(widget, "label163");
	forward_button = lookup_widget(widget, "button46");
	back_button = lookup_widget(widget, "button45");
	first_button = lookup_widget(widget, "button47");
	last_button = lookup_widget(widget, "button48");
	zoom_button = lookup_widget(widget, "button50");
	

	printf("%s: viewport h,w: %d %d \n", __PRETTY_FUNCTION__, viewport->allocation.height, viewport->allocation.width);
	height = viewport->allocation.height;
	
	switch (move)
	{	
	  case  GEOPHOTO_NEXT:
		if(geocode_photo_list->next)
		{
			geocode_photo_list = geocode_photo_list->next;
			gtk_widget_set_sensitive (back_button, TRUE);
			gtk_widget_set_sensitive (first_button, TRUE);
		}
		if(!geocode_photo_list->next)
		{
			gtk_widget_set_sensitive (forward_button, FALSE);
			gtk_widget_set_sensitive (last_button, FALSE);
		}
		gtk_widget_set_sensitive(zoom_button, TRUE);
		break;
	  case  GEOPHOTO_PREV:
		if(geocode_photo_list->prev)
		{
			geocode_photo_list = geocode_photo_list->prev;
			gtk_widget_set_sensitive (forward_button, TRUE);
			gtk_widget_set_sensitive (last_button, TRUE);
		}
		if(!geocode_photo_list->prev)
		{
			gtk_widget_set_sensitive (back_button, FALSE);
			gtk_widget_set_sensitive (first_button, FALSE);
		}
		gtk_widget_set_sensitive(zoom_button, TRUE);
		break;
	  case  GEOPHOTO_FIRST:
		geocode_photo_list = g_list_first(geocode_photo_list);
	  	gtk_widget_set_sensitive (forward_button, TRUE);
	  	gtk_widget_set_sensitive (last_button, TRUE);
	  	gtk_widget_set_sensitive (back_button, FALSE);
	  	gtk_widget_set_sensitive (first_button, FALSE);
		gtk_widget_set_sensitive(zoom_button, TRUE);
		break;
	  case  GEOPHOTO_LAST:
		geocode_photo_list = g_list_last(geocode_photo_list);
	  	gtk_widget_set_sensitive (back_button, TRUE);
	  	gtk_widget_set_sensitive (first_button, TRUE);
	  	gtk_widget_set_sensitive (forward_button, FALSE);
	  	gtk_widget_set_sensitive (last_button, FALSE);
		gtk_widget_set_sensitive(zoom_button, TRUE);
		break;
	  case  GEOPHOTO_FULLSIZE:
		fullsize = TRUE;
	}

	if (pixbuf)
		g_object_unref (pixbuf);
	
	if(!fullsize)
	{
		pixbuf = gdk_pixbuf_new_from_file_at_scale((const gchar *) geocode_photo_list->data, -1, height, TRUE, &err);
		if(!pixbuf)
			printf("%s loading pixbuf failed - actually this should not happen\n", __PRETTY_FUNCTION__);
		
		gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
	}
	else
	{
		gtk_image_set_from_file(GTK_IMAGE(image), (const gchar *) geocode_photo_list->data);
		img_width = gdk_pixbuf_get_width(gtk_image_get_pixbuf(GTK_IMAGE(image)));
	}
		
	ed = exif_data_new_from_file((const gchar *) geocode_photo_list->data);
	if (!ed) {
		printf("File not readable or no EXIF data in file %s\n", (const gchar *) geocode_photo_list->data);
		return;
	}

        datetime = show_tag(ed, EXIF_IFD_0, EXIF_TAG_DATE_TIME);
	strptime(datetime, "%Y:%m:%d %H:%M:%S", &tm_photo);
	
	gtk_label_set_label(GTK_LABEL(label), datetime);
	update_gps_time_label();
	
	gtk_widget_show (image);
}


void
geo_photo_close_dialog_image_data()
{
	GtkWidget *entry, *label1, *label2, *combobox;
	const char *txt;
	char *label_txt;
	
	entry = lookup_widget(dialog_image_data, "entry28");
	combobox = lookup_widget(dialog_image_data, "combobox7");
	
	geocode_timezone = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox))-12;
	
	label1 = lookup_widget(dialog_photo_correlate, "label172");
	label2 = lookup_widget(dialog_photo_correlate, "label174");
	
	txt = gtk_entry_get_text(GTK_ENTRY(entry));
	geocode_correction = atoi(txt);
	
	label_txt = g_strdup_printf("  %d seconds", geocode_correction);
	gtk_label_set_label(GTK_LABEL(label2), label_txt);
	
	label_txt = g_strdup_printf("  %d:00h", geocode_timezone);
	gtk_label_set_label(GTK_LABEL(label1), label_txt);
	
	gconf_client_set_int(global_gconfclient, GCONF"/geocode_correction", geocode_correction, NULL);
	gconf_client_set_int(global_gconfclient, GCONF"/geocode_timezone", geocode_timezone+13, NULL);
	
	gtk_widget_hide(dialog_image_data);
	gtk_widget_show(dialog_photo_correlate);
}

void
geo_photo_cancel_dialog_image_data()
{
	gtk_widget_hide(dialog_image_data);
	gtk_widget_show(dialog_photo_correlate);	
}


void
geo_photo_cancel_dialog_photo_correlate()
{
	gtk_widget_hide(dialog_photo_correlate);
}

void
geo_photo_set_timezone(GtkComboBox *combobox)
{
	geocode_timezone = gtk_combo_box_get_active(combobox)-12;
	update_gps_time_label();
}

void
geo_photo_set_add_to_database(GtkToggleButton *togglebutton)
{
	add_to_database = gtk_toggle_button_get_active(togglebutton);
	printf("add_to_database: %d\n", add_to_database);
}

void
geo_photo_close_dialog_photo_correlate()
{
	gchar *command_line;

	prepare_perl();
	
	dialog_geocode_result = create_dialog_geocode_result();

	gtk_widget_show(dialog_geocode_result);
	gtk_widget_hide(dialog_photo_correlate);

	command_line = g_strdup_printf("/tmp/tangogps_geocode.pl '%s' '%s' '%d' '%d' '%d'", 
					geocode_trackname, 
					geocode_photodir,
					geocode_timezone,
					geocode_correction,
					add_to_database);
printf("commandline out thread: %s\n", command_line);	
	
	g_thread_create(geocode_thread, command_line, FALSE, NULL);
	
}




void
geo_photo_correction_entry_cb(GtkEditable *editable)
{
	update_gps_time_label();
}

void
update_gps_time_label()
{
	GtkWidget *label, *entry, *combobox;
	int correction;
	int timezone;
	time_t time;
	struct tm *tm_gps;
	char buf[1024];
	
	
	label = lookup_widget(dialog_image_data, "label171");
	entry = lookup_widget(dialog_image_data, "entry28");
	combobox = lookup_widget(dialog_image_data, "combobox7");
	
	correction = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
	timezone = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox))-12;

	time = mktime(&tm_photo) + correction - timezone*3600;

	tm_gps = localtime(&time);
	printf("timezone: %d\n", timezone);	

	strftime(buf, sizeof(buf), "<span color=\"#009\">%a %Y-%m-%d %H:%M:%S</span>", tm_gps);
	
	gtk_label_set_label(GTK_LABEL(label), buf);
}







gpointer
geocode_thread(gpointer user_data)
{
	GtkWidget *label, *item;
	gchar *standard_output;
	gchar *standard_error;
	gint exit_status;
	GError *err = NULL;
	char *command_line = (char *) user_data;
	gboolean res;

printf("commandline in thread: %s\n", command_line);	
	
	res = g_spawn_command_line_sync  (
				command_line, 
				&standard_output, 
				&standard_error,
				&exit_status,
				&err);
	
	if(!res)
	{
		fprintf (stderr, "Error running tangogps_geocode.pl: %s\n", err->message);
		g_error_free (err);
	}
	
	printf ("%s(): STDERR \n%s \nRET: %d \n", __PRETTY_FUNCTION__, standard_error, exit_status);
	
	gdk_threads_enter();
	
	label = lookup_widget(dialog_geocode_result, "label177");
	gtk_label_set_text(GTK_LABEL(label), g_strdup(standard_output));
	
	if(add_to_database)
	{
		item = lookup_widget(menu1, "item9");
		gtk_menu_item_activate (GTK_MENU_ITEM(item));
	}
	
	gdk_threads_leave();
	
	g_free(command_line);

	return NULL;
}


void
prepare_perl()
{
char *command;
FILE *fp;

{
	printf("* %s\n", __PRETTY_FUNCTION__);

	
	
	
	
	
	
	
command = g_strdup(
"#!/usr/bin/perl\n"
"\n"
"# (C)2008 Marcus Bauer, License: GPLv2, marus.bauer@gmail.com\n"
"\n"
"#\n"
"# helper for tangoGPS to geocode photos\n"
"#\n"
"\n"
"# needs: gpscorrelate, sqlite3, jhead\n"
"\n"
"# input:\n"
"# - .log or .gpx file\n"
"# - photo list\n"
"# - timezone\n"
"# - correction\n"
"# - do_insert2db\n"
"\n"
"# logic:\n"
"# - convert to gpx\n"
"# - correlate\n"
"# - in2db tangogps\n"
"\n"
"# gpscorrelate -g foo.gpx -z timezone --max-dist 120 --photooffset 5 p1.jpg ...\n"
"\n"
"$geocode_track = $ARGV[0];\n"
"$geocode_dir   = $ARGV[1];\n"
"$timezone      = $ARGV[2];\n"
"$correction    = $ARGV[3];\n"
"$do_insert2db  = $ARGV[4];\n"
"\n"
"$db = \"~/.tangogps/geophoto.db\";\n"
"\n"
"#===================  MAIN  ====================\n"
"\n"
"print STDERR \"\n"
"VARS: \n"
"  geocode_track = $ARGV[0];\n"
"  geocode_dir   = $ARGV[1];\n"
"  timezone      = $ARGV[2];\n"
"  correction    = $ARGV[3];\n"
"  do_insert2db  = $ARGV[4];\n"
"\";\n"
"\n"
"&test_for_helper_programs();\n"
"&get_photos_from_dir();\n"
"\n"
"&convert2gpx();\n"
"&correlate();\n"
"&insert2db();\n"
"\n"
"#==================  END MAIN  ==================\n"
"\n"
"sub test_for_helper_programs()\n"
"{\n"
"	# jhead, sqlite3, gpscorrelate\n"
"\n"
"	$missing_prog = 0;\n"
"\n"
"	if(system(\"jhead -h >/dev/null\") == -1){ $install .= \" jhead,\";	$missing_prog = 1;};\n"
"	if(system(\"sqlite3\") == -1)		 { $install .= \" sqlite3, \";	$missing_prog = 1;};\n"
"	if(system(\"gpscorrelate -h >/dev/null\")  == -1)	 { $install .= \" gpscorrelate\"; 	$missing_prog = 1;};\n"
"\n"
"	$error_msg = 	\"Hello, I couldn\'t find the following helper programs: \\n\\n\" .\n"
"			\"   $install \\n\\n\" .\n"
"			\"-> You can find them in your Linux distribution.\\n\\n\" .\n"
"			\"Please install them first and try again.\\n\";\n"
"\n"
"	if($missing_prog) {print STDOUT $error_msg;\n"
"	exit;}\n"
"}\n"
"\n"
"sub get_photos_from_dir()\n"
"{\n"
"	opendir(DIR, $geocode_dir) || die(\"Cannot open directory\");\n"
"	@photos= readdir(DIR);\n"
"	closedir(DIR);\n"
"}\n"
"\n"
"sub convert2gpx\n"
"{\n"
"	# test if *.log \n"
"	if($geocode_track =~ /\\.log$/)\n"
"	{\n"
"		&do_convert2gpx();\n"
"	}\n"
"}\n"
"\n"
"\n"
"sub correlate\n"
"{\n"
"	#\n"
"	# construct command line\n"
"	#\n"
"\n"
"	chdir($geocode_dir);\n"
"\n"
"	foreach(@photos)\n"
"	{\n"
"		if(	-f \"$_\"   && \n"
"			( ( $_ =~ /\\.jpg$/i ) ||\n"
"			  ( $_ =~ /\\.jpeg$/i)\n"
"			)\n"
"		  )\n"
"		{\n"
"			$photo_list .= \" \'$_\'\";\n"
"		}\n"
"		else { print STDERR \"not a file: $_ \\n\"; }\n"
"	}\n"
"\n"
"	# gpscorrelate ... \n"
"	$command_line =  \"gpscorrelate \"\n"
"			.\"-g \'$geocode_track\' \"\n"
"			.\"-z $timezone \"\n"
"			.\"--max-dist 120 \"\n"
"			.\"--photooffset $correction\"\n"
"			. $photo_list;\n"
"\n"
"	print STDERR \"$command_line\\n\";\n"
"\n"
"	$output = `$command_line`;\n"
"\n"
"	print STDOUT \"$output \\n\";\n"
"\n"
"}\n"
"\n"
"\n"
"sub insert2db()\n"
"{\n"
"	if($do_insert2db)\n"
"	{\n"
"		&do_insert2db();\n"
"	}\n"
"	else\n"
"	{\n"
"		print STDERR \"Not adding to tangoGPS database\\n\";\n"
"	}\n"
"\n"
"}\n"
"\n"
"\n"
"#=========== END MAIN FUCTIONS, START HELPER FUNCTIONS ===========\n"
"\n"
"\n"
"sub do_convert2gpx\n"
"{\n"
"	\n"
"#---  open track logfile ---\n"
"	\n"
"open (INFILE, $geocode_track) or die $!;\n"
"open (OUTFILE, \">/tmp/$$.gpx\") or die $!;\n"
"\n"
"\n"
"	\n"
"#--- start GPX ---\n"
"\n"
"$gpx = <<EOT\n"
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<gpx	version=\"1.0\"\n"
"	creator=\"convert2gpx.pl http://www.tangogps.org\"\n"
"	xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
"	xmlns=\"http://www.topografix.com/GPX/1/0\"\n"
"	xsi:schemaLocation=\"http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd\">\n"
"\n"
"<trk>\n"
"<trkseg>\n"
"EOT\n"
";\n"
"\n"
"\n"
"while (<INFILE>)\n"
"{\n"
"\n"
"@arr = split(\',\',$_);\n"
"chop @arr[6];\n"
"\n"
"$gpx .= <<EOT\n"
"<trkpt lat=\"@arr[0]\" lon=\"@arr[1]\">\n"
"  <ele>@arr[2]</ele>\n"
"  <speed>@arr[3]</speed>\n"
"  <course>@arr[4]</course>\n"
"  <fix>3d</fix>\n"
"  <hdop>@arr[5]</hdop>\n"
"  <time>@arr[6]</time>\n"
"</trkpt>\n"
"EOT\n"
";\n"
"\n"
"} #end while()\n"
"\n"
"\n"
"$gpx .= <<EOT\n"
"</trkseg>\n"
"</trk>\n"
"</gpx>\n"
"EOT\n"
";\n"
"\n"
"\n"
"\n"
"# write .gpx to /tmp/$$\n"
"print OUTFILE $gpx;\n"
"\n"
"# set geocode_track to filename\n"
"$geocode_track = \"/tmp/$$.gpx\";\n"
"\n"
"print STDERR \"track: $geocode_track\\n\"\n"
"}\n"
"\n"
"\n"
"#------------------------------------------------------------\n"
"\n"
"#---------------------------------------------\n"
"# get exif info from photo and put into db\n"
"#---------------------------------------------\n"
"\n"
"sub exif2db\n"
"{\n"
"\n"
"local($photo) = @_;\n"
"\n"
"# ------------------\n"
"# extract exif info\n"
"# ------------------\n"
"$lat_string = `jhead $photo | grep \"GPS Latitude\" `;\n"
"$lon_string = `jhead $photo | grep \"GPS Longitude\" `;\n"
"\n"
"\n"
"($lat_half, $lat_deg, $lat_min, $lat_sec) =\n"
"	$lat_string =~ /^GPS Latitude : (N|S) +(\\d+)d (\\d+)m +(\\d+\\.\\d+)s$/;\n"
"\n"
"($lon_half, $lon_deg, $lon_min, $lon_sec) =\n"
"	$lon_string =~ /^GPS Longitude: (E|W) +(\\d+)d (\\d+)m +(\\d+\\.\\d+)s$/;\n"
"\n"
"$lat = $lat_deg + $lat_min/60 + $lat_sec/3600;\n"
"$lat = ($lat_half eq \"N\") ? $lat : -$lat;\n"
"\n"
"$lon = $lon_deg + $lon_min/60 + $lon_sec/3600;\n"
"$lon = ($lon_half eq \"E\") ? $lon : -$lon;\n"
"\n"
"\n"
"#----------------------------\n"
"# extract filename from path \n"
"#----------------------------\n"
"$filename = \"\\\"\" . $photo . \"\\\"\";\n"
"$file =  `basename $filename` ;\n"
"chop $file;\n"
"$file = \"\\\"\" . $file . \"\\\"\";\n"
"$desc = \"\\\"unset\\\"\";\n"
"\n"
"\n"
"\n"
"print STDERR \"$file $lat - $lon\\n\";\n"
"\n"
"\n"
"#-----------------------\n"
"# insert into sqlite db\n"
"#-----------------------\n"
"\n"
"if ($lat !=0 && $lon !=0)\n"
"{\n"
"	$res = `sqlite3 $db \'INSERT INTO photo VALUES (\"$geocode_dir/$photo\",$file,$lat,$lon,$desc)\'`;\n"
"\n"
"	print STDERR $res;\n"
"}\n"
"\n"
"}\n"
"\n"
"\n"
"sub do_insert2db \n"
"{\n"
"\n"
"#-------------------------------------------\n"
"# create database if it does not yet exist\n"
"#-------------------------------------------\n"
"$sql = \"\n"
"CREATE TABLE \n"
"	photo (\n"
"		filename TEXT primary key, \n"
"		name TEXT, \n"
"		lat REAL, \n"
"		lon REAL, \n"
"		desc TEXT\n"
"	)\n"
"\";\n"
"$res = `sqlite3 $db \'$sql\'`;\n"
"\n"
"print STDERR $res;\n"
"\n"
"\n"
"#-----------------------\n"
"# insert photos into db\n"
"#----------------------\n"
"foreach(@photos)\n"
"{\n"
"	#\n"
"	# check if jpeg file\n"
"	#\n"
"	if(	-f \"$_\"   && \n"
"		( ( $_ =~ /\\.jpg$/i ) ||\n"
"		  ( $_ =~ /\\.jpeg$/i)\n"
"		)\n"
"	  )\n"
"	{\n"
"		&exif2db(\"$_\");\n"
"	}\n"
"}\n"
"\n"
"\n"
"}\n"
);
}


fp = fopen("/tmp/tangogps_geocode.pl", "w+");
if (fp==0) 
	printf("could not open tmp\n");	

fprintf(fp, "%s", command);
fclose(fp);

system ("chmod 700 /tmp/tangogps_geocode.pl");

}
