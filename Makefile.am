## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= $(MMUX_CFLAGS) -I$(srcdir)/src -I$(builddir)/src
MMUX_DEPENDENCY_INCLUDES = $(CCEXCEPTIONS_HEADER) $(CCMEMORY_HEADER) $(CCSTRUCTS_HEADER)

## --------------------------------------------------------------------

EXTRA_DIST		+= meta/scripts/ccstrings.pc.in
pkgconfigdir		= $(libdir)/pkgconfig
nodist_pkgconfig_DATA	= meta/scripts/ccstrings.pc

## --------------------------------------------------------------------

AM_MAKEINFOFLAGS	= --no-split
AM_MAKEINFOHTMLFLAGS	= --split=node -c WORDS_IN_PAGE=0 \
	-c PRE_BODY_CLOSE="<p>This document describes version <tt>$(PACKAGE_VERSION)</tt> of <em>$(PACKAGE_NAME)</em>.</p>"

info_TEXINFOS		= doc/ccstrings.texi
doc_ccstrings_TEXINFOS	= \
	doc/macros.texi		\
	doc/lgpl-3.0.texi	\
	doc/fdl-1.3.texi


#### libraries

ccstrings_CURRENT	= @ccstrings_VERSION_INTERFACE_CURRENT@
ccstrings_REVISION	= @ccstrings_VERSION_INTERFACE_REVISION@
ccstrings_AGE		= @ccstrings_VERSION_INTERFACE_AGE@

include_HEADERS		= src/ccstrings.h

lib_LTLIBRARIES			= libccstrings.la
libccstrings_la_CPPFLAGS	= $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS) $(CCSTRUCTS_CFLAGS)
libccstrings_la_LDFLAGS		= \
	-version-info $(ccstrings_CURRENT):$(ccstrings_REVISION):$(ccstrings_AGE) \
	$(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCSTRUCTS_LIBS)
libccstrings_la_SOURCES= \
	src/ccstrings.h			\
	src/ccstrings-internals.h	\
	src/ccstrings-version.c		\
	src/ccstrings-conditions.c	\
	src/ccstrings-buffer.c		\
	src/ccstrings-strings.c


#### tests

check_PROGRAMS	= \
	tests/version		\
	tests/buffers

TESTS				= $(check_PROGRAMS)

ccstrings_tests_cppflags	= -I$(srcdir)/src $(CCEXCEPTIONS_FLAGS)
ccstrings_tests_ldadd		= libccstrings.la $(CCEXCEPTIONS_LIBS)

tests_version_CPPFLAGS		= $(ccstrings_tests_cppflags)
tests_version_LDADD		= $(ccstrings_tests_ldadd)

tests_buffers_CPPFLAGS		= $(ccstrings_tests_cppflags)
tests_buffers_LDADD		= $(ccstrings_tests_ldadd)

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


#### common rules

include $(top_srcdir)/meta/automake/mmux-makefile-rules

### end of file
