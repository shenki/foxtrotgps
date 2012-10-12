void
reset_loaded_track();

void
paint_track();

void
track_log();

void
track_log_open();

void
track_log_close();

void
tracks_open_tracks_dialog();

void
paint_loaded_track();

gboolean
tracks_on_file_button_release_event      (	GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
fetch_track(GtkWidget *widget, char *service, char *start, char *end);

void
fetch_yournavigation_track(GtkWidget *widget, char *start, char *end);

void
fetch_openrouteservice_track(GtkWidget *widget, char *start, char *end);

void
show_bbox (bbox_t bbox);
