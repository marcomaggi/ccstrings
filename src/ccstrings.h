/*
  Part of: CCStrings
  Contents: public header file
  Date: Apr 17, 2017

  Abstract

	This header file must be included  in all the source files using
	CCStrings.

  Copyright (C) 2017-2020 Marco Maggi <mrc.mgg@gmail.com>

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

#ifdef __cplusplus
extern "C" {
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

cclib_decl void ccstr_library_init (void)
  CCLIB_FUNC_ATTRIBUTE_CONSTRUCTOR;


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

cclib_decl char const *	ccstr_version_string		(void);
cclib_decl int		ccstr_version_interface_current	(void);
cclib_decl int		ccstr_version_interface_revision(void);
cclib_decl int		ccstr_version_interface_age	(void);


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
 ** Subordinate header files.
 ** ----------------------------------------------------------------- */

#include <ccstrings-buffers.h>


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

cclib_decl ccstr_vtable_t const * const ccstr_malloc_vtable;

cclib_decl ccstr_t * ccstr_new (cce_destination_t L, ccstr_vtable_t const * vtable, size_t num_of_wchars)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl void ccstr_delete (ccstr_t * S)
  __attribute__((__nonnull__(1)));

cclib_decl void ccstr_cleanup_handler_init (cce_destination_t L, cce_handler_t * H, ccstr_t * S)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_error_handler_init (cce_destination_t L, cce_handler_t * H, ccstr_t * S)
  __attribute__((__nonnull__(1,2,3)));

/* ------------------------------------------------------------------ */

cclib_decl ccstr_t * ccstr_new_from_static (cce_destination_t L, ccstr_vtable_t const * vtable, wchar_t const * str, size_t num_of_wchars)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

cclib_decl ccstr_t * ccstr_new_from_staticz (cce_destination_t L, ccstr_vtable_t const * vtable, wchar_t const * str)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

/* ------------------------------------------------------------------ */

cclib_decl void ccstr_format (cce_destination_t L, ccstr_t * S, const char * template, ...)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_vformat (cce_destination_t L, ccstr_t * S, const char * template, va_list ap)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_fwrite (cce_destination_t L, ccstr_t * S, FILE * stream)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_write (cce_destination_t L, ccstr_t * S, int filedes)
  __attribute__((__nonnull__(1,2)));

cclib_decl void ccstr_enlarge (cce_destination_t L, ccstr_t * S, size_t required_len)
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

cclib_decl void cce_descriptor_set_parent_to(ccstr_descriptor_buffer_size_overflow_t) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void ccstr_condition_init_buffer_size_overflow (cce_destination_t L,
							   ccstr_condition_buffer_size_overflow_t * C,
							   ccstr_buffer_t const * B, size_t required_len)
  __attribute__((__nonnull__(1,2)));

cclib_decl cce_condition_t const * ccstr_condition_new_buffer_size_overflow (cce_destination_t L,
									     ccstr_buffer_t const * B, size_t required_len)
  __attribute__((__nonnull__(1,2)));

cclib_decl bool ccstr_condition_is_buffer_size_overflow (cce_condition_t const * C)
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

cclib_decl void cce_descriptor_set_parent_to(ccstr_descriptor_buffer_output_incomplete_t) (cce_descriptor_t * const D)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl void ccstr_condition_init_buffer_output_incomplete (cce_destination_t L,
							       ccstr_condition_buffer_output_incomplete_t * C,
							       ccstr_buffer_t const * B, size_t written_len)
  __attribute__((__nonnull__(1,2)));

cclib_decl cce_condition_t const * ccstr_condition_new_buffer_output_incomplete (cce_destination_t L,
										 ccstr_buffer_t const * B, size_t written_len)
  __attribute__((__nonnull__(1,2)));

cclib_decl bool ccstr_condition_is_buffer_output_incomplete (cce_condition_t const * C)
  __attribute__((__pure__,__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCSTRINGS_H */

/* end of file */
