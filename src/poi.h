#ifndef POI_H
#define POI_H

#include <gtk/gtk.h>

void
paint_pois();

void
set_poi(GtkWidget *dialog);

void
update_poi(GtkWidget *dialog);

void
delete_poi(poi_t *p);

void
show_window6();

void
on_combobox_cat_changed(GtkComboBox     *combobox);

void
get_pois();

void
show_poi_detail();

#endif /* POI_H */
