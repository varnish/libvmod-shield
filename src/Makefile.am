AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_shield.la

libvmod_shield_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_shield_la_SOURCES = \
	vmod_shield.c

nodist_libvmod_shield_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

vmod_shield.lo: vcc_if.c vcc_if.h

vcc_if.c: vcc_if.h

vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_shield.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_shield.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc: libvmod_shield.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_shield.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_shield.rst \
	$(builddir)/vmod_shield.man.rst
