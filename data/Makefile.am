## Process this file with automake to produce Makefile.in

foxtrotgps_datadir = $(datadir)/applications
foxtrotgps_data_in_files = foxtrotgps.desktop.in
foxtrotgps_data_DATA = $(foxtrotgps_data_in_files:.desktop.in=.desktop)

@INTLTOOL_DESKTOP_RULE@


dist_pkgdata_DATA = foxtrotgps.glade

EXTRA_DIST = $(foxtrotgps_data_in_files)
DISTCLEANFILES = $(foxtrotgps_data_in_files:.desktop.in=.desktop)
