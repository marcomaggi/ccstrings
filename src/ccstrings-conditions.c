/*
  Part of: CCStrings
  Contents: condition objects definitions
  Date: Tue Jul  4, 2017

  Abstract



  Copyright (C) 2017-2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstrings-internals.h"


/** --------------------------------------------------------------------
 ** Exceptional-condition object: buffer size overflow.
 ** ----------------------------------------------------------------- */

static cce_condition_delete_fun_t		ccstr_condition_delete_buffer_size_overflow;
static cce_condition_static_message_fun_t	ccstr_condition_static_message_buffer_size_overflow;

static ccstr_descriptor_buffer_size_overflow_t ccstr_descriptor_buffer_size_overflow = {
  /* This "parent" field is set below by the module initialisation function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= ccstr_condition_delete_buffer_size_overflow,
  .descriptor.final		= NULL,
  .descriptor.static_message	= ccstr_condition_static_message_buffer_size_overflow
};

void
cce_descriptor_set_parent_to(ccstr_descriptor_buffer_size_overflow_t) (cce_descriptor_t * const D)
{
  D->parent = cce_descriptor_pointer(ccstr_descriptor_buffer_size_overflow);
}

/* ------------------------------------------------------------------ */

void
ccstr_condition_delete_buffer_size_overflow (cce_condition_t * C)
/* The  delete  function  is  called  automatically  when  the  client  code  applies
   "cce_condition_delete()" to the argument C.   Here we release memory allocated for
   the condition object. */
{
  free(C);
}

char const *
ccstr_condition_static_message_buffer_size_overflow (cce_condition_t const * C CCE_UNUSED)
{
  return "requested new size of CCStrings buffer too big";
}

/* ------------------------------------------------------------------ */

void
ccstr_condition_init_buffer_size_overflow (cce_destination_t L CCSTR_UNUSED, ccstr_condition_buffer_size_overflow_t * C,
					   ccstr_buffer_t const * B, size_t required_len)
/* This initialisation function must be called both by:
 *
 * - The constructor function of this object type.
 *
 * - The initialisation functions of object types derived from this type.
 *
 * Here we call  the parent's initialisation function; then we  initialise the fields
 * of this type.
 */
{
  cce_condition_init_runtime_error(&(C->runtime_error));
  C->buffer		= B;
  C->required_len	= required_len;
}

cce_condition_t const *
ccstr_condition_new_buffer_size_overflow (cce_destination_t upper_L, ccstr_buffer_t const * B, size_t required_len)
/* This constructor function is the public  interface to the constructor of condition
 * objects of type "ccstr_condition_buffer_size_overflow_t".
 *
 * Here we:
 *
 * 1. Allocate memory for the condition object itself.
 *
 * 2. Initialise the descriptor field by calling "cce_condition_init()".
 *
 * 3. Call the initialisation function for this type.
 */
{
  cce_location_t	L[1];
  cce_error_handler_t	C_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_condition_buffer_size_overflow_t * C = cce_sys_malloc_guarded(L, C_H, sizeof(ccstr_condition_buffer_size_overflow_t));

    cce_condition_init((cce_condition_t *) C, cce_descriptor_pointer(ccstr_descriptor_buffer_size_overflow));
    ccstr_condition_init_buffer_size_overflow(L, C, B, required_len);

    cce_run_body_handlers(L);
    return (cce_condition_t const *) C;
  }
}

bool
ccstr_condition_is_buffer_size_overflow (cce_condition_t const * C)
{
  return cce_condition_is(C, cce_descriptor_pointer(ccstr_descriptor_buffer_size_overflow));
}


/** --------------------------------------------------------------------
 ** Exceptional-condition object: buffer output incomplete.
 ** ----------------------------------------------------------------- */

static cce_condition_delete_fun_t		ccstr_condition_delete_buffer_output_incomplete;
static cce_condition_static_message_fun_t	ccstr_condition_static_message_buffer_output_incomplete;

static ccstr_descriptor_buffer_output_incomplete_t ccstr_descriptor_buffer_output_incomplete = {
  /* This "parent" field is set below by the module initialisation function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= ccstr_condition_delete_buffer_output_incomplete,
  .descriptor.final		= NULL,
  .descriptor.static_message	= ccstr_condition_static_message_buffer_output_incomplete
};

void
cce_descriptor_set_parent_to(ccstr_descriptor_buffer_output_incomplete_t) (cce_descriptor_t * const D)
{
  D->parent = cce_descriptor_pointer(ccstr_descriptor_buffer_output_incomplete);
}

/* ------------------------------------------------------------------ */

void
ccstr_condition_delete_buffer_output_incomplete (cce_condition_t * C)
/* The  delete  function  is  called  automatically  when  the  client  code  applies
   "cce_condition_delete()" to the argument C.   Here we release memory allocated for
   the condition object. */
{
  free(C);
}

char const *
ccstr_condition_static_message_buffer_output_incomplete (cce_condition_t const * C CCE_UNUSED)
{
  return "writing buffer data to output device";
}

/* ------------------------------------------------------------------ */

void
ccstr_condition_init_buffer_output_incomplete (cce_destination_t L CCSTR_UNUSED, ccstr_condition_buffer_output_incomplete_t * C,
					   ccstr_buffer_t const * B, size_t written_len)
/* This initialisation function must be called both by:
 *
 * - The constructor function of this object type.
 *
 * - The initialisation functions of object types derived from this type.
 *
 * Here we call  the parent's initialisation function; then we  initialise the fields
 * of this type.
 */
{
  cce_condition_init_runtime_error(&(C->runtime_error));
  C->buffer		= B;
  C->written_len	= written_len;
}

cce_condition_t const *
ccstr_condition_new_buffer_output_incomplete (cce_destination_t upper_L, ccstr_buffer_t const * B, size_t written_len)
/* This constructor function is the public  interface to the constructor of condition
 * objects of type "ccstr_condition_buffer_output_incomplete_t".
 *
 * Here we:
 *
 * 1. Allocate memory for the condition object itself.
 *
 * 2. Initialise the descriptor field by calling "cce_condition_init()".
 *
 * 3. Call the initialisation function for this type.
 */
{
  cce_location_t	L[1];
  cce_error_handler_t	C_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_condition_buffer_output_incomplete_t * C = cce_sys_malloc_guarded(L, C_H, sizeof(ccstr_condition_buffer_output_incomplete_t));

    cce_condition_init((cce_condition_t *) C, cce_descriptor_pointer(ccstr_descriptor_buffer_output_incomplete));
    ccstr_condition_init_buffer_output_incomplete(L, C, B, written_len);

    cce_run_body_handlers(L);
    return (cce_condition_t const *) C;
  }
}

bool
ccstr_condition_is_buffer_output_incomplete (cce_condition_t const * C)
{
  return cce_condition_is(C, cce_descriptor_pointer(ccstr_descriptor_buffer_output_incomplete));
}


/** --------------------------------------------------------------------
 ** Initialisation.
 ** ----------------------------------------------------------------- */

void
ccstr_library_init (void)
{
  cce_descriptor_set_parent_to(cce_descriptor_runtime_error_t)(cce_descriptor_pointer(ccstr_descriptor_buffer_size_overflow));
  cce_descriptor_set_parent_to(cce_descriptor_runtime_error_t)(cce_descriptor_pointer(ccstr_descriptor_buffer_output_incomplete));
}

/* end of file */
