
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include "support.h"
#include "converter.h"
#include "callbacks.h"
#include "wp.h"
#include "globals.h"

static GdkPixbuf	*wp_icon = NULL;
static GdkPixbuf	*myposition_icon = NULL;
static GdkGC		*gc_map = NULL;



void
do_paint_myposition();



void
set_current_wp(double lat, double lon)
{
	global_wp_on = TRUE;
	global_wp.lat = lat;
	global_wp.lon = lon;
	
	
	repaint_all();
}



GdkPixbuf *
load_wp_icon ()
{
	GdkPixbuf *wp_icon = NULL;
	GError *error = NULL;

	wp_icon = gdk_pixbuf_new_from_file_at_size (
			PACKAGE_PIXMAPS_DIR "/foxtrotgps-wp.png", 36, 36,
			&error);
	if (error)
	{
		g_print ("%s%s(): loading pixbuf failure. %s\n", __FUNCTION__,__FILE__,
		         error->message);
		g_error_free (error);
	}

	return wp_icon;
}

void
paint_wp()
{
	if(global_wp_on) do_paint_wp();	
}

void
do_paint_wp()
{	
	int pixel_x, pixel_y, x,y;
	float lat, lon;
	GdkColor color;
	GdkGC *gc;
	
	gc = gdk_gc_new(pixmap);
	color.green = 60000;
	color.blue = 0;
	color.red = 10000;
	gdk_gc_set_rgb_fg_color(gc, &color);
	

	if(!wp_icon)
		wp_icon = load_wp_icon ();

	if (pixmap && !gc_map)	
		gc_map = gdk_gc_new(pixmap);

	lat = global_wp.lat;
	lon = global_wp.lon;
	
	
	
	
	pixel_x = lon2pixel(global_zoom, lon);
	pixel_y = lat2pixel(global_zoom, lat);
	
	x = pixel_x - global_x;
	y = pixel_y - global_y;
	
	
	
	if(!wp_icon)
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
			gc_map,
			wp_icon,
			0,0,
			x,y-36,
			36,36,
			GDK_RGB_DITHER_NONE, 0, 0);
		
		gtk_widget_queue_draw_area (
			map_drawable, 
			x, y-36,
			36,36);
	}
}




void
osd_wp()
{
	PangoContext		*context = NULL;
	PangoLayout		*layout  = NULL;
	PangoFontDescription	*desc    = NULL;
	
	GdkColor color;
	GdkGC *gc;
	
	gchar *buffer;
	static gchar distunit[3];
	
	
	static int width = 0, height = 0;

	float distance;
	double unit_conv = 1;

	if(gpsdata && mouse_dx == 0 && mouse_dy == 0) 
	{
		switch (global_speed_unit)
		{
			case 0:
				unit_conv = 1.0;
				g_sprintf(distunit, "%s", "km");
				break;
			case 1 :
				unit_conv = 1.0 / 1.609344;
				g_sprintf(distunit, "%s", "m");
				break;
			case 2 :
				unit_conv = 1.0 / 1.852;
				g_sprintf(distunit, "%s", "NM");
				break;		
		}
		

		distance = get_distance(deg2rad(gpsdata->fix.latitude), 
					deg2rad(gpsdata->fix.longitude), 
					global_wp.lat,global_wp.lon);
		buffer = g_strdup_printf("%.3f\n%.1f°", 
					distance*unit_conv, 
					
					rad2deg(gpsdata->fix.bearing));
		
		
		context = gtk_widget_get_pango_context (map_drawable);
		layout  = pango_layout_new (context);
		desc    = pango_font_description_new();
		
		pango_font_description_set_size (desc, 20 * PANGO_SCALE);
		pango_layout_set_font_description (layout, desc);
		pango_layout_set_text (layout, buffer, strlen(buffer));
	
	
		gc = gdk_gc_new (map_drawable->window);
	
		
		color.red = 0;
		color.green = 0;
		color.blue = 0;
		
		gdk_gc_set_rgb_fg_color (gc, &color);
	
	
		
		
		
		
		gdk_draw_drawable (
			map_drawable->window,
			map_drawable->style->fg_gc[GTK_WIDGET_STATE (map_drawable)],
			pixmap,
			global_drawingarea_width - width - 10, 
			global_drawingarea_height - height - 10,
			global_drawingarea_width - width - 10, 
			global_drawingarea_height - height - 10,
			width+10,height+10);


		
		pango_layout_get_pixel_size(layout, &width, &height);
		
		
		
			gdk_draw_layout(map_drawable->window,
					gc,
					global_drawingarea_width - width - 10, 
					global_drawingarea_height - height -10,
					layout);
		

	
	
		g_free(buffer);
		pango_font_description_free (desc);
		g_object_unref (layout);
		g_object_unref (gc);
	}
}





void
paint_myposition()
{
	if(global_myposition.lat) do_paint_myposition();	
}

void
do_paint_myposition()
{	
	int pixel_x, pixel_y, x,y;
	float lat, lon;
	GdkColor color;
	GdkGC *gc;
	GError	*error = NULL;
	
	gc = gdk_gc_new(pixmap);
	color.green = 60000;
	color.blue = 0;
	color.red = 10000;
	gdk_gc_set_rgb_fg_color(gc, &color);
	

	if(!myposition_icon)
	{
		myposition_icon = gdk_pixbuf_new_from_file_at_size (
			PACKAGE_PIXMAPS_DIR "/" PACKAGE "-myposition.png", 36,36,
			&error);
		if (error)
		{
			g_print ("%s(): loading pixbuf failure. %s\n", __FUNCTION__,
			error->message);
			g_error_free (error);
			
			
		}
	}
	if (pixmap && !gc_map)	
		gc_map = gdk_gc_new(pixmap);

	lat = deg2rad(global_myposition.lat);
	lon = deg2rad(global_myposition.lon);
	
	
	
	
	pixel_x = lon2pixel(global_zoom, lon);
	pixel_y = lat2pixel(global_zoom, lat);
	
	x = pixel_x - global_x;
	y = pixel_y - global_y;

	if(!myposition_icon)
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
			gc_map,
			myposition_icon,
			0,0,
			x,y-36,
			36,36,
			GDK_RGB_DITHER_NONE, 0, 0);
		
		gtk_widget_queue_draw_area (
			map_drawable, 
			x, y-36,
			36,36);
	}
}
