
#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "globals.h"
#include "tracks.h"
#include "interface.h"
#include "support.h"
#include "converter.h"
#include "map_management.h"

GSList *loaded_track;
GtkWidget *window12;

GtkWidget *
make_file_label(const char *file, char *full_file);

					
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
tracks_on_file_button_release_event      (	GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *drawingarea, *range;
	char *file;
	char line[121];
	char **arr;
	FILE *fd;
	float lat=0, lon=0, max_lat=-90, max_lon=-180, min_lat=90, min_lon=180, lat_tmp, lon_tmp;
	gboolean first_point = TRUE;
	int track_zoom, width, height;
	
	drawingarea = lookup_widget(window1, "drawingarea1");
	width  = drawingarea->allocation.width;
	height = drawingarea->allocation.height;
	
	file = (char *) user_data;
	
	g_slist_free(loaded_track);
	loaded_track = NULL;

	gtk_widget_destroy(window12);

	printf("+++++++++++++++++++++++++++++++++++++++++++ %s \n", file);
	fd = fopen(file, "r");
	while(fgets(line,120, fd))
	{
		
		trackpoint_t *tp = g_new0(trackpoint_t,1);
		
		arr = g_strsplit(line, ",", 2);
		
		
		if (arr[0] == NULL || arr[1] == NULL) continue;

		
		
		lat_tmp = atof(arr[0]);
		lon_tmp = atof(arr[1]);
		
		tp->lat = deg2rad(lat_tmp);
		tp->lon = deg2rad(lon_tmp);
		
		if(first_point)
		{
			lat = atof(arr[0]);
			lon = atof(arr[1]);
			first_point = FALSE;
		}
		
		max_lat = (lat_tmp>max_lat) ? lat_tmp : max_lat;
		min_lat = (lat_tmp<min_lat) ? lat_tmp : min_lat;
		max_lon = (lon_tmp>max_lon) ? lon_tmp : max_lon;
		min_lon = (lon_tmp<min_lon) ? lon_tmp : min_lon;
		
		
		loaded_track = g_slist_append(loaded_track, tp);
	}
	
	gtk_notebook_set_current_page(GTK_NOTEBOOK(lookup_widget(window1,"notebook1")), 0);


	
	
	
	track_zoom = get_zoom_covering(width, height, max_lat, min_lon, min_lat, max_lon);
	track_zoom = (track_zoom > 15) ? 15 : track_zoom;
	
	if(lat!=0 && lon!=0)
		set_mapcenter((max_lat+min_lat)/2, (max_lon+min_lon)/2, track_zoom);

printf("%.0f - %.0f ## %.0f - %.0f\n",max_lat,max_lon,min_lat,min_lon);
		
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
