float
deg2rad(float deg);

float
rad2deg(float rad);

int
lat2pixel(	float zoom,
		float lat);

int
lon2pixel(	float zoom,
		float lon);
		
float
pixel2lon(	float zoom,
		int pixel_x);
		
float
pixel2lat(	float zoom,
		int pixel_y);
char *
latdeg2latmin(	float lat);

char *
londeg2lonmin(	float lon);

char *
latdeg2latsec(	float lat);

char *
londeg2lonsec(	float lon);

float
get_bearing(double lat1, double lon1, double lat2, double lon2);

float
get_distance(double lat1, double lon1, double lat2, double lon2);

int
get_zoom_covering(int width, int height, double lat_max, double lon_min, double lat_min, double lon_max);
