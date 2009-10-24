#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


#include <gtk/gtk.h>
#include <gconf/gconf-client.h>

#define GCONF "/apps/tangogps"
#define TILESIZE 256
#define PNAME "tangogps"

typedef struct {
	float lat;
	float lon;
//	int pixel_x;
//	int pixel_y;
} trackpoint_t;

typedef struct {
	double lat;
	double lon;
//	int pixel_x;
//	int pixel_y;
} waypoint_t;

typedef struct {
	char *name;
	char *uri;
	char *dir;
	int inverted_zoom;
} repo_t;

typedef struct {
	int type;
	char *nick;
	float lat;
	float lon;
	int head;
	int speed;
	char *lastseen;
	char *msg;
	int screen_x;
	int screen_y;
} friend_t;

typedef struct {
	char *filename;
	char *name;
	double lat;
	double lon;
	char *desc;
	int screen_x;
	int screen_y;
} photo_t;

typedef struct {
	char *idmd5;
	double lat_deg;
	double lon_deg;
	int visibility;
	int category;
	int subcategory;
	char *keywords;
	char *desc;
	int price_range;
	int extended_open;
	int screen_x;
	int screen_y;
	GtkWidget *widget;
} poi_t;

typedef struct {
    double time;        /* Time of update, seconds since Unix epoch */
    int    mode;        /* Mode of fix */
    double latitude;    /* Latitude in degrees (valid if mode >= 2) */
    double longitude;   /* Longitude in degrees (valid if mode >= 2) */
    double altitude;    /* Altitude in meters (valid if mode == 3) */
    double track;       /* Course made good (relative to true north) */
    double speed;       /* Speed over ground, meters/sec */
    double bearing;	/* in radian */
} gps_fix_t;

typedef struct {
	gps_fix_t fix;
	int satellites_used;
	int satellites_inview;
	double hdop;
	gboolean valid;
	gboolean seen_vaild; /* ever had a vaild fix? */
} gps_data_t;

extern GdkPixmap 	*pixmap;
extern GtkWidget	*window1, *window2;
extern GtkWidget	*map_drawable;
extern GtkWidget	*dialog1;
extern GtkWidget	*dialog8;
extern GtkWidget	*window3;
extern GtkWidget	*menu1;
//extern char repo_dir[]; //FIXME: delete me
extern char *global_track_dir;

extern int global_x;
extern int global_y;
extern int global_zoom;
extern int global_zoom_max;
extern int global_detail_zoom;

extern int mouse_dx; // for mouse move pixmap
extern int mouse_dy;

extern int global_speed_unit;
extern int global_alt_unit;
extern int global_latlon_unit;

extern int global_drawingarea_width;
extern int global_drawingarea_height;


extern gps_data_t *gpsdata;

//extern trackpoint_t global_track_arr[10];

extern GSList		*trackpoint_list;
extern GSList		*friends_list;
extern GSList		*photo_list;
extern GSList		*poi_list;
extern float		trip_distance;
extern double		trip_maxspeed;
extern double		trip_time;
extern double		trip_starttime;
extern gboolean		trip_counter_on;
extern trackpoint_t	global_myposition;
extern gboolean		trip_logger_on;

extern gchar		*global_curr_reponame;
extern int		global_repo_cnt;
extern GSList	 	*global_repo_list, *global_curr_repo;
extern GConfClient	*global_gconfclient;

extern gboolean		global_auto_download;
extern gboolean		global_mapmode;
extern gboolean		global_autocenter;
extern gboolean		global_reconnect_gpsd;
extern int		global_tiles_in_dl_queue;

extern gboolean		global_show_pois;
extern gboolean		global_show_friends;
extern gboolean		global_show_photos;
extern int		global_poi_cat;

extern gboolean		global_wp_on;
extern waypoint_t	global_wp;

extern gboolean		global_ffupdate_auto;
extern int		global_ffupdate_interval;
extern double		global_ffupdate_interval_minutes;
extern gboolean		global_fftimer_running;
extern gboolean		global_ffcm_public;
extern gboolean		global_ffcm_registered;
extern gboolean		global_ffcm_friends;
extern gboolean		global_ffcu_public;
extern gboolean		global_ffcu_registered;
extern gboolean		global_ffcu_friends;
extern int		global_ff_mode;

extern gchar		*global_server;
extern gchar		*global_port;

extern gchar		*global_home_dir;
extern gchar		*tangogps_dir;

extern int		mouse_x;
extern int		mouse_y;


enum {
	PRIVATE_MODE = 1,
	FRIEND_MODE = 2,
	FUN_MODE = 3
};

enum {
	METRICAL = 0,
	IMPERIAL = 1,
	NAUTICAL = 2
};
