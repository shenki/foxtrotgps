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
