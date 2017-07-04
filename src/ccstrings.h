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

#include <ccexceptions.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>


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
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef struct ccstr_buffer_t		ccstr_buffer_t;


/** --------------------------------------------------------------------
 ** Buffer handling.
 ** ----------------------------------------------------------------- */

struct ccstr_buffer_t {
  /* Pointer to the output buffer. */
  char *	bufptr;

  /* Number of bytes allocated for the output buffer. */
  size_t	buflen;

  /* Offset of the next free byte in the output buffer. */
  size_t	bufoff;
};

ccstr_decl void ccstr_buffer_init (cce_location_t * L, ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((nonnull(1,2)));

ccstr_decl void ccstr_buffer_final (ccstr_buffer_t * B)
  __attribute__((nonnull(1)));

ccstr_decl void ccstr_buffer_write (cce_location_t * L, ccstr_buffer_t * B, const char * template, ...)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_buffer_vwrite (cce_location_t * L, ccstr_buffer_t * B, const char * template, va_list ap)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_buffer_enlarge (cce_location_t * L, ccstr_buffer_t * B, size_t required_len)
  __attribute__((nonnull(1,2)));

/* ------------------------------------------------------------------ */

__attribute__((pure,nonnull(1),returns_nonnull,always_inline))
static inline char *
ccstr_buffer_output (ccstr_buffer_t * B)
/* Return a pointer to the first character in the buffer.  */
{
  return B->bufptr;
}

__attribute__((pure,nonnull(1),always_inline))
static inline bool
ccstr_buffer_full_p (ccstr_buffer_t * B)
/* Return true if the buffer is full. */
{
  return (B->bufoff < B->buflen)? false : true;
}

__attribute__((pure,nonnull(1),always_inline))
static inline char *
ccstr_buffer_output_target (ccstr_buffer_t * B)
/* Return a  pointer to  the first  free character  in the  buffer.  The
   return  value of  this  function  is meaningful  only  if  a call  to
   "ccstr_buffer_full_p()" applied to the same buffer returns false. */
{
  return (B->bufptr + B->bufoff);
}

__attribute__((pure,nonnull(1),always_inline))
static inline size_t
ccstr_buffer_output_size (ccstr_buffer_t * B)
/* Return the number of bytes available in the buffer.  The return value
   of   this    function   is   meaningful    only   if   a    call   to
   "ccstr_buffer_full_p()" applied to the same buffer returns false. */
{
  return (B->buflen - B->bufoff);
}


/** --------------------------------------------------------------------
 ** Exceptions handlers.
 ** ----------------------------------------------------------------- */

ccstr_decl void ccstr_cleanup_handler_buffer_init (cce_location_t * L, cce_handler_t * H, ccstr_buffer_t * B)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_error_handler_buffer_init (cce_location_t * L, cce_handler_t * H, ccstr_buffer_t * B)
  __attribute__((nonnull(1,2,3)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRINGS_H */

/* end of file */
