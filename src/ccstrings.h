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

  You  should have received  a copy  of the  GNU General  Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCSTRINGS_H
#define CCSTRINGS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCS_UNUSED  indicates  that  a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCS_UNUSED;
   int foo (char unused_argument CCS_UNUSED);
   int unused_variable CCS_UNUSED;
*/
#ifdef __GNUC__
#  define CCS_UNUSED		__attribute__((unused))
#else
#  define CCS_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define ccs_decl		__attribute__((dllexport))
#    else
#      define ccs_decl		__declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define ccs_decl		__attribute__((dllimport))
#    else
#      define ccs_decl		__declspec(dllimport)
#    endif
#  endif
#  define ccs_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccs_decl		__attribute__((visibility ("default")))
#    define ccs_private_decl	__attribute__((visibility ("hidden")))
#  else
#    define ccs_decl		extern
#    define ccs_private_decl	extern
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

ccs_decl const char *	ccs_version_string		(void);
ccs_decl int		ccs_version_interface_current	(void);
ccs_decl int		ccs_version_interface_revision	(void);
ccs_decl int		ccs_version_interface_age	(void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRINGS_H */

/* end of file */
