## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL configure.sh
dist_doc_DATA		= README COPYING
AM_CFLAGS		= -I$(srcdir)/src -Wall $(AX_CFLAGS)

## --------------------------------------------------------------------

EXTRA_DIST		+= meta/scripts/ccstrings.pc.in
pkgconfigdir		= $(libdir)/pkgconfig
nodist_pkgconfig_DATA	= meta/scripts/ccstrings.pc

## --------------------------------------------------------------------

AM_MAKEINFOFLAGS	= --no-split

info_TEXINFOS		= doc/ccstrings.texi
doc_ccstrings_TEXINFOS	= \
	doc/macros.texi		\
	doc/lgpl-3.0.texi	\
	doc/fdl-1.3.texi

#page
#### libraries

ccstrings_CURRENT	= @ccstrings_VERSION_INTERFACE_CURRENT@
ccstrings_REVISION	= @ccstrings_VERSION_INTERFACE_REVISION@
ccstrings_AGE		= @ccstrings_VERSION_INTERFACE_AGE@

include_HEADERS		= src/ccstrings.h

lib_LTLIBRARIES		= libccstrings.la
libccstrings_la_LDFLAGS= -version-info $(ccstrings_CURRENT):$(ccstrings_REVISION):$(ccstrings_AGE)
libccstrings_la_SOURCES= \
	src/ccstrings.h			\
	src/ccstrings-internals.h	\
	src/ccstrings-version.c

#page
#### tests

check_PROGRAMS	= \
	tests/version

TESTS				= $(check_PROGRAMS)

ccstrings_tests_cppflags	= -I$(srcdir)/src
ccstrings_tests_ldadd		= libccstrings.la

tests_version_CPPFLAGS		= $(ccstrings_tests_cppflags)
tests_version_LDADD		= $(ccstrings_tests_ldadd)

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

### end of file
