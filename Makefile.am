## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CPPFLAGS		= -I$(srcdir)/src
AM_CFLAGS		= $(MMUX_CFLAGS)

## --------------------------------------------------------------------

nodist_pkgconfig_DATA	= meta/scripts/ccstrings.pc


#### documentation

AM_MAKEINFOFLAGS	= --no-split
AM_MAKEINFOHTMLFLAGS	= --split=node -c WORDS_IN_PAGE=0 \
	-c PRE_BODY_CLOSE="<p>This document describes version <tt>$(PACKAGE_VERSION)</tt> of <em>$(PACKAGE_NAME)</em>.</p>"

info_TEXINFOS		= doc/ccstrings.texi
doc_ccstrings_TEXINFOS	= \
	doc/macros.texi			\
	doc/ccexceptions-macros.texi	\
	doc/overview-linking.texi	\
	doc/overview-ccnames.texi	\
	doc/overview-ccexceptions.texi	\
	doc/overview-ccmemory.texi	\
	doc/lgpl-3.0.texi		\
	doc/fdl-1.3.texi


#### libraries

ccstrings_CURRENT		= @ccstrings_VERSION_INTERFACE_CURRENT@
ccstrings_REVISION		= @ccstrings_VERSION_INTERFACE_REVISION@
ccstrings_AGE			= @ccstrings_VERSION_INTERFACE_AGE@
ccstrings_LINKER_VERSION	= -version-info $(ccstrings_CURRENT):$(ccstrings_REVISION):$(ccstrings_AGE)

include_HEADERS			= src/ccstrings.h src/ccstrings-buffers.h

lib_LTLIBRARIES			= libccstrings.la
libccstrings_la_CPPFLAGS	= $(AM_CPPFLAGS)
libccstrings_la_CFLAGS		= $(AM_CFLAGS) $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS) $(CCSTRUCTS_CFLAGS)
libccstrings_la_LDFLAGS		= $(ccstrings_LINKER_VERSION) $(AM_LDFLAGS) $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCSTRUCTS_LIBS)
libccstrings_la_SOURCES= \
	src/ccstrings.h			\
	src/ccstrings-buffers.h		\
	src/ccstrings-internals.h	\
	src/ccstrings-version.c		\
	src/ccstrings-conditions.c	\
	src/ccstrings-buffer.c		\
	src/ccstrings-strings.c


#### tests

check_PROGRAMS	= \
	tests/version		\
	tests/buffers

if MMUX_TESTING_ENABLED
TESTS				= $(check_PROGRAMS)
endif

ccstrings_tests_cppflags	= $(AM_CPPFLAGS)
ccstrings_tests_cflags		= $(AM_CFLAGS) $(CCEXCEPTIONS_FLAGS) $(CCMEMORY_FLAGS) $(CCSTRUCTS_FLAGS) $(CCTESTS_FLAGS)
ccstrings_tests_ldadd		= $(AM_LDFLAGS) libccstrings.la $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCSTRUCTS_LIBS) $(CCTESTS_LIBS)

## --------------------------------------------------------------------

tests_version_CPPFLAGS		= $(ccstrings_tests_cppflags)
tests_version_CFLAGS		= $(ccstrings_tests_cflags)
tests_version_LDADD		= $(ccstrings_tests_ldadd)

tests_buffers_CPPFLAGS		= $(ccstrings_tests_cppflags)
tests_buffers_CFLAGS		= $(ccstrings_tests_cflags)
tests_buffers_LDADD		= $(ccstrings_tests_ldadd)

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


#### common rules

include $(top_srcdir)/meta/automake/mmux-makefile-rules

### end of file
