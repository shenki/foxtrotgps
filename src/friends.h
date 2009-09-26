/***************************************************************************
 *            friends.h
 *
 *  Tue Feb 12 16:58:38 2008
 *  Copyright  2008  User
 *  Email
 ****************************************************************************/

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
