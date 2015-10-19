

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>

#include <gdk/gdkkeysyms.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "globals.h"
#include "map_management.h"
#include "tile_management.h"
#include "converter.h"
#include "gps_functions.h"
#include "friends.h"
#include "init.h"
#include "geo_photos.h"
#include "poi.h"
#include "wp.h"
#include "tracks.h"
#include "route.h"
#include "hrm_functions.h"

/* How many move events must come in for a drag to be recognized: */
#define WTFCOUNTER 5


static int wtfcounter=0; 

static int	friendfinder_timer = 0;
static gboolean distance_mode = FALSE;
static gboolean pickpoint_mode = FALSE;
static int	pickpoint;
static int	msg_timer = 0;
static gboolean msg_pane_visible=TRUE;
static gboolean maximized = FALSE;


GtkWidget *dialog10 = NULL;


static int local_x = 0;
static int local_y = 0;


static	GdkPixmap *pixmap_photo = NULL;
static	GdkPixmap *pixmap_photo_big = NULL;

void do_distance();
void do_pickpoint();
void move_map(int i);

void
set_cursor(int type)
{
	static GdkCursor *cursor_cross = NULL;
	static GdkCursor *cursor_default = NULL;
	
	if(!cursor_cross)
	{
		cursor_cross = gdk_cursor_new(GDK_CROSSHAIR);
		cursor_default = gdk_cursor_new(GDK_LEFT_PTR);
	}

	if(type == GDK_CROSSHAIR)
		gdk_window_set_cursor(window1->window, cursor_cross);
	else
		gdk_window_set_cursor(window1->window, cursor_default);
}

waypoint_t *selected_wp;

gboolean
on_drawingarea1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	wtfcounter = 0;

	mouse_x = (int) event->x;
	mouse_y = (int) event->y;
	local_x = global_x;
	local_y = global_y;
		
	selected_wp = find_routepoint (mouse_x, mouse_y);
	
	return FALSE;
}

gboolean
on_drawingarea1_button_release_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {

		GtkWidget *range;

		if(global_zoom<global_zoom_max)
		{
			range = lookup_widget(window1, "vscale1");

			global_zoom++;
			gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);

			global_x = 2 * global_x + (int)event->x;
			global_y = 2 * global_y + (int)event->y;

			repaint_all();
		}
	}
	else {
		if(wtfcounter >= WTFCOUNTER)
		{
			/* This is the mouse release event
			   of a previous drag: */

			if (!selected_wp) {
				int mouse_dx, mouse_dy;

				global_x = local_x;
				global_y = local_y;

				mouse_dx = mouse_x - (int) event->x;
				mouse_dy = mouse_y - (int) event->y;

				global_x += mouse_dx;
				global_y += mouse_dy;

				gdk_draw_rectangle (
					pixmap,
					widget->style->white_gc,
					TRUE,
					0, 0,
					widget->allocation.width+260,
					widget->allocation.height+260);

				gtk_widget_queue_draw_area (
					widget, 
					0,0,widget->allocation.width+260,widget->allocation.height+260);


				repaint_all ();
			} else {
				selected_wp = NULL;
			}
		}
		
		if (abs(mouse_x - (int) event->x) < 10 && abs(mouse_y - (int) event->y) < 10)
		{
			GSList *list;
			gboolean friend_found = FALSE;
			gboolean photo_found = FALSE;
			gboolean poi_found = FALSE;
			waypoint_t *routepoint;
			
			
			if(global_show_friends)
			{
				for(list = friends_list; list != NULL && !friend_found; list = list->next)
				{
					friend_t *f = list->data;

					if( 	abs(f->screen_x - mouse_x) < 15 &&
						abs(f->screen_y - mouse_y) < 15)
					{
						
						friend_found = TRUE;
					}
				
				}
			}
			
			if(global_show_photos && !photo_found)
			{
				for(list = photo_list; list != NULL && !photo_found; list = list->next)
				{
					photo_t *p = list->data;
					
					if( 	abs(p->screen_x - mouse_x) < 15 &&
						abs(p->screen_y - mouse_y) < 15)
					{
						
						photo_found = TRUE;
					}
				
				}
			}
			
			if (global_show_pois )
			{	
				for(list = poi_list; list != NULL && !poi_found; list = list->next)
				{
					poi_t *p = list->data;
					
					if( 	abs(p->screen_x - mouse_x) < 15 &&
						abs(p->screen_y - mouse_y) < 15)
					{
						
						poi_found = TRUE;
					}
				
				}
			}
			
			routepoint = find_routepoint (mouse_x, mouse_y);
			
			if (!friend_found && !photo_found && !poi_found && !routepoint && 
				!distance_mode && !pickpoint_mode)
			{	
	
				gtk_widget_show(menu1);
				
				gtk_menu_popup (GTK_MENU(menu1), NULL, NULL, NULL, NULL, 
					  0, event->time);
				
			}
			
			if(distance_mode)
				do_distance();
			else if (pickpoint_mode)
				do_pickpoint();
			else
			{
				if (friend_found)
					on_item3_activate(NULL, NULL);
				if (photo_found)
					on_item10_activate(NULL, NULL);
				if (poi_found)
					on_item15_activate(NULL, NULL);
				if (routepoint) {
					gtk_widget_show (route_menu);
					gtk_menu_popup (GTK_MENU (route_menu),
					                NULL, NULL, NULL, NULL, 
					                event->button,
					                event->time);
				}
			}
		}
	
		wtfcounter = 0;
	
			
		mouse_dx = mouse_dy = 0;
		drag_started = 0;
	}
	return FALSE;
}

gboolean
on_drawingarea1_motion_notify_event    (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
	if(global_mapmode)
	{
		int x, y;
		GdkModifierType state;
		
		if (event->is_hint)
			gdk_window_get_pointer (event->window, &x, &y, &state);
		else
		{
			x = event->x;
			y = event->y;
			state = event->state;
		}
	 
		if (state & GDK_BUTTON1_MASK  && wtfcounter>=WTFCOUNTER) 
		{

			if (selected_wp) {
				double lat = pixel2lat (global_zoom, global_y+event->y);
				double lon = pixel2lon (global_zoom, global_x+event->x);
				change_waypoint_of_route (selected_wp, lat, lon);
				repaint_all ();
				return FALSE;
			}

			GtkToggleToolButton *autocenter_toggle;

			if(!drag_started)
			{
				mouse_x = (int) event->x;
				mouse_y = (int) event->y;
				local_x = global_x;
				local_y = global_y;

				drag_started = 1;				
			}
			global_autocenter = FALSE;
				
			mouse_dx = x - mouse_x;	
			mouse_dy = y - mouse_y;
				
			gdk_draw_drawable (
				widget->window,
				widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
				pixmap,
				0,0,
				mouse_dx,mouse_dy,
				-1,-1);
	
			if(mouse_dx>0)
				gdk_draw_rectangle (
					widget->window,
					widget->style->white_gc,
					TRUE,
					0, 0,
					mouse_dx,
					widget->allocation.height);
			
			if (mouse_dy>0)
				gdk_draw_rectangle (
					widget->window,
					widget->style->white_gc,
					TRUE,
					0, 0,
					widget->allocation.width,
					mouse_dy);
					
			autocenter_toggle =
				GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1,
				                                     "button3"));
			gtk_toggle_tool_button_set_active(autocenter_toggle,
			                                  FALSE);

			autocenter_toggle =
				GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1,
				                                     "button56"));
			gtk_toggle_tool_button_set_active(autocenter_toggle,
			                                  FALSE);

		}	
		else
			wtfcounter++;
	}
	
  return FALSE;
}


gboolean
on_drawingarea1_configure_event        (GtkWidget         *widget,
                                        GdkEventConfigure *event,
                                        gpointer           user_data)
{
	map_drawable = widget;
	
	global_drawingarea_width  = widget->allocation.width;
	global_drawingarea_height = widget->allocation.height;
	
	
	if (pixmap)
		g_object_unref (pixmap);

	pixmap = gdk_pixmap_new (
			widget->window,
			widget->allocation.width+260, 
			widget->allocation.height+260,
			-1);

	if (!pixmap)
	{
		printf("aieee: pixmap NULL\n");
	}

	gdk_draw_rectangle (
		pixmap,
		widget->style->white_gc,
		TRUE,
		0, 0,
		widget->allocation.width+260,
		widget->allocation.height+260);
				
	gtk_widget_queue_draw_area (
		widget, 
		0,0,widget->allocation.width+260,widget->allocation.height+260);

	repaint_all();	
	
	return FALSE;
}


gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	
	
	
	gdk_draw_drawable (
		widget->window,
		widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		pixmap,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
	
	osd_speed(TRUE);
	osd_hrm(TRUE);
	map_scale_indicator();
	
	return FALSE;
}

void
on_button1_clicked                     (GtkToggleToolButton *button,
                                        gpointer         user_data)
{
	maximized = gtk_toggle_tool_button_get_active (button);

	if(maximized)
	{
		gtk_window_fullscreen(GTK_WINDOW(window1));
		fill_tiles_pixel(global_x, global_y, global_zoom, FALSE);
	}
	else
	{
		gtk_window_unfullscreen(GTK_WINDOW(window1));
	}
}



void
on_vscale1_value_changed               (GtkRange        *range,
                                        gpointer         user_data)
{


}

void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *range;
	
	
	int zoom_old;
	double factor;
	int width_center, height_center;

	if(global_zoom<global_zoom_max)
	{	
		range = lookup_widget(window1, "vscale1");
		
		width_center  = map_drawable->allocation.width 	/ 2;
		height_center = map_drawable->allocation.height / 2;
				
		zoom_old = global_zoom;
	
		global_zoom++;
		gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
		factor = exp(global_zoom * M_LN2)/exp2(zoom_old);
		
		global_x = ((global_x + width_center) * factor) - width_center;
		global_y = ((global_y + height_center) * factor) - height_center;
		
		
		repaint_all();
	}
}


void
on_button3_clicked                     (GtkToggleToolButton *button,
                                        gpointer         user_data)
{
	global_autocenter = gtk_toggle_tool_button_get_active(button);

	if (!global_autocenter)
		return;

	if(gpsdata) {
		if(isnan(gpsdata->fix.latitude) == 0	&&
		   isnan(gpsdata->fix.longitude)== 0	&&
		   gpsdata->fix.latitude !=0		&&
		   gpsdata->fix.longitude!=0) {
			set_mapcenter(gpsdata->fix.latitude, gpsdata->fix.longitude, global_zoom);
		}
	}
}

gboolean
on_window1_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	track_log_close ();
	gtk_main_quit();
	
	return FALSE; 
}


gboolean
on_window1_destroy_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	track_log_close ();
	gtk_main_quit();

	return FALSE;
}


void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	int zoom_old;
	float factor;
	int width_center, height_center;
		GtkWidget *range;
	if(global_zoom>2)
	{
		range = lookup_widget(window1, "vscale1");
	
		width_center  = map_drawable->allocation.width 	/ 2;
		height_center = map_drawable->allocation.height / 2;
				
		zoom_old = global_zoom;
	
		global_zoom--;
		gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
	
		factor = exp(global_zoom * M_LN2)/exp(zoom_old * M_LN2);
		
		global_x = ((global_x + width_center) * factor) - width_center;
		global_y = ((global_y + height_center) * factor) - height_center;
		
		repaint_all();
	}
}

gboolean
on_vscale1_change_value                (GtkRange        *range,
                                        GtkScrollType    scroll,
                                        gdouble          value,
                                        gpointer         user_data)
{

  return FALSE;
}

gboolean
on_vscale1_button_press_event          (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_vscale1_button_release_event        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{	
	int zoom_old;
	float factor;
	int width_center, height_center;
	
	width_center  = map_drawable->allocation.width 	/ 2;
	height_center = map_drawable->allocation.height / 2;
		
	zoom_old = global_zoom;

	global_zoom = gtk_range_get_value(GTK_RANGE(widget));
	factor = exp(global_zoom * M_LN2)/exp(zoom_old * M_LN2);
	
	global_x = ((global_x + width_center) * factor) - width_center;
	global_y = ((global_y + height_center) * factor) - height_center;
	
	repaint_all();
	
	return FALSE;
}


void
on_combobox1_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GSList	*list;
	gchar *reponame_combo;
	static gboolean first_run = TRUE;

	reponame_combo = gtk_combo_box_get_active_text(combobox);

	global_curr_reponame = g_strdup(reponame_combo);
	if(!global_curr_reponame)
	{
		global_curr_reponame = g_strdup("OSM");
		printf("YOUR DISTRIBUTION SUCKS BIGTIME\n");
	}

	for(list = global_repo_list; list != NULL; list = list->next)
	{
		repo_t	*repo;
		gchar	*reponame;

		repo = list->data;
		reponame = g_strdup(repo->name);

		if(g_strrstr(reponame,global_curr_reponame) != NULL &&
			strlen(reponame) == strlen(global_curr_reponame))
		{
			global_curr_repo = list;
		}
	}

	gconf_client_set_string(
			global_gconfclient,
			GCONF"/repo_name",
			global_curr_reponame,
			NULL);

	global_repo_nr = gtk_combo_box_get_active(combobox);

	if (first_run)
		first_run = FALSE;
	else
		repaint_all();
}

void
on_dialog1_close                       (GtkDialog       *dialog,
                                        gpointer         user_data)
{
}


void
on_dialog1_response                    (GtkDialog       *dialog,
                                        gint             response_id,
                                        gpointer         user_data)
{
}


void
on_cancelbutton1_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(dialog1);
}


void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_repo;
	GtkWidget	*combobox;
	GtkWidget	*entry_uri;
	GtkWidget	*entry_dir;
	GtkWidget	*togglebutton;
	const gchar	*reponame, *uri, *dir;
	gboolean	reversed;
	repo_t *repo = g_new0(repo_t, 1);
	
	
	entry_repo = lookup_widget(dialog1, "entry5");
	entry_uri = lookup_widget(dialog1, "entry20");
	entry_dir = lookup_widget(dialog1, "entry21");
	togglebutton = lookup_widget(dialog1, "checkbutton12");
	combobox = lookup_widget(window1, "combobox1");

	reponame = gtk_entry_get_text(GTK_ENTRY(entry_repo));
	uri = gtk_entry_get_text(GTK_ENTRY(entry_uri));
	dir = gtk_entry_get_text(GTK_ENTRY(entry_dir));
	reversed = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton));
	
	gtk_combo_box_append_text (GTK_COMBO_BOX(combobox), g_strdup(reponame));
	gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), global_repo_cnt);
	global_repo_cnt++;
	

	repo->name = g_strdup(reponame);
	repo->dir = g_strdup(dir);
	repo->uri = g_strdup(uri);
	repo->inverted_zoom = reversed;
	
	global_repo_list = g_slist_prepend(global_repo_list, repo);
	global_curr_repo = global_repo_list;
	
	gconf_set_repolist();

	gtk_widget_hide(dialog1);
}


void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_repo;
	GtkWidget	*entry_uri;
	GtkWidget	*entry_dir;
	GtkWidget	*togglebutton;

	dialog1 = glade_xml_get_widget (gladexml, "dialog1");

	entry_repo = lookup_widget(dialog1, "entry5");
	entry_uri = lookup_widget(dialog1, "entry20");
	entry_dir = lookup_widget(dialog1, "entry21");
	togglebutton = lookup_widget(dialog1, "checkbutton12");

	gtk_entry_set_text(GTK_ENTRY(entry_repo), "");
	gtk_entry_set_text(GTK_ENTRY(entry_uri), "");
	gtk_entry_set_text(GTK_ENTRY(entry_dir), "");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(togglebutton), FALSE);

	gtk_widget_show(dialog1);
}

void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	trip_distance	= 0;
	trip_starttime	= 0;
	trip_time	= 0;
	trip_maxspeed	= 0;
}

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean	toggled;
	gboolean success = FALSE;
	GError **error = NULL;	
	
	toggled = gtk_toggle_button_get_active(togglebutton);
	global_auto_download = toggled;

	gconf_client_set_bool(
			global_gconfclient,
			GCONF"/auto_download",
			global_auto_download,
			error);
}


void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_server, *entry_port;
	const gchar	*server, *port;

	entry_server	= lookup_widget(window1, "entry3");
	entry_port	= lookup_widget(window1, "entry4");
	server	= gtk_entry_get_text(GTK_ENTRY(entry_server));
	port	= gtk_entry_get_text(GTK_ENTRY(entry_port));
	global_server	= g_strdup(server);
	global_port	= g_strdup(port);
	
	reset_gpsd_io ();
}



void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	GError **error = NULL;
	
	
	if(!global_fftimer_running)
	{
		update_position();
		send_message(NULL);
		friendfinder_timer = g_timeout_add_seconds(global_ffupdate_interval/1000,update_position,NULL);
		msg_timer	   = g_timeout_add_seconds(global_ffupdate_interval/1000,send_message,NULL);

		widget = lookup_widget(window1, "image24");
		gtk_widget_show(widget);
		
		gtk_button_set_label (button, _("Stop"));
		
		widget = lookup_widget(menu1, "item19");
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), TRUE);
		
		global_fftimer_running = TRUE;
	}
	
	
	
	else
	{
		widget = lookup_widget(window1, "image24");
		gtk_widget_hide(widget);
		
		g_source_remove(friendfinder_timer);
		g_source_remove(msg_timer);
		friendfinder_timer = 0;
		msg_timer =0;
		global_fftimer_running = FALSE;
		
		gtk_button_set_label (button, _("Share!"));
	}

	gconf_client_set_bool(
		global_gconfclient,
		GCONF"/fftimer_running",
		global_fftimer_running,
		error);

	global_show_friends = TRUE;
}


void
on_item3_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{	
	GSList *list;
	GladeXML *gladexml;
	GtkWidget *label, *window, *friend_box, *widget, *hseparator;
	gchar buffer[8192];
	gboolean friend_found = FALSE;
	float lat, lon;
	float distance=0;

	gladexml = glade_xml_new (gladefile, "window8", GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	window = glade_xml_get_widget (gladexml, "window8");
	g_signal_connect_swapped (window, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);

	widget = lookup_widget(window, "vbox35");
	gtk_widget_show (window);

	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	if(gpsdata !=NULL && !global_myposition.lat && !global_myposition.lon)
	{
		distance = 	6371.0 *  
				acos(sin(deg2rad(gpsdata->fix.latitude)) * 
				sin(lat) +
		
				cos(deg2rad(gpsdata->fix.latitude)) * 
				cos(lat) * 
				cos(lon - deg2rad(gpsdata->fix.longitude)) );
	}
	else if(global_myposition.lat && global_myposition.lon)
	{
		distance = 	6371.0 *  
				acos(sin(deg2rad(global_myposition.lat)) * 
				sin(lat) +
		
				cos(deg2rad(global_myposition.lat)) * 
				cos(lat) * 
				cos(lon - deg2rad(global_myposition.lon)) );
				
	}

	g_sprintf (buffer, _("<b><i>Distance:</i></b> %.3fkm\n"), distance);
	
	for(list = friends_list; list != NULL; list = list->next)
	{
		friend_t *f = list->data;

		if( 	abs(f->screen_x - mouse_x) < 15 &&
			abs(f->screen_y - mouse_y) < 15)
		{
			friend_box = create_friend_box(f);
			
			gtk_box_pack_start (GTK_BOX (widget), friend_box, FALSE, FALSE, 0);
			
			hseparator = gtk_hseparator_new ();
			gtk_widget_show (hseparator);
			gtk_box_pack_start (GTK_BOX (widget), hseparator, FALSE, FALSE, 0);
			
			friend_found = TRUE;
		}
	
	}
	
	if (!friend_found)
		g_sprintf (buffer, _("No friends at or near this position"));


	label = lookup_widget(window,"label119");
	gtk_label_set_label(GTK_LABEL(label),buffer);
}

void
on_item4_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *label;
	gchar buffer[512]; gchar *bufp;
	gchar latlon[64];
	static float start_lat=0, start_lon=0;
	static float overall_distance = 0;
	static int start_x=0, start_y=0;
	float lat, lon,lat_deg,lon_deg, bearing=0;
	float distance=0;
	double unit_conv = 1;
	static gchar distunit[3];

	if(!distance_mode)
		overall_distance = 0.0;

	set_cursor(GDK_CROSSHAIR);

	
	
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);

	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);

	switch (global_latlon_unit) 
	{
	case 0:
		g_sprintf(latlon, "%f - %f", lat_deg, lon_deg);
		break;
	case 1:
		g_sprintf(latlon, "%s   %s", 
			  latdeg2latmin(lat_deg),
			  londeg2lonmin(lon_deg));
		break;
	case 2:
		g_sprintf(latlon, "%s   %s", 
			  latdeg2latsec(lat_deg),
			  londeg2lonsec(lon_deg));
	}

	
	if(global_speed_unit==1)
	{
		unit_conv = 1.0/1.609344;
		g_sprintf(distunit, "%s", "m");
	}
	else if(global_speed_unit==2)
	{
		unit_conv = 1.0/1.852;
		g_sprintf(distunit, "%s", "NM");
	}
	else
	{
		g_sprintf(distunit, "%s", "km");
	}
	
	
	
	if(distance_mode)
	{
		distance = 	6371.0 *  
				acos(sin(deg2rad(start_lat)) * 
				sin(lat) +
		
				cos(deg2rad(start_lat)) * 
				cos(lat) * 
				cos(lon - deg2rad(start_lon)) );
		
		bearing = get_bearing(deg2rad(start_lat), deg2rad(start_lon), lat, lon);		
	}
	else if(gpsdata !=NULL && gpsdata->fix.latitude)
	{
		distance = 	6371.0 *  
				acos(sin(deg2rad(gpsdata->fix.latitude)) * 
				sin(lat) +
		
				cos(deg2rad(gpsdata->fix.latitude)) * 
				cos(lat) * 
				cos(lon - deg2rad(gpsdata->fix.longitude)) );
	}

	if(distance_mode)
		overall_distance += distance;
	
	
	gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), latlon, -1);
	
	
	
	label = lookup_widget(window2,"label64");

	bufp = buffer;
	bufp += g_sprintf (bufp, _("<b>This point:</b>\n%s\n"
	                           "<small><i>(coords auto-copied to clipboard)\n</i></small>\n"),
	                   latlon);

	if (gpsdata && gpsdata->fix.latitude)
	{
		bufp += g_sprintf (bufp, _("<b>Bearing:</b>\n%.1f°\n"),
		                   bearing/M_PI*180);

		if (!distance_mode)
		{
			bufp += g_sprintf (bufp, _("<b>Distance from your location:</b>\n%.2f%s\n"),
			                   distance*unit_conv,
			                   distunit);
		}
	}

	if (!distance_mode)
	{
		bufp += g_sprintf (bufp, _("Click another point for distance"));
	}
	else
	{
		bufp += g_sprintf (bufp, _("<b>Distance from last point:</b>\n%.2f%s\n"),
		                   distance*unit_conv, distunit);
		bufp += g_sprintf (bufp, _("<b>Overall Distance:</b>\n%.2f%s"),
		                   overall_distance*unit_conv, distunit);
	}
	
	gtk_label_set_label(GTK_LABEL(label),buffer);
	gtk_widget_show (window2);

	
	
	if(distance_mode)
	{
		
		int pixel_x, pixel_y, x, y;
		float lt, ln;
		
		
		GdkColor color;
		GdkGC *gc;
	
		gc = gdk_gc_new(pixmap);
		color.green = 0;
		color.blue = 50000;
		color.red = 0;
		gdk_gc_set_rgb_fg_color(gc, &color);
		gdk_gc_set_line_attributes(
		gc, 5, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);


		
		
		lt = deg2rad(start_lat);
		ln = deg2rad(start_lon);
		pixel_x = lon2pixel(global_zoom, ln);
		pixel_y = lat2pixel(global_zoom, lt);
		x = pixel_x - global_x;
		y = pixel_y - global_y;
		


		gdk_draw_line (pixmap, gc, x, y, mouse_x, mouse_y);

		gtk_widget_queue_draw_area (
			map_drawable, 
			((x > mouse_x) ? mouse_x : x) - 4, 
			((y > mouse_y) ? mouse_y : y) - 4,
			abs(mouse_x - x) + 8,
			abs(mouse_y - y) + 8);
	}
	else
	{
		
		
		GdkColor color;
		GdkGC *gc;
	
		gc = gdk_gc_new(pixmap);
		color.green = 20000;
		color.blue = 20000;
		color.red = 65000;
		gdk_gc_set_rgb_fg_color(gc, &color);
		gdk_gc_set_line_attributes(
		gc, 5, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);


		
		
		gdk_draw_arc (
			pixmap,
			
			gc,
			TRUE,			
			mouse_x-8, mouse_y-8,		
			16,16,			
			0,23040);		

		gtk_widget_queue_draw_area (
			map_drawable, 
			mouse_x - 8, 
			mouse_y - 8,
			mouse_x + 16,
			mouse_y + 16);
			
	}
	
	
	start_x = mouse_x;
	start_y = mouse_y;
	start_lat = lat_deg;
	start_lon = lon_deg;
	
	
	distance_mode = TRUE;

}



void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(GTK_WIDGET(button), "window2");
	gtk_widget_hide(window);
	
	distance_mode = FALSE;
	set_cursor(GDK_HAND2);
	repaint_all();
}

gboolean
on_item5_activate                      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	
	GtkWidget *label;
	gchar buffer[512];
	float lat, lon,lat_deg,lon_deg;

	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);
	
	global_myposition.lat = lat_deg;
	global_myposition.lon = lon_deg;

	label = lookup_widget(window2,"label64");

	g_sprintf (buffer, _("<b>Manually set position</b>\n\n"
	                     "This point:\n\n  <i>%f %f</i>\n\n"
	                     "will now be used as your location\n"
	                     "for the friend finder service."),
	           global_myposition.lat,
	           global_myposition.lon);

	gtk_label_set_label(GTK_LABEL(label),buffer);
	gtk_widget_show (window2);
	
	gconf_client_set_float(
		global_gconfclient, 
		GCONF"/myposition_lat",
		global_myposition.lat,
		NULL);

	gconf_client_set_float(
		global_gconfclient, 
		GCONF"/myposition_lon",
		global_myposition.lon,
		NULL);
		
	paint_myposition();
	
	return FALSE;
}

gboolean
on_drawinarea1_scroll_event            (GtkWidget       *widget,
                                        GdkEventScroll  *event,
                                        gpointer         user_data)
{
	if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {
		return TRUE;
	}
	else
	{
		GtkWidget *range;
		int zoom_old;
		static int slowpad = 0;

		if (event->direction == GDK_SCROLL_UP && slowpad % 2 ==0)
		{
			slowpad++;
						
			if(global_zoom<global_zoom_max)
			{	
				range = lookup_widget(window1, "vscale1");
				
				global_zoom++;
				gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
				
				
				global_x = 2 * global_x + (int)event->x;
				global_y = 2 * global_y + (int)event->y;
				
				
				repaint_all();
			}
		}
		else if (event->direction == GDK_SCROLL_DOWN && slowpad % 2 ==0)
		{
			slowpad++;

			if(global_zoom>2)
			{
				range = lookup_widget(window1, "vscale1");
			
				global_zoom--;
				gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
			
				global_x = global_x/2 - (int)event->x/2;
				global_y = global_y/2 - (int)event->y/2;
				
				repaint_all();
			}
		}
		else slowpad++;
			
		return TRUE;
	}


}

void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	trip_counter_on = (trip_counter_on) ? FALSE : TRUE;
	
	if(trip_counter_on)
		gtk_button_set_label (button, _("Stop"));
	else
		gtk_button_set_label (button, _("Resume"));
}

void
on_entry7_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *nick;
	const gchar *n;
	GError **error = NULL;

	nick  = lookup_widget(window1, "entry7");
	
	n = gtk_entry_get_text(GTK_ENTRY(nick));
		
	gconf_client_set_string(
			global_gconfclient, 
			GCONF"/nick",
			n,
			error);
}


void
on_entry8_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *pass;
	const gchar *p;

	pass  = lookup_widget(window1, "entry8");

	p = gtk_entry_get_text(GTK_ENTRY(pass));

	gconf_client_set_string(
			global_gconfclient,
			GCONF"/pass",
			p,
			NULL);

}

void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	register_nick();
}



void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	
	track_log_close();
	track_log_open();
	
}


void
on_button20_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog3, *entry;

	dialog3 = glade_xml_get_widget (gladexml, "dialog3");
	entry = lookup_widget(dialog3, "entry12");
	gtk_entry_set_text(GTK_ENTRY(entry), global_track_dir);
	
	gtk_widget_show(dialog3);
}

void
on_cancelbutton2_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*dialog3;

	dialog3 = lookup_widget(GTK_WIDGET(button), "dialog3");
	
	gtk_widget_hide(dialog3);
}


void
on_okbutton2_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog3;
	GtkEntry *entry;
	gint mkres;
	GError **error = NULL;
	int result;

	
	entry = (GtkEntry *)lookup_widget(GTK_WIDGET(button), "entry12");
	global_track_dir = g_strconcat(gtk_entry_get_text(entry),"/",NULL);

	result = strncmp(global_track_dir, "~", 1); 
	
	if(!result)
	{
		char *sub_home, *home_dir;
		
		strsep(&global_track_dir, "~");
		sub_home = g_strdup(strsep(&global_track_dir, "~"));
		home_dir = getenv("HOME");
		
		g_free(global_track_dir);
		global_track_dir = g_strconcat(home_dir, sub_home, NULL);
		
		g_free(sub_home);
	}

	mkres = g_mkdir_with_parents(global_track_dir,0700);
	if(mkres==-1) {
		perror("mkdir........");
	}

	gconf_client_set_string(
			global_gconfclient,
			GCONF"/track_dir",
			global_track_dir,
			error);

	dialog3 = lookup_widget(GTK_WIDGET(button), "dialog3");
	
	gtk_widget_hide(dialog3);
}



void
on_item6_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


gboolean
on_item7_activate                      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	global_myposition.lat = global_myposition.lon = 0;
	
	gconf_client_set_float(
		global_gconfclient, 
		GCONF"/myposition_lat",
		0,
		NULL);

	gconf_client_set_float(
		global_gconfclient, 
		GCONF"/myposition_lon",
		0,
		NULL);
	
	repaint_all();
	
	return FALSE;
}

void
on_item8_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *dialog4;
	
	dialog4 = glade_xml_get_widget (gladexml, "dialog4");
	gtk_widget_show(dialog4);
}

void
on_cancelbutton3_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*dialog;

	dialog = lookup_widget(GTK_WIDGET(button), "dialog4");
	gtk_widget_hide(dialog);
}


void
on_okbutton3_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*dialog;

	dialog = lookup_widget(GTK_WIDGET(button), "dialog4");
	cb_download_maps(dialog);
}


gboolean
on_drawingarea2_configure_event        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{
	if (!pixmap_photo)
	pixmap_photo = gdk_pixmap_new (
			widget->window,
			widget->allocation.width,
			widget->allocation.height,
			-1);

	if (!pixmap_photo)
	{
		printf("aieee: pixmap_photo NULL\n");
	}

	return FALSE;
}


gboolean
on_drawingarea2_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	gdk_draw_drawable (
		widget->window,
		widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		pixmap_photo,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
	
	
	return FALSE;
}



void
on_item10_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *label, *widget;
	GtkWidget *drawingarea2;
	
	static gulong hd1 = 0, hd2 = 0;

	GSList *list;
	gchar buffer[512];
	gchar *photo_file = NULL;
	gboolean photo_found = FALSE;

	GdkPixbuf *photo = NULL;
	GError	*error = NULL;
	GdkGC *gc;
	
	waypoint_t *wp = g_new0(waypoint_t,1);
	
	gtk_widget_show(window3);

	drawingarea2 = lookup_widget(window3,"drawingarea2");

	
	


	
	
	label = lookup_widget(window3,"label104");
	
	

	
	
	
	for(list = photo_list; list != NULL; list = list->next)
	{
		photo_t *p = list->data;
	
		if(abs(p->screen_x - mouse_x) < 15 &&
		   abs(p->screen_y - mouse_y) < 15 &&
		   !photo_found && !photo) 
		{
			g_sprintf(buffer, 
				"%s ",
				p->name);
			photo_found = TRUE;
			wp->lat = deg2rad(p->lat);
			wp->lon = deg2rad(p->lon);
			
			
			photo = gdk_pixbuf_new_from_file_at_size (
							p->filename, 240,-1,
							&error);
			if(!photo)
			{
				printf ("+++++++++++++ FOTO NOT FOUND +++++++++\n");
				g_sprintf (buffer, _("File not found"));
			}
			else
			{
				photo_file = p->filename;

				gc = gdk_gc_new(pixmap_photo);
				
				gdk_draw_rectangle (
					pixmap_photo,
					drawingarea2->style->white_gc,
					TRUE,
					0, 0,
					drawingarea2->allocation.width,
					drawingarea2->allocation.height);
				
				gdk_draw_pixbuf (
					pixmap_photo,
					gc,
					photo,
					0,0,
					0, 0,
					-1,-1,
					GDK_RGB_DITHER_NONE, 0, 0);
				
				gdk_draw_drawable (
					drawingarea2->window,
					drawingarea2->style->fg_gc[GTK_WIDGET_STATE (drawingarea2)],
					pixmap_photo,
					0,0,
					0,0,
					-1,-1);

				gtk_widget_queue_draw_area (
					drawingarea2, 
					0, 0,
					80,80);

			}


	
		}
	
	}
	
	if(!photo_found)
		g_sprintf (buffer, _("No Geo Photo found"));
	
	gtk_label_set_text(GTK_LABEL(label),buffer);

	widget = lookup_widget(window3, "button29");
	if(hd1) g_signal_handler_disconnect(G_OBJECT(widget), hd1);
	hd1 = g_signal_connect (	(gpointer) widget, "clicked",
				G_CALLBACK (on_button29_clicked),
				(gpointer) wp);
	
	widget = lookup_widget(window3, "button21");
	if(hd2) g_signal_handler_disconnect(G_OBJECT(widget), hd2);
	hd2 = g_signal_connect (	(gpointer) widget, "clicked",
				G_CALLBACK (on_button21_clicked),
				(gpointer) g_strdup(photo_file));
		
}


void
on_item11_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GladeXML *gladexml;
	GtkWidget *widget;
	GtkWidget *drawingarea;

	gchar buffer[512];
	gchar *photo_file = user_data;

	GdkPixbuf *photo = NULL;
	GError	*error = NULL;
	GdkGC *gc;

	gladexml = glade_xml_new (gladefile, "win13_biggeo", GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	widget = glade_xml_get_widget (gladexml, "win13_biggeo");
	g_signal_connect_swapped (widget, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);

	gtk_widget_show(widget);
	
	drawingarea = lookup_widget(widget, "drawingarea3");
	
	photo = gdk_pixbuf_new_from_file_at_size (
							photo_file, 640,-1,
							&error);
	if(!photo)
	{
		printf ("+++++++++++++ FOTO NOT FOUND: %s +++++++++\n", photo_file);
		g_sprintf (buffer, _("File not found"));
	}
	else
	{
		gc = gdk_gc_new(pixmap_photo);
		
		gdk_draw_rectangle (
			pixmap_photo,
			drawingarea->style->white_gc,
			TRUE,
			0, 0,
			drawingarea->allocation.width,
			drawingarea->allocation.height);
		
		gdk_draw_pixbuf (
			pixmap_photo,
			gc,
			photo,
			0,0,
			0, 0,
			-1,-1,
			GDK_RGB_DITHER_NONE, 0, 0);
		
		gdk_draw_drawable (
			drawingarea->window,
			drawingarea->style->fg_gc[GTK_WIDGET_STATE (drawingarea)],
			pixmap_photo,
			0,0,
			0,0,
			-1,-1);

		gtk_widget_queue_draw_area (
			drawingarea, 
			0, 0,
			80,80);

	}


	
	
	gtk_widget_hide(window3);printf("*** %s(): 44\n",__PRETTY_FUNCTION__);

}



gboolean
on_item12_activate                     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	show_window6();
	
	return FALSE;
}


gboolean
on_item14_activate                     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *dialog, *combobox;

	dialog = glade_xml_get_widget (gladexml, "dialog6");
	gtk_widget_show(dialog);
	
	combobox = lookup_widget(dialog, "combobox4");
	gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), 0);

	return FALSE;
}


void
on_cancelbutton4_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*dialog;

	dialog = lookup_widget(GTK_WIDGET(button), "window6");
	gtk_widget_destroy(dialog);
}


void
on_okbutton4_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog;
	dialog = lookup_widget(GTK_WIDGET(button), "window6");
	set_poi(dialog);
	

	global_show_pois = TRUE; 
	repaint_all();
}


void
on_cancelbutton5_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog;

	dialog = lookup_widget(GTK_WIDGET(button), "dialog6");
	gtk_widget_hide(dialog);

}


void
on_okbutton5_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog,*combobox,*widget;
	gboolean pois_shown;

	dialog = lookup_widget(GTK_WIDGET(button), "dialog6");
	
	combobox = lookup_widget(GTK_WIDGET(button), "combobox4");
	global_poi_cat = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox));

	gtk_widget_hide(dialog);
	
	widget = lookup_widget(menu1, "item20");
	pois_shown = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget));
	
	if(pois_shown)
		repaint_all();
	else
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), TRUE);
	
}

gboolean
on_dialog6_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_hide (widget);
  return TRUE;
}


void
on_combobox2_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	on_combobox_cat_changed(combobox);
}

void
on_item15_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	show_poi_detail();
}

void
on_button22_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(GTK_WIDGET(button), "window5");
	gtk_widget_destroy(window);
}



void
on_entry16_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	global_ffupdate_interval_minutes = atof(gtk_entry_get_text(GTK_ENTRY(editable)));
	global_ffupdate_interval = global_ffupdate_interval_minutes * 60000;
	
	if (global_ffupdate_interval < 30000)
		global_ffupdate_interval = 30000;

	if(global_fftimer_running)
	{
		if(friendfinder_timer) {
			g_source_remove(friendfinder_timer);
			friendfinder_timer = 0;
		}
		
		if(msg_timer) {
			g_source_remove(msg_timer);
			msg_timer = 0;
		}
		
		friendfinder_timer = g_timeout_add_seconds(global_ffupdate_interval/1000, update_position, NULL);
		msg_timer	   = g_timeout_add_seconds(global_ffupdate_interval/1000, send_message, NULL);
	}


	gconf_client_set_float(
			global_gconfclient,
			GCONF"/ffupdate_interval_minutes",
			global_ffupdate_interval_minutes,
			NULL);
}


void
on_radiobutton14_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_speed_unit = (gtk_toggle_button_get_active(togglebutton)) ? 0 : global_speed_unit;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/speed_unit",
			global_speed_unit,
			NULL);
}


void
on_radiobutton15_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_speed_unit = (gtk_toggle_button_get_active(togglebutton)) ? 1 : global_speed_unit;
	
	gconf_client_set_int(
			global_gconfclient,
			GCONF"/speed_unit",
			global_speed_unit,
			NULL);
}


void
on_radiobutton16_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_speed_unit = (gtk_toggle_button_get_active(togglebutton)) ? 2 : global_speed_unit;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/speed_unit",
			global_speed_unit,
			NULL);
}


void
on_radiobutton17_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_alt_unit = (gtk_toggle_button_get_active(togglebutton)) ? 0 : global_alt_unit;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/alt_unit",
			global_alt_unit,
			NULL);
}


void
on_radiobutton18_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_alt_unit = (gtk_toggle_button_get_active(togglebutton)) ? 1 : global_alt_unit;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/alt_unit",
			global_alt_unit,
			NULL);
}


void
on_radiobutton19_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_latlon_unit = (gtk_toggle_button_get_active(togglebutton)) ? 0 : global_latlon_unit;
	
	gconf_client_set_int(
			global_gconfclient,
			GCONF"/latlon_unit",
			global_latlon_unit,
			NULL);
}


void
on_radiobutton20_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_latlon_unit = (gtk_toggle_button_get_active(togglebutton)) ? 1 : global_latlon_unit;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/latlon_unit",
			global_latlon_unit,
			NULL);
}

void
on_radiobutton21_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_latlon_unit = (gtk_toggle_button_get_active(togglebutton)) ? 2 : global_latlon_unit;
	
	gconf_client_set_int(
			global_gconfclient,
			GCONF"/latlon_unit",
			global_latlon_unit,
			NULL);
}


gboolean
on_button11_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	return FALSE;
}



void
on_button26_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(GTK_WIDGET(button), "window8");
	gtk_widget_destroy(window);
}

gboolean
on_window2_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_hide_on_delete       (widget);
	distance_mode = FALSE;
	set_cursor(GDK_HAND2);
	repaint_all();
  return TRUE;
}

void
on_button27_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window;
	waypoint_t *wp;
	
	wp = user_data;
	set_current_wp(wp->lat, wp->lon);
	
	window = lookup_widget(GTK_WIDGET(button), "window5");
	gtk_widget_destroy(window);
}



gboolean
on_window3_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gtk_widget_hide_on_delete       (widget);
  return TRUE;
}

void
on_item19_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gboolean active;
	
	active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	global_show_friends = (active) ? TRUE : FALSE;
	
	
	if(global_show_friends && !global_fftimer_running) {
		GtkWidget *widget = NULL;
		
		widget = lookup_widget(window1, "button11");
		gtk_button_clicked(GTK_BUTTON(widget));
	}
	repaint_all();
}


void
on_item20_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gboolean active;

	active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	global_show_pois = (active) ? TRUE : FALSE;


	
	repaint_all();
}



void
on_item9_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gboolean active;

	active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	global_show_photos = (active) ? TRUE : FALSE;

	if (active && photo_list == NULL)
		get_photos();
	
	repaint_all();
}


void
repaint_all()
{
	


	fill_tiles_pixel(global_x, global_y, global_zoom, FALSE);
	paint_track();
	paint_loaded_track();
	paint_friends();
	paint_photos();
	paint_pois();
	paint_wp();
	paint_route();
	paint_myposition();
	
}

void
on_button29_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window;
	waypoint_t *wp;
	
	wp = user_data;
	set_current_wp(wp->lat, wp->lon);

	window = lookup_widget(GTK_WIDGET(button), "window3");
	gtk_widget_hide(window);
}

void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *entry14, *entry15;
	char buf[64];

	if(gpsdata && gpsdata->fix.latitude !=0)
	{
		entry14 = lookup_widget(GTK_WIDGET(button), "entry14");
		entry15 = lookup_widget(GTK_WIDGET(button), "entry15");
		
		g_sprintf(buf, "%f", gpsdata->fix.latitude);
		gtk_entry_set_text(GTK_ENTRY(entry14), buf);
		g_sprintf(buf, "%f", gpsdata->fix.longitude);
		gtk_entry_set_text(GTK_ENTRY(entry15), buf);
	}
	
}

void
on_button33_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GladeXML *gladexml;

	GtkWidget *widget;
	GtkTextBuffer *tbuffer;
	GtkWidget *window;

	poi_t *p;
	
	p = user_data;
	tbuffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_insert_at_cursor(tbuffer, "p->desc", -1);
	gtk_text_buffer_set_text(tbuffer, "p->desc", -1);
	
	
	
        
	gladexml = glade_xml_new (gladefile, "window10", GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	window = glade_xml_get_widget (gladexml, "window10");
	g_signal_connect_swapped (window, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);
	gtk_widget_show(window);
	
	
	
	widget = lookup_widget(window, "entry17");
	gtk_entry_set_text(GTK_ENTRY(widget), g_strdup_printf("%f",p->lat_deg));
	
	widget = lookup_widget(window, "entry18");
	gtk_entry_set_text(GTK_ENTRY(widget), g_strdup_printf("%f",p->lon_deg));

	widget = lookup_widget(window, "entry19");
	gtk_entry_set_text(GTK_ENTRY(widget), p->keywords);
	
	widget = lookup_widget(window, "textview2");
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(widget), tbuffer);
	gtk_text_buffer_set_text(tbuffer, p->desc, -1);

	widget = lookup_widget(window, "label126");
	
	if (p->idmd5==NULL)
		gtk_label_set_label (GTK_LABEL(widget),
		                     _("<span foreground='#ff0000'>"
		                       "POI has no ID -> see website for help!"
		                       "</span>"));
	else
		gtk_label_set_text(GTK_LABEL(widget), p->idmd5);

	
	widget = lookup_widget(GTK_WIDGET(button), "window5");
	gtk_widget_destroy(widget);
}

void
on_cancelbutton5a_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*dialog;

	dialog = lookup_widget(GTK_WIDGET(button), "window10");
	gtk_widget_destroy(dialog);
}



void
on_okbutton5a_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	widget = lookup_widget(GTK_WIDGET(button), "window10");
	update_poi(widget);
	
	

	
	repaint_all();
}

void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *entry17, *entry18;
	char buf[64];

	if(gpsdata && gpsdata->fix.latitude !=0)
	{
		entry17 = lookup_widget(GTK_WIDGET(button), "entry17");
		entry18 = lookup_widget(GTK_WIDGET(button), "entry18");
		
		g_sprintf(buf, "%f", gpsdata->fix.latitude);
		gtk_entry_set_text(GTK_ENTRY(entry17), buf);
		g_sprintf(buf, "%f", gpsdata->fix.longitude);
		gtk_entry_set_text(GTK_ENTRY(entry18), buf);
	}
	
}

gboolean
on_drawingarea1_key_press_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	if (event->keyval == GDK_Page_Up || event->keyval == GDK_KP_Up || event->keyval == GDK_i)
		on_button4_clicked(NULL, NULL);
	else if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK && event->keyval == GDK_p)
		geo_photos_open_dialog_photo_correlate();
	else if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK && event->keyval == GDK_t)
		tracks_open_tracks_dialog();
	else if(event->keyval == GDK_Page_Down || event->keyval == GDK_o)
		on_button5_clicked(NULL, NULL);
	else if(event->keyval == GDK_m)
		on_button76_clicked(NULL, NULL);
	else if(event->keyval == GDK_space || event->keyval == GDK_F11)
	{
		maximized = !maximized;
		gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1, "button1")), maximized);
		gtk_toggle_tool_button_set_active(GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1, "button53")), maximized);
	}
	else if(event->keyval == GDK_Right)
		move_map(1);
	else if(event->keyval == GDK_Down)
		move_map(2);
	else if(event->keyval == GDK_Left)
		move_map(3);
	else if(event->keyval == GDK_Up)
		move_map(4);
	else if(event->keyval == GDK_a)
	{
		global_autocenter = !global_autocenter;
		GtkToggleToolButton *autocenter_toggle;

		autocenter_toggle =
			GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1,
			                                     "button3"));
		gtk_toggle_tool_button_set_active(autocenter_toggle,
		                                  global_autocenter);

		autocenter_toggle =
			GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1,
			                                     "button56"));
		gtk_toggle_tool_button_set_active(autocenter_toggle,
		                                  global_autocenter);
	}
	else if(event->keyval == GDK_r)
		on_item23_button_release_event(NULL, NULL, NULL);
	else if(event->keyval == GDK_1)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
		repaint_all();
	}
	else if(event->keyval == GDK_2)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 1);
		repaint_all();
	}
	else if(event->keyval == GDK_3)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 2);
		repaint_all();
	}
	else if(event->keyval == GDK_4)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 3);
		repaint_all();
	}
	else if(event->keyval == GDK_5)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 4);
		repaint_all();
	}
	else if(event->keyval == GDK_6)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 5);
		repaint_all();
	}
	else if(event->keyval == GDK_7)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 6);
		repaint_all();
	}
	else if(event->keyval == GDK_8)
	{
		GtkWidget *widget;
		widget = lookup_widget(window1, "combobox1");
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 7);
		repaint_all();
	}

	return TRUE;
}

void
on_button34_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GladeXML *gladexml;
	GtkWidget *widget, *widget2;
	poi_t *p;

	p = user_data;
	gladexml = glade_xml_new (gladefile,
				  "dialog7",
				  GETTEXT_PACKAGE);
	glade_xml_signal_autoconnect (gladexml);
	widget = glade_xml_get_widget (gladexml, "dialog7");
	g_signal_connect_swapped (widget, "destroy",
				  G_CALLBACK (g_object_unref), gladexml);
	gtk_widget_show(widget);
	
	widget2 = lookup_widget(widget, "okbutton6");
	g_signal_connect (	(gpointer) widget2, "clicked",
				G_CALLBACK (on_okbutton6_clicked),
				(gpointer) p);
}


gboolean
on_dialog7_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	return FALSE;
}


void
on_cancelbutton6_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;

	widget = lookup_widget(GTK_WIDGET(button), "dialog7");
	gtk_widget_destroy(widget);
}


void
on_okbutton6_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	poi_t *p;

	p = user_data;
	
	gtk_widget_destroy(p->widget); 
	delete_poi(p);
	
	widget = lookup_widget(GTK_WIDGET(button), "dialog7");
	gtk_widget_destroy(widget);
}

void
on_button35_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	widget = lookup_widget(window1, "vbox48");
	
	if(msg_pane_visible)
	{	
		gtk_widget_hide(widget);
		msg_pane_visible = FALSE;
		gtk_button_set_label (button, _("Show Messages"));
	}
	else
	{
		gtk_widget_show(widget);
		msg_pane_visible = TRUE;
		gtk_button_set_label (button, _("Hide Messages"));
	}
}

void
on_entry3_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	const char *entry;
	
	widget = lookup_widget(window1, "entry3");
	entry = gtk_entry_get_text(GTK_ENTRY(widget));
	
	gconf_client_set_string(	global_gconfclient, 
					GCONF"/gpsd_host",
					entry,
					NULL);
}


void
on_entry4_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	const char *entry;
	
	widget = lookup_widget(window1, "entry4");
	entry = gtk_entry_get_text(GTK_ENTRY(widget));
	
	gconf_client_set_string(	global_gconfclient, 
					GCONF"/gpsd_port",
					entry,
					NULL);
}

void
on_button36_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	tracks_open_tracks_dialog();
}

gboolean
on_window12_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	GtkWidget *window, *vbox;

	window = lookup_widget(widget, "window12");
	gtk_widget_hide(window);

	vbox = lookup_widget(window, "vbox39");		
	gtk_container_foreach (GTK_CONTAINER (vbox),
			       (GtkCallback) gtk_widget_destroy,
			       NULL);

	return TRUE;
}

void
on_button37_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget, *vbox;

	widget = lookup_widget(GTK_WIDGET(button), "window12");
	gtk_widget_hide(widget);

	vbox = lookup_widget(widget, "vbox39");		
	gtk_container_foreach (GTK_CONTAINER (vbox),
			       (GtkCallback) gtk_widget_destroy,
			       NULL);
}

void
on_button38_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_repo;
	GtkWidget	*entry_uri;
	GtkWidget	*entry_dir;
	GtkWidget	*togglebutton;
	repo_t		*repo;
		
	dialog8 = glade_xml_get_widget (gladexml, "dialog8");
		
	entry_repo = lookup_widget(dialog8, "entry24");
	entry_uri = lookup_widget(dialog8, "entry25");
	entry_dir = lookup_widget(dialog8, "entry26");
	togglebutton = lookup_widget(dialog8, "checkbutton13");

	repo = global_curr_repo->data;
	gtk_entry_set_text( GTK_ENTRY(entry_repo), repo->name );
	gtk_entry_set_text( GTK_ENTRY(entry_uri), repo->uri );
	gtk_entry_set_text( GTK_ENTRY(entry_dir), repo->dir );
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(togglebutton), repo->inverted_zoom);


	
	gtk_widget_show(dialog8);
}


void
on_cancelbutton7_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(dialog8);
}


void
on_okbutton7_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_repo;
	GtkComboBox	*combobox;
	GtkWidget	*entry_uri;
	GtkWidget	*entry_dir;
	GtkWidget	*togglebutton;
	const gchar	*reponame, *uri, *dir;
	gboolean	reversed;
	repo_t 		*repo;
	
	repo = global_curr_repo->data;
	
	entry_repo = lookup_widget(dialog8, "entry24");
	entry_uri = lookup_widget(dialog8, "entry25");
	entry_dir = lookup_widget(dialog8, "entry26");
	togglebutton = lookup_widget(dialog8, "checkbutton13");
	combobox = GTK_COMBO_BOX(lookup_widget(window1, "combobox1"));

	reponame = gtk_entry_get_text(GTK_ENTRY(entry_repo));
	uri = gtk_entry_get_text(GTK_ENTRY(entry_uri));
	dir = gtk_entry_get_text(GTK_ENTRY(entry_dir));
	reversed = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton));
	
	repo->name = g_strdup(reponame);
	repo->dir = g_strdup(dir);
	repo->uri = g_strdup(uri);
	repo->inverted_zoom = reversed;
	
	global_curr_reponame = g_strdup(reponame);
	
	gtk_combo_box_remove_text(combobox, gtk_combo_box_get_active(combobox));
	gtk_combo_box_prepend_text (combobox, g_strdup(repo->name));
	gtk_combo_box_set_active(combobox, 0);

	gconf_set_repolist();

	gtk_widget_hide(dialog8);

}

void
on_entry5_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*widget;
	const char	*txt1, *txt2, *txt3;

	
	widget = lookup_widget(GTK_WIDGET(editable), "entry5");
	txt1 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry20");
	txt2 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry21");
	txt3 = gtk_entry_get_text(GTK_ENTRY(widget));

	
	widget = lookup_widget(GTK_WIDGET(editable), "okbutton1");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
}


void
on_entry20_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*widget;
	const char	*txt1, *txt2, *txt3;

	
	widget = lookup_widget(GTK_WIDGET(editable), "entry5");
	txt1 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry20");
	txt2 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry21");
	txt3 = gtk_entry_get_text(GTK_ENTRY(widget));

	
	widget = lookup_widget(GTK_WIDGET(editable), "okbutton1");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
}


void
on_entry21_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*widget;
	const char	*txt1, *txt2, *txt3;
	const gchar	*dir;
	int result;
	
	dir = gtk_entry_get_text(GTK_ENTRY(editable));

	result = strncmp(dir, "~", 1);
	if(!result)
		gtk_entry_set_text(GTK_ENTRY(editable), g_strdup(getenv("HOME")));


	
	widget = lookup_widget(GTK_WIDGET(editable), "entry5");
	txt1 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry20");
	txt2 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry21");
	txt3 = gtk_entry_get_text(GTK_ENTRY(widget));

	widget = lookup_widget(GTK_WIDGET(editable), "okbutton1");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
}


void
on_checkbutton12_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_entry24_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*widget;
	const char	*txt1, *txt2, *txt3;

	
	widget = lookup_widget(GTK_WIDGET(editable), "entry24");
	txt1 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry25");
	txt2 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry26");
	txt3 = gtk_entry_get_text(GTK_ENTRY(widget));

	
	widget = lookup_widget(GTK_WIDGET(editable), "okbutton7");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
}


void
on_entry25_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*widget;
	const char	*txt1, *txt2, *txt3;

	
	widget = lookup_widget(GTK_WIDGET(editable), "entry24");
	txt1 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry25");
	txt2 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry26");
	txt3 = gtk_entry_get_text(GTK_ENTRY(widget));

	
	widget = lookup_widget(GTK_WIDGET(editable), "okbutton7");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
}


void
on_entry26_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*widget;
	const char	*txt1, *txt2, *txt3;
	const gchar	*dir;
	int result;
	
	dir = gtk_entry_get_text(GTK_ENTRY(editable));

	result = strncmp(dir, "~", 1);
	if(!result)
		gtk_entry_set_text(GTK_ENTRY(editable), g_strdup(getenv("HOME")));


	
	widget = lookup_widget(GTK_WIDGET(editable), "entry24");
	txt1 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry25");
	txt2 = gtk_entry_get_text(GTK_ENTRY(widget));
	widget = lookup_widget(GTK_WIDGET(editable), "entry26");
	txt3 = gtk_entry_get_text(GTK_ENTRY(widget));

	widget = lookup_widget(GTK_WIDGET(editable), "okbutton7");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
}


void
on_checkbutton13_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}

void
on_entry21_activate                    (GtkEntry        *entry,
                                        gpointer         user_data)
{
}

gboolean
on_eventbox1_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	gdk_draw_rectangle (
		pixmap_photo,
		widget->style->white_gc,
		TRUE,
		0, 0,
		widget->allocation.width,
		widget->allocation.height);
					
	gtk_widget_queue_draw_area (
		widget, 
		0,0,widget->allocation.width,widget->allocation.height);
	
	gtk_widget_hide(window3);
	
	return FALSE;
}

gboolean
on_eventbox2_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *window;
	
	window = lookup_widget(widget, "win13_biggeo");
	
	gtk_widget_destroy(window);
	
  return FALSE;
}

gboolean
on_drawingarea3_configure_event        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{
	if (!pixmap_photo_big)
	pixmap_photo = gdk_pixmap_new (
			widget->window,
			widget->allocation.width,
			widget->allocation.height,
			-1);

	if (!pixmap_photo_big)
	{
		printf("aieee: pixmap_photo NULL\n");
	}

	return FALSE;
}


gboolean
on_drawingarea3_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	gdk_draw_drawable (
		widget->window,
		widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		pixmap_photo,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
	
	
	return FALSE;
}

gboolean
on_itemgeocode1_activate               (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	geo_photos_open_dialog_photo_correlate();
	return FALSE;
}

gboolean
on_itemgeocode1_expose_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	if (system ("command -v gpscorrelate > /dev/null") != 0) {
		gtk_widget_set_sensitive (widget, FALSE);
		gtk_widget_set_tooltip_text
			(widget, _("gpscorrelate is necessary for this feature "
                                   "but does not appear to be installed."));
	} else {
		gtk_widget_set_sensitive (widget, TRUE);
		gtk_widget_set_tooltip_text (widget, NULL);
	}

	return FALSE;
}



void
on_button39_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photos_geocode_track_select_dialog(button, user_data);
}


void
on_button40_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photos_geocode_dir_select_dialog(button, user_data);
}


void
on_cancelbutton8_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photo_cancel_dialog_photo_correlate();
}


void
on_okbutton8_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photo_close_dialog_photo_correlate();
}

void
on_button44_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photos_open_dialog_image_data();
}


void
on_button45_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget = lookup_widget(GTK_WIDGET(button), "dialog_image_data");
	geo_photo_dialog_image_data_next(widget, user_data, GEOPHOTO_PREV);
}


void
on_button46_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget = lookup_widget(GTK_WIDGET(button), "dialog_image_data");
	geo_photo_dialog_image_data_next(widget, user_data, GEOPHOTO_NEXT);
}

void
on_button47_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget = lookup_widget(GTK_WIDGET(button), "dialog_image_data");
	geo_photo_dialog_image_data_next(widget, user_data, GEOPHOTO_FIRST);
}


void
on_button48_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget = lookup_widget(GTK_WIDGET(button), "dialog_image_data");
	geo_photo_dialog_image_data_next(widget, user_data, GEOPHOTO_LAST);
}

void
on_okbutton9_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photo_close_dialog_image_data();
}


void
on_button49_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	geo_photo_cancel_dialog_image_data();
}


gboolean
on_eventbox3_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	
	
	return FALSE;
}

int
on_checkbutton14_expose_event (GtkWidget *togglebutton, gpointer user_data)
{
	if (system ("command -v jhead > /dev/null") != 0) {
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (togglebutton), FALSE);
		gtk_widget_set_sensitive (togglebutton, FALSE);
		gtk_widget_set_tooltip_text
			(togglebutton, _("jhead is necessary for this feature "
			                 "but does not appear to be installed."));
	} else {
		gtk_widget_set_sensitive (togglebutton, TRUE);
		gtk_widget_set_tooltip_text (togglebutton, NULL);
	}

	return FALSE;
}

void
on_checkbutton14_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	geo_photo_set_add_to_database(togglebutton);
}


void
on_combobox7_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	geo_photo_set_timezone(combobox);
}


gboolean
on_dialog_geocode_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	geo_photo_cancel_dialog_photo_correlate();
	return TRUE;
}


gboolean
on_dialog_image_data_delete_event      (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	geo_photo_close_dialog_image_data();

  return TRUE;
}

gboolean
on_eventbox4_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *window;
	window = lookup_widget(widget, "window2");
	gtk_widget_hide(window);
	distance_mode = FALSE;
	set_cursor(GDK_HAND2);
	repaint_all();
	
	return FALSE;
}

void
on_entry28_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	geo_photo_correction_entry_cb(editable);
}


void
on_button50_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window = lookup_widget(GTK_WIDGET(button), "dialog_image_data");
	geo_photo_dialog_image_data_next(window, user_data, GEOPHOTO_FULLSIZE);	
	gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
}

void
on_closebutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget = lookup_widget(GTK_WIDGET(button), "dialog_geocode_result");	
	gtk_widget_hide(widget);
}

void
on_radiobutton27_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_ff_mode = FUN_MODE;
}


void
on_radiobutton28_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_ff_mode = FRIEND_MODE;
}


void
on_radiobutton29_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_ff_mode = PRIVATE_MODE;
}


void
on_button51_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	set_cursor(GDK_CROSSHAIR);
	
	distance_mode = TRUE;
}


void
on_button52_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
do_distance()
{
	on_item4_activate(NULL, NULL);
}

gboolean
on_item17_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	float lat, lon;

	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	set_current_wp(lat, lon);
  return FALSE;
}

gboolean
on_add_wp_button_release_event (GtkWidget *widget,
                                GdkEventButton *event,
                                gpointer user_data)
{
	float lat, lon;

	lat = pixel2lat (global_zoom, global_y+mouse_y);
	lon = pixel2lon (global_zoom, global_x+mouse_x);

	append_waypoint_to_route (lat, lon);
	repaint_all ();

	return FALSE;
}

gboolean
on_clear_route_button_release_event (GtkWidget *widget,
                                     GdkEventButton *event,
                                     gpointer user_data)
{
	reset_route ();
	repaint_all ();
	return FALSE;
}

gboolean
on_save_route_gpx_button_release_event (GtkWidget *widget,
                                        GdkEventButton *event,
                                        gpointer user_data)
{
	char *filename;

	filename = choose_save_file ("Unnamed.gpx");
	save_route_as_gpx (filename);
	g_free (filename);
	return FALSE;
}

gboolean
on_load_route_button_release_event (GtkWidget *widget,
                                    GdkEventButton *event,
                                    gpointer user_data)
{
	char *filename;

	filename = choose_load_file ();
	load_route (filename);
	repaint_all ();
	g_free (filename);
	return FALSE;
}

gboolean
on_save_route_tomtom_button_release_event (GtkWidget *widget,
                                           GdkEventButton *event,
                                           gpointer user_data)
{
	char *filename;

	filename = choose_save_file ("Unnamed.itn");
	save_route_as_tomtom_itn (filename);
	g_free (filename);
	return FALSE;
}


gboolean
on_item18_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	global_wp_on = FALSE;
	repaint_all();
  return FALSE;
}




void
on_button57_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *combobox;
	
	combobox = lookup_widget(window1, "combobox1");

	if(global_repo_cnt-1 > global_repo_nr)
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), global_repo_nr+1);
	else
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), 0);
		
}


void
on_button58_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *combobox;
	
	combobox = lookup_widget(window1, "combobox1");

	if (global_repo_nr > 0)
	{
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), global_repo_nr-1);
	}
	else
		gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), global_repo_cnt-1);
}

void
on_entry30_activate                    (GtkEntry        *entry,
                                        gpointer         user_data)
{
	GtkWidget *widget;

	widget = lookup_widget(GTK_WIDGET(entry), "okbutton10");
	gtk_button_clicked(GTK_BUTTON(widget));
}


void
on_cancelbutton9_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
			
	widget = lookup_widget(GTK_WIDGET(button), "dialog9");
	gtk_widget_destroy(widget);
}

gboolean
on_eventbox5_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	if(global_new_msg) 
	{
		GtkWidget *widget;
		
		if(!global_infopane_visible)
		{
			widget = lookup_widget(window1, "button76");
			g_signal_emit_by_name (widget, "clicked");
		}
		
		gtk_widget_hide(global_infopane_current->data);
	
		gtk_widget_show(g_list_nth_data(global_infopane_widgets, FRIENDS_PAGE));
		global_infopane_current = g_list_nth(global_infopane_widgets, FRIENDS_PAGE);
		
		widget = lookup_widget(window1, "button35");
		
		if(!msg_pane_visible)
			gtk_button_clicked(GTK_BUTTON(widget));
		
		global_new_msg = FALSE;
	}
	return FALSE;
}


gboolean
on_item23_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	GtkWidget *label, *button, *entry, *cbox;
	
	if (!dialog10)
		dialog10 = glade_xml_get_widget (gladexml, "dialog10");

	gtk_widget_show(dialog10);
	
	label = lookup_widget(dialog10, "label190");
	gtk_label_set_label(GTK_LABEL(label),"");

	entry = lookup_widget(dialog10, "entry31");
	gtk_entry_set_text(GTK_ENTRY(entry),"");
	entry = lookup_widget(dialog10, "entry32");
	gtk_entry_set_text(GTK_ENTRY(entry),"");	
	
	button = lookup_widget(dialog10, "okbutton11");
	gtk_widget_set_sensitive(button, TRUE);
	
	cbox = lookup_widget(GTK_WIDGET(button), "combobox8");
	gtk_combo_box_set_active(GTK_COMBO_BOX(cbox), 0);	
	
	if (gpsdata && gpsdata->fix.latitude !=0)
	{
		button = lookup_widget(dialog10, "button61");
		gtk_widget_set_sensitive(button, TRUE);
	}

	return FALSE;
}


void
on_button59_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	
	widget = lookup_widget(GTK_WIDGET(button), "dialog10");
	
	gtk_widget_hide(widget);
	
	pickpoint_mode = TRUE;
	pickpoint = 1;
}


void
on_button60_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{		
	gtk_widget_hide(dialog10);
	
	pickpoint_mode = TRUE;
	pickpoint = 2;
}


void
on_button61_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget = NULL;
	
	widget = lookup_widget(dialog10, "entry31");
	
	gtk_entry_set_text(GTK_ENTRY(widget), 
		g_strdup_printf("%f,%f",gpsdata->fix.latitude,gpsdata->fix.longitude));
}


void
on_cancelbutton10_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	
	widget = lookup_widget(GTK_WIDGET(button), "dialog10");
	gtk_widget_hide(widget);
}


void
on_okbutton11_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	char *start=NULL, *end=NULL;
	char *service=NULL;
	
	gtk_widget_set_sensitive(GTK_WIDGET(button),FALSE);
	
	widget = lookup_widget(GTK_WIDGET(button), "label190");
	
	gtk_label_set_label (GTK_LABEL(widget),
	                     _("<b><i>Connecting...</i></b>"));
	
	widget = lookup_widget(GTK_WIDGET(button), "entry31");
	start = g_strdup( gtk_entry_get_text(GTK_ENTRY(widget)) );
	
	widget = lookup_widget(GTK_WIDGET(button), "entry32");
	end   = g_strdup( gtk_entry_get_text(GTK_ENTRY(widget)) );
	
	widget = lookup_widget(GTK_WIDGET(button), "combobox8");
	service = g_strdup (gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget)));
	
	fetch_track (dialog10, service, start, end);
}

void
do_pickpoint()
{
	GtkWidget *widget = NULL;
	float lat=0, lon=0;

	lat = rad2deg( pixel2lat(global_zoom, global_y+mouse_y) );
	lon = rad2deg( pixel2lon(global_zoom, global_x+mouse_x) );
	
	if (pickpoint == 1)
		widget = lookup_widget(dialog10, "entry31");
	if (pickpoint == 2)
		widget = lookup_widget(dialog10, "entry32");
	
	gtk_entry_set_text(GTK_ENTRY(widget), g_strdup_printf("%f,%f",lat,lon));
	
	if (pickpoint == 2)
		gtk_widget_grab_focus(widget);
	
	gtk_widget_show(dialog10);

	pickpoint_mode = FALSE;
}

gboolean
on_dialog10_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	
	gtk_widget_hide_on_delete(widget);
	return TRUE;
}

void
on_entry32_activate                    (GtkEntry        *entry,
                                        gpointer         user_data)
{
	GtkWidget *widget;

	widget = lookup_widget(dialog10, "okbutton11");
	gtk_button_clicked(GTK_BUTTON(widget));
}

void
on_combobox8_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	
	
	
}


void
on_button76_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	

	GtkWidget *widget, *widget1, *draw_widget, *toolbar;

	widget  = lookup_widget(window1, "vbox53");  
	widget1 = lookup_widget(window1, "hbox52");

	if(!global_infopane_visible)
	{
		if(window1->allocation.width <= 480)
		{
			gtk_widget_hide(widget1);
			gtk_widget_set_size_request(widget, window1->allocation.width, -1);
		}
		else
			gtk_widget_set_size_request(widget, 360, -1);
		
		gtk_widget_show(widget);
		
		if(!global_landscape) {
			toolbar = lookup_widget(window1, "toolbar1");
			gtk_widget_hide(toolbar);
		}
		
		if(!global_infopane_current) {
			gtk_widget_show((GtkWidget *) global_infopane_widgets->data);
			global_infopane_current = global_infopane_widgets;
		}

		global_infopane_visible = TRUE;
	}
	else {
		draw_widget = lookup_widget(window1, "drawingarea1");
		
		gtk_widget_hide(widget);
		gtk_widget_show(widget1);
		gtk_widget_grab_focus(draw_widget);

		if(!global_landscape) {
			toolbar = lookup_widget(window1, "toolbar1");
			gtk_widget_show(toolbar);
		}
		
		global_infopane_visible = FALSE;		
	}
}


void
on_button69_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(global_infopane_current->data);
	
	if(global_infopane_current->prev) {
		gtk_widget_show(global_infopane_current->prev->data);
		global_infopane_current = global_infopane_current->prev;
	}
	else {
		gtk_widget_show(g_list_last(global_infopane_widgets)->data);
		global_infopane_current = g_list_last(global_infopane_widgets);
	}

}




void
on_button70_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

	gtk_widget_hide(global_infopane_current->data);
	
	if(global_infopane_current->next) {
		gtk_widget_show(global_infopane_current->next->data);
		global_infopane_current = global_infopane_current->next;
	}
	else {
		gtk_widget_show(global_infopane_widgets->data);
		global_infopane_current = global_infopane_widgets;
	}
		
}

void
on_checkbutton15_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget *widget = NULL;
	gboolean active;
	
	active = gtk_toggle_button_get_active(togglebutton);

	widget = lookup_widget(window1, "entry8");
	gtk_entry_set_visibility (GTK_ENTRY (widget), active);

}

void
move_map(int i)
{
	GtkWidget *widget = NULL;
	GtkToggleToolButton *autocenter_toggle;

	widget = lookup_widget(window1, "drawingarea1");
	
	if(i == 1)
		global_x += 80;
	else if(i == 3)
		global_x -= 80;
	else if(i == 2)
		global_y += 80;
	else if(i == 4)
		global_y -= 80;

		
	gdk_draw_rectangle (
		pixmap,
		widget->style->white_gc,
		TRUE,
		0, 0,
		widget->allocation.width+260,
		widget->allocation.height+260);
				
	gtk_widget_queue_draw_area (
		widget, 
		0,0,widget->allocation.width+260,widget->allocation.height+260);

	autocenter_toggle =
		GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1, "button3"));
	gtk_toggle_tool_button_set_active(autocenter_toggle, FALSE);

	autocenter_toggle =
		GTK_TOGGLE_TOOL_BUTTON(lookup_widget(window1, "button56"));
	gtk_toggle_tool_button_set_active(autocenter_toggle, FALSE);

	repaint_all();
}

void
on_button78_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_checkbutton16_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	trip_livelog_on = gtk_toggle_button_get_active(togglebutton);
}

void
tracklog_toolbutton_toggled (GtkToggleToolButton *button, gpointer data)
{
	GtkToggleButton *main_toggle =
		GTK_TOGGLE_BUTTON (lookup_widget (window1, "checkbutton17"));

	trip_logger_on = gtk_toggle_tool_button_get_active (button);

	gtk_toggle_button_set_active (main_toggle, trip_logger_on);
}

void
on_checkbutton17_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkToggleToolButton *toolbar_toggle =
		GTK_TOGGLE_TOOL_BUTTON (lookup_widget (window1, "button62"));

	trip_logger_on = gtk_toggle_button_get_active(togglebutton);

	gtk_toggle_tool_button_set_active (toolbar_toggle, trip_logger_on);

	if(trip_logger_on)
	{
		track_log_open();
		gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/tracklog_on",
				TRUE, NULL);
	}
	else
	{
		track_log_close();
		gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/tracklog_on",
				FALSE, NULL);
	}
}


void
on_button79_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{	
	GtkWidget *widget;
	
	reset_loaded_track();
	gtk_widget_hide(GTK_WIDGET(button));
	
	widget = lookup_widget(window1, "button78");
	gtk_widget_hide(widget);
	
	widget = lookup_widget(window1, "label203");
	gtk_label_set_label(GTK_LABEL(widget), "");
	
	repaint_all();
}

void
on_entry29_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	const char *me_msg;

	me_msg = gtk_entry_get_text(GTK_ENTRY(editable));
	gconf_client_set_string(global_gconfclient, GCONF"/me_msg", me_msg, NULL);
}

void
on_checkbutton18_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	
	hrm_on = gtk_toggle_button_get_active(togglebutton);
	
	gconf_client_set_bool(	global_gconfclient, 
				GCONF"/hrm_on",
				hrm_on, NULL);

	global_reconnect_hrm = TRUE;
	
	widget = lookup_widget(window1, "label205");
	(hrm_on) ? gtk_widget_show(widget) : gtk_widget_hide(widget);

	widget = lookup_widget(window1, "label206");
	(hrm_on) ? gtk_widget_show(widget) : gtk_widget_hide(widget);

	widget = lookup_widget(window1, "label207");
	(hrm_on) ? gtk_widget_show(widget) : gtk_widget_hide(widget);
}


void
on_entry33_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	const char *entry;
	
	entry = gtk_entry_get_text(GTK_ENTRY(editable));
	
	gconf_client_set_string(global_gconfclient, 
				GCONF"/hrm_bt_addr",
				entry, NULL);
	
	global_hrm_bt_addr = g_strdup(entry);
	global_reconnect_hrm = TRUE;
}

void
set_map_detail_menuitem_sensitivity (GtkMenuItem *zoomout, GtkMenuItem *menu)
{
	gtk_widget_set_sensitive (GTK_WIDGET (zoomout),
				  global_detail_zoom != 0);
}

void
activate_more_map_details (GtkMenuItem *menu_item, gpointer user_data)
{
	if (global_detail_zoom > 0)
		global_detail_zoom--;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/global_detail_zoom",
			global_detail_zoom,
			NULL);

	repaint_all ();
}

void
activate_larger_map_details (GtkMenuItem *larger_item, GtkMenuItem *more_item)
{
	global_detail_zoom++;

	gconf_client_set_int(
			global_gconfclient,
			GCONF"/global_detail_zoom",
			global_detail_zoom,
			NULL);

	repaint_all ();
}


void
toggle_tile_redownload (GtkToggleButton *togglebutton, gpointer data)
{
	global_no_redownload = !gtk_toggle_button_get_active (togglebutton);

	gconf_client_set_bool (global_gconfclient, 
	                       GCONF"/no_redownload",
	                       global_no_redownload, NULL);
}

gboolean
on_delete_waypoint_button_release_event (GtkWidget *widget,
                                         GdkEventButton *event,
                                         gpointer user_data)
{
	delete_waypoint_of_route (selected_wp);
	selected_wp = NULL;
	repaint_all ();

	return FALSE;
}

gboolean
on_insert_waypoint_button_release_event (GtkWidget *widget,
                                         GdkEventButton *event,
                                         gpointer user_data)
{
	insert_waypoint_before_of_route (selected_wp);
	selected_wp = NULL;
	repaint_all ();

	return FALSE;
}

void
on_help_menuitem_activate (GtkMenuItem *help_menuitem, gpointer user_data)
{
	system ("xdg-open " PACKAGE_HTML_DIR "/" PACKAGE ".html");
}
