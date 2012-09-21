#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#include "globals.h"
#include "tile_management.h"
#include "route.h"
#include "wp.h"
#include "interface.h"
#include "support.h"
#include "converter.h"
#include "map_management.h"
#include "util.h"
#include "tracks.h"

#define GPX_ENCODING "utf-8"

/**
 * This is a GSList containing the waypoints of the route
 * which we are planing. It is the central data structure for route.c
 */
static GSList *route = NULL;

static GdkPixbuf	*wp_icon = NULL;
static int              wp_icon_width = 0;
static int              wp_icon_height = 0;

/**
 * Clear the route.
 */
void
reset_route ()
{
	route = NULL;
}

/**
 * Append a new waypoint at the end of the route.
 */
void
append_waypoint_to_route (double lat, double lon)
{
	waypoint_t *tp = g_new0 (waypoint_t,1);

	tp->lat = lat;
	tp->lon = lon;

	route = g_slist_append (route, tp);
}

/**
 * Change the position of the given waypoint to the new position.
 */
void
change_waypoint_of_route (waypoint_t *tp, double lat, double lon)
{
	tp->lat = lat;
	tp->lon = lon;
}

/**
 * Delete the given waypoint from the route.
 */
void
delete_waypoint_of_route (waypoint_t *wp)
{
	route = g_slist_remove (route, wp);
	g_free (wp);
}

/**
 * Insert a new waypoint before the given waypoint. This waypoint lies
 * between the given waypoint and the waypoint before this waypoint.
 */
void
insert_waypoint_before_of_route (waypoint_t *wp)
{
	waypoint_t *previous_wp;
	int position;

	position = g_slist_index (route, wp);
	if (position > 0) {
		previous_wp = g_slist_nth_data (route, position - 1);

		waypoint_t *new_wp = g_new0 (waypoint_t,1);

		new_wp->lat = previous_wp->lat - (previous_wp->lat - wp->lat) / 2;
		new_wp->lon = previous_wp->lon - (previous_wp->lon - wp->lon) / 2;

		route = g_slist_insert (route, new_wp, position + 0);
	}
}

/**
 * Find the waypoint which wp_icon is at the given mouse position.
 * Return that waypoint or NULL if none was found.
 */
waypoint_t *
find_routepoint (int mouse_x, int mouse_y)
{
	GSList *list;
	double lat;
	double lon;
	int pixel_x, pixel_y, x,y;

	for (list = route; list != NULL; list = list->next)
	{
		waypoint_t *tp = list->data;

		lat = tp->lat;
		lon = tp->lon;

		pixel_x = lon2pixel (global_zoom, lon);
		pixel_y = lat2pixel (global_zoom, lat);

		x = pixel_x - global_x + wp_icon_width / 2;
		y = pixel_y - global_y - wp_icon_height / 2;

		if (abs (x - mouse_x) < wp_icon_width / 2 &&
		    abs (y - mouse_y) < wp_icon_height / 2)
		{
			return tp;
		}
	}

	return NULL;
}

static
void
draw_arrow (GdkGC *gc, int start_x, int start_y, int end_x, int end_y)
{
	int x1,y1,x2,y2;
	double angle = atan2 (end_y - start_y, end_x - start_x) + M_PI;
	double arrow_length = 20;
	double arrow_degrees = M_PI / 10;

	/* http://kapo-cpp.blogspot.com/2008/10/drawing-arrows-with-cairo.html */

	x1 = end_x + arrow_length * cos (angle - arrow_degrees);
	y1 = end_y + arrow_length * sin (angle - arrow_degrees);
	x2 = end_x + arrow_length * cos (angle + arrow_degrees);
	y2 = end_y + arrow_length * sin (angle + arrow_degrees);

	gdk_draw_line (pixmap, gc, start_x, start_y, end_x, end_y);
	gdk_draw_line (pixmap, gc, end_x, end_y, x1, y1);
	gdk_draw_line (pixmap, gc, x1, y1, x2, y2);
	gdk_draw_line (pixmap, gc, x2, y2, end_x, end_y);
}

static
void
draw_line_of_route (GdkGC *gc, int x1, int y1, int x2, int y2)
{
	if (abs (x1-x2) > 30 || abs (y1-y2) > 30) {
		/* Line is long enough. Draw arrow */
		draw_arrow (gc, x1, y1, x2, y2);
	} else {
		/* short line. Omit arrow. */
		gdk_draw_line (pixmap, gc, x1, y1, x2, y2);
	}
}

/**
 * This function draws the current route on the screen.
 */
void
paint_route ()
{
	GSList *list;
	int pixel_x, pixel_y, x,y, last_x = 0, last_y = 0;
	float lat, lon;
	GdkColor color;
	GdkGC *gc;
	gboolean is_line = FALSE;

	/* Load icon if not already loaded: */
	if (!wp_icon) {
		wp_icon        = load_wp_icon ();
		wp_icon_width  = gdk_pixbuf_get_width (wp_icon);
		wp_icon_height = gdk_pixbuf_get_height (wp_icon);
	}

	/* Create GC for drawing the route line */
	gc = gdk_gc_new (pixmap);
	color.green = 0;
	color.blue = 0;
	color.red = 50000;
	gdk_gc_set_rgb_fg_color (gc, &color);
	gdk_gc_set_line_attributes (gc, 5, GDK_LINE_SOLID,
	                            GDK_CAP_ROUND, GDK_JOIN_ROUND);

	/* [1] paint line first */
	for (list = route; list != NULL; list = list->next)
	{
		waypoint_t *tp = list->data;

		lat = tp->lat;
		lon = tp->lon;

		pixel_x = lon2pixel (global_zoom, lon);
		pixel_y = lat2pixel (global_zoom, lat);

		x = pixel_x - global_x;
		y = pixel_y - global_y;

		if (is_line)
		{
			draw_line_of_route (gc, last_x, last_y, x, y);
			gtk_widget_queue_draw_area (map_drawable,
			                            x-4, y-4, 8, 8);
		}

		last_x = x;
		last_y = y;

		is_line = TRUE;
	}

	/* [2] paint flags after line */
	for (list = route; list != NULL; list = list->next)
	{
		waypoint_t *tp = list->data;

		lat = tp->lat;
		lon = tp->lon;

		pixel_x = lon2pixel (global_zoom, lon);
		pixel_y = lat2pixel (global_zoom, lat);

		x = pixel_x - global_x;
		y = pixel_y - global_y;

		if (!wp_icon) {
			gdk_draw_arc (pixmap,
			              gc,
			              TRUE,
			              x-4, y-4,
			              8,8,
			              0,23040);
		} else {
			gdk_draw_pixbuf (pixmap,
			                 NULL,
			                 wp_icon,
			                 0,0,
			                 x,y-wp_icon_height,
			                 wp_icon_width,wp_icon_height,
			                 GDK_RGB_DITHER_NONE, 0, 0);

			gtk_widget_queue_draw_area (map_drawable,
			                            x, y-wp_icon_height,
			                            wp_icon_width,
			                            wp_icon_height);
		}
	}
}

/** 
 * Find the bounding box of the given GSList containin waypoints.
 */
bbox_t
get_way_bbox (GSList *ways)
{
	GSList *list;
	bbox_t bbox;
	double lat, lon;

	bbox.lat1 =  -90;
	bbox.lon1 =  180;
	bbox.lat2 =   90;
	bbox.lon2 = -180;

	for (list = ways; list != NULL; list = list->next)
	{
		waypoint_t *tp = list->data;

		lat = tp->lat;
		lon = tp->lon;
		bbox.lat1 = (lat > bbox.lat1) ? lat : bbox.lat1;
		bbox.lat2 = (lat < bbox.lat2) ? lat : bbox.lat2;
		bbox.lon1 = (lon < bbox.lon1) ? lon : bbox.lon1;
		bbox.lon2 = (lon > bbox.lon2) ? lon : bbox.lon2;
	}

	return bbox;
}

/**
 * Write a single route point to the XML file in GPX format.
 */
static
void
write_rtept (xmlTextWriterPtr writer, waypoint_t *wp, int no)
{
	xmlTextWriterStartElement (writer, BAD_CAST "rtept");
	xmlTextWriterWriteFormatAttribute (writer, BAD_CAST "lat",
	                                   "%f", rad2deg (wp->lat));
	xmlTextWriterWriteFormatAttribute (writer, BAD_CAST "lon",
	                                   "%f", rad2deg (wp->lon));
	xmlTextWriterEndElement (writer); /* </rtept> */
}

/**
 * Save the route in GPX format to the given URI.
 */
void
save_route_as_gpx (const char *uri) 
{
	int rc;
	xmlTextWriterPtr writer;
	int no;
	GSList *list;
	char now_as_string[200];
	struct tm now_as_tm;
	time_t now;

	if (uri == NULL) return;

	bbox_t bbox = get_way_bbox (route);

	/*
	 * this initialize the library and check potential ABI mismatches
	 * between the version it was compiled for and the actual shared
	 * library used.
	 */
	LIBXML_TEST_VERSION

	/* Create a new XmlWriter for uri, with no compression. */
	writer = xmlNewTextWriterFilename (uri, 0);
	if (writer == NULL) {
		printf ("testXmlwriterFilename: Error creating the xml writer\n");
		return;
	}

	/* We would like to indent the elements for better readability. */
	xmlTextWriterSetIndent (writer, 1);

	/* Start the document with the xml default for the version,
	 * encoding and the default for the standalone
	 * declaration. */
	rc = xmlTextWriterStartDocument (writer, "1.0", GPX_ENCODING, "no");
	if (rc < 0) {
		printf ("testXmlwriterFilename: Error at xmlTextWriterStartDocument\n");
		return;
	}

	xmlTextWriterStartElement (writer, BAD_CAST "gpx");
	xmlTextWriterWriteAttribute (writer, BAD_CAST "version",
	                                     BAD_CAST "1.1");
	xmlTextWriterWriteAttribute (writer, BAD_CAST "creator",
	                                     BAD_CAST PACKAGE_STRING);
	xmlTextWriterWriteAttribute (writer, BAD_CAST "xmlns:xsi",
	                                     BAD_CAST "http://www.w3.org/2001/XMLSchema-instance");
	xmlTextWriterWriteAttribute (writer, BAD_CAST "xmlns:topografix",
	                                     BAD_CAST "http://www.topografix.com/GPX/Private/TopoGrafix/0/1");
	xmlTextWriterWriteAttribute (writer, BAD_CAST "xmlns",
	                                     BAD_CAST "http://www.topografix.com/GPX/1/1");
	xmlTextWriterWriteAttribute (writer, BAD_CAST "xsi:schemaLocation",
	                                     BAD_CAST "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");

	xmlTextWriterStartElement (writer, BAD_CAST "metadata");

	/* save current time into GPX file: */
	time (&now);
	localtime_r (&now, &now_as_tm);
	strftime (now_as_string, sizeof (now_as_string), "%Y-%m-%dT%H:%M:%S%Z",
	          &now_as_tm);
	xmlTextWriterWriteElement (writer, BAD_CAST "time",
	                                   BAD_CAST now_as_string);

	xmlTextWriterStartElement (writer, BAD_CAST "bounds");
	xmlTextWriterWriteFormatAttribute (writer, BAD_CAST "minlat",
	                                   "%f", rad2deg (bbox.lat2));
	xmlTextWriterWriteFormatAttribute (writer, BAD_CAST "minlon",
	                                   "%f", rad2deg (bbox.lon1));
	xmlTextWriterWriteFormatAttribute (writer, BAD_CAST "maxlat",
	                                   "%f", rad2deg (bbox.lat1));
	xmlTextWriterWriteFormatAttribute (writer, BAD_CAST "maxlon",
	                                   "%f", rad2deg (bbox.lon2));
	xmlTextWriterEndElement (writer); /* </bounds> */

	xmlTextWriterEndElement (writer); /* </metadata> */

	xmlTextWriterStartElement (writer, BAD_CAST "rte");

	for (list = route, no = 1; list != NULL; list = list->next, no++)
	{
		waypoint_t *wp = list->data;
		write_rtept (writer, wp, no);
	}

	xmlTextWriterEndElement (writer); /* </rte> */
	xmlTextWriterEndElement (writer); /* </gpx> */

	xmlTextWriterEndDocument (writer);

	xmlFreeTextWriter (writer);
}

/**
 * Save a route to a TomTom ITN file format.
 */
void
save_route_as_tomtom_itn (const char *uri)
{
	FILE *tomtom;
	int no;
	GSList *list;

	if (uri == NULL) return;

	tomtom = fopen (uri, "w");
	if (tomtom == NULL) {
		perror ("opening file to save tomtom.");
	} else {
		for (list = route, no = 1;
		     list != NULL;
		     list = list->next, no++)
		{
			waypoint_t *wp = list->data;
			fprintf (tomtom, "%d|%d|WP%d|0\n", 
			         (int) (rad2deg (wp->lon) * 100000),
			         (int) (rad2deg (wp->lat) * 100000),
			         no);
		}

		fclose (tomtom);
	}
}

/**
 * Take all routepoints from a DOM tree containing GPX nodes.
 */
static
GSList *
parse_gpx_routepoints (xmlNode *node)
{
	xmlNode *cur_node = NULL;
	GSList *list = NULL;

	for (cur_node = node; cur_node; cur_node = cur_node->next)
	{
		if (cur_node->type == XML_ELEMENT_NODE)			
		{
			if (xmlStrEqual (cur_node->name, BAD_CAST "rtept"))
			{
				double lat, lon;
				waypoint_t *tp = g_new0 (waypoint_t, 1);

				lat = atof ((char *) xmlGetProp (cur_node,
				                                 BAD_CAST "lat"));
				lon = atof ((char *) xmlGetProp (cur_node,
				                                 BAD_CAST "lon"));

				tp->lat = deg2rad (lat);
				tp->lon = deg2rad (lon);

				list = g_slist_append (list, tp);
			}
			else
			{
				printf ("  OTHER XML ELEMENT: %s \n",
				        cur_node->name);
			}
		}
		list = g_slist_concat (list,
		                       parse_gpx_routepoints (cur_node->children));
	}

	return list;
}

/**
 * Load a route from a given GPX file.
 */
GSList *
load_route_as_gpx (const char *file) 
{
  	GSList *list = NULL;
	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;

	LIBXML_TEST_VERSION

	doc = xmlReadFile (file, NULL, 0);
	if (doc == NULL)
	{
		printf ("error: could not parse file %s\n", file);
	}

	root_element = xmlDocGetRootElement (doc);
	list = parse_gpx_routepoints (root_element);
	xmlFreeDoc (doc);
	xmlCleanupParser ();

	return list;
}

/**
 * Load a route from a file with a supported file format.
 */
void
load_route (const char *filename)
{
	bbox_t bbox;

	if (filename == NULL) return;

	route = load_route_as_gpx (filename);
	if (route != NULL)
	{
		bbox = get_way_bbox (route);
		show_bbox (bbox);
	}
}


char *
choose_save_file (char *currentName)
{
	char *filename = NULL;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Save File",
	                                      NULL,
	                                      GTK_FILE_CHOOSER_ACTION_SAVE,
	                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
	                                      NULL);
	gtk_file_chooser_set_do_overwrite_confirmation
		(GTK_FILE_CHOOSER (dialog), TRUE);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog),
	                                   currentName);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename
			(GTK_FILE_CHOOSER (dialog));
	}

	gtk_widget_destroy (dialog);

	return filename;
}

char *
choose_load_file ()
{
	char *filename = NULL;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Open File", NULL,
	                                      GTK_FILE_CHOOSER_ACTION_OPEN,
	                                      GTK_STOCK_CANCEL,
	                                      GTK_RESPONSE_CANCEL,
	                                      GTK_STOCK_OPEN,
	                                      GTK_RESPONSE_ACCEPT,
	                                      NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename
			(GTK_FILE_CHOOSER (dialog));
	}
	gtk_widget_destroy (dialog);

	return filename;
}
