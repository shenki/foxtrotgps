

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
create_window1 (void)
{
  GtkWidget *window1;
  GtkWidget *vbox1;
  GtkWidget *toolbar1;
  GtkIconSize tmp_toolbar_icon_size;
  GtkWidget *toolitem1;
  GtkWidget *button1;
  GtkWidget *image19;
  GtkWidget *toolitem2;
  GtkWidget *button4;
  GtkWidget *image20;
  GtkWidget *toolitem3;
  GtkWidget *button5;
  GtkWidget *image21;
  GtkWidget *toolitem5;
  GtkWidget *button77;
  GtkWidget *image22;
  GtkWidget *toolitem6;
  GtkWidget *button3;
  GtkWidget *image23;
  GtkWidget *hbox1;
  GtkWidget *hbox52;
  GtkWidget *toolbar4;
  GtkWidget *toolitem15;
  GtkWidget *button76;
  GtkWidget *image18;
  GtkWidget *toolitem24;
  GtkWidget *label184;
  GtkWidget *toolitem25;
  GtkWidget *button53;
  GtkWidget *image6;
  GtkWidget *toolitem18;
  GtkWidget *label199;
  GtkWidget *toolitem19;
  GtkWidget *button54;
  GtkWidget *image7;
  GtkWidget *toolitem20;
  GtkWidget *button55;
  GtkWidget *image8;
  GtkWidget *toolitem21;
  GtkWidget *label186;
  GtkWidget *toolitem22;
  GtkWidget *button56;
  GtkWidget *image9;
  GtkWidget *toolitem26;
  GtkWidget *label185;
  GtkWidget *toolitem31;
  GtkWidget *button57;
  GtkWidget *image10;
  GtkWidget *toolitem30;
  GtkWidget *button58;
  GtkWidget *image11;
  GtkWidget *drawingarea1;
  GtkWidget *vscale1;
  GtkWidget *vbox53;
  GtkWidget *hbox50;
  GtkWidget *button69;
  GtkWidget *image17;
  GtkWidget *button71;
  GtkWidget *image14;
  GtkWidget *button70;
  GtkWidget *alignment20;
  GtkWidget *hbox51;
  GtkWidget *image12;
  GtkWidget *label196;
  GtkWidget *hbox49a;
  GtkWidget *scrolledwindow6;
  GtkWidget *viewport10;
  GtkWidget *vbox4;
  GtkWidget *frame1;
  GtkWidget *vbox16;
  GtkWidget *hbox49;
  GtkWidget *label32;
  GtkWidget *label38;
  GtkWidget *alignment1;
  GtkWidget *table3;
  GtkWidget *label28;
  GtkWidget *label67;
  GtkWidget *label45;
  GtkWidget *label68;
  GtkWidget *label69;
  GtkWidget *label65;
  GtkWidget *label70;
  GtkWidget *label66;
  GtkWidget *hbox5;
  GtkWidget *button15;
  GtkWidget *button8;
  GtkWidget *label47;
  GtkWidget *frame2;
  GtkWidget *alignment2;
  GtkWidget *table4;
  GtkWidget *label33;
  GtkWidget *label36;
  GtkWidget *label30;
  GtkWidget *label35;
  GtkWidget *label37;
  GtkWidget *label39;
  GtkWidget *label42;
  GtkWidget *label41;
  GtkWidget *label31;
  GtkWidget *label43;
  GtkWidget *label48;
  GtkWidget *scrolledwindow2;
  GtkWidget *viewport2;
  GtkWidget *vbox5;
  GtkWidget *label200;
  GtkWidget *button35;
  GtkWidget *vbox48;
  GtkWidget *label132;
  GtkWidget *label187;
  GtkWidget *frame6;
  GtkWidget *alignment6;
  GtkWidget *vbox14;
  GtkWidget *hbox17;
  GtkWidget *label101;
  GtkWidget *label99;
  GtkWidget *hbox4;
  GtkWidget *label202;
  GtkWidget *entry16;
  GtkWidget *label113;
  GtkWidget *vbox8;
  GtkWidget *hbox14;
  GtkWidget *button11;
  GtkWidget *label97;
  GtkWidget *image24;
  GtkWidget *label51;
  GtkWidget *label61;
  GtkWidget *frame14;
  GtkWidget *alignment19;
  GtkWidget *vbox47;
  GtkWidget *label180;
  GtkWidget *radiobutton27;
  GSList *radiobutton27_group = NULL;
  GtkWidget *radiobutton28;
  GtkWidget *radiobutton29;
  GtkWidget *label182;
  GtkWidget *entry29;
  GtkWidget *label179;
  GtkWidget *frame5;
  GtkWidget *alignment5;
  GtkWidget *vbox13;
  GtkWidget *table5;
  GtkWidget *label57;
  GtkWidget *label58;
  GtkWidget *entry8;
  GtkWidget *entry7;
  GtkWidget *checkbutton15;
  GtkWidget *scrolledwindow14;
  GtkWidget *textview6;
  GtkWidget *hbox18;
  GtkWidget *label59;
  GtkWidget *entry9;
  GtkWidget *hbox15;
  GtkWidget *button13;
  GtkWidget *label62;
  GtkWidget *label56;
  GtkWidget *frame7;
  GtkWidget *alignment7;
  GtkWidget *vbox17;
  GtkWidget *label204;
  GtkWidget *checkbutton17;
  GtkWidget *checkbutton16;
  GtkWidget *label203;
  GtkWidget *hbox53;
  GtkWidget *button19;
  GtkWidget *label76;
  GtkWidget *hbox7;
  GtkWidget *button36;
  GtkWidget *button79;
  GtkWidget *button78;
  GtkWidget *hbox54;
  GtkWidget *button20;
  GtkWidget *label74;
  GtkWidget *scrolledwindow1;
  GtkWidget *viewport1;
  GtkWidget *vbox2;
  GtkWidget *label201;
  GtkWidget *label117;
  GtkWidget *frame9;
  GtkWidget *alignment9;
  GtkWidget *vbox19;
  GtkWidget *label81;
  GtkWidget *checkbutton2;
  GtkWidget *label80;
  GtkWidget *frame8;
  GtkWidget *alignment8;
  GtkWidget *vbox18;
  GtkWidget *label86;
  GtkWidget *hbox3;
  GtkWidget *combobox1;
  GtkWidget *hbox37;
  GtkWidget *button7;
  GtkWidget *label140;
  GtkWidget *button38;
  GtkWidget *table1;
  GtkWidget *label20;
  GtkWidget *checkbutton1;
  GtkWidget *label18;
  GtkWidget *label19;
  GtkWidget *entry2;
  GtkWidget *entry1;
  GtkWidget *hbox8;
  GtkWidget *button6;
  GtkWidget *label89;
  GtkWidget *label78;
  GtkWidget *frame11;
  GtkWidget *alignment11;
  GtkWidget *vbox32;
  GtkWidget *label114;
  GtkWidget *hbox22;
  GtkWidget *radiobutton14;
  GSList *radiobutton14_group = NULL;
  GtkWidget *radiobutton15;
  GtkWidget *radiobutton16;
  GtkWidget *label115;
  GtkWidget *hbox23;
  GtkWidget *radiobutton17;
  GSList *radiobutton17_group = NULL;
  GtkWidget *radiobutton18;
  GtkWidget *label116;
  GtkWidget *hbox24;
  GtkWidget *radiobutton19;
  GSList *radiobutton19_group = NULL;
  GtkWidget *radiobutton20;
  GtkWidget *radiobutton21;
  GtkWidget *label87;
  GtkWidget *frame12;
  GtkWidget *alignment12;
  GtkWidget *vbox22;
  GtkWidget *label91;
  GtkWidget *hbox2;
  GtkWidget *label21;
  GtkWidget *label22;
  GtkWidget *entry3;
  GtkWidget *label23;
  GtkWidget *entry4;
  GtkWidget *hbox10;
  GtkWidget *button9;
  GtkWidget *label92;
  GtkWidget *label90;
  GtkWidget *eventbox5;
  GtkWidget *label4;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window1), _("foxtrotGPS"));
  gtk_window_set_default_size (GTK_WINDOW (window1), 700, 480);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (window1), vbox1);

  toolbar1 = gtk_toolbar_new ();
  gtk_box_pack_start (GTK_BOX (vbox1), toolbar1, FALSE, FALSE, 0);
  gtk_widget_set_size_request (toolbar1, -1, 55);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar1), GTK_TOOLBAR_ICONS);
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar1));

  toolitem1 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem1);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem1);

  button1 = gtk_button_new ();
  gtk_widget_show (button1);
  gtk_container_add (GTK_CONTAINER (toolitem1), button1);
  gtk_widget_set_size_request (button1, 90, -1);
  GTK_WIDGET_UNSET_FLAGS (button1, GTK_CAN_FOCUS);
  gtk_button_set_focus_on_click (GTK_BUTTON (button1), FALSE);

  image19 = gtk_image_new_from_stock ("gtk-fullscreen", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image19);
  gtk_container_add (GTK_CONTAINER (button1), image19);

  toolitem2 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem2);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem2);

  button4 = gtk_button_new ();
  gtk_widget_show (button4);
  gtk_container_add (GTK_CONTAINER (toolitem2), button4);
  gtk_widget_set_size_request (button4, 90, -1);
  GTK_WIDGET_UNSET_FLAGS (button4, GTK_CAN_FOCUS);
  gtk_button_set_focus_on_click (GTK_BUTTON (button4), FALSE);

  image20 = gtk_image_new_from_stock ("gtk-zoom-in", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image20);
  gtk_container_add (GTK_CONTAINER (button4), image20);

  toolitem3 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem3);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem3);

  button5 = gtk_button_new ();
  gtk_widget_show (button5);
  gtk_container_add (GTK_CONTAINER (toolitem3), button5);
  gtk_widget_set_size_request (button5, 90, -1);
  GTK_WIDGET_UNSET_FLAGS (button5, GTK_CAN_FOCUS);
  gtk_button_set_focus_on_click (GTK_BUTTON (button5), FALSE);

  image21 = gtk_image_new_from_stock ("gtk-zoom-out", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image21);
  gtk_container_add (GTK_CONTAINER (button5), image21);

  toolitem5 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem5);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem5);

  button77 = gtk_button_new ();
  gtk_widget_show (button77);
  gtk_container_add (GTK_CONTAINER (toolitem5), button77);
  gtk_widget_set_size_request (button77, 90, -1);

  image22 = gtk_image_new_from_stock ("gtk-info", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image22);
  gtk_container_add (GTK_CONTAINER (button77), image22);

  toolitem6 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem6);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem6);

  button3 = gtk_button_new ();
  gtk_widget_show (button3);
  gtk_container_add (GTK_CONTAINER (toolitem6), button3);
  gtk_widget_set_size_request (button3, 90, -1);
  GTK_WIDGET_UNSET_FLAGS (button3, GTK_CAN_FOCUS);
  gtk_button_set_focus_on_click (GTK_BUTTON (button3), FALSE);

  image23 = gtk_image_new_from_stock ("gtk-jump-to", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image23);
  gtk_container_add (GTK_CONTAINER (button3), image23);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  hbox52 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox52);
  gtk_box_pack_start (GTK_BOX (hbox1), hbox52, TRUE, TRUE, 1);

  toolbar4 = gtk_toolbar_new ();
  gtk_box_pack_start (GTK_BOX (hbox52), toolbar4, FALSE, FALSE, 0);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar4), GTK_TOOLBAR_BOTH);
  gtk_toolbar_set_orientation (GTK_TOOLBAR (toolbar4), GTK_ORIENTATION_VERTICAL);
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar4));

  toolitem15 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem15);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem15);

  button76 = gtk_button_new ();
  gtk_widget_show (button76);
  gtk_container_add (GTK_CONTAINER (toolitem15), button76);
  gtk_widget_set_size_request (button76, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button76, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button76, _("Show Info"), NULL);

  image18 = gtk_image_new_from_stock ("gtk-info", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image18);
  gtk_container_add (GTK_CONTAINER (button76), image18);

  toolitem24 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem24);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem24);

  label184 = gtk_label_new ("");
  gtk_widget_show (label184);
  gtk_container_add (GTK_CONTAINER (toolitem24), label184);
  gtk_widget_set_size_request (label184, -1, 8);

  toolitem25 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem25);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem25);

  button53 = gtk_button_new ();
  gtk_widget_show (button53);
  gtk_container_add (GTK_CONTAINER (toolitem25), button53);
  gtk_widget_set_size_request (button53, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button53, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button53, _("Fullscreen (F11 or Space)"), NULL);
  gtk_button_set_focus_on_click (GTK_BUTTON (button53), FALSE);

  image6 = gtk_image_new_from_stock ("gtk-fullscreen", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image6);
  gtk_container_add (GTK_CONTAINER (button53), image6);

  toolitem18 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem18);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem18);

  label199 = gtk_label_new ("");
  gtk_widget_show (label199);
  gtk_container_add (GTK_CONTAINER (toolitem18), label199);
  gtk_widget_set_size_request (label199, -1, 8);

  toolitem19 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem19);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem19);

  button54 = gtk_button_new ();
  gtk_widget_show (button54);
  gtk_container_add (GTK_CONTAINER (toolitem19), button54);
  gtk_widget_set_size_request (button54, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button54, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button54, _("Zoom in"), NULL);
  gtk_button_set_focus_on_click (GTK_BUTTON (button54), FALSE);

  image7 = gtk_image_new_from_stock ("gtk-zoom-in", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image7);
  gtk_container_add (GTK_CONTAINER (button54), image7);

  toolitem20 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem20);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem20);

  button55 = gtk_button_new ();
  gtk_widget_show (button55);
  gtk_container_add (GTK_CONTAINER (toolitem20), button55);
  gtk_widget_set_size_request (button55, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button55, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button55, _("Zoom out"), NULL);
  gtk_button_set_focus_on_click (GTK_BUTTON (button55), FALSE);

  image8 = gtk_image_new_from_stock ("gtk-zoom-out", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image8);
  gtk_container_add (GTK_CONTAINER (button55), image8);

  toolitem21 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem21);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem21);

  label186 = gtk_label_new ("");
  gtk_widget_show (label186);
  gtk_container_add (GTK_CONTAINER (toolitem21), label186);
  gtk_widget_set_size_request (label186, -1, 8);

  toolitem22 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem22);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem22);

  button56 = gtk_button_new ();
  gtk_widget_show (button56);
  gtk_container_add (GTK_CONTAINER (toolitem22), button56);
  gtk_widget_set_size_request (button56, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button56, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button56, _("Autocenter On"), NULL);
  gtk_button_set_focus_on_click (GTK_BUTTON (button56), FALSE);

  image9 = gtk_image_new_from_stock ("gtk-jump-to", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image9);
  gtk_container_add (GTK_CONTAINER (button56), image9);

  toolitem26 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem26);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem26);

  label185 = gtk_label_new ("");
  gtk_widget_show (label185);
  gtk_container_add (GTK_CONTAINER (toolitem26), label185);
  gtk_widget_set_size_request (label185, -1, 8);

  toolitem31 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem31);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem31);

  button57 = gtk_button_new ();
  gtk_widget_show (button57);
  gtk_container_add (GTK_CONTAINER (toolitem31), button57);
  gtk_widget_set_size_request (button57, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button57, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button57, _("Next map repo"), NULL);
  gtk_button_set_focus_on_click (GTK_BUTTON (button57), FALSE);

  image10 = gtk_image_new_from_stock ("gtk-go-forward", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image10);
  gtk_container_add (GTK_CONTAINER (button57), image10);

  toolitem30 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem30);
  gtk_container_add (GTK_CONTAINER (toolbar4), toolitem30);

  button58 = gtk_button_new ();
  gtk_widget_show (button58);
  gtk_container_add (GTK_CONTAINER (toolitem30), button58);
  gtk_widget_set_size_request (button58, 50, 50);
  GTK_WIDGET_UNSET_FLAGS (button58, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button58, _("Previous map repo"), NULL);
  gtk_button_set_focus_on_click (GTK_BUTTON (button58), FALSE);

  image11 = gtk_image_new_from_stock ("gtk-go-back", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image11);
  gtk_container_add (GTK_CONTAINER (button58), image11);

  drawingarea1 = gtk_drawing_area_new ();
  gtk_widget_show (drawingarea1);
  gtk_box_pack_start (GTK_BOX (hbox52), drawingarea1, TRUE, TRUE, 0);
  GTK_WIDGET_SET_FLAGS (drawingarea1, GTK_CAN_FOCUS);
  gtk_widget_set_events (drawingarea1, GDK_EXPOSURE_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_LEAVE_NOTIFY_MASK);

  vscale1 = gtk_vscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (3, 2, 17, 1, 0, 0)));
  gtk_widget_show (vscale1);
  gtk_box_pack_start (GTK_BOX (hbox52), vscale1, FALSE, FALSE, 0);
  gtk_widget_set_size_request (vscale1, 25, -1);
  GTK_WIDGET_UNSET_FLAGS (vscale1, GTK_CAN_FOCUS);
  gtk_scale_set_digits (GTK_SCALE (vscale1), 0);
  gtk_range_set_inverted (GTK_RANGE (vscale1), TRUE);

  vbox53 = gtk_vbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (hbox1), vbox53, FALSE, FALSE, 0);

  hbox50 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox50);
  gtk_box_pack_start (GTK_BOX (vbox53), hbox50, FALSE, FALSE, 10);

  button69 = gtk_button_new ();
  gtk_widget_show (button69);
  gtk_box_pack_start (GTK_BOX (hbox50), button69, TRUE, TRUE, 3);
  gtk_widget_set_size_request (button69, -1, 40);
  GTK_WIDGET_UNSET_FLAGS (button69, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button69, _("Go to Previous Page"), NULL);

  image17 = gtk_image_new_from_stock ("gtk-go-back", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image17);
  gtk_container_add (GTK_CONTAINER (button69), image17);

  button71 = gtk_button_new ();
  gtk_widget_show (button71);
  gtk_box_pack_start (GTK_BOX (hbox50), button71, FALSE, TRUE, 0);
  gtk_widget_set_size_request (button71, 80, -1);
  GTK_WIDGET_UNSET_FLAGS (button71, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button71, _("Close Info Area"), NULL);

  image14 = gtk_image_new_from_stock ("gtk-close", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image14);
  gtk_container_add (GTK_CONTAINER (button71), image14);

  button70 = gtk_button_new ();
  gtk_widget_show (button70);
  gtk_box_pack_start (GTK_BOX (hbox50), button70, TRUE, TRUE, 3);
  GTK_WIDGET_UNSET_FLAGS (button70, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button70, _("Go to Next Page"), NULL);

  alignment20 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment20);
  gtk_container_add (GTK_CONTAINER (button70), alignment20);

  hbox51 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox51);
  gtk_container_add (GTK_CONTAINER (alignment20), hbox51);

  image12 = gtk_image_new_from_stock ("gtk-go-forward", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image12);
  gtk_box_pack_start (GTK_BOX (hbox51), image12, FALSE, FALSE, 0);

  label196 = gtk_label_new_with_mnemonic ("");
  gtk_widget_show (label196);
  gtk_box_pack_start (GTK_BOX (hbox51), label196, FALSE, FALSE, 0);

  hbox49a = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox49a);
  gtk_box_pack_start (GTK_BOX (vbox53), hbox49a, TRUE, TRUE, 0);

  scrolledwindow6 = gtk_scrolled_window_new (NULL, NULL);
  gtk_box_pack_start (GTK_BOX (hbox49a), scrolledwindow6, TRUE, TRUE, 0);
  gtk_widget_set_size_request (scrolledwindow6, 300, -1);
  GTK_WIDGET_UNSET_FLAGS (scrolledwindow6, GTK_CAN_FOCUS);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow6), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

  viewport10 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport10);
  gtk_container_add (GTK_CONTAINER (scrolledwindow6), viewport10);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport10), GTK_SHADOW_NONE);

  vbox4 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox4);
  gtk_container_add (GTK_CONTAINER (viewport10), vbox4);

  frame1 = gtk_frame_new (NULL);
  gtk_widget_show (frame1);
  gtk_box_pack_start (GTK_BOX (vbox4), frame1, FALSE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame1), 7);
  gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_NONE);

  vbox16 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox16);
  gtk_container_add (GTK_CONTAINER (frame1), vbox16);

  hbox49 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox49);
  gtk_box_pack_start (GTK_BOX (vbox16), hbox49, TRUE, TRUE, 0);

  label32 = gtk_label_new (_("Speed"));
  gtk_widget_show (label32);
  gtk_box_pack_start (GTK_BOX (hbox49), label32, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label32), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label32), 12, 0);

  label38 = gtk_label_new (_("   <span font_desc='40'> -- </span>"));
  gtk_widget_show (label38);
  gtk_box_pack_start (GTK_BOX (hbox49), label38, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label38), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label38), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label38), 0, 2);

  alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment1);
  gtk_box_pack_start (GTK_BOX (vbox16), alignment1, TRUE, TRUE, 0);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment1), 0, 0, 12, 0);

  table3 = gtk_table_new (2, 4, FALSE);
  gtk_widget_show (table3);
  gtk_container_add (GTK_CONTAINER (alignment1), table3);
  gtk_table_set_row_spacings (GTK_TABLE (table3), 2);
  gtk_table_set_col_spacings (GTK_TABLE (table3), 2);

  label28 = gtk_label_new (_("Trip "));
  gtk_widget_show (label28);
  gtk_table_attach (GTK_TABLE (table3), label28, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label28), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label28), 0, 2);

  label67 = gtk_label_new (_("Average "));
  gtk_widget_show (label67);
  gtk_table_attach (GTK_TABLE (table3), label67, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label67), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label67), 0, 2);

  label45 = gtk_label_new (_("0"));
  gtk_widget_show (label45);
  gtk_table_attach (GTK_TABLE (table3), label45, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label45), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label45), 0, 0.5);

  label68 = gtk_label_new (_("0"));
  gtk_widget_show (label68);
  gtk_table_attach (GTK_TABLE (table3), label68, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label68), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label68), 0, 0.5);

  label69 = gtk_label_new (_("Max "));
  gtk_widget_show (label69);
  gtk_table_attach (GTK_TABLE (table3), label69, 2, 3, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label69), 0, 0.5);

  label65 = gtk_label_new (_("Time "));
  gtk_widget_show (label65);
  gtk_table_attach (GTK_TABLE (table3), label65, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label65), 0, 0.5);

  label70 = gtk_label_new (_("0"));
  gtk_widget_show (label70);
  gtk_table_attach (GTK_TABLE (table3), label70, 3, 4, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label70), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label70), 0, 0.5);

  label66 = gtk_label_new (_("0"));
  gtk_widget_show (label66);
  gtk_table_attach (GTK_TABLE (table3), label66, 3, 4, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (label66), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label66), 0, 0.5);

  hbox5 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox5);
  gtk_box_pack_start (GTK_BOX (vbox16), hbox5, TRUE, TRUE, 4);
  gtk_widget_set_size_request (hbox5, -1, 55);

  button15 = gtk_button_new_with_mnemonic (_("Stop"));
  gtk_widget_show (button15);
  gtk_box_pack_start (GTK_BOX (hbox5), button15, FALSE, FALSE, 4);
  gtk_widget_set_size_request (button15, 130, -1);
  GTK_WIDGET_UNSET_FLAGS (button15, GTK_CAN_FOCUS);

  button8 = gtk_button_new_with_mnemonic (_("Reset"));
  gtk_widget_show (button8);
  gtk_box_pack_start (GTK_BOX (hbox5), button8, FALSE, FALSE, 12);
  gtk_widget_set_size_request (button8, 90, 40);
  GTK_WIDGET_UNSET_FLAGS (button8, GTK_CAN_FOCUS);

  label47 = gtk_label_new (_("<big><b>Trip Meter</b></big>   <small>[1/4]</small>"));
  gtk_widget_show (label47);
  gtk_frame_set_label_widget (GTK_FRAME (frame1), label47);
  gtk_label_set_use_markup (GTK_LABEL (label47), TRUE);

  frame2 = gtk_frame_new (NULL);
  gtk_widget_show (frame2);
  gtk_box_pack_start (GTK_BOX (vbox4), frame2, TRUE, TRUE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (frame2), 7);
  gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_NONE);

  alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (frame2), alignment2);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment2), 5, 0, 12, 0);

  table4 = gtk_table_new (5, 2, FALSE);
  gtk_widget_show (table4);
  gtk_container_add (GTK_CONTAINER (alignment2), table4);
  gtk_table_set_col_spacings (GTK_TABLE (table4), 4);

  label33 = gtk_label_new (_("Altitude"));
  gtk_widget_show (label33);
  gtk_table_attach (GTK_TABLE (table4), label33, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label33), 0, 0.5);

  label36 = gtk_label_new (_("Heading"));
  gtk_widget_show (label36);
  gtk_table_attach (GTK_TABLE (table4), label36, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label36), 0, 0.5);

  label30 = gtk_label_new (_("Lat - Lon"));
  gtk_widget_show (label30);
  gtk_table_attach (GTK_TABLE (table4), label30, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label30), 0, 0.5);

  label35 = gtk_label_new (_("GPS Time"));
  gtk_widget_show (label35);
  gtk_table_attach (GTK_TABLE (table4), label35, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label35), 0, 0.5);

  label37 = gtk_label_new (_("Satellites  "));
  gtk_widget_show (label37);
  gtk_table_attach (GTK_TABLE (table4), label37, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label37), 0, 0.5);

  label39 = gtk_label_new (_("0"));
  gtk_widget_show (label39);
  gtk_table_attach (GTK_TABLE (table4), label39, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 2);
  gtk_label_set_use_markup (GTK_LABEL (label39), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label39), 0, 0.5);

  label42 = gtk_label_new (_("0"));
  gtk_widget_show (label42);
  gtk_table_attach (GTK_TABLE (table4), label42, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 2);
  gtk_label_set_use_markup (GTK_LABEL (label42), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label42), 0, 0.5);

  label41 = gtk_label_new (_("0"));
  gtk_widget_show (label41);
  gtk_table_attach (GTK_TABLE (table4), label41, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 2);
  gtk_label_set_use_markup (GTK_LABEL (label41), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label41), 0, 0.5);

  label31 = gtk_label_new (_("0"));
  gtk_widget_show (label31);
  gtk_table_attach (GTK_TABLE (table4), label31, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 2);
  gtk_label_set_use_markup (GTK_LABEL (label31), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label31), 0, 0.5);

  label43 = gtk_label_new (_("0"));
  gtk_widget_show (label43);
  gtk_table_attach (GTK_TABLE (table4), label43, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 2);
  gtk_label_set_use_markup (GTK_LABEL (label43), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label43), 0, 0.5);

  label48 = gtk_label_new (_("<b>GPS Data</b>"));
  gtk_widget_show (label48);
  gtk_frame_set_label_widget (GTK_FRAME (frame2), label48);
  gtk_label_set_use_markup (GTK_LABEL (label48), TRUE);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_box_pack_start (GTK_BOX (hbox49a), scrolledwindow2, TRUE, TRUE, 0);
  gtk_widget_set_size_request (scrolledwindow2, 300, -1);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  viewport2 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport2);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), viewport2);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport2), GTK_SHADOW_NONE);

  vbox5 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox5);
  gtk_container_add (GTK_CONTAINER (viewport2), vbox5);

  label200 = gtk_label_new (_("<big><b>Friends</b></big>   <small>[2/4]</small>"));
  gtk_widget_show (label200);
  gtk_box_pack_start (GTK_BOX (vbox5), label200, FALSE, FALSE, 4);
  gtk_label_set_use_markup (GTK_LABEL (label200), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label200), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label200), 9, 0);

  button35 = gtk_button_new_with_mnemonic (_("Hide Messages"));
  gtk_box_pack_start (GTK_BOX (vbox5), button35, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button35, -1, 55);
  gtk_container_set_border_width (GTK_CONTAINER (button35), 5);
  GTK_WIDGET_UNSET_FLAGS (button35, GTK_CAN_FOCUS);

  vbox48 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox48);
  gtk_box_pack_start (GTK_BOX (vbox5), vbox48, FALSE, FALSE, 0);

  label132 = gtk_label_new (_("<i>No Messages</i>"));
  gtk_box_pack_start (GTK_BOX (vbox48), label132, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label132), TRUE);
  gtk_label_set_line_wrap (GTK_LABEL (label132), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label132), 0.02, 0.5);
  gtk_misc_set_padding (GTK_MISC (label132), 5, 0);

  label187 = gtk_label_new ("");
  gtk_widget_show (label187);
  gtk_box_pack_start (GTK_BOX (vbox5), label187, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label187), TRUE);

  frame6 = gtk_frame_new (NULL);
  gtk_widget_show (frame6);
  gtk_box_pack_start (GTK_BOX (vbox5), frame6, FALSE, TRUE, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (frame6), GTK_SHADOW_NONE);

  alignment6 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment6);
  gtk_container_add (GTK_CONTAINER (frame6), alignment6);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment6), 0, 0, 5, 0);

  vbox14 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox14);
  gtk_container_add (GTK_CONTAINER (alignment6), vbox14);

  hbox17 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox17);
  gtk_box_pack_start (GTK_BOX (vbox14), hbox17, TRUE, TRUE, 0);

  label101 = gtk_label_new (_("Enable position sharing and\nmessaging with your friends"));
  gtk_widget_show (label101);
  gtk_box_pack_start (GTK_BOX (hbox17), label101, FALSE, FALSE, 0);
  gtk_label_set_line_wrap (GTK_LABEL (label101), TRUE);

  label99 = gtk_label_new (_("\n\n"));
  gtk_widget_show (label99);
  gtk_box_pack_start (GTK_BOX (hbox17), label99, FALSE, FALSE, 0);
  gtk_label_set_line_wrap (GTK_LABEL (label99), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label99), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label99), 0, 3);

  hbox4 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox14), hbox4, FALSE, FALSE, 2);

  label202 = gtk_label_new (_("Update interval  "));
  gtk_widget_show (label202);
  gtk_box_pack_start (GTK_BOX (hbox4), label202, FALSE, FALSE, 0);

  entry16 = gtk_entry_new ();
  gtk_widget_show (entry16);
  gtk_box_pack_start (GTK_BOX (hbox4), entry16, FALSE, FALSE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entry16), 4);
  gtk_entry_set_text (GTK_ENTRY (entry16), _("5"));
  gtk_entry_set_width_chars (GTK_ENTRY (entry16), 4);

  label113 = gtk_label_new (_("minutes"));
  gtk_widget_show (label113);
  gtk_box_pack_start (GTK_BOX (hbox4), label113, FALSE, FALSE, 1);
  gtk_misc_set_alignment (GTK_MISC (label113), 0, 0.5);

  vbox8 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox8);
  gtk_box_pack_start (GTK_BOX (vbox14), vbox8, FALSE, TRUE, 0);

  hbox14 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox14);
  gtk_box_pack_start (GTK_BOX (vbox8), hbox14, TRUE, FALSE, 8);

  button11 = gtk_button_new_with_mnemonic (_("     Share!     "));
  gtk_widget_show (button11);
  gtk_box_pack_start (GTK_BOX (hbox14), button11, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button11, 100, 50);
  GTK_WIDGET_UNSET_FLAGS (button11, GTK_CAN_FOCUS);

  label97 = gtk_label_new (_("     "));
  gtk_widget_show (label97);
  gtk_box_pack_start (GTK_BOX (hbox14), label97, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label97), 0, 0.5);

  image24 = gtk_image_new_from_icon_name ("gtk-ok", GTK_ICON_SIZE_BUTTON);
  gtk_image_set_pixel_size (image24, 50);
  gtk_box_pack_start (GTK_BOX (hbox14), image24, FALSE, FALSE, 0);

  label51 = gtk_label_new ("");
  gtk_widget_show (label51);
  gtk_box_pack_start (GTK_BOX (vbox8), label51, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label51), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label51), 0, 0.5);

  label61 = gtk_label_new (_("<b>Position Sharing  </b>"));
  gtk_widget_show (label61);
  gtk_frame_set_label_widget (GTK_FRAME (frame6), label61);
  gtk_label_set_use_markup (GTK_LABEL (label61), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label61), 0.18, 0.5);
  gtk_misc_set_padding (GTK_MISC (label61), 3, 8);

  frame14 = gtk_frame_new (NULL);
  gtk_widget_show (frame14);
  gtk_box_pack_start (GTK_BOX (vbox5), frame14, TRUE, TRUE, 5);
  gtk_container_set_border_width (GTK_CONTAINER (frame14), 4);
  gtk_frame_set_shadow_type (GTK_FRAME (frame14), GTK_SHADOW_NONE);

  alignment19 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment19);
  gtk_container_add (GTK_CONTAINER (frame14), alignment19);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment19), 4, 5, 2, 0);

  vbox47 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox47);
  gtk_container_add (GTK_CONTAINER (alignment19), vbox47);

  label180 = gtk_label_new (_("Decide whom you see and \nwho can see you:"));
  gtk_widget_show (label180);
  gtk_box_pack_start (GTK_BOX (vbox47), label180, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label180), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label180), 0, 4);

  radiobutton27 = gtk_radio_button_new_with_mnemonic (NULL, _("fun mode"));
  gtk_widget_show (radiobutton27);
  gtk_box_pack_start (GTK_BOX (vbox47), radiobutton27, FALSE, FALSE, 2);
  GTK_WIDGET_UNSET_FLAGS (radiobutton27, GTK_CAN_FOCUS);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton27), radiobutton27_group);
  radiobutton27_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton27));

  radiobutton28 = gtk_radio_button_new_with_mnemonic (NULL, _("friend mode"));
  gtk_widget_show (radiobutton28);
  gtk_box_pack_start (GTK_BOX (vbox47), radiobutton28, FALSE, FALSE, 2);
  GTK_WIDGET_UNSET_FLAGS (radiobutton28, GTK_CAN_FOCUS);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton28), radiobutton27_group);
  radiobutton27_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton28));

  radiobutton29 = gtk_radio_button_new_with_mnemonic (NULL, _("private mode"));
  gtk_widget_show (radiobutton29);
  gtk_box_pack_start (GTK_BOX (vbox47), radiobutton29, FALSE, FALSE, 2);
  GTK_WIDGET_UNSET_FLAGS (radiobutton29, GTK_CAN_FOCUS);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton29), radiobutton27_group);
  radiobutton27_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton29));

  label182 = gtk_label_new (_("<i>What are you up to?</i>"));
  gtk_widget_show (label182);
  gtk_box_pack_start (GTK_BOX (vbox47), label182, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label182), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label182), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label182), 0, 3);

  entry29 = gtk_entry_new ();
  gtk_widget_show (entry29);
  gtk_box_pack_start (GTK_BOX (vbox47), entry29, FALSE, FALSE, 0);
  gtk_entry_set_text (GTK_ENTRY (entry29), _("just idle..."));
  gtk_entry_set_invisible_char (GTK_ENTRY (entry29), 9679);

  label179 = gtk_label_new (_("<b>Sharing Mode</b> "));
  gtk_widget_show (label179);
  gtk_frame_set_label_widget (GTK_FRAME (frame14), label179);
  gtk_label_set_use_markup (GTK_LABEL (label179), TRUE);
  gtk_misc_set_padding (GTK_MISC (label179), 0, 14);

  frame5 = gtk_frame_new (NULL);
  gtk_widget_show (frame5);
  gtk_box_pack_start (GTK_BOX (vbox5), frame5, FALSE, TRUE, 10);
  gtk_widget_set_size_request (frame5, 300, -1);
  gtk_container_set_border_width (GTK_CONTAINER (frame5), 1);
  gtk_frame_set_shadow_type (GTK_FRAME (frame5), GTK_SHADOW_NONE);

  alignment5 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment5);
  gtk_container_add (GTK_CONTAINER (frame5), alignment5);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment5), 0, 0, 2, 0);

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (alignment5), vbox13);

  table5 = gtk_table_new (3, 2, FALSE);
  gtk_widget_show (table5);
  gtk_box_pack_start (GTK_BOX (vbox13), table5, FALSE, TRUE, 10);

  label57 = gtk_label_new (_("Nickname "));
  gtk_widget_show (label57);
  gtk_table_attach (GTK_TABLE (table5), label57, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label57), 0, 0.5);

  label58 = gtk_label_new (_("Password"));
  gtk_widget_show (label58);
  gtk_table_attach (GTK_TABLE (table5), label58, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label58), 0, 0.5);

  entry8 = gtk_entry_new ();
  gtk_widget_show (entry8);
  gtk_table_attach (GTK_TABLE (table5), entry8, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_visibility (GTK_ENTRY (entry8), FALSE);
  gtk_entry_set_text (GTK_ENTRY (entry8), _("foobar"));

  entry7 = gtk_entry_new ();
  gtk_widget_show (entry7);
  gtk_table_attach (GTK_TABLE (table5), entry7, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_text (GTK_ENTRY (entry7), _("JohnDoe"));

  checkbutton15 = gtk_check_button_new_with_mnemonic (_("Show password"));
  gtk_widget_show (checkbutton15);
  gtk_table_attach (GTK_TABLE (table5), checkbutton15, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  scrolledwindow14 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow14);
  gtk_box_pack_start (GTK_BOX (vbox13), scrolledwindow14, TRUE, TRUE, 3);
  gtk_widget_set_size_request (scrolledwindow14, -1, 75);
  GTK_WIDGET_UNSET_FLAGS (scrolledwindow14, GTK_CAN_FOCUS);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow14), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

  textview6 = gtk_text_view_new ();
  gtk_widget_show (textview6);
  gtk_container_add (GTK_CONTAINER (scrolledwindow14), textview6);
  GTK_WIDGET_UNSET_FLAGS (textview6, GTK_CAN_FOCUS);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview6), FALSE);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview6), GTK_WRAP_WORD);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview6), FALSE);
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview6), 4);
  gtk_text_buffer_set_text (gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview6)), _("Simply choose any nickname and password.\n\nBefore first use register them by clicking on the button below. "), -1);

  hbox18 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox18);
  gtk_box_pack_start (GTK_BOX (vbox13), hbox18, TRUE, TRUE, 10);

  label59 = gtk_label_new (_("Email        "));
  gtk_widget_show (label59);
  gtk_box_pack_start (GTK_BOX (hbox18), label59, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label59), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label59), 0, 0.5);

  entry9 = gtk_entry_new ();
  gtk_widget_show (entry9);
  gtk_box_pack_start (GTK_BOX (hbox18), entry9, TRUE, TRUE, 0);

  hbox15 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox15);
  gtk_box_pack_start (GTK_BOX (vbox13), hbox15, TRUE, TRUE, 0);

  button13 = gtk_button_new_with_mnemonic (_("     Register!     "));
  gtk_widget_show (button13);
  gtk_box_pack_start (GTK_BOX (hbox15), button13, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button13, -1, 45);

  label62 = gtk_label_new (_("     "));
  gtk_widget_show (label62);
  gtk_box_pack_start (GTK_BOX (vbox13), label62, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label62), TRUE);
  gtk_label_set_justify (GTK_LABEL (label62), GTK_JUSTIFY_CENTER);
  gtk_misc_set_alignment (GTK_MISC (label62), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label62), 3, 5);

  label56 = gtk_label_new (_("<b>Me</b>"));
  gtk_widget_show (label56);
  gtk_frame_set_label_widget (GTK_FRAME (frame5), label56);
  gtk_label_set_use_markup (GTK_LABEL (label56), TRUE);
  gtk_misc_set_padding (GTK_MISC (label56), 0, 4);

  frame7 = gtk_frame_new (NULL);
  gtk_box_pack_start (GTK_BOX (hbox49a), frame7, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame7), 5);
  gtk_frame_set_shadow_type (GTK_FRAME (frame7), GTK_SHADOW_NONE);

  alignment7 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment7);
  gtk_container_add (GTK_CONTAINER (frame7), alignment7);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment7), 0, 0, 2, 9);

  vbox17 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox17);
  gtk_container_add (GTK_CONTAINER (alignment7), vbox17);

  label204 = gtk_label_new (_("    "));
  gtk_widget_show (label204);
  gtk_box_pack_start (GTK_BOX (vbox17), label204, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label204, -1, 12);

  checkbutton17 = gtk_check_button_new_with_mnemonic (_("Enable Track Logging"));
  gtk_widget_show (checkbutton17);
  gtk_box_pack_start (GTK_BOX (vbox17), checkbutton17, FALSE, FALSE, 0);
  gtk_widget_set_size_request (checkbutton17, -1, 35);

  checkbutton16 = gtk_check_button_new_with_mnemonic (_("Enable Live Tracking"));
  gtk_box_pack_start (GTK_BOX (vbox17), checkbutton16, FALSE, FALSE, 0);
  gtk_widget_set_size_request (checkbutton16, -1, 35);

  label203 = gtk_label_new (_("     "));
  gtk_widget_show (label203);
  gtk_box_pack_start (GTK_BOX (vbox17), label203, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label203), 0, 0.5);

  hbox53 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox53);
  gtk_box_pack_start (GTK_BOX (vbox17), hbox53, FALSE, FALSE, 10);

  button19 = gtk_button_new_with_mnemonic (_("Split"));
  gtk_widget_show (button19);
  gtk_box_pack_start (GTK_BOX (hbox53), button19, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button19, 147, 70);
  GTK_WIDGET_UNSET_FLAGS (button19, GTK_CAN_FOCUS);

  label76 = gtk_label_new ("");
  gtk_widget_show (label76);
  gtk_box_pack_start (GTK_BOX (vbox17), label76, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label76), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label76), 0, 0);

  hbox7 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox17), hbox7, FALSE, TRUE, 5);
  gtk_widget_set_size_request (hbox7, -1, 45);

  button36 = gtk_button_new_with_mnemonic (_("Load"));
  gtk_widget_show (button36);
  gtk_box_pack_start (GTK_BOX (hbox7), button36, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button36, 100, -1);
  GTK_WIDGET_UNSET_FLAGS (button36, GTK_CAN_FOCUS);

  button79 = gtk_button_new_with_mnemonic (_("Clear"));
  gtk_box_pack_start (GTK_BOX (hbox7), button79, FALSE, FALSE, 4);
  gtk_widget_set_size_request (button79, 100, -1);

  button78 = gtk_button_new_with_mnemonic (_("Upload"));
  gtk_box_pack_start (GTK_BOX (hbox7), button78, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button78, 100, -1);

  hbox54 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox54);
  gtk_box_pack_start (GTK_BOX (vbox17), hbox54, FALSE, TRUE, 0);

  button20 = gtk_button_new_with_mnemonic (_("Configure"));
  gtk_widget_show (button20);
  gtk_box_pack_start (GTK_BOX (hbox54), button20, FALSE, FALSE, 0);
  gtk_widget_set_size_request (button20, 100, 40);
  GTK_WIDGET_UNSET_FLAGS (button20, GTK_CAN_FOCUS);

  label74 = gtk_label_new (_("<big><b>Tracks</b></big>   <small>[3/4]</small>"));
  gtk_widget_show (label74);
  gtk_frame_set_label_widget (GTK_FRAME (frame7), label74);
  gtk_label_set_use_markup (GTK_LABEL (label74), TRUE);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_box_pack_start (GTK_BOX (hbox49a), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  viewport1 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), viewport1);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport1), GTK_SHADOW_NONE);

  vbox2 = gtk_vbox_new (FALSE, 1);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (viewport1), vbox2);

  label201 = gtk_label_new (_("<big><b>Configuration</b></big>   <small>[4/4]</small>"));
  gtk_widget_show (label201);
  gtk_box_pack_start (GTK_BOX (vbox2), label201, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label201), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label201), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label201), 2, 2);

  label117 = gtk_label_new (_("<small><i>foxtrotGPS Version:\nDeveloper: Marcus Bauer &amp; Community</i></small>"));
  gtk_widget_show (label117);
  gtk_box_pack_start (GTK_BOX (vbox2), label117, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label117), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label117), 0.01, 0);
  gtk_misc_set_padding (GTK_MISC (label117), 0, 4);

  frame9 = gtk_frame_new (NULL);
  gtk_widget_show (frame9);
  gtk_box_pack_start (GTK_BOX (vbox2), frame9, FALSE, FALSE, 9);
  gtk_container_set_border_width (GTK_CONTAINER (frame9), 1);
  gtk_frame_set_shadow_type (GTK_FRAME (frame9), GTK_SHADOW_NONE);

  alignment9 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment9);
  gtk_container_add (GTK_CONTAINER (frame9), alignment9);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment9), 0, 0, 3, 0);

  vbox19 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox19);
  gtk_container_add (GTK_CONTAINER (alignment9), vbox19);

  label81 = gtk_label_new (_("Activate or deactivate automatic\ndownload of missing tiles into cache"));
  gtk_widget_show (label81);
  gtk_box_pack_start (GTK_BOX (vbox19), label81, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label81), 0, 0);

  checkbutton2 = gtk_check_button_new_with_mnemonic (_("Auto download map tiles"));
  gtk_widget_show (checkbutton2);
  gtk_box_pack_start (GTK_BOX (vbox19), checkbutton2, FALSE, FALSE, 0);
  gtk_widget_set_size_request (checkbutton2, 270, -1);
  gtk_container_set_border_width (GTK_CONTAINER (checkbutton2), 10);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton2), TRUE);

  label80 = gtk_label_new (_("<b>Auto Download</b>"));
  gtk_widget_show (label80);
  gtk_frame_set_label_widget (GTK_FRAME (frame9), label80);
  gtk_label_set_use_markup (GTK_LABEL (label80), TRUE);
  gtk_misc_set_padding (GTK_MISC (label80), 0, 6);

  frame8 = gtk_frame_new (NULL);
  gtk_widget_show (frame8);
  gtk_box_pack_start (GTK_BOX (vbox2), frame8, FALSE, FALSE, 0);
  gtk_widget_set_size_request (frame8, 350, -1);
  gtk_frame_set_shadow_type (GTK_FRAME (frame8), GTK_SHADOW_NONE);

  alignment8 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment8);
  gtk_container_add (GTK_CONTAINER (frame8), alignment8);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment8), 0, 0, 3, 0);

  vbox18 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox18);
  gtk_container_add (GTK_CONTAINER (alignment8), vbox18);

  label86 = gtk_label_new (_("Current Map:"));
  gtk_widget_show (label86);
  gtk_box_pack_start (GTK_BOX (vbox18), label86, FALSE, FALSE, 0);
  gtk_misc_set_alignment (GTK_MISC (label86), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label86), 0, 4);

  hbox3 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (vbox18), hbox3, TRUE, TRUE, 0);

  combobox1 = gtk_combo_box_new_text ();
  gtk_widget_show (combobox1);
  gtk_box_pack_start (GTK_BOX (hbox3), combobox1, FALSE, FALSE, 1);
  gtk_widget_set_size_request (combobox1, 320, 44);
  gtk_container_set_border_width (GTK_CONTAINER (combobox1), 8);

  hbox37 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox37);
  gtk_box_pack_start (GTK_BOX (vbox18), hbox37, TRUE, TRUE, 10);

  button7 = gtk_button_new_with_mnemonic (_("      New...       "));
  gtk_widget_show (button7);
  gtk_box_pack_start (GTK_BOX (hbox37), button7, FALSE, FALSE, 0);

  label140 = gtk_label_new (_("    "));
  gtk_widget_show (label140);
  gtk_box_pack_start (GTK_BOX (hbox37), label140, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label140, -1, 50);

  button38 = gtk_button_new_with_mnemonic (_("      Edit...     "));
  gtk_widget_show (button38);
  gtk_box_pack_start (GTK_BOX (hbox37), button38, FALSE, FALSE, 0);

  table1 = gtk_table_new (3, 2, FALSE);
  gtk_box_pack_start (GTK_BOX (vbox18), table1, TRUE, TRUE, 6);

  label20 = gtk_label_new ("");
  gtk_widget_show (label20);
  gtk_table_attach (GTK_TABLE (table1), label20, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label20), 0, 0.5);

  checkbutton1 = gtk_check_button_new_with_mnemonic (_("xyz instead of zxy"));
  gtk_widget_show (checkbutton1);
  gtk_table_attach (GTK_TABLE (table1), checkbutton1, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 7, 7);

  label18 = gtk_label_new (_("URI"));
  gtk_widget_show (label18);
  gtk_table_attach (GTK_TABLE (table1), label18, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 3, 0);
  gtk_misc_set_alignment (GTK_MISC (label18), 0, 0.5);

  label19 = gtk_label_new (_("Cache Dir"));
  gtk_widget_show (label19);
  gtk_table_attach (GTK_TABLE (table1), label19, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 3, 0);
  gtk_misc_set_alignment (GTK_MISC (label19), 0, 0.5);

  entry2 = gtk_entry_new ();
  gtk_widget_show (entry2);
  gtk_table_attach (GTK_TABLE (table1), entry2, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 7, 0);

  entry1 = gtk_entry_new ();
  gtk_widget_show (entry1);
  gtk_table_attach (GTK_TABLE (table1), entry1, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND), 7, 0);

  hbox8 = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox18), hbox8, TRUE, TRUE, 0);

  button6 = gtk_button_new_with_mnemonic (_("    Save Repository Configuration    "));
  gtk_widget_show (button6);
  gtk_box_pack_start (GTK_BOX (hbox8), button6, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (button6), 4);
  gtk_widget_set_sensitive (button6, FALSE);

  label89 = gtk_label_new (_("     "));
  gtk_widget_show (label89);
  gtk_box_pack_start (GTK_BOX (hbox8), label89, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label89, -1, 50);

  label78 = gtk_label_new (_("<b>Map Types</b>"));
  gtk_widget_show (label78);
  gtk_frame_set_label_widget (GTK_FRAME (frame8), label78);
  gtk_label_set_use_markup (GTK_LABEL (label78), TRUE);
  gtk_misc_set_padding (GTK_MISC (label78), 0, 5);

  frame11 = gtk_frame_new (NULL);
  gtk_widget_show (frame11);
  gtk_box_pack_start (GTK_BOX (vbox2), frame11, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame11), 1);
  gtk_frame_set_shadow_type (GTK_FRAME (frame11), GTK_SHADOW_NONE);

  alignment11 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment11);
  gtk_container_add (GTK_CONTAINER (frame11), alignment11);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment11), 0, 0, 3, 0);

  vbox32 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox32);
  gtk_container_add (GTK_CONTAINER (alignment11), vbox32);

  label114 = gtk_label_new (_("<i>Speed and Distance:</i>"));
  gtk_widget_show (label114);
  gtk_box_pack_start (GTK_BOX (vbox32), label114, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label114), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label114), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label114), 0, 3);

  hbox22 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox22);
  gtk_box_pack_start (GTK_BOX (vbox32), hbox22, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox22), 5);

  radiobutton14 = gtk_radio_button_new_with_mnemonic (NULL, _("metrical"));
  gtk_widget_show (radiobutton14);
  gtk_box_pack_start (GTK_BOX (hbox22), radiobutton14, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton14), radiobutton14_group);
  radiobutton14_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton14));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton14), TRUE);

  radiobutton15 = gtk_radio_button_new_with_mnemonic (NULL, _("imperial"));
  gtk_widget_show (radiobutton15);
  gtk_box_pack_start (GTK_BOX (hbox22), radiobutton15, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton15), radiobutton14_group);
  radiobutton14_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton15));

  radiobutton16 = gtk_radio_button_new_with_mnemonic (NULL, _("nautical"));
  gtk_widget_show (radiobutton16);
  gtk_box_pack_start (GTK_BOX (hbox22), radiobutton16, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton16), radiobutton14_group);
  radiobutton14_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton16));

  label115 = gtk_label_new (_("<i>Altitude:</i>"));
  gtk_widget_show (label115);
  gtk_box_pack_start (GTK_BOX (vbox32), label115, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label115), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label115), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label115), 0, 2);

  hbox23 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox23);
  gtk_box_pack_start (GTK_BOX (vbox32), hbox23, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox23), 5);

  radiobutton17 = gtk_radio_button_new_with_mnemonic (NULL, _("meters"));
  gtk_widget_show (radiobutton17);
  gtk_box_pack_start (GTK_BOX (hbox23), radiobutton17, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton17), radiobutton17_group);
  radiobutton17_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton17));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton17), TRUE);

  radiobutton18 = gtk_radio_button_new_with_mnemonic (NULL, _("feet"));
  gtk_widget_show (radiobutton18);
  gtk_box_pack_start (GTK_BOX (hbox23), radiobutton18, FALSE, FALSE, 4);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton18), radiobutton17_group);
  radiobutton17_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton18));

  label116 = gtk_label_new (_("<i>Lat &amp; Lon:</i>"));
  gtk_widget_show (label116);
  gtk_box_pack_start (GTK_BOX (vbox32), label116, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label116), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label116), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label116), 0, 2);

  hbox24 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox24);
  gtk_box_pack_start (GTK_BOX (vbox32), hbox24, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox24), 5);

  radiobutton19 = gtk_radio_button_new_with_mnemonic (NULL, _("d.dd"));
  gtk_widget_show (radiobutton19);
  gtk_box_pack_start (GTK_BOX (hbox24), radiobutton19, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton19), radiobutton19_group);
  radiobutton19_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton19));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton19), TRUE);

  radiobutton20 = gtk_radio_button_new_with_mnemonic (NULL, _("d m.m'"));
  gtk_widget_show (radiobutton20);
  gtk_box_pack_start (GTK_BOX (hbox24), radiobutton20, FALSE, FALSE, 4);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton20), radiobutton19_group);
  radiobutton19_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton20));

  radiobutton21 = gtk_radio_button_new_with_mnemonic (NULL, _("d m's.s\""));
  gtk_widget_show (radiobutton21);
  gtk_box_pack_start (GTK_BOX (hbox24), radiobutton21, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton21), radiobutton19_group);
  radiobutton19_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton21));

  label87 = gtk_label_new (_("<b>Units</b>"));
  gtk_widget_show (label87);
  gtk_frame_set_label_widget (GTK_FRAME (frame11), label87);
  gtk_label_set_use_markup (GTK_LABEL (label87), TRUE);
  gtk_misc_set_padding (GTK_MISC (label87), 0, 10);

  frame12 = gtk_frame_new (NULL);
  gtk_widget_show (frame12);
  gtk_box_pack_start (GTK_BOX (vbox2), frame12, FALSE, FALSE, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (frame12), GTK_SHADOW_NONE);

  alignment12 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment12);
  gtk_container_add (GTK_CONTAINER (frame12), alignment12);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment12), 0, 0, 3, 0);

  vbox22 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox22);
  gtk_container_add (GTK_CONTAINER (alignment12), vbox22);

  label91 = gtk_label_new (_("\nSet GPSD Host IP\n"));
  gtk_widget_show (label91);
  gtk_box_pack_start (GTK_BOX (vbox22), label91, FALSE, FALSE, 0);
  gtk_label_set_line_wrap (GTK_LABEL (label91), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label91), 0, 0.5);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (vbox22), hbox2, TRUE, TRUE, 0);

  label21 = gtk_label_new (_(" GPSD "));
  gtk_widget_show (label21);
  gtk_box_pack_start (GTK_BOX (hbox2), label21, FALSE, FALSE, 0);

  label22 = gtk_label_new (_("Host:"));
  gtk_widget_show (label22);
  gtk_box_pack_start (GTK_BOX (hbox2), label22, FALSE, FALSE, 0);

  entry3 = gtk_entry_new ();
  gtk_widget_show (entry3);
  gtk_box_pack_start (GTK_BOX (hbox2), entry3, FALSE, FALSE, 0);
  gtk_entry_set_text (GTK_ENTRY (entry3), _("127.0.0.1"));
  gtk_entry_set_width_chars (GTK_ENTRY (entry3), 9);

  label23 = gtk_label_new (_(" Port:"));
  gtk_widget_show (label23);
  gtk_box_pack_start (GTK_BOX (hbox2), label23, FALSE, FALSE, 0);

  entry4 = gtk_entry_new ();
  gtk_widget_show (entry4);
  gtk_box_pack_start (GTK_BOX (hbox2), entry4, FALSE, FALSE, 0);
  gtk_entry_set_text (GTK_ENTRY (entry4), _("2947"));
  gtk_entry_set_width_chars (GTK_ENTRY (entry4), 5);

  hbox10 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox10);
  gtk_box_pack_start (GTK_BOX (vbox22), hbox10, FALSE, FALSE, 0);

  button9 = gtk_button_new_with_mnemonic (_("     Change GPSD     "));
  gtk_widget_show (button9);
  gtk_box_pack_start (GTK_BOX (hbox10), button9, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (button9), 5);

  label92 = gtk_label_new (_("    "));
  gtk_widget_show (label92);
  gtk_box_pack_start (GTK_BOX (hbox10), label92, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label92, -1, 50);

  label90 = gtk_label_new (_("<b>GPSD</b>"));
  gtk_widget_show (label90);
  gtk_frame_set_label_widget (GTK_FRAME (frame12), label90);
  gtk_label_set_use_markup (GTK_LABEL (label90), TRUE);
  gtk_misc_set_padding (GTK_MISC (label90), 0, 10);

  eventbox5 = gtk_event_box_new ();
  gtk_widget_show (eventbox5);
  gtk_box_pack_start (GTK_BOX (vbox1), eventbox5, FALSE, FALSE, 0);

  label4 = gtk_label_new (_("<b>no GPS found</b>"));
  gtk_widget_show (label4);
  gtk_container_add (GTK_CONTAINER (eventbox5), label4);
  gtk_label_set_use_markup (GTK_LABEL (label4), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label4), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label4), 3, 1);

  g_signal_connect ((gpointer) window1, "delete_event",
                    G_CALLBACK (on_window1_delete_event),
                    NULL);
  g_signal_connect ((gpointer) window1, "destroy_event",
                    G_CALLBACK (on_window1_destroy_event),
                    NULL);
  g_signal_connect ((gpointer) button1, "clicked",
                    G_CALLBACK (on_button1_clicked),
                    NULL);
  g_signal_connect ((gpointer) button4, "clicked",
                    G_CALLBACK (on_button4_clicked),
                    NULL);
  g_signal_connect ((gpointer) button5, "clicked",
                    G_CALLBACK (on_button5_clicked),
                    NULL);
  g_signal_connect ((gpointer) button77, "clicked",
                    G_CALLBACK (on_button76_clicked),
                    NULL);
  g_signal_connect ((gpointer) button3, "clicked",
                    G_CALLBACK (on_button3_clicked),
                    NULL);
  g_signal_connect ((gpointer) button76, "clicked",
                    G_CALLBACK (on_button76_clicked),
                    NULL);
  g_signal_connect ((gpointer) button53, "clicked",
                    G_CALLBACK (on_button1_clicked),
                    NULL);
  g_signal_connect ((gpointer) button54, "clicked",
                    G_CALLBACK (on_button4_clicked),
                    NULL);
  g_signal_connect ((gpointer) button55, "clicked",
                    G_CALLBACK (on_button5_clicked),
                    NULL);
  g_signal_connect ((gpointer) button56, "clicked",
                    G_CALLBACK (on_button3_clicked),
                    NULL);
  g_signal_connect ((gpointer) button57, "clicked",
                    G_CALLBACK (on_button57_clicked),
                    NULL);
  g_signal_connect ((gpointer) button58, "clicked",
                    G_CALLBACK (on_button58_clicked),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "button_press_event",
                    G_CALLBACK (on_drawingarea1_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "motion_notify_event",
                    G_CALLBACK (on_drawingarea1_motion_notify_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "configure_event",
                    G_CALLBACK (on_drawingarea1_configure_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "expose_event",
                    G_CALLBACK (on_drawingarea1_expose_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "button_release_event",
                    G_CALLBACK (on_drawingarea1_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "scroll_event",
                    G_CALLBACK (on_drawinarea1_scroll_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "key_press_event",
                    G_CALLBACK (on_drawingarea1_key_press_event),
                    NULL);
  g_signal_connect ((gpointer) vscale1, "value_changed",
                    G_CALLBACK (on_vscale1_value_changed),
                    NULL);
  g_signal_connect ((gpointer) vscale1, "change_value",
                    G_CALLBACK (on_vscale1_change_value),
                    NULL);
  g_signal_connect ((gpointer) vscale1, "button_press_event",
                    G_CALLBACK (on_vscale1_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) vscale1, "button_release_event",
                    G_CALLBACK (on_vscale1_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) button69, "clicked",
                    G_CALLBACK (on_button69_clicked),
                    NULL);
  g_signal_connect ((gpointer) button71, "clicked",
                    G_CALLBACK (on_button76_clicked),
                    NULL);
  g_signal_connect ((gpointer) button70, "clicked",
                    G_CALLBACK (on_button70_clicked),
                    NULL);
  g_signal_connect ((gpointer) button15, "clicked",
                    G_CALLBACK (on_button15_clicked),
                    NULL);
  g_signal_connect ((gpointer) button8, "clicked",
                    G_CALLBACK (on_button8_clicked),
                    NULL);
  g_signal_connect ((gpointer) button35, "clicked",
                    G_CALLBACK (on_button35_clicked),
                    NULL);
  g_signal_connect ((gpointer) entry16, "changed",
                    G_CALLBACK (on_entry16_changed),
                    NULL);
  g_signal_connect ((gpointer) button11, "clicked",
                    G_CALLBACK (on_button11_clicked),
                    NULL);
  g_signal_connect ((gpointer) button11, "expose_event",
                    G_CALLBACK (on_button11_expose_event),
                    NULL);
  g_signal_connect ((gpointer) radiobutton27, "toggled",
                    G_CALLBACK (on_radiobutton27_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton28, "toggled",
                    G_CALLBACK (on_radiobutton28_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton29, "toggled",
                    G_CALLBACK (on_radiobutton29_toggled),
                    NULL);
  g_signal_connect ((gpointer) entry29, "changed",
                    G_CALLBACK (on_entry29_changed),
                    NULL);
  g_signal_connect ((gpointer) entry8, "changed",
                    G_CALLBACK (on_entry8_changed),
                    NULL);
  g_signal_connect ((gpointer) entry7, "changed",
                    G_CALLBACK (on_entry7_changed),
                    NULL);
  g_signal_connect ((gpointer) checkbutton15, "toggled",
                    G_CALLBACK (on_checkbutton15_toggled),
                    NULL);
  g_signal_connect ((gpointer) button13, "clicked",
                    G_CALLBACK (on_button13_clicked),
                    NULL);
  g_signal_connect ((gpointer) checkbutton17, "toggled",
                    G_CALLBACK (on_checkbutton17_toggled),
                    NULL);
  g_signal_connect ((gpointer) checkbutton16, "toggled",
                    G_CALLBACK (on_checkbutton16_toggled),
                    NULL);
  g_signal_connect ((gpointer) button19, "clicked",
                    G_CALLBACK (on_button19_clicked),
                    NULL);
  g_signal_connect ((gpointer) button36, "clicked",
                    G_CALLBACK (on_button36_clicked),
                    NULL);
  g_signal_connect ((gpointer) button79, "clicked",
                    G_CALLBACK (on_button79_clicked),
                    NULL);
  g_signal_connect ((gpointer) button78, "clicked",
                    G_CALLBACK (on_button78_clicked),
                    NULL);
  g_signal_connect ((gpointer) button20, "clicked",
                    G_CALLBACK (on_button20_clicked),
                    NULL);
  g_signal_connect ((gpointer) checkbutton2, "toggled",
                    G_CALLBACK (on_checkbutton2_toggled),
                    NULL);
  g_signal_connect ((gpointer) combobox1, "changed",
                    G_CALLBACK (on_combobox1_changed),
                    NULL);
  g_signal_connect ((gpointer) button7, "clicked",
                    G_CALLBACK (on_button7_clicked),
                    NULL);
  g_signal_connect ((gpointer) button38, "clicked",
                    G_CALLBACK (on_button38_clicked),
                    NULL);
  g_signal_connect ((gpointer) checkbutton1, "toggled",
                    G_CALLBACK (on_checkbutton1_toggled),
                    NULL);
  g_signal_connect ((gpointer) entry2, "changed",
                    G_CALLBACK (on_entry2_changed),
                    NULL);
  g_signal_connect ((gpointer) entry1, "changed",
                    G_CALLBACK (on_entry1_changed),
                    NULL);
  g_signal_connect ((gpointer) button6, "clicked",
                    G_CALLBACK (on_button6_clicked),
                    NULL);
  g_signal_connect ((gpointer) radiobutton14, "toggled",
                    G_CALLBACK (on_radiobutton14_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton15, "toggled",
                    G_CALLBACK (on_radiobutton15_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton16, "toggled",
                    G_CALLBACK (on_radiobutton16_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton17, "toggled",
                    G_CALLBACK (on_radiobutton17_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton18, "toggled",
                    G_CALLBACK (on_radiobutton18_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton19, "toggled",
                    G_CALLBACK (on_radiobutton19_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton20, "toggled",
                    G_CALLBACK (on_radiobutton20_toggled),
                    NULL);
  g_signal_connect ((gpointer) radiobutton21, "toggled",
                    G_CALLBACK (on_radiobutton21_toggled),
                    NULL);
  g_signal_connect ((gpointer) entry3, "changed",
                    G_CALLBACK (on_entry3_changed),
                    NULL);
  g_signal_connect ((gpointer) entry4, "changed",
                    G_CALLBACK (on_entry4_changed),
                    NULL);
  g_signal_connect ((gpointer) button9, "clicked",
                    G_CALLBACK (on_button9_clicked),
                    NULL);
  g_signal_connect ((gpointer) eventbox5, "button_release_event",
                    G_CALLBACK (on_eventbox5_button_release_event),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window1, window1, "window1");
  GLADE_HOOKUP_OBJECT (window1, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (window1, toolbar1, "toolbar1");
  GLADE_HOOKUP_OBJECT (window1, toolitem1, "toolitem1");
  GLADE_HOOKUP_OBJECT (window1, button1, "button1");
  GLADE_HOOKUP_OBJECT (window1, image19, "image19");
  GLADE_HOOKUP_OBJECT (window1, toolitem2, "toolitem2");
  GLADE_HOOKUP_OBJECT (window1, button4, "button4");
  GLADE_HOOKUP_OBJECT (window1, image20, "image20");
  GLADE_HOOKUP_OBJECT (window1, toolitem3, "toolitem3");
  GLADE_HOOKUP_OBJECT (window1, button5, "button5");
  GLADE_HOOKUP_OBJECT (window1, image21, "image21");
  GLADE_HOOKUP_OBJECT (window1, toolitem5, "toolitem5");
  GLADE_HOOKUP_OBJECT (window1, button77, "button77");
  GLADE_HOOKUP_OBJECT (window1, image22, "image22");
  GLADE_HOOKUP_OBJECT (window1, toolitem6, "toolitem6");
  GLADE_HOOKUP_OBJECT (window1, button3, "button3");
  GLADE_HOOKUP_OBJECT (window1, image23, "image23");
  GLADE_HOOKUP_OBJECT (window1, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (window1, hbox52, "hbox52");
  GLADE_HOOKUP_OBJECT (window1, toolbar4, "toolbar4");
  GLADE_HOOKUP_OBJECT (window1, toolitem15, "toolitem15");
  GLADE_HOOKUP_OBJECT (window1, button76, "button76");
  GLADE_HOOKUP_OBJECT (window1, image18, "image18");
  GLADE_HOOKUP_OBJECT (window1, toolitem24, "toolitem24");
  GLADE_HOOKUP_OBJECT (window1, label184, "label184");
  GLADE_HOOKUP_OBJECT (window1, toolitem25, "toolitem25");
  GLADE_HOOKUP_OBJECT (window1, button53, "button53");
  GLADE_HOOKUP_OBJECT (window1, image6, "image6");
  GLADE_HOOKUP_OBJECT (window1, toolitem18, "toolitem18");
  GLADE_HOOKUP_OBJECT (window1, label199, "label199");
  GLADE_HOOKUP_OBJECT (window1, toolitem19, "toolitem19");
  GLADE_HOOKUP_OBJECT (window1, button54, "button54");
  GLADE_HOOKUP_OBJECT (window1, image7, "image7");
  GLADE_HOOKUP_OBJECT (window1, toolitem20, "toolitem20");
  GLADE_HOOKUP_OBJECT (window1, button55, "button55");
  GLADE_HOOKUP_OBJECT (window1, image8, "image8");
  GLADE_HOOKUP_OBJECT (window1, toolitem21, "toolitem21");
  GLADE_HOOKUP_OBJECT (window1, label186, "label186");
  GLADE_HOOKUP_OBJECT (window1, toolitem22, "toolitem22");
  GLADE_HOOKUP_OBJECT (window1, button56, "button56");
  GLADE_HOOKUP_OBJECT (window1, image9, "image9");
  GLADE_HOOKUP_OBJECT (window1, toolitem26, "toolitem26");
  GLADE_HOOKUP_OBJECT (window1, label185, "label185");
  GLADE_HOOKUP_OBJECT (window1, toolitem31, "toolitem31");
  GLADE_HOOKUP_OBJECT (window1, button57, "button57");
  GLADE_HOOKUP_OBJECT (window1, image10, "image10");
  GLADE_HOOKUP_OBJECT (window1, toolitem30, "toolitem30");
  GLADE_HOOKUP_OBJECT (window1, button58, "button58");
  GLADE_HOOKUP_OBJECT (window1, image11, "image11");
  GLADE_HOOKUP_OBJECT (window1, drawingarea1, "drawingarea1");
  GLADE_HOOKUP_OBJECT (window1, vscale1, "vscale1");
  GLADE_HOOKUP_OBJECT (window1, vbox53, "vbox53");
  GLADE_HOOKUP_OBJECT (window1, hbox50, "hbox50");
  GLADE_HOOKUP_OBJECT (window1, button69, "button69");
  GLADE_HOOKUP_OBJECT (window1, image17, "image17");
  GLADE_HOOKUP_OBJECT (window1, button71, "button71");
  GLADE_HOOKUP_OBJECT (window1, image14, "image14");
  GLADE_HOOKUP_OBJECT (window1, button70, "button70");
  GLADE_HOOKUP_OBJECT (window1, alignment20, "alignment20");
  GLADE_HOOKUP_OBJECT (window1, hbox51, "hbox51");
  GLADE_HOOKUP_OBJECT (window1, image12, "image12");
  GLADE_HOOKUP_OBJECT (window1, label196, "label196");
  GLADE_HOOKUP_OBJECT (window1, hbox49a, "hbox49a");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow6, "scrolledwindow6");
  GLADE_HOOKUP_OBJECT (window1, viewport10, "viewport10");
  GLADE_HOOKUP_OBJECT (window1, vbox4, "vbox4");
  GLADE_HOOKUP_OBJECT (window1, frame1, "frame1");
  GLADE_HOOKUP_OBJECT (window1, vbox16, "vbox16");
  GLADE_HOOKUP_OBJECT (window1, hbox49, "hbox49");
  GLADE_HOOKUP_OBJECT (window1, label32, "label32");
  GLADE_HOOKUP_OBJECT (window1, label38, "label38");
  GLADE_HOOKUP_OBJECT (window1, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (window1, table3, "table3");
  GLADE_HOOKUP_OBJECT (window1, label28, "label28");
  GLADE_HOOKUP_OBJECT (window1, label67, "label67");
  GLADE_HOOKUP_OBJECT (window1, label45, "label45");
  GLADE_HOOKUP_OBJECT (window1, label68, "label68");
  GLADE_HOOKUP_OBJECT (window1, label69, "label69");
  GLADE_HOOKUP_OBJECT (window1, label65, "label65");
  GLADE_HOOKUP_OBJECT (window1, label70, "label70");
  GLADE_HOOKUP_OBJECT (window1, label66, "label66");
  GLADE_HOOKUP_OBJECT (window1, hbox5, "hbox5");
  GLADE_HOOKUP_OBJECT (window1, button15, "button15");
  GLADE_HOOKUP_OBJECT (window1, button8, "button8");
  GLADE_HOOKUP_OBJECT (window1, label47, "label47");
  GLADE_HOOKUP_OBJECT (window1, frame2, "frame2");
  GLADE_HOOKUP_OBJECT (window1, alignment2, "alignment2");
  GLADE_HOOKUP_OBJECT (window1, table4, "table4");
  GLADE_HOOKUP_OBJECT (window1, label33, "label33");
  GLADE_HOOKUP_OBJECT (window1, label36, "label36");
  GLADE_HOOKUP_OBJECT (window1, label30, "label30");
  GLADE_HOOKUP_OBJECT (window1, label35, "label35");
  GLADE_HOOKUP_OBJECT (window1, label37, "label37");
  GLADE_HOOKUP_OBJECT (window1, label39, "label39");
  GLADE_HOOKUP_OBJECT (window1, label42, "label42");
  GLADE_HOOKUP_OBJECT (window1, label41, "label41");
  GLADE_HOOKUP_OBJECT (window1, label31, "label31");
  GLADE_HOOKUP_OBJECT (window1, label43, "label43");
  GLADE_HOOKUP_OBJECT (window1, label48, "label48");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow2, "scrolledwindow2");
  GLADE_HOOKUP_OBJECT (window1, viewport2, "viewport2");
  GLADE_HOOKUP_OBJECT (window1, vbox5, "vbox5");
  GLADE_HOOKUP_OBJECT (window1, label200, "label200");
  GLADE_HOOKUP_OBJECT (window1, button35, "button35");
  GLADE_HOOKUP_OBJECT (window1, vbox48, "vbox48");
  GLADE_HOOKUP_OBJECT (window1, label132, "label132");
  GLADE_HOOKUP_OBJECT (window1, label187, "label187");
  GLADE_HOOKUP_OBJECT (window1, frame6, "frame6");
  GLADE_HOOKUP_OBJECT (window1, alignment6, "alignment6");
  GLADE_HOOKUP_OBJECT (window1, vbox14, "vbox14");
  GLADE_HOOKUP_OBJECT (window1, hbox17, "hbox17");
  GLADE_HOOKUP_OBJECT (window1, label101, "label101");
  GLADE_HOOKUP_OBJECT (window1, label99, "label99");
  GLADE_HOOKUP_OBJECT (window1, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (window1, label202, "label202");
  GLADE_HOOKUP_OBJECT (window1, entry16, "entry16");
  GLADE_HOOKUP_OBJECT (window1, label113, "label113");
  GLADE_HOOKUP_OBJECT (window1, vbox8, "vbox8");
  GLADE_HOOKUP_OBJECT (window1, hbox14, "hbox14");
  GLADE_HOOKUP_OBJECT (window1, button11, "button11");
  GLADE_HOOKUP_OBJECT (window1, label97, "label97");
  GLADE_HOOKUP_OBJECT (window1, image24, "image24");
  GLADE_HOOKUP_OBJECT (window1, label51, "label51");
  GLADE_HOOKUP_OBJECT (window1, label61, "label61");
  GLADE_HOOKUP_OBJECT (window1, frame14, "frame14");
  GLADE_HOOKUP_OBJECT (window1, alignment19, "alignment19");
  GLADE_HOOKUP_OBJECT (window1, vbox47, "vbox47");
  GLADE_HOOKUP_OBJECT (window1, label180, "label180");
  GLADE_HOOKUP_OBJECT (window1, radiobutton27, "radiobutton27");
  GLADE_HOOKUP_OBJECT (window1, radiobutton28, "radiobutton28");
  GLADE_HOOKUP_OBJECT (window1, radiobutton29, "radiobutton29");
  GLADE_HOOKUP_OBJECT (window1, label182, "label182");
  GLADE_HOOKUP_OBJECT (window1, entry29, "entry29");
  GLADE_HOOKUP_OBJECT (window1, label179, "label179");
  GLADE_HOOKUP_OBJECT (window1, frame5, "frame5");
  GLADE_HOOKUP_OBJECT (window1, alignment5, "alignment5");
  GLADE_HOOKUP_OBJECT (window1, vbox13, "vbox13");
  GLADE_HOOKUP_OBJECT (window1, table5, "table5");
  GLADE_HOOKUP_OBJECT (window1, label57, "label57");
  GLADE_HOOKUP_OBJECT (window1, label58, "label58");
  GLADE_HOOKUP_OBJECT (window1, entry8, "entry8");
  GLADE_HOOKUP_OBJECT (window1, entry7, "entry7");
  GLADE_HOOKUP_OBJECT (window1, checkbutton15, "checkbutton15");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow14, "scrolledwindow14");
  GLADE_HOOKUP_OBJECT (window1, textview6, "textview6");
  GLADE_HOOKUP_OBJECT (window1, hbox18, "hbox18");
  GLADE_HOOKUP_OBJECT (window1, label59, "label59");
  GLADE_HOOKUP_OBJECT (window1, entry9, "entry9");
  GLADE_HOOKUP_OBJECT (window1, hbox15, "hbox15");
  GLADE_HOOKUP_OBJECT (window1, button13, "button13");
  GLADE_HOOKUP_OBJECT (window1, label62, "label62");
  GLADE_HOOKUP_OBJECT (window1, label56, "label56");
  GLADE_HOOKUP_OBJECT (window1, frame7, "frame7");
  GLADE_HOOKUP_OBJECT (window1, alignment7, "alignment7");
  GLADE_HOOKUP_OBJECT (window1, vbox17, "vbox17");
  GLADE_HOOKUP_OBJECT (window1, label204, "label204");
  GLADE_HOOKUP_OBJECT (window1, checkbutton17, "checkbutton17");
  GLADE_HOOKUP_OBJECT (window1, checkbutton16, "checkbutton16");
  GLADE_HOOKUP_OBJECT (window1, label203, "label203");
  GLADE_HOOKUP_OBJECT (window1, hbox53, "hbox53");
  GLADE_HOOKUP_OBJECT (window1, button19, "button19");
  GLADE_HOOKUP_OBJECT (window1, label76, "label76");
  GLADE_HOOKUP_OBJECT (window1, hbox7, "hbox7");
  GLADE_HOOKUP_OBJECT (window1, button36, "button36");
  GLADE_HOOKUP_OBJECT (window1, button79, "button79");
  GLADE_HOOKUP_OBJECT (window1, button78, "button78");
  GLADE_HOOKUP_OBJECT (window1, hbox54, "hbox54");
  GLADE_HOOKUP_OBJECT (window1, button20, "button20");
  GLADE_HOOKUP_OBJECT (window1, label74, "label74");
  GLADE_HOOKUP_OBJECT (window1, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (window1, viewport1, "viewport1");
  GLADE_HOOKUP_OBJECT (window1, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (window1, label201, "label201");
  GLADE_HOOKUP_OBJECT (window1, label117, "label117");
  GLADE_HOOKUP_OBJECT (window1, frame9, "frame9");
  GLADE_HOOKUP_OBJECT (window1, alignment9, "alignment9");
  GLADE_HOOKUP_OBJECT (window1, vbox19, "vbox19");
  GLADE_HOOKUP_OBJECT (window1, label81, "label81");
  GLADE_HOOKUP_OBJECT (window1, checkbutton2, "checkbutton2");
  GLADE_HOOKUP_OBJECT (window1, label80, "label80");
  GLADE_HOOKUP_OBJECT (window1, frame8, "frame8");
  GLADE_HOOKUP_OBJECT (window1, alignment8, "alignment8");
  GLADE_HOOKUP_OBJECT (window1, vbox18, "vbox18");
  GLADE_HOOKUP_OBJECT (window1, label86, "label86");
  GLADE_HOOKUP_OBJECT (window1, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (window1, combobox1, "combobox1");
  GLADE_HOOKUP_OBJECT (window1, hbox37, "hbox37");
  GLADE_HOOKUP_OBJECT (window1, button7, "button7");
  GLADE_HOOKUP_OBJECT (window1, label140, "label140");
  GLADE_HOOKUP_OBJECT (window1, button38, "button38");
  GLADE_HOOKUP_OBJECT (window1, table1, "table1");
  GLADE_HOOKUP_OBJECT (window1, label20, "label20");
  GLADE_HOOKUP_OBJECT (window1, checkbutton1, "checkbutton1");
  GLADE_HOOKUP_OBJECT (window1, label18, "label18");
  GLADE_HOOKUP_OBJECT (window1, label19, "label19");
  GLADE_HOOKUP_OBJECT (window1, entry2, "entry2");
  GLADE_HOOKUP_OBJECT (window1, entry1, "entry1");
  GLADE_HOOKUP_OBJECT (window1, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (window1, button6, "button6");
  GLADE_HOOKUP_OBJECT (window1, label89, "label89");
  GLADE_HOOKUP_OBJECT (window1, label78, "label78");
  GLADE_HOOKUP_OBJECT (window1, frame11, "frame11");
  GLADE_HOOKUP_OBJECT (window1, alignment11, "alignment11");
  GLADE_HOOKUP_OBJECT (window1, vbox32, "vbox32");
  GLADE_HOOKUP_OBJECT (window1, label114, "label114");
  GLADE_HOOKUP_OBJECT (window1, hbox22, "hbox22");
  GLADE_HOOKUP_OBJECT (window1, radiobutton14, "radiobutton14");
  GLADE_HOOKUP_OBJECT (window1, radiobutton15, "radiobutton15");
  GLADE_HOOKUP_OBJECT (window1, radiobutton16, "radiobutton16");
  GLADE_HOOKUP_OBJECT (window1, label115, "label115");
  GLADE_HOOKUP_OBJECT (window1, hbox23, "hbox23");
  GLADE_HOOKUP_OBJECT (window1, radiobutton17, "radiobutton17");
  GLADE_HOOKUP_OBJECT (window1, radiobutton18, "radiobutton18");
  GLADE_HOOKUP_OBJECT (window1, label116, "label116");
  GLADE_HOOKUP_OBJECT (window1, hbox24, "hbox24");
  GLADE_HOOKUP_OBJECT (window1, radiobutton19, "radiobutton19");
  GLADE_HOOKUP_OBJECT (window1, radiobutton20, "radiobutton20");
  GLADE_HOOKUP_OBJECT (window1, radiobutton21, "radiobutton21");
  GLADE_HOOKUP_OBJECT (window1, label87, "label87");
  GLADE_HOOKUP_OBJECT (window1, frame12, "frame12");
  GLADE_HOOKUP_OBJECT (window1, alignment12, "alignment12");
  GLADE_HOOKUP_OBJECT (window1, vbox22, "vbox22");
  GLADE_HOOKUP_OBJECT (window1, label91, "label91");
  GLADE_HOOKUP_OBJECT (window1, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (window1, label21, "label21");
  GLADE_HOOKUP_OBJECT (window1, label22, "label22");
  GLADE_HOOKUP_OBJECT (window1, entry3, "entry3");
  GLADE_HOOKUP_OBJECT (window1, label23, "label23");
  GLADE_HOOKUP_OBJECT (window1, entry4, "entry4");
  GLADE_HOOKUP_OBJECT (window1, hbox10, "hbox10");
  GLADE_HOOKUP_OBJECT (window1, button9, "button9");
  GLADE_HOOKUP_OBJECT (window1, label92, "label92");
  GLADE_HOOKUP_OBJECT (window1, label90, "label90");
  GLADE_HOOKUP_OBJECT (window1, eventbox5, "eventbox5");
  GLADE_HOOKUP_OBJECT (window1, label4, "label4");
  GLADE_HOOKUP_OBJECT_NO_REF (window1, tooltips, "tooltips");

  gtk_widget_grab_focus (drawingarea1);
  return window1;
}

GtkWidget*
create_menu1 (void)
{
  GtkWidget *menu1;
  GtkWidget *item4;
  GtkWidget *item19;
  GtkWidget *item20;
  GtkWidget *item9;
  GtkWidget *item16;
  GtkWidget *item16_menu;
  GtkWidget *item23;
  GtkWidget *item22;
  GtkWidget *item17;
  GtkWidget *item18;
  GtkWidget *item11;
  GtkWidget *item11_menu;
  GtkWidget *item12;
  GtkWidget *item14;
  GtkWidget *item21;
  GtkWidget *item21_menu;
  GtkWidget *itemgeocode1;
  GtkWidget *item6;
  GtkWidget *item6_menu;
  GtkWidget *item5;
  GtkWidget *item7;
  GtkWidget *item8;

  menu1 = gtk_menu_new ();

  item4 = gtk_menu_item_new_with_mnemonic (_("this point"));
  gtk_widget_show (item4);
  gtk_container_add (GTK_CONTAINER (menu1), item4);

  item19 = gtk_check_menu_item_new_with_mnemonic (_("show friends"));
  gtk_widget_show (item19);
  gtk_container_add (GTK_CONTAINER (menu1), item19);

  item20 = gtk_check_menu_item_new_with_mnemonic (_("show POIs"));
  gtk_widget_show (item20);
  gtk_container_add (GTK_CONTAINER (menu1), item20);

  item9 = gtk_check_menu_item_new_with_mnemonic (_("show photos"));
  gtk_widget_show (item9);
  gtk_container_add (GTK_CONTAINER (menu1), item9);

  item16 = gtk_menu_item_new_with_mnemonic (_("ways & routes"));
  gtk_widget_show (item16);
  gtk_container_add (GTK_CONTAINER (menu1), item16);

  item16_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item16), item16_menu);

  item23 = gtk_menu_item_new_with_mnemonic (_("get route"));
  gtk_widget_show (item23);
  gtk_container_add (GTK_CONTAINER (item16_menu), item23);

  item22 = gtk_menu_item_new_with_mnemonic (_("create way"));
  gtk_container_add (GTK_CONTAINER (item16_menu), item22);

  item17 = gtk_menu_item_new_with_mnemonic (_("set WP"));
  gtk_widget_show (item17);
  gtk_container_add (GTK_CONTAINER (item16_menu), item17);

  item18 = gtk_menu_item_new_with_mnemonic (_("unset WP"));
  gtk_widget_show (item18);
  gtk_container_add (GTK_CONTAINER (item16_menu), item18);

  item11 = gtk_menu_item_new_with_mnemonic (_("POIs"));
  gtk_widget_show (item11);
  gtk_container_add (GTK_CONTAINER (menu1), item11);

  item11_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item11), item11_menu);

  item12 = gtk_menu_item_new_with_mnemonic (_("add POI"));
  gtk_widget_show (item12);
  gtk_container_add (GTK_CONTAINER (item11_menu), item12);

  item14 = gtk_menu_item_new_with_mnemonic (_("select POIs"));
  gtk_widget_show (item14);
  gtk_container_add (GTK_CONTAINER (item11_menu), item14);

  item21 = gtk_menu_item_new_with_mnemonic (_("photos"));
  gtk_widget_show (item21);
  gtk_container_add (GTK_CONTAINER (menu1), item21);

  item21_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item21), item21_menu);

  itemgeocode1 = gtk_menu_item_new_with_mnemonic (_("geocode"));
  gtk_widget_show (itemgeocode1);
  gtk_container_add (GTK_CONTAINER (item21_menu), itemgeocode1);

  item6 = gtk_menu_item_new_with_mnemonic (_("my position"));
  gtk_widget_show (item6);
  gtk_container_add (GTK_CONTAINER (menu1), item6);

  item6_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item6), item6_menu);

  item5 = gtk_menu_item_new_with_mnemonic (_("set"));
  gtk_widget_show (item5);
  gtk_container_add (GTK_CONTAINER (item6_menu), item5);

  item7 = gtk_menu_item_new_with_mnemonic (_("unset"));
  gtk_widget_show (item7);
  gtk_container_add (GTK_CONTAINER (item6_menu), item7);

  item8 = gtk_menu_item_new_with_mnemonic (_("map download"));
  gtk_widget_show (item8);
  gtk_container_add (GTK_CONTAINER (menu1), item8);

  g_signal_connect ((gpointer) item4, "activate",
                    G_CALLBACK (on_item4_activate),
                    NULL);
  g_signal_connect ((gpointer) item19, "activate",
                    G_CALLBACK (on_item19_activate),
                    NULL);
  g_signal_connect ((gpointer) item20, "activate",
                    G_CALLBACK (on_item20_activate),
                    NULL);
  g_signal_connect ((gpointer) item9, "activate",
                    G_CALLBACK (on_item9_activate),
                    NULL);
  g_signal_connect ((gpointer) item23, "button_release_event",
                    G_CALLBACK (on_item23_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) item22, "button_release_event",
                    G_CALLBACK (on_item22_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) item17, "button_release_event",
                    G_CALLBACK (on_item17_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) item18, "button_release_event",
                    G_CALLBACK (on_item18_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) item11, "activate",
                    G_CALLBACK (on_item11_activate),
                    NULL);
  g_signal_connect ((gpointer) item12, "button_release_event",
                    G_CALLBACK (on_item12_activate),
                    NULL);
  g_signal_connect ((gpointer) item14, "button_release_event",
                    G_CALLBACK (on_item14_activate),
                    NULL);
  g_signal_connect ((gpointer) itemgeocode1, "button_release_event",
                    G_CALLBACK (on_itemgeocode1_activate),
                    NULL);
  g_signal_connect ((gpointer) item6, "activate",
                    G_CALLBACK (on_item6_activate),
                    NULL);
  g_signal_connect ((gpointer) item5, "button_release_event",
                    G_CALLBACK (on_item5_activate),
                    NULL);
  g_signal_connect ((gpointer) item7, "button_release_event",
                    G_CALLBACK (on_item7_activate),
                    NULL);
  g_signal_connect ((gpointer) item8, "activate",
                    G_CALLBACK (on_item8_activate),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (menu1, menu1, "menu1");
  GLADE_HOOKUP_OBJECT (menu1, item4, "item4");
  GLADE_HOOKUP_OBJECT (menu1, item19, "item19");
  GLADE_HOOKUP_OBJECT (menu1, item20, "item20");
  GLADE_HOOKUP_OBJECT (menu1, item9, "item9");
  GLADE_HOOKUP_OBJECT (menu1, item16, "item16");
  GLADE_HOOKUP_OBJECT (menu1, item16_menu, "item16_menu");
  GLADE_HOOKUP_OBJECT (menu1, item23, "item23");
  GLADE_HOOKUP_OBJECT (menu1, item22, "item22");
  GLADE_HOOKUP_OBJECT (menu1, item17, "item17");
  GLADE_HOOKUP_OBJECT (menu1, item18, "item18");
  GLADE_HOOKUP_OBJECT (menu1, item11, "item11");
  GLADE_HOOKUP_OBJECT (menu1, item11_menu, "item11_menu");
  GLADE_HOOKUP_OBJECT (menu1, item12, "item12");
  GLADE_HOOKUP_OBJECT (menu1, item14, "item14");
  GLADE_HOOKUP_OBJECT (menu1, item21, "item21");
  GLADE_HOOKUP_OBJECT (menu1, item21_menu, "item21_menu");
  GLADE_HOOKUP_OBJECT (menu1, itemgeocode1, "itemgeocode1");
  GLADE_HOOKUP_OBJECT (menu1, item6, "item6");
  GLADE_HOOKUP_OBJECT (menu1, item6_menu, "item6_menu");
  GLADE_HOOKUP_OBJECT (menu1, item5, "item5");
  GLADE_HOOKUP_OBJECT (menu1, item7, "item7");
  GLADE_HOOKUP_OBJECT (menu1, item8, "item8");

  return menu1;
}

GtkWidget*
create_dialog1 (void)
{
  GtkWidget *dialog1;
  GtkWidget *dialog_vbox1;
  GtkWidget *vbox3;
  GtkWidget *label26;
  GtkWidget *entry5;
  GtkWidget *label136;
  GtkWidget *label137;
  GtkWidget *entry20;
  GtkWidget *label139;
  GtkWidget *entry21;
  GtkWidget *checkbutton12;
  GtkWidget *dialog_action_area1;
  GtkWidget *cancelbutton1;
  GtkWidget *okbutton1;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  dialog1 = gtk_dialog_new ();
  gtk_widget_set_size_request (dialog1, 360, -1);
  gtk_window_set_title (GTK_WINDOW (dialog1), _("New Repository"));
  gtk_window_set_position (GTK_WINDOW (dialog1), GTK_WIN_POS_CENTER_ON_PARENT);
  gtk_window_set_modal (GTK_WINDOW (dialog1), TRUE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (dialog1), TRUE);
  gtk_window_set_skip_taskbar_hint (GTK_WINDOW (dialog1), TRUE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (dialog1), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (dialog1), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox1 = GTK_DIALOG (dialog1)->vbox;
  gtk_widget_show (dialog_vbox1);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), vbox3, FALSE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox3), 8);

  label26 = gtk_label_new (_("<b>Name for the new Repository</b>"));
  gtk_widget_show (label26);
  gtk_box_pack_start (GTK_BOX (vbox3), label26, FALSE, FALSE, 5);
  gtk_label_set_use_markup (GTK_LABEL (label26), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label26), 0, 0.5);

  entry5 = gtk_entry_new ();
  gtk_widget_show (entry5);
  gtk_box_pack_start (GTK_BOX (vbox3), entry5, FALSE, FALSE, 0);

  label136 = gtk_label_new (_(" "));
  gtk_widget_show (label136);
  gtk_box_pack_start (GTK_BOX (vbox3), label136, FALSE, FALSE, 0);

  label137 = gtk_label_new (_("<b>URI</b>"));
  gtk_widget_show (label137);
  gtk_box_pack_start (GTK_BOX (vbox3), label137, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label137), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label137), 0, 0.5);

  entry20 = gtk_entry_new ();
  gtk_widget_show (entry20);
  gtk_box_pack_start (GTK_BOX (vbox3), entry20, FALSE, FALSE, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry20), 9679);

  label139 = gtk_label_new (_("<b>Cache Dir</b>"));
  gtk_widget_show (label139);
  gtk_box_pack_start (GTK_BOX (vbox3), label139, FALSE, FALSE, 3);
  gtk_label_set_use_markup (GTK_LABEL (label139), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label139), 0, 0.5);

  entry21 = gtk_entry_new ();
  gtk_widget_show (entry21);
  gtk_box_pack_start (GTK_BOX (vbox3), entry21, FALSE, FALSE, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry21), 9679);

  checkbutton12 = gtk_check_button_new_with_mnemonic (_("xyz instead of zxy"));
  gtk_widget_show (checkbutton12);
  gtk_box_pack_start (GTK_BOX (vbox3), checkbutton12, FALSE, FALSE, 8);

  dialog_action_area1 = GTK_DIALOG (dialog1)->action_area;
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  cancelbutton1 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog1), cancelbutton1, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton1, GTK_CAN_DEFAULT);

  okbutton1 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog1), okbutton1, GTK_RESPONSE_OK);
  gtk_widget_set_sensitive (okbutton1, FALSE);
  GTK_WIDGET_SET_FLAGS (okbutton1, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, okbutton1, _("All fields must be filled in"), NULL);

  g_signal_connect ((gpointer) dialog1, "close",
                    G_CALLBACK (on_dialog1_close),
                    NULL);
  g_signal_connect ((gpointer) dialog1, "response",
                    G_CALLBACK (on_dialog1_response),
                    NULL);
  g_signal_connect ((gpointer) entry5, "changed",
                    G_CALLBACK (on_entry5_changed),
                    NULL);
  g_signal_connect ((gpointer) entry20, "changed",
                    G_CALLBACK (on_entry20_changed),
                    NULL);
  g_signal_connect ((gpointer) entry21, "changed",
                    G_CALLBACK (on_entry21_changed),
                    NULL);
  g_signal_connect ((gpointer) entry21, "activate",
                    G_CALLBACK (on_entry21_activate),
                    NULL);
  g_signal_connect ((gpointer) checkbutton12, "toggled",
                    G_CALLBACK (on_checkbutton12_toggled),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton1, "clicked",
                    G_CALLBACK (on_cancelbutton1_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton1, "clicked",
                    G_CALLBACK (on_okbutton1_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog1, dialog1, "dialog1");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog1, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (dialog1, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (dialog1, label26, "label26");
  GLADE_HOOKUP_OBJECT (dialog1, entry5, "entry5");
  GLADE_HOOKUP_OBJECT (dialog1, label136, "label136");
  GLADE_HOOKUP_OBJECT (dialog1, label137, "label137");
  GLADE_HOOKUP_OBJECT (dialog1, entry20, "entry20");
  GLADE_HOOKUP_OBJECT (dialog1, label139, "label139");
  GLADE_HOOKUP_OBJECT (dialog1, entry21, "entry21");
  GLADE_HOOKUP_OBJECT (dialog1, checkbutton12, "checkbutton12");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog1, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (dialog1, cancelbutton1, "cancelbutton1");
  GLADE_HOOKUP_OBJECT (dialog1, okbutton1, "okbutton1");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog1, tooltips, "tooltips");

  return dialog1;
}

GtkWidget*
create_window2 (void)
{
  GtkWidget *window2;
  GtkWidget *vbox15;
  GtkWidget *vbox25;
  GtkWidget *eventbox4;
  GtkWidget *label64;
  GtkWidget *hbox48;
  GtkWidget *button51;
  GtkWidget *button52;
  GtkWidget *button14;

  window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window2), _("GPS Info"));
  gtk_window_set_position (GTK_WINDOW (window2), GTK_WIN_POS_CENTER);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (window2), TRUE);
  gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window2), TRUE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (window2), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (window2), GDK_WINDOW_TYPE_HINT_DIALOG);

  vbox15 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox15);
  gtk_container_add (GTK_CONTAINER (window2), vbox15);

  vbox25 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox25);
  gtk_box_pack_start (GTK_BOX (vbox15), vbox25, TRUE, TRUE, 9);

  eventbox4 = gtk_event_box_new ();
  gtk_widget_show (eventbox4);
  gtk_box_pack_start (GTK_BOX (vbox25), eventbox4, FALSE, FALSE, 0);

  label64 = gtk_label_new (_("--"));
  gtk_widget_show (label64);
  gtk_container_add (GTK_CONTAINER (eventbox4), label64);
  gtk_label_set_use_markup (GTK_LABEL (label64), TRUE);
  gtk_label_set_line_wrap (GTK_LABEL (label64), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label64), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label64), 4, 2);

  hbox48 = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox15), hbox48, TRUE, TRUE, 2);

  button51 = gtk_button_new_with_mnemonic (_("Distance to\nnext point"));
  gtk_widget_show (button51);
  gtk_box_pack_start (GTK_BOX (hbox48), button51, TRUE, TRUE, 2);

  button52 = gtk_button_new_with_mnemonic (_("Set point as\nmy position"));
  gtk_widget_show (button52);
  gtk_box_pack_start (GTK_BOX (hbox48), button52, TRUE, TRUE, 2);

  button14 = gtk_button_new_with_mnemonic (_("Close"));
  gtk_widget_show (button14);
  gtk_box_pack_start (GTK_BOX (vbox15), button14, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) window2, "delete_event",
                    G_CALLBACK (on_window2_delete_event),
                    NULL);
  g_signal_connect ((gpointer) eventbox4, "button_release_event",
                    G_CALLBACK (on_eventbox4_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) button51, "clicked",
                    G_CALLBACK (on_button51_clicked),
                    NULL);
  g_signal_connect ((gpointer) button52, "clicked",
                    G_CALLBACK (on_button52_clicked),
                    NULL);
  g_signal_connect ((gpointer) button14, "clicked",
                    G_CALLBACK (on_button14_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window2, window2, "window2");
  GLADE_HOOKUP_OBJECT (window2, vbox15, "vbox15");
  GLADE_HOOKUP_OBJECT (window2, vbox25, "vbox25");
  GLADE_HOOKUP_OBJECT (window2, eventbox4, "eventbox4");
  GLADE_HOOKUP_OBJECT (window2, label64, "label64");
  GLADE_HOOKUP_OBJECT (window2, hbox48, "hbox48");
  GLADE_HOOKUP_OBJECT (window2, button51, "button51");
  GLADE_HOOKUP_OBJECT (window2, button52, "button52");
  GLADE_HOOKUP_OBJECT (window2, button14, "button14");

  return window2;
}

GtkWidget*
create_dialog2 (void)
{
  GtkWidget *dialog2;
  GtkWidget *dialog_vbox2;
  GtkWidget *dialog_action_area2;
  GtkWidget *closebutton1;

  dialog2 = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog2), _("unused"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog2), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox2 = GTK_DIALOG (dialog2)->vbox;
  gtk_widget_show (dialog_vbox2);

  dialog_action_area2 = GTK_DIALOG (dialog2)->action_area;
  gtk_widget_show (dialog_action_area2);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area2), GTK_BUTTONBOX_END);

  closebutton1 = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_show (closebutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog2), closebutton1, GTK_RESPONSE_CLOSE);
  GTK_WIDGET_SET_FLAGS (closebutton1, GTK_CAN_DEFAULT);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog2, dialog2, "dialog2");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog2, dialog_vbox2, "dialog_vbox2");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog2, dialog_action_area2, "dialog_action_area2");
  GLADE_HOOKUP_OBJECT (dialog2, closebutton1, "closebutton1");

  return dialog2;
}

GtkWidget*
create_dialog3 (void)
{
  GtkWidget *dialog3;
  GtkWidget *dialog_vbox3;
  GtkWidget *vbox21;
  GtkWidget *label85;
  GtkWidget *entry12;
  GtkWidget *dialog_action_area3;
  GtkWidget *cancelbutton2;
  GtkWidget *okbutton2;

  dialog3 = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog3), _("Trackdir Config"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog3), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox3 = GTK_DIALOG (dialog3)->vbox;
  gtk_widget_show (dialog_vbox3);

  vbox21 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox21);
  gtk_box_pack_start (GTK_BOX (dialog_vbox3), vbox21, TRUE, TRUE, 0);

  label85 = gtk_label_new (_("Directory in which the tracks should be written:"));
  gtk_widget_show (label85);
  gtk_box_pack_start (GTK_BOX (vbox21), label85, FALSE, FALSE, 0);
  gtk_label_set_line_wrap (GTK_LABEL (label85), TRUE);

  entry12 = gtk_entry_new ();
  gtk_widget_show (entry12);
  gtk_box_pack_start (GTK_BOX (vbox21), entry12, FALSE, FALSE, 0);

  dialog_action_area3 = GTK_DIALOG (dialog3)->action_area;
  gtk_widget_show (dialog_action_area3);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area3), GTK_BUTTONBOX_END);

  cancelbutton2 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton2);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog3), cancelbutton2, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton2, GTK_CAN_DEFAULT);

  okbutton2 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton2);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog3), okbutton2, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton2, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) cancelbutton2, "clicked",
                    G_CALLBACK (on_cancelbutton2_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton2, "clicked",
                    G_CALLBACK (on_okbutton2_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog3, dialog3, "dialog3");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog3, dialog_vbox3, "dialog_vbox3");
  GLADE_HOOKUP_OBJECT (dialog3, vbox21, "vbox21");
  GLADE_HOOKUP_OBJECT (dialog3, label85, "label85");
  GLADE_HOOKUP_OBJECT (dialog3, entry12, "entry12");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog3, dialog_action_area3, "dialog_action_area3");
  GLADE_HOOKUP_OBJECT (dialog3, cancelbutton2, "cancelbutton2");
  GLADE_HOOKUP_OBJECT (dialog3, okbutton2, "okbutton2");

  return dialog3;
}

GtkWidget*
create_dialog4 (void)
{
  GtkWidget *dialog4;
  GtkWidget *dialog_vbox4;
  GtkWidget *frame13;
  GtkWidget *alignment14;
  GtkWidget *vbox23;
  GtkWidget *label103;
  GtkWidget *vbox24;
  GtkWidget *radiobutton2;
  GSList *radiobutton2_group = NULL;
  GtkWidget *radiobutton3;
  GtkWidget *radiobutton4;
  GtkWidget *radiobutton5;
  GtkWidget *radiobutton6;
  GtkWidget *radiobutton7;
  GtkWidget *label102;
  GtkWidget *dialog_action_area4;
  GtkWidget *cancelbutton3;
  GtkWidget *okbutton3;

  dialog4 = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog4), _("Map DL"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog4), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox4 = GTK_DIALOG (dialog4)->vbox;
  gtk_widget_show (dialog_vbox4);

  frame13 = gtk_frame_new (NULL);
  gtk_widget_show (frame13);
  gtk_box_pack_start (GTK_BOX (dialog_vbox4), frame13, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame13), 5);

  alignment14 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment14);
  gtk_container_add (GTK_CONTAINER (frame13), alignment14);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment14), 0, 0, 12, 0);

  vbox23 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox23);
  gtk_container_add (GTK_CONTAINER (alignment14), vbox23);

  label103 = gtk_label_new (_("Download maps of currently visible area:"));
  gtk_widget_show (label103);
  gtk_box_pack_start (GTK_BOX (vbox23), label103, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label103, 250, -1);
  gtk_label_set_line_wrap (GTK_LABEL (label103), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label103), 0, 0.5);

  vbox24 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox24);
  gtk_box_pack_start (GTK_BOX (vbox23), vbox24, TRUE, TRUE, 0);

  radiobutton2 = gtk_radio_button_new_with_mnemonic (NULL, _("+ 1 zoom level"));
  gtk_widget_show (radiobutton2);
  gtk_box_pack_start (GTK_BOX (vbox24), radiobutton2, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton2), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton2));

  radiobutton3 = gtk_radio_button_new_with_mnemonic (NULL, _("+ 2 zoom levels"));
  gtk_widget_show (radiobutton3);
  gtk_box_pack_start (GTK_BOX (vbox24), radiobutton3, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton3), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton3));

  radiobutton4 = gtk_radio_button_new_with_mnemonic (NULL, _("+ 3 zoom levels"));
  gtk_widget_show (radiobutton4);
  gtk_box_pack_start (GTK_BOX (vbox24), radiobutton4, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton4), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton4));

  radiobutton5 = gtk_radio_button_new_with_mnemonic (NULL, _("+ 4 zoom levels (~25MB)"));
  gtk_widget_show (radiobutton5);
  gtk_box_pack_start (GTK_BOX (vbox24), radiobutton5, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton5), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton5));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton5), TRUE);

  radiobutton6 = gtk_radio_button_new_with_mnemonic (NULL, _("+ 5 zoom levels (~100MB)"));
  gtk_widget_show (radiobutton6);
  gtk_box_pack_start (GTK_BOX (vbox24), radiobutton6, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton6), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton6));

  radiobutton7 = gtk_radio_button_new_with_mnemonic (NULL, _("+ 6 zoom levels (~400MB)"));
  gtk_widget_show (radiobutton7);
  gtk_box_pack_start (GTK_BOX (vbox24), radiobutton7, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton7), radiobutton2_group);
  radiobutton2_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton7));

  label102 = gtk_label_new (_("<b> Map Download </b>"));
  gtk_widget_show (label102);
  gtk_frame_set_label_widget (GTK_FRAME (frame13), label102);
  gtk_label_set_use_markup (GTK_LABEL (label102), TRUE);

  dialog_action_area4 = GTK_DIALOG (dialog4)->action_area;
  gtk_widget_show (dialog_action_area4);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area4), GTK_BUTTONBOX_END);

  cancelbutton3 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton3);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog4), cancelbutton3, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton3, GTK_CAN_DEFAULT);

  okbutton3 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton3);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog4), okbutton3, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton3, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) cancelbutton3, "clicked",
                    G_CALLBACK (on_cancelbutton3_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton3, "clicked",
                    G_CALLBACK (on_okbutton3_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog4, dialog4, "dialog4");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog4, dialog_vbox4, "dialog_vbox4");
  GLADE_HOOKUP_OBJECT (dialog4, frame13, "frame13");
  GLADE_HOOKUP_OBJECT (dialog4, alignment14, "alignment14");
  GLADE_HOOKUP_OBJECT (dialog4, vbox23, "vbox23");
  GLADE_HOOKUP_OBJECT (dialog4, label103, "label103");
  GLADE_HOOKUP_OBJECT (dialog4, vbox24, "vbox24");
  GLADE_HOOKUP_OBJECT (dialog4, radiobutton2, "radiobutton2");
  GLADE_HOOKUP_OBJECT (dialog4, radiobutton3, "radiobutton3");
  GLADE_HOOKUP_OBJECT (dialog4, radiobutton4, "radiobutton4");
  GLADE_HOOKUP_OBJECT (dialog4, radiobutton5, "radiobutton5");
  GLADE_HOOKUP_OBJECT (dialog4, radiobutton6, "radiobutton6");
  GLADE_HOOKUP_OBJECT (dialog4, radiobutton7, "radiobutton7");
  GLADE_HOOKUP_OBJECT (dialog4, label102, "label102");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog4, dialog_action_area4, "dialog_action_area4");
  GLADE_HOOKUP_OBJECT (dialog4, cancelbutton3, "cancelbutton3");
  GLADE_HOOKUP_OBJECT (dialog4, okbutton3, "okbutton3");

  return dialog4;
}

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
create_dialog6 (void)
{
  GtkWidget *dialog6;
  GtkWidget *dialog_vbox6;
  GtkWidget *combobox4;
  GtkWidget *dialog_action_area6;
  GtkWidget *cancelbutton5;
  GtkWidget *okbutton5;

  dialog6 = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog6), _("Show POIs"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog6), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox6 = GTK_DIALOG (dialog6)->vbox;
  gtk_widget_show (dialog_vbox6);

  combobox4 = gtk_combo_box_new_text ();
  gtk_widget_show (combobox4);
  gtk_box_pack_start (GTK_BOX (dialog_vbox6), combobox4, FALSE, TRUE, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("-- Show All --"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Accomodation"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Businesses"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Car"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Cultural"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Medical"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Cafe / Pub / Nightlife"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Place of Worship"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Public Transportation"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Restaurant"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Services"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Sights / Leisure"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Shopping"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("Sport"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox4), _("My Personal Places"));

  dialog_action_area6 = GTK_DIALOG (dialog6)->action_area;
  gtk_widget_show (dialog_action_area6);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area6), GTK_BUTTONBOX_END);

  cancelbutton5 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton5);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog6), cancelbutton5, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton5, GTK_CAN_DEFAULT);

  okbutton5 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton5);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog6), okbutton5, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton5, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) dialog6, "delete_event",
                    G_CALLBACK (on_dialog6_delete_event),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton5, "clicked",
                    G_CALLBACK (on_cancelbutton5_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton5, "clicked",
                    G_CALLBACK (on_okbutton5_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog6, dialog6, "dialog6");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog6, dialog_vbox6, "dialog_vbox6");
  GLADE_HOOKUP_OBJECT (dialog6, combobox4, "combobox4");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog6, dialog_action_area6, "dialog_action_area6");
  GLADE_HOOKUP_OBJECT (dialog6, cancelbutton5, "cancelbutton5");
  GLADE_HOOKUP_OBJECT (dialog6, okbutton5, "okbutton5");

  gtk_widget_grab_focus (okbutton5);
  return dialog6;
}

GtkWidget*
create_window5 (void)
{
  GtkWidget *window5;
  GtkWidget *vbox29;
  GtkWidget *vbox30;
  GtkWidget *label110;
  GtkWidget *scrolledwindow10;
  GtkWidget *viewport7;
  GtkWidget *label111;
  GtkWidget *label112;
  GtkWidget *table6;
  GtkWidget *button27;
  GtkWidget *alignment18;
  GtkWidget *hbox35;
  GtkWidget *image4;
  GtkWidget *label130;
  GtkWidget *button33;
  GtkWidget *alignment17;
  GtkWidget *hbox34;
  GtkWidget *image3;
  GtkWidget *label129;
  GtkWidget *button34;
  GtkWidget *alignment16;
  GtkWidget *hbox33;
  GtkWidget *image2;
  GtkWidget *label128;
  GtkWidget *button22;
  GtkWidget *alignment15;
  GtkWidget *hbox32;
  GtkWidget *image1;
  GtkWidget *label127;

  window5 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window5), _("POI"));
  gtk_window_set_position (GTK_WINDOW (window5), GTK_WIN_POS_MOUSE);
  gtk_window_set_type_hint (GTK_WINDOW (window5), GDK_WINDOW_TYPE_HINT_DIALOG);

  vbox29 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox29);
  gtk_container_add (GTK_CONTAINER (window5), vbox29);

  vbox30 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox30);
  gtk_box_pack_start (GTK_BOX (vbox29), vbox30, TRUE, TRUE, 0);

  label110 = gtk_label_new (_("<b>-----</b>"));
  gtk_widget_show (label110);
  gtk_box_pack_start (GTK_BOX (vbox30), label110, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label110, 320, -1);
  gtk_label_set_use_markup (GTK_LABEL (label110), TRUE);
  gtk_label_set_line_wrap (GTK_LABEL (label110), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label110), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label110), 0, 2);

  scrolledwindow10 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow10);
  gtk_box_pack_start (GTK_BOX (vbox30), scrolledwindow10, TRUE, TRUE, 0);
  gtk_widget_set_size_request (scrolledwindow10, -1, 200);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow10), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  viewport7 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport7);
  gtk_container_add (GTK_CONTAINER (scrolledwindow10), viewport7);

  label111 = gtk_label_new (_("-"));
  gtk_widget_show (label111);
  gtk_container_add (GTK_CONTAINER (viewport7), label111);
  gtk_widget_set_size_request (label111, 320, -1);
  gtk_label_set_use_markup (GTK_LABEL (label111), TRUE);
  gtk_label_set_line_wrap (GTK_LABEL (label111), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label111), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label111), 0, 2);

  label112 = gtk_label_new (_("<b>-</b>"));
  gtk_widget_show (label112);
  gtk_box_pack_start (GTK_BOX (vbox30), label112, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label112), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label112), 0, 0.5);

  table6 = gtk_table_new (2, 2, FALSE);
  gtk_widget_show (table6);
  gtk_box_pack_start (GTK_BOX (vbox29), table6, FALSE, TRUE, 0);
  gtk_table_set_col_spacings (GTK_TABLE (table6), 3);

  button27 = gtk_button_new ();
  gtk_widget_show (button27);
  gtk_table_attach (GTK_TABLE (table6), button27, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 2, 2);

  alignment18 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment18);
  gtk_container_add (GTK_CONTAINER (button27), alignment18);

  hbox35 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox35);
  gtk_container_add (GTK_CONTAINER (alignment18), hbox35);

  image4 = gtk_image_new_from_stock ("gtk-jump-to", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image4);
  gtk_box_pack_start (GTK_BOX (hbox35), image4, FALSE, FALSE, 0);

  label130 = gtk_label_new_with_mnemonic (_("Go To "));
  gtk_widget_show (label130);
  gtk_box_pack_start (GTK_BOX (hbox35), label130, FALSE, FALSE, 0);

  button33 = gtk_button_new ();
  gtk_widget_show (button33);
  gtk_table_attach (GTK_TABLE (table6), button33, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 2, 2);

  alignment17 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment17);
  gtk_container_add (GTK_CONTAINER (button33), alignment17);

  hbox34 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox34);
  gtk_container_add (GTK_CONTAINER (alignment17), hbox34);

  image3 = gtk_image_new_from_stock ("gtk-edit", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image3);
  gtk_box_pack_start (GTK_BOX (hbox34), image3, FALSE, FALSE, 0);

  label129 = gtk_label_new_with_mnemonic (_("Edit"));
  gtk_widget_show (label129);
  gtk_box_pack_start (GTK_BOX (hbox34), label129, FALSE, FALSE, 0);

  button34 = gtk_button_new ();
  gtk_widget_show (button34);
  gtk_table_attach (GTK_TABLE (table6), button34, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 2, 2);

  alignment16 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment16);
  gtk_container_add (GTK_CONTAINER (button34), alignment16);

  hbox33 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox33);
  gtk_container_add (GTK_CONTAINER (alignment16), hbox33);

  image2 = gtk_image_new_from_stock ("gtk-delete", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image2);
  gtk_box_pack_start (GTK_BOX (hbox33), image2, FALSE, FALSE, 0);

  label128 = gtk_label_new_with_mnemonic (_("Delete"));
  gtk_widget_show (label128);
  gtk_box_pack_start (GTK_BOX (hbox33), label128, FALSE, FALSE, 0);

  button22 = gtk_button_new ();
  gtk_widget_show (button22);
  gtk_table_attach (GTK_TABLE (table6), button22, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 2, 2);

  alignment15 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment15);
  gtk_container_add (GTK_CONTAINER (button22), alignment15);

  hbox32 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox32);
  gtk_container_add (GTK_CONTAINER (alignment15), hbox32);

  image1 = gtk_image_new_from_stock ("gtk-close", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image1);
  gtk_box_pack_start (GTK_BOX (hbox32), image1, FALSE, FALSE, 0);

  label127 = gtk_label_new_with_mnemonic (_("Close"));
  gtk_widget_show (label127);
  gtk_box_pack_start (GTK_BOX (hbox32), label127, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) button22, "clicked",
                    G_CALLBACK (on_button22_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window5, window5, "window5");
  GLADE_HOOKUP_OBJECT (window5, vbox29, "vbox29");
  GLADE_HOOKUP_OBJECT (window5, vbox30, "vbox30");
  GLADE_HOOKUP_OBJECT (window5, label110, "label110");
  GLADE_HOOKUP_OBJECT (window5, scrolledwindow10, "scrolledwindow10");
  GLADE_HOOKUP_OBJECT (window5, viewport7, "viewport7");
  GLADE_HOOKUP_OBJECT (window5, label111, "label111");
  GLADE_HOOKUP_OBJECT (window5, label112, "label112");
  GLADE_HOOKUP_OBJECT (window5, table6, "table6");
  GLADE_HOOKUP_OBJECT (window5, button27, "button27");
  GLADE_HOOKUP_OBJECT (window5, alignment18, "alignment18");
  GLADE_HOOKUP_OBJECT (window5, hbox35, "hbox35");
  GLADE_HOOKUP_OBJECT (window5, image4, "image4");
  GLADE_HOOKUP_OBJECT (window5, label130, "label130");
  GLADE_HOOKUP_OBJECT (window5, button33, "button33");
  GLADE_HOOKUP_OBJECT (window5, alignment17, "alignment17");
  GLADE_HOOKUP_OBJECT (window5, hbox34, "hbox34");
  GLADE_HOOKUP_OBJECT (window5, image3, "image3");
  GLADE_HOOKUP_OBJECT (window5, label129, "label129");
  GLADE_HOOKUP_OBJECT (window5, button34, "button34");
  GLADE_HOOKUP_OBJECT (window5, alignment16, "alignment16");
  GLADE_HOOKUP_OBJECT (window5, hbox33, "hbox33");
  GLADE_HOOKUP_OBJECT (window5, image2, "image2");
  GLADE_HOOKUP_OBJECT (window5, label128, "label128");
  GLADE_HOOKUP_OBJECT (window5, button22, "button22");
  GLADE_HOOKUP_OBJECT (window5, alignment15, "alignment15");
  GLADE_HOOKUP_OBJECT (window5, hbox32, "hbox32");
  GLADE_HOOKUP_OBJECT (window5, image1, "image1");
  GLADE_HOOKUP_OBJECT (window5, label127, "label127");

  return window5;
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
create_window10 (void)
{
  GtkWidget *window10;
  GtkWidget *vbox36;
  GtkWidget *scrolledwindow7;
  GtkWidget *viewport5;
  GtkWidget *vbox37;
  GtkWidget *hbox28;
  GtkWidget *button30;
  GtkWidget *label120;
  GtkWidget *entry17;
  GtkWidget *label121;
  GtkWidget *entry18;
  GtkWidget *label123;
  GtkWidget *entry19;
  GtkWidget *hbox27;
  GtkWidget *radiobutton22;
  GSList *radiobutton22_group = NULL;
  GtkWidget *radiobutton23;
  GtkWidget *label122;
  GtkWidget *combobox5;
  GtkWidget *combobox6;
  GtkWidget *label124;
  GtkWidget *scrolledwindow8;
  GtkWidget *textview2;
  GtkWidget *hbox29;
  GtkWidget *radiobutton24;
  GSList *radiobutton24_group = NULL;
  GtkWidget *radiobutton25;
  GtkWidget *radiobutton26;
  GtkWidget *checkbutton11;
  GtkWidget *label126;
  GtkWidget *toolbar3;
  GtkIconSize tmp_toolbar_icon_size;
  GtkWidget *toolitem11;
  GtkWidget *toolitem12;
  GtkWidget *label125;
  GtkWidget *toolitem13;
  GtkWidget *button31;
  GtkWidget *toolitem14;
  GtkWidget *button32;

  window10 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window10), _("Edit POI"));
  gtk_window_set_modal (GTK_WINDOW (window10), TRUE);
  gtk_window_set_default_size (GTK_WINDOW (window10), 470, 470);

  vbox36 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox36);
  gtk_container_add (GTK_CONTAINER (window10), vbox36);

  scrolledwindow7 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow7);
  gtk_box_pack_start (GTK_BOX (vbox36), scrolledwindow7, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow7), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

  viewport5 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport5);
  gtk_container_add (GTK_CONTAINER (scrolledwindow7), viewport5);
  gtk_container_set_border_width (GTK_CONTAINER (viewport5), 5);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport5), GTK_SHADOW_NONE);

  vbox37 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox37);
  gtk_container_add (GTK_CONTAINER (viewport5), vbox37);

  hbox28 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox28);
  gtk_box_pack_start (GTK_BOX (vbox37), hbox28, FALSE, TRUE, 0);
  gtk_widget_set_size_request (hbox28, -1, 40);

  button30 = gtk_button_new_with_mnemonic (_("GPS"));
  gtk_widget_show (button30);
  gtk_box_pack_start (GTK_BOX (hbox28), button30, FALSE, FALSE, 1);
  gtk_widget_set_size_request (button30, -1, 40);

  label120 = gtk_label_new (_("Lat: "));
  gtk_widget_show (label120);
  gtk_box_pack_start (GTK_BOX (hbox28), label120, FALSE, FALSE, 0);
  gtk_misc_set_padding (GTK_MISC (label120), 1, 0);

  entry17 = gtk_entry_new ();
  gtk_widget_show (entry17);
  gtk_box_pack_start (GTK_BOX (hbox28), entry17, TRUE, TRUE, 0);
  gtk_entry_set_width_chars (GTK_ENTRY (entry17), 5);

  label121 = gtk_label_new (_(" Lon: "));
  gtk_widget_show (label121);
  gtk_box_pack_start (GTK_BOX (hbox28), label121, FALSE, FALSE, 0);
  gtk_misc_set_padding (GTK_MISC (label121), 1, 0);

  entry18 = gtk_entry_new ();
  gtk_widget_show (entry18);
  gtk_box_pack_start (GTK_BOX (hbox28), entry18, TRUE, TRUE, 0);
  gtk_entry_set_width_chars (GTK_ENTRY (entry18), 5);

  label123 = gtk_label_new (_("Name - Keywords / Tags:"));
  gtk_widget_show (label123);
  gtk_box_pack_start (GTK_BOX (vbox37), label123, FALSE, FALSE, 7);
  gtk_misc_set_alignment (GTK_MISC (label123), 0, 0.5);

  entry19 = gtk_entry_new ();
  gtk_widget_show (entry19);
  gtk_box_pack_start (GTK_BOX (vbox37), entry19, FALSE, FALSE, 0);

  hbox27 = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_end (GTK_BOX (vbox37), hbox27, FALSE, FALSE, 0);

  radiobutton22 = gtk_radio_button_new_with_mnemonic (NULL, _("personal"));
  gtk_widget_show (radiobutton22);
  gtk_box_pack_start (GTK_BOX (hbox27), radiobutton22, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton22), radiobutton22_group);
  radiobutton22_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton22));

  radiobutton23 = gtk_radio_button_new_with_mnemonic (NULL, _("public"));
  gtk_widget_show (radiobutton23);
  gtk_box_pack_start (GTK_BOX (hbox27), radiobutton23, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (radiobutton23), 2);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton23), radiobutton22_group);
  radiobutton22_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton23));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton23), TRUE);

  label122 = gtk_label_new (_("Category:"));
  gtk_box_pack_end (GTK_BOX (vbox37), label122, FALSE, FALSE, 7);
  gtk_misc_set_alignment (GTK_MISC (label122), 0, 0.5);

  combobox5 = gtk_combo_box_new_text ();
  gtk_box_pack_end (GTK_BOX (vbox37), combobox5, FALSE, FALSE, 1);
  GTK_WIDGET_SET_FLAGS (combobox5, GTK_CAN_FOCUS);
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("- please choose -"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Accomodation"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Businesses"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Car"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Cultural"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Medical"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Nightlife"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Place of Worship"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Public Transportation"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Restaurant & Food"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Services"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Sights & Leisure"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Shopping"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (combobox5), _("Sport"));
  gtk_combo_box_set_add_tearoffs (GTK_COMBO_BOX (combobox5), TRUE);

  combobox6 = gtk_combo_box_new_text ();
  gtk_box_pack_end (GTK_BOX (vbox37), combobox6, FALSE, FALSE, 0);

  label124 = gtk_label_new (_("Description:"));
  gtk_widget_show (label124);
  gtk_box_pack_start (GTK_BOX (vbox37), label124, FALSE, FALSE, 7);
  gtk_misc_set_alignment (GTK_MISC (label124), 0, 0.5);

  scrolledwindow8 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow8);
  gtk_box_pack_start (GTK_BOX (vbox37), scrolledwindow8, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow8), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow8), GTK_SHADOW_IN);

  textview2 = gtk_text_view_new ();
  gtk_widget_show (textview2);
  gtk_container_add (GTK_CONTAINER (scrolledwindow8), textview2);
  gtk_widget_set_size_request (textview2, 300, -1);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview2), GTK_WRAP_WORD);
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview2), 2);

  hbox29 = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox37), hbox29, TRUE, TRUE, 0);

  radiobutton24 = gtk_radio_button_new_with_mnemonic (NULL, _("budget"));
  gtk_widget_show (radiobutton24);
  gtk_box_pack_start (GTK_BOX (hbox29), radiobutton24, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton24), radiobutton24_group);
  radiobutton24_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton24));

  radiobutton25 = gtk_radio_button_new_with_mnemonic (NULL, _("medium"));
  gtk_widget_show (radiobutton25);
  gtk_box_pack_start (GTK_BOX (hbox29), radiobutton25, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton25), radiobutton24_group);
  radiobutton24_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton25));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton25), TRUE);

  radiobutton26 = gtk_radio_button_new_with_mnemonic (NULL, _("exclusive"));
  gtk_widget_show (radiobutton26);
  gtk_box_pack_start (GTK_BOX (hbox29), radiobutton26, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton26), radiobutton24_group);
  radiobutton24_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton26));

  checkbutton11 = gtk_check_button_new_with_mnemonic (_("extended opening hours"));
  gtk_box_pack_start (GTK_BOX (vbox37), checkbutton11, FALSE, FALSE, 0);

  label126 = gtk_label_new (_("<b>-</b>"));
  gtk_widget_show (label126);
  gtk_box_pack_start (GTK_BOX (vbox37), label126, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label126), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label126), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label126), 2, 2);

  toolbar3 = gtk_toolbar_new ();
  gtk_widget_show (toolbar3);
  gtk_box_pack_start (GTK_BOX (vbox36), toolbar3, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (toolbar3), 6);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar3), GTK_TOOLBAR_ICONS);
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar3));

  toolitem11 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem11);
  gtk_container_add (GTK_CONTAINER (toolbar3), toolitem11);

  toolitem12 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem12);
  gtk_container_add (GTK_CONTAINER (toolbar3), toolitem12);

  label125 = gtk_label_new (_("       "));
  gtk_widget_show (label125);
  gtk_container_add (GTK_CONTAINER (toolitem12), label125);

  toolitem13 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem13);
  gtk_container_add (GTK_CONTAINER (toolbar3), toolitem13);

  button31 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (button31);
  gtk_container_add (GTK_CONTAINER (toolitem13), button31);
  gtk_container_set_border_width (GTK_CONTAINER (button31), 7);

  toolitem14 = (GtkWidget*) gtk_tool_item_new ();
  gtk_widget_show (toolitem14);
  gtk_container_add (GTK_CONTAINER (toolbar3), toolitem14);

  button32 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (button32);
  gtk_container_add (GTK_CONTAINER (toolitem14), button32);
  gtk_container_set_border_width (GTK_CONTAINER (button32), 7);

  g_signal_connect ((gpointer) button30, "clicked",
                    G_CALLBACK (on_button30_clicked),
                    NULL);
  g_signal_connect ((gpointer) combobox5, "changed",
                    G_CALLBACK (on_combobox2_changed),
                    NULL);
  g_signal_connect ((gpointer) button31, "clicked",
                    G_CALLBACK (on_cancelbutton5a_clicked),
                    NULL);
  g_signal_connect ((gpointer) button32, "clicked",
                    G_CALLBACK (on_okbutton5a_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window10, window10, "window10");
  GLADE_HOOKUP_OBJECT (window10, vbox36, "vbox36");
  GLADE_HOOKUP_OBJECT (window10, scrolledwindow7, "scrolledwindow7");
  GLADE_HOOKUP_OBJECT (window10, viewport5, "viewport5");
  GLADE_HOOKUP_OBJECT (window10, vbox37, "vbox37");
  GLADE_HOOKUP_OBJECT (window10, hbox28, "hbox28");
  GLADE_HOOKUP_OBJECT (window10, button30, "button30");
  GLADE_HOOKUP_OBJECT (window10, label120, "label120");
  GLADE_HOOKUP_OBJECT (window10, entry17, "entry17");
  GLADE_HOOKUP_OBJECT (window10, label121, "label121");
  GLADE_HOOKUP_OBJECT (window10, entry18, "entry18");
  GLADE_HOOKUP_OBJECT (window10, label123, "label123");
  GLADE_HOOKUP_OBJECT (window10, entry19, "entry19");
  GLADE_HOOKUP_OBJECT (window10, hbox27, "hbox27");
  GLADE_HOOKUP_OBJECT (window10, radiobutton22, "radiobutton22");
  GLADE_HOOKUP_OBJECT (window10, radiobutton23, "radiobutton23");
  GLADE_HOOKUP_OBJECT (window10, label122, "label122");
  GLADE_HOOKUP_OBJECT (window10, combobox5, "combobox5");
  GLADE_HOOKUP_OBJECT (window10, combobox6, "combobox6");
  GLADE_HOOKUP_OBJECT (window10, label124, "label124");
  GLADE_HOOKUP_OBJECT (window10, scrolledwindow8, "scrolledwindow8");
  GLADE_HOOKUP_OBJECT (window10, textview2, "textview2");
  GLADE_HOOKUP_OBJECT (window10, hbox29, "hbox29");
  GLADE_HOOKUP_OBJECT (window10, radiobutton24, "radiobutton24");
  GLADE_HOOKUP_OBJECT (window10, radiobutton25, "radiobutton25");
  GLADE_HOOKUP_OBJECT (window10, radiobutton26, "radiobutton26");
  GLADE_HOOKUP_OBJECT (window10, checkbutton11, "checkbutton11");
  GLADE_HOOKUP_OBJECT (window10, label126, "label126");
  GLADE_HOOKUP_OBJECT (window10, toolbar3, "toolbar3");
  GLADE_HOOKUP_OBJECT (window10, toolitem11, "toolitem11");
  GLADE_HOOKUP_OBJECT (window10, toolitem12, "toolitem12");
  GLADE_HOOKUP_OBJECT (window10, label125, "label125");
  GLADE_HOOKUP_OBJECT (window10, toolitem13, "toolitem13");
  GLADE_HOOKUP_OBJECT (window10, button31, "button31");
  GLADE_HOOKUP_OBJECT (window10, toolitem14, "toolitem14");
  GLADE_HOOKUP_OBJECT (window10, button32, "button32");

  gtk_widget_grab_focus (radiobutton23);
  return window10;
}

GtkWidget*
create_dialog7 (void)
{
  GtkWidget *dialog7;
  GtkWidget *dialog_vbox7;
  GtkWidget *label131;
  GtkWidget *dialog_action_area7;
  GtkWidget *cancelbutton6;
  GtkWidget *okbutton6;

  dialog7 = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog7), _("Delete POI?"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog7), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox7 = GTK_DIALOG (dialog7)->vbox;
  gtk_widget_show (dialog_vbox7);

  label131 = gtk_label_new (_("Do you really want to \ndelete this Point of Interest?"));
  gtk_widget_show (label131);
  gtk_box_pack_start (GTK_BOX (dialog_vbox7), label131, TRUE, TRUE, 0);
  gtk_label_set_line_wrap (GTK_LABEL (label131), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label131), 0, 0);
  gtk_misc_set_padding (GTK_MISC (label131), 8, 8);

  dialog_action_area7 = GTK_DIALOG (dialog7)->action_area;
  gtk_widget_show (dialog_action_area7);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area7), GTK_BUTTONBOX_END);

  cancelbutton6 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton6);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog7), cancelbutton6, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton6, GTK_CAN_DEFAULT);

  okbutton6 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton6);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog7), okbutton6, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton6, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) dialog7, "delete_event",
                    G_CALLBACK (on_dialog7_delete_event),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton6, "clicked",
                    G_CALLBACK (on_cancelbutton6_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog7, dialog7, "dialog7");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog7, dialog_vbox7, "dialog_vbox7");
  GLADE_HOOKUP_OBJECT (dialog7, label131, "label131");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog7, dialog_action_area7, "dialog_action_area7");
  GLADE_HOOKUP_OBJECT (dialog7, cancelbutton6, "cancelbutton6");
  GLADE_HOOKUP_OBJECT (dialog7, okbutton6, "okbutton6");

  return dialog7;
}

GtkWidget*
create_window12 (void)
{
  GtkWidget *window12;
  GtkWidget *vbox38;
  GtkWidget *label134;
  GtkWidget *scrolledwindow9;
  GtkWidget *viewport6;
  GtkWidget *vbox39;
  GtkWidget *hbox36;
  GtkWidget *label135;
  GtkWidget *button37;

  window12 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window12, 420, 460);
  gtk_window_set_title (GTK_WINDOW (window12), _("Load track..."));

  vbox38 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox38);
  gtk_container_add (GTK_CONTAINER (window12), vbox38);

  label134 = gtk_label_new (_("<b>Choose track to open (.log / .gpx)</b>"));
  gtk_widget_show (label134);
  gtk_box_pack_start (GTK_BOX (vbox38), label134, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label134), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label134), 0, 0.5);
  gtk_misc_set_padding (GTK_MISC (label134), 2, 4);

  scrolledwindow9 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow9);
  gtk_box_pack_start (GTK_BOX (vbox38), scrolledwindow9, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow9), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  viewport6 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport6);
  gtk_container_add (GTK_CONTAINER (scrolledwindow9), viewport6);

  vbox39 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox39);
  gtk_container_add (GTK_CONTAINER (viewport6), vbox39);

  hbox36 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox36);
  gtk_box_pack_start (GTK_BOX (vbox38), hbox36, FALSE, FALSE, 5);

  label135 = gtk_label_new ("");
  gtk_widget_show (label135);
  gtk_box_pack_start (GTK_BOX (hbox36), label135, TRUE, FALSE, 0);

  button37 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (button37);
  gtk_box_pack_start (GTK_BOX (hbox36), button37, FALSE, FALSE, 4);

  g_signal_connect ((gpointer) window12, "delete_event",
                    G_CALLBACK (on_window12_delete_event),
                    NULL);
  g_signal_connect ((gpointer) button37, "clicked",
                    G_CALLBACK (on_button37_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (window12, window12, "window12");
  GLADE_HOOKUP_OBJECT (window12, vbox38, "vbox38");
  GLADE_HOOKUP_OBJECT (window12, label134, "label134");
  GLADE_HOOKUP_OBJECT (window12, scrolledwindow9, "scrolledwindow9");
  GLADE_HOOKUP_OBJECT (window12, viewport6, "viewport6");
  GLADE_HOOKUP_OBJECT (window12, vbox39, "vbox39");
  GLADE_HOOKUP_OBJECT (window12, hbox36, "hbox36");
  GLADE_HOOKUP_OBJECT (window12, label135, "label135");
  GLADE_HOOKUP_OBJECT (window12, button37, "button37");

  return window12;
}

GtkWidget*
create_dialog8 (void)
{
  GtkWidget *dialog8;
  GtkWidget *dialog_vbox8;
  GtkWidget *vbox41;
  GtkWidget *label144;
  GtkWidget *entry24;
  GtkWidget *label145;
  GtkWidget *label146;
  GtkWidget *entry25;
  GtkWidget *label147;
  GtkWidget *entry26;
  GtkWidget *checkbutton13;
  GtkWidget *dialog_action_area9;
  GtkWidget *cancelbutton7;
  GtkWidget *okbutton7;

  dialog8 = gtk_dialog_new ();
  gtk_widget_set_size_request (dialog8, 360, -1);
  GTK_WIDGET_SET_FLAGS (dialog8, GTK_CAN_FOCUS);
  gtk_window_set_title (GTK_WINDOW (dialog8), _("Edit Repository"));
  gtk_window_set_type_hint (GTK_WINDOW (dialog8), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox8 = GTK_DIALOG (dialog8)->vbox;
  gtk_widget_show (dialog_vbox8);

  vbox41 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox41);
  gtk_box_pack_start (GTK_BOX (dialog_vbox8), vbox41, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (vbox41), 8);

  label144 = gtk_label_new (_("<b>Repository Name</b>"));
  gtk_widget_show (label144);
  gtk_box_pack_start (GTK_BOX (vbox41), label144, FALSE, FALSE, 5);
  gtk_label_set_use_markup (GTK_LABEL (label144), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label144), 0, 0.5);

  entry24 = gtk_entry_new ();
  gtk_widget_show (entry24);
  gtk_box_pack_start (GTK_BOX (vbox41), entry24, FALSE, FALSE, 0);

  label145 = gtk_label_new (_(" "));
  gtk_widget_show (label145);
  gtk_box_pack_start (GTK_BOX (vbox41), label145, FALSE, FALSE, 0);

  label146 = gtk_label_new (_("<b>URI</b>"));
  gtk_widget_show (label146);
  gtk_box_pack_start (GTK_BOX (vbox41), label146, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (label146), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label146), 0, 0.5);

  entry25 = gtk_entry_new ();
  gtk_widget_show (entry25);
  gtk_box_pack_start (GTK_BOX (vbox41), entry25, FALSE, FALSE, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry25), 9679);

  label147 = gtk_label_new (_("<b>Cache Dir</b>"));
  gtk_widget_show (label147);
  gtk_box_pack_start (GTK_BOX (vbox41), label147, FALSE, FALSE, 3);
  gtk_label_set_use_markup (GTK_LABEL (label147), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label147), 0, 0.5);

  entry26 = gtk_entry_new ();
  gtk_widget_show (entry26);
  gtk_box_pack_start (GTK_BOX (vbox41), entry26, FALSE, FALSE, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (entry26), 9679);

  checkbutton13 = gtk_check_button_new_with_mnemonic (_("xyz instead of zxy"));
  gtk_widget_show (checkbutton13);
  gtk_box_pack_start (GTK_BOX (vbox41), checkbutton13, FALSE, FALSE, 8);

  dialog_action_area9 = GTK_DIALOG (dialog8)->action_area;
  gtk_widget_show (dialog_action_area9);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area9), GTK_BUTTONBOX_END);

  cancelbutton7 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton7);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog8), cancelbutton7, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton7, GTK_CAN_DEFAULT);

  okbutton7 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton7);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog8), okbutton7, GTK_RESPONSE_OK);
  gtk_widget_set_sensitive (okbutton7, FALSE);
  GTK_WIDGET_SET_FLAGS (okbutton7, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) entry24, "changed",
                    G_CALLBACK (on_entry24_changed),
                    NULL);
  g_signal_connect ((gpointer) entry25, "changed",
                    G_CALLBACK (on_entry25_changed),
                    NULL);
  g_signal_connect ((gpointer) entry26, "changed",
                    G_CALLBACK (on_entry26_changed),
                    NULL);
  g_signal_connect ((gpointer) checkbutton13, "toggled",
                    G_CALLBACK (on_checkbutton13_toggled),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton7, "clicked",
                    G_CALLBACK (on_cancelbutton7_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton7, "clicked",
                    G_CALLBACK (on_okbutton7_clicked),
                    NULL);

  
  GLADE_HOOKUP_OBJECT_NO_REF (dialog8, dialog8, "dialog8");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog8, dialog_vbox8, "dialog_vbox8");
  GLADE_HOOKUP_OBJECT (dialog8, vbox41, "vbox41");
  GLADE_HOOKUP_OBJECT (dialog8, label144, "label144");
  GLADE_HOOKUP_OBJECT (dialog8, entry24, "entry24");
  GLADE_HOOKUP_OBJECT (dialog8, label145, "label145");
  GLADE_HOOKUP_OBJECT (dialog8, label146, "label146");
  GLADE_HOOKUP_OBJECT (dialog8, entry25, "entry25");
  GLADE_HOOKUP_OBJECT (dialog8, label147, "label147");
  GLADE_HOOKUP_OBJECT (dialog8, entry26, "entry26");
  GLADE_HOOKUP_OBJECT (dialog8, checkbutton13, "checkbutton13");
  GLADE_HOOKUP_OBJECT_NO_REF (dialog8, dialog_action_area9, "dialog_action_area9");
  GLADE_HOOKUP_OBJECT (dialog8, cancelbutton7, "cancelbutton7");
  GLADE_HOOKUP_OBJECT (dialog8, okbutton7, "okbutton7");

  return dialog8;
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
create_filechooserdialog1 (void)
{
  GtkWidget *filechooserdialog1;
  GtkWidget *dialog_vbox10;
  GtkWidget *filechooser_label;
  GtkWidget *dialog_action_area11;
  GtkWidget *button42;
  GtkWidget *button43;

  filechooserdialog1 = gtk_file_chooser_dialog_new (_("Please choose"), NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
  gtk_widget_set_size_request (filechooserdialog1, 450, -1);
  gtk_container_set_border_width (GTK_CONTAINER (filechooserdialog1), 5);
  gtk_window_set_type_hint (GTK_WINDOW (filechooserdialog1), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox10 = GTK_DIALOG (filechooserdialog1)->vbox;
  gtk_widget_show (dialog_vbox10);

  filechooser_label = gtk_label_new (_("<b>This is important!</b>\n"));
  gtk_widget_show (filechooser_label);
  gtk_box_pack_start (GTK_BOX (dialog_vbox10), filechooser_label, FALSE, FALSE, 0);
  gtk_label_set_use_markup (GTK_LABEL (filechooser_label), TRUE);
  gtk_misc_set_alignment (GTK_MISC (filechooser_label), 0.02, 0.5);

  dialog_action_area11 = GTK_DIALOG (filechooserdialog1)->action_area;
  gtk_widget_show (dialog_action_area11);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area11), GTK_BUTTONBOX_END);

  button42 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (button42);
  gtk_dialog_add_action_widget (GTK_DIALOG (filechooserdialog1), button42, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (button42, GTK_CAN_DEFAULT);

  button43 = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_show (button43);
  gtk_dialog_add_action_widget (GTK_DIALOG (filechooserdialog1), button43, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (button43, GTK_CAN_DEFAULT);

  
  GLADE_HOOKUP_OBJECT_NO_REF (filechooserdialog1, filechooserdialog1, "filechooserdialog1");
  GLADE_HOOKUP_OBJECT_NO_REF (filechooserdialog1, dialog_vbox10, "dialog_vbox10");
  GLADE_HOOKUP_OBJECT (filechooserdialog1, filechooser_label, "filechooser_label");
  GLADE_HOOKUP_OBJECT_NO_REF (filechooserdialog1, dialog_action_area11, "dialog_action_area11");
  GLADE_HOOKUP_OBJECT (filechooserdialog1, button42, "button42");
  GLADE_HOOKUP_OBJECT (filechooserdialog1, button43, "button43");

  gtk_widget_grab_default (button43);
  return filechooserdialog1;
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

