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
#include <ccnames.h>

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

ccstr_decl void ccstr_library_init (void)
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

  /* Offset of the next  free byte in the output buffer.  This is  also the number of
     bytes used in the buffer. */
  size_t	bufoff;
};

/* ------------------------------------------------------------------ */

ccstr_decl void ccname_init(ccstr_buffer_t) (cce_destination_t L, ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((__nonnull__(1,2)));

ccstr_decl void ccname_init(ccstr_buffer_t, copy) (cce_destination_t L, ccstr_buffer_t * dst, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccname_final(ccstr_buffer_t) (ccstr_buffer_t * B)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

ccstr_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t) (cce_destination_t L, size_t initial_buflen)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccstr_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, copy) (cce_destination_t L, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

ccstr_decl void ccname_delete(ccstr_buffer_t) (ccstr_buffer_t * B)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

ccstr_decl void ccname_init(ccstr_buffer_t, clean) (cce_destination_t L, cce_clean_handler_t * H,
							     ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccname_init(ccstr_buffer_t, error) (cce_destination_t L, cce_error_handler_t * H,
							     ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((__nonnull__(1,2,3)));

/* ------------------------------------------------------------------ */

ccstr_decl void ccname_init(ccstr_buffer_t, copy, clean) (cce_destination_t L, cce_clean_handler_t * H,
								   ccstr_buffer_t * dst, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3,4)));

ccstr_decl void ccname_init(ccstr_buffer_t, copy, error) (cce_destination_t L, cce_error_handler_t * H,
								   ccstr_buffer_t * dst, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3,4)));

/* ------------------------------------------------------------------ */

ccstr_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, clean) (cce_destination_t L, cce_clean_handler_t * H, size_t initial_buflen)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

ccstr_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, error) (cce_destination_t L, cce_error_handler_t * H, size_t initial_buflen)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

/* ------------------------------------------------------------------ */

ccstr_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, copy, clean) (cce_destination_t L, cce_clean_handler_t * H,
									      ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

ccstr_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, copy, error) (cce_destination_t L, cce_error_handler_t * H,
									      ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

/* ------------------------------------------------------------------ */

ccstr_decl void ccstr_buffer_format (cce_destination_t L, ccstr_buffer_t * B, const char * template, ...)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_buffer_vformat (cce_destination_t L, ccstr_buffer_t * B, const char * template, va_list ap)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_buffer_fwrite (cce_destination_t L, ccstr_buffer_t const * B, FILE * stream)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_buffer_write (cce_destination_t L, ccstr_buffer_t const * B, int filedes)
  __attribute__((__nonnull__(1,2)));

ccstr_decl void ccstr_buffer_enlarge (cce_destination_t L, ccstr_buffer_t * B, size_t required_len)
  __attribute__((__nonnull__(1,2)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccstr_buffer_full_p (ccstr_buffer_t * B)
/* Return true if the buffer is full. */
{
  return (B->bufoff < B->buflen)? false : true;
}

/* ------------------------------------------------------------------ */

__attribute__((__pure__,__nonnull__(1),__always_inline__))
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

__attribute__((__pure__,__nonnull__(1),__always_inline__))
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

__attribute__((__pure__,__nonnull__(1),__always_inline__))
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

__attribute__((__pure__,__nonnull__(1),__always_inline__))
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
 ** Buffer objects: exception handlers.
 ** ----------------------------------------------------------------- */

ccstr_decl void ccstr_init_and_register_buffer_clean_handler (cce_destination_t L,
							      cce_clean_handler_t * H, ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_init_and_register_buffer_error_handler (cce_destination_t L,
							      cce_error_handler_t * H, ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1,2,3)));

#define ccstr_init_and_register_buffer_handler(L,H,B)			\
  _Generic((H),								\
	   cce_clean_handler_t *: ccstr_init_and_register_buffer_clean_handler, \
	   cce_error_handler_t *: ccstr_init_and_register_buffer_error_handler)(L,H,B)


/** --------------------------------------------------------------------
 ** Buffer objects: implemented interfaces.
 ** ----------------------------------------------------------------- */

/* Constructor for a "ccstructs_dumpable_T" trait that prints a struct representation
   on some output channel. */
ccstructs_decl ccstructs_dumpable_T ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t) (ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Strings.
 ** ----------------------------------------------------------------- */

typedef void ccstr_final_t (ccstr_t * S);
typedef ccstr_t * ccstr_alloc_t (cce_destination_t L, size_t num_of_wchars);
typedef ccstr_t * ccstr_realloc_t (cce_destination_t L, ccstr_t * S, size_t new_num_of_wchars);
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

ccstr_decl ccstr_t * ccstr_new (cce_destination_t L, ccstr_vtable_t const * vtable, size_t num_of_wchars)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccstr_decl void ccstr_delete (ccstr_t * S)
  __attribute__((__nonnull__(1)));

ccstr_decl void ccstr_cleanup_handler_init (cce_destination_t L, cce_handler_t * H, ccstr_t * S)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_error_handler_init (cce_destination_t L, cce_handler_t * H, ccstr_t * S)
  __attribute__((__nonnull__(1,2,3)));

/* ------------------------------------------------------------------ */

ccstr_decl ccstr_t * ccstr_new_from_static (cce_destination_t L, ccstr_vtable_t const * vtable, wchar_t const * str, size_t num_of_wchars)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

ccstr_decl ccstr_t * ccstr_new_from_staticz (cce_destination_t L, ccstr_vtable_t const * vtable, wchar_t const * str)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

/* ------------------------------------------------------------------ */

ccstr_decl void ccstr_format (cce_destination_t L, ccstr_t * S, const char * template, ...)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_vformat (cce_destination_t L, ccstr_t * S, const char * template, va_list ap)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_fwrite (cce_destination_t L, ccstr_t * S, FILE * stream)
  __attribute__((__nonnull__(1,2,3)));

ccstr_decl void ccstr_write (cce_destination_t L, ccstr_t * S, int filedes)
  __attribute__((__nonnull__(1,2)));

ccstr_decl void ccstr_enlarge (cce_destination_t L, ccstr_t * S, size_t required_len)
  __attribute__((__nonnull__(1,2)));


/** --------------------------------------------------------------------
 ** Exceptional-condition object: buffer size overflow.
 ** ----------------------------------------------------------------- */

typedef struct ccstr_descriptor_buffer_size_overflow_t	ccstr_descriptor_buffer_size_overflow_t;
typedef struct ccstr_condition_buffer_size_overflow_t	ccstr_condition_buffer_size_overflow_t;

struct ccstr_descriptor_buffer_size_overflow_t {
  cce_descriptor_t	descriptor;
};

struct ccstr_condition_buffer_size_overflow_t {
  cce_condition_runtime_error_t	runtime_error;
  ccstr_buffer_t const *	buffer;
  size_t			required_len;
};

ccstr_decl void cce_descriptor_set_parent_to(ccstr_descriptor_buffer_size_overflow_t) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

ccstr_decl void ccstr_condition_init_buffer_size_overflow (cce_destination_t L,
							   ccstr_condition_buffer_size_overflow_t * C,
							   ccstr_buffer_t const * B, size_t required_len)
  __attribute__((__nonnull__(1,2)));

ccstr_decl cce_condition_t const * ccstr_condition_new_buffer_size_overflow (cce_destination_t L,
									     ccstr_buffer_t const * B, size_t required_len)
  __attribute__((__nonnull__(1,2)));

ccstr_decl bool ccstr_condition_is_buffer_size_overflow (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Exceptional-condition object: buffer output incomplete.
 ** ----------------------------------------------------------------- */

typedef struct ccstr_descriptor_buffer_output_incomplete_t	ccstr_descriptor_buffer_output_incomplete_t;
typedef struct ccstr_condition_buffer_output_incomplete_t	ccstr_condition_buffer_output_incomplete_t;

struct ccstr_descriptor_buffer_output_incomplete_t {
  cce_descriptor_t	descriptor;
};

struct ccstr_condition_buffer_output_incomplete_t {
  cce_condition_runtime_error_t	runtime_error;
  ccstr_buffer_t const *	buffer;
  size_t			written_len;
};

ccstr_decl void cce_descriptor_set_parent_to(ccstr_descriptor_buffer_output_incomplete_t) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

ccstr_decl void ccstr_condition_init_buffer_output_incomplete (cce_destination_t L,
							       ccstr_condition_buffer_output_incomplete_t * C,
							       ccstr_buffer_t const * B, size_t written_len)
  __attribute__((__nonnull__(1,2)));

ccstr_decl cce_condition_t const * ccstr_condition_new_buffer_output_incomplete (cce_destination_t L,
										 ccstr_buffer_t const * B, size_t written_len)
  __attribute__((__nonnull__(1,2)));

ccstr_decl bool ccstr_condition_is_buffer_output_incomplete (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRINGS_H */

/* end of file */
