

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

#define WTFCOUNTER 5


static int wtfcounter=0; 

static int friendfinder_timer = 0;
static gboolean distance_mode = FALSE;


static int local_x = 0;
static int local_y = 0;


static int drag_started = 0;

static	GdkPixmap *pixmap_photo = NULL;
static	GdkPixmap *pixmap_photo_big = NULL;

void do_distance();

void
set_cursor(int type)
{
	printf("setting cursor to %d\n", type);
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


void
print_track()
{	
	GSList *list;
	int pixel_x, pixel_y, x,y, last_x = 0, last_y = 0;
	float lat, lon;
	GdkColor color;
	GdkGC *gc;
	gboolean is_line = FALSE;
	
	gc = gdk_gc_new(pixmap);
	color.green = 0;
	color.blue = 0;
	color.red = 60000;
	gdk_gc_set_rgb_fg_color(gc, &color);
	gdk_gc_set_line_attributes(gc,
		5, GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);

	
			
		
		
		
	

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	for(list = trackpoint_list; list != NULL; list = list->next)
	{
		trackpoint_t *tp = list->data;
	
		lat = tp->lat;
		lon = tp->lon;
		
		
		
		
		pixel_x = lon2pixel(global_zoom, lon);
		pixel_y = lat2pixel(global_zoom, lat);
		
		x = pixel_x - global_x;
		y = pixel_y - global_y;
		
		


		if(is_line)
		{
			gdk_draw_line (pixmap, gc, x, y, last_x, last_y);
			gtk_widget_queue_draw_area (
				map_drawable, 
				x-4, y-4,
				8,8);
		}
		
		last_x = x;
		last_y = y;
		
		
		is_line = TRUE;
	}
	
	
	
	
	
	if(	
		gpsdata && 
		gpsdata->fix.longitude !=0 &&  
		gpsdata->fix.latitude != 0 &&
		last_x != 0 &&
		last_y != 0
		)
	{
		pixel_x = lon2pixel(global_zoom, deg2rad(gpsdata->fix.longitude));
		pixel_y = lat2pixel(global_zoom, deg2rad(gpsdata->fix.latitude));
			
		x = pixel_x - global_x;
		y = pixel_y - global_y;

	
		gdk_draw_line (pixmap, gc, x, y, last_x, last_y);
printf("LINE x y lx ly: %d %d %d %d\n",x,y,last_x,last_y);	
			gtk_widget_queue_draw_area (
			map_drawable, 
			x-4, y-4,
			8,8);
	}
	
}

gboolean
on_drawingarea1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	
	wtfcounter = 0;
	if ( event->type==GDK_2BUTTON_PRESS) 
	{
		printf("double click\n");
		
		
		
			
	}
	
	mouse_x = (int) event->x;
	mouse_y = (int) event->y;
	local_x = global_x;
	local_y = global_y;

	
	
		
		
  return FALSE;
}

gboolean
on_drawingarea1_button_release_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {
		printf("CONTROL WAS PRESSED\n");
		GtkWidget *range;
		int zoom_old;
		double factor;
		int width_center, height_center;
			

			
		if(global_zoom<global_zoom_max)
		{	
			range = lookup_widget(window1, "vscale1");
			
			width_center  = map_drawable->allocation.width 	/ 2;
			height_center = map_drawable->allocation.height / 2;
			
			printf("x vorher: %d, %f, %f\n",global_x,event->x,event->y);
			
			zoom_old = global_zoom;
		
			global_zoom++;
			gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
			
			
			
			factor = 2;
			
			
			global_x = 2 * global_x + (int)event->x;
			global_y = 2 * global_y + (int)event->y;
			
			
			repaint_all();
		}
	}
	else {
		
		if ( event->type==GDK_2BUTTON_PRESS) 
		{	
			printf("end double click\n");
		}
		
		if(wtfcounter >= WTFCOUNTER)
		{
			printf("* mouse drag +8events\n");
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
			
		
			repaint_all();
			
		}
		
		if (abs(mouse_x - (int) event->x) < 10 && abs(mouse_y - (int) event->y) < 10)
		{
			GSList *list;
			gboolean friend_found = FALSE;
			gboolean photo_found = FALSE;
			gboolean poi_found = FALSE;
			
			
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
			
			
			if (!friend_found && !photo_found && !poi_found && !distance_mode)
			{	
	
				gtk_widget_show(menu1);
				
				gtk_menu_popup (GTK_MENU(menu1), NULL, NULL, NULL, NULL, 
					  event->button, event->time);
				
			}
			
			if(distance_mode)
				do_distance();
			else
			{
				if (friend_found)
					on_item3_activate(NULL, NULL);
				if (photo_found)
					on_item10_activate(NULL, NULL);
				if (poi_found)
					on_item15_activate(NULL, NULL);
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
		

		int x, y, width, height;
		GdkModifierType state;
		
		width  = map_drawable->allocation.width;
		height = map_drawable->allocation.height;
		
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
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
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


if(pixmap) printf("pixmap created\n");
else printf("aieee: pixmap NULL\n");

	
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


	
	
	fill_tiles_pixel(global_x, global_y, global_zoom);
	
return FALSE;
}


gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	
	printf("** expose event %d %d %d %d\n", event->area.x, event->area.y, event->area.width, event->area.height);
	
	gdk_draw_drawable (
		widget->window,
		widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		pixmap,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
	
	osd_speed(TRUE);
	map_scale_indicator();
	
	return FALSE;
}

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *notebook;
	static int maximized = FALSE;
	
	printf("button1 clicked\n");
	notebook = lookup_widget(GTK_WIDGET(button), "notebook1");
	
	if(!maximized)
	{
		
			
		gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), FALSE);
		gtk_window_fullscreen(GTK_WINDOW(window1));
		fill_tiles_pixel(global_x, global_y, global_zoom);

		maximized = TRUE;
	}
	else
	{
		gtk_window_unfullscreen(GTK_WINDOW(window1));
		gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), TRUE);
		
		

		maximized = FALSE;
	}
	
}

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	float lat, lon;
	printf("button2 clicked\n");
	
	lat = deg2rad(51.52468);
	lon = deg2rad(-0.13762);
	fill_tiles_latlon(lat, lon, 15);
}



void
on_vscale1_value_changed               (GtkRange        *range,
                                        gpointer         user_data)
{
#if 0
	int zoom_old;
	float factor;
	int width_center, height_center;
	
	width_center  = map_drawable->allocation.width 	/ 2;
	height_center = map_drawable->allocation.height / 2;
	
	printf("x vorher: %d",global_x);
	
	zoom_old = global_zoom;

	global_zoom = gtk_range_get_value(range);
	factor = exp2(global_zoom)/exp2(zoom_old);

	
	
	
	
	global_x = ((global_x + width_center) * factor) - width_center;
	global_y = ((global_y + height_center) * factor) - height_center;
	
	
	fill_tiles_pixel(global_x, global_y, global_zoom);

	
	printf("zoom changed from %d to %d factor: %f x: %d\n",
	zoom_old,global_zoom, factor, global_x);
#endif
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
		
		printf("x vorher: %d",global_x);
		
		zoom_old = global_zoom;
	
		global_zoom++;
		gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
		factor = exp(global_zoom * M_LN2)/exp(zoom_old * M_LN2);
	
		
		
		
		
		global_x = ((global_x + width_center) * factor) - width_center;
		global_y = ((global_y + height_center) * factor) - height_center;
		
		
		repaint_all();
		
		
		printf("zoom changed from %d to %d factor: %f x: %d\n",
		zoom_old,global_zoom, factor, global_x);
	

	}
}


void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	global_autocenter = TRUE;
	
	if(gpsdata) {
		if(isnan(gpsdata->fix.latitude) == 0	&&
		   isnan(gpsdata->fix.longitude)== 0	&&
		   gpsdata->fix.latitude !=0		&&
		   gpsdata->fix.longitude!=0) {
			set_mapcenter(gpsdata->fix.latitude, gpsdata->fix.longitude, global_zoom);
		}
	}
	else
		printf("Not autocentering map due to missing gps data\n");
}

gboolean
on_window1_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	printf("%s()\n",__PRETTY_FUNCTION__);
	gtk_main_quit();
	
	return FALSE; 
}


gboolean
on_window1_destroy_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	printf("%s()\n",__PRETTY_FUNCTION__);
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
		
		printf("x vorher: %d",global_x);
		
		zoom_old = global_zoom;
	
		global_zoom--;
		gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
	
		factor = exp(global_zoom * M_LN2)/exp(zoom_old * M_LN2);
	
		
		
		
		
		global_x = ((global_x + width_center) * factor) - width_center;
		global_y = ((global_y + height_center) * factor) - height_center;
		
		
		repaint_all();
		
		
		printf("zoom changed from %d to %d factor: %f x: %d\n",
		zoom_old,global_zoom, factor, global_x);

	}
}

void
on_item1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_item2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

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
	printf("%s(): \n", __PRETTY_FUNCTION__);
	
		int zoom_old;
	float factor;
	int width_center, height_center;
	
	width_center  = map_drawable->allocation.width 	/ 2;
	height_center = map_drawable->allocation.height / 2;
	
	printf("x vorher: %d",global_x);
	
	zoom_old = global_zoom;

	global_zoom = gtk_range_get_value(GTK_RANGE(widget));
	factor = exp(global_zoom * M_LN2)/exp(zoom_old * M_LN2);

	
	
	
	
	global_x = ((global_x + width_center) * factor) - width_center;
	global_y = ((global_y + height_center) * factor) - height_center;
	
	
	
	repaint_all();

	
	printf("zoom changed from %d to %d factor: %f x: %d\n",
	zoom_old,global_zoom, factor, global_x);
	
	
  return FALSE;
}


void
on_combobox1_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	GSList	*list;
	gchar *reponame_combo;
	GError **error = NULL;
	gboolean success = FALSE;

	printf("%s():\n",__PRETTY_FUNCTION__);
	
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
		printf("*** %s(): reponame: %s %s\n",__PRETTY_FUNCTION__,reponame,repo->uri);
		
		if(	g_strrstr(reponame,global_curr_reponame) != NULL &&
			strlen(reponame) == strlen(global_curr_reponame)	
		) 
		{
			
			global_curr_repo = list;
		}
		
	}
	
	
	success = gconf_client_set_string(
					global_gconfclient, 
					GCONF"/repo_name",
					global_curr_reponame,
					error);
	
	
	repaint_all();
	gtk_notebook_set_current_page(GTK_NOTEBOOK(lookup_widget(window1,"notebook1")), 0);

}

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	GtkWidget	*button6;
	gboolean	toggled;
	repo_t *repo;
	
	repo = global_curr_repo->data;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	toggled = gtk_toggle_button_get_active(togglebutton);
	repo->inverted_zoom = toggled;
	
	button6 = lookup_widget(GTK_WIDGET(togglebutton), "button6");
	gtk_widget_set_sensitive (button6, TRUE);
}


void
on_dialog1_close                       (GtkDialog       *dialog,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

}


void
on_dialog1_response                    (GtkDialog       *dialog,
                                        gint             response_id,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

}


void
on_cancelbutton1_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry;

	entry = lookup_widget(dialog1, "entry5");
	
	gtk_entry_set_text(GTK_ENTRY(entry),"");
	gtk_widget_hide(dialog1);

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
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

	gtk_widget_destroy(dialog1);

	
	
	printf("*** %s(): new repo: %s\n",__PRETTY_FUNCTION__, reponame);
	


}


void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	dialog1 = create_dialog1();

	gtk_widget_show(dialog1);
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
}

void
on_entry1_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*entry_uri, *button6;
	const gchar	*uri;
	repo_t *repo;
	
	entry_uri = lookup_widget(window1, "entry1");
	uri = gtk_entry_get_text(GTK_ENTRY(entry_uri));

	repo = global_curr_repo->data;
	repo->uri = g_strdup(uri);
	global_curr_repo->data = repo;

	button6 = lookup_widget(GTK_WIDGET(editable), "button6");
	gtk_widget_set_sensitive (button6, TRUE);

	printf("*** %s(): \n",__PRETTY_FUNCTION__);

}


void
on_entry2_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget	*entry_dir, *button6;
	const gchar	*dir;
	repo_t *repo;
	int result;
	
	entry_dir = lookup_widget(window1, "entry2");
	dir = gtk_entry_get_text(GTK_ENTRY(entry_dir));

	result = strncmp(dir, "~", 1);
	if(!result)
	{
		char *curr_dir, *sub_home, *home_dir, *full_dir;
		
		curr_dir = g_strdup(dir);
		
		strsep(&curr_dir, "~");
		sub_home = g_strdup(strsep(&curr_dir, "~"));
		home_dir = getenv("HOME");
		
		full_dir = g_strconcat(home_dir, sub_home, NULL);
		
		gtk_entry_set_text(GTK_ENTRY(entry_dir), g_strdup(full_dir));
		
		
		
		g_free(curr_dir),
		g_free(sub_home);
		g_free(full_dir);
	}
	
	repo = global_curr_repo->data;
	repo->dir = g_strdup(dir);
	global_curr_repo->data = repo;
	
	button6 = lookup_widget(GTK_WIDGET(editable), "button6");
	gtk_widget_set_sensitive (button6, TRUE);
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
}

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	gconf_set_repolist();

	gtk_widget_set_sensitive (GTK_WIDGET(button), FALSE);
}

void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	g_slist_free(trackpoint_list);
	trackpoint_list = NULL;
	trip_distance = 0;
	trip_starttime = 0;
	trip_time =0;
	trip_maxspeed = 0;
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
	
	success = gconf_client_set_bool(
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
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	entry_server	= lookup_widget(window1, "entry3");
	entry_port	= lookup_widget(window1, "entry4");
	server	= gtk_entry_get_text(GTK_ENTRY(entry_server));
	port	= gtk_entry_get_text(GTK_ENTRY(entry_port));
	global_server	= g_strdup(server);
	global_port	= g_strdup(port);
	
	global_reconnect_gpsd = TRUE;
}

void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_command;
	const gchar	*command;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	entry_command = lookup_widget(window1, "entry6");
	command = gtk_entry_get_text(GTK_ENTRY(entry_command));
	printf("cmd: %s\n",command);
	system(command);
	
}

void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	
	
	
	
	
	

	GtkWidget *widget;
	gboolean success = FALSE;
	GError **error = NULL;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	
	if(global_ffupdate_auto && !global_fftimer_running)
	{
		
		update_position();
		friendfinder_timer = g_timeout_add(global_ffupdate_interval,update_position,NULL);
		global_fftimer_running = TRUE;
		
		
		
		
		widget = lookup_widget(window1, "button23");
		gtk_widget_set_sensitive(widget, TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
		
		printf("TIMER FF called\n");

	}
	
	
	
	else if(global_ffupdate_auto && global_fftimer_running)
	{
		widget = lookup_widget(window1, "label97");
		gtk_label_set_text(GTK_LABEL(widget), "");
		
		g_source_remove(friendfinder_timer);
		friendfinder_timer = 0;
		global_fftimer_running = FALSE;
	}
	
	else if(!global_ffupdate_auto)
	{
		update_position();
		global_fftimer_running = FALSE; 
	}
	
	success = gconf_client_set_bool(
		global_gconfclient, 
		GCONF"/fftimer_running",
		global_fftimer_running,
		error);
	
	success = gconf_client_set_bool(
			global_gconfclient, 
			GCONF"/ffupdate_auto",
			global_ffupdate_auto,
			error);
	
	global_show_friends = TRUE;
}


void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	
	
	
	
	
	
	
	
}

void
on_togglebutton1_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	global_mapmode = (gtk_toggle_button_get_active(togglebutton)) ? FALSE : TRUE;
	if(!global_mapmode)
		gtk_button_set_label(GTK_BUTTON(togglebutton), "tap");
	else
		gtk_button_set_label(GTK_BUTTON(togglebutton), "map");
}

void
on_item3_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{	
	GSList *list;
	GtkWidget *label, *window;
	gchar buffer[4096];
	gboolean friend_found = FALSE;
	float lat, lon,lat_deg,lon_deg;
	float distance=0;

	printf("screen x,y: %d %d \n",mouse_x, mouse_y);
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);
	printf ("##### Lonitude: %f %f - %f %f \n", lat, lon, lat_deg, lon_deg);
	
	
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
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	g_sprintf(buffer, "Friends\nDistance: %.3fkm\n",distance);
	
	for(list = friends_list; list != NULL; list = list->next)
	{
		friend_t *f = list->data;
		printf("PIXEL FRIENDS: %d %d   \n",f->screen_x,f->screen_y);
		if( 	abs(f->screen_x - mouse_x) < 15 &&
			abs(f->screen_y - mouse_y) < 15)
		{
			printf("FOUND FRIEND X: %d %d %s\n\n",f->screen_x, mouse_x,f->nick);
	
			
			g_sprintf(buffer, 
				"%s \n"
				"Nickname: <b>%s</b> \n"
				"Last seen: %s\n<i>'%s'</i>",
				buffer,
				f->nick,
				f->lastseen,
				f->msg);
			friend_found = TRUE;
		}
	
	}
	
	if (!friend_found)
		g_sprintf(buffer,"No friends at or near this position");

	window = create_window8();

	label = lookup_widget(window,"label119");
	gtk_label_set_label(GTK_LABEL(label),buffer);

	gtk_widget_show (window);
}

void
on_item4_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *label;
	gchar buffer[512];
	gchar latlon[64];
	static float start_lat=0, start_lon=0;
	static float overall_distance = 0;
	static int start_x=0, start_y=0;
	float lat, lon,lat_deg,lon_deg, bearing=0;
	float distance=0;
	double unit_conv = 1;
	static gchar distunit[3];
	
	printf("screen x,y, global x,y: %d %d %d %d\n",mouse_x, mouse_y, global_x, global_y);

	if(!distance_mode)
		overall_distance = 0.0;

	set_cursor(GDK_CROSSHAIR);

	
	
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);

	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);

	printf ("##### Lonitude: %f %f - %f %f \n", lat, lon, lat_deg, lon_deg);

	
		
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
	
	if(!distance_mode && gpsdata && gpsdata->fix.latitude)
	{
		g_sprintf(buffer,"<b>This point:</b> \n%s \n"
				"<small><i>(coords auto-copied to clipboard)\n</i></small>\n"
				"<b>Bearing:</b>\n%.1f°\n"
				"<b>Distance from your location:</b>\n%.2f%s\n"
				"Click another point for distance",
				latlon, bearing/M_PI*180, 
				distance*unit_conv, distunit);
	}
	else if (!distance_mode && (!gpsdata || (gpsdata && !gpsdata->fix.latitude)))
	{
		g_sprintf(buffer,"<b>This point:</b> \n%s \n"
				"<small><i>(coords auto-copied to clipboard)\n</i></small>\n" 
				"Click another point for distance",
				latlon);		
	}
	else
	{
		g_sprintf(buffer,"<b>This point:</b> \n%s \n"
				"<small><i>(coords auto-copied to clipboard)\n</i></small>\n"
				"<b>Bearing:</b>\n%.1f°\n"
				"<b>Distance from last point:</b>\n%.2f%s\n"
				"<b>Overall Distance:</b>\n%.2f%s",
				latlon, bearing/M_PI*180, 
				distance*unit_conv, distunit, 
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
			

		printf("LINE x y lx ly: %d %d %d %d\n", start_x, start_y, mouse_x, mouse_y);
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
	
	
	printf("screen x,y: %d %d \n",mouse_x, mouse_y);
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	lat_deg = rad2deg(lat);
	lon_deg = rad2deg(lon);
	printf ("##### Lonitude: %f %f - %f %f \n", lat, lon, lat_deg, lon_deg);
	
	global_myposition.lat = lat_deg;
	global_myposition.lon = lon_deg;

	label = lookup_widget(window2,"label64");
	
	g_sprintf(buffer,"<b>Manually set position</b>\n\nThis point: \n\n"
			"  <i>%f %f</i> \n\n"
			"will now be used as your location\n"
			"for the friend finder service.",
			global_myposition.lat,
			global_myposition.lon);
			
	gtk_label_set_label(GTK_LABEL(label),buffer);
	gtk_widget_show (window2);
	
	
	paint_myposition();
	
	return FALSE;
}

gboolean
on_drawinarea1_scroll_event            (GtkWidget       *widget,
                                        GdkEventScroll  *event,
                                        gpointer         user_data)
{
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {
		if (event->direction == GDK_SCROLL_UP) {
			printf("SCROLL UP+Ctrl\n");
		} else {
			printf("SCROLL DOWN+Ctrl\n");
		}
		return TRUE;
	}
	else
	{
		GtkWidget *range;
		int zoom_old;
		double factor;
		int width_center, height_center;
		static int slowpad = 0;
		
		if (event->direction == GDK_SCROLL_UP && slowpad % 1 ==0)
		{
			slowpad++;
			
		
			printf("SCROLL UP\n");
			
			
			if(global_zoom<global_zoom_max)
			{	
				range = lookup_widget(window1, "vscale1");
				
				width_center  = map_drawable->allocation.width 	/ 2;
				height_center = map_drawable->allocation.height / 2;
				
				printf("x vorher: %d, %f, %f\n",global_x,event->x,event->y);
				
				zoom_old = global_zoom;
			
				global_zoom++;
				gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
				
				
				
				factor = 2;
				
				
				global_x = 2 * global_x + (int)event->x;
				global_y = 2 * global_y + (int)event->y;
				
				
				repaint_all();
			}
		}
		else if (event->direction == GDK_SCROLL_DOWN && slowpad % 1 ==0)
		{
			slowpad++;
			printf("SCROLL DOWN\n");
			
			if(global_zoom>2)
			{
				range = lookup_widget(window1, "vscale1");
			
				width_center  = map_drawable->allocation.width 	/ 2;
				height_center = map_drawable->allocation.height / 2;
				
				printf("x vorher: %d",global_x);
				
				zoom_old = global_zoom;
			
				global_zoom--;
				gtk_range_set_value(GTK_RANGE(range), (double) global_zoom);
			
				factor = exp(global_zoom * M_LN2)/exp(zoom_old * M_LN2);
			
				
				
				
				
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
		gtk_button_set_label(button, "      Stop      ");
	else
		gtk_button_set_label(button, "      Start      ");
}

void
on_entry7_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
	GtkWidget *nick;
	const gchar *n;
	GError **error = NULL;
	gboolean success = FALSE;
	
	nick  = lookup_widget(window1, "entry7");
	
	n = gtk_entry_get_text(GTK_ENTRY(nick));
		
	success = gconf_client_set_string(
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
	GError **error = NULL;
	gboolean success = FALSE;
	
	pass  = lookup_widget(window1, "entry8");
	
	p = gtk_entry_get_text(GTK_ENTRY(pass));
	
	
	success = gconf_client_set_string(
					global_gconfclient, 
					GCONF"/pass",
					p,
					error);

}

void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	register_nick();
}

void
on_button16_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_command;
	const gchar	*command;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	entry_command = lookup_widget(window1, "entry10");
	command = gtk_entry_get_text(GTK_ENTRY(entry_command));
	printf("cmd: %s\n",command);
	system(command);
}

void
on_button17_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*entry_command;
	const gchar	*command;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	entry_command = lookup_widget(window1, "entry11");
	command = gtk_entry_get_text(GTK_ENTRY(entry_command));
	printf("cmd: %s\n",command);
	system(command);
}

void
on_button18_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	trip_logger_on = (trip_logger_on) ? FALSE : TRUE;
	
	
	if(trip_logger_on)
	{
		gtk_button_set_label(button, "            Stop              ");
		track_log_open();
		gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/tracklog_on",
				TRUE, NULL);
	}
	else
	{
		gtk_button_set_label(button, "            Start             ");
		track_log_close();
		gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/tracklog_on",
				FALSE, NULL);
	}
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
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	dialog3 = create_dialog3();
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
	
	gtk_widget_destroy(dialog3);

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
}


void
on_okbutton2_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog3;
	GtkEntry *entry;
	gint mkres;
	GError **error = NULL;
	gboolean success = FALSE;
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
	
	
	printf("TRACKDIR: %s - ~ %d\n",global_track_dir, result);
	
	
	mkres = g_mkdir_with_parents(global_track_dir,0700);
	if(mkres==-1) {
		printf("MKDIR ERROR\n\n");
		perror("mkdir........");
	}
	
	success = gconf_client_set_string(
				global_gconfclient, 
				GCONF"/track_dir",
				global_track_dir,
				error);
	
	dialog3 = lookup_widget(GTK_WIDGET(button), "dialog3");
	
	gtk_widget_destroy(dialog3);
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
	
	return FALSE;
}

void
on_item8_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *dialog4;
	
	dialog4 = create_dialog4();
	gtk_widget_show(dialog4);
}

void
on_cancelbutton3_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget	*dialog;

	dialog = lookup_widget(GTK_WIDGET(button), "dialog4");
	gtk_widget_destroy(dialog);
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
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	

	
	if (!pixmap_photo)
	pixmap_photo = gdk_pixmap_new (
			widget->window,
			widget->allocation.width,
			widget->allocation.height,
			-1);

	if(pixmap_photo)
		printf("pixmap_photo NOT NULL");
	else
		printf("aieee: pixmap_photo NULL\n");

	
	
	
	
	
	
	return FALSE;
}


gboolean
on_drawingarea2_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	printf("** D2: expose event\n");

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
		printf("\n\nPIXEL PHOTOS: %d %d   \n\n",p->screen_x,p->screen_y);
		
		if(abs(p->screen_x - mouse_x) < 15 &&
		   abs(p->screen_y - mouse_y) < 15 &&
		   !photo_found && !photo) 
		{
			
			printf("FOUND PHOTO X: %d %d %s\n",p->screen_x, mouse_x, p->name);
	
			
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
				g_sprintf(buffer, "File not found");
			}
			else
			{
				photo_file = p->filename;
				
				printf ("+++++++++++++ F*CKING  DRAWINF +++++++++\n");

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
		g_sprintf(buffer, "No Geo Photo found");
	
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
	GtkWidget *widget;
	GtkWidget *drawingarea;

	gchar buffer[512];
	gchar *photo_file = user_data;

	GdkPixbuf *photo = NULL;
	GError	*error = NULL;
	GdkGC *gc;
	
printf("*** %s(): \n",__PRETTY_FUNCTION__);

	
	widget = create_win13_biggeo();
	gtk_widget_show(widget);
	
	drawingarea = lookup_widget(widget, "drawingarea3");
	
	photo = gdk_pixbuf_new_from_file_at_size (
							photo_file, 640,-1,
							&error);
	if(!photo)
	{
		printf ("+++++++++++++ FOTO NOT FOUND: %s +++++++++\n", photo_file);
		g_sprintf(buffer, "File not found");
	}
	else
	{
printf("*** %s():22 \n",__PRETTY_FUNCTION__);

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

printf("*** %s(): 33\n",__PRETTY_FUNCTION__);

	
		

	
	
	gtk_widget_hide(window3);printf("*** %s(): 44\n",__PRETTY_FUNCTION__);

}

gboolean
on_item9_button_release_event          (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

  return FALSE;
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

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	dialog = create_dialog6();
	gtk_widget_show(dialog);
	
	combobox = lookup_widget(dialog, "combobox4");
	gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), 0);

	return FALSE;
}


void
on_dialog5_close                       (GtkDialog       *dialog,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

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
on_dialog6_close                       (GtkDialog       *dialog,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

}


void
on_cancelbutton5_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	dialog = lookup_widget(GTK_WIDGET(button), "dialog6");
	gtk_widget_destroy(dialog);

}


void
on_okbutton5_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *dialog,*combobox,*widget;
	gboolean pois_shown;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	dialog = lookup_widget(GTK_WIDGET(button), "dialog6");
	
	
	combobox = lookup_widget(GTK_WIDGET(button), "combobox4");
	global_poi_cat = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox));

	gtk_widget_destroy(dialog);


	
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
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

  return FALSE;
}

gboolean
on_dialog5_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	GtkWidget	*dialog;
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	dialog = lookup_widget(widget, "dialog5");
	gtk_widget_destroy(dialog);

	return FALSE;
}


void
on_combobox2_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
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
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	if (gtk_toggle_button_get_active(togglebutton))
	{
		GtkWidget *widget;
		
		if(friendfinder_timer) g_source_remove(friendfinder_timer);
		friendfinder_timer = 0;
		global_fftimer_running = FALSE;
		global_ffupdate_auto = FALSE;
		
		widget = lookup_widget(window1, "button23");
		gtk_widget_set_sensitive(widget,FALSE);
		widget = lookup_widget(window1, "button11");
		gtk_widget_set_sensitive(widget, TRUE);
	}
	
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffupdate_auto",
				global_ffupdate_auto,
				error);
	
	success = gconf_client_set_bool(
		global_gconfclient, 
		GCONF"/fftimer_running",
		global_fftimer_running,
		error);
}


void
on_radiobutton13_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_ffupdate_auto = (gtk_toggle_button_get_active(togglebutton)) ? TRUE : global_ffupdate_auto;

	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffupdate_auto",
				global_ffupdate_auto,
				error);
}


void
on_entry16_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
		
	GtkWidget *widget;
	
	
	
	global_ffupdate_interval_minutes = atof(gtk_entry_get_text(GTK_ENTRY(editable)));
	global_ffupdate_interval = (int)floor(global_ffupdate_interval_minutes) * 60000;
	if (global_ffupdate_interval<10000) global_ffupdate_interval = 10000;
	
	
	
	
	widget = lookup_widget(window1, "button23");
	gtk_widget_set_sensitive(widget,FALSE);
	widget = lookup_widget(window1, "button11");
	gtk_widget_set_sensitive(widget, TRUE);

	if(friendfinder_timer) g_source_remove(friendfinder_timer);
	friendfinder_timer = 0;
	global_fftimer_running = FALSE;
	
	success = gconf_client_set_float(
			global_gconfclient, 
			GCONF"/ffupdate_interval_minutes",
			global_ffupdate_interval_minutes,
			error);
	
	success = gconf_client_set_bool(
			global_gconfclient, 
			GCONF"/fftimer_running",
			global_fftimer_running,
			error);

	printf("*%s(): ffinterval: %d\n",__PRETTY_FUNCTION__, global_ffupdate_interval );
}


void
on_radiobutton14_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_speed_unit = (gtk_toggle_button_get_active(togglebutton)) ? 0 : global_speed_unit;

	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/speed_unit",
				global_speed_unit,
				error);
}


void
on_radiobutton15_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_speed_unit = (gtk_toggle_button_get_active(togglebutton)) ? 1 : global_speed_unit;
	
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/speed_unit",
				global_speed_unit,
				error);
}


void
on_radiobutton16_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_speed_unit = (gtk_toggle_button_get_active(togglebutton)) ? 2 : global_speed_unit;
	
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/speed_unit",
				global_speed_unit,
				error);
}


void
on_radiobutton17_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_alt_unit = (gtk_toggle_button_get_active(togglebutton)) ? 0 : global_alt_unit;
	
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/alt_unit",
				global_alt_unit,
				error);
}


void
on_radiobutton18_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_alt_unit = (gtk_toggle_button_get_active(togglebutton)) ? 1 : global_alt_unit;

	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/alt_unit",
				global_alt_unit,
				error);
}


void
on_radiobutton19_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_latlon_unit = (gtk_toggle_button_get_active(togglebutton)) ? 0 : global_latlon_unit;
	
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/latlon_unit",
				global_latlon_unit,
				error);
}


void
on_radiobutton20_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;
	
	global_latlon_unit = (gtk_toggle_button_get_active(togglebutton)) ? 1 : global_latlon_unit;

	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/latlon_unit",
				global_latlon_unit,
				error);
}

void
on_radiobutton21_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_latlon_unit = (gtk_toggle_button_get_active(togglebutton)) ? 2 : global_latlon_unit;
	
	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/latlon_unit",
				global_latlon_unit,
				error);
}

void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_ffcm_public = gtk_toggle_button_get_active(togglebutton);
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffcm_public",
				global_ffcm_public,
				error);
}


void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_ffcm_registered = gtk_toggle_button_get_active(togglebutton);
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffcm_registered",
				global_ffcm_registered,
				error);
}


void
on_checkbutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_ffcm_friends = gtk_toggle_button_get_active(togglebutton);
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffcm_friends",
				global_ffcm_friends,
				error);
}


void
on_checkbutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_ffcu_public = gtk_toggle_button_get_active(togglebutton);
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffcu_public",
				global_ffcu_public,
				error);
}


void
on_checkbutton7_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_ffcu_registered = gtk_toggle_button_get_active(togglebutton);
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffcu_registered",
				global_ffcu_registered,
				error);
}


void
on_checkbutton8_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	gboolean success = FALSE;
	GError **error = NULL;

	global_ffcu_friends = gtk_toggle_button_get_active(togglebutton);
	
	success = gconf_client_set_bool(
				global_gconfclient, 
				GCONF"/ffcu_friends",
				global_ffcu_friends,
				error);
}

gboolean
on_button11_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{


	
  return FALSE;
}

void
on_button23_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	GError **error = NULL;
	
	gtk_widget_set_sensitive(GTK_WIDGET(button),FALSE);
	widget = lookup_widget(window1, "button11");
	gtk_widget_set_sensitive(widget, TRUE);

			
	g_source_remove(friendfinder_timer);
	friendfinder_timer = 0;
	global_fftimer_running = FALSE;
	
	gconf_client_set_bool(
		global_gconfclient, 
		GCONF"/fftimer_running",
		global_fftimer_running,
		error);
}

void
on_item17_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	float lat, lon;
	
	
	printf("screen x,y: %d %d \n",mouse_x, mouse_y);
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	set_current_wp(lat, lon);	
	
}


void
on_item18_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	global_wp_on = FALSE;
	repaint_all();
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
	printf("hello, world, %f %f\n", wp->lat, wp->lon);
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
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	global_show_friends = (active) ? TRUE : FALSE;
	
	if(friends_list==NULL)
		update_position();
	repaint_all();
}


void
on_item20_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gboolean active;
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	global_show_pois = (active) ? TRUE : FALSE;


	
	repaint_all();
}



void
on_item9_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gboolean active;
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	global_show_photos = (active) ? TRUE : FALSE;

	if (active && photo_list == NULL)
		get_photos();
	
	repaint_all();
}


void
repaint_all()
{
	fill_tiles_pixel(global_x, global_y, global_zoom);
	print_track();
	paint_loaded_track();
	paint_friends();
	paint_photos();
	paint_pois();
	paint_wp();
	paint_myposition();
	osd_speed(TRUE);

}

void
on_button29_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window;
	waypoint_t *wp;
printf("DEBUG\n");	
	wp = user_data;
printf("hello, world, %f %f\n", wp->lat, wp->lon);
	set_current_wp(wp->lat, wp->lon);
printf("DEBUG\n");	

	window = lookup_widget(GTK_WIDGET(button), "window3");
	gtk_widget_hide(window);
}

void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	
	GtkWidget *entry14, *entry15;

	char buf[64];

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	
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
	GtkWidget *widget;
	GtkTextBuffer *tbuffer;
	GtkWidget *window;

	poi_t *p;

	
	p = user_data;
	tbuffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_insert_at_cursor(tbuffer, "p->desc", -1);
	gtk_text_buffer_set_text(tbuffer, "p->desc", -1);
	
	
	
	window = create_window10();
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
		gtk_label_set_label(GTK_LABEL(widget), "<span foreground='#ff0000'>POI has no ID -> see website for help!</span>");
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

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	
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
	if (event->keyval == GDK_Page_Up || event->keyval == GDK_KP_Up || event->keyval == 'i')
	{
		printf("up/dn key pressed\n");	
		on_button4_clicked(NULL, NULL);
	}
	else if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK && event->keyval == 'p')
		geo_photos_open_dialog_photo_correlate();
	else if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK && event->keyval == 't')
		tracks_open_tracks_dialog();
	else if(event->keyval == GDK_Page_Down || event->keyval == 'o')
		on_button5_clicked(NULL, NULL);
	else if(event->keyval == GDK_space)
		on_button1_clicked(GTK_BUTTON(window1), NULL);
	else if(event->keyval == GDK_a)
		on_button3_clicked(GTK_BUTTON(window1), NULL);
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
	else
		printf("some key pressed\n");
	
  return TRUE;
}

void
on_button34_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget, *widget2;
	poi_t *p;

	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	p = user_data;
	widget = create_dialog7();
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
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

  return FALSE;
}


void
on_cancelbutton6_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	widget = lookup_widget(GTK_WIDGET(button), "dialog7");
	gtk_widget_destroy(widget);
}


void
on_okbutton6_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	poi_t *p;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
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
	static gboolean visible=FALSE;
	widget = lookup_widget(window1, "label132");
	
	if(visible)
	{	
		gtk_widget_hide(widget);
		visible = FALSE;
		gtk_button_set_label(button, "open");
	}
	else
	{
		gtk_widget_show(widget);
		visible = TRUE;
		gtk_button_set_label(button, "close");
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
	GtkWidget *window;
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	window = lookup_widget(widget, "window12");
	gtk_widget_destroy(window);
	
	return FALSE;
}

void
on_button37_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *widget;
	printf("*** %s(): \n",__PRETTY_FUNCTION__);

	widget = lookup_widget(GTK_WIDGET(button), "window12");
	gtk_widget_destroy(widget);
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
		
	dialog8 = create_dialog8();
		
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
	GtkWidget	*widget;

	widget = lookup_widget(GTK_WIDGET(button), "dialog8");
	
	gtk_widget_destroy(dialog8);
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

	printf("*** %s(): new repo: %s %s\n",__PRETTY_FUNCTION__, repo->name, global_curr_reponame);
	gconf_set_repolist();

	gtk_widget_destroy(dialog8);

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

	printf("strlen: %d \n", strlen(txt1));
	
	widget = lookup_widget(GTK_WIDGET(editable), "okbutton1");
	
	if(strlen(txt1) && strlen(txt2) && strlen(txt3))
		gtk_widget_set_sensitive (widget, TRUE);
	else
		gtk_widget_set_sensitive (widget, FALSE);
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
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

	printf("strlen: %d \n", strlen(txt1));
	
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
	printf("%s(): \n",__PRETTY_FUNCTION__);
}

gboolean
on_eventbox1_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	printf("%s(): \n",__PRETTY_FUNCTION__);
	
	GtkWidget	*window;
	
	window = lookup_widget(widget, "drawingarea2");

	
		
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
	
	gtk_widget_hide(window);
	
  return FALSE;
}

gboolean
on_drawingarea3_configure_event        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	

	
	if (!pixmap_photo_big)
	pixmap_photo = gdk_pixmap_new (
			widget->window,
			widget->allocation.width,
			widget->allocation.height,
			-1);

	if(pixmap_photo_big)
		printf("pixmap_photo NOT NULL");
	else
		printf("aieee: pixmap_photo NULL\n");

	
	
	
	
	
	
	return FALSE;
}


gboolean
on_drawingarea3_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	printf("** D2: expose event\n");
	
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


void
on_itemimport1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_itemselect1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

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
on_button41_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

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
	printf("%s \n", __PRETTY_FUNCTION__);
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
printf("I am deleted\n");
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
	printf("distance_mode\n");
	on_item4_activate(NULL, NULL);
}

gboolean
on_item17_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	float lat, lon;
	
	
	printf("screen x,y: %d %d \n",mouse_x, mouse_y);
	lat = pixel2lat(global_zoom, global_y+mouse_y);
	lon = pixel2lon(global_zoom, global_x+mouse_x);
	
	set_current_wp(lat, lon);
  return FALSE;
}


gboolean
on_item18_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	global_wp_on = FALSE;
	repaint_all();
  return FALSE;
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
	GError *error = NULL;
	gboolean success = FALSE;

	printf ("shrink details\n");

	if (global_detail_zoom > 0) {
		global_detail_zoom--;

	}

	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/global_detail_zoom",
				global_detail_zoom,
				&error);

	repaint_all ();
}

void
activate_larger_map_details (GtkMenuItem *larger_item, GtkMenuItem *more_item)
{
	GError *error = NULL;
	gboolean success = FALSE;

	printf ("enlarge details\n");

	global_detail_zoom++;

	success = gconf_client_set_int(
				global_gconfclient, 
				GCONF"/global_detail_zoom",
				global_detail_zoom,
				&error);

	repaint_all ();
}
