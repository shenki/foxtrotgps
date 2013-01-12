## Process this file with automake to produce Makefile.in

SUBDIRS = po src pixmaps data doc contrib

dist_doc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	HACKING\
	NEWS\
	TODO

bzr_dirstate = $(wildcard .bzr/checkout/dirstate)

ChangeLog: $(bzr_dirstate)
	(bzr log --verbose --include-merges || \
	bzr log --verbose) | fmt -s > $@.tmp && mv $@.tmp $@

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
