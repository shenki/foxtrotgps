

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_window3 (void)
{
  GtkWidget *window3;
  GtkWidget *vbox27;
  GtkWidget *vbox26;
  GtkWidget *label104;
  GtkWidget *eventbox1;
  GtkWidget *drawingarea2;
  GtkWidget *hbox26;
  GtkWidget *button21;
  GtkWidget *button29;

  window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window3), _("Geo Photo"));
  gtk_window_set_position (GTK_WINDOW (window3), GTK_WIN_POS_MOUSE);
  gtk_window_set_decorated (GTK_WINDOW (window3), FALSE);
  gtk_window_set_type_hint (GTK_WINDOW (window3), GDK_WINDOW_TYPE_HINT_MENU);

  vbox27 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox27);
  gtk_container_add (GTK_CONTAINER (window3), vbox27);

  vbox26 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox26);
  gtk_box_pack_start (GTK_BOX (vbox27), vbox26, TRUE, TRUE, 0);

  label104 = gtk_label_new (_("--"));
  gtk_widget_show (label104);
  gtk_box_pack_start (GTK_BOX (vbox26), label104, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label104), 0, 0.5);

  eventbox1 = gtk_event_box_new ();
  gtk_widget_show (eventbox1);
  gtk_box_pack_start (GTK_BOX (vbox26), eventbox1, TRUE, TRUE, 0);

  drawingarea2 = gtk_drawing_area_new ();
  gtk_widget_show (drawingarea2);
  gtk_container_add (GTK_CONTAINER (eventbox1), drawingarea2);
  gtk_widget_set_size_request (drawingarea2, 240, 180);
  gtk_widget_set_events (drawingarea2, GDK_EXPOSURE_MASK);

  hbox26 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox26);
  gtk_box_pack_start (GTK_BOX (vbox27), hbox26, FALSE, FALSE, 0);

  button21 = gtk_button_new_with_mnemonic (_("Big"));
  gtk_widget_show (button21);
  gtk_box_pack_start (GTK_BOX (hbox26), button21, TRUE, TRUE, 0);

  button29 = gtk_button_new_with_mnemonic (_("Go To"));
  gtk_widget_show (button29);
  gtk_box_pack_start (GTK_BOX (hbox26), button29, TRUE, TRUE, 0);

  g_signal_connect ((gpointer) window3, "delete_event",
                    G_CALLBACK (on_window3_delete_event),
                    NULL);
  g_signal_connect ((gpointer) eventbox1, "button_release_event",
                    G_CALLBACK (on_eventbox1_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea2, "configure_event",
                    G_CALLBACK (on_drawingarea2_configure_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea2, "expose_event",
                    G_CALLBACK (on_drawingarea2_expose_event),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window3, window3, "window3");
  GLADE_HOOKUP_OBJECT (window3, vbox27, "vbox27");
  GLADE_HOOKUP_OBJECT (window3, vbox26, "vbox26");
  GLADE_HOOKUP_OBJECT (window3, label104, "label104");
  GLADE_HOOKUP_OBJECT (window3, eventbox1, "eventbox1");
  GLADE_HOOKUP_OBJECT (window3, drawingarea2, "drawingarea2");
  GLADE_HOOKUP_OBJECT (window3, hbox26, "hbox26");
  GLADE_HOOKUP_OBJECT (window3, button21, "button21");
  GLADE_HOOKUP_OBJECT (window3, button29, "button29");

  gtk_widget_grab_focus (button21);
  return window3;
}

GtkWidget*
create_window6 (void)
{
  GtkWidget *window6;
  GtkWidget *vbox33;
  GtkWidget *scrolledwindow5;
  GtkWidget *viewport3;
  GtkWidget *vbox28;
  GtkWidget *hbox21;
  GtkWidget *radiobutton12;
  GSList *radiobutton12_group = NULL;
  GtkWidget *radiobutton11;
  GtkWidget *label181;
  GtkWidget *hbox20;
  GtkWidget *label108;
  GtkWidget *entry14;
  GtkWidget *label109;
  GtkWidget *entry15;
  GtkWidget *button28;
  GtkWidget *label107;
  GtkWidget *combobox2;
  GtkWidget *combobox3;
  GtkWidget *label105;
  GtkWidget *entry13;
  GtkWidget *label106;
  GtkWidget *scrolledwindow3;
  GtkWidget *textview1;
  GtkWidget *hbox19;
  GtkWidget *radiobutton8;
  GSList *radiobutton8_group = NULL;
  GtkWidget *radiobutton9;
  GtkWidget *radiobutton10;
  GtkWidget *checkbutton10;
  GtkWidget *toolbar2;
  GtkIconSize tmp_toolbar_icon_size;
  GtkWidget *toolitem8;
  GtkWidget *toolitem7;
  GtkWidget *label118;
  GtkWidget *toolitem9;
  GtkWidget *button25;
  GtkWidget *toolitem10;
  GtkWidget *button24;

  window6 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window6), _("Add POI"));
  gtk_window_set_default_size (GTK_WINDOW (window6), 470, 470);

  vbox33 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox33);
  gtk_container_add (GTK_CONTAINER (window6), vbox33);

  scrolledwindow5 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow5);
  gtk_box_pack_start (GTK_BOX (vbox33), scrolledwindow5, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow5), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

  viewport3 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport3);
  gtk_container_add (GTK_CONTAINER (scrolledwindow5), viewport3);
  gtk_container_set_border_width (GTK_CONTAINER (viewport3), 5);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport3), GTK_SHADOW_NONE);

  vbox28 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox28);
  gtk_container_add (GTK_CONTAINER (viewport3), vbox28);

  hbox21 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox21);
  gtk_box_pack_start (GTK_BOX (vbox28), hbox21, TRUE, TRUE, 0);

  radiobutton12 = gtk_radio_button_new_with_mnemonic (NULL, _("personal"));
  gtk_widget_show (radiobutton12);
  gtk_box_pack_start (GTK_BOX (hbox21), radiobutton12, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton12), radiobutton12_group);
  radiobutton12_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton12));

  radiobutton11 = gtk_radio_button_new_with_mnemonic (NULL, _("public"));
  gtk_widget_show (radiobutton11);
  gtk_box_pack_start (GTK_BOX (hbox21), radiobutton11, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (radiobutton11), 2);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton11), radiobutton12_group);
  radiobutton12_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton11));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton11), TRUE);

  label181 = gtk_label_new (_("Coordinates <b><i>clicked</i></b> on the map:"));
  gtk_widget_show (label181);
  gtk_box_pack_start (GTK_BOX (vbox28), label181, FALSE, FALSE, 4);
  gtk_label_set_use_markup (GTK_LABEL (label181), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label181), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label181), 0, 4);

  hbox20 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox20);
  gtk_box_pack_start (GTK_BOX (vbox28), hbox20, TRUE, TRUE, 0);

  label108 = gtk_label_new (_("Lat: "));
  gtk_widget_show (label108);
  gtk_box_pack_start (GTK_BOX (hbox20), label108, FALSE, FALSE, 0);
  gtk_misc_set_padding (GTK_MISC (label108), 1, 0);

  entry14 = gtk_entry_new ();
  gtk_widget_show (entry14);
  gtk_box_pack_start (GTK_BOX (hbox20), entry14, TRUE, TRUE, 0);
  gtk_entry_set_width_chars (GTK_ENTRY (entry14), 5);

  label109 = gtk_label_new (_(" Lon: "));
  gtk_widget_show (label109);
  gtk_box_pack_start (GTK_BOX (hbox20), label109, FALSE, FALSE, 0);
  gtk_misc_set_padding (GTK_MISC (label109), 1, 0);

  entry15 = gtk_entry_new ();
  gtk_widget_show (entry15);
  gtk_box_pack_start (GTK_BOX (hbox20), entry15, TRUE, TRUE, 0);
  gtk_entry_set_width_chars (GTK_ENTRY (entry15), 5);

  button28 = gtk_button_new_with_mnemonic (_("Use current GPS position instead"));
  gtk_widget_show (button28);
  gtk_box_pack_start (GTK_BOX (vbox28), button28, FALSE, FALSE, 5);

  label107 = gtk_label_new (_("Category:"));
  gtk_widget_show (label107);
  gtk_box_pack_start (GTK_BOX (vbox28), label107, FALSE, FALSE, 7);
  gtk_misc_set_alignment (GTK_MISC (label107), 0, 0.5);

  combobox2 = gtk_combo_box_new_text ();
  gtk_widget_show (combobox2);
  gtk_box_pack_start (GTK_BOX (vbox28), combobox2, FALSE, TRUE, 1);
  GTK_WIDGET_SET_FLAGS (combobox2, GTK_CAN_FOCUS);
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("- please choose -"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Accomodation"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Businesses"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Car"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Cultural"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Medical"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Cafe / Pub / Nightlife"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Place of Worship"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Public Transportation"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Restaurant & Food"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Services"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Sights & Leisure"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Shopping"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("Sport"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox2), _("My Personal Places"));
  gtk_combo_box_set_add_tearoffs (GTK_COMBO_BOX (combobox2), TRUE);

  combobox3 = gtk_combo_box_new_text ();
  gtk_box_pack_start (GTK_BOX (vbox28), combobox3, FALSE, TRUE, 0);

  label105 = gtk_label_new (_("Name - Keywords / Tags:"));
  gtk_widget_show (label105);
  gtk_box_pack_start (GTK_BOX (vbox28), label105, FALSE, FALSE, 7);
  gtk_misc_set_alignment (GTK_MISC (label105), 0, 0.5);

  entry13 = gtk_entry_new ();
  gtk_widget_show (entry13);
  gtk_box_pack_start (GTK_BOX (vbox28), entry13, FALSE, FALSE, 0);

  label106 = gtk_label_new (_("Description:"));
  gtk_widget_show (label106);
  gtk_box_pack_start (GTK_BOX (vbox28), label106, FALSE, FALSE, 7);
  gtk_misc_set_alignment (GTK_MISC (label106), 0, 0.5);

  scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow3);
  gtk_box_pack_start (GTK_BOX (vbox28), scrolledwindow3, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow3), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow3), GTK_SHADOW_IN);

  textview1 = gtk_text_view_new ();
  gtk_widget_show (textview1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow3), textview1);
  gtk_widget_set_size_request (textview1, 300, -1);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview1), GTK_WRAP_WORD);
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview1), 2);

  hbox19 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox19);
  gtk_box_pack_start (GTK_BOX (vbox28), hbox19, TRUE, TRUE, 0);

  radiobutton8 = gtk_radio_button_new_with_mnemonic (NULL, _("budget"));
  gtk_widget_show (radiobutton8);
  gtk_box_pack_start (GTK_BOX (hbox19), radiobutton8, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton8), radiobutton8_group);
  radiobutton8_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton8));

  radiobutton9 = gtk_radio_button_new_with_mnemonic (NULL, _("medium"));
  gtk_widget_show (radiobutton9);
  gtk_box_pack_start (GTK_BOX (hbox19), radiobutton9, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton9), radiobutton8_group);
  radiobutton8_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton9));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton9), TRUE);

  radiobutton10 = gtk_radio_button_new_with_mnemonic (NULL, _("exclusive"));
  gtk_widget_show (radiobutton10);
  gtk_box_pack_start (GTK_BOX (hbox19), radiobutton10, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton10), radiobutton8_group);
  radiobutton8_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton10));

  checkbutton10 = gtk_check_button_new_with_mnemonic (_("extended opening hours"));
  gtk_widget_show (checkbutton10);
  gtk_box_pack_start (GTK_BOX (vbox28), checkbutton10, FALSE, FALSE, 0);

  toolbar2 = gtk_toolbar_new ();
  gtk_widget_show (toolbar2);
  gtk_box_pack_start (GTK_BOX (vbox33), toolbar2, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (toolbar2), 6);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar2), GTK_TOOLBAR_ICONS);
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar2));

  toolitem8 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem8);
  gtk_container_add (GTK_CONTAINER (toolbar2), toolitem8);

  toolitem7 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem7);
  gtk_container_add (GTK_CONTAINER (toolbar2), toolitem7);

  label118 = gtk_label_new (_("       "));
  gtk_widget_show (label118);
  gtk_container_add (GTK_CONTAINER (toolitem7), label118);

  toolitem9 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem9);
  gtk_container_add (GTK_CONTAINER (toolbar2), toolitem9);

  button25 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (button25);
  gtk_container_add (GTK_CONTAINER (toolitem9), button25);
  gtk_container_set_border_width (GTK_CONTAINER (button25), 7);

  toolitem10 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem10);
  gtk_container_add (GTK_CONTAINER (toolbar2), toolitem10);

  button24 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (button24);
  gtk_container_add (GTK_CONTAINER (toolitem10), button24);
  gtk_container_set_border_width (GTK_CONTAINER (button24), 7);

  g_signal_connect ((gpointer) button28, "clicked",
                    G_CALLBACK (on_button28_clicked),
                    NULL);
  g_signal_connect ((gpointer) combobox2, "changed",
                    G_CALLBACK (on_combobox2_changed),
                    NULL);
  g_signal_connect ((gpointer) button25, "clicked",
                    G_CALLBACK (on_cancelbutton4_clicked),
                    NULL);
  g_signal_connect ((gpointer) button24, "clicked",
                    G_CALLBACK (on_okbutton4_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window6, window6, "window6");
  GLADE_HOOKUP_OBJECT (window6, vbox33, "vbox33");
  GLADE_HOOKUP_OBJECT (window6, scrolledwindow5, "scrolledwindow5");
  GLADE_HOOKUP_OBJECT (window6, viewport3, "viewport3");
  GLADE_HOOKUP_OBJECT (window6, vbox28, "vbox28");
  GLADE_HOOKUP_OBJECT (window6, hbox21, "hbox21");
  GLADE_HOOKUP_OBJECT (window6, radiobutton12, "radiobutton12");
  GLADE_HOOKUP_OBJECT (window6, radiobutton11, "radiobutton11");
  GLADE_HOOKUP_OBJECT (window6, label181, "label181");
  GLADE_HOOKUP_OBJECT (window6, hbox20, "hbox20");
  GLADE_HOOKUP_OBJECT (window6, label108, "label108");
  GLADE_HOOKUP_OBJECT (window6, entry14, "entry14");
  GLADE_HOOKUP_OBJECT (window6, label109, "label109");
  GLADE_HOOKUP_OBJECT (window6, entry15, "entry15");
  GLADE_HOOKUP_OBJECT (window6, button28, "button28");
  GLADE_HOOKUP_OBJECT (window6, label107, "label107");
  GLADE_HOOKUP_OBJECT (window6, combobox2, "combobox2");
  GLADE_HOOKUP_OBJECT (window6, combobox3, "combobox3");
  GLADE_HOOKUP_OBJECT (window6, label105, "label105");
  GLADE_HOOKUP_OBJECT (window6, entry13, "entry13");
  GLADE_HOOKUP_OBJECT (window6, label106, "label106");
  GLADE_HOOKUP_OBJECT (window6, scrolledwindow3, "scrolledwindow3");
  GLADE_HOOKUP_OBJECT (window6, textview1, "textview1");
  GLADE_HOOKUP_OBJECT (window6, hbox19, "hbox19");
  GLADE_HOOKUP_OBJECT (window6, radiobutton8, "radiobutton8");
  GLADE_HOOKUP_OBJECT (window6, radiobutton9, "radiobutton9");
  GLADE_HOOKUP_OBJECT (window6, radiobutton10, "radiobutton10");
  GLADE_HOOKUP_OBJECT (window6, checkbutton10, "checkbutton10");
  GLADE_HOOKUP_OBJECT (window6, toolbar2, "toolbar2");
  GLADE_HOOKUP_OBJECT (window6, toolitem8, "toolitem8");
  GLADE_HOOKUP_OBJECT (window6, toolitem7, "toolitem7");
  GLADE_HOOKUP_OBJECT (window6, label118, "label118");
  GLADE_HOOKUP_OBJECT (window6, toolitem9, "toolitem9");
  GLADE_HOOKUP_OBJECT (window6, button25, "button25");
  GLADE_HOOKUP_OBJECT (window6, toolitem10, "toolitem10");
  GLADE_HOOKUP_OBJECT (window6, button24, "button24");

  gtk_widget_grab_focus (radiobutton11);
  return window6;
}

GtkWidget*
create_window8 (void)
{
  GtkWidget *window8;
  GtkWidget *vbox34;
  GtkWidget *scrolledwindow15;
  GtkWidget *viewport9;
  GtkWidget *vbox35;
  GtkWidget *label119;
  GtkWidget *hseparator2;
  GtkWidget *button26;

  window8 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window8, 390, 400);
  gtk_window_set_title (GTK_WINDOW (window8), _("Friend Info"));
  gtk_window_set_position (GTK_WINDOW (window8), GTK_WIN_POS_MOUSE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (window8), TRUE);
  gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window8), TRUE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (window8), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (window8), GDK_WINDOW_TYPE_HINT_DIALOG);

  vbox34 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox34);
  gtk_container_add (GTK_CONTAINER (window8), vbox34);

  scrolledwindow15 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow15);
  gtk_box_pack_start (GTK_BOX (vbox34), scrolledwindow15, TRUE, TRUE, 9);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow15), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  viewport9 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport9);
  gtk_container_add (GTK_CONTAINER (scrolledwindow15), viewport9);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport9), GTK_SHADOW_NONE);

  vbox35 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox35);
  gtk_container_add (GTK_CONTAINER (viewport9), vbox35);

  label119 = gtk_label_new (_("--"));
  gtk_widget_show (label119);
  gtk_box_pack_start (GTK_BOX (vbox35), label119, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label119), TRUE);
  gtk_label_set_line_wrap (GTK_LABEL (label119), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label119), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label119), 4, 2);

  hseparator2 = gtk_hseparator_new ();
  gtk_widget_show (hseparator2);
  gtk_box_pack_start (GTK_BOX (vbox35), hseparator2, FALSE, FALSE, 0);

  button26 = gtk_button_new_with_mnemonic (_("Close"));
  gtk_widget_show (button26);
  gtk_box_pack_start (GTK_BOX (vbox34), button26, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) button26, "clicked",
                    G_CALLBACK (on_button26_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window8, window8, "window8");
  GLADE_HOOKUP_OBJECT (window8, vbox34, "vbox34");
  GLADE_HOOKUP_OBJECT (window8, scrolledwindow15, "scrolledwindow15");
  GLADE_HOOKUP_OBJECT (window8, viewport9, "viewport9");
  GLADE_HOOKUP_OBJECT (window8, vbox35, "vbox35");
  GLADE_HOOKUP_OBJECT (window8, label119, "label119");
  GLADE_HOOKUP_OBJECT (window8, hseparator2, "hseparator2");
  GLADE_HOOKUP_OBJECT (window8, button26, "button26");

  return window8;
}

GtkWidget*
create_win13_biggeo (void)
{
  GtkWidget *win13_biggeo;
  GtkWidget *eventbox2;
  GtkWidget *drawingarea3;

  win13_biggeo = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (win13_biggeo), _("GeoPhoto"));
  gtk_window_set_position (GTK_WINDOW (win13_biggeo), GTK_WIN_POS_MOUSE);
  gtk_window_set_type_hint (GTK_WINDOW (win13_biggeo), GDK_WINDOW_TYPE_HINT_MENU);

  eventbox2 = gtk_event_box_new ();
  gtk_widget_show (eventbox2);
  gtk_container_add (GTK_CONTAINER (win13_biggeo), eventbox2);

  drawingarea3 = gtk_drawing_area_new ();
  gtk_widget_show (drawingarea3);
  gtk_container_add (GTK_CONTAINER (eventbox2), drawingarea3);
  gtk_widget_set_size_request (drawingarea3, 640, 480);

  g_signal_connect ((gpointer) eventbox2, "button_release_event",
                    G_CALLBACK (on_eventbox2_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea3, "configure_event",
                    G_CALLBACK (on_drawingarea3_configure_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea3, "expose_event",
                    G_CALLBACK (on_drawingarea3_expose_event),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (win13_biggeo, win13_biggeo, "win13_biggeo");
  GLADE_HOOKUP_OBJECT (win13_biggeo, eventbox2, "eventbox2");
  GLADE_HOOKUP_OBJECT (win13_biggeo, drawingarea3, "drawingarea3");

  return win13_biggeo;
}

GtkWidget*
create_dialog_geocode (void)
{
  GtkWidget *dialog_geocode;
  GtkWidget *dialog_vbox9;
  GtkWidget *vbox42;
  GtkWidget *label148;
  GtkWidget *scrolledwindow12;
  GtkWidget *textview5;
  GtkWidget *table7;
  GtkWidget *label149;
  GtkWidget *label150;
  GtkWidget *button39;
  GtkWidget *button40;
  GtkWidget *label154;
  GtkWidget *label155;
  GtkWidget *label156;
  GtkWidget *label157;
  GtkWidget *button44;
  GtkWidget *label172;
  GtkWidget *label174;
  GtkWidget *label173;
  GtkWidget *label158;
  GtkWidget *hbox38;
  GtkWidget *label160;
  GtkWidget *checkbutton14;
  GtkWidget *label161;
  GtkWidget *dialog_action_area10;
  GtkWidget *cancelbutton8;
  GtkWidget *okbutton8;

  dialog_geocode = gtk_dialog_new ();
  gtk_widget_set_size_request (dialog_geocode, 380, -1);
  gtk_window_set_title (GTK_WINDOW (dialog_geocode), _("Photo Correlate"));

  dialog_vbox9 = GTK_DIALOG (dialog_geocode)->vbox;
  gtk_widget_show (dialog_vbox9);

  vbox42 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox42);
  gtk_box_pack_start (GTK_BOX (dialog_vbox9), vbox42, TRUE, TRUE, 0);

  label148 = gtk_label_new (_("<b>Geocoding your photos</b>"));
  gtk_widget_show (label148);
  gtk_box_pack_start (GTK_BOX (vbox42), label148, FALSE, FALSE, 8);
  gtk_label_set_use_markup (GTK_LABEL (label148), TRUE);

  scrolledwindow12 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow12);
  gtk_box_pack_start (GTK_BOX (vbox42), scrolledwindow12, FALSE, FALSE, 7);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow12), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

  textview5 = gtk_text_view_new ();
  gtk_widget_show (textview5);
  gtk_container_add (GTK_CONTAINER (scrolledwindow12), textview5);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview5), FALSE);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview5), GTK_WRAP_WORD);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview5), FALSE);
  gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textview5), 3);
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview5), 5);
  gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview5)), _("Geocode your photos by correlating them with a gps track.\n"), -1);

  table7 = gtk_table_new (5, 3, FALSE);
  gtk_widget_show (table7);
  gtk_box_pack_start (GTK_BOX (vbox42), table7, FALSE, FALSE, 2);

  label149 = gtk_label_new (_("  <b>1. Add Track</b>        "));
  gtk_widget_show (label149);
  gtk_table_attach (GTK_TABLE (table7), label149, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label149), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label149), 0, 0.5);

  label150 = gtk_label_new (_("  <b>2. Add Photos</b> "));
  gtk_widget_show (label150);
  gtk_table_attach (GTK_TABLE (table7), label150, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label150), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label150), 0, 0.5);

  button39 = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_show (button39);
  gtk_table_attach (GTK_TABLE (table7), button39, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 5, 5);

  button40 = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_show (button40);
  gtk_table_attach (GTK_TABLE (table7), button40, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND), 5, 5);

  label154 = gtk_label_new (_("  <span color=\"red\" weight=\"bold\">-</span>"));
  gtk_widget_show (label154);
  gtk_table_attach (GTK_TABLE (table7), label154, 2, 3, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label154), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label154), 0, 0.5);

  label155 = gtk_label_new (_("  <span color=\"red\" weight=\"bold\">-</span>"));
  gtk_widget_show (label155);
  gtk_table_attach (GTK_TABLE (table7), label155, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label155), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label155), 0, 0.5);

  label156 = gtk_label_new (_("       "));
  gtk_widget_show (label156);
  gtk_table_attach (GTK_TABLE (table7), label156, 2, 3, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label156), 0, 0.5);

  label157 = gtk_label_new (_("  <b>3. Adjust Time</b>"));
  gtk_widget_show (label157);
  gtk_table_attach (GTK_TABLE (table7), label157, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label157), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label157), 0, 0.5);

  button44 = gtk_button_new_with_mnemonic (_("View GPS Photo"));
  gtk_widget_show (button44);
  gtk_table_attach (GTK_TABLE (table7), button44, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 5, 5);
  gtk_widget_set_sensitive (button44, FALSE);

  label172 = gtk_label_new (_("  +00:00h"));
  gtk_widget_show (label172);
  gtk_table_attach (GTK_TABLE (table7), label172, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label172), 0, 0.5);

  label174 = gtk_label_new (_("  0 seconds"));
  gtk_widget_show (label174);
  gtk_table_attach (GTK_TABLE (table7), label174, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label174), 0, 0.5);

  label173 = gtk_label_new (_("Correction:"));
  gtk_widget_show (label173);
  gtk_table_attach (GTK_TABLE (table7), label173, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label173), 1, 0);

  label158 = gtk_label_new (_("Timezone:"));
  gtk_widget_show (label158);
  gtk_table_attach (GTK_TABLE (table7), label158, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label158), 1, 0);

  hbox38 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox38);
  gtk_box_pack_start (GTK_BOX (vbox42), hbox38, FALSE, FALSE, 12);

  label160 = gtk_label_new ("");
  gtk_widget_show (label160);
  gtk_box_pack_start (GTK_BOX (hbox38), label160, FALSE, TRUE, 0);

  checkbutton14 = gtk_check_button_new_with_mnemonic (_("  add photos to the foxtrotGPS database"));
  gtk_widget_show (checkbutton14);
  gtk_box_pack_start (GTK_BOX (hbox38), checkbutton14, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton14), TRUE);

  label161 = gtk_label_new ("");
  gtk_widget_show (label161);
  gtk_box_pack_start (GTK_BOX (hbox38), label161, TRUE, TRUE, 0);

  dialog_action_area10 = GTK_DIALOG (dialog_geocode)->action_area;
  gtk_widget_show (dialog_action_area10);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area10), GTK_BUTTONBOX_END);

  cancelbutton8 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton8);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog_geocode), cancelbutton8, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton8, GTK_CAN_DEFAULT);

  okbutton8 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton8);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog_geocode), okbutton8, GTK_RESPONSE_OK);
  gtk_widget_set_sensitive (okbutton8, FALSE);
  GTK_WIDGET_SET_FLAGS (okbutton8, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) dialog_geocode, "delete_event",
                    G_CALLBACK (on_dialog_geocode_delete_event),
                    NULL);
  g_signal_connect ((gpointer) button39, "clicked",
                    G_CALLBACK (on_button39_clicked),
                    NULL);
  g_signal_connect ((gpointer) button40, "clicked",
                    G_CALLBACK (on_button40_clicked),
                    NULL);
  g_signal_connect ((gpointer) button44, "clicked",
                    G_CALLBACK (on_button44_clicked),
                    NULL);
  g_signal_connect ((gpointer) checkbutton14, "toggled",
                    G_CALLBACK (on_checkbutton14_toggled),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton8, "clicked",
                    G_CALLBACK (on_cancelbutton8_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton8, "clicked",
                    G_CALLBACK (on_okbutton8_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_geocode, dialog_geocode, "dialog_geocode");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_geocode, dialog_vbox9, "dialog_vbox9");
  GLADE_HOOKUP_OBJECT (dialog_geocode, vbox42, "vbox42");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label148, "label148");
  GLADE_HOOKUP_OBJECT (dialog_geocode, scrolledwindow12, "scrolledwindow12");
  GLADE_HOOKUP_OBJECT (dialog_geocode, textview5, "textview5");
  GLADE_HOOKUP_OBJECT (dialog_geocode, table7, "table7");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label149, "label149");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label150, "label150");
  GLADE_HOOKUP_OBJECT (dialog_geocode, button39, "button39");
  GLADE_HOOKUP_OBJECT (dialog_geocode, button40, "button40");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label154, "label154");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label155, "label155");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label156, "label156");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label157, "label157");
  GLADE_HOOKUP_OBJECT (dialog_geocode, button44, "button44");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label172, "label172");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label174, "label174");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label173, "label173");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label158, "label158");
  GLADE_HOOKUP_OBJECT (dialog_geocode, hbox38, "hbox38");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label160, "label160");
  GLADE_HOOKUP_OBJECT (dialog_geocode, checkbutton14, "checkbutton14");
  GLADE_HOOKUP_OBJECT (dialog_geocode, label161, "label161");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_geocode, dialog_action_area10, "dialog_action_area10");
  GLADE_HOOKUP_OBJECT (dialog_geocode, cancelbutton8, "cancelbutton8");
  GLADE_HOOKUP_OBJECT (dialog_geocode, okbutton8, "okbutton8");

  gtk_widget_grab_focus (button39);
  return dialog_geocode;
}

GtkWidget*
create_dialog_image_data (void)
{
  GtkWidget *dialog_image_data;
  GtkWidget *vbox44;
  GtkWidget *vbox43;
  GtkWidget *hbox39;
  GtkWidget *button47;
  GtkWidget *button45;
  GtkWidget *button50;
  GtkWidget *button46;
  GtkWidget *button48;
  GtkWidget *scrolledwindow13;
  GtkWidget *viewport8;
  GtkWidget *eventbox3;
  GtkWidget *image5;
  GtkWidget *hbox43;
  GtkWidget *hbox45;
  GtkWidget *label170;
  GtkWidget *label171;
  GtkWidget *hbox44;
  GtkWidget *label167;
  GtkWidget *label163;
  GtkWidget *hbox42;
  GtkWidget *hbox46;
  GtkWidget *label164;
  GtkWidget *entry28;
  GtkWidget *label168;
  GtkWidget *hbox47;
  GtkWidget *label175;
  GtkWidget *combobox7;
  GtkWidget *hseparator1;
  GtkWidget *hbox41;
  GtkWidget *label165;
  GtkWidget *button49;
  GtkWidget *okbutton9;

  dialog_image_data = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (dialog_image_data, 450, 460);
  gtk_window_set_title (GTK_WINDOW (dialog_image_data), _("Image Data"));
  gtk_window_set_position (GTK_WINDOW (dialog_image_data), GTK_WIN_POS_MOUSE);

  vbox44 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox44);
  gtk_container_add (GTK_CONTAINER (dialog_image_data), vbox44);

  vbox43 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox43);
  gtk_box_pack_start (GTK_BOX (vbox44), vbox43, TRUE, TRUE, 0);

  hbox39 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox39);
  gtk_box_pack_start (GTK_BOX (vbox43), hbox39, FALSE, FALSE, 0);

  button47 = gtk_button_new_from_stock ("gtk-goto-first");
  gtk_widget_show (button47);
  gtk_box_pack_start (GTK_BOX (hbox39), button47, TRUE, TRUE, 0);

  button45 = gtk_button_new_from_stock ("gtk-go-back");
  gtk_widget_show (button45);
  gtk_box_pack_start (GTK_BOX (hbox39), button45, TRUE, TRUE, 0);

  button50 = gtk_button_new_from_stock ("gtk-zoom-in");
  gtk_widget_show (button50);
  gtk_box_pack_start (GTK_BOX (hbox39), button50, TRUE, TRUE, 0);

  button46 = gtk_button_new_from_stock ("gtk-go-forward");
  gtk_widget_show (button46);
  gtk_box_pack_start (GTK_BOX (hbox39), button46, TRUE, TRUE, 0);

  button48 = gtk_button_new_from_stock ("gtk-goto-last");
  gtk_widget_show (button48);
  gtk_box_pack_start (GTK_BOX (hbox39), button48, TRUE, TRUE, 0);

  scrolledwindow13 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow13);
  gtk_box_pack_start (GTK_BOX (vbox43), scrolledwindow13, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow13), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  viewport8 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport8);
  gtk_container_add (GTK_CONTAINER (scrolledwindow13), viewport8);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport8), GTK_SHADOW_NONE);

  eventbox3 = gtk_event_box_new ();
  gtk_widget_show (eventbox3);
  gtk_container_add (GTK_CONTAINER (viewport8), eventbox3);

  image5 = create_pixmap (dialog_image_data, NULL);
  gtk_widget_show (image5);
  gtk_container_add (GTK_CONTAINER (eventbox3), image5);

  hbox43 = gtk_hbox_new (TRUE, 0);
  gtk_widget_show (hbox43);
  gtk_box_pack_start (GTK_BOX (vbox43), hbox43, FALSE, FALSE, 4);

  hbox45 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox45);
  gtk_box_pack_start (GTK_BOX (hbox43), hbox45, TRUE, TRUE, 0);

  label170 = gtk_label_new (_(" <b>GPS:</b> "));
  gtk_widget_show (label170);
  gtk_box_pack_start (GTK_BOX (hbox45), label170, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label170), TRUE);

  label171 = gtk_label_new (_("      "));
  gtk_widget_show (label171);
  gtk_box_pack_start (GTK_BOX (hbox45), label171, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label171), TRUE);

  hbox44 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox44);
  gtk_box_pack_start (GTK_BOX (hbox43), hbox44, TRUE, TRUE, 0);

  label167 = gtk_label_new (_(" <b>Camera:</b> "));
  gtk_widget_show (label167);
  gtk_box_pack_start (GTK_BOX (hbox44), label167, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label167), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label167), 0, 0.5);

  label163 = gtk_label_new (_("      "));
  gtk_widget_show (label163);
  gtk_box_pack_start (GTK_BOX (hbox44), label163, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label163), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label163), 0, 0.5);

  hbox42 = gtk_hbox_new (TRUE, 0);
  gtk_widget_show (hbox42);
  gtk_box_pack_start (GTK_BOX (vbox43), hbox42, FALSE, FALSE, 4);

  hbox46 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox46);
  gtk_box_pack_start (GTK_BOX (hbox42), hbox46, TRUE, TRUE, 0);

  label164 = gtk_label_new (_(" <b>Correction:</b> "));
  gtk_widget_show (label164);
  gtk_box_pack_start (GTK_BOX (hbox46), label164, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label164), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label164), 0.02, 0.5);

  entry28 = gtk_entry_new ();
  gtk_widget_show (entry28);
  gtk_box_pack_start (GTK_BOX (hbox46), entry28, FALSE, FALSE, 0);
  gtk_widget_set_size_request (entry28, 40, -1);
  gtk_entry_set_text (GTK_ENTRY (entry28), _("0"));
  gtk_entry_set_invisible_char (GTK_ENTRY (entry28), 9679);

  label168 = gtk_label_new (_("s   "));
  gtk_widget_show (label168);
  gtk_box_pack_start (GTK_BOX (hbox46), label168, FALSE, FALSE, 0);

  hbox47 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox47);
  gtk_box_pack_start (GTK_BOX (hbox42), hbox47, TRUE, TRUE, 0);

  label175 = gtk_label_new (_(" <b>Timezone:</b>  "));
  gtk_widget_show (label175);
  gtk_box_pack_start (GTK_BOX (hbox47), label175, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label175), TRUE);

  combobox7 = gtk_combo_box_new_text ();
  gtk_widget_show (combobox7);
  gtk_box_pack_start (GTK_BOX (hbox47), combobox7, FALSE, FALSE, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-12:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-11:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-10:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-09:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-08:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-07:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-06:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-05:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-04:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-03:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-02:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("-01:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+00:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+01:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+02:00 "));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+03:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+04:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+05:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+06:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+07:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+08:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+09:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+10:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+11:00"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox7), _("+12:00"));

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_show (hseparator1);
  gtk_box_pack_start (GTK_BOX (vbox44), hseparator1, FALSE, FALSE, 3);

  hbox41 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox41);
  gtk_box_pack_start (GTK_BOX (vbox44), hbox41, FALSE, FALSE, 0);

  label165 = gtk_label_new ("");
  gtk_widget_show (label165);
  gtk_box_pack_start (GTK_BOX (hbox41), label165, TRUE, TRUE, 0);
  gtk_widget_set_size_request (label165, 200, -1);

  button49 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (button49);
  gtk_box_pack_start (GTK_BOX (hbox41), button49, FALSE, TRUE, 5);
  gtk_widget_set_size_request (button49, 100, -1);
  gtk_container_set_border_width (GTK_CONTAINER (button49), 3);

  okbutton9 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton9);
  gtk_box_pack_start (GTK_BOX (hbox41), okbutton9, FALSE, FALSE, 5);
  gtk_widget_set_size_request (okbutton9, 100, -1);
  gtk_container_set_border_width (GTK_CONTAINER (okbutton9), 3);
  GTK_WIDGET_SET_FLAGS (okbutton9, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) dialog_image_data, "delete_event",
                    G_CALLBACK (on_dialog_image_data_delete_event),
                    NULL);
  g_signal_connect ((gpointer) button47, "clicked",
                    G_CALLBACK (on_button47_clicked),
                    NULL);
  g_signal_connect ((gpointer) button45, "clicked",
                    G_CALLBACK (on_button45_clicked),
                    NULL);
  g_signal_connect ((gpointer) button50, "clicked",
                    G_CALLBACK (on_button50_clicked),
                    NULL);
  g_signal_connect ((gpointer) button46, "clicked",
                    G_CALLBACK (on_button46_clicked),
                    NULL);
  g_signal_connect ((gpointer) button48, "clicked",
                    G_CALLBACK (on_button48_clicked),
                    NULL);
  g_signal_connect ((gpointer) eventbox3, "button_release_event",
                    G_CALLBACK (on_eventbox3_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) entry28, "changed",
                    G_CALLBACK (on_entry28_changed),
                    NULL);
  g_signal_connect ((gpointer) combobox7, "changed",
                    G_CALLBACK (on_combobox7_changed),
                    NULL);
  g_signal_connect ((gpointer) button49, "clicked",
                    G_CALLBACK (on_button49_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton9, "clicked",
                    G_CALLBACK (on_okbutton9_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_image_data, dialog_image_data, "dialog_image_data");
  GLADE_HOOKUP_OBJECT (dialog_image_data, vbox44, "vbox44");
  GLADE_HOOKUP_OBJECT (dialog_image_data, vbox43, "vbox43");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox39, "hbox39");
  GLADE_HOOKUP_OBJECT (dialog_image_data, button47, "button47");
  GLADE_HOOKUP_OBJECT (dialog_image_data, button45, "button45");
  GLADE_HOOKUP_OBJECT (dialog_image_data, button50, "button50");
  GLADE_HOOKUP_OBJECT (dialog_image_data, button46, "button46");
  GLADE_HOOKUP_OBJECT (dialog_image_data, button48, "button48");
  GLADE_HOOKUP_OBJECT (dialog_image_data, scrolledwindow13, "scrolledwindow13");
  GLADE_HOOKUP_OBJECT (dialog_image_data, viewport8, "viewport8");
  GLADE_HOOKUP_OBJECT (dialog_image_data, eventbox3, "eventbox3");
  GLADE_HOOKUP_OBJECT (dialog_image_data, image5, "image5");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox43, "hbox43");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox45, "hbox45");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label170, "label170");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label171, "label171");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox44, "hbox44");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label167, "label167");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label163, "label163");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox42, "hbox42");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox46, "hbox46");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label164, "label164");
  GLADE_HOOKUP_OBJECT (dialog_image_data, entry28, "entry28");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label168, "label168");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox47, "hbox47");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label175, "label175");
  GLADE_HOOKUP_OBJECT (dialog_image_data, combobox7, "combobox7");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hseparator1, "hseparator1");
  GLADE_HOOKUP_OBJECT (dialog_image_data, hbox41, "hbox41");
  GLADE_HOOKUP_OBJECT (dialog_image_data, label165, "label165");
  GLADE_HOOKUP_OBJECT (dialog_image_data, button49, "button49");
  GLADE_HOOKUP_OBJECT (dialog_image_data, okbutton9, "okbutton9");

  gtk_widget_grab_focus (button46);
  return dialog_image_data;
}

GtkWidget*
create_dialog_geocode_result (void)
{
  GtkWidget *dialog_geocode_result;
  GtkWidget *dialog_vbox11;
  GtkWidget *vbox46;
  GtkWidget *label178;
  GtkWidget *label177;
  GtkWidget *dialog_action_area12;
  GtkWidget *closebutton2;

  dialog_geocode_result = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog_geocode_result), _("Geocode Result"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog_geocode_result), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox11 = GTK_DIALOG (dialog_geocode_result)->vbox;
  gtk_widget_show (dialog_vbox11);

  vbox46 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox46);
  gtk_box_pack_start (GTK_BOX (dialog_vbox11), vbox46, FALSE, FALSE, 0);

  label178 = gtk_label_new (_("<b>The output from gpscorrelate:</b>"));
  gtk_widget_show (label178);
  gtk_box_pack_start (GTK_BOX (vbox46), label178, FALSE, FALSE, 7);
  gtk_label_set_use_markup (GTK_LABEL (label178), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label178), 0, 0.5);

  label177 = gtk_label_new (_("Working...."));
  gtk_widget_show (label177);
  gtk_box_pack_start (GTK_BOX (vbox46), label177, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label177), 0.02, 0.5);

  dialog_action_area12 = GTK_DIALOG (dialog_geocode_result)->action_area;
  gtk_widget_show (dialog_action_area12);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area12), GTK_BUTTONBOX_END);

  closebutton2 = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_show (closebutton2);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog_geocode_result), closebutton2, GTK_RESPONSE_CLOSE);
  GTK_WIDGET_SET_FLAGS (closebutton2, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) closebutton2, "clicked",
                    G_CALLBACK (on_closebutton2_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_geocode_result, dialog_geocode_result, "dialog_geocode_result");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_geocode_result, dialog_vbox11, "dialog_vbox11");
  GLADE_HOOKUP_OBJECT (dialog_geocode_result, vbox46, "vbox46");
  GLADE_HOOKUP_OBJECT (dialog_geocode_result, label178, "label178");
  GLADE_HOOKUP_OBJECT (dialog_geocode_result, label177, "label177");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog_geocode_result, dialog_action_area12, "dialog_action_area12");
  GLADE_HOOKUP_OBJECT (dialog_geocode_result, closebutton2, "closebutton2");

  return dialog_geocode_result;
}

GtkWidget*
create_dialog9 (void)
{
  GtkWidget *dialog9;
  GtkWidget *dialog_vbox12;
  GtkWidget *vbox49;
  GtkWidget *label188;
  GtkWidget *entry30;
  GtkWidget *dialog_action_area13;
  GtkWidget *cancelbutton9;
  GtkWidget *okbutton10;

  dialog9 = gtk_dialog_new ();
  gtk_widget_set_size_request (dialog9, 400, -1);
  gtk_window_set_title (GTK_WINDOW (dialog9), _("Message"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog9), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox12 = GTK_DIALOG (dialog9)->vbox;
  gtk_widget_show (dialog_vbox12);

  vbox49 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox49);
  gtk_box_pack_start (GTK_BOX (dialog_vbox12), vbox49, TRUE, TRUE, 0);

  label188 = gtk_label_new (_("Send Message to:"));
  gtk_widget_show (label188);
  gtk_box_pack_start (GTK_BOX (vbox49), label188, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label188), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label188), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label188), 0, 3);

  entry30 = gtk_entry_new ();
  gtk_widget_show (entry30);
  gtk_box_pack_start (GTK_BOX (vbox49), entry30, FALSE, FALSE, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry30), 9679);

  dialog_action_area13 = GTK_DIALOG (dialog9)->action_area;
  gtk_widget_show (dialog_action_area13);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area13), GTK_BUTTONBOX_END);

  cancelbutton9 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton9);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog9), cancelbutton9, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton9, GTK_CAN_DEFAULT);

  okbutton10 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton10);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog9), okbutton10, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton10, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) entry30, "activate",
                    G_CALLBACK (on_entry30_activate),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton9, "clicked",
                    G_CALLBACK (on_cancelbutton9_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog9, dialog9, "dialog9");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog9, dialog_vbox12, "dialog_vbox12");
  GLADE_HOOKUP_OBJECT (dialog9, vbox49, "vbox49");
  GLADE_HOOKUP_OBJECT (dialog9, label188, "label188");
  GLADE_HOOKUP_OBJECT (dialog9, entry30, "entry30");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog9, dialog_action_area13, "dialog_action_area13");
  GLADE_HOOKUP_OBJECT (dialog9, cancelbutton9, "cancelbutton9");
  GLADE_HOOKUP_OBJECT (dialog9, okbutton10, "okbutton10");

  return dialog9;
}

GtkWidget*
create_dialog10 (void)
{
  GtkWidget *dialog10;
  GtkWidget *dialog_vbox13;
  GtkWidget *vbox50;
  GtkWidget *table8;
  GtkWidget *entry31;
  GtkWidget *entry32;
  GtkWidget *button61;
  GtkWidget *label191;
  GtkWidget *label192;
  GtkWidget *button59;
  GtkWidget *button60;
  GtkWidget *label193;
  GtkWidget *label194;
  GtkWidget *combobox8;
  GtkWidget *label189;
  GtkWidget *label190;
  GtkWidget *dialog_action_area14;
  GtkWidget *cancelbutton10;
  GtkWidget *okbutton11;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  dialog10 = gtk_dialog_new ();
  gtk_widget_set_size_request (dialog10, 400, -1);
  gtk_window_set_title (GTK_WINDOW (dialog10), _("Get Route"));
  gtk_window_set_position (GTK_WINDOW (dialog10), GTK_WIN_POS_MOUSE);
  gtk_window_set_type_hint (GTK_WINDOW (dialog10), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox13 = GTK_DIALOG (dialog10)->vbox;
  gtk_widget_show (dialog_vbox13);

  vbox50 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox50);
  gtk_box_pack_start (GTK_BOX (dialog_vbox13), vbox50, TRUE, TRUE, 0);

  table8 = gtk_table_new (5, 4, FALSE);
  gtk_widget_show (table8);
  gtk_box_pack_start (GTK_BOX (vbox50), table8, TRUE, TRUE, 0);

  entry31 = gtk_entry_new ();
  gtk_widget_show (entry31);
  gtk_table_attach (GTK_TABLE (table8), entry31, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_text (GTK_ENTRY (entry31), _("Street,City,Country"));
  gtk_entry_set_invisible_char (GTK_ENTRY (entry31), 9679);

  entry32 = gtk_entry_new ();
  gtk_widget_show (entry32);
  gtk_table_attach (GTK_TABLE (table8), entry32, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry32), 9679);

  button61 = gtk_button_new_with_mnemonic (_(" GPS "));
  gtk_widget_show (button61);
  gtk_table_attach (GTK_TABLE (table8), button61, 3, 4, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_sensitive (button61, FALSE);

  label191 = gtk_label_new (_("<b>Start</b> "));
  gtk_widget_show (label191);
  gtk_table_attach (GTK_TABLE (table8), label191, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 3, 0);
  gtk_label_set_use_markup (GTK_LABEL (label191), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label191), 0, 0.5);

  label192 = gtk_label_new (_("<b>End</b>"));
  gtk_widget_show (label192);
  gtk_table_attach (GTK_TABLE (table8), label192, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 3, 0);
  gtk_label_set_use_markup (GTK_LABEL (label192), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label192), 0, 0.5);

  button59 = gtk_button_new_with_mnemonic (_(" Pick "));
  gtk_widget_show (button59);
  gtk_table_attach (GTK_TABLE (table8), button59, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 5, 5);
  gtk_tooltips_set_tip (tooltips, button59, _("Pick Start on Map"), NULL);

  button60 = gtk_button_new_with_mnemonic (_("Pick"));
  gtk_widget_show (button60);
  gtk_table_attach (GTK_TABLE (table8), button60, 2, 3, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 5, 5);
  gtk_tooltips_set_tip (tooltips, button60, _("Pick End on Map"), NULL);

  label193 = gtk_label_new (_("<b>Service </b>"));
  gtk_widget_show (label193);
  gtk_table_attach (GTK_TABLE (table8), label193, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label193), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label193), 0, 0.5);

  label194 = gtk_label_new (_("  "));
  gtk_widget_show (label194);
  gtk_table_attach (GTK_TABLE (table8), label194, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_size_request (label194, -1, 8);
  gtk_misc_set_alignment (GTK_MISC (label194), 0, 0.5);

  combobox8 = gtk_combo_box_new_text ();
  gtk_widget_show (combobox8);
  gtk_table_attach (GTK_TABLE (table8), combobox8, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND), 0, 0);
  gtk_widget_set_size_request (combobox8, 225, -1);
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox8), _("yournavigation.org"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox8), _("openrouteservice.org"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox8), _("gnuite.com"));

  label189 = gtk_label_new (_("<i>Insert Start and End:</i>\n<small>(experimental feature)</small>"));
  gtk_widget_show (label189);
  gtk_table_attach (GTK_TABLE (table8), label189, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 4);
  gtk_label_set_use_markup (GTK_LABEL (label189), TRUE);
  gtk_label_set_justify (GTK_LABEL (label189), GTK_JUSTIFY_CENTER);

  label190 = gtk_label_new (_("<i><b>Connecting...</b></i>"));
  gtk_widget_show (label190);
  gtk_box_pack_start (GTK_BOX (vbox50), label190, FALSE, FALSE, 5);
  gtk_label_set_use_markup (GTK_LABEL (label190), TRUE);
  gtk_label_set_justify (GTK_LABEL (label190), GTK_JUSTIFY_CENTER);

  dialog_action_area14 = GTK_DIALOG (dialog10)->action_area;
  gtk_widget_show (dialog_action_area14);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area14), GTK_BUTTONBOX_END);

  cancelbutton10 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton10);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog10), cancelbutton10, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton10, GTK_CAN_DEFAULT);

  okbutton11 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton11);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog10), okbutton11, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton11, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) dialog10, "delete_event",
                    G_CALLBACK (on_dialog10_delete_event),
                    NULL);
  g_signal_connect ((gpointer) entry32, "activate",
                    G_CALLBACK (on_entry32_activate),
                    NULL);
  g_signal_connect ((gpointer) button61, "clicked",
                    G_CALLBACK (on_button61_clicked),
                    NULL);
  g_signal_connect ((gpointer) button59, "clicked",
                    G_CALLBACK (on_button59_clicked),
                    NULL);
  g_signal_connect ((gpointer) button60, "clicked",
                    G_CALLBACK (on_button60_clicked),
                    NULL);
  g_signal_connect ((gpointer) combobox8, "changed",
                    G_CALLBACK (on_combobox8_changed),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton10, "clicked",
                    G_CALLBACK (on_cancelbutton10_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton11, "clicked",
                    G_CALLBACK (on_okbutton11_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog10, dialog10, "dialog10");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog10, dialog_vbox13, "dialog_vbox13");
  GLADE_HOOKUP_OBJECT (dialog10, vbox50, "vbox50");
  GLADE_HOOKUP_OBJECT (dialog10, table8, "table8");
  GLADE_HOOKUP_OBJECT (dialog10, entry31, "entry31");
  GLADE_HOOKUP_OBJECT (dialog10, entry32, "entry32");
  GLADE_HOOKUP_OBJECT (dialog10, button61, "button61");
  GLADE_HOOKUP_OBJECT (dialog10, label191, "label191");
  GLADE_HOOKUP_OBJECT (dialog10, label192, "label192");
  GLADE_HOOKUP_OBJECT (dialog10, button59, "button59");
  GLADE_HOOKUP_OBJECT (dialog10, button60, "button60");
  GLADE_HOOKUP_OBJECT (dialog10, label193, "label193");
  GLADE_HOOKUP_OBJECT (dialog10, label194, "label194");
  GLADE_HOOKUP_OBJECT (dialog10, combobox8, "combobox8");
  GLADE_HOOKUP_OBJECT (dialog10, label189, "label189");
  GLADE_HOOKUP_OBJECT (dialog10, label190, "label190");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog10, dialog_action_area14, "dialog_action_area14");
  GLADE_HOOKUP_OBJECT (dialog10, cancelbutton10, "cancelbutton10");
  GLADE_HOOKUP_OBJECT (dialog10, okbutton11, "okbutton11");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog10, tooltips, "tooltips");

  gtk_widget_grab_focus (entry31);
  return dialog10;
}

