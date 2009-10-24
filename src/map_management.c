

#include <glib.h>
#include <gtk/gtk.h>
#include <glib/gstring.h>
#include <glib/gprintf.h>
#include <gconf/gconf.h>
#include <math.h>
#include "support.h"
#include "globals.h"
#include "map_management.h"
#include "converter.h"
#include "tile_management.h"
#include "callbacks.h"
#include "friends.h"
#include "gps_functions.h"
#include "geo_photos.h"
#include "poi.h"
#include "wp.h"


static GError		*error = NULL;
static GdkGC		*gc_map = NULL;

static GtkWidget	*drawingarea11 = NULL;

 


void
load_tile(	gchar *dir,
		int zoom,
		int x,
		int y,
		int offset_x,
		int offset_y)
{
	int detail_zoom=global_detail_zoom;	/* round (dpi/96.0)? */
	int overzoom=0;
	int upscale=1;
	gboolean tile_found = FALSE;
	repo_t *repo;
	static gchar filename[256];

	GdkPixbuf	*pixbuf = NULL;
	

	printf("* load tile()\n");


	if(gc_map)
		g_object_unref(gc_map);
	if(pixmap)
	{
		gc_map = gdk_gc_new(pixmap);
	}
	else printf("no drawable -> NULL\n");


	upscale = (int) powf (2.0, (float) detail_zoom);

	for(overzoom = detail_zoom;
	    overzoom <= detail_zoom + 3;
	    overzoom++)
	{
		g_sprintf(filename, "%s/%u/%u/%u.png", dir, zoom-overzoom, x/upscale, y/upscale);
		printf("** %d. IMG: %s\n", overzoom, filename);

		pixbuf = gdk_pixbuf_new_from_file (filename, NULL);

		if(pixbuf)
		{
			tile_found = TRUE;
			break;
		}		

		upscale *= 2;
	}
	
	if(pixbuf && overzoom)
	{
		GdkPixbuf	*pixbuf_scaled = NULL;

		
		pixbuf_scaled = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 256, 256); 

		gdk_pixbuf_scale (	pixbuf, pixbuf_scaled,
					0, 0,
					TILESIZE, TILESIZE,
					-TILESIZE*(x%upscale), -TILESIZE*(y%upscale),
					upscale, upscale,
					GDK_INTERP_NEAREST );

		if (pixbuf)
		{
			g_object_unref (pixbuf);
		}

		pixbuf = pixbuf_scaled;
	}

	if(!tile_found)
	{
		
		GtkWidget *widget;
			
		widget = lookup_widget(window1, "drawingarea1");
			
		gdk_draw_rectangle (
			pixmap,
			widget->style->white_gc,
			TRUE,
			offset_x, offset_y,
			256,
			256);
						
		gtk_widget_queue_draw_area (
			widget, 
			offset_x,offset_y,256,256);
		
		
		
		printf("PIXBUF: error loading png\n");
		error = NULL;
		

	}
	else
	{
		printf("PIXBUF: loading okay\n");

	
		
		gdk_draw_pixbuf (
			pixmap,
			gc_map,
			pixbuf,
			0,0,
			offset_x,offset_y,
			TILESIZE,TILESIZE,
			GDK_RGB_DITHER_NONE, 0, 0);

		g_object_unref (pixbuf);
	}


		
	
	
	drawingarea11 = lookup_widget(window1, "drawingarea1");
	
	gtk_widget_queue_draw_area (
		drawingarea11, 
		offset_x,offset_y,
		TILESIZE,TILESIZE);

	if(overzoom)
	{
		if (global_auto_download)
		{
			repo = global_curr_repo->data;
			download_tile(repo,zoom,x,y);
		}
		else
		{
			printf("*** Not downloading tile \n");
		}
	}	

}



void
fill_tiles_pixel(	int pixel_x,
			int pixel_y,
			int zoom)
{
	GtkWidget *widget;
	int i,j, width, height, tile_x0, tile_y0, tiles_nx, tiles_ny;
	int offset_xn = 0;
	int offset_yn = 0;
	int offset_x;
	int offset_y;
	gboolean success = FALSE;
	GError **error = NULL;
	repo_t *repo = g_new0(repo_t, 1);
	
	printf("*** %s(): xyz %d %d %d\n",__PRETTY_FUNCTION__,pixel_x,pixel_y,zoom);

	
	widget = lookup_widget(window1,"drawingarea1");
	
	repo = global_curr_repo->data;
	printf("---repo dir: %s \n",g_strdup(repo->dir));
	
	
	offset_x = - pixel_x % TILESIZE;
	offset_y = - pixel_y % TILESIZE;
	if (offset_x > 0) offset_x -= 256;
	if (offset_y > 0) offset_y -= 256;
	
	global_x = pixel_x;
	global_y = pixel_y;
	global_zoom = zoom;
	
	offset_xn = offset_x; 
	offset_yn = offset_y;
	
	width  = map_drawable->allocation.width;
	height = map_drawable->allocation.height;

	tiles_nx = floor((width  - offset_x) / TILESIZE) + 1;
	tiles_ny = floor((height - offset_y) / TILESIZE) + 1;
	
	

	
	tile_x0 =  floor((float)pixel_x / (float)TILESIZE);
	tile_y0 =  floor((float)pixel_y / (float)TILESIZE);
	
	
	
	

	for (i=tile_x0; i<(tile_x0+tiles_nx);i++)
	{
		for (j=tile_y0;  j<(tile_y0+tiles_ny); j++)
		{
			printf("---i,j,x,y,offsetx,y: %d,%d -- %d,%d -- %d,%d\n",i,j,pixel_x,pixel_y,offset_x,offset_y);

			if(	j<0			||
				i<0			||
				i>=exp(zoom * M_LN2)	||
				j>=exp(zoom * M_LN2))
			{
				gdk_draw_rectangle (
					pixmap,
					widget->style->white_gc,
					TRUE,
					offset_xn, offset_yn,
					TILESIZE,
					TILESIZE);
				
				gtk_widget_queue_draw_area (
					widget, 
					offset_xn,offset_yn,
					TILESIZE,TILESIZE);
				
			}
			else
			{
				load_tile(
					repo->dir,
					zoom,
					i,j,
					offset_xn,offset_yn);
			}
			offset_yn += TILESIZE;
		}
		offset_xn += TILESIZE;
		offset_yn = offset_y;
	}
	
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/global_x",
				global_x,
				error);
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/global_y",
				global_y,
				error);
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/global_zoom",
				global_zoom,
				error);
}

void
fill_tiles_latlon(	float lat,
			float lon,
			int zoom)
{
	int pixel_x, pixel_y;
	
	
	pixel_x = lon2pixel(zoom, lon);

	pixel_y = lat2pixel(zoom, lat);

	printf("fill_tiles_latlon(): lat %f  %i -- lon %f  %i\n",
	lat,pixel_y,lon,pixel_x);
	
	fill_tiles_pixel (pixel_x, pixel_y, zoom);
}

void
set_mapcenter(	float lat,
		float lon,
		int zoom)
{
	int pixel_x, pixel_y;
	
	lat = deg2rad(lat);
	lon = deg2rad(lon);
	
	
	pixel_x = lon2pixel(zoom, lon);
	pixel_y = lat2pixel(zoom, lat);

	printf("fill_tiles_latlon(): lat %f  %i -- lon %f  %i\n",
	lat,pixel_y,lon,pixel_x);
	
	osd_speed(TRUE);
	fill_tiles_pixel (	pixel_x - global_drawingarea_width/2, 
				pixel_y - global_drawingarea_height/2,
				zoom);
	print_track();
	paint_friends();
	paint_photos();
	paint_pois();
	paint_wp();
	osd_speed(TRUE); 
	


}



void
fill_tiles_latlon_hack(	float lat,
			float lon,
			int zoom)
{
	int pixel_x, pixel_y;
	
	
	pixel_x = lon2pixel(zoom, lon);

	pixel_y = lat2pixel(zoom, lat);

	printf("fill_tiles_latlon(): lat %f  %i -- lon %f  %i\n",
	lat,pixel_y,lon,pixel_x);
	
	fill_tiles_pixel (pixel_x - 240, pixel_y - 300, zoom);
}
