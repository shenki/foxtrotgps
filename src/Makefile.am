## Process this file with automake to produce Makefile.in

AM_CFLAGS =\
	 -DHAVE_CONFIG_H\
	 -Wall\
	 -O2\
	 -g

AM_CPPFLAGS = \
	-DPACKAGE_DATA_DIR="\"$(datadir)\"" \
	-DPACKAGE_PIXMAPS_DIR="\"$(datadir)/pixmaps\"" \
	-DPACKAGE_LOCALE_DIR="\"$(localedir)\"" \
	\
	$(GTK_CFLAGS) \
	$(GCONF_CFLAGS) \
	$(LIBCURL_CFLAGS) \
	$(SQLITE_CFLAGS) \
	$(LIBEXIF_CFLAGS) \
	$(LIBXML_CFLAGS)

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
	$(GTK_LIBS) \
	$(GCONF_LIBS) \
	$(LIBCURL_LIBS) \
	$(SQLITE_LIBS) \
	$(LIBEXIF_LIBS) \
	$(LIBXML_LIBS)
