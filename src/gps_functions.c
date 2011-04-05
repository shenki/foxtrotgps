

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <glib.h>
#include <glib/gprintf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include <gps.h>

#include "gps_functions.h"
#include "globals.h"
#include "support.h"
#include "tile_management.h"
#include "map_management.h"
#include "converter.h"
#include "wp.h"
#include "tracks.h"

#define BUFSIZE 512
char * distance2scale(float distance, float *factor);
static void * get_gps_thread(void *ptr);


static GIOChannel *gpsd_io_channel =NULL;
static struct gps_data_t *libgps_gpsdata = NULL;

gboolean reconnect_gpsd = TRUE;

static guint sid1 = 0;
static guint sid3 = 0; 
static guint watchdog = 0;
static guint gps_timer = 0;

gboolean
cb_gps_timer()
{
	
	
	int pixel_x, pixel_y, x, y, last_x, last_y;
	static float lat, lon, lat_tmp=0, lon_tmp=0;
	float trip_delta=0;

	static double trip_time_accumulated = 0;
	static gboolean trip_counter_got_stopped = FALSE;

	GdkColor color;
	static GdkGC *gc=NULL, *gc_2=NULL, *gc_3=NULL, *gc_4=NULL, *gc_5=NULL;
	
	if(gc == NULL)
	{
		gc   = gdk_gc_new(pixmap);
		gc_2 = gdk_gc_new(pixmap);
		gc_3 = gdk_gc_new(pixmap);
		gc_4 = gdk_gc_new(pixmap);
		gc_5 = gdk_gc_new(pixmap);
		
		
		color.red = 60000;
		color.green = 0;
		color.blue = 0;
		gdk_gc_set_rgb_fg_color(gc, &color);
		gdk_gc_set_line_attributes(gc,
				5, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
		
		
		color.red = 5000;
		color.green = 5000;
		color.blue = 55000;
		gdk_gc_set_rgb_fg_color(gc_2, &color);
		gdk_gc_set_line_attributes(gc_2,
				6, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
	
		
		color.red = 25500; 
		color.green = 35000;
		color.blue = 65500;
		gdk_gc_set_rgb_fg_color(gc_3, &color);
		gdk_gc_set_line_attributes(gc_3,
				7, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
		
		
		color.red = 35500; 
		color.green = 5000;
		color.blue = 500;
		gdk_gc_set_rgb_fg_color(gc_4, &color);
		gdk_gc_set_line_attributes(gc_4,
				7, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
				
		
		color.red = 65500; 
		color.green = 65500;
		color.blue = 65500;
		gdk_gc_set_rgb_fg_color(gc_5, &color);
		gdk_gc_set_line_attributes(gc_5,
				11, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
				
	}
	
	
	if(!gpsdata  || reconnect_gpsd)
		get_gps();
	

	if(gpsdata)
	{
		trackpoint_t *tp = g_new0(trackpoint_t,1);
		
		lat = deg2rad(gpsdata->fix.latitude);
		lon = deg2rad(gpsdata->fix.longitude);		
		
		
		pixel_x = lon2pixel(global_zoom, lon);
		pixel_y = lat2pixel(global_zoom, lat);
		
		x = pixel_x - global_x;
		y = pixel_y - global_y;
		
		
		pixel_x = lon2pixel(global_zoom, lon_tmp);
		pixel_y = lat2pixel(global_zoom, lat_tmp);
		
		last_x = pixel_x - global_x;
		last_y = pixel_y - global_y;


		
		if(gpsdata->seen_vaild)
		{
			int hand_x, hand_y, hand_wp_x, hand_wp_y;
			double heading_rad, bearing;
			
			heading_rad = (gpsdata->fix.heading * (1.0 / 180.0)) * M_PI;

			if(gpsdata->fix.speed>0.3) 
			{
				hand_x =  25 * sinf(heading_rad);
				hand_y = -25 * cosf(heading_rad);
			}
			else
			{
				hand_x = 0;
				hand_y = 0;
			}


			
			gdk_draw_drawable (
				map_drawable->window,
				map_drawable->style->fg_gc[GTK_WIDGET_STATE (map_drawable)],
				pixmap,
				last_x-29, last_y-29,
				last_x-29 + mouse_dx, last_y-29 + mouse_dy,
				58,58);

		
			if (lat_tmp && lon_tmp)
				gdk_draw_line(pixmap, gc, last_x, last_y, x, y);
			
			
			gdk_window_process_all_updates();

			
			if(mouse_dx == 0 && mouse_dy == 0)
			{
				
				gdk_draw_arc (
					map_drawable->window,
					gc_2,
					FALSE,		
					x-15 + mouse_dx,
					y-15 + mouse_dy,
					30,30,		
					0, 360*64);	
				
				
				if(global_wp_on && gpsdata->valid)
				{
					
					bearing = get_bearing(lat, lon, global_wp.lat, global_wp.lon);
					gpsdata->fix.bearing = bearing;

					hand_wp_x =  25 * sinf(bearing);
					hand_wp_y = -25 * cosf(bearing);
					
					gdk_draw_line(map_drawable->window,
							gc_5,
							x + mouse_dx,
							y + mouse_dy,
							x + mouse_dx + hand_wp_x,
							y + mouse_dy + hand_wp_y);

					gdk_draw_line(map_drawable->window,
							gc_4,
							x + mouse_dx,
							y + mouse_dy,
							x + mouse_dx + hand_wp_x,
							y + mouse_dy + hand_wp_y);
					
					osd_wp();
					
				}
				
				
				gdk_draw_line(map_drawable->window,
						gc_5,
						x + mouse_dx,
						y + mouse_dy,
						x + mouse_dx + hand_x,
						y + mouse_dy + hand_y);
				
				gdk_draw_line(map_drawable->window,
						gc_3,
						x + mouse_dx,
						y + mouse_dy,
						x + mouse_dx + hand_x,
						y + mouse_dy + hand_y);
			}
		}
		
		
		if(global_autocenter)
		{
			if(    (x < (global_drawingarea_width /2 - global_drawingarea_width /8) ||
				x > (global_drawingarea_width /2 + global_drawingarea_width /8) ||
				y < (global_drawingarea_height /2 - global_drawingarea_height /8) ||
				y > (global_drawingarea_height /2 + global_drawingarea_height /8) ) &&
			
				
				isnan(gpsdata->fix.latitude) ==0 &&
				isnan(gpsdata->fix.longitude)==0 &&
				gpsdata->fix.latitude  !=0 &&
				gpsdata->fix.longitude !=0
				)
			{
				set_mapcenter(gpsdata->fix.latitude, gpsdata->fix.longitude, global_zoom);
			}
		}
		

		

		
		if( gpsdata->valid && lat_tmp!=0 && lon_tmp!=0)
		{
			trip_delta = 6371.0 *  acos(sin(lat) * sin(lat_tmp) + 
				     cos(lat) * cos(lat_tmp) * cos(lon_tmp-lon) );
			
			if(isnan(trip_delta))
			{
				
				trip_delta = 0;
			}
			
			if(trip_delta > TRIP_DELTA_MIN)
			{
					tp->time    = gpsdata->fix.time;
					tp->lat     = lat;
					tp->lon     = lon;
					tp->lat_deg = gpsdata->fix.latitude;
					tp->lon_deg = gpsdata->fix.longitude;
					tp->alt     = gpsdata->fix.altitude;
					tp->speed   = gpsdata->fix.speed;
					tp->head    = gpsdata->fix.heading;
					tp->hdop    = gpsdata->hdop;
					tp->heart   = 0;
					
					if (trip_delta > SEGMENT_DISTANCE)
						tp->hdop = 999;

					
					if (trackpoint_list->length > TRACKPOINT_LIST_MAX_LENGTH)
						g_free(g_queue_pop_head(trackpoint_list));
						
					g_queue_push_tail(trackpoint_list, tp);
			}
		}
			
		if(trip_counter_on)
		{
			trip_distance += trip_delta;

			
			if(gpsdata->valid && gpsdata->fix.speed > trip_maxspeed)
				trip_maxspeed = gpsdata->fix.speed;
			
			
			
			
			if(trip_time == 0) 
				trip_time_accumulated = 0;
			
			if(trip_counter_got_stopped)
			{
				printf("counter had been stopped \n");
				trip_counter_got_stopped = FALSE;
				trip_time_accumulated = trip_time;
				trip_starttime = 0;
			}
			
			
			if(trip_starttime == 0 && gpsdata->seen_vaild)
			{
				trip_starttime = gpsdata->fix.time;
			}
			
			
			if(trip_starttime > 0 && gpsdata->seen_vaild)
			{
				trip_time = gpsdata->fix.time - trip_starttime + trip_time_accumulated;				
			}
			
			if(trip_time < 0)
			{
				trip_time = 0;
				trip_starttime = 0;
				trip_distance = 0;
				trip_maxspeed = 0;
			}

		}

		else
		{
			printf("trip counter halted\n");
			trip_counter_got_stopped = TRUE;
			lat_tmp = lon_tmp = 0;
		}
		
		
		
		set_label();
		
		
		if(trip_logger_on && gpsdata->valid)
			track_log();
		
		if(gpsdata->valid)
		{	
			lat_tmp = lat;
			lon_tmp = lon;
		}
	}
	else 
	{
		set_label_nogps();
	}
	
	return TRUE; 
}

gboolean
reset_gpsd_io()
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	reconnect_gpsd = TRUE;

	return FALSE;	
}


void
osd_speed(gboolean force_redraw)
{
	
	PangoContext		*context = NULL;
	PangoLayout		*layout  = NULL;
	PangoFontDescription	*desc    = NULL;
	
	GdkColor color;
	GdkGC *gc;
	
	gchar *buffer;
	static int x = 10, y = 10;
	static int width = 0, height = 0;

	static double speed_tmp = 0;
	
	double unit_conv = 1;
		
	if(gpsdata && mouse_dx == 0 && mouse_dy == 0) 
	{
		switch (global_speed_unit)
		{
			case 0:
				unit_conv = 1.0;
				break;
			case 1 :
				unit_conv = 1.0/1.609344;
				break;
			case 2 :
				unit_conv = 1.0 / 1.852;
				break;		
		}
		

	
		buffer = g_strdup_printf("%.0f", gpsdata->fix.speed*3.6*unit_conv);
		
		
		context = gtk_widget_get_pango_context (map_drawable);
		layout  = pango_layout_new (context);
		desc    = pango_font_description_new();
		
		pango_font_description_set_absolute_size (desc, 80 * PANGO_SCALE);
		pango_layout_set_font_description (layout, desc);
		pango_layout_set_text (layout, buffer, strlen(buffer));
	
	
		gc = gdk_gc_new (map_drawable->window);
	
		color.red = (gpsdata->fix.speed*3.6*unit_conv > 50) ? 0xffff : 0;
		color.green = 0;
		color.blue = 0;
		
		gdk_gc_set_rgb_fg_color (gc, &color);

		
		
		if(speed_tmp != floor(gpsdata->fix.speed*3.6*unit_conv) || force_redraw)
		{
			
			gdk_draw_drawable (
				map_drawable->window,
				map_drawable->style->fg_gc[GTK_WIDGET_STATE (map_drawable)],
				pixmap,
				0,0,
				0, 0,
				width+10,height+10);
		
			
			if(gpsdata->fix.speed>0.01 && gpsdata->valid) 
				gdk_draw_layout(map_drawable->window,
						gc,
						x, y,
						layout);
			
			
			pango_layout_get_pixel_size(layout, &width, &height);
		}
		
		speed_tmp = floor(gpsdata->fix.speed*3.6*unit_conv);
		
		g_free(buffer);
		pango_font_description_free (desc);
		g_object_unref (layout);
		g_object_unref (gc);
	}
}
void
set_label_nogps()
{
	static GtkLabel *label=NULL;
	static gchar buffer[BUFSIZE];
	int num_dl_threads = 0;

	if(label == NULL)
		label   = GTK_LABEL(lookup_widget(window1, "label4"));
	
	num_dl_threads = update_thread_number(0);
	if(num_dl_threads && !global_tiles_in_dl_queue)
	{	
		g_snprintf(buffer, BUFSIZE,
			"<b>no GPSD found</b> - <span foreground='#0000ff'><b>D%d</b></span>",
			num_dl_threads);
	}
	else if (num_dl_threads && global_tiles_in_dl_queue)
		g_snprintf(buffer, BUFSIZE,
			"<b>no GPSD found</b> - <span foreground='#0000ff'><b>D%d</b></span> - <b>[%d]</b>",
			num_dl_threads, global_tiles_in_dl_queue);
	else
		g_snprintf(buffer, BUFSIZE, "<b>no GPSD found</b>");
	
	if(global_new_msg)
		g_snprintf(buffer, BUFSIZE, "<span foreground='#ff0000'><b>New Message arrived. Click here.</b></span>");
	
	gtk_label_set_label(label, buffer);

}
void
set_label()
{
	static GtkLabel *label=NULL,   *label31, *label38, *label39;
	static GtkLabel *label41, *label42, *label43, *label45;
	static GtkLabel *label66, *label68, *label70;
	static gchar buffer[BUFSIZE];
	static gchar numdl_buf[64], dl_buf[64], ff_buf[64], tr_buf[64];
	static gchar speedunit[5], distunit[3], altunit[3];
	int trip_hours, trip_minutes, trip_seconds;
	int num_dl_threads = 0;
	time_t time_sec;
	struct tm  *ts;
	double unit_conv = 1, unit_conv_alt = 1;
	
	osd_speed(FALSE);
	
	if(global_speed_unit==1)
	{
		unit_conv = 1.0/1.609344;
		g_sprintf(speedunit, "%s","mph");
		g_sprintf(distunit, "%s", "m");
	}
	else if(global_speed_unit==2)
	{
		unit_conv = 1.0/1.852;
		g_sprintf(speedunit, "%s","kn");
		g_sprintf(distunit, "%s", "NM");
	}
	else
	{
		g_sprintf(speedunit, "%s","km/h");
		g_sprintf(distunit, "%s", "km");
	}
	
	
	if(global_alt_unit==1)
	{
		unit_conv_alt = 1.0/0.3048;
		g_sprintf(altunit, "%s", "ft");
	}
	else
		g_sprintf(altunit, "%s", "m");
	
	if(global_auto_download)
		g_sprintf(dl_buf, "%s", "");
	else
		g_sprintf(dl_buf, "%s", "<span foreground='#ff0000'><b>!</b></span>");
	
	if (global_fftimer_running)
		g_sprintf(ff_buf, "%s", "<span foreground='#00e000'><b>f</b></span>");
	else
		g_sprintf(ff_buf, "%s", "");
	
	if (trip_logger_on)
		g_sprintf(tr_buf, "%s", "<span foreground='#00e000'><b>t</b></span>");
	else
		g_sprintf(tr_buf, "%s", "");
	
	if(label == NULL)
	{
		label   = GTK_LABEL(lookup_widget(window1, "label4"));
		label45 = GTK_LABEL(lookup_widget(window1, "label45"));
		label41 = GTK_LABEL(lookup_widget(window1, "label41"));
		label31 = GTK_LABEL(lookup_widget(window1, "label31"));
		label38 = GTK_LABEL(lookup_widget(window1, "label38"));
		label39 = GTK_LABEL(lookup_widget(window1, "label39"));
		label42 = GTK_LABEL(lookup_widget(window1, "label42"));
		label43 = GTK_LABEL(lookup_widget(window1, "label43"));
		label66 = GTK_LABEL(lookup_widget(window1, "label66"));
		label68 = GTK_LABEL(lookup_widget(window1, "label68"));
		label70 = GTK_LABEL(lookup_widget(window1, "label70"));
	}


	
	
	
	num_dl_threads = update_thread_number(0);
	
	if(num_dl_threads && !global_tiles_in_dl_queue)
		g_sprintf(numdl_buf, "<span foreground='#0000ff'><b>D%d</b></span> ", 
			  num_dl_threads);
	else if (num_dl_threads && global_tiles_in_dl_queue)
		g_sprintf(numdl_buf, "<span foreground='#0000ff'><b>D%d</b></span>-%d ", 
			  num_dl_threads, global_tiles_in_dl_queue);
	else
		g_sprintf(numdl_buf, "%s", "");
	

	g_snprintf(buffer, BUFSIZE,
		"%s%s%s%s<b>%4.1f</b>%s "
		"<small>trp </small><b>%.2f</b>%s "
		"<small>alt </small><b>%.0f</b>%s "
		"<small>hdg </small><b>%.0f</b>° "
		"<small></small>%d/%.1f",
		numdl_buf,
		dl_buf,
		tr_buf,
		ff_buf,
		gpsdata->fix.speed * 3.6 * unit_conv,	speedunit,
		trip_distance * unit_conv,		distunit,
		gpsdata->fix.altitude * unit_conv_alt,	altunit,
		gpsdata->fix.heading * unit_conv,
		gpsdata->satellites_used,
		gpsdata->hdop);

	if(global_new_msg)
		g_snprintf(buffer, BUFSIZE, "<span foreground='#ff0000'><b>New Message arrived. Click here.</b></span>");

	gtk_label_set_label(label, buffer);


	if(global_infopane_visible)
	{
		
		
		
		
		
		time_sec = (time_t)gpsdata->fix.time;
		ts = localtime(&time_sec);
		
		
		strftime(buffer, sizeof(buffer), "<big><b>%a %Y-%m-%d %H:%M:%S</b></big>", ts); 
		gtk_label_set_label(label41,buffer);
	
		
		switch (global_latlon_unit)
		{
			case 0:
				g_snprintf(buffer, BUFSIZE, "<big><b>%f - %f</b></big>", gpsdata->fix.latitude, gpsdata->fix.longitude);
				break;
			case 1:
				g_snprintf(buffer, BUFSIZE, "<big><b>%s   %s</b></big>", 
					  latdeg2latmin(gpsdata->fix.latitude),
					  londeg2lonmin(gpsdata->fix.longitude));
				break;
			case 2:
				g_snprintf(buffer, BUFSIZE, "<big><b>%s   %s</b></big>", 
					  latdeg2latsec(gpsdata->fix.latitude),
					  londeg2lonsec(gpsdata->fix.longitude));
		}
		gtk_label_set_label(label31,buffer);
		
		
		g_snprintf(buffer, BUFSIZE, 
			"<b><span foreground='#0000ff'><span font_desc='50'>%.1f</span></span></b> %s", 
			gpsdata->fix.speed*3.6*unit_conv, speedunit);
		gtk_label_set_label(label38,buffer);
	
		
		g_snprintf(buffer, BUFSIZE, "<big><b>%.1f %s</b></big>", gpsdata->fix.altitude * unit_conv_alt, altunit);
		gtk_label_set_label(label39,buffer);
		
		
		g_snprintf(buffer, BUFSIZE, "<big><b>%.1f°</b></big> ", gpsdata->fix.heading);
		gtk_label_set_label(label42,buffer);
		
		
		g_snprintf(buffer, BUFSIZE, "<big><b>%d</b>  <small>HDOP</small><b> %.1f</b></big>", 
				gpsdata->satellites_used, gpsdata->hdop);
		gtk_label_set_label(label43,buffer);
	
		
		
		
	
		
		g_snprintf(buffer, BUFSIZE, "<big><b>%.3f</b></big> <small>%s</small>", trip_distance*unit_conv,distunit);
		gtk_label_set_label(label45,buffer);
	
	
		
		trip_hours   = trip_time / 3600;
		trip_minutes = ((int)trip_time%3600)/60;
		trip_seconds = (int)trip_time % 60;
		
		if (trip_seconds < 10 && trip_minutes < 10)
		{
			g_sprintf(buffer, "<big><b>%d:0%d:0%d</b></big>",trip_hours,trip_minutes,trip_seconds);
		}
		else if (trip_seconds < 10)
			g_sprintf(buffer, "<big><b>%d:%d:0%d</b></big>",trip_hours,trip_minutes,trip_seconds);
		else if (trip_minutes < 10)
			g_sprintf(buffer, "<big><b>%d:0%d:%d</b></big>",trip_hours,trip_minutes,trip_seconds);
		else
			g_sprintf(buffer, "<big><b>%d:%d:%d</b></big>",trip_hours,trip_minutes,trip_seconds);
	
		gtk_label_set_label(label66,buffer);
	
		
		g_sprintf(buffer, "<big><b>%.1f</b></big><small> %s</small>", trip_distance*3600*unit_conv/(trip_time+2.0), speedunit);
		gtk_label_set_label(label68,buffer);
	
		
		g_sprintf(buffer, "<big><b>%.1f</b></big><small> %s</small>", trip_maxspeed*3.6*unit_conv, speedunit);
		gtk_label_set_label(label70,buffer);
	}
}





static gboolean
cb_gpsd_io_error(GIOChannel *src, GIOCondition condition, gpointer data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	reset_gpsd_io();

	return FALSE; 
}



static gboolean
cb_gpsd_data(GIOChannel *src, GIOCondition condition, gpointer data)
{
	int ret;

        if (libgps_gpsdata == NULL)
            return FALSE;

	ret = gps_poll(libgps_gpsdata);
	if (ret == 0)
	{
		gpsdata->satellites_used = libgps_gpsdata->satellites_used;
		gpsdata->hdop = libgps_gpsdata->dop.hdop;
		gpsdata->fix.time = libgps_gpsdata->fix.time;
		if (isnan(gpsdata->fix.time))
		{
			gpsdata->fix.time = (time_t) 0;
		}
		gpsdata->valid = (libgps_gpsdata->status != STATUS_NO_FIX);
		if (gpsdata->valid)
		{
			gpsdata->seen_vaild = TRUE;
			gpsdata->fix.latitude = libgps_gpsdata->fix.latitude;
			gpsdata->fix.longitude = libgps_gpsdata->fix.longitude;
			gpsdata->fix.speed = libgps_gpsdata->fix.speed;
			gpsdata->fix.heading = libgps_gpsdata->fix.track;
			gpsdata->fix.altitude = libgps_gpsdata->fix.altitude;
		}
		
		g_source_remove(watchdog);
		watchdog = g_timeout_add_seconds_full(G_PRIORITY_DEFAULT_IDLE,60,reset_gpsd_io,NULL,NULL);
	}
	else
	{
		fprintf(stderr, "connection to gpsd LOST\n");
		return cb_gpsd_io_error(src, condition, data);
	}
	return TRUE;
}


void 
get_gps()
{
	/* Set this flag to FALSE *immediately* so that a slow gps_open()
	   doesn't cause successive cb_gps_timer() callbacks to call
	   us *again* before we've even finished *this* invocation--
	   which would create multiple, simultaneous get_gps_thread()
	   threads and all sorts of associated problems:
	*/
	reconnect_gpsd = FALSE;

	if (gps_timer) {
		/* Disable the regularly scheduled callback to cb_gps_timer()
		   until after get_gps_thread() has returned, to guard against
		   the situation described above when reconnect_gpsd
		   is re-set by something else (e.g.: the user bouncing
		   on the `Change GPSD' button):
		*/
		g_source_remove (gps_timer);
		gps_timer = 0;
	}

	if (watchdog) {
		g_source_remove(watchdog);
	}

	if (sid1) {
		g_source_remove(sid1);
		sid1 = 0;
	}

	if (sid3) {
		g_source_remove(sid3);
		sid3 = 0;
	}

	if (gpsd_io_channel) {
		g_io_channel_unref (gpsd_io_channel);
		gpsd_io_channel = NULL;
	}

	/* Note that we're *not* free'ing the internal gpsdata structure,
	   ever. We'd only immediately reallocate it, so it's not a net win
	   in terms of memory-footprint; and it doesn't contain references
	   to any file-descriptors or other ephemeral resources, so
	   the only thing we'd be doing by re-initialising it would be
	   throwing away our last known fix, etc.
	*/

	if (libgps_gpsdata) {
		gps_close(libgps_gpsdata);
		libgps_gpsdata = NULL;
	}

	g_thread_create(&get_gps_thread, NULL, FALSE, NULL);
}

static void *
get_gps_thread(void *ptr)
{
	libgps_gpsdata = gps_open(global_server, global_port);
	if (libgps_gpsdata)
	{
		fprintf(stderr, "connection to gpsd SUCCEEDED \n");

		/* Unless someone has re-set reconnect_gpsd
		   between when get_gps() set it and now,
		   then it should still be FALSE; if someone else
		   *did* re-set it, then they did it for a reason.

		   Either way, we're better off leaving it alone,
		   here.
		*/

		if(!gpsdata)
		{
			gpsdata = g_new0(tangogps_gps_data_t,1);
		}
		
	
		gps_stream(libgps_gpsdata, WATCH_ENABLE | POLL_NONBLOCK, NULL);
		
		watchdog = g_timeout_add_seconds_full(G_PRIORITY_DEFAULT_IDLE,60,reset_gpsd_io,NULL,NULL);
		
		
		gpsd_io_channel = g_io_channel_unix_new(libgps_gpsdata->gps_fd);
		g_io_channel_set_flags(gpsd_io_channel, G_IO_FLAG_NONBLOCK, NULL);
		
		
		sid1 = g_io_add_watch_full(gpsd_io_channel, G_PRIORITY_HIGH_IDLE+200, G_IO_ERR | G_IO_HUP, cb_gpsd_io_error, NULL, NULL);
		
		
		sid3 = g_io_add_watch_full(gpsd_io_channel, G_PRIORITY_HIGH_IDLE+200, G_IO_IN | G_IO_PRI, cb_gpsd_data, NULL, NULL);
	
	} else {
		/* Failure. Maybe it's transient--try again
		   on the next cycle: */
		reconnect_gpsd = TRUE;
	}

	gps_timer = g_timeout_add (1000, cb_gps_timer, NULL);

	return NULL;
}

void
map_scale_indicator()
{
	int y, width, height, max_bar_length=250;
	float distance, factor, lat, lon1, lon2;
	char *buffer=NULL;
	GdkColor color;
	static GdkGC *gc=NULL, *gc1=NULL;
	
	PangoContext		*context = NULL;
	PangoLayout		*layout  = NULL;
	PangoFontDescription	*desc    = NULL;
	
	y = map_drawable->allocation.height - 8;
	
	if(gc == NULL)
	{
		gc   = gdk_gc_new(pixmap);
		gc1  = gdk_gc_new(pixmap);
	}
	color.red   = 0;
	color.green = 0;
	color.blue  = 0;
	
	gdk_gc_set_rgb_fg_color(gc, &color);
        gdk_gc_set_line_attributes(gc,
                        5, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_ROUND);

	color.red   = 65000;
	color.green = 65000;
	color.blue  = 65000;
	
	gdk_gc_set_rgb_fg_color(gc1, &color);
        gdk_gc_set_line_attributes(gc1,
                        3, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_ROUND);
	


	lat   = pixel2lat(global_zoom, global_y+y);
	lon1  = pixel2lon(global_zoom, 0);
	lon2  = pixel2lon(global_zoom, max_bar_length);

	distance = get_distance(lat, lon1, lat, lon2);
	
	buffer = distance2scale(distance, &factor);
	max_bar_length *= factor;
	
	gdk_draw_line(map_drawable->window, gc, 4, y, max_bar_length+6, y);
	gdk_draw_line(map_drawable->window, gc1,5, y, max_bar_length+5, y);	

	
	context = gtk_widget_get_pango_context (map_drawable);
	layout  = pango_layout_new (context);
	desc    = pango_font_description_new();
	
	pango_font_description_set_absolute_size (desc, 12 * PANGO_SCALE);
	pango_layout_set_font_description (layout, desc);
	pango_layout_set_text (layout, buffer, strlen(buffer));


	
	pango_layout_get_pixel_size(layout, &width, &height);

	
	
	gdk_gc_set_line_attributes(gc,
                        height+2, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_ROUND);	

        gdk_gc_set_line_attributes(gc1,
                        height, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_ROUND);	

	gdk_draw_line(map_drawable->window, gc1, 22, y-height/2+6, 20+width+6, y-height/2+6);

     

		gdk_draw_layout(map_drawable->window,
				gc,
				25, y-height+7,
				layout);
	


	g_free(buffer);
	pango_font_description_free (desc);
	g_object_unref (layout);
	
	
	
}

char *
distance2scale(float distance, float *factor)
{
	float unit_conv=1;
	char *buf = NULL;
	char unit[5];
	
	switch (global_speed_unit)
	{
		case METRICAL:
			unit_conv = 1.0;
			strncpy(unit, "km", 3);
			break;
		case IMPERIAL :
			unit_conv = 1.0/1.609344;
			strncpy(unit, "m", 2);
			break;
		case NAUTICAL :
			unit_conv = 1.0 / 1.852;
			strncpy(unit, "NM", 3);
			break;		
	}
	
	distance *= unit_conv;
	if (distance >= 5000) {
		buf = g_strconcat("5000", unit, NULL);
		*factor = 5000/distance;
	}
	else if (distance < 5000 && distance >= 2000) {
		buf = g_strconcat("2000", unit, NULL);
		*factor = 2000/distance;
	}
	else if (distance < 2000 && distance >= 1000) {
		buf = g_strconcat("1000", unit, NULL);
		*factor = 1000/distance;
	}
	else if (distance < 1000 && distance >= 500) {
		buf = g_strconcat("500", unit, NULL);
		*factor = 500/distance;
	}
	else if (distance < 500 && distance >= 200) {
		buf = g_strconcat("200", unit, NULL);
		*factor = 200/distance;
	}
	else if (distance < 200 && distance >= 100) {
		buf = g_strconcat("100", unit, NULL);
		*factor = 100/distance;
	}
	else if (distance < 100 && distance >= 50) {
		buf = g_strconcat("50", unit, NULL);
		*factor = 50/distance;
	}
	else if (distance < 50 && distance >= 20) {
		buf = g_strconcat("20", unit, NULL);
		*factor = 20/distance;
	}
	else if (distance < 20 && distance >= 10) {
		buf = g_strconcat("10", unit, NULL);
		*factor = 10/distance;
	}
	else if (distance < 10 && distance >= 5) {
		buf = g_strconcat("5", unit, NULL);
		*factor = 5/distance;
	}
	else if (distance < 5 && distance >= 2) {
		buf = g_strconcat("2", unit, NULL);
		*factor = 2/distance;
	}
	else if (distance < 2 && distance >= 1) {
		buf = g_strconcat("1", unit, NULL);
		*factor = 1/distance;
	}
	else if(global_speed_unit == METRICAL)
	{
		if (distance < 1 && distance >= 0.5) {
			buf = g_strdup("500m");
			*factor = 0.5/distance;
		}
		else if (distance < 0.5 && distance >= 0.2) {
			buf = g_strdup("200m");
			*factor = 0.2/distance;
		}
		else if (distance < 0.2 && distance >= 0.1) {
			buf = g_strdup("100m");
			*factor = 0.1/distance;
		}
		else if (distance < 0.1 && distance >= 0.05) {
			buf = g_strdup("50m");
			*factor = 0.05/distance;
		}
		else if (distance < 0.05 && distance >= 0.02) {
			buf = g_strdup("20m");
			*factor = 0.02/distance;
		}
		else {
			buf = g_strdup("10m");
			*factor = 0.01/distance;
		}
	}
	else if(global_speed_unit == IMPERIAL)
	{
		distance *= 5280;
		if (distance >= 5000) {
			buf = g_strdup("5000ft");
			*factor = 5000/distance;
		}
		else if (distance < 5000 && distance >= 2000) {
			buf = g_strdup("2000ft");
			*factor = 2000/distance;
		}
		else if (distance < 2000 && distance >= 1000) {
			buf = g_strdup("1000ft");
			*factor = 1000/distance;
		}
		else if (distance < 1000 && distance >= 500) {
			buf = g_strdup("500ft");
			*factor = 500/distance;
		}
		else if (distance < 500 && distance >= 200) {
			buf = g_strdup("200ft");
			*factor = 200/distance;
		}
		else {
			buf = g_strdup("100ft");
			*factor = 100/distance;
		}
	}
	else if(global_speed_unit == NAUTICAL)
	{
		if (distance < 1 && distance >= 0.5) {
			buf = g_strdup("0.5NM");
			*factor = 0.5/distance;
		}
		else if (distance < 0.5 && distance >= 0.2) {
			buf = g_strdup("0.2NM");
			*factor = 0.2/distance;
		}
		else if (distance < 0.2 && distance >= 0.1) {
			buf = g_strdup("0.1NM");
			*factor = 0.1/distance;
		}
		else if (distance < 0.1 && distance >= 0.05) {
			buf = g_strdup("0.05NM");
			*factor = 0.05/distance;
		}
		else if (distance < 0.05 && distance >= 0.02) {
			buf = g_strdup("0.02NM");
			*factor = 0.02/distance;
		}
		else {
			buf = g_strdup("0.01NM");
			*factor = 0.01/distance;
		}
	}

	if(!buf)
		buf=g_strdup("bingo");

	return buf;
}
