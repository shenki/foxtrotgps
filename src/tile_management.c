

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h> 
#include <math.h>
#include "globals.h"
#include "tile_management.h"
#include "map_management.h"
#include "gps_functions.h"
#include "callbacks.h"
#include "support.h"
#include "converter.h"
#include "geo_photos.h"
#include "friends.h"
#include "poi.h"
#include "wp.h"
#include "tracks.h"
#include "route.h"

GtkWidget *Bar = NULL; 
static GSList *tile_download_list = NULL;

static gboolean map_redraw_scheduled;

typedef struct  {
	char *tile_url;
} Repo_data_t;

	

int
update_thread_number (int change)
{
	static int current_number = 0;
	int ret_val;
	static GStaticMutex mutex = G_STATIC_MUTEX_INIT;
	
	g_static_mutex_lock (&mutex);
	ret_val = current_number += change; 
	g_static_mutex_unlock (&mutex);


	return ret_val;
}
	
	
gboolean
map_redraw(void *p)
{
	int number_threads;
	number_threads = update_thread_number(0);
	
	
	
	if (!drag_started)
	{
		map_redraw_scheduled = FALSE;
	
		fill_tiles_pixel(global_x, global_y, global_zoom, TRUE);
		paint_track();
		paint_loaded_track();
		paint_friends();
		paint_photos();
		paint_pois();
		paint_wp();
		paint_route();
		paint_myposition();
		osd_speed(TRUE);
		
		return FALSE;
	}
	else
		return TRUE;
}	
	
	
size_t 
cb_write_func(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	
	
	return 
	fwrite(ptr, size, nmemb, stream); 
}


size_t
cb_read_func (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  return fread(ptr, size, nmemb, stream);
}

int
cb_progress_func(GtkWidget *Bar,
                     double t, 
                     double d, 
                     double ultotal,
                     double ulnow)
{

  return 0;

}



gboolean
download_tile(	repo_t *repo,
		int zoom,
		int x,
		int y)
{
	gchar *tile_data;
	gchar tile_data_tmp[512];
	gchar filtered_repo_uri[256];
	gchar tile_url[256];
	static GHashTable *ht = NULL;
	gchar *key;
	int value=1;
	int *found;
	int maxzoom=18;
	gboolean retval = FALSE;
	gchar *inp, *outp;
	int nfmts;
	
	if(ht==NULL)
	{
		ht = g_hash_table_new (g_str_hash, g_str_equal);
	}


	/* Sanitise repo->uri, filtering out bad/excessive formatters,
	   so bad user inputs here don't cause a crash or other badness:
	*/
	nfmts = 0;
	inp = repo->uri;
	outp = filtered_repo_uri;
	while (*inp && outp - filtered_repo_uri < (sizeof filtered_repo_uri) - 1)
	{
		if (*inp == '%')
		{
			switch (*(++inp))
			{
			case 'd': /* support up to 3 "%d" formatters */
				if (++nfmts > 3)
				{
			default: /* just drop unsupported formatters */
					++inp;
					continue;
				}
			/* fall through */
			case '%': /* support "%%" for literal %-chars */
				(*outp++) = '%';
			}
		}

		*(outp++) = *(inp++);
	}
	*outp = '\0';

	if (!repo->inverted_zoom)
		g_sprintf(tile_url, filtered_repo_uri, zoom, x, y);
	else
		g_sprintf(tile_url, filtered_repo_uri, x, y, zoom); 
	
	
	g_sprintf(tile_data_tmp, "%s|%s/%d/%d/%d.png|%s/%d/%d/",
			tile_url,
			repo->dir, zoom, x, y,
			repo->dir, zoom, x);
	
	
	if(strcmp(repo->uri,"maps-for-free")==0)
	{
		g_sprintf(tile_data_tmp, 
				"http://maps-for-free.com/layer/relief/z%d/row%d/%d_%d-%d.jpg"
				"|%s/%d/%d/%d.png|%s/%d/%d/",
				zoom,y,zoom,x,y,
				repo->dir, zoom, x, y,
				repo->dir, zoom, x);
		maxzoom=12;
	}
	
	if(strcmp(repo->uri,"openaerial")==0)
	{
		g_sprintf(tile_data_tmp, 
				"http://tile.openaerialmap.org/tiles/1.0.0/openaerialmap-900913/%d/%d/%d.jpg"
				"|%s/%d/%d/%d.png|%s/%d/%d/",
				zoom,x,y,
				repo->dir, zoom, x, y,
				repo->dir, zoom, x);
	}


	tile_data = g_strdup(tile_data_tmp);
	
	key = g_strdup_printf("%s/%d/%d/%d", repo->dir, zoom, x, y);
	found = g_hash_table_lookup (ht, key);

	if(!found && zoom <=maxzoom)
	{
		g_hash_table_insert(ht, key, &value);
			
		if (!g_thread_create(&dl_thread, (void *)tile_data, FALSE, NULL) != 0)
			g_warning("can't create DL thread");
		
		retval = TRUE;
	}	
	
	
	
	

	return retval;
}




void *
dl_thread(void *ptr)
{



	CURL *curl;
	CURLcode res;
	FILE *outfile;
	char err_buffer[CURL_ERROR_SIZE];
	int number_threads;

	const gchar *tile_data;
	gchar **arr1;

	int mkres;
	tile_data = ptr;

	arr1 = g_strsplit(tile_data,"|",3);

	if (global_no_redownload)
	{
		struct stat outfile_buf;
		if (!stat(arr1[1], &outfile_buf) && outfile_buf.st_size != 0)
		{
			printf("Tile exists - not redownladed: %s\n", arr1[1]);
			return NULL;
		}
	}

	number_threads = update_thread_number(1);


	mkres = g_mkdir_with_parents(arr1[2],0700);
	
	
	
	
	
	
	outfile = fopen(arr1[1], "w");
	if (outfile==NULL)
	{
		perror("###### ERROR - Could not open OUTFILE");
		printf("aieee: outfile=NULL\n");
	}

	curl = curl_easy_init();

	if(curl && outfile) 
	{
		/* Multithreading requires setting NOSIGNAL,
		   otherwise we're likely to crash in the event
		   of a resolver timeout:
		 */
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		curl_easy_setopt(curl, CURLOPT_URL, arr1[0]);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, 
			"libcurl-agent/1.0 | " PACKAGE " " VERSION " | " __VERSION__);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,	 cb_write_func);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION,	 cb_read_func);
		
		
		
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, err_buffer);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1); 
		
		res = curl_easy_perform(curl);
		
		if (res!=0)
			printf("TILE DL PROBLEM: %s\n   %s\n",err_buffer,tile_data);
		
		
		curl_easy_cleanup(curl);
		
		
		gdk_threads_enter();
		if (!map_redraw_scheduled) {
			g_timeout_add(500, map_redraw, NULL);
			map_redraw_scheduled = TRUE;
		}
		gdk_threads_leave();
	}
	if(outfile != NULL)
		fclose(outfile);

	number_threads = update_thread_number(-1);

	g_free(ptr);
	return NULL;
}


void
cb_download_maps(GtkWidget *dialog)
{
	GtkToggleButton *z1, *z2, *z3, *z4, *z5, *z6;
	bbox_t bbox;
	int zoom_end = 1;
	
	bbox = get_bbox();
	
	z1 = (GtkToggleButton *)lookup_widget(dialog, "radiobutton2");
	z2 = (GtkToggleButton *)lookup_widget(dialog, "radiobutton3");
	z3 = (GtkToggleButton *)lookup_widget(dialog, "radiobutton4");
	z4 = (GtkToggleButton *)lookup_widget(dialog, "radiobutton5");
	z5 = (GtkToggleButton *)lookup_widget(dialog, "radiobutton6");
	z6 = (GtkToggleButton *)lookup_widget(dialog, "radiobutton7");

	zoom_end = (gtk_toggle_button_get_active(z1)) ? global_zoom + 1 : zoom_end; 
	zoom_end = (gtk_toggle_button_get_active(z2)) ? global_zoom + 2 : zoom_end;
	zoom_end = (gtk_toggle_button_get_active(z3)) ? global_zoom + 3 : zoom_end;
	zoom_end = (gtk_toggle_button_get_active(z4)) ? global_zoom + 4 : zoom_end;
	zoom_end = (gtk_toggle_button_get_active(z5)) ? global_zoom + 5 : zoom_end;
	zoom_end = (gtk_toggle_button_get_active(z6)) ? global_zoom + 6 : zoom_end;
	
	

	download_maps(bbox, global_zoom+1, zoom_end);

	gtk_widget_hide(dialog);
}



void
download_maps(bbox_t bbox, int zoom_start, int zoom_end)
{
	GSList *list = NULL;
	tile_t *tile;
	bbox_pixel_t bbox_pixel;
	int zoom;

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	zoom_end = (zoom_end > 17) ? 17 : zoom_end;
	
	for(zoom=zoom_start; zoom<=zoom_end; zoom++)
	{
		bbox_pixel = get_bbox_pixel(bbox, zoom);
		queue_tile_dl_for_bbox(bbox_pixel,zoom);
	}
	
	
	g_timeout_add(100, timer_tile_download, NULL);

	for(list = tile_download_list; list != NULL; list = list->next)
	{		
		tile = list->data;

		printf("LIST: %d %d %d %s\n",tile->x, tile->y, tile->zoom,tile->repo->name);	
		
	}

}

tile_t
get_tile(int pixel_x, int pixel_y, int zoom)
{
	tile_t tile;
	
	tile.x =  (int)floor((float)pixel_x / (float)TILESIZE);
	tile.y =  (int)floor((float)pixel_y / (float)TILESIZE);
	tile.zoom = zoom;
	tile.repo = global_curr_repo->data;
	
	return tile;
}


void
queue_tile_dl_for_bbox(bbox_pixel_t bbox_pixel, int zoom)
{
	tile_t tile_11, tile_22;
	int i,j,k=0;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	tile_11 = get_tile(bbox_pixel.x1, bbox_pixel.y1, zoom);
	tile_22 = get_tile(bbox_pixel.x2, bbox_pixel.y2, zoom);
	
	
	for(i=tile_11.x; i<=tile_22.x; i++)
	{
		
		for(j=tile_11.y; j<=tile_22.y; j++)
		{
			tile_t *tile = g_new0(tile_t,1);
			printf("### DEBUG queue: %d %d - %d\n",i,j,k);
			
			k++;
			tile->x = i;
			tile->y = j;
			tile->zoom = zoom;
			tile->repo = global_curr_repo->data;
			
			
			tile_download_list = g_slist_prepend(tile_download_list, tile);
			global_tiles_in_dl_queue++;
		}
	}
}

bbox_t
get_bbox()
{
	bbox_t bbox;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	bbox.lat1 = pixel2lat(global_zoom, global_y);
	bbox.lon1 = pixel2lon(global_zoom, global_x);
	bbox.lat2 = pixel2lat(global_zoom, global_y + global_drawingarea_height);
	bbox.lon2 = pixel2lon(global_zoom, global_x + global_drawingarea_width);

	printf("BBOX: %f %f %f %f \n", bbox.lat1, bbox.lon1, bbox.lat2, bbox.lon2);
	
	return bbox;
}

bbox_t
get_bbox_deg()
{
	bbox_t bbox;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	bbox.lat1 = rad2deg( pixel2lat(global_zoom, global_y) );
	bbox.lon1 = rad2deg( pixel2lon(global_zoom, global_x) );
	bbox.lat2 = rad2deg( pixel2lat(global_zoom, global_y + global_drawingarea_height) );
	bbox.lon2 = rad2deg( pixel2lon(global_zoom, global_x + global_drawingarea_width) );

	printf("BBOX: %f %f %f %f \n", bbox.lat1, bbox.lon1, bbox.lat2, bbox.lon2);
	
	return bbox;
}

bbox_pixel_t
get_bbox_pixel(bbox_t bbox, int zoom)
{
	bbox_pixel_t bbox_pixel;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	bbox_pixel.x1 = lon2pixel(zoom, bbox.lon1);
	bbox_pixel.y1 = lat2pixel(zoom, bbox.lat1);
	bbox_pixel.x2 = lon2pixel(zoom, bbox.lon2);
	bbox_pixel.y2 = lat2pixel(zoom, bbox.lat2);

	printf("DEBUG: xy12 %d %d %d %d \n",bbox_pixel.x1,bbox_pixel.y1,bbox_pixel.x2,bbox_pixel.y2);
	
	return	bbox_pixel;
}


gboolean
timer_tile_download(gpointer data)
{
	GSList *list = NULL;
	tile_t *tile;
	gboolean more_tiles = TRUE;
	int i;
	int running_downloads, possible_downloads, max_downloads = 6;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	
	running_downloads = update_thread_number(0);
	
	possible_downloads = max_downloads - running_downloads;
	
	for( i=1; i<=possible_downloads; i++)
	{
printf("\n\n####LOOP %d %d ###########\n\n",i,possible_downloads);		
		list = g_slist_nth(tile_download_list, 0);
		if (list)
		{
			
			tile = list->data;
			printf("\n\n\nTIMER DL: %d %d -- %d\n\n\n", tile->x, tile->y, possible_downloads);
			
			if(	tile->x >= 0				&&
				tile->y >= 0				&&
				tile->x < exp(tile->zoom * M_LN2)	&&
				tile->y < exp(tile->zoom * M_LN2))
			{
				download_tile(tile->repo, tile->zoom, tile->x, tile->y);
			}
			global_tiles_in_dl_queue--;
		}
		else
		{
			printf("========= TILE DL LIST END \n");
			more_tiles = FALSE;
			global_tiles_in_dl_queue = 0;
		}
		tile_download_list = g_slist_delete_link(tile_download_list, list);
	}
	
	return more_tiles;
}
