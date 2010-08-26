#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


#include <gtk/gtk.h>
#include <glade/glade.h>
#include <gconf/gconf-client.h>

#define MSG_SEND_URL "http://tangogps.org/friends/msg_send.php"

#define GCONF "/apps/" PACKAGE
#define TILESIZE 256
#define MAP_PAGE 0
#define FRIENDS_PAGE 1

#define TRACKPOINT_LIST_MAX_LENGTH 10000	/* max points to keep in mem */
#define TRIP_DELTA_MIN 0.005			/* min distance between points to log: 5m */
#define SEGMENT_DISTANCE 100			/* start a new segment when distance exceeds: 100m */

typedef struct {
	int   time;
	float lat;
	float lon;
	float lat_deg;
	float lon_deg;
	float alt;
	float speed;
	float head;
	float hdop;
	int   heart;
} trackpoint_t;

typedef struct {
	double lat;
	double lon;
} waypoint_t;

typedef struct {
	char *name;
	char *uri;
	char *dir;
	int inverted_zoom;
} repo_t;


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
	double time;		/* Time of update, seconds since Unix epoch */
	int    mode;		/* Mode of fix */
	double latitude;	/* Latitude in degrees (valid if mode >= 2) */
	double longitude;	/* Longitude in degrees (valid if mode >= 2) */
	double altitude;	/* Altitude in meters (valid if mode == 3) */
	double heading;
	double speed;		/* Speed over ground, meters/sec */
	double bearing;		/* in radian, calculated by tangogps */
} tangogps_gps_fix_t;

typedef struct {
	tangogps_gps_fix_t fix;
	int satellites_used;
	int satellites_inview;
	double hdop;
	gboolean valid;
	gboolean seen_vaild; /* ever had a vaild fix? */
} tangogps_gps_data_t;

extern GdkPixmap 	*pixmap;

extern const char	*gladefile;
extern GladeXML		*gladexml;

extern GtkWidget	*window1, *window2;
extern GtkWidget	*map_drawable;
extern GtkWidget	*dialog1;
extern GtkWidget	*dialog8;
extern GtkWidget	*window3;
extern GtkWidget	*menu1;
extern GList		*global_infopane_widgets;
extern GList		*global_infopane_current;

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


extern tangogps_gps_data_t *gpsdata;


extern GQueue		*trackpoint_list;
extern GSList		*friends_list;
extern GSList		*photo_list;
extern GSList		*poi_list;
extern GSList		*msg_list;
extern float		trip_distance;
extern double		trip_maxspeed;
extern double		trip_time;
extern double		trip_starttime;
extern gboolean		trip_counter_on;
extern trackpoint_t	global_myposition;
extern gboolean		trip_logger_on;
extern gboolean		trip_livelog_on;

extern gchar		*global_curr_reponame;
extern int		global_repo_cnt;
extern int		global_repo_nr;
extern GSList	 	*global_repo_list, *global_curr_repo;
extern GConfClient	*global_gconfclient;

extern gboolean		global_infopane_visible;
extern gboolean		global_landscape;
extern gboolean		global_auto_download;
extern gboolean		global_mapmode;
extern gboolean		global_autocenter;
extern gboolean		global_reconnect_gpsd;
extern int		global_tiles_in_dl_queue;

extern gboolean		global_show_pois;
extern gboolean		global_show_friends;
extern gboolean		global_show_photos;
extern gboolean		global_new_msg;
extern int		global_poi_cat;

extern gboolean		global_wp_on;
extern waypoint_t	global_wp;

extern char		*global_friend_nick;
extern char		*global_friend_pass;

extern int		global_ffupdate_interval;
extern double		global_ffupdate_interval_minutes;
extern gboolean		global_fftimer_running;
extern int		global_ff_mode;

extern gchar		*global_server;
extern gchar		*global_port;

extern gchar		*global_home_dir;
extern gchar		*foxtrotgps_dir;

extern int		mouse_x;
extern int		mouse_y;

extern int		drag_started;


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
