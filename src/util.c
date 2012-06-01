#include "util.h"


#include <glib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"

int
sql_execute(char *db_name, char *sql, int (*cb_func)(void*,int,char**,char**))
{
	sqlite3 *db;
	char *errmsg = 0;
	int rc;
	int result = 0;
	
	printf("*** %s(): \n",__PRETTY_FUNCTION__);


	rc = sqlite3_open(db_name, &db);
	if( rc ){
		fprintf (stderr, _("Can't open database: %s\n"),
		         sqlite3_errmsg (db));
		sqlite3_close(db);
		result = -1;
	}
	else
	{
		rc = sqlite3_exec(db, sql, cb_func, 0, &errmsg);
	}
	
	if( rc!=SQLITE_OK ){
		fprintf (stderr, _("SQL error: %s\n"), errmsg);
		sqlite3_free(errmsg);
		result = 1;
	}
  
	sqlite3_close(db);
	return result;
}

static size_t
mycurl_write_to_mem_cb(void *ptr, size_t rsize, size_t nmemb, void *data)
{
	size_t size; 
	mem_struct_t *mem; 
	
	size = rsize * nmemb;
	mem = (mem_struct_t *)data;
	
	mem->memory = (char *) g_realloc(mem->memory, mem->size + size + 1);
	
	if (mem->memory)
	{
		memcpy(&(mem->memory[mem->size]), ptr, size);
		mem->size += size;
		mem->memory[mem->size] = 0;
	}
	
	return size;
}

postreply_t*
mycurl__do_http_post_XML (char *url, char *xmlString, char *useragent)
{
	GSList *list;
	postreply_t *postreply;
	
	CURL *curl_handle;
	
	struct curl_httppost *lastptr  = NULL;
		
	mem_struct_t chunk;
	long int status_code;
	
	chunk.memory = NULL;
	chunk.size   = 0;
	
	curl_global_init(CURL_GLOBAL_ALL);
	
	curl_handle = curl_easy_init();
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, xmlString);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, mycurl_write_to_mem_cb);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	curl_easy_perform(curl_handle);
	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &status_code);
	
	curl_easy_cleanup(curl_handle);
	
	postreply = g_new0(postreply_t, 1);
	postreply->status_code = status_code;
	if(chunk.memory)
		postreply->size = strlen(chunk.memory);
	else
		postreply->size = 0;
	postreply->data = g_strdup(chunk.memory);
	
	if(chunk.memory)
		g_free(chunk.memory);
	
	curl_global_cleanup();
	
	return postreply;
}

postreply_t*
mycurl__do_http_post (char *url, GSList *post_data_list, char *useragent)
{
	GSList *list;
	postreply_t *postreply;

		
	CURL *curl_handle;
	
	struct curl_httppost *formdata = NULL;
	struct curl_httppost *lastptr  = NULL;
		
	mem_struct_t chunk;
	long int status_code;


	
	chunk.memory = NULL;
	chunk.size   = 0;	
	
	curl_global_init(CURL_GLOBAL_ALL);


	
	for(list = post_data_list; list != NULL; list = list->next)
	{
		postdata_item_t *postdata_item;
		
		postdata_item = list->data;
		
		curl_formadd(&formdata,
		       &lastptr,
		       CURLFORM_COPYNAME,	postdata_item->name,
		       CURLFORM_COPYCONTENTS,	postdata_item->value,
		       CURLFORM_END);
	}
	
	
	
	curl_handle = curl_easy_init();
	
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formdata);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, mycurl_write_to_mem_cb);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, useragent);

	curl_easy_perform(curl_handle);
	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &status_code);
	
	curl_easy_cleanup(curl_handle);
	
	

	
	
	postreply = g_new0(postreply_t, 1);
	postreply->status_code = status_code;
	if(chunk.memory)
		postreply->size = strlen(chunk.memory);
	else
		postreply->size = 0;
	postreply->data = g_strdup(chunk.memory);
	
	
	if(chunk.memory)
		g_free(chunk.memory);
	
	curl_global_cleanup();
	
	
	return postreply;
}


postreply_t*
mycurl__do_http_get (char *url, char *useragent)
{
	postreply_t *postreply;

		
	CURL *curl_handle;

		
	mem_struct_t chunk;
	long int status_code;


	
	chunk.memory = NULL;
	chunk.size   = 0;	
	
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();
 
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, mycurl_write_to_mem_cb);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	
	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 120);
	curl_easy_setopt(curl_handle, CURLOPT_LOW_SPEED_LIMIT, 1000); 
	curl_easy_setopt(curl_handle, CURLOPT_LOW_SPEED_TIME, 40);    
 
	if(!useragent)
		curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 


	curl_easy_perform(curl_handle);
	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &status_code);
	
	curl_easy_cleanup(curl_handle);
	
	

	
	
	postreply = g_new0(postreply_t, 1);
	postreply->status_code = status_code;
	if(chunk.memory)
		postreply->size = strlen(chunk.memory);
	else
		postreply->size = 0;
	postreply->data = g_strdup(chunk.memory);
	
	
	if(chunk.memory)
		g_free(chunk.memory);
	
	curl_global_cleanup();
	
	
	return postreply;
}
