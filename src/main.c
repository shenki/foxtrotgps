



#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
 
#include <locale.h>
#include <string.h>
#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"
#include "init.h"
#include "callbacks.h"
#include "globals.h"

int
main (int argc, char *argv[])
{
	
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


  pre_init();
  window1 = create_window1 ();
  gtk_widget_show (window1);

  if(argc > 1 && strcmp(argv[1], "-fullscreen") == 0)
	  on_button1_clicked(GTK_BUTTON(window1), NULL);
  
  window2 = create_window2();
  window3 = create_window3();
  menu1 = create_menu1();

  
  init();
  
  gtk_main ();
  
  gdk_threads_leave ();
  
  return 0;
}
