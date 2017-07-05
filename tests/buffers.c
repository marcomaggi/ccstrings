/*
  Part of: CCStrings
  Contents: test program for output bufers
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

#include "ccstrings.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void
test_buffer_allocation (void)
/* Test explicit buffer initialisation and finalisation. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  volatile bool		error_flag = false;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
    error_flag = true;
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_buffer_final(B);
    cce_run_cleanup_handlers(L);
  }
  assert(false == error_flag);
}


static void
test_buffer_handler (void)
/* Test implicit buffer finalisation with a CCExceptions handler. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_handler_t		B_H[1];
  volatile bool		error_flag = false;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
    error_flag = true;
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_cleanup_handler_buffer_init(L, B_H, B);
    cce_run_cleanup_handlers(L);
  }
  assert(false == error_flag);
}


static void
test_buffer_write (void)
/* Test writing a string to the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_handler_t		B_H[1];
  volatile bool		error_flag = false;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
    error_flag = true;
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_cleanup_handler_buffer_init(L, B_H, B);
    ccstr_buffer_write(L, B, "ciao\n");
    if (0) { fprintf(stderr, "%s: \"%s\"\n", __func__, ccstr_buffer_output(B)); }
    assert(0 == strcmp(ccstr_buffer_output(B), "ciao\n"));
    cce_run_cleanup_handlers(L);
  }
  assert(false == error_flag);
}


static void
test_buffer_write_realloc (void)
/* Test  writing  a  string  to  the  buffer in  a  way  that  causes  a
   reallocation of the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_handler_t		B_H[1];
  volatile bool		error_flag = false;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
    error_flag = true;
  } else {
    ccstr_buffer_init(L, B, 1);
    ccstr_cleanup_handler_buffer_init(L, B_H, B);
    ccstr_buffer_write(L, B, "ciao %d %d %d\n", 1, 2, 3);
    if (0) { fprintf(stderr, "%s: \"%s\"\n", __func__, ccstr_buffer_output(B)); }
    assert(0 == strcmp(ccstr_buffer_output(B), "ciao 1 2 3\n"));
    cce_run_cleanup_handlers(L);
  }
  assert(false == error_flag);
}


static void
test_buffer_write_multiple (void)
/* Test writing multiple strings to the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_handler_t		B_H[1];
  volatile bool		error_flag = false;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
    error_flag = true;
  } else {
    ccstr_buffer_init(L, B, 123);
    ccstr_cleanup_handler_buffer_init(L, B_H, B);
    ccstr_buffer_write(L, B, "ciao");
    ccstr_buffer_write(L, B, " mamma\n");
    if (0) { fprintf(stderr, "%s: \"%s\"\n", __func__, ccstr_buffer_output(B)); }
    assert(0 == strcmp(ccstr_buffer_output(B), "ciao mamma\n"));
    cce_run_cleanup_handlers(L);
  }
  assert(false == error_flag);
}


static void
test_buffer_write_multiple_realloc (void)
/* Test writing  multiple strings to the  buffer in a way  that causes a
   reallocation of the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_handler_t		B_H[1];
  volatile bool		error_flag = false;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
    error_flag = true;
  } else {
    ccstr_buffer_init(L, B, 1);
    ccstr_cleanup_handler_buffer_init(L, B_H, B);
    ccstr_buffer_write(L, B, "ciao ");
    ccstr_buffer_write(L, B, "mamma\n");
    if (0) { fprintf(stderr, "%s: \"%s\"\n", __func__, ccstr_buffer_output(B)); }
    assert(0 == strcmp(ccstr_buffer_output(B), "ciao mamma\n"));
    cce_run_cleanup_handlers(L);
  }
  assert(false == error_flag);
}


int
main (int argc CCSTR_UNUSED, const char *const argv[] CCSTR_UNUSED)
{
  if (1) { test_buffer_allocation(); }
  if (1) { test_buffer_handler(); }
  if (1) { test_buffer_write(); }
  if (1) { test_buffer_write_realloc(); }
  if (1) { test_buffer_write_multiple(); }
  if (1) { test_buffer_write_multiple_realloc(); }
  exit(EXIT_SUCCESS);
}

/* end of file */
