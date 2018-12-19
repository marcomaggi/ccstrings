/*
  Part of: CCStr
  Contents: handling of strings
  Date: Jul  6, 2017

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


/** --------------------------------------------------------------------
 ** Predefined CCExceptions handler: buffer.
 ** ----------------------------------------------------------------- */

#if 0
__attribute__((nonnull(1,2)))
static void
ccstr_handler_buffer_function (const cce_condition_t * C CCE_UNUSED, cce_handler_t * H)
{
  ccstr_buffer_final(H->pointer);
  if (0) { fprintf(stderr, "%s: done\n", __func__); }
}

void
ccstr_cleanup_handler_buffer_init (cce_location_t * L, cce_handler_t * H, ccstr_buffer_t * B)
{
  H->function	= ccstr_handler_buffer_function;
  H->pointer	= B;
  cce_register_cleanup_handler(L, H);
}

void
ccstr_error_handler_buffer_init (cce_location_t * L, cce_handler_t * H, ccstr_buffer_t * B)
{
  H->function	= ccstr_handler_buffer_function;
  H->pointer	= B;
  cce_register_error_handler(L, H);
}
#endif


/** --------------------------------------------------------------------
 ** Memory management.
 ** ----------------------------------------------------------------- */

#if 0

void
ccstr_buffer_enlarge (cce_location_t * L, ccstr_buffer_t * B, size_t required_len)
/* Reallocate the  buffer enlarging  it so  that it  can hold  more than
   "required_len" characters.  If an  error occurs reallocating: perform
   a non-local exit by jumping to L. */
{
  size_t	new_buflen;

  /* We want the new buffer length to  be a multiple of 4096 that leaves
     at least 4096 free characters  at the end after "newlen" characters
     have been consumed. */
  if (0) {
    size_t	tmplen;
    for (tmplen = B->buflen % 4096; tmplen > required_len; tmplen += 4096);
    tmplen	+= 4096;
    new_buflen	= B->buflen + tmplen;
  } else {
    /* We would like the "new_buflen" to be:
     *
     *   ((B->buflen + required_len) % 4096) * 4096 + 4096 + 4096
     *
     * we can compute this as:
     *
     *   ((B->buflen % 4096) + (required_len % 4096)) * 4096 + 4096 + 4096
     *   ((B->buflen % 4096) + (required_len % 4096) + 2) * 4096
     *   ((B->buflen % 4096) + (required_len % 4096) + 2) << 12
     *
     * but we  must also check  for overflow  when doing the  shift.  We
     * take  "UINT_MAX" as  upper  limit for  the  buffer size  (maximum
     * number of bytes).
     */
    size_t	num_of_chunks = (B->buflen % 4096) + (required_len % 4096) + 2;
    if ((UINT_MAX >> 12) > num_of_chunks) {
      new_buflen = num_of_chunks << 12;
    } else {
      cce_raise(L, ccstr_condition_new_buffer_size_overflow(L, B, required_len));
    }
  }

  B->bufptr	= cce_sys_realloc(L, B->bufptr, new_buflen);
  B->buflen	= new_buflen;
}

#endif


/** --------------------------------------------------------------------
 ** Formatting buffer contents.
 ** ----------------------------------------------------------------- */

#if 0
void
ccstr_buffer_format (cce_location_t * L, ccstr_buffer_t * B, const char * template, ...)
{
  size_t	required_len = 0;

  /* First attempt at writing the output. */
  {
    va_list	ap;
    va_start(ap, template);
    {
      ccstr_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, ap);
      if (block.len > required_len) {
	/* Success! */
	B->bufoff += required_len;
      } else {
	/* Not enough room! */
  	goto fail;
      }
    }
    va_end(ap);
    return;
  }

 fail:
  ccstr_buffer_enlarge(L, B, required_len);

  /* Second attempt  at writing  the output.  We  assume that  this will
     succeed.  */
  {
    va_list	ap;
    va_start(ap, template);
    {
      ccstr_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, ap);
      B->bufoff += required_len;
      assert(block.len > required_len);
    }
    va_end(ap);
  }
}

void
ccstr_buffer_vformat (cce_location_t * L, ccstr_buffer_t * B, const char * template, va_list ap)
{
  size_t	required_len = 0;

  /* First attempt at writing the output. */
  {
    va_list	aq;
    va_copy(aq, ap);
    {
      ccstr_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, aq);
      if (block.len > required_len) {
	/* Success! */
	B->bufoff += required_len;
      } else {
	/* Not enough room! */
  	goto fail;
      }
    }
    va_end(aq);
    return;
  }

 fail:
  ccstr_buffer_enlarge(L, B, required_len);

  /* Second attempt  at writing  the output.  We  assume that  this will
     succeed.  */
  {
    va_list	aq;
    va_copy(aq, ap);
    {
      ccstr_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, aq);
      B->bufoff += required_len;
      assert(block.len > required_len);
    }
    va_end(aq);
  }
}

#endif


/** --------------------------------------------------------------------
 ** Writing output.
 ** ----------------------------------------------------------------- */

#if 0

void
ccstr_buffer_fwrite (cce_location_t * L, ccstr_buffer_t * B, FILE * stream)
{
  const size_t	count = B->bufoff;
  size_t	rv;

  errno = 0;
  rv = fwrite(B->bufptr, 1, count, stream);
  if (count != rv) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

void
ccstr_buffer_write (cce_location_t * L, ccstr_buffer_t * B, int filedes)
{
  const ssize_t	count = (ssize_t)B->bufoff;
  ssize_t	rv;

 doit:
  errno = 0;
  rv = write(filedes, B->bufptr, count);
  if (count == rv) {
    /* Success. */
    return;
  } else if (0 <= rv) {
    /* Successfull call, but not all the data was writeen. */
    cce_raise(L, ccstr_condition_new_buffer_output_incomplete(L, B, (size_t)rv));
  } else if (EINTR == errno) {
    /* The call was interrupted by a signal.  Try again. */
    goto doit;
  } else {
    /* An error occurred. */
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

#endif

/* end of file */
