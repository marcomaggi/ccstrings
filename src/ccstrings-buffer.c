/*
  Part of: CCStr
  Contents: handling of output buffer
  Date: Fri Mar 17, 2017

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


/** --------------------------------------------------------------------
 ** Initialisation and finalisation.
 ** ----------------------------------------------------------------- */

void
ccstr_buffer_init (cce_location_t * L, ccstr_buffer_t * B, size_t initial_buflen)
/* Initialise the buffer  structure.  Allocate memory for  the buffer at
   the initial size of "initial_buflen".  If an error occurs allocating:
   perform a non-local exit by jumping to L. */
{
  B->bufptr	= cce_sys_malloc(L, initial_buflen);
  B->buflen	= initial_buflen;
  B->bufoff	= 0;
  memset(B->bufptr, 0, initial_buflen);
}

void
ccstr_buffer_final (ccstr_buffer_t * B)
{
  free(B->bufptr);
  B->bufptr	= NULL;
  B->buflen	= 0;
  B->bufoff	= 0;
}


/** --------------------------------------------------------------------
 ** Predefined CCExceptions handler: buffer.
 ** ----------------------------------------------------------------- */

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


/** --------------------------------------------------------------------
 ** Memory management.
 ** ----------------------------------------------------------------- */

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
      assert(0);
    }
  }

  B->bufptr	= cce_sys_realloc(L, B->bufptr, new_buflen);
  B->buflen	= new_buflen;
}


/** --------------------------------------------------------------------
 ** Writing output.
 ** ----------------------------------------------------------------- */

void
ccstr_buffer_write (cce_location_t * L, ccstr_buffer_t * B, const char * template, ...)
{
  size_t	required_len = 0;

  /* First attempt at writing the output. */
  {
    va_list	ap;
    va_start(ap, template);
    {
      size_t	pre_output_size = ccstr_buffer_output_size(B);
      required_len = vsnprintf(ccstr_buffer_output_target(B), pre_output_size, template, ap);
      if (pre_output_size > required_len) {
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
      size_t	pre_output_size = ccstr_buffer_output_size(B);
      required_len = vsnprintf(ccstr_buffer_output_target(B), pre_output_size, template, ap);
      B->bufoff += required_len;
      assert(pre_output_size > required_len);
    }
    va_end(ap);
  }
}

void
ccstr_buffer_vwrite (cce_location_t * L, ccstr_buffer_t * B, const char * template, va_list ap)
{
  size_t	required_len = 0;

  /* First attempt at writing the output. */
  {
    va_list	aq;
    va_copy(aq, ap);
    {
      size_t	pre_output_size = ccstr_buffer_output_size(B);
      required_len = vsnprintf(ccstr_buffer_output_target(B), pre_output_size, template, aq);
      if (pre_output_size > required_len) {
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
      size_t	pre_output_size = ccstr_buffer_output_size(B);
      required_len = vsnprintf(ccstr_buffer_output_target(B), pre_output_size, template, aq);
      B->bufoff += required_len;
      assert(pre_output_size > required_len);
    }
    va_end(aq);
  }
}

/* end of file */
