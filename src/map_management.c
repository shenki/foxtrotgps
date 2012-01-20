

#include <glib.h>
#include <gtk/gtk.h>
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
#include "tracks.h"

typedef struct {
	GdkPixbuf *pixbuf;
	gboolean reused;
} tile_hash_t;


static GdkGC		*gc_map = NULL;

static GtkWidget	*drawingarea11 = NULL;
static GHashTable	*hash_table = NULL;

void hash_destroy_key_func   (gpointer data);
void hash_destroy_value_func (gpointer data);
gboolean hash_sieve_func (gpointer key, gpointer value, gpointer user_data);

void
hash_destroy_key_func   (gpointer data)
{
	g_free(data);
}

void
hash_destroy_value_func (gpointer data)
{
	tile_hash_t *tile_hash = data;

	g_object_unref(tile_hash->pixbuf);
	g_free(data);
}

gboolean
hash_sieve_func (gpointer key, gpointer value, gpointer user_data)
{
	gboolean remove = TRUE;
	
	tile_hash_t *tile_hash = value;
	
	if(tile_hash->reused)
	{
		tile_hash->reused = FALSE;
		remove = FALSE;
	}

	return remove;
}


void
load_tile(	gchar *dir,
		int zoom,
		int x,
		int y,
		int offset_x,
		int offset_y)
{
	int		detail_zoom	= global_detail_zoom; /* round (dpi/96.0) */
	int		detail_scale	= (int) pow (2.0, (float) detail_zoom);
	int 		overzoom	= 0;
	int 		upscale		= 1;
	gboolean	hash_not_found = TRUE;
	static gchar 	filename[256];
	static gchar	wanted_filename[256];

	GdkPixbuf	*pixbuf		= NULL;
	repo_t 		*repo;
	tile_hash_t	*tile_hash;

	
	if(gc_map)
		g_object_unref(gc_map);
	if(pixmap)
	{
		gc_map = gdk_gc_new(pixmap);
	}
	else printf("no drawable -> NULL\n");

	upscale = detail_scale;
	zoom -= detail_zoom;

	g_snprintf(wanted_filename, 255, "%s/%u/%u/%u.png", dir, zoom, x, y);
	tile_hash = g_hash_table_lookup(hash_table, wanted_filename);
	
	if(tile_hash)
	{
		pixbuf = tile_hash->pixbuf;
		
		tile_hash->reused = TRUE;
		hash_not_found	  = FALSE;
	}
	
	else
	{
		
		for(overzoom=0; overzoom<=3; overzoom++)
		{
			g_snprintf(filename, 255, "%s/%u/%u/%u.png", dir, zoom-overzoom, x/upscale, y/upscale);
	
			pixbuf = gdk_pixbuf_new_from_file (filename, NULL);
	
			if(pixbuf)
				break;
	
			upscale *= 2;
		}
		
		if(pixbuf && upscale > 1)
		{
			GdkPixbuf	*pixbuf_scaled	= NULL;
			pixbuf_scaled = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 256, 256); 
	
			gdk_pixbuf_scale (	pixbuf, pixbuf_scaled,
						0, 0,
						TILESIZE, TILESIZE,
						-TILESIZE*(x%upscale), -TILESIZE*(y%upscale),
						upscale, upscale,
						GDK_INTERP_BILINEAR );

			if (pixbuf) {
				g_object_unref (pixbuf);
			}

			pixbuf = pixbuf_scaled;
		}
	}
	
	if(!pixbuf)
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
	}
	
	else
	{
		
		gdk_draw_pixbuf (
			pixmap,
			gc_map,
			pixbuf,
			0,0,
			offset_x,offset_y,
			TILESIZE,TILESIZE,
			GDK_RGB_DITHER_NONE, 0, 0);

		
		if(hash_not_found)
		{
			tile_hash = g_new0(tile_hash_t,1);
			tile_hash->pixbuf = pixbuf;
			tile_hash->reused = TRUE;
	
			g_hash_table_insert(hash_table, g_strdup(wanted_filename), tile_hash);
		}
	}

	
	drawingarea11 = lookup_widget(window1, "drawingarea1");
	
	gtk_widget_queue_draw_area (
		drawingarea11, 
		offset_x,offset_y,
		TILESIZE,TILESIZE);

	if(overzoom && global_auto_download)
	{
		repo = global_curr_repo->data;
		download_tile(repo,zoom,x/detail_scale,y/detail_scale);
	}	
}



void
fill_tiles_pixel(	int pixel_x,
			int pixel_y,
			int zoom,
			gboolean force_refresh)
{
	GtkWidget *widget;
	int i,j, i_corrected, width, height, tile_x0, tile_y0, tiles_nx, tiles_ny;
	int max_pixel;
	int offset_xn = 0;
	int offset_yn = 0;
	int offset_x;
	int offset_y;
	gboolean success = FALSE;
	GError **error = NULL;
	repo_t *repo = g_new0(repo_t, 1);
	
	
	if (!hash_table)
	{
		hash_table = g_hash_table_new_full (g_str_hash,
						    g_str_equal,
						    hash_destroy_key_func,
						    hash_destroy_value_func);
	}
	
	if(force_refresh)
	{
		g_hash_table_remove_all(hash_table);	
	}
	
	widget = lookup_widget(window1,"drawingarea1");
	
	repo = global_curr_repo->data;

	
	max_pixel = (int) exp2(zoom) * TILESIZE; 

	if(pixel_x < 0)
		pixel_x += max_pixel;
	
	else if (pixel_x > max_pixel)
		pixel_x -= max_pixel;	

	
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
	
	

	for (i=tile_x0; i<(tile_x0+tiles_nx); i++)
	{
		for (j=tile_y0;  j<(tile_y0+tiles_ny); j++)
		{
			
			

			
			if(j<0 || j>=exp2(zoom))
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
				i_corrected = (i>=exp2(zoom)) ? i-exp2(zoom) : i;
				
				load_tile(
					repo->dir,
					zoom,
					i_corrected,j,
					offset_xn,offset_yn);
			}
			offset_yn += TILESIZE;
		}
		offset_xn += TILESIZE;
		offset_yn = offset_y;
	}

	
	g_hash_table_foreach_remove (hash_table, hash_sieve_func, NULL);
	
	
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
	
	fill_tiles_pixel (pixel_x, pixel_y, zoom, FALSE);
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

	
	osd_speed(TRUE);
	fill_tiles_pixel (	pixel_x - global_drawingarea_width/2, 
				pixel_y - global_drawingarea_height/2,
				zoom, FALSE);
	print_track();
	paint_loaded_track();
	paint_friends();
	paint_photos();
	paint_pois();
	paint_wp();
	
	
}
