## Process this file with automake to produce Makefile.in

INCLUDES = \
	$(PACKAGE_CFLAGS)

AM_CFLAGS =\
	 -DRELEASE -DHAVE_CONFIG_H\
	 -Wall\
	 -O2\
	 -g

bin_PROGRAMS = foxtrotgps

foxtrotgps_SOURCES = \
	support.h\
	support.c\
	main.c\
	interface.h\
	interface.c\
	callbacks.h\
	callbacks.c\
	map_management.c\
	map_management.h\
	globals.c\
	globals.h\
	converter.c\
	converter.h\
	gps_functions.c\
	gps_functions.h\
	init.c\
	init.h\
	tile_management.c\
	tile_management.h\
	friends.c\
	friends.h\
	gpsdstart.sh\
	geo_photos.c\
	geo_photos.h\
	poi.c\
	poi.h\
	util.c\
	util.h\
	wp.c\
	wp.h\
	tracks.c\
	tracks.h\
	exif.c\
	exif.h

foxtrotgps_LDFLAGS = 

foxtrotgps_LDADD =  \
	$(PACKAGE_LIBS)\
	 -lcurl -lgthread-2.0 -lgconf-2 -lsqlite3 -lexif -lxml2

