/*
  Part of: CCStrings
  Contents: public header file
  Date: Apr 17, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser General  Public
  License     along    with     this    program.      If    not,     see
  <http://www.gnu.org/licenses/>.
*/

#ifndef CCSTRINGS_H
#define CCSTRINGS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCSTR_UNUSED  indicates  that  a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCSTR_UNUSED;
   int foo (char unused_argument CCSTR_UNUSED);
   int unused_variable CCSTR_UNUSED;
*/
#ifdef __GNUC__
#  define CCSTR_UNUSED		__attribute__((unused))
#else
#  define CCSTR_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

#ifndef __GNUC__
#  define __builtin_expect(...)	/* empty */
#endif

#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define ccstr_decl		__attribute__((dllexport)) extern
#    else
#      define ccstr_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define ccstr_decl		__attribute__((dllimport)) extern
#    else
#      define ccstr_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define ccstr_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccstr_decl		__attribute__((visibility ("default"))) extern
#    define ccstr_private_decl	__attribute__((visibility ("hidden")))  extern
#  else
#    define ccstr_decl		extern
#    define ccstr_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccstr_decl const char *	ccstr_version_string		(void);
ccstr_decl int		ccstr_version_interface_current	(void);
ccstr_decl int		ccstr_version_interface_revision(void);
ccstr_decl int		ccstr_version_interface_age	(void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRINGS_H */

/* end of file */
