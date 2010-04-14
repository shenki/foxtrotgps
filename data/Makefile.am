## Process this file with automake to produce Makefile.in
#foxtrotgps_datadir = $(prefix)/@NO_PREFIX_PACKAGE_DATA_DIR@/@PACKAGE@/applications
foxtrotgps_datadir = $(prefix)/@NO_PREFIX_PACKAGE_DATA_DIR@/applications
foxtrotgps_data_in_files = foxtrotgps.desktop.in
foxtrotgps_data_DATA = $(foxtrotgps_data_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = $(foxtrotgps_data_DATA)

