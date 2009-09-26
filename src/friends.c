

#include "friends.h"
#include "globals.h"
#include "converter.h"
#include "support.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>


struct mem_struct {
	char *memory;
	size_t size;
};


static size_t
cb_write_to_mem(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct mem_struct *mem = (struct mem_struct *)data;
	
	mem->memory = (char *)g_realloc(mem->memory, mem->size + realsize + 1);
	
	if (mem->memory)
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

static GdkPixbuf	*friend_icon = NULL;
static GdkGC		*gc_map = NULL;


























gboolean
update_position()
{		
	GtkLabel *label_msg;
	label_msg = (GtkLabel *)lookup_widget(window1, "label51");
	gtk_label_set_label(label_msg, "Connecting...");

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	if (!g_thread_create(&update_position_thread, NULL, FALSE, NULL) != 0)
		g_warning("### can't create friend thread\n");

	return TRUE;	
}
	
void *
update_position_thread(void *ptr)
{
	int i=1;
	
	GtkToggleButton *v_public, *v_member, *v_friend;
	GtkToggleButton *g_public, *g_member, *g_friend;
	GtkEntry *nick, *pass, *email, *msg;
	GtkLabel *label_msg;
	const gchar *n, *p, *e, *m;	
	gchar *vp, *vm, *vf, *gp, *gm, *gf, *ff_mode;
	static gchar lat[64], lon[64], mode[64];
	static gchar alt[16] = "0", speed[16] = "0", head[16]="0";
	
	
	gchar **user_data_sets;
	long int response_code;
	
	CURL *curl_handle;
	
	struct curl_httppost *formdata=NULL;
	struct curl_httppost *lastptr=NULL;
		
	struct mem_struct chunk;
	
	chunk.memory=NULL;
	chunk.size = 0;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);


	label_msg = (GtkLabel *)lookup_widget(window1, "label51");

	
	v_public = (GtkToggleButton *)lookup_widget(window1, "checkbutton3");
	v_member = (GtkToggleButton *)lookup_widget(window1, "checkbutton4");
	v_friend = (GtkToggleButton *)lookup_widget(window1, "checkbutton5");
	g_public = (GtkToggleButton *)lookup_widget(window1, "checkbutton6");
	g_member = (GtkToggleButton *)lookup_widget(window1, "checkbutton7");
	g_friend = (GtkToggleButton *)lookup_widget(window1, "checkbutton8");
	nick  = (GtkEntry *)lookup_widget(window1, "entry7");
	pass  = (GtkEntry *)lookup_widget(window1, "entry8");
	email = (GtkEntry *)lookup_widget(window1, "entry9");
	msg   = (GtkEntry *)lookup_widget(window1, "entry29");

	vp = (gtk_toggle_button_get_active(v_public)) ? g_strdup("y") : g_strdup("n");
	vm = (gtk_toggle_button_get_active(v_member)) ? g_strdup("y") : g_strdup("n");
	vf = (gtk_toggle_button_get_active(v_friend)) ? g_strdup("y") : g_strdup("n");
	gp = (gtk_toggle_button_get_active(g_public)) ? g_strdup("y") : g_strdup("n");
	gm = (gtk_toggle_button_get_active(g_member)) ? g_strdup("y") : g_strdup("n");
	gf = (gtk_toggle_button_get_active(g_friend)) ? g_strdup("y") : g_strdup("n");

	switch (global_ff_mode) {
	case PRIVATE_MODE: 
		ff_mode = g_strdup("private");
		break;
	case FRIEND_MODE:
		ff_mode = g_strdup("friends");
		break;
	case FUN_MODE:
		ff_mode = g_strdup("fun");
		break;
	default:
		ff_mode = g_strdup("");
	}
	
	n = gtk_entry_get_text(nick);
	p = gtk_entry_get_text(pass);
	e = gtk_entry_get_text(email);
	m = gtk_entry_get_text(msg);

	
	if (global_myposition.lat && global_myposition.lon)
	{
		g_sprintf(lat, "%f", global_myposition.lat);
		g_sprintf(lon, "%f", global_myposition.lon);
		g_sprintf(mode, "%s|%dx%d", "man", global_drawingarea_width, global_drawingarea_height);		
	}
	else if (gpsdata && gpsdata->fix.latitude !=0)
	{
		g_sprintf(lat, "%f", gpsdata->fix.latitude);
		g_sprintf(lon, "%f", gpsdata->fix.longitude);
		g_sprintf(mode, "%s|%dx%d", "gps", global_drawingarea_width, global_drawingarea_height);		
	}
	else
	{
		float tmplat, tmplon;
		
		tmplat = rad2deg( pixel2lat(global_zoom, global_y+global_drawingarea_height/2) );
		tmplon = rad2deg( pixel2lon(global_zoom, global_x+global_drawingarea_width/2) );
		g_sprintf(lat, "%f", tmplat);
		g_sprintf(lon, "%f", tmplon);
		g_sprintf(mode, "%s|%dx%d", "atm", global_drawingarea_width, global_drawingarea_height);		

		printf("## friends: neither fix, no manual position %f %f\n", tmplat, tmplon);

	}
	
	
	if(gpsdata)
	{
		g_snprintf(alt, 16, "%.1f", gpsdata->fix.altitude);
		g_snprintf(head, 16, "%.1f", gpsdata->fix.track);
		g_snprintf(speed, 16, "%.1f", gpsdata->fix.speed);
	}
	
	curl_global_init(CURL_GLOBAL_ALL);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "lat",
               CURLFORM_COPYCONTENTS, lat,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "lon",
               CURLFORM_COPYCONTENTS, lon,
               CURLFORM_END);
	
	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "alt",
               CURLFORM_COPYCONTENTS, alt,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "head",
               CURLFORM_COPYCONTENTS, head,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "speed",
               CURLFORM_COPYCONTENTS, speed,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "mode",
               CURLFORM_COPYCONTENTS, mode,
               CURLFORM_END);
	       
       	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "ff_mode",
               CURLFORM_COPYCONTENTS, ff_mode,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "nick",
               CURLFORM_COPYCONTENTS, n,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "pass",
               CURLFORM_COPYCONTENTS, p,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "msg",
               CURLFORM_COPYCONTENTS, m,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "v_public",
               CURLFORM_COPYCONTENTS, vp,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "v_member",
               CURLFORM_COPYCONTENTS, vm,
               CURLFORM_END);
	       	
		
	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "v_friend",
               CURLFORM_COPYCONTENTS, vf,
               CURLFORM_END);
	       
	       
	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "g_public",
               CURLFORM_COPYCONTENTS, gp,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "g_member",
               CURLFORM_COPYCONTENTS, gm,
               CURLFORM_END);
	       	
		
	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "g_friend",
               CURLFORM_COPYCONTENTS, gf,
               CURLFORM_END);
	       
	       
	curl_handle = curl_easy_init();
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.tangogps.org/friends/update_pos.php");
	curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formdata);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb_write_to_mem);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0 |" VERSION " | " __VERSION__);



	curl_easy_perform(curl_handle);
	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &response_code);
	
	
	curl_easy_cleanup(curl_handle);
	
	printf("REPLY: %s - response: %d\n",chunk.memory, (int)response_code);
	
	
	
	


	if (response_code == 200) 
	{ 
		
		
		
		

		user_data_sets = g_strsplit_set (chunk.memory, "|", -1);
	
			
		gdk_threads_enter();
		g_slist_free(friends_list);
		friends_list = NULL;
		gtk_label_set_label(label_msg, user_data_sets[0]); 
		gdk_threads_leave();
		
		while (user_data_sets[i] && !g_str_equal(user_data_sets[i],"EOD") )
		{
			gchar **array;
			int len=0;
			friend_t *friend = g_new0(friend_t,1);
			
			array = g_strsplit(user_data_sets[i],"#",-1);
			while (array[len]) len++;
			
			
			
			
			
			if(len>=7)
			{
				friend->type = atoi(g_strdup(array[0]));
				friend->nick  = g_strdup(array[1]);
				friend->lat = atof(g_strdup(array[2]));printf("##%f\n",friend->lat);
				friend->lon = atof(g_strdup(array[3]));
				friend->head = atoi(g_strdup(array[4]));
				friend->lastseen = g_strdup(array[5]);
				friend->msg = g_strdup(array[6]);
				
				friends_list = g_slist_append(friends_list, friend);
			}
			
			
			i++;
		}
	}
	else
	{
		gdk_threads_enter();
		gtk_label_set_text(label_msg, "No response (200)"); 
		gdk_threads_leave();
		
	}
	
	
	
	
	gdk_threads_enter();
	paint_friends();
	
	gdk_threads_leave();
	
	
	if(chunk.memory)
		g_free(chunk.memory);
	
	curl_global_cleanup();
	
	g_free(vp);
	g_free(vm);
	g_free(vf);
	g_free(gp);
	g_free(gm);
	g_free(gf);
	g_free(ff_mode);

	return NULL;
}

void
paint_friends()
{	
	GSList *list;
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
	

	if(!friend_icon)
	{
		friend_icon = gdk_pixbuf_new_from_file_at_size (
			PACKAGE_PIXMAPS_DIR "/tangogps-friend.png", 24,24,
			&error);
	}
	if (pixmap && !gc_map)	
		gc_map = gdk_gc_new(pixmap);
		
	

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	if (global_show_friends)
		{
		for(list = friends_list; list != NULL; list = list->next)
		{
			friend_t *f = list->data;
		
			lat = deg2rad(f->lat);
			lon = deg2rad(f->lon);
			
			
			
			
			pixel_x = lon2pixel(global_zoom, lon);
			pixel_y = lat2pixel(global_zoom, lat);
			
			x = pixel_x - global_x;
			y = pixel_y - global_y;
			
			f->screen_x = x;
			f->screen_y = y;
			
			
			
			if(!friend_icon)
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
					friend_icon,
					0,0,
					x-12,y-12,
					24,24,
					GDK_RGB_DITHER_NONE, 0, 0);
				
				gtk_widget_queue_draw_area (
					map_drawable, 
					x-12, y-12,
					24,24);
			}
			printf("FRIEND: %s lat %f - lon %f\n",f->nick,f->lat, f->lon);
		}
	}
}

void
update_position0()
{
	CURL *curl;
	CURLcode res;

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	curl = curl_easy_init();
	
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, 
				"127.0.0.1/friends/update_position.php?lat=1&lon=1");
		res = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
	}
	
}








int
register_nick()
{		
	GtkLabel *label_msg;
	label_msg = (GtkLabel *)lookup_widget(window1, "label62");
	gtk_label_set_text(label_msg, "Connecting...");

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	if (!g_thread_create(&register_nick_thread, NULL, FALSE, NULL) != 0)
		g_warning("### can't create register_nick() thread\n");
	
	return 0;
}
	
void *
register_nick_thread(void *ptr)
{
	
	GtkEntry *nick, *pass, *email;
	GtkLabel *label_msg;
	const gchar *n, *p, *e;
	gchar *buffer;
	
	
	
	CURL *curl_handle;
	
	struct curl_httppost *formdata=NULL;
	struct curl_httppost *lastptr=NULL;
		
	struct mem_struct chunk;
	
	chunk.memory=NULL;
	chunk.size = 0;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);



	
	nick  = (GtkEntry *)lookup_widget(window1, "entry7");
	pass  = (GtkEntry *)lookup_widget(window1, "entry8");
	email = (GtkEntry *)lookup_widget(window1, "entry9");

	n = gtk_entry_get_text(nick);
	p = gtk_entry_get_text(pass);
	e = gtk_entry_get_text(email);

	
	curl_global_init(CURL_GLOBAL_ALL);

	       
	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "nick",
               CURLFORM_COPYCONTENTS, n,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "pass",
               CURLFORM_COPYCONTENTS, p,
               CURLFORM_END);

	curl_formadd(&formdata,
               &lastptr,
               CURLFORM_COPYNAME, "email",
               CURLFORM_COPYCONTENTS, e,
               CURLFORM_END);

	       
	       
	curl_handle = curl_easy_init();
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.tangogps.org/friends/register_nick.php");
	curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formdata);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb_write_to_mem);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");


	curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);

	printf("REPLY: %s %d \n",chunk.memory, (int)chunk.size);

	if((int)chunk.size > 0){
		buffer = g_strdup(chunk.memory);
	}
	else
		buffer = g_strdup("Oh. Some error occurred...");

	gdk_threads_enter();
	label_msg = (GtkLabel *)lookup_widget(window1, "label62");
	gtk_label_set_text(label_msg, buffer); 
	gdk_threads_leave();
	

	
	
	
	curl_global_cleanup();
	
	return NULL;
}
