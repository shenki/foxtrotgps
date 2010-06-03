

#include "friends.h"
#include "globals.h"
#include "converter.h"
#include "interface.h"
#include "support.h"
#include "wp.h"
#include "util.h"
#include "map_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>



void
on_msg_friend_clicked(GtkButton *button, gpointer user_data);

void
on_goto_friend_clicked(GtkButton *button, gpointer user_data);

void
on_msg_send_clicked(GtkButton *button, gpointer user_data);


void *
thread_send_message(void *ptr);

GSList*
create_msg_postdata(msg_t *m);

void
process_msg_replydata(postreply_t *postreply);

void
add_message(msg_t *m);

GtkWidget*
create_msg_box(msg_t *m);

void
on_goto_friend2_clicked(GtkButton *button, gpointer user_data);




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
static char		*db_ts_last_request_friends = NULL;


















gboolean
update_position()
{		
	GtkLabel *label_msg;
	label_msg = (GtkLabel *)lookup_widget(window1, "label51");
	gtk_label_set_label(label_msg, "Connecting...");

	if (!g_thread_create(&update_position_thread, NULL, FALSE, NULL) != 0)
		g_warning("### can't create friend thread\n");

	return TRUE;	
}
	
void *
update_position_thread(void *ptr)
{
	int i=1;
	
	GtkEntry *nick, *pass, *email, *msg;
	GtkLabel *label_msg;
	const gchar *n, *p, *e, *m;	
	gchar *ff_mode;
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
	

gdk_threads_enter();
	
	label_msg = (GtkLabel *)lookup_widget(window1, "label51");

	
	nick  = (GtkEntry *)lookup_widget(window1, "entry7");
	pass  = (GtkEntry *)lookup_widget(window1, "entry8");
	email = (GtkEntry *)lookup_widget(window1, "entry9");
	msg   = (GtkEntry *)lookup_widget(window1, "entry29");

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

gdk_threads_leave();
	
	
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
	}
	
	
	if(gpsdata)
	{
		g_snprintf(alt, 16, "%.1f", gpsdata->fix.altitude);
		g_snprintf(head, 16, "%.1f", gpsdata->fix.heading);
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
	       
	       
	curl_handle = curl_easy_init();
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.tangogps.org/friends/update_pos.php");
	curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formdata);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb_write_to_mem);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0 |" VERSION " | " __VERSION__);



	curl_easy_perform(curl_handle);
	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &response_code);
	
	
	curl_easy_cleanup(curl_handle);
	
	
	
	
	
	


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
				friend->lat = atof(g_strdup(array[2]));
				friend->lon = atof(g_strdup(array[3]));
				friend->head = atoi(g_strdup(array[4]));
				friend->lastseen = g_strdup(array[5]);
				friend->away_msg = g_strdup(array[6]);
				
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
			PACKAGE_PIXMAPS_DIR "/" PACKAGE "-friend.png", 24,24,
			&error);
	}
	if (pixmap && !gc_map)	
		gc_map = gdk_gc_new(pixmap);
		
	
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


GtkWidget*
create_friend_box(friend_t *f)
{
	GtkWidget *hbox, *label, *vbox, *button;
	char *label_txt;
	
	label_txt = g_strdup_printf("<b>%s</b>\nLast seen:\n%s\n<i>%s</i>",f->nick, f->lastseen, f->away_msg);
	
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_widget_show (hbox);
	
	label = gtk_label_new ("");
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);

	gtk_label_set_label(GTK_LABEL(label), label_txt);
	
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
	
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
	
	button = gtk_button_new_with_mnemonic (_("Msg"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 2);
	
	g_signal_connect ((gpointer) button, "clicked",
				G_CALLBACK (on_msg_friend_clicked),
				(gpointer) f->nick);
				
	button = gtk_button_new_with_mnemonic (_("Go To"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 2);
	
	g_signal_connect ((gpointer) button, "clicked",
				G_CALLBACK (on_goto_friend_clicked),
				(gpointer) f);
	return hbox;
}


void
on_msg_friend_clicked(GtkButton *button, gpointer user_data)
{
	GladeXML *gladexml;
	GtkWidget *widget, *window;
	char *label_txt;
	char *to;
	
	to = user_data;
	label_txt = g_strdup_printf("Send Message To: <b>%s</b>", to);
	
	printf("* %s() %s\n", __PRETTY_FUNCTION__, label_txt);
	
	widget = lookup_widget(GTK_WIDGET(button), "window8");
	gtk_widget_destroy(widget);
	
	gladexml = glade_xml_new (gladefile, "dialog9", GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	window = glade_xml_get_widget (gladexml, "dialog9");
	g_signal_connect_swapped (window, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);

	gtk_widget_show(window);

	widget = lookup_widget(window, "label188");	
	gtk_label_set_label(GTK_LABEL(widget), label_txt);

	widget = lookup_widget(window, "okbutton10");
	g_signal_connect ((gpointer) GTK_BUTTON(widget), "clicked",
				G_CALLBACK (on_msg_send_clicked),
				(gpointer) to);

}

void
on_goto_friend_clicked(GtkButton *button, gpointer user_data)
{
	GtkWidget *widget;
	
	friend_t *f;
	f = user_data;
	
	printf("btn42 clicked: %s\n", f->nick);
	
	widget = lookup_widget(GTK_WIDGET(button), "window8");
	set_current_wp(deg2rad(f->lat), deg2rad(f->lon));
	gtk_widget_destroy(widget);
}

void
on_msg_send_clicked(GtkButton *button, gpointer user_data)
{
	GtkWidget *widget;
	char *to;
	msg_t *m;
	
	to = user_data;
	m = g_new0(msg_t,1);
	
	widget = lookup_widget(GTK_WIDGET(button), "entry30");
	m->txt = g_strdup( gtk_entry_get_text(GTK_ENTRY(widget)) );
	m->to = g_strdup(to);
	if (global_myposition.lat && global_myposition.lon)
	{
		m->lat = global_myposition.lat;
		m->lon = global_myposition.lon;
	}
	else if (gpsdata)
	{
		m->lat = gpsdata->fix.latitude;
		m->lon = gpsdata->fix.longitude;
	}
	else
	{
		m->lat = 0;
		m->lon = 0;
	}
		
	printf("* %s() %s %s %f %f\n", __PRETTY_FUNCTION__, to, m->txt, m->lat,m->lon);
	
	add_message(m);
	send_message((gpointer) m);
	widget = lookup_widget(GTK_WIDGET(button), "dialog9");
	gtk_widget_destroy(widget);
}

gboolean
send_message(gpointer user_data)
{
	GSList *postdata = NULL;
	msg_t *m;
	
	m = user_data;

	postdata = create_msg_postdata(m);

	if (!g_thread_create(&thread_send_message, postdata, FALSE, NULL) != 0)
		g_warning("### can't create mission thread\n");
	
	return TRUE;
}

void *
thread_send_message(void *ptr)
{
	
	GSList		*postdata = NULL;
	postreply_t	*postreply;
	
		

	postdata = ptr;

	
	postreply = mycurl__do_http_post(MSG_SEND_URL, postdata, VERSION);
	

	
	
	gdk_threads_enter();
	process_msg_replydata(postreply);
	gdk_threads_leave();

	
	
	g_slist_free(postdata);
	g_free(postreply);
	
	return NULL;
}

GSList*
create_msg_postdata(msg_t *m)
{
	GSList		*postdata = NULL;
	const char *n, *p;
	postdata_item_t *item;

		
	
	
	n = gtk_entry_get_text((GtkEntry *)lookup_widget(window1, "entry7"));
	p = gtk_entry_get_text((GtkEntry *)lookup_widget(window1, "entry8"));
	
	item = g_new0(postdata_item_t, 1);
	item->name=g_strdup("user");
	item->value=g_strdup(n);
	postdata = g_slist_append(postdata, item);

	item = g_new0(postdata_item_t, 1);
	item->name=g_strdup("pass");
	item->value=g_strdup(p);
	postdata = g_slist_append(postdata, item);
	
	

	if(m)
	{
		
		item = g_new0(postdata_item_t, 1);
		item->name=g_strdup("lat");
		item->value=g_strdup_printf("%f", m->lat);
		postdata = g_slist_append(postdata, item);
		
		item = g_new0(postdata_item_t, 1);
		item->name=g_strdup("lon");
		item->value=g_strdup_printf("%f", m->lon);
		postdata = g_slist_append(postdata, item);	
		
		item = g_new0(postdata_item_t, 1);
		item->name=g_strdup("txt");
		item->value=g_strdup_printf("%s", m->txt);
		postdata = g_slist_append(postdata, item);	
		
		item = g_new0(postdata_item_t, 1);
		item->name=g_strdup("to");
		item->value=g_strdup_printf("%s", m->to);
		postdata = g_slist_append(postdata, item);	
	}

	
	
	if(db_ts_last_request_friends)
	{
		item = g_new0(postdata_item_t, 1);
		item->name=g_strdup("db_ts_last_request_friends");
		item->value=g_strdup(db_ts_last_request_friends);
		postdata = g_slist_append(postdata, item);
	}
	
	return postdata;
}


void
process_msg_replydata(postreply_t *postreply)
{
	GtkWidget *widget;
	char **arr0 = NULL, **arr = NULL;
	msg_t *msg = NULL;
	int i = 1;
	static gboolean first_call = TRUE;
	
	
	
	widget = lookup_widget(window1, "label132");
	
	
	
	
	if(postreply->status_code == 200 && postreply->size > 0)
	{
		arr0 = g_strsplit (postreply->data, "###", -1);
		
		
		
		if (arr0[0] && strlen(arr0[0]))
		{
			char *err_msg;
			
			arr = g_strsplit (arr0[0], "|", -1);
			
			err_msg	= g_strdup(arr[4]);
			gtk_label_set_label(GTK_LABEL(widget), err_msg );

			
			if(atoi(arr[6]) > 0)
			{
				
				db_ts_last_request_friends = g_strdup(arr[2]);
				
				if(first_call)
				{
					GtkWidget *widget = NULL;
					
					widget = lookup_widget(window1, "button35");
					gtk_widget_show(widget);
					
					first_call = FALSE;
				}
				else
					global_new_msg = TRUE;
			}
			
			
			
			g_strfreev(arr);
		}
		
		
		while (arr0[i] && strlen(arr0[i]) )
		{

			
			msg = g_new0(msg_t, 1);
			
			
			arr = g_strsplit (arr0[i], "|||", -1);
			
			
			
			
			msg->id 	= atoi(arr[1]);
			msg->time	= g_strdup(arr[2]);
			msg->txt	= g_strdup(arr[3]);
			msg->from	= g_strdup(arr[4]);
			msg->to		= g_strdup(arr[5]);
			msg->lat	= atof(arr[6]);
			msg->lon	= atof(arr[7]);
			msg->incoming	= TRUE;


			add_message(msg);
			
			i++;
			
			g_strfreev(arr);
		}
	}
	else
	{
		gtk_label_set_label(GTK_LABEL(widget), g_strdup_printf("msg-code: %d",(int)postreply->status_code) );
	}
	
	
	
	
	
	

	

}

void
add_message(msg_t *m)
{
	GtkWidget *msg_box, *widget, *hseparator;
	msg_list = g_slist_append(msg_list, m);
	
	msg_box = create_msg_box(m);
	
	widget = lookup_widget(window1, "vbox48");
	gtk_box_pack_start (GTK_BOX (widget), msg_box, FALSE, FALSE, 0);
	
	hseparator = gtk_hseparator_new ();
	gtk_widget_show (hseparator);
	gtk_box_pack_start (GTK_BOX (widget), hseparator, FALSE, FALSE, 0);
	

}

GtkWidget*
create_msg_box(msg_t *m)
{
	GtkWidget *hbox, *label, *vbox, *button;
	char *label_txt;
	
	
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_widget_set_size_request(hbox, 340, -1);
	gtk_widget_show (hbox);
	
	label = gtk_label_new ("");
	gtk_widget_set_size_request(label, 260, -1);

	gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
	gtk_misc_set_padding (GTK_MISC (label), 5, 2);
	
	if(m->incoming)
		label_txt = g_strdup_printf("<i><b>%s</b>, %s</i>\n\n%s",m->from, m->time, m->txt);
	else
		label_txt = g_strdup_printf("<i><small>To: </small><b>%s</b></i>\n\n%s",m->to, m->txt);
	
	gtk_label_set_label(GTK_LABEL(label), label_txt);
	
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
	
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox);
	gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
	
	if(m->incoming)
	{
		button = gtk_button_new_with_mnemonic (_("  Reply  "));
		gtk_widget_show (button);
		gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 2);
		
		g_signal_connect ((gpointer) button, "clicked",
					G_CALLBACK (on_msg_friend_clicked),
					(gpointer) m->from);
					
		button = gtk_button_new_with_mnemonic (_("  Go To  "));
		gtk_widget_show (button);
		gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 2);
		
		g_signal_connect ((gpointer) button, "clicked",
					G_CALLBACK (on_goto_friend2_clicked),
					(gpointer) m);
	}
	
	return hbox;
}

void
on_goto_friend2_clicked(GtkButton *button, gpointer user_data)
{	
	msg_t *m;
	m = user_data;
	
	printf("btn42 clicked: %s\n", m->from);
	
	set_current_wp(deg2rad(m->lat), deg2rad(m->lon));
	
	set_mapcenter(m->lat,m->lon, global_zoom);

}
