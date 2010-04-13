
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "globals.h"
#include "tracks.h"
#include "interface.h"
#include "support.h"
#include "converter.h"
#include "map_management.h"
#include "tile_management.h"

GSList *loaded_track = NULL;
GtkWidget *window12;




GtkWidget *
make_file_label(const char *file, char *full_file);

bbox_t
get_track_bbox(GSList *track);

GSList *
load_log_file_into_list(char *file);

GSList *
load_gpx_file_into_list(char *file);

GSList *
parse_nodes(xmlNode *node);





void
tracks_open_tracks_dialog()
{
	GDir *dir;
	GError *err = NULL;
	const char *file;
	gboolean isfile;
	GList *list = NULL;

	GtkWidget *label, *vbox, *eventbox;
	

	dir = g_dir_open(global_track_dir, 0, &err);
	
	if (err != NULL)
	{
		fprintf (stderr, "Problem opening directory: %s\n", err->message);
		g_error_free (err);
		return;
	}
	
	
	
	window12 = create_window12();
	gtk_widget_show(window12);
	
	vbox = lookup_widget(window12, "vbox39");		
	
	
	
	file = g_dir_read_name(dir);

	while (file)
	{
		isfile = g_file_test(g_strconcat(global_track_dir,file,NULL), G_FILE_TEST_IS_REGULAR);
		
		if(isfile)
			list = g_list_insert_sorted( list, g_strdup(file), (GCompareFunc) g_strcmp0 );

		file = g_dir_read_name(dir);
	}

	for(; list!=NULL; list=list->next)
	{
		char *file = list->data;
		
		
		printf("%s \n", file);
		eventbox = gtk_event_box_new ();
		gtk_widget_set_events (eventbox, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_ENTER_NOTIFY_MASK);
		gtk_widget_show (eventbox);
		

		gtk_box_pack_start (GTK_BOX (vbox), eventbox, FALSE, FALSE, 0);
		
		label = make_file_label(file, g_strconcat(global_track_dir,file,NULL));
		gtk_widget_show(label);
		gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
		gtk_misc_set_padding (GTK_MISC (label), 3, 2);

		gtk_container_add (GTK_CONTAINER (eventbox), label);
		
		g_signal_connect ((gpointer) eventbox, "button_release_event",
				G_CALLBACK (tracks_on_file_button_release_event),
				g_strconcat(global_track_dir,file,NULL));
	}
	
	g_list_free(list);
	g_dir_close(dir);
}


GtkWidget *
make_file_label(const char *file, char *full_file)
{
	GtkWidget *label;
	
	label = gtk_label_new (g_strdup(file));
	
	return label;
}

gboolean
tracks_on_file_button_release_event   (	GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *drawingarea, *range;
	int track_zoom, width, height;
	char *file;
	bbox_t bbox;
	
	drawingarea = lookup_widget(window1, "drawingarea1");
	width  = drawingarea->allocation.width;
	height = drawingarea->allocation.height;
	
	file = (char *) user_data;
	
	gtk_widget_destroy(window12);

	if(loaded_track)
		g_slist_free(loaded_track);
	loaded_track = NULL;

	if (g_strrstr(file,".gpx") ||
	    g_strrstr(file,".GPX") ||
	    g_strrstr(file,".Gpx") )
	{
		loaded_track = load_gpx_file_into_list(file);
	}
	else
		loaded_track = load_log_file_into_list(file);
	
	
	
	gtk_notebook_set_current_page(GTK_NOTEBOOK(lookup_widget(window1,"notebook1")), 0);	
	
	
	bbox = get_track_bbox(loaded_track);
	
	track_zoom = get_zoom_covering(width, height, bbox.lat1, bbox.lon1, bbox.lat2, bbox.lon2);
	track_zoom = (track_zoom > 15) ? 15 : track_zoom;
	
	
	if(loaded_track)
		set_mapcenter(rad2deg((bbox.lat1+bbox.lat2)/2), rad2deg((bbox.lon1+bbox.lon2)/2), track_zoom);

	
	range = lookup_widget(window1, "vscale1");
	gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);

	paint_loaded_track();
	
	
	return FALSE;	
}


void
paint_loaded_track()
{
	
	GSList *list;
	int pixel_x, pixel_y, x,y, last_x = 0, last_y = 0;
	float lat, lon;
	GdkColor color;
	GdkGC *gc;
	gboolean is_line = FALSE;
	
	gc = gdk_gc_new(pixmap);
	color.green = 50000;
	color.blue = 0;
	color.red = 0;
	gdk_gc_set_rgb_fg_color(gc, &color);
	gdk_gc_set_line_attributes(gc,
		5, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);

	

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	for(list = loaded_track; list != NULL; list = list->next)
	{
		trackpoint_t *tp = list->data;
	
		lat = tp->lat;
		lon = tp->lon;
		
		
		
		
		pixel_x = lon2pixel(global_zoom, lon);
		pixel_y = lat2pixel(global_zoom, lat);
		
		x = pixel_x - global_x;
		y = pixel_y - global_y;
		

		if(is_line)
		{
			gdk_draw_line (pixmap, gc, x, y, last_x, last_y);
			gtk_widget_queue_draw_area (
				map_drawable, 
				x-4, y-4,
				8,8);
			
		}
		
		last_x = x;
		last_y = y;
		
		
		is_line = TRUE;
	}
}

bbox_t
get_track_bbox(GSList *track)
{
	GSList *list;
	bbox_t bbox;
	double lat, lon;
	
	bbox.lat1 =  -90;
	bbox.lon1 =  180;
	bbox.lat2 =   90;
	bbox.lon2 = -180;
	
	
	for(list = track; list != NULL; list = list->next)
	{
		trackpoint_t *tp = list->data;
	
		lat = tp->lat;
		lon = tp->lon;
		bbox.lat1 = (lat > bbox.lat1) ? lat : bbox.lat1;
		bbox.lat2 = (lat < bbox.lat2) ? lat : bbox.lat2;
		bbox.lon1 = (lon < bbox.lon1) ? lon : bbox.lon1;
		bbox.lon2 = (lon > bbox.lon2) ? lon : bbox.lon2;
	}
	
	return bbox;
}


GSList *
load_log_file_into_list(char *file)
{
	GSList *list = NULL;
	float lat, lon;
	char line[121];
	char **arr;
	FILE *fd;

	fd = fopen(file, "r");
	while(fgets(line,120, fd))
	{
		trackpoint_t *tp = g_new0(trackpoint_t,1);
		
		
		arr = g_strsplit(line, ",", 2);
		
		
		if (arr[0] == NULL || arr[1] == NULL) continue;

		
		lat = atof(arr[0]);
		lon = atof(arr[1]);
		
		tp->lat = deg2rad(lat);
		tp->lon = deg2rad(lon);		

		list = g_slist_append(list, tp);
	}
	
	return list;
}


GSList *
load_gpx_file_into_list(char *file)
{
	GSList *list = NULL;
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	
	
	LIBXML_TEST_VERSION
	
	doc = xmlReadFile(file, NULL, 0);
	
	if (doc == NULL) {
		printf("error: could not parse file %s\n", file);
	}
	
	root_element = xmlDocGetRootElement(doc);
	list = parse_nodes(root_element);
	
	xmlFreeDoc(doc);
	xmlCleanupParser();
	
	return list;
}


GSList *
parse_nodes(xmlNode *node)
{
	xmlNode *cur_node = NULL;
	GSList *list = NULL;


	for (cur_node = node; cur_node; cur_node = cur_node->next)
	{
		if (cur_node->type == XML_ELEMENT_NODE)			
		{
			if (xmlStrEqual(cur_node->name, BAD_CAST "trkpt"))
			{
				double lat, lon;
				trackpoint_t *tp = g_new0(trackpoint_t,1);
				
				lat = atof((char *)xmlGetProp(cur_node, BAD_CAST "lat"));
				lon = atof((char *)xmlGetProp(cur_node, BAD_CAST "lon"));
				
				tp->lat = deg2rad(lat);
				tp->lon = deg2rad(lon);		
		
				list = g_slist_append(list, tp);
			}
			else
			{
				printf("  OTHER XML ELEMENT: %s \n", cur_node->name);
			}
		}
		list = g_slist_concat(list, parse_nodes(cur_node->children));
	}
	
	return list;
}
