

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <glib.h>

#include <stdio.h>
#include <unistd.h>

#ifdef HAVE_BLUEZ
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#endif /* HAVE_BLUEZ */

#include "hrm_functions.h"
#include "globals.h"
#include "support.h"

#define MAX_HEART_FREQ 160

static GIOChannel *hrm_io_channel = NULL;

static guint hrm_sid1,  hrm_sid3; 
guint watchdog;

void * get_hrm_data_thread(void *ptr);

gboolean
reset_hrm_io()
{
#ifdef HAVE_BLUEZ
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	g_free(hrmdata);
	hrmdata = NULL;
	
	global_reconnect_hrm = TRUE;
	g_source_remove(watchdog);

	g_source_remove(hrm_sid1); 
	g_source_remove(hrm_sid3); 
	
	osd_hrm(TRUE);
#endif /* HAVE_BLUEZ */
	
	return FALSE;	
}

void
osd_hrm(gboolean force_redraw)
{
#ifdef HAVE_BLUEZ
	PangoContext		*context = NULL;
	PangoLayout		*layout  = NULL;
	PangoFontDescription	*desc    = NULL;
	
	GdkColor color;
	GdkGC *gc;
	
	gchar *buffer;
	static int x = 10, y = 310;
	static int width = 0, height = 0;

	static int hrm_tmp = 0;
	int hrm;

	if(!hrm_on)
		return;


	if(mouse_dx == 0 && mouse_dy == 0) 
	{
		if(hrmdata) 
			buffer = g_strdup_printf("%u", hrmdata->freq);
		else
			buffer = g_strdup_printf("--");
		
		
		context = gtk_widget_get_pango_context (map_drawable);
		layout  = pango_layout_new (context);
		desc    = pango_font_description_new();
		
		pango_font_description_set_absolute_size (desc, 50 * PANGO_SCALE);
		pango_layout_set_font_description (layout, desc);
		pango_layout_set_text (layout, buffer, strlen(buffer));
	
	
		gc = gdk_gc_new (map_drawable->window);
	
		if(hrmdata) 
			color.red = (hrmdata->freq > MAX_HEART_FREQ) ? 0xffff : 0;
		else
			color.red = 0;
		color.green = 0;
		color.blue = 0;
		
		gdk_gc_set_rgb_fg_color (gc, &color);
		
		if(hrmdata)
			hrm = hrmdata->freq;
		else
			hrm = 0;
		
		if(hrm_tmp != hrm || force_redraw)
		{
			
			gdk_draw_drawable (
				map_drawable->window,
				map_drawable->style->fg_gc[GTK_WIDGET_STATE (map_drawable)],
				pixmap,
				0,300,
				0, 300,
				width+10,height+10);
		
			

				gdk_draw_layout(map_drawable->window,
						gc,
						x, y,
						layout);
			
			
			pango_layout_get_pixel_size(layout, &width, &height);
		}
	
		hrm_tmp = hrm;
		
		g_free(buffer);
		pango_font_description_free (desc);
		g_object_unref (layout);
		g_object_unref (gc);
	}
#endif /* HAVE_BLUEZ */
}

void
set_hrm_labels()
{
#ifdef HAVE_BLUEZ
	static GtkWidget *widget1=NULL, *widget2=NULL;
	static gchar buffer[128];
				
	if(!widget1) {
		widget1 = lookup_widget(window1, "label206");
		widget2 = lookup_widget(window1, "label207");
	}
	
	g_snprintf (buffer, 128, _("<b><big>%d</big></b> <small>bpm</small>"),
	            hrmdata->freq);
	gtk_label_set_label(GTK_LABEL(widget1), buffer);

	g_snprintf (buffer, 128, _("<b><big>%d/%d</big></b>"),
	            hrmdata->min, hrmdata->max);
	gtk_label_set_label(GTK_LABEL(widget2), buffer);
#endif /* HAVE_BLUEZ */
}


static gboolean
cb_hrm_io_error(GIOChannel *src, GIOCondition condition, gpointer data)
{
#ifdef HAVE_BLUEZ
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	g_free(hrmdata);
	hrmdata = NULL;
	g_source_remove(hrm_sid1); 
	g_source_remove(hrm_sid3); 
#endif /* HAVE_BLUEZ */
	
	return FALSE; 
}


static gboolean
cb_hrm_data(GIOChannel *src, GIOCondition condition, gpointer data)
{
#ifdef HAVE_BLUEZ
	static int hrm_status = 0;
	
	gsize bytes_read;
	GError *error = NULL;
	gchar buf[1024];
	GIOStatus status;

	status =  g_io_channel_read_chars(
				hrm_io_channel,
				(char *) buf, sizeof(buf),
				&bytes_read, &error);
				
	if(status == G_IO_STATUS_NORMAL)
	{

		
		if(hrm_status == 0)
		{
			if((bytes_read == 60) && (buf[0] == 2))
				hrmdata->freq = buf[12];
			
			if((bytes_read == 1) && (buf[0] == 2))
				hrm_status = 1;
		}
		else {
			if(bytes_read == 59)
				hrmdata->freq = buf[11];
			
			hrm_status = 0;
		}	
		
		
		g_source_remove(watchdog);
		watchdog = g_timeout_add_seconds_full(G_PRIORITY_DEFAULT_IDLE,60,reset_hrm_io,NULL,NULL);
	}
	else
	{
		if (error)
			printf("gio: %s \n", error->message);
			
	}
	
	
	if(hrmdata->freq < hrmdata->min && hrmdata->freq > 50)
		hrmdata->min = hrmdata->freq;
	if(hrmdata->freq > hrmdata->max && hrmdata->freq < 220)
		hrmdata->max = hrmdata->freq;
#endif /* HAVE_BLUEZ */

	return TRUE;
}



void 
get_hrm_data()
{
#ifdef HAVE_BLUEZ
	g_thread_create(&get_hrm_data_thread, NULL, FALSE, NULL);
#endif /* HAVE_BLUEZ */
}

void *
get_hrm_data_thread(void *ptr)
{
#ifdef HAVE_BLUEZ
	static int hrm_sock = 0;
	struct sockaddr_rc addr = {0};
	int conn, len;
	unsigned char buf[501];
	static int cnt = 0;
	GError *error = NULL;

	if(!hrm_on)
		return NULL;

	if(!global_hrm_bt_addr)
		return NULL;
	
	if(!hrmdata  || global_reconnect_hrm)
	{
		if(cnt++ % 15 != 0)
			return NULL;
		
		if (hrm_sock) hrm_sock = close(hrm_sock);

		hrm_sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
		if(hrm_sock < 0) {
			printf("error opening hrm socket\n");
			return NULL;
		}
		
		str2ba(global_hrm_bt_addr, &addr.rc_bdaddr);
		
		addr.rc_family = AF_BLUETOOTH;
		addr.rc_channel = 1;
    
		conn = connect(hrm_sock, (struct sockaddr *)&addr, sizeof(addr));
		if(conn < 0) {
			printf("error connecting %s\n", global_hrm_bt_addr);
			
			conn = 1;
			shutdown(hrm_sock, SHUT_RDWR);
		}
		else {
			printf("connection done %s\n", global_hrm_bt_addr);
			
			global_reconnect_hrm = FALSE;
			
			if(!hrmdata) {
				hrmdata = g_new0(hrm_data_t,1);
				hrmdata->min = 999;
			}

			len = read(hrm_sock, buf, 500);
			
			fprintf(stderr, "HRM Rcvd %u bytes", len);
			
			
			watchdog = g_timeout_add_seconds_full(G_PRIORITY_DEFAULT_IDLE,60,reset_hrm_io,NULL,NULL);
			
			hrm_io_channel = g_io_channel_unix_new(hrm_sock);
			g_io_channel_set_encoding(hrm_io_channel, NULL, &error);
			g_io_channel_set_flags(hrm_io_channel, G_IO_FLAG_NONBLOCK, NULL);
			
			hrm_sid1 = g_io_add_watch_full(hrm_io_channel, G_PRIORITY_HIGH_IDLE+200, G_IO_ERR | G_IO_HUP, cb_hrm_io_error, NULL, NULL);
			hrm_sid3 = g_io_add_watch_full(hrm_io_channel, G_PRIORITY_HIGH_IDLE+200, G_IO_IN | G_IO_PRI, cb_hrm_data, NULL, NULL);
		}
	}
	return NULL;
#endif /* HAVE_BLUEZ */
}
