
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include <gtk/gtk.h>
#include <glib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <gps.h>


#include "globals.h"
#include "interface.h"
#include "support.h"
#include "converter.h"
#include "map_management.h"
#include "tile_management.h"
#include "tracks.h"
#include "util.h"

GSList *loaded_track = NULL;
GtkWidget *window12;
GtkWidget *dialog10;



GtkWidget *	make_file_label(const char *file, char *full_file);

bbox_t		get_track_bbox(GSList *track);

GSList *	load_log_file_into_list(char *file);
GSList *	load_gpx_file_into_list(char *file);
GSList * load_ols_XML_file_into_list(char *file);
GSList * load_kml_XML_file_into_list(char *file);
GSList * parse_gpx_nodes(xmlNode *node);
GSList * parse_ols_XML_nodes(xmlNode *node);
GSList * parse_kml_XML_nodes(xmlNode *node);

void * fetch_track_thread(void *ptr);
void * fetch_openrouteservice_track_thread(void *ptr);


void
reset_loaded_track()
{
	
	loaded_track = NULL;
}

void
paint_track()
{	
	GList *list;
	int pixel_x, pixel_y, x,y, last_x = 0, last_y = 0;
	int counter = -1, modulo, j=0;
	float lat, lon;
	GdkColor color;
	GdkGC *gc;
	gboolean is_line = FALSE;
	
	gc = gdk_gc_new(pixmap);
	color.green = 0;
	color.blue = 0;
	color.red = 60000;
	gdk_gc_set_rgb_fg_color(gc, &color);
	gdk_gc_set_line_attributes(gc,
		5, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);

	if (global_zoom < 16 && global_zoom > 10)
		modulo = exp2(16-global_zoom);
	else if (global_zoom <= 10)
		modulo = 32;
	else
		modulo = 1;
	
	for(list = trackpoint_list->tail; list != NULL; list = list->prev)
	{
		counter++;
		
		if (counter % modulo == 0)
		{
			j++;
			if (j > 300) 
			{
				break; 
			}
			
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


FILE *fp = NULL;



void
track_log()
{
	gchar buffer[256];
	const gchar *fixstr;
	time_t time_sec;
	struct tm *ts;
	int heartfreq = 42;
	
	
	if(gpsdata->valid)
	{
		
		time_sec = (time_t)gpsdata->fix.time;
		ts = gmtime(&time_sec);
		strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", ts);
		
		heartfreq = (hrmdata) ? hrmdata->freq : 0;

		switch (gpsdata->fix.mode) {
		default:
		case MODE_NOT_SEEN:
		case MODE_NO_FIX:
			fixstr = "none";
			break;
		case MODE_2D:
			fixstr = "2d";
			break;
		case MODE_3D:
			fixstr = "3d";
			break;
		}

		if (fp)
		{
			fprintf (fp, "\n"
			         "<trkpt lat=\"%f\" lon=\"%f\">\n"
			         "  <ele>%g</ele>\n"
			         "  <time>%s</time>\n"
			         "  <fix>%s</fix>\n"
			         "  <hdop>%g</hdop>\n"
			         "  <extensions>\n"
			         "    <gpxtpx:TrackPointExtension>\n",
			         gpsdata->fix.latitude,
			         gpsdata->fix.longitude,
			         gpsdata->fix.altitude,
			         buffer,
			         fixstr,
			         gpsdata->hdop);

			if (heartfreq > 0)
			{
				/* The TrackPointExtension schema defines
				   the lower bound on heart-rate to be 1. */

				fprintf (fp,
				 "      <gpxtpx:hr>%d</gpxtpx:hr>\n",
				         heartfreq);
			}

			fprintf (fp,
			         "      <gpxtpx:speed>%g</gpxtpx:speed>\n"
			         "      <gpxtpx:course>%g</gpxtpx:course>\n"
			         "    </gpxtpx:TrackPointExtension>\n"
			         "  </extensions>\n"
			         "</trkpt>\n",
			         gpsdata->fix.speed,
			         gpsdata->fix.heading);
      }
  }
}

void
track_log_open()
{
	time_t time_epoch_sec;
	struct tm  *tm_struct;
	gchar buffer[256];
	gchar *filename = NULL;
	GtkLabel *label76;
	gchar *labeltext;
	
	label76 = GTK_LABEL(lookup_widget(window1, "label76"));
	
	
	time_epoch_sec = time(NULL);
	tm_struct = localtime(&time_epoch_sec);
	
	
	

	strftime (buffer, sizeof (buffer), "%Y%m%d_%H%M%S%z.gpx", tm_struct);

	
	filename = g_strconcat(global_track_dir, buffer,NULL);
	
	printf("*** %s(): %s\n",__PRETTY_FUNCTION__,filename);
	
	if(fp==NULL && trip_logger_on)
	{
		fp = fopen(filename,"w");
		if(!fp)
		{
			printf (_("oops: %s\n"), strerror (errno));
			perror (_("Triplog open failed: "));
			gtk_label_set_label (label76,
			                     _("<span foreground='#ff0000'>"
			                       "Error opening logfile"
			                       "</span>"));
		}
		else 
		{
			labeltext = g_strdup_printf (_("<b><span foreground='#0000ff'>Log: %s</span></b>"), buffer);
			gtk_label_set_label(label76,labeltext);
			g_free(labeltext);	

			fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			            "<gpx version=\"1.1\"\n"
			            "     creator=\"" PACKAGE_NAME " " PACKAGE_VERSION "\"\n"
			            "     xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			            "     xmlns:gpxtpx=\"http://www.garmin.com/xmlschemas/TrackPointExtension/v2\"\n"
			            "     xmlns=\"http://www.topografix.com/GPX/1/1\"\n"
			            "     xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1\n"
			            "                         http://www.topografix.com/GPX/1/1/gpx.xsd\n"
			            "                         http://www.garmin.com/xmlschemas/TrackPointExtension/v2\n"
			            "                         http://www8.garmin.com/xmlschemas/TrackPointExtensionv2.xsd\">\n"
			            "<trk>\n"
			            "<trkseg>\n");
		}
	}
	
	g_free(filename);
}


void
track_log_close()
{
	int ret;
	GtkLabel *label76;
	label76 = GTK_LABEL(lookup_widget(window1, "label76"));
	gtk_label_set_label(label76,"");
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	if(fp) {
		printf("closing FP\n");

		fprintf (fp, "\n"
		         "</trkseg>\n"
		         "</trk>\n"
		         "</gpx>\n");

		ret = fclose(fp);
		fp = NULL;
	
		if(ret) printf("ERROR closing file\n");
	}
}




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
		fprintf (stderr, _("Problem opening directory: %s\n"),
		         err->message);
		g_error_free (err);
		return;
	}
	
	
	
	window12 = glade_xml_get_widget(gladexml, "window12");
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

void
show_bbox (bbox_t bbox) 
{
	GtkWidget *drawingarea, *range;
	int track_zoom, width, height;

	drawingarea = lookup_widget (window1, "drawingarea1");
	width  = drawingarea->allocation.width;
	height = drawingarea->allocation.height;

	track_zoom = get_zoom_covering (width, height,
	                                bbox.lat1, bbox.lon1,
	                                bbox.lat2, bbox.lon2);
	track_zoom = (track_zoom > 15) ? 15 : track_zoom;

	set_mapcenter (rad2deg ((bbox.lat1+bbox.lat2)/2),
	               rad2deg ((bbox.lon1+bbox.lon2)/2),
	               track_zoom);

	range = lookup_widget (window1, "vscale1");
	gtk_range_set_value (GTK_RANGE (range), (double) global_zoom);
}

gboolean
tracks_on_file_button_release_event   (	GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *widget_tmp;
	char *file;
	bbox_t bbox;
	
	widget_tmp = lookup_widget(window1, "button79");
	gtk_widget_show(widget_tmp);
	
	file = (char *) user_data;

	if (widget && window12) {
		/* Note that this function is also called from
		   geo_photos_geocode_track_select_dialog(),
		   not just as a GTK+ callback!

		   In this case, all arguments except for user_data
		   are NULL and we have not been called as a result of
		   anything actually involving window12, and we should
		   avoid messing with it. In fact, we *must* avoid it:
		   the window12 object may not even exist, since it's
		   created only on demand.
		*/

		GtkWidget *vbox;

		gtk_widget_hide(window12);

		vbox = lookup_widget(window12, "vbox39");		
		gtk_container_foreach (GTK_CONTAINER (vbox),
				       (GtkCallback) gtk_widget_destroy,
				       NULL);
	}

	if(loaded_track)
	{
		g_slist_foreach (loaded_track, (GFunc) g_free, NULL);
		g_slist_free (loaded_track);
	}
	loaded_track = NULL;

	if (g_strrstr(file,".gpx") ||
	    g_strrstr(file,".GPX") ||
	    g_strrstr(file,".Gpx") )
	{
		loaded_track = load_gpx_file_into_list(file);
	}
	else
		loaded_track = load_log_file_into_list(file);

	if(loaded_track)
	{
		bbox = get_track_bbox (loaded_track);
		show_bbox (bbox);
	}

	paint_loaded_track();

	return FALSE;	
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
	char line[121];
	FILE *fd;

	fd = fopen(file, "r");

	if (!fd) {
		return list;
	}

	while(fgets(line,120, fd))
	{
		trackpoint_t *tp;
		char *latstr, *lonstr;
		char *parseptr;
		
		latstr = strtok_r (line, ",", &parseptr);
		lonstr = strtok_r (NULL, ",", &parseptr);
		
		
		if (latstr == NULL || lonstr == NULL) continue;


		tp = g_new0 (trackpoint_t, 1);
		tp->lat = deg2rad (atof (latstr));
		tp->lon = deg2rad (atof (lonstr));		

		list = g_slist_append(list, tp);
	}

	fclose (fd);

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
	} else {
		root_element = xmlDocGetRootElement(doc);
		list = parse_gpx_nodes(root_element);

		xmlFreeDoc(doc);
	}

	return list;
}

GSList *
load_gpx_string_into_list(char *gpx_string)
{
	GSList *list = NULL;
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	
	if(!gpx_string) return NULL;
	
	LIBXML_TEST_VERSION
	
	doc = xmlReadMemory(gpx_string, strlen(gpx_string), "noname.xml", NULL, 0);
	
	if (doc == NULL) {
		fprintf (stderr, _("Failed to parse document\n"));
	} else {
		root_element = xmlDocGetRootElement(doc);
		list = parse_gpx_nodes(root_element);

		xmlFreeDoc(doc);
	}

	return list;
}

GSList *
load_ols_XML_string_into_list(char *ols_string)
{
	GSList *list = NULL;
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;
	
	if(!ols_string) return NULL;
	
	LIBXML_TEST_VERSION
	
	doc = xmlReadMemory(ols_string, strlen(ols_string), "noname.xml", NULL, 0);
	
	if (doc == NULL) {
		fprintf (stderr, _("Failed to parse document\n"));
	} else {
		root_element = xmlDocGetRootElement(doc);
		list = parse_ols_XML_nodes(root_element);
		xmlFreeDoc(doc);
	}

	return list;
}

GSList *
load_kml_XML_string_into_list(char *kml_string)
{
	GSList *list = NULL;
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;

	if(!kml_string) return NULL;

	LIBXML_TEST_VERSION

	doc = xmlReadMemory(kml_string, strlen(kml_string), "noname.xml", NULL, 0);

	if (doc == NULL) {
		fprintf (stderr, _("Failed to parse document\n"));
	} else {
		root_element = xmlDocGetRootElement(doc);
		list = parse_kml_XML_nodes(root_element);
		xmlFreeDoc(doc);
	}

	return list;
}

GSList *
parse_gpx_nodes(xmlNode *node)
{
	xmlNode *cur_node = NULL;
	GSList *list = NULL;


	for (cur_node = node; cur_node; cur_node = cur_node->next)
	{
		if (cur_node->type == XML_ELEMENT_NODE)
		{
			if (xmlStrEqual(cur_node->name, BAD_CAST "trkpt") ||
			    xmlStrEqual(cur_node->name, BAD_CAST "rtept"))
			{
				double lat, lon;
				trackpoint_t *tp = g_new0(trackpoint_t,1);
				
				if (xmlHasProp(cur_node, BAD_CAST "junction") &&
				    strcmp(xmlGetProp(cur_node, BAD_CAST "junction"), "") == 0)
				{
					continue;
				}

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
		list = g_slist_concat(list, parse_gpx_nodes(cur_node->children));
	}
	
	return list;
}

GSList *
parse_ols_XML_nodes(xmlNode *node)
{
	xmlNode *cur_node = NULL;
	GSList *list = NULL;

	for (cur_node = node; cur_node; cur_node = cur_node->next)
	{
		if (xmlStrEqual(cur_node->name, BAD_CAST "RouteGeometry"))
		{
			xmlNode *geometry_node = cur_node->children;
			while (geometry_node != NULL)
			{
				if (xmlStrEqual(geometry_node->name, BAD_CAST "LineString"))
				{
					xmlNode *inner_cur_node = geometry_node->children;
					while (inner_cur_node != NULL)
					{
						if (xmlStrEqual(inner_cur_node->name, BAD_CAST "pos"))
						{
							double lat, lon;
							char** lonlat;

							trackpoint_t *tp = g_new0(trackpoint_t,1);
							fflush(stdout);
							lonlat = g_strsplit(xmlNodeGetContent(inner_cur_node), " ", 2);
							if (lonlat[0])
							{
								lon = atof(lonlat[0]);
								if (lonlat[1])
								{
									lat = atof(lonlat[1]);
									tp->lat = deg2rad(lat);
									tp->lon = deg2rad(lon);
									list = g_slist_append(list, tp);
								}
							}
							g_strfreev (lonlat);
						}
						inner_cur_node = inner_cur_node->next;
					}
				}
				geometry_node = geometry_node->next;
			}
		}
		list = g_slist_concat(list, parse_ols_XML_nodes(cur_node->children));
	}
	
	return list;
}

GSList *
parse_kml_XML_nodes(xmlNode *node)
{
	xmlNode *cur_node = NULL;
	GSList *list = NULL;

	for (cur_node = node; cur_node; cur_node = cur_node->next)
	{
		if (xmlStrEqual(cur_node->name, BAD_CAST "Placemark"))
		{
			xmlNode *geometry_node = cur_node->children;
			while (geometry_node != NULL)
			{
				if (xmlStrEqual(geometry_node->name, BAD_CAST "LineString"))
				{
					xmlNode *inner_cur_node = geometry_node->children;
					while (inner_cur_node != NULL)
					{
						if (xmlStrEqual(inner_cur_node->name, BAD_CAST "coordinates")) {
							char** lonlatlist;
							lonlatlist = g_strsplit(xmlNodeGetContent(inner_cur_node), "\n", -1);
							for(unsigned int i = 0; lonlatlist[i]; i++){
								g_strchug(lonlatlist[i]);
								g_strchomp(lonlatlist[i]);
								char** lonlat = g_strsplit(lonlatlist[i], ",", 2);
								if (lonlat[0])
								{
									double lat, lon;
									lon = atof(lonlat[0]);
									if (lonlat[1])
									{
										trackpoint_t *tp = g_new0(trackpoint_t,1);
										lat = atof(lonlat[1]);
										tp->lat = deg2rad(lat);
										tp->lon = deg2rad(lon);
										list = g_slist_append(list, tp);
									}
								}
								g_strfreev (lonlat);
							}
							g_strfreev (lonlatlist);
						}
						inner_cur_node = inner_cur_node->next;
					}
				}
				geometry_node = geometry_node->next;
			}
		}
		list = g_slist_concat(list, parse_kml_XML_nodes(cur_node->children));
	}

	return list;
}


void
fetch_track(GtkWidget *widget, char *service, char *start, char *end)
{
	if (strcmp (service, "yournavigation.org") == 0)
		fetch_yournavigation_track(widget, start, end);
	else if (strcmp (service, "openrouteservice.org") == 0)
		fetch_openrouteservice_track(widget, start, end);
	else
	{
		char *err_msg = g_strdup_printf (_("<span color='#aa0000'><b>"
		                                   "Unknown service selected"
		                                   "</b></span>\n"
		                                   "This is a bug in %s!"),
		                                 _(PACKAGE_NAME));
		GtkWidget *tmpWidget;

		tmpWidget = lookup_widget(dialog10, "label190");
		gtk_label_set_label(GTK_LABEL(tmpWidget), err_msg);

		tmpWidget = lookup_widget(dialog10, "okbutton11");
		gtk_widget_set_sensitive(tmpWidget, TRUE);
		
		g_warning("###unknown route service (%s) selected\n", service);
	}
}

void fetch_yournavigation_track(GtkWidget *widget, char *start, char *end)
{
	char *url;
	char *startlatstr;
	char *startlonstr;
	char *endlatstr;
	char *endlonstr;
	char *parseptr;
	startlatstr = strtok_r (start, ",", &parseptr);
	startlonstr = strtok_r (NULL, ",", &parseptr);
	endlatstr = strtok_r (end, ",", &parseptr);
	endlonstr = strtok_r (NULL, ",", &parseptr);
	dialog10 = widget;
	printf("%s(): %s, %s\n",__PRETTY_FUNCTION__, start, end);
	
	url = g_strdup_printf("http://www.yournavigation.org/api/dev/gosmore.php?format=gpx&flat=%s&flon=%s&tlat=%s&tlon=%s&v=motorcar&fast=1&layer=mapnik",startlatstr, startlonstr, endlatstr, endlonstr);
	if (!g_thread_create(&fetch_track_thread, (void *)url, FALSE, NULL) != 0)
		g_warning("### can't create route thread\n");
}

void fetch_openrouteservice_track(GtkWidget *widget, char *start, char *end)
{
	char *url;
	dialog10 = widget;
	printf("%s(): %s, %s\n",__PRETTY_FUNCTION__, start, end);
	char *startlatstr;
	char *startlonstr;
	char *endlatstr;
	char *endlonstr;
	char *parseptr;
	startlatstr = strtok_r (start, ",", &parseptr);
	startlonstr = strtok_r (NULL, ",", &parseptr);
	endlatstr = strtok_r (end, ",", &parseptr);
	endlonstr = strtok_r (NULL, ",", &parseptr);
	char *request;
	
	request = g_strdup_printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	                          "<xls:XLS xmlns:xls=\"http://www.opengis.net/xls\" xmlns:sch=\"http://www.ascc.net/xml/schematron\" "
	                          "xmlns:gml=\"http://www.opengis.net/gml\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
	                          "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
	                          "xsi:schemaLocation=\"http://www.opengis.net/xls "
	                          "http://schemas.opengis.net/ols/1.1.0/RouteService.xsd\" version=\"1.1\" xls:lang=\"en\">\n"
	                          "<xls:RequestHeader/>\n"
	                          "<xls:Request methodName=\"RouteRequest\" requestID=\"999\" version=\"1.1\">\n"
	                          "<xls:DetermineRouteRequest distanceUnit=\"KM\">\n"    
	                          "<xls:RoutePlan>\n"
	                          "<xls:RoutePreference>Fastest</xls:RoutePreference>"
	                          "<xls:WayPointList>\n"
	                          "<xls:StartPoint>\n"
	                          "<xls:Position>\n"
	                          "<gml:Point srsName=\"EPSG:4326\">\n"
	                          "<gml:pos>%s %s</gml:pos>\n"
	                          "</gml:Point>\n"
	                          "</xls:Position>\n"
	                          "</xls:StartPoint>\n"
	                          "<xls:EndPoint>\n"
	                          "<xls:Position>\n"
	                          "<gml:Point srsName=\"EPSG:4326\">\n"
	                          "<gml:pos>%s %s</gml:pos>\n"
	                          "</gml:Point>\n"
	                          "</xls:Position>\n"
	                          "</xls:EndPoint>\n"
	                          "</xls:WayPointList>\n"
	                          "</xls:RoutePlan>\n"
	                          "<xls:RouteInstructionsRequest provideGeometry=\"true\"/>\n"
	                          "<xls:RouteGeometryRequest/>\n"
	                          "</xls:DetermineRouteRequest>"
	                          "</xls:Request>\n"
	                          "</xls:XLS>\n",
	                          startlonstr,
	                          startlatstr,
	                          endlonstr,
	                          endlatstr
	);

	url = g_strdup_printf("http://openls.geog.uni-heidelberg.de/osm/eu/routing");

	char **urlAndRequest = g_malloc(2 * sizeof(char*));
	urlAndRequest[0] = url;
	urlAndRequest[1] = request;

	if (!g_thread_create(&fetch_openrouteservice_track_thread, (void *)urlAndRequest, FALSE, NULL) != 0)
		g_warning("### can't create route thread\n");
}

void process_fetched_track(postreply_t *reply, bool save_gpx)
{
	bbox_t bbox;
	
	if(loaded_track)
	{
		if (save_gpx)
		{
			FILE *fp = NULL;
			time_t time_epoch_sec;
			struct tm  *tm_struct;
			gchar buffer[256];
			gchar *filename = NULL;	
		
			time_epoch_sec = time(NULL);
			tm_struct = localtime(&time_epoch_sec);
			strftime(buffer, sizeof(buffer), "nav%Y%m%d_%H%M%S%z.gpx", tm_struct);
		
			filename = g_strconcat(global_track_dir, buffer,NULL);
	
			fp = fopen(filename,"w");
			if(!fp)
			{
				printf("oops: %s \n",strerror(errno));
				perror("navtrack open failed: ");
			}
			else
			{
				fprintf(fp,"%s", reply->data);
				fclose(fp);
			}
			
			g_free(filename);
		}
		
		gdk_threads_enter();
		{
			if(loaded_track)
			{
				bbox = get_track_bbox (loaded_track);
				show_bbox (bbox);
			}

			paint_loaded_track();
			gtk_widget_hide(dialog10);
		}
		gdk_threads_leave();
	}
	else
	{
		const char *err_msg;
		
		
		
		if(reply->status_code == 200)
			err_msg = g_strdup (_("<span color='#aa0000'><b>"
			                      "Oops! No Route found"
			                      "</b></span>\n"
			                      "Try with another Start/End"));
		
		
		else if(reply->status_code == 203)
			err_msg = g_strdup(reply->data);
		
		
		else if (reply->status_code)
			err_msg = g_strdup (_("<span color='#aa0000'><b>"
			                      "Duh! A Server Error"
			                      "</b></span>\n"
			                      "Maybe try later again..."));
		
		
		else
			err_msg = g_strdup (_("<span color='#aa0000'><b>"
			                      "Oh! A Network Error"
			                      "</b></span>\n"
			                      "Check the internet!"));
		
		gdk_threads_enter();
		{
			GtkWidget *widget;

			widget = lookup_widget(dialog10, "label190");
			gtk_label_set_label(GTK_LABEL(widget), err_msg);
			
			widget = lookup_widget(dialog10, "okbutton11");
			gtk_widget_set_sensitive(widget, TRUE);			
		}
		gdk_threads_leave();
	
	}
		
}

void *
fetch_openrouteservice_track_thread(void *ptr)
{
	postreply_t *reply = NULL;
	char *url;
	char *request;
	
	url = ((char**)ptr)[0];
	request = ((char**)ptr)[1];
	
	
	reply = mycurl__do_http_post_XML(url, request, NULL);

	printf("HTTP-POST: size: %d, statuscode %d \n", (int)reply->size, (int)reply->status_code);
	loaded_track = load_ols_XML_string_into_list(reply->data);
	process_fetched_track(reply, false);
	
	g_free(url);
	g_free(request);
	g_free((char**)ptr);
	return NULL;
}

void *
fetch_track_thread(void *ptr)
{
	postreply_t *reply = NULL;
	char *url;
	GtkWidget *range, *drawingarea;
	int track_zoom, width, height;
	bbox_t bbox;
	
	drawingarea = lookup_widget(window1, "drawingarea1");
	width  = drawingarea->allocation.width;
	height = drawingarea->allocation.height;
	
	url = ptr;
	
	reply = mycurl__do_http_get(url, NULL); 

	printf("HTTP-GET: size: %d, statuscode %d \n", (int)reply->size, (int)reply->status_code);

	loaded_track = load_gpx_string_into_list(reply->data);
	process_fetched_track(reply, true);
		
	return NULL;
}
