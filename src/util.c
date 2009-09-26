#include "util.h"


#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h> 

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
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		result = -1;
	}
	else
	{
		rc = sqlite3_exec(db, sql, cb_func, 0, &errmsg);
	}
	
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", errmsg);
		sqlite3_free(errmsg);
		result = 1;
	}
  
	sqlite3_close(db);
	return result;
}
