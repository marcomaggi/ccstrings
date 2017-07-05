/*
  Part of: CCStrings
  Contents: condition objects definitions
  Date: Tue Jul  4, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstrings-internals.h"


/** --------------------------------------------------------------------
 ** Base condition type.
 ** ----------------------------------------------------------------- */

static void condition_final_base (cce_condition_t * C);
static const char * condition_static_message_base (const cce_condition_t * C);

/* Instance of condition descriptor.   The "parent" field is initialised
   to  NULL   here  and  reinitialised   to  the  "root"  later   by  an
   initialisation function. */
static ccstr_descriptor_base_t descriptor_base = {
  .descriptor.parent            = NULL,
  .descriptor.delete            = NULL,
  .descriptor.final             = condition_final_base,
  .descriptor.static_message    = condition_static_message_base
};

const ccstr_descriptor_base_t * const ccstr_descriptor_base = &descriptor_base;

void
ccstr_condition_init_base (ccstr_condition_base_t * C CCSTR_UNUSED)
/* Initialise an already allocated condition object. */
{
  return;
}

void
condition_final_base (cce_condition_t * C CCSTR_UNUSED)
/* Finalise a condition object; do not release memory. */
{
  return;
}

static const char *
condition_static_message_base (const cce_condition_t * C CCSTR_UNUSED)
{
  return "CCStrings base exceptional condition";
}

bool
ccstr_condition_is_base (const cce_condition_t * C)
{
  return cce_is_condition(C, &descriptor_base.descriptor);
}


/** --------------------------------------------------------------------
 ** Condition object: size overflow.
 ** ----------------------------------------------------------------- */

static void condition_delete_buffer_size_overflow  (cce_condition_t * C);
static void condition_final_buffer_size_overflow (cce_condition_t * C);
static const char * condition_static_message_buffer_size_overflow (const cce_condition_t * C);

/* Instance of condition descriptor.   The "parent" field is initialised
   to  NULL   here  and  reinitialised   to  the  "root"  later   by  an
   initialisation function. */
static ccstr_descriptor_buffer_size_overflow_t descriptor_buffer_size_overflow = {
  .descriptor.parent            = &descriptor_base.descriptor,
  .descriptor.delete            = condition_delete_buffer_size_overflow,
  .descriptor.final             = condition_final_buffer_size_overflow,
  .descriptor.static_message    = condition_static_message_buffer_size_overflow
};

const ccstr_descriptor_buffer_size_overflow_t * const ccstr_descriptor_buffer_size_overflow = &descriptor_buffer_size_overflow;

cce_condition_t *
ccstr_condition_new_buffer_size_overflow (cce_location_t * L, ccstr_buffer_t * B, size_t required_len)
/* Allocate a condition object and initialise it. */
{
  ccstr_condition_buffer_size_overflow_t *	C = cce_sys_malloc(L, sizeof(ccstr_condition_buffer_size_overflow_t));
  cce_condition_init((cce_condition_t *)C, &descriptor_buffer_size_overflow.descriptor);
  ccstr_condition_init_buffer_size_overflow(C, B, required_len);
  return (cce_condition_t *) C;
}

void
condition_delete_buffer_size_overflow (cce_condition_t * C)
/* Release the condition object memory. */
{
  free(C);
}

void
ccstr_condition_init_buffer_size_overflow (ccstr_condition_buffer_size_overflow_t * C, ccstr_buffer_t * B, size_t required_len)
/* Initialise an already allocated condition object. */
{
  ccstr_condition_init_base(&(C->base));
  C->buffer		= B;
  C->required_len	= required_len;
}

void
condition_final_buffer_size_overflow (cce_condition_t * C CCE_UNUSED)
/* Finalise a condition object; do not release memory. */
{
  return;
}

static const char *
condition_static_message_buffer_size_overflow (const cce_condition_t * C CCE_UNUSED)
{
  return "requested new size of CCStrings buffer too big";
}

bool
ccstr_condition_is_buffer_size_overflow (const cce_condition_t * C)
{
  return cce_is_condition(C, &descriptor_buffer_size_overflow.descriptor);
}


/** --------------------------------------------------------------------
 ** Initialisation.
 ** ----------------------------------------------------------------- */

void
ccstr_init (void)
{
  cce_descriptor_set_root_parent(&descriptor_base.descriptor);
}

/* end of file */
