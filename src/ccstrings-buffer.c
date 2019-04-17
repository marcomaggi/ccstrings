/*
  Part of: CCStrings
  Contents: handling of output buffer
  Date: Fri Mar 17, 2017

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
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <errno.h>


/** --------------------------------------------------------------------
 ** Initialisation and finalisation.
 ** ----------------------------------------------------------------- */

void
ccname_init(ccstr_buffer_t) (cce_destination_t L, ccstr_buffer_t * const B, size_t const initial_buflen)
/* Initialise the  buffer structure.  Allocate memory  for the buffer at  the initial
   size of "initial_buflen".  If an error occurs allocating: perform a non-local exit
   by jumping to L. */
{
  B->bufptr	= ccmem_std_malloc(L, initial_buflen);
  B->buflen	= initial_buflen;
  B->bufoff	= 0;
  memset(B->bufptr, 0, initial_buflen);
}

void
ccname_init(ccstr_buffer_t, copy) (cce_destination_t L, ccstr_buffer_t * const dst, ccstr_buffer_t const * const src)
{
  dst->bufptr	= ccmem_std_malloc(L, src->buflen);
  dst->buflen	= src->buflen;
  dst->bufoff	= src->bufoff;
  memcpy(dst->bufptr, src->bufptr, dst->buflen);
}

/* ------------------------------------------------------------------ */

void
ccname_final(ccstr_buffer_t) (ccstr_buffer_t * B)
{
  ccmem_std_free(B->bufptr);
  B->bufptr	= NULL;
  B->buflen	= 0;
  B->bufoff	= 0;
}


/** --------------------------------------------------------------------
 ** Allocation and releasing.
 ** ----------------------------------------------------------------- */

static ccstr_buffer_t *
ccname_alloc(ccstr_buffer_t, error) (cce_destination_t L, ccmem_error_handler_t * B_H)
{
  return ccmem_std_malloc_guarded(L, B_H, sizeof(ccstr_buffer_t));
}

static void
ccname_release(ccstr_buffer_t) (ccstr_buffer_t * B)
{
  ccmem_std_free(B);
}


/** --------------------------------------------------------------------
 ** Construction and destruction.
 ** ----------------------------------------------------------------- */

ccstr_buffer_t *
ccname_new(ccstr_buffer_t) (cce_destination_t upper_L, size_t initial_buflen)
{
  cce_location_t	L[1];
  ccmem_error_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t *	B = ccname_alloc(ccstr_buffer_t, error)(L, B_H);

    ccname_init(ccstr_buffer_t)(L, B, initial_buflen);
    cce_run_body_handlers(L);
    return B;
  }
}

ccstr_buffer_t *
ccname_new(ccstr_buffer_t, copy) (cce_destination_t upper_L, ccstr_buffer_t const * const src)
{
  cce_location_t	L[1];
  ccmem_error_handler_t	dst_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t *	dst = ccname_alloc(ccstr_buffer_t, error)(L, dst_H);

    ccname_init(ccstr_buffer_t, copy)(L, dst, src);
    cce_run_body_handlers(L);
    return dst;
  }
}

void
ccname_delete(ccstr_buffer_t) (ccstr_buffer_t * B)
{
  ccname_final(ccstr_buffer_t)(B);
  ccname_release(ccstr_buffer_t)(B);
}


/** --------------------------------------------------------------------
 ** Exception handlers.
 ** ----------------------------------------------------------------- */

void
ccstr_init_and_register_buffer_clean_handler (cce_destination_t L, cce_clean_handler_t * const H, ccstr_buffer_t const * const B)
{
  cce_init_and_register_handler(L, H, cce_default_clean_handler_function,
				cce_resource_pointer(B), cce_resource_destructor(ccname_final(ccstr_buffer_t)));
}

void
ccstr_init_and_register_buffer_error_handler (cce_destination_t L, cce_error_handler_t * const H, ccstr_buffer_t const * const B)
{
  cce_init_and_register_handler(L, H, cce_default_error_handler_function,
				cce_resource_pointer(B), cce_resource_destructor(ccname_final(ccstr_buffer_t)));
}


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

void
ccname_init(ccstr_buffer_t, clean) (cce_destination_t L, cce_clean_handler_t * const H, ccstr_buffer_t * const B,
				    size_t const initial_buflen)
{
  ccname_init(ccstr_buffer_t)(L, B, initial_buflen);
  ccstr_init_and_register_buffer_clean_handler(L, H, B);
}

void
ccname_init(ccstr_buffer_t, error) (cce_destination_t L, cce_error_handler_t * const H, ccstr_buffer_t * const B,
				    size_t const initial_buflen)
{
  ccname_init(ccstr_buffer_t)(L, B, initial_buflen);
  ccstr_init_and_register_buffer_error_handler(L, H, B);
}

/* ------------------------------------------------------------------ */

void
ccname_init(ccstr_buffer_t, copy, clean) (cce_destination_t L, cce_clean_handler_t * const H,
					  ccstr_buffer_t * const dst, ccstr_buffer_t const * const src)
{
  ccname_init(ccstr_buffer_t, copy)(L, dst, src);
  ccstr_init_and_register_buffer_clean_handler(L, H, dst);
}

void
ccname_init(ccstr_buffer_t, copy, error) (cce_destination_t L, cce_error_handler_t * const H,
					  ccstr_buffer_t * const dst, ccstr_buffer_t const * const src)
{
  ccname_init(ccstr_buffer_t, copy)(L, dst, src);
  ccstr_init_and_register_buffer_error_handler(L, H, dst);
}

/* ------------------------------------------------------------------ */

ccstr_buffer_t *
ccname_new(ccstr_buffer_t, clean) (cce_destination_t L, cce_clean_handler_t * const H, size_t initial_buflen)
{
  ccstr_buffer_t *	B = ccname_new(ccstr_buffer_t)(L, initial_buflen);
  ccstr_init_and_register_buffer_clean_handler(L, H, B);
  return B;
}

ccstr_buffer_t *
ccname_new(ccstr_buffer_t, error) (cce_destination_t L, cce_error_handler_t * const H, size_t initial_buflen)
{
  ccstr_buffer_t *	B = ccname_new(ccstr_buffer_t)(L, initial_buflen);
  ccstr_init_and_register_buffer_error_handler(L, H, B);
  return B;
}

/* ------------------------------------------------------------------ */

ccstr_buffer_t *
ccname_new(ccstr_buffer_t, copy, clean) (cce_destination_t L, cce_clean_handler_t * const H, ccstr_buffer_t const * const src)
{
  ccstr_buffer_t *	dst = ccname_new(ccstr_buffer_t, copy)(L, src);
  ccstr_init_and_register_buffer_clean_handler(L, H, dst);
  return dst;
}

ccstr_buffer_t *
ccname_new(ccstr_buffer_t, copy, error) (cce_destination_t L, cce_error_handler_t * const H, ccstr_buffer_t const * const src)
{
  ccstr_buffer_t *	dst = ccname_new(ccstr_buffer_t, copy)(L, src);
  ccstr_init_and_register_buffer_error_handler(L, H, dst);
  return dst;
}


/** --------------------------------------------------------------------
 ** Memory management.
 ** ----------------------------------------------------------------- */

void
ccstr_buffer_enlarge (cce_destination_t L, ccstr_buffer_t * B, size_t required_len)
/* Reallocate the  buffer enlarging it so  that it can hold  more than "required_len"
   characters.  If an error occurs reallocating:  perform a non-local exit by jumping
   to L. */
{
  size_t	new_buflen;

  /* We want the new buffer length to be a multiple of 4096 that leaves at least 4096
     free characters at the end after "newlen" characters have been consumed. */
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
     * but we must also check for overflow  when doing the shift.  We take "UINT_MAX"
     * as upper limit for the buffer size (maximum number of bytes).
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


/** --------------------------------------------------------------------
 ** Formatting buffer contents.
 ** ----------------------------------------------------------------- */

void
ccstr_buffer_format (cce_destination_t L, ccstr_buffer_t * B, const char * template, ...)
{
  size_t	required_len = 0;

  /* First attempt at writing the output. */
  {
    va_list	ap;
    bool	done = false;

    va_start(ap, template);
    {
      ccmem_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, ap);
      if (block.len > required_len) {
	/* Success! */
	B->bufoff += required_len;
	done = true;
      } else {
	/* Not enough room! */
	done = false;
      }
    }
    va_end(ap);
    if (done) { return; }
  }

  ccstr_buffer_enlarge(L, B, required_len);

  /* Second attempt at writing the output.  We assume that this will succeed.  */
  {
    va_list	ap;
    va_start(ap, template);
    {
      ccmem_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, ap);
      B->bufoff += required_len;
      assert(block.len > required_len);
    }
    va_end(ap);
  }
}

void
ccstr_buffer_vformat (cce_destination_t L, ccstr_buffer_t * B, const char * template, va_list ap)
{
  size_t	required_len = 0;

  /* First attempt at writing the output. */
  {
    va_list	aq;
    bool	done = false;

    va_copy(aq, ap);
    {
      ccmem_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, aq);
      if (block.len > required_len) {
	/* Success! */
	B->bufoff += required_len;
	done = true;
      } else {
	/* Not enough room! */
	done = false;
      }
    }
    va_end(aq);
    if (done) { return; }
  }

  ccstr_buffer_enlarge(L, B, required_len);

  /* Second attempt at writing the output.  We assume that this will succeed.  */
  {
    va_list	aq;
    va_copy(aq, ap);
    {
      ccmem_ascii_t	block = ccstr_buffer_target_ascii(B);
      required_len = vsnprintf(block.ptr, block.len, template, aq);
      B->bufoff += required_len;
      assert(block.len > required_len);
    }
    va_end(aq);
  }
}


/** --------------------------------------------------------------------
 ** Writing output.
 ** ----------------------------------------------------------------- */

void
ccstr_buffer_fwrite (cce_destination_t L, ccstr_buffer_t const * const B, FILE * const stream)
{
  size_t const	count = B->bufoff;
  size_t	rv;

  errno = 0;
  rv = fwrite(B->bufptr, 1, count, stream);
  if (count != rv) {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

void
ccstr_buffer_write (cce_destination_t L, ccstr_buffer_t const * const B, int const filedes)
{
  ssize_t const	count = (ssize_t)(B->bufoff);
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


/** --------------------------------------------------------------------
 ** Trait "ccstructs_dumpable_T": implementation for "ccstr_buffer_t".
 ** ----------------------------------------------------------------- */

static ccname_trait_method_type(ccstructs_dumpable_T, dump)  ccname_trait_method(ccstructs_dumpable_T, ccstr_buffer_t, dump);

static ccname_trait_table_type(ccstructs_dumpable_T) const ccname_trait_table(ccstructs_dumpable_T, ccstr_buffer_t) = {
  .dump	= ccname_trait_method(ccstructs_dumpable_T, ccstr_buffer_t, dump)
};

ccstructs_dumpable_T
ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t) (ccstr_buffer_t const * S)
{
  return ccname_new(ccstructs_dumpable_T)(ccstructs_core(S), &ccname_trait_table(ccstructs_dumpable_T, ccstr_buffer_t));
}

void
ccname_trait_method(ccstructs_dumpable_T, ccstr_buffer_t, dump) (cce_destination_t L, ccstructs_dumpable_T the_trait)
{
  CCSTRUCTS_PC(ccstr_buffer_t const, B, ccstructs_dumpable_self(the_trait));

  ccstr_buffer_fwrite(L, B, stderr);
}

/* end of file */
