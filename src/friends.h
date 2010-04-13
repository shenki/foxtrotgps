/***************************************************************************
 *            friends.h
 *
 *  Tue Feb 12 16:58:38 2008
 *  Copyright  2008  User
 *  Email
 ****************************************************************************/
#include <gtk/gtk.h>
typedef struct {
	int type;
	char *nick;
	float lat;
	float lon;
	int head;
	int speed;
	char *lastseen;
	char *away_msg;
	int screen_x;
	int screen_y;
} friend_t;


typedef struct {
	int long id;
	char *txt;
	char *to;
	char *from;
	char *time;
	gboolean incoming; 
	float lat;
	float lon;
	int flag;
} msg_t;


int
update_position();

void *
update_position_thread(void *ptr);

void
paint_friends();

int
register_nick();
	
void *
register_nick_thread(void *ptr);

GtkWidget*
create_friend_box(friend_t *f);

gboolean
send_message(gpointer user_data);
