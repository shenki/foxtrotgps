

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <glib.h>
#include <glib/gstdio.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gdk/gdk.h>
#include <gconf/gconf.h>
#include <math.h>
#include <time.h>
#include <errno.h>

#include "globals.h"
#include "map_management.h"
#include "converter.h"
#include "gps_functions.h"
#include "support.h"
#include "callbacks.h"
#include "wp.h"

FILE *fp = NULL;



void
track_log()
{
	gchar buffer[256];
	gchar data[256];
	time_t time_sec;
	struct tm *ts;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	if(gpsdata->valid)
	{
		
		time_sec = (time_t)gpsdata->fix.time;
		ts = localtime(&time_sec);
		
		
		strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", ts);
		
		
		sprintf(data, "%f,%f,%.1f,%.1f,%.1f,%.1f,%s\n",
				gpsdata->fix.latitude,
				gpsdata->fix.longitude,
				gpsdata->fix.altitude,
				gpsdata->fix.speed,
				gpsdata->fix.track,
				gpsdata->hdop,
				buffer);
		
		if (fp) fprintf(fp,data);
	}
}

void
track_log_open()
{
	time_t time_epoch_sec;
	struct tm  *tm_struct;
	gchar buffer[256];
	gchar *filename = NULL;
	GtkLabel *label76;
	gchar *labeltext;
	
	label76 = GTK_LABEL(lookup_widget(window1, "label76"));
	
	
	time_epoch_sec = time(NULL);
	tm_struct = localtime(&time_epoch_sec);
	
	
	

	strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S.log", tm_struct);
	

	
	filename = g_strconcat(global_track_dir, buffer,NULL);
	
	printf("*** %s(): %s\n",__PRETTY_FUNCTION__,filename);
	
	if(fp==NULL && trip_logger_on)
	{
		fp = fopen(filename,"w");
		if(!fp)
		{
			printf("oops: %s \n",strerror(errno));
			perror("Triplog open failed: ");
			gtk_label_set_label(label76,"<span foreground='#ff0000'>Error opening logfile</span>");
		}
		else 
		{
			labeltext = g_strconcat("<b><span foreground='#0000ff'>Log: ",buffer,"</span></b>",NULL);
			gtk_label_set_label(label76,labeltext);
			g_free(labeltext);	
		}
	}
	
	g_free(filename);
}


void
track_log_close()
{
	int ret;
	GtkLabel *label76;
	label76 = GTK_LABEL(lookup_widget(window1, "label76"));
	gtk_label_set_label(label76,"");
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);
	
	if(fp) {
		printf("closing FP\n");
		ret = fclose(fp);
		fp = NULL;
	
		if(ret) printf("ERROR closing file\n");
	}
}


gboolean
cb_gps_timer()
{
	int pixel_x, pixel_y, x, y, last_x, last_y;
	static float lat, lon;
	static float lat_tmp=0, lon_tmp=0;
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
	}
	
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
			
			

	get_gps();
	

	if(gpsdata) 
	{
		trackpoint_t *tp = g_new0(trackpoint_t,1);
		static int counter = 0;
		

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
			
			heading_rad = (gpsdata->fix.track * (1.0 / 180.0)) * M_PI;

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
					x-15 + mouse_dx, y-15 + mouse_dy,		
					30,30,			
					0, 360*64);		
				
				
				if(global_wp_on && gpsdata->valid)
				{
					
					bearing = get_bearing(lat, lon, global_wp.lat, global_wp.lon);
					gpsdata->fix.bearing = bearing;
					printf("BEARING: %f\n", bearing);
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
		

		
		if(trip_counter_on)
		{
			
			
			
			if( gpsdata->valid && lat_tmp!=0 && lon_tmp!=0) 
			{
				trip_delta = 6371.0 *  acos(sin(lat) * sin(lat_tmp) + 
								cos(lat) * cos(lat_tmp) * cos(lon_tmp-lon) );
				if(isnan(trip_delta))
				{
					
					
					printf("WTF??? %f %f %f %f %f \n",lat,lon,lat_tmp,lon_tmp,trip_delta);
				}
				else
				{
					trip_distance += trip_delta;
					
					
					if(trip_distance > 0.005)
					{
						
						counter++;
						if(counter % 5 == 0)
						{
							tp->lat = lat;
							tp->lon = lon;
							trackpoint_list = g_slist_append(trackpoint_list, tp);
						}	
					}
				}
			}
			
			
			
			
			
			
			
			
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
		printf("no gpsdata for timer\n");
		set_label_nogps();
	}
	return TRUE; 
}

GSList *
gconf_get_repolist()
{
	GSList	*repo_list;
	
	GSList	*list;
	GError **error = NULL;
	
	
	repo_list = gconf_client_get_list(	global_gconfclient, 
						GCONF"/repos",
						GCONF_VALUE_STRING,
						error);
	
	if (repo_list == NULL)
	{
		repo_t *repo1 = g_new0(repo_t, 1);
		repo_t *repo2 = g_new0(repo_t, 1);
		repo_t *repo3 = g_new0(repo_t, 1);
		repo_t *repo4 = g_new0(repo_t, 1);
		repo_t *repo5 = g_new0(repo_t, 1);

		
		printf("REPOLIST == NULL\n");
		repo1->name = g_strdup("OSM");
		repo1->uri  = g_strdup("http://tile.openstreetmap.org/%d/%d/%d.png");
		repo1->dir  = g_strdup_printf("%s/Maps/OSM",global_home_dir);
		repo1->inverted_zoom = 0;
		global_repo_list = g_slist_append(global_repo_list, repo1);

		repo2->name = g_strdup("Topo");
		repo2->uri  = g_strdup("maps-for-free");
		repo2->dir  = g_strdup_printf("%s/Maps/maps4free",global_home_dir);
		repo2->inverted_zoom = 0;
		global_repo_list = g_slist_append(global_repo_list, repo2);
		
		repo3->name = g_strdup("Aerial");
		repo3->uri  = g_strdup("openaerial");
		repo3->dir  = g_strdup_printf("%s/Maps/openaerial",global_home_dir);
		repo3->inverted_zoom = 0;
		global_repo_list = g_slist_append(global_repo_list, repo3);
		
		repo4->name = g_strdup("Opencyclemap");
		repo4->uri  = g_strdup("http://a.andy.sandbox.cloudmade.com/tiles/cycle/%d/%d/%d.png");
		repo4->dir  = g_strdup_printf("%s/Maps/opencyclemap",global_home_dir);
		repo4->inverted_zoom = 0;
		global_repo_list = g_slist_append(global_repo_list, repo4);
		
		repo5->name = g_strdup("Google Sat (testing only)");
		repo5->uri  = g_strdup("http://khm.google.com/kh/v=45&x=%d&y=%d&z=%d");
		repo5->dir  = g_strdup_printf("%s/Maps/googlesat",global_home_dir);
		repo5->inverted_zoom = 1;
		global_repo_list = g_slist_append(global_repo_list, repo5);
		
	}
	
	
	for(list = repo_list; list != NULL; list = list->next)
	{
		gchar **array;
		gchar *str = list->data;
		repo_t *repo = g_new0(repo_t, 1);
		
		array = g_strsplit(str,"|",4);	
		
		repo->name = g_strdup(array[0]);
		repo->uri  = g_strdup(array[1]);
		repo->dir  = g_strdup(array[2]);
		repo->inverted_zoom = (atoi(g_strdup(array[3])) == 1) ? TRUE : FALSE;
		
		global_repo_list = g_slist_append(global_repo_list, repo);

		printf("GCONF: \n -- name: %s \n -- uri: %s \n -- dir: %s \n",
			repo->name, repo->uri, repo->dir);
	}
	
	
	return global_repo_list;	
					
}

void
gconf_set_repolist()
{
	
	GSList	*list;
	GSList	*gconf_list = NULL;
	GError **error = NULL;
	gboolean success = FALSE;
	
	
	
	for(list = global_repo_list; list != NULL; list = list->next)
	{
		repo_t *repo;
		gchar gconf_str[1024];
		
		repo = list->data;
		
		
		g_sprintf(	gconf_str, 
				"%s|%s|%s|%i",
				repo->name, repo->uri, repo->dir, repo->inverted_zoom);
		
		gconf_list = g_slist_append(gconf_list, g_strdup(gconf_str));

		printf("GCONFSAVE: \n -- name: %s \n -- uri: %s \n -- dir: %s \n -- zoom: %i \n\n %s \n",
			repo->name, repo->uri, repo->dir, repo->inverted_zoom, gconf_str);
	}
	
	success = gconf_client_set_list(	global_gconfclient, 
						GCONF"/repos",
						GCONF_VALUE_STRING,
						gconf_list,
						error);
	
	printf("*** %s(): %i \n",__PRETTY_FUNCTION__, success);

}




void
repoconfig__populate_dialog()
{

}

void
repoconfig__set_current_list_pointer()
{
	
	
	GSList		*list;
	const gchar	*reponame;
	
	for(list = global_repo_list; list != NULL; list = list->next)
	{
		repo_t *repo;
		repo	= list->data;
		
		reponame = g_strdup(repo->name);
		
		if(	g_strrstr(reponame,global_curr_reponame) != NULL &&
			strlen(reponame) == strlen(global_curr_reponame)	
		)
			global_curr_repo = list;
	}
	if(!global_curr_repo)
	{
		printf("\n#\n#\n#  ERROR: repository %s is broken \n#\n#\n", global_curr_reponame);
		
		printf("Resetting repo_name and exiting now.\n\n");
		printf("If problem persists after restart, \n");
		printf("execute in a terminal: gconftool-2 -u /apps/tangogps/repos");
		system("gconftool-2 -u /apps/tangogps/repo_name");
		exit(EXIT_FAILURE);		
	}
}


void
repoconfig__create_dropdown()
{
	GtkWidget	*combobox;
	GSList		*list;
	int 		i = 0;
	int		j = 0;
	const gchar	*reponame;
	
	combobox = lookup_widget(window1, "combobox1");

	for(list = global_repo_list; list != NULL; list = list->next)
	{
		repo_t	*repo;
		
		repo = list->data;
		reponame = g_strdup(repo->name);
		gtk_combo_box_append_text (GTK_COMBO_BOX(combobox), g_strdup(repo->name));
		
		if(	g_strrstr(reponame,global_curr_reponame) != NULL &&
			strlen(reponame) == strlen(global_curr_reponame)	
		)
		{
			j = i;
			global_curr_repo = list;
		}
		i++;
	}
	global_repo_cnt = i;
	gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), j);
}


void
pre_init()
{
	GError	**err = NULL;

	g_type_init();

	global_home_dir = getenv("HOME");

	global_gconfclient	= gconf_client_get_default();
	global_curr_reponame	= gconf_client_get_string(global_gconfclient, GCONF"/repo_name",err);


	if(global_curr_reponame == NULL)
	{
		printf("gconf repo_name not set\n");
		global_curr_reponame = g_strdup("OSM");
	}
	gconf_get_repolist();	
	repoconfig__set_current_list_pointer();
	
	global_x = gconf_client_get_int(
				global_gconfclient, 
				GCONF"/global_x",
				err);
	global_y = gconf_client_get_int(
				global_gconfclient, 
				GCONF"/global_y",
				err);
	global_zoom = gconf_client_get_int(
				global_gconfclient, 
				GCONF"/global_zoom",
				err);
	



	if(global_zoom <= 2) 
	{
		global_x = 890;
		global_y = 515;
		global_zoom = 3;
	}
	
	if(gconf_client_get_bool(global_gconfclient, GCONF"/started_before", err))	
		global_auto_download = gconf_client_get_bool(
					global_gconfclient, 
					GCONF"/auto_download",
					err);
	else
	{
		gconf_client_set_bool(global_gconfclient, GCONF"/started_before", TRUE, err);
		gconf_client_set_bool(global_gconfclient, GCONF"/auto_download", TRUE, err);
		global_auto_download = TRUE;
	}
}

void
init()
{
	gint timer;
	gpointer data = NULL;	
	
	GError	*err = NULL;
	const gchar *nick, *pass;
	GtkWidget *nick_entry, *pass_entry, *widget;
	gchar buffer[128];
	gboolean gconf_fftimer_running;
	char *str = NULL;
	

	
	tangogps_dir = g_strconcat(global_home_dir, "/.tangogps", NULL);
	g_mkdir(tangogps_dir, 0700);

	repoconfig__create_dropdown();

	
	nick_entry  = lookup_widget(window1, "entry7");
	pass_entry  = lookup_widget(window1, "entry8");

	global_gconfclient	= gconf_client_get_default(); 
	nick			= gconf_client_get_string(global_gconfclient, GCONF"/nick",&err);
	pass			= gconf_client_get_string(global_gconfclient, GCONF"/pass",&err);
	
	global_speed_unit	= gconf_client_get_int(global_gconfclient, GCONF"/speed_unit",&err);
	global_alt_unit		= gconf_client_get_int(global_gconfclient, GCONF"/alt_unit",&err);
	global_latlon_unit	= gconf_client_get_int(global_gconfclient, GCONF"/latlon_unit",&err);
	
	switch (global_speed_unit)
	{
		case 1:
			widget = lookup_widget(window1, "radiobutton15");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
			break;
		case 2:
			widget = lookup_widget(window1, "radiobutton16");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
			break;
	}
	
	switch (global_alt_unit)
	{
		case 1:
			widget = lookup_widget(window1, "radiobutton18");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
			break;
	}
	
	switch (global_latlon_unit)
	{
		case 1:
			widget = lookup_widget(window1, "radiobutton20");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
			break;
		case 2:
			widget = lookup_widget(window1, "radiobutton21");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
			break;
	}
	
	gtk_entry_set_text( GTK_ENTRY(nick_entry), nick );
	gtk_entry_set_text( GTK_ENTRY(pass_entry), pass );
	
	widget = lookup_widget(window1, "vscale1");
	gtk_range_set_value(GTK_RANGE(widget), (double) global_zoom);
	
	global_track_dir	= gconf_client_get_string(global_gconfclient, GCONF"/track_dir",&err);
	if(!global_track_dir)
		global_track_dir = g_strdup_printf("%s/Maps/",global_home_dir);
	
	global_myposition.lat = 0;
	global_myposition.lon = 0;

	widget = lookup_widget(window1, "checkbutton2");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), global_auto_download);

	
	
	
	
	
	gconf_fftimer_running = gconf_client_get_bool(global_gconfclient, GCONF"/fftimer_running",&err);
	
	
	global_ffupdate_interval_minutes = gconf_client_get_float(global_gconfclient, GCONF"/ffupdate_interval_minutes",&err);
	global_ffupdate_interval = (int)floor(global_ffupdate_interval_minutes) * 60000;
	widget = lookup_widget(window1, "entry16");
	if (global_ffupdate_interval_minutes<10)
		g_sprintf(buffer, "%.1f", global_ffupdate_interval_minutes);
	else
		g_sprintf(buffer, "%.0f", global_ffupdate_interval_minutes);
	gtk_entry_set_text( GTK_ENTRY(widget), buffer );
	
	
	global_ffupdate_auto	= gconf_client_get_bool(global_gconfclient, GCONF"/ffupdate_auto",&err);
	if(global_ffupdate_auto)
	{
		widget = lookup_widget(window1, "radiobutton13");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),TRUE);
	}

	
	if(gconf_fftimer_running)
	{
		widget = lookup_widget(menu1, "item19");
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), TRUE);
	}
		
	
	global_ffcm_public	= gconf_client_get_bool(global_gconfclient, GCONF"/ffcm_public",&err);
	global_ffcm_registered	= gconf_client_get_bool(global_gconfclient, GCONF"/ffcm_registered",&err);
	global_ffcm_friends	= gconf_client_get_bool(global_gconfclient, GCONF"/ffcm_friends",&err);
	
	widget = lookup_widget(window1, "checkbutton3");
	if(global_ffcm_public)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
	}


	widget = lookup_widget(window1, "checkbutton4");
	if(global_ffcm_registered)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
	}

	
	widget = lookup_widget(window1, "checkbutton5");
	if(global_ffcm_friends)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
	}	
	
	
	
	
	global_ffcu_public	= gconf_client_get_bool(global_gconfclient, GCONF"/ffcu_public",&err);
	global_ffcu_registered	= gconf_client_get_bool(global_gconfclient, GCONF"/ffcu_registered",&err);
	global_ffcu_friends	= gconf_client_get_bool(global_gconfclient, GCONF"/ffcu_friends",&err);
	
	widget = lookup_widget(window1, "checkbutton6");
	if(global_ffcu_public)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
	}
	
	
	widget = lookup_widget(window1, "checkbutton7");
	if(global_ffcu_registered)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
	}

	
	widget = lookup_widget(window1, "checkbutton8");
	if(global_ffcu_friends)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
	}	
	
	widget = lookup_widget(window1, "label117");
#ifdef VERSION
	gtk_label_set_label(GTK_LABEL(widget), "<i>tangoGPS version: " VERSION "\nDeveloper: Marcus Bauer</i>");
#endif

	str = gconf_client_get_string(global_gconfclient, GCONF"/gpsd_host",&err);
	widget = lookup_widget(window1, "entry3");
	gtk_entry_set_text(GTK_ENTRY(widget), g_strdup(str));
	g_free(str);
	
	str = gconf_client_get_string(global_gconfclient, GCONF"/gpsd_port",&err);
	widget = lookup_widget(window1, "entry4");
	gtk_entry_set_text(GTK_ENTRY(widget), g_strdup(str));
	g_free(str);
	
	if (gconf_client_get_bool(global_gconfclient, GCONF"/tracklog_on", NULL))
		gtk_button_clicked(GTK_BUTTON(lookup_widget(window1,"button18")));
	
	timer = g_timeout_add (1000,cb_gps_timer,data);
	
	gtk_window_set_icon_from_file(GTK_WINDOW(window1), PACKAGE_PIXMAPS_DIR "/" PNAME ".png" ,&err);
	if (err)
	{
		fprintf (stderr, "Failed to load pixbuf file:  %s\n", err->message);
		g_error_free (err);
	}
}
