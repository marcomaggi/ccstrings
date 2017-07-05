## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL configure.sh		\
			  meta/slackstuff/config.in	\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= $(AX_CFLAGS) -Wall -I$(srcdir)/src -I$(builddir)/src

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
libccstrings_la_CPPFLAGS= $(CCEXCEPTIONS_CFLAGS)
libccstrings_la_LDFLAGS	= -version-info $(ccstrings_CURRENT):$(ccstrings_REVISION):$(ccstrings_AGE) \
			  $(CCEXCEPTIONS_LIBS)
libccstrings_la_SOURCES= \
	src/ccstrings.h			\
	src/ccstrings-internals.h	\
	src/ccstrings-version.c		\
	src/ccstrings-conditions.c	\
	src/ccstrings-buffer.c

#page
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

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

#page
#### Coverity support
#
# First run  "make clean",  then run "make  coverity" to  generate the
# report.  Remember  to put  in the  PATH the  directory in  which the
# Coverity tools are installed.
#
# The tool  will use  a temporary directory  "$(builddir)/cov-int"; we
# must *not* change this pathname.
#
# To generate and submit a report we must do:
#
#    $ make clean
#    $ make coverity-scan
#    $ make coverity-archive
#    $ make coverity-upload
#
# after "make  coverity-scan" we should  check that the last  lines of
# the file "cov-int/build-log.txt" report a successful build.
#
# Notice that if your Linux kernel is  at version 4.8 or above we have
# to first issue the command:
#
#    $ sudo /sbin/sysctl vsyscall=emulate
#
# to make the Coverity tools work.
#

CCSTRINGS_COVERITY_TOKEN_FILE = /home/unsafe-users/marco-devel/.coverity-ccstrings-token

.PHONY: coverity-scan coverity-archive coverity-upload

coverity-scan:
	cov-build --dir cov-int make -j 4

coverity-archive:
	tar caf ccstrings.xz cov-int

coverity-upload:
	curl --form token=$$(<$(CCSTRINGS_COVERITY_TOKEN_FILE)) \
	     --form email='marco.maggi-ipsu@poste.it' \
	     --form file='@ccstrings.xz' \
	     --form version="$(VERSION)" \
	     --form description="A build description" \
	     'https://scan.coverity.com/builds?project=marcomaggi%2Fccstrings'

#page
#### Static analysis with Clang's Static Analyzer
#
# See the documentation for the command line tool at:
#
#    <http://clang-analyzer.llvm.org/scan-build.html>
#
# To run the tool we must do:
#
#    $ make clean
#    $ make clang-static-analysis
#
# The  program  "scan-build"  works  by  overriding  the  CC  and  CXX
# environment variables.  Automake defines CXX as:
#
#    CXX = g++ -std=c++11
#
# so we override CXXFLAGS to include the language specification.
#

.PHONY: clang-static-analysis

clang-static-analysis:
	scan-build make CXXFLAGS='-std=c++11'

### end of file
