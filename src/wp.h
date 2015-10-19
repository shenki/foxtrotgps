/*
 *  Copyright  2008  Marcus Bauer 
 *  GPLv2
 *  Email marcus.bauer@gmail.com
 */

#ifndef WP_H
#define WP_H

#include <gtk/gtk.h>

void
paint_wp();

void
paint_myposition();

void
do_paint_wp();

GdkPixbuf *
load_wp_icon();

void
set_current_wp(double lat, double lon);

void
osd_wp();

#endif /* WP_H */
