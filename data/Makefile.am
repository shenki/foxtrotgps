## Process this file with automake to produce Makefile.in

foxtrotgps_datadir = $(datadir)/applications
foxtrotgps_data_in_files = foxtrotgps.desktop.in
foxtrotgps_data_DATA = $(foxtrotgps_data_in_files:.desktop.in=.desktop)

@INTLTOOL_DESKTOP_RULE@


gconf_schemadir = $(GCONF_SCHEMA_FILE_DIR)
gconf_schema_in_files = apps_foxtrotgps.schemas.in
gconf_schema_DATA = $(gconf_schema_in_files:.schemas.in=.schemas)

@INTLTOOL_SCHEMAS_RULE@

if GCONF_SCHEMAS_INSTALL
install-data-local:
	GCONF_CONFIG_SOURCE=$(GCONF_SCHEMA_CONFIG_SOURCE) \
	gconftool-2 --makefile-install-rule $(gconf_schema_DATA)
endif


dist_pkgdata_DATA = foxtrotgps.glade

EXTRA_DIST = $(foxtrotgps_data_in_files) $(gconf_schema_in_files)
DISTCLEANFILES = \
	$(foxtrotgps_data_in_files:.desktop.in=.desktop) \
	$(gconf_schema_in_files:.schemas.in=.schemas)
