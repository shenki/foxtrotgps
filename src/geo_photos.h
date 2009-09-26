
typedef enum {
	GEOPHOTO_NEXT,
	GEOPHOTO_PREV,
	GEOPHOTO_FIRST,
	GEOPHOTO_LAST,
	GEOPHOTO_FULLSIZE
} geo_photo_move_e;

void
get_photos();

void
paint_photos();

void
geo_photos_open_dialog_image_data();

void
geo_photos_open_dialog_photo_correlate();

void
geo_photos_geocode_dir_select_dialog (GtkButton       *button,
                               gpointer         user_data);

void
geo_photos_geocode_track_select_dialog (GtkButton       *button,
                               gpointer         user_data);

void
geo_photo_dialog_image_data_next(GtkWidget *widget, gpointer user_data, geo_photo_move_e move);

void
geo_photo_close_dialog_image_data();

void
geo_photo_cancel_dialog_image_data();

void
geo_photo_cancel_dialog_photo_correlate();

void
geo_photo_set_timezone(GtkComboBox *combobox);

void
geo_photo_set_add_to_database(GtkToggleButton *togglebutton);

void
geo_photo_close_dialog_photo_correlate();

void
geo_photo_correction_entry_cb(GtkEditable *editable);
