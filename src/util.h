#include <stdlib.h>
#include <gtk/gtk.h>

#include <curl/curl.h>
#include <curl/easy.h>
int
sql_execute(const char *db_name, const char *sql, int (*cb_func)(void*,int,char**,char**));

typedef struct {
	char *name;
	char *value;
} postdata_item_t;


typedef struct {
	long int status_code;
	size_t size;
	char *data ;
} postreply_t;



typedef struct {
	char *memory;
	size_t size;
} mem_struct_t;



postreply_t*
mycurl__do_http_post (char *url, GSList *post_data_list, char *useragent);

postreply_t*
mycurl__do_http_post_XML (char *url, char *xmlString, char *useragent);

postreply_t*
mycurl__do_http_get (char *url, char *useragent);
