/*
  Part of: CCStrings
  Contents: public header file
  Date: Apr 17, 2017

  Abstract

	This header file must be included in all the source files using CCStrings.

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

#ifndef CCSTRINGS_BUFFERS_H
#define CCSTRINGS_BUFFERS_H 1


/** --------------------------------------------------------------------
 ** Buffer handling: type definitions.
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


/** --------------------------------------------------------------------
 ** Buffer handling: plain constructors and destructors.
 ** ----------------------------------------------------------------- */

cclib_decl void ccname_init(ccstr_buffer_t) (cce_destination_t L, ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((__nonnull__(1,2)));

cclib_decl void ccname_init(ccstr_buffer_t, copy) (cce_destination_t L, ccstr_buffer_t * dst, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccname_final(ccstr_buffer_t) (ccstr_buffer_t * B)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

cclib_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t) (cce_destination_t L, size_t initial_buflen)
  __attribute__((__nonnull__(1),__returns_nonnull__));

cclib_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, copy) (cce_destination_t L, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cclib_decl void ccname_delete(ccstr_buffer_t) (ccstr_buffer_t * B)
  __attribute__((__nonnull__(1)));


/** --------------------------------------------------------------------
 ** Buffer objects: exception handlers.
 ** ----------------------------------------------------------------- */

cclib_decl void ccstr_init_and_register_final_buffer_clean_handler (cce_destination_t L,
								    cce_clean_handler_t * H, ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_init_and_register_final_buffer_error_handler (cce_destination_t L,
								    cce_error_handler_t * H, ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1,2,3)));

#define ccstr_init_and_register_final_buffer_handler(L,H,B)		\
  _Generic((H),								\
	   cce_clean_handler_t *: ccstr_init_and_register_final_buffer_clean_handler, \
	   cce_error_handler_t *: ccstr_init_and_register_final_buffer_error_handler)(L,H,B)

/* ------------------------------------------------------------------ */

cclib_decl void ccstr_init_and_register_delete_buffer_clean_handler (cce_destination_t L,
								     cce_clean_handler_t * H, ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_init_and_register_delete_buffer_error_handler (cce_destination_t L,
								     cce_error_handler_t * H, ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1,2,3)));

#define ccstr_init_and_register_delete_buffer_handler(L,H,B)		\
  _Generic((H),								\
	   cce_clean_handler_t *: ccstr_init_and_register_delete_buffer_clean_handler, \
	   cce_error_handler_t *: ccstr_init_and_register_delete_buffer_error_handler)(L,H,B)


/** --------------------------------------------------------------------
 ** Buffer handling: guarded constructors and destructors.
 ** ----------------------------------------------------------------- */

cclib_decl void ccname_init(ccstr_buffer_t, clean) (cce_destination_t L, cce_clean_handler_t * H,
						    ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccname_init(ccstr_buffer_t, error) (cce_destination_t L, cce_error_handler_t * H,
						    ccstr_buffer_t * B, size_t initial_buflen)
  __attribute__((__nonnull__(1,2,3)));

/* ------------------------------------------------------------------ */

cclib_decl void ccname_init(ccstr_buffer_t, copy, clean) (cce_destination_t L, cce_clean_handler_t * H,
							  ccstr_buffer_t * dst, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3,4)));

cclib_decl void ccname_init(ccstr_buffer_t, copy, error) (cce_destination_t L, cce_error_handler_t * H,
							  ccstr_buffer_t * dst, ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3,4)));

/* ------------------------------------------------------------------ */

cclib_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, clean) (cce_destination_t L, cce_clean_handler_t * H, size_t initial_buflen)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

cclib_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, error) (cce_destination_t L, cce_error_handler_t * H, size_t initial_buflen)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

/* ------------------------------------------------------------------ */

cclib_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, copy, clean) (cce_destination_t L, cce_clean_handler_t * H,
								     ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));

cclib_decl ccstr_buffer_t * ccname_new(ccstr_buffer_t, copy, error) (cce_destination_t L, cce_error_handler_t * H,
								     ccstr_buffer_t const * src)
  __attribute__((__nonnull__(1,2,3),__returns_nonnull__));


/** --------------------------------------------------------------------
 ** Buffer handling: format functions.
 ** ----------------------------------------------------------------- */

cclib_decl void ccstr_buffer_format (cce_destination_t L, ccstr_buffer_t * B, const char * template, ...)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_buffer_vformat (cce_destination_t L, ccstr_buffer_t * B, const char * template, va_list ap)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_buffer_fwrite (cce_destination_t L, ccstr_buffer_t const * B, FILE * stream)
  __attribute__((__nonnull__(1,2,3)));

cclib_decl void ccstr_buffer_write (cce_destination_t L, ccstr_buffer_t const * B, int filedes)
  __attribute__((__nonnull__(1,2)));

cclib_decl void ccstr_buffer_enlarge (cce_destination_t L, ccstr_buffer_t * B, size_t required_len)
  __attribute__((__nonnull__(1,2)));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccstr_buffer_is_full (ccstr_buffer_t * B)
/* Return true if the buffer is full. */
{
  return (B->bufoff < B->buflen)? false : true;
}


/** --------------------------------------------------------------------
 ** Buffer handling: inspection.
 ** ----------------------------------------------------------------- */

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
/* Return a block representing the free room in the buffer.  The return value of this
   function is meaningful  only if a call to "ccstr_buffer_is_full()"  applied to the
   same buffer returns false. */
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
/* Return a block representing the free room in the buffer.  The return value of this
   function is meaningful  only if a call to "ccstr_buffer_is_full()"  applied to the
   same buffer returns false. */
{
  ccmem_ascii_t	ascii = {
    .ptr = (char *)(B->bufptr + B->bufoff),
    .len = (B->buflen - B->bufoff)
  };
  return ascii;
}


/** --------------------------------------------------------------------
 ** Buffer objects: implemented interfaces.
 ** ----------------------------------------------------------------- */

cclib_decl ccstructs_dtor_T ccname_trait_new(ccstructs_dtor_T, ccstr_buffer_t, embedded) (ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1)));

cclib_decl ccstructs_dtor_T ccname_trait_new(ccstructs_dtor_T, ccstr_buffer_t, standalone) (ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1)));

/* Constructor for a "ccstructs_dumpable_T" trait that prints a struct representation
   on some output channel. */
cclib_decl ccstructs_dumpable_T ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t) (ccstr_buffer_t const * B)
  __attribute__((__nonnull__(1)));




/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CCSTRINGS_BUFFERS_H */

/* end of file */
