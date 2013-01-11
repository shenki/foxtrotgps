man_MANS = foxtrotgps.1

nobase_dist_html_DATA = \
	foxtrotgps.html \
	$(images)

info_TEXINFOS = foxtrotgps.texi

foxtrotgps_TEXINFOS = $(images) $(images_eps)

images = \
	foxtrotgps.png \
	screenshots/main-window.png

# Some of the TeX-based outputs need images in EPS format:
images_eps = $(patsubst %.png,%.eps,$(images))
.png.eps:
	convert $< $@

foxtrotgps.png:
	$(LN_S) $(top_srcdir)/pixmaps/$@ $@

$(images): | screenshots

screenshots:
# If this directory doesn't exist, try a checkout of the upstream
# screenshot-archive:

	bzr co --lightweight lp:foxtrotgps/screenshots


AM_MAKEINFOHTMLFLAGS = --no-split --no-headers

EXTRA_DIST = foxtrotgps.h2m.in foxtrotgps.1.in
DISTCLEANFILES = foxtrotgps.1
MAINTAINERCLEANFILES = foxtrotgps.1.in $(images_eps)

foxtrotgps.1: foxtrotgps.1.in Makefile
	sed -e 's|@htmldir[@]|$(htmldir)|g' $< > $@.tmp
	mv $@.tmp $@

foxtrotgps.1.in: $(top_srcdir)/src/main.c $(top_srcdir)/configure.in foxtrotgps.h2m.in
	$(MAKE) -C $(top_builddir)/src foxtrotgps$(EXEEXT)

	help2man sh --output=foxtrotgps.1.in \
		--help-option="-c \"$(top_builddir)/src/foxtrotgps$(EXEEXT) \
				--help | sed -e '1N;2s/\\n//'\"" \
		--version-option="-c \"$(top_builddir)/src/foxtrotgps$(EXEEXT)\
				--version\"" \
		--info-page=foxtrotgps \
		--include=$(srcdir)/foxtrotgps.h2m.in

.texi.txt:
	$(MAKEINFO) --plaintext --output=$@ $<
