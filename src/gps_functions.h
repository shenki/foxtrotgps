#ifndef GPS_FUNCTIONS_H
#define GPS_FUNCTIONS_H

#include <gtk/gtk.h>

gboolean
cb_gps_timer();

void
get_gps();

gboolean
reset_gpsd_io();

void
set_label();

void
set_label_nogps();

void
set_label_newmsg();

void
osd_speed(gboolean force_redraw);

void
map_scale_indicator();

#endif /* GPS_FUNCTIONS_H */
