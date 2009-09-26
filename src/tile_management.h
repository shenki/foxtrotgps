
typedef struct {
	double lat1;
	double lon1;
	double lat2;
	double lon2;
} bbox_t;

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} bbox_pixel_t;


typedef struct {
	int x;
	int y;
	int zoom;
	repo_t *repo;
} tile_t;

gboolean
download_tile(	repo_t *repo,//TODO das sollte eine repo struct sein
		int zoom,
		int x,
		int y);
void *
dl_thread(void *ptr);

int
update_thread_number (int change);

void
cb_download_maps(GtkWidget *dialog);

bbox_t
get_bbox();

bbox_t
get_bbox_deg();

bbox_pixel_t
get_bbox_pixel(bbox_t bbox, int zoom);

void
download_maps(bbox_t bbox, int zoom_start, int zoom_end);

void
queue_tile_dl_for_bbox(bbox_pixel_t bbox_pixel, int zoom);

gboolean
timer_tile_download(gpointer data);
