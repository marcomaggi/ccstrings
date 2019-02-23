/*
  Part of: CCStrings
  Contents: test program for output bufers
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
 ** Header files.
 ** ----------------------------------------------------------------- */

#include "ccstrings.h"
#include <cctests.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** --------------------------------------------------------------------
 ** Constructors and destructors.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Test explicit buffer initialisation and finalisation. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_buffer_final(B);
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Test implicit buffer finalisation with a CCExceptions handler. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_clean_handler_buffer_init(L, B_H, B);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Buffer formatting.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Test writing a string to the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_clean_handler_buffer_init(L, B_H, B);
    ccstr_buffer_format(L, B, "ciao\n");
    if (0) {
      ccmem_ascii_t	block = ccstr_buffer_output_ascii(B);
      fprintf(stderr, "%s: \"%s\"\n", __func__, (char *)block.ptr);
    }
    cctests_assert_asciiz(L, ccstr_buffer_output_ascii(B).ptr, "ciao\n");
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Test writing  a string to the  buffer in a way  that causes a reallocation  of the
   buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 1);
    ccstr_clean_handler_buffer_init(L, B_H, B);
    ccstr_buffer_format(L, B, "ciao %d %d %d\n", 1, 2, 3);
    if (0) {
      ccmem_ascii_t	block = ccstr_buffer_output_ascii(B);
      fprintf(stderr, "%s: \"%s\"\n", __func__, (char *)block.ptr);
    }
    cctests_assert_asciiz(L, ccstr_buffer_output_ascii(B).ptr, "ciao 1 2 3\n");
    cce_run_body_handlers(L);
  }
}

void
test_2_3 (cce_destination_t upper_L)
/* Test writing multiple strings to the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_clean_handler_buffer_init(L, B_H, B);
    ccstr_buffer_format(L, B, "ciao");
    ccstr_buffer_format(L, B, " mamma\n");
    if (0) {
      ccmem_ascii_t	block = ccstr_buffer_output_ascii(B);
      fprintf(stderr, "%s: \"%s\"\n", __func__, (char *)block.ptr);
    }
    cctests_assert_asciiz(L, ccstr_buffer_output_ascii(B).ptr, "ciao mamma\n");
    cce_run_body_handlers(L);
  }
}

void
test_2_4 (cce_destination_t upper_L)
/* Test writing multiple strings to the buffer in a way that causes a reallocation of
   the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 1);
    ccstr_clean_handler_buffer_init(L, B_H, B);
    ccstr_buffer_format(L, B, "ciao ");
    ccstr_buffer_format(L, B, "mamma\n");
    if (0) {
      ccmem_ascii_t	block = ccstr_buffer_output_ascii(B);
      fprintf(stderr, "%s: \"%s\"\n", __func__, (char *)block.ptr);
    }
    cctests_assert_asciiz(L, ccstr_buffer_output_ascii(B).ptr, "ciao mamma\n");
    cce_run_body_handlers(L);
  }
}

void
test_2_5 (cce_destination_t upper_L)
/* Test writing a buffer to a "FILE". */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_init(L, B, 1);
    ccstr_clean_handler_buffer_init(L, B_H, B);
    ccstr_buffer_format(L, B, "ciao ");
    ccstr_buffer_format(L, B, "mamma\n");
    if (0) {
      ccmem_ascii_t	block = ccstr_buffer_output_ascii(B);
      fprintf(stderr, "%s: \"%s\"\n", __func__, (char *)block.ptr);
    }
    ccstr_buffer_fwrite(L, B, stdout);
    cctests_assert_asciiz(L, ccstr_buffer_output_ascii(B).ptr, "ciao mamma\n");
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Let's go.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  ccstr_library_init();

  cctests_init("tests for buffers");
  {
    cctests_begin_group("constructors and destructors");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
    }
    cctests_end_group();

    cctests_begin_group("buffer formatting");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
      cctests_run(test_2_4);
      cctests_run(test_2_5);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
