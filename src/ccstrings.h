/*
  Part of: CCStrings
  Contents: public header file
  Date: Apr 17, 2017

  Abstract

	This header file must be included  in all the source files using
	CCStrings.

  Copyright (C) 2017-2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
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
#  define CCSTR_UNUSED		__attribute__((__unused__))
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
#      define ccstr_decl	__attribute__((__dllexport__)) extern
#    else
#      define ccstr_decl	__declspec(dllexpor) extern
#    endif
#  else
#    ifdef __GNUC__
#      define ccstr_decl	__attribute__((__dllimport__)) extern
#    else
#      define ccstr_decl	__declspec(dllimport) extern
#    endif
#  endif
#  define ccstr_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccstr_decl		__attribute__((__visibility__("default"))) extern
#    define ccstr_private_decl	__attribute__((__visibility__("hidden")))  extern
#  else
#    define ccstr_decl		extern
#    define ccstr_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccstructs.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Initialisation.
 ** ----------------------------------------------------------------- */

ccstr_decl void ccstr_init (void)
  __attribute__((__constructor__));


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccstr_decl char const *	ccstr_version_string		(void);
ccstr_decl int		ccstr_version_interface_current	(void);
ccstr_decl int		ccstr_version_interface_revision(void);
ccstr_decl int		ccstr_version_interface_age	(void);


/** --------------------------------------------------------------------
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef struct ccstr_buffer_t			ccstr_buffer_t;

typedef struct ccstr_vtable_t			ccstr_vtable_t;
typedef struct ccstr_t				ccstr_t;

typedef struct ccstr_descriptor_base_t		ccstr_descriptor_base_t;
typedef struct ccstr_condition_base_t		ccstr_condition_base_t;

typedef struct ccstr_descriptor_buffer_size_overflow_t		ccstr_descriptor_buffer_size_overflow_t;
typedef struct ccstr_condition_buffer_size_overflow_t		ccstr_condition_buffer_size_overflow_t;

typedef struct ccstr_descriptor_buffer_output_incomplete_t	ccstr_descriptor_buffer_output_incomplete_t;
typedef struct ccstr_condition_buffer_output_incomplete_t	ccstr_condition_buffer_output_incomplete_t;


/** --------------------------------------------------------------------
 ** Buffer handling.
 ** ----------------------------------------------------------------- */

struct ccstr_buffer_t {
  /* Pointer to the output buffer. */
  uint8_t *	bufptr;

  /* Number of bytes allocated for the output buffer. */
  size_t	buflen;

  /* Offset of  the next free byte  in the output buffer.   This is also
     the number of bytes used in the buffer. */
  size_t	bufoff;
};

ccstr_decl void ccstr_buffer_init (cce_location_t * L, ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((nonnull(1,2)));

ccstr_decl void ccstr_buffer_final (ccstr_buffer_t * B)
  __attribute__((nonnull(1)));

ccstr_decl void ccstr_clean_handler_buffer_init (cce_location_t * L, cce_clean_handler_t * H, ccstr_buffer_t * B)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_error_handler_buffer_init (cce_location_t * L, cce_error_handler_t * H, ccstr_buffer_t * B)
  __attribute__((nonnull(1,2,3)));

/* ------------------------------------------------------------------ */

ccstr_decl void ccstr_buffer_format (cce_location_t * L, ccstr_buffer_t * B, const char * template, ...)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_buffer_vformat (cce_location_t * L, ccstr_buffer_t * B, const char * template, va_list ap)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_buffer_fwrite (cce_location_t * L, ccstr_buffer_t * B, FILE * stream)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_buffer_write (cce_location_t * L, ccstr_buffer_t * B, int filedes)
  __attribute__((nonnull(1,2)));

ccstr_decl void ccstr_buffer_enlarge (cce_location_t * L, ccstr_buffer_t * B, size_t required_len)
  __attribute__((nonnull(1,2)));

__attribute__((pure,nonnull(1),always_inline))
static inline bool
ccstr_buffer_full_p (ccstr_buffer_t * B)
/* Return true if the buffer is full. */
{
  return (B->bufoff < B->buflen)? false : true;
}

/* ------------------------------------------------------------------ */

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_block_t
ccstr_buffer_output_block (ccstr_buffer_t * B)
/* Return a block representing the data in the buffer. */
{
  ccmem_block_t	block = {
    .ptr = B->bufptr,
    .len = B->bufoff
  };
  return block;
}

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_ascii_t
ccstr_buffer_output_ascii (ccstr_buffer_t * B)
/* Return a block representing the data in the buffer. */
{
  ccmem_ascii_t	block = {
    .ptr = (char *)B->bufptr,
    .len = B->bufoff
  };
  return block;
}

/* ------------------------------------------------------------------ */

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_block_t
ccstr_buffer_target_block (ccstr_buffer_t * B)
/* Return a block representing the free  room in the buffer.  The return
   value   of  this   function  is   meaningful  only   if  a   call  to
   "ccstr_buffer_full_p()" applied to the same buffer returns false. */
{
  ccmem_block_t	block = {
    .ptr = (B->bufptr + B->bufoff),
    .len = (B->buflen - B->bufoff)
  };
  return block;
}

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_ascii_t
ccstr_buffer_target_ascii (ccstr_buffer_t * B)
/* Return a block representing the free  room in the buffer.  The return
   value   of  this   function  is   meaningful  only   if  a   call  to
   "ccstr_buffer_full_p()" applied to the same buffer returns false. */
{
  ccmem_ascii_t	ascii = {
    .ptr = (char *)(B->bufptr + B->bufoff),
    .len = (B->buflen - B->bufoff)
  };
  return ascii;
}


/** --------------------------------------------------------------------
 ** Strings.
 ** ----------------------------------------------------------------- */

typedef void ccstr_final_t (ccstr_t * S);
typedef ccstr_t * ccstr_alloc_t (cce_location_t * L, size_t num_of_wchars);
typedef ccstr_t * ccstr_realloc_t (cce_location_t * L, ccstr_t * S, size_t new_num_of_wchars);
typedef void ccstr_free_t (ccstr_t * S);

struct ccstr_vtable_t {
  ccstr_final_t *	final;
  ccstr_alloc_t *	alloc;
  ccstr_realloc_t *	realloc;
  ccstr_free_t *	free;
};

struct ccstr_t {
  ccstr_vtable_t const *vtable;
  size_t		len;
  wchar_t const *	ptr;
  wchar_t		data[];
};

ccstr_decl ccstr_vtable_t const * const ccstr_malloc_vtable;

ccstr_decl ccstr_t * ccstr_new (cce_location_t * L, ccstr_vtable_t const * vtable, size_t num_of_wchars)
  __attribute__((nonnull(1),returns_nonnull));

ccstr_decl void ccstr_delete (ccstr_t * S)
  __attribute__((nonnull(1)));

ccstr_decl void ccstr_cleanup_handler_init (cce_location_t * L, cce_handler_t * H, ccstr_t * S)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_error_handler_init (cce_location_t * L, cce_handler_t * H, ccstr_t * S)
  __attribute__((nonnull(1,2,3)));

/* ------------------------------------------------------------------ */

ccstr_decl ccstr_t * ccstr_new_from_static (cce_location_t * L, ccstr_vtable_t const * vtable, wchar_t const * str, size_t num_of_wchars)
  __attribute__((nonnull(1,2,3),returns_nonnull));

ccstr_decl ccstr_t * ccstr_new_from_staticz (cce_location_t * L, ccstr_vtable_t const * vtable, wchar_t const * str)
  __attribute__((nonnull(1,2,3),returns_nonnull));

/* ------------------------------------------------------------------ */

ccstr_decl void ccstr_format (cce_location_t * L, ccstr_t * S, const char * template, ...)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_vformat (cce_location_t * L, ccstr_t * S, const char * template, va_list ap)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_fwrite (cce_location_t * L, ccstr_t * S, FILE * stream)
  __attribute__((nonnull(1,2,3)));

ccstr_decl void ccstr_write (cce_location_t * L, ccstr_t * S, int filedes)
  __attribute__((nonnull(1,2)));

ccstr_decl void ccstr_enlarge (cce_location_t * L, ccstr_t * S, size_t required_len)
  __attribute__((nonnull(1,2)));

#if 0

__attribute__((pure,nonnull(1),always_inline))
static inline bool
ccstr_full_p (ccstr_t * S)
/* Return true if the buffer is full. */
{
  return (S->bufoff < S->buflen)? false : true;
}

/* ------------------------------------------------------------------ */

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_block_t
ccstr_output_block (ccstr_t * S)
/* Return a block representing the data in the buffer. */
{
  ccmem_block_t	block = {
    .ptr = S->bufptr,
    .len = S->bufoff
  };
  return block;
}

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_ascii_t
ccstr_output_ascii (ccstr_t * S)
/* Return a block representing the data in the buffer. */
{
  ccmem_ascii_t	block = {
    .ptr = (char *)S->bufptr,
    .len = S->bufoff
  };
  return block;
}

/* ------------------------------------------------------------------ */

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_block_t
ccstr_target_block (ccstr_t * S)
/* Return a block representing the free  room in the buffer.  The return
   value   of  this   function  is   meaningful  only   if  a   call  to
   "ccstr_full_p()" applied to the same buffer returns false. */
{
  ccmem_block_t	block = {
    .ptr = (S->bufptr + S->bufoff),
    .len = (S->buflen - S->bufoff)
  };
  return block;
}

__attribute__((pure,nonnull(1),always_inline))
static inline ccmem_ascii_t
ccstr_target_ascii (ccstr_t * S)
/* Return a block representing the free  room in the buffer.  The return
   value   of  this   function  is   meaningful  only   if  a   call  to
   "ccstr_full_p()" applied to the same buffer returns false. */
{
  ccmem_ascii_t	ascii = {
    .ptr = (char *)(S->bufptr + S->bufoff),
    .len = (S->buflen - S->bufoff)
  };
  return ascii;
}

#endif


/** --------------------------------------------------------------------
 ** Condition objects definitions.
 ** ----------------------------------------------------------------- */

struct ccstr_descriptor_base_t {
  cce_descriptor_t      descriptor;
};

struct ccstr_condition_base_t {
  cce_condition_root_t  root;
};

ccstr_decl const ccstr_descriptor_base_t * const ccstr_descriptor_base;

ccstr_decl void ccstr_condition_init_base (ccstr_condition_base_t * C);
ccstr_decl bool ccstr_condition_is_base (const cce_condition_t * C);

/* ------------------------------------------------------------------ */

struct ccstr_descriptor_buffer_size_overflow_t {
  cce_descriptor_t      descriptor;
};

struct ccstr_condition_buffer_size_overflow_t {
  ccstr_condition_base_t	base;
  ccstr_buffer_t *		buffer;
  size_t			required_len;
};

ccstr_decl const ccstr_descriptor_buffer_size_overflow_t * const ccstr_descriptor_buffer_size_overflow;

ccstr_decl cce_condition_t * ccstr_condition_new_buffer_size_overflow (cce_location_t * L, ccstr_buffer_t * B, size_t required_len);
ccstr_decl void ccstr_condition_init_buffer_size_overflow (ccstr_condition_buffer_size_overflow_t * C, ccstr_buffer_t * B, size_t required_len);
ccstr_decl bool ccstr_condition_is_buffer_size_overflow (const cce_condition_t * C);

/* ------------------------------------------------------------------ */

struct ccstr_descriptor_buffer_output_incomplete_t {
  cce_descriptor_t      descriptor;
};

struct ccstr_condition_buffer_output_incomplete_t {
  ccstr_condition_base_t	base;
  ccstr_buffer_t *		buffer;
  size_t			written_len;
};

ccstr_decl const ccstr_descriptor_buffer_output_incomplete_t * const ccstr_descriptor_buffer_output_incomplete;

ccstr_decl cce_condition_t * ccstr_condition_new_buffer_output_incomplete (cce_location_t * L, ccstr_buffer_t * B, size_t written_len);
ccstr_decl void ccstr_condition_init_buffer_output_incomplete (ccstr_condition_buffer_output_incomplete_t * C,
							       ccstr_buffer_t * B, size_t written_len);
ccstr_decl bool ccstr_condition_is_buffer_output_incomplete (const cce_condition_t * C);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRINGS_H */

/* end of file */
