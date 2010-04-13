

void
load_tiles();

void
load_tile(	gchar *dir,
		int zoom,
		int x,
		int y,
		int offset_x,
		int offset_y);
void
fill_tiles_pixel(	int pixel_x,
			int pixel_y,
			int zoom,
			gboolean force_redraw);

void
fill_tiles_latlon(	float lat,
			float lon,
			int zoom);
			
			
void
set_mapcenter(	float lat,
		float lon,
		int zoom);
