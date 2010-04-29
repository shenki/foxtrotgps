## Process this file with automake to produce Makefile.in

SUBDIRS = po src pixmaps data

foxtrotgpsdocdir = ${prefix}/doc/foxtrotgps
dist_foxtrotgpsdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	TODO



# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

