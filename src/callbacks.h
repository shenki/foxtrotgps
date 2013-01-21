#include <gtk/gtk.h>

void
paint_track();

gboolean
on_drawingarea1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_motion_notify_event    (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_configure_event        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_button1_clicked                     (GtkToggleToolButton *button,
                                        gpointer         user_data);

gboolean
on_drawingarea1_button_release_event   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_vscale1_value_changed               (GtkRange        *range,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkToggleToolButton *button,
                                        gpointer         user_data);

gboolean
on_window1_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_window1_destroy_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_vscale1_change_value                (GtkRange        *range,
                                        GtkScrollType    scroll,
                                        gdouble          value,
                                        gpointer         user_data);

gboolean
on_vscale1_button_press_event          (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_vscale1_button_release_event        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_combobox1_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_dialog1_close                       (GtkDialog       *dialog,
                                        gpointer         user_data);

void
on_dialog1_response                    (GtkDialog       *dialog,
                                        gint             response_id,
                                        gpointer         user_data);

void
on_cancelbutton1_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry1_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry2_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry1_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry2_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_item3_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_item4_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);


void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data);


gboolean
on_drawinarea1_scroll_event            (GtkWidget       *widget,
                                        GdkEventScroll   *event,
                                        gpointer         user_data);

void
on_button15_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry7_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry8_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button18_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button20_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton2_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton2_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton9_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_item6_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);


void
on_item8_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_cancelbutton3_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton3_clicked                   (GtkButton       *button,
                                        gpointer         user_data);


gboolean
on_drawingarea2_configure_event        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

gboolean
on_drawingarea2_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_closebutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_item10_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_item11_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton4_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton4_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton5_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton5_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_dialog6_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_combobox2_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_item15_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button22_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_item5_activate                      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_item7_activate                      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_item12_activate                     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_item14_activate                     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);


void
on_entry16_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_radiobutton14_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton15_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton16_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton17_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton18_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton19_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton20_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton21_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);


gboolean
on_button11_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_togglebutton2_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cancelbutton4_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton4_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button26_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_window2_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button27_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_window3_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_item19_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_item20_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_null_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_item9_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
repaint_all();

void
on_button29_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button33_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton5_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton5_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton5a_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton5a_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawingarea1_key_press_event        (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_button34_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_dialog7_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_cancelbutton6_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton6_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button35_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry3_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry4_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_button36_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_window12_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button37_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button38_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton7_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton7_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry5_changed                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry20_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry21_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_checkbutton12_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_entry24_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry25_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_entry26_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_checkbutton13_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_entry21_activate                    (GtkEntry        *entry,
                                        gpointer         user_data);

gboolean
on_eventbox1_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_eventbox1_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_eventbox1_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_eventbox2_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea3_configure_event        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

gboolean
on_drawingarea3_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

//void
//on_itemgeocode1_activate               (GtkMenuItem     *menuitem,
//                                        gpointer         user_data);

void
on_button39_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button40_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton8_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton8_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button44_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button45_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button46_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button47_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button48_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton9_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button49_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_eventbox3_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_checkbutton14_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_combobox7_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data);

gboolean
on_dialog_geocode_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_dialog_image_data_delete_event      (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_eventbox4_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_entry28_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_button50_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_closebutton2_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton27_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton28_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton29_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button51_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button52_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_itemgeocode1_activate               (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_item17_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_add_wp_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_clear_route_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_save_route_gpx_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_save_route_tomtom_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_route_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_item18_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);


void
on_button57_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button58_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry30_activate                    (GtkEntry        *entry,
                                        gpointer         user_data);

void
on_cancelbutton9_clicked               (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_eventbox5_button_release_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_item23_button_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_button59_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button60_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button61_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton10_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton11_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_dialog10_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_entry32_activate                    (GtkEntry        *entry,
                                        gpointer         user_data);

void
on_combobox8_changed                   (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_button76_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button69_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button71_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button70_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button76_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton15_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button78_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton16_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton17_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button79_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry29_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_checkbutton18_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_entry33_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
set_map_detail_menuitem_sensitivity (GtkMenuItem *zoomout, GtkMenuItem *menu);

void
activate_more_map_details (GtkMenuItem *menu_item, gpointer user_data);

void
activate_larger_map_details (GtkMenuItem *larger_item, GtkMenuItem *more_item);

void
on_help_menuitem_activate (GtkMenuItem *help_menuitem, gpointer user_data);
