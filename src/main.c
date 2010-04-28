



#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
 
#include <locale.h>
#include <string.h>
#include <gtk/gtk.h>

#include <glade/glade.h>

#include "interface.h"
#include "support.h"
#include "init.h"
#include "callbacks.h"
#include "globals.h"

int
main (int argc, char *argv[])
{
	
	GladeXML *gladexml;
#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
	gtk_set_locale ();
	
	if (!g_thread_supported ()) g_thread_init (NULL);
	gdk_threads_init ();
	gdk_threads_enter ();
	
	
	gtk_init (&argc, &argv);
	
	setlocale (LC_NUMERIC, "C");
	
	add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
	
	
	global_server	= g_strdup("127.0.0.1");
	global_port	= g_strdup("2947");
	
	
        glade_init ();
        
        gladexml = glade_xml_new (PACKAGE_DATA_DIR "/" PACKAGE "/" PACKAGE ".glade", NULL, GETTEXT_PACKAGE);
        glade_xml_signal_autoconnect (gladexml);

	pre_init();
	window1 = glade_xml_get_widget (gladexml, "window1");
	


  	
	int screen_height, screen_width;
  	GtkWidget *toolbar;

  	screen_height = gdk_screen_get_height(gdk_screen_get_default());
	screen_width  = gdk_screen_get_width (gdk_screen_get_default());
	
	if (screen_height > screen_width)
	{
		toolbar = lookup_widget(window1, "toolbar1");
		global_landscape = FALSE;
	}
	else {
		toolbar = lookup_widget(window1, "toolbar4");
		global_landscape = TRUE;
	}
	gtk_widget_show(toolbar);
	
	
	if(screen_height < 640 && screen_height > screen_width)
	{
		printf("height: %d \n",screen_height);
		gtk_window_resize(GTK_WINDOW(window1), 
				  (screen_width < 480) ? screen_width : 480, 
				  screen_height-30);
	}
	else if(screen_height < 640 && screen_width <= 1024 && screen_height < screen_width)
	{
		gtk_window_resize(GTK_WINDOW(window1), 
				  (screen_width < 480) ? screen_width : 480, 
				  screen_height-60);		
	}
	
	GtkWidget *hbox;
	hbox = lookup_widget(window1, "hbox49a");
	global_infopane_widgets = gtk_container_get_children(GTK_CONTAINER(hbox));

	
	gtk_widget_show (window1);
		
	if(argc > 1 && strcmp(argv[1], "-fullscreen") == 0)
		on_button1_clicked(GTK_BUTTON(window1), NULL);
	
	window2 = create_window2();
	window3 = create_window3();
	menu1 = glade_xml_get_widget (gladexml, "menu1");
	
	
	init();
	
	gtk_main ();
	
	gdk_threads_leave ();
	
	return 0;
}
