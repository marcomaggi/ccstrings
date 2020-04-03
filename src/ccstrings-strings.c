/*
  Part of: CCStrings
  Contents: handling of strings
  Date: Jul  6, 2017

  Abstract



  Copyright (C) 2017, 2019, 2020 Marco Maggi <mrc.mgg@gmail.com>

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

#include "ccstrings-internals.h"
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <wchar.h>


/** --------------------------------------------------------------------
 ** Table of functions with malloc memory management.
 ** ----------------------------------------------------------------- */

static void
ccstr_malloc_table_final (ccstr_t * S)
{
  S->vtable->free(S);
}

static ccstr_t *
ccstr_malloc_table_alloc (cce_location_t * L, size_t num_of_wchars)
{
  return cce_sys_malloc(L, sizeof(ccstr_t) + num_of_wchars);
}

static ccstr_t *
ccstr_malloc_table_realloc (cce_location_t * L, ccstr_t * S, size_t new_num_of_wchars)
{
  return cce_sys_realloc(L, S, sizeof(ccstr_t) + new_num_of_wchars);
}

static void
ccstr_malloc_table_free (ccstr_t * S)
{
  free(S);
}

static ccstr_vtable_t const ccstr_malloc_vtable_stru = {
  .final	= ccstr_malloc_table_final,
  .alloc	= ccstr_malloc_table_alloc,
  .realloc	= ccstr_malloc_table_realloc,
  .free		= ccstr_malloc_table_free
};

ccstr_vtable_t const * const ccstr_malloc_vtable = &ccstr_malloc_vtable_stru;


/** --------------------------------------------------------------------
 ** Basic construction and destruction.
 ** ----------------------------------------------------------------- */

ccstr_t *
ccstr_new (cce_location_t * L, ccstr_vtable_t const * const vtable, size_t num_of_wchars)
/* Build a new string structure.  Allocate  memory for the buffer at the
   initial  size of  "num_of_wchars".   If an  error occurs  allocating:
   perform a non-local exit by jumping to "L". */
{
  ccstr_t *	S = vtable->alloc(L, num_of_wchars);
  S->vtable	= vtable;
  S->len	= num_of_wchars;
  S->ptr	= &(S->data[0]);
  return S;
}

void
ccstr_delete (ccstr_t * S)
/* Call the  finalisation function registered  in "S".  After  this call
   "S" is no more valid. */
{
  S->vtable->final(S);
}


/** --------------------------------------------------------------------
 ** Other constructors.
 ** ----------------------------------------------------------------- */

ccstr_t *
ccstr_new_from_static (cce_location_t * L, ccstr_vtable_t const * vtable, wchar_t const * str, size_t num_of_wchars)
/* Initialise  a string  structure with  a statically-allocated  string.
   Allocate memory for  the structure itself, but not for  the data.  If
   an error occurs allocating: perform a non-local exit by jumping to L.
   The pointer  "str" must reference  a memory  block of at  least "len"
   characters. */
{
  ccstr_t *	S = vtable->alloc(L, num_of_wchars);
  S->vtable	= vtable;
  S->len	= num_of_wchars;
  S->ptr	= str;
  return S;
}

ccstr_t *
ccstr_new_from_staticz (cce_location_t * L, ccstr_vtable_t const * vtable, wchar_t const * str)
/* Initialise   a   string   structure  with   a   statically-allocated,
   zero-terminated string.   Allocate memory  for the  structure itself,
   but  not for  the data.   If an  error occurs  allocating: perform  a
   non-local exit by  jumping to L.  The pointer "str"  must reference a
   memory block holding a zero-terminated string. */
{
  return ccstr_new_from_static(L, vtable, str, wcslen(str));
}

/* end of file */
