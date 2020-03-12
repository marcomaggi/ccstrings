/*
  Part of: CCStrings
  Contents: test program for output bufers
  Date: Fri Mar 17, 2017

  Abstract



  Copyright (C) 2017-2019 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Convenience definitions.
 ** ----------------------------------------------------------------- */

typedef struct envelope_t	envelope_t;

struct envelope_t {
  ccstr_buffer_t	B[1];
};

void
ccname_init(envelope_t) (cce_destination_t upper_L, envelope_t * E)
{
  cce_location_t	L[1];
  cce_error_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t)(L, E->B, 64);
    ccstr_init_and_register_final_buffer_handler(L, B_H, E->B);

    /* Initialise the other fields of E, if any. */
    cce_run_body_handlers(L);
  }
}

void
ccname_init(envelope_t, from_buffer)
  (cce_destination_t L, envelope_t * E, ccstr_buffer_t const * B)
{
  ccname_init(ccstr_buffer_t, copy)(L, E->B, B);
}

void
ccname_final(envelope_t) (envelope_t * E)
{
  ccname_final(ccstr_buffer_t)(E->B);
}

void
ccname_init(envelope_t, clean)
  (cce_destination_t L, cce_clean_handler_t * E_H, envelope_t * E)
{
  ccname_init(envelope_t)(L, E);
  cce_init_and_register_handler
    (L, E_H, cce_default_clean_handler_function,
     cce_resource_pointer(E),
     cce_resource_destructor(ccname_final(envelope_t)));
}

void
ccname_init(envelope_t, error)
  (cce_destination_t L, cce_error_handler_t * E_H, envelope_t * E)
{
  ccname_init(envelope_t)(L, E);
  cce_init_and_register_handler
    (L, E_H, cce_default_error_handler_function,
     cce_resource_pointer(E),
     cce_resource_destructor(ccname_final(envelope_t)));
}


/** --------------------------------------------------------------------
 ** Initialisation and finalisation: embedded struct instances, plain constructors.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Plain constructor, explicit clean handler usage. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	B_H[1];
  ccstr_buffer_t	B[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t)(L, B, 64);
    ccstr_init_and_register_final_buffer_handler(L, B_H, B);
    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Plain constructor, explicit error handler usage. */
{
  cce_location_t	L[1];
  cce_error_handler_t	B_H[1];
  ccstr_buffer_t	B[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstr_buffer_t)(L, B, 64);
    ccstr_init_and_register_final_buffer_handler(L, B_H, B);
    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Plain constructor, plain copy constructor, explicit clean handlers usage. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	src[1], dst[1];
  cce_clean_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t)(L, src, 64);
    ccstr_init_and_register_final_buffer_handler(L, src_H, src);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);

    ccname_init(ccstr_buffer_t, copy)(L, dst, src);
    ccstr_init_and_register_final_buffer_handler(L, dst_H, dst);

    ccstructs_dumpable_dump(L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump(L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));
    cce_run_body_handlers(L);
  }
}

void
test_1_4 (cce_destination_t upper_L)
/* Plain constructor, plain copy constructor, explicit error handlers usage. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	src[1], dst[1];
  cce_error_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstr_buffer_t)(L, src, 64);
    ccstr_init_and_register_final_buffer_handler(L, src_H, src);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);

    ccname_init(ccstr_buffer_t, copy)(L, dst, src);
    ccstr_init_and_register_final_buffer_handler(L, dst_H, dst);

    ccstructs_dumpable_dump(L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump(L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_1_5 (cce_destination_t upper_L)
/* Enveloped buffer, clean handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	E_H[1];
  envelope_t		E[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(envelope_t, clean)(L, E_H, E);
    ccstr_buffer_format(L, E->B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(E->B));
    cce_run_body_handlers(L);
  }
}

void
test_1_6 (cce_destination_t upper_L)
/* Enveloped buffer, error handler. */
{
  cce_location_t	L[1];
  cce_error_handler_t	E_H[1];
  envelope_t		E[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(envelope_t, error)(L, E_H, E);
    ccstr_buffer_format(L, E->B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(E->B));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}


/** --------------------------------------------------------------------
 ** Initialisation and finalisation: embedded struct instances, guarded constructors.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Guarded initialisation, finalisation with clean handler. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t, clean)(L, B_H, B, 64);
    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Guarded initialisation, finalisation with error handler. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_error_handler_t	B_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstr_buffer_t, error)(L, B_H, B, 64);
    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_2_3 (cce_destination_t upper_L)
/* Initialisation, copy initialisation, finalisation with clean handlers. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	src[1], dst[1];
  cce_clean_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t,       clean)(L, src_H, src, 64);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);
    ccname_init(ccstr_buffer_t, copy, clean)(L, dst_H, dst, src);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));
    cce_run_body_handlers(L);
  }
}

void
test_2_4 (cce_destination_t upper_L)
/* Initialisation, copy initialisation, finalisation with error handlers. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	src[1], dst[1];
  cce_error_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccname_init(ccstr_buffer_t,       error)(L, src_H, src, 64);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);
    ccname_init(ccstr_buffer_t, copy, error)(L, dst_H, dst, src);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}


/** --------------------------------------------------------------------
 ** Construction and destruction: standalone struct instances, plain constructors.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Plain constructor, explicit clean handler usage. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t	*B = ccname_new(ccstr_buffer_t)(L, 64);
    ccstr_init_and_register_delete_buffer_handler(L, B_H, B);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_run_body_handlers(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* Plain constructor, explicit error handler usage. */
{
  cce_location_t	L[1];
  cce_error_handler_t	B_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstr_buffer_t	*B = ccname_new(ccstr_buffer_t)(L, 64);
    ccstr_init_and_register_delete_buffer_handler(L, B_H, B);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

void
test_3_3 (cce_destination_t upper_L)
{
  cce_location_t	L[1];
  cce_clean_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t	*src, *dst;

    src = ccname_new(ccstr_buffer_t)(L, 64);
    ccstr_init_and_register_delete_buffer_handler(L, src_H, src);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);

    dst = ccname_new(ccstr_buffer_t, copy)(L, src);
    ccstr_init_and_register_delete_buffer_handler(L, dst_H, dst);

    ccstructs_dumpable_dump(L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump(L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Construction and destruction: standalone struct instances, guarded constructors.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
/* Finalisation with clean handler. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t	*B = ccname_new(ccstr_buffer_t, clean)(L, B_H, 64);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_run_body_handlers(L);
  }
}

void
test_4_2 (cce_destination_t upper_L)
/* Finalisation with error handler. */
{
  cce_location_t	L[1];
  cce_error_handler_t	B_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstr_buffer_t	*B = ccname_new(ccstr_buffer_t, error)(L, B_H, 64);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_4_3 (cce_destination_t upper_L)
/* Initialisation, copy initialisation, finalisation with clean handlers. */
{
  cce_location_t	L[1];
  cce_clean_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t	*src, *dst;

    src = ccname_new(ccstr_buffer_t, clean)(L, src_H, 64);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);
    dst = ccname_new(ccstr_buffer_t, copy, clean)(L, dst_H, src);

    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));
    cce_run_body_handlers(L);
  }
}

void
test_4_4 (cce_destination_t upper_L)
/* Initialisation, copy initialisation, finalisation with error handlers. */
{
  cce_location_t	L[1];
  cce_error_handler_t	src_H[1], dst_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstr_buffer_t	*src, *dst;

    src = ccname_new(ccstr_buffer_t, error)(L, src_H, 64);
    ccstr_buffer_format(L, src, "These are the buffer's contents (%s).\n", __func__);
    dst = ccname_new(ccstr_buffer_t, copy, error)(L, dst_H, src);

    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(src));
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(dst));

    cce_raise(L, cctests_condition_new_signal_1());
  }
}


/** --------------------------------------------------------------------
 ** Buffer formatting.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
/* Test writing a string to the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t, clean)(L, B_H, B, 64);
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
test_5_2 (cce_destination_t upper_L)
/* Test writing  a string to the  buffer in a way  that causes a reallocation  of the
   buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t, clean)(L, B_H, B, 1);
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
test_5_3 (cce_destination_t upper_L)
/* Test writing multiple strings to the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t, clean)(L, B_H, B, 64);
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
test_5_4 (cce_destination_t upper_L)
/* Test writing multiple strings to the buffer in a way that causes a reallocation of
   the buffer. */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t, clean)(L, B_H, B, 1);
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
test_5_5 (cce_destination_t upper_L)
/* Test writing a buffer to a "FILE". */
{
  cce_location_t	L[1];
  ccstr_buffer_t	B[1];
  cce_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccname_init(ccstr_buffer_t, clean)(L, B_H, B, 1);
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
 ** Trait: dtor implementations.
 ** ----------------------------------------------------------------- */

void
test_6_1 (cce_destination_t upper_L)
/* Test the "dtor" trait with embedded buffers, clean handler. */
{
  cce_location_t		L[1];
  ccstr_buffer_t		B[1];
  ccstructs_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstructs_dtor_T	DB;

    ccname_init(ccstr_buffer_t)(L, B, 64);
    DB = ccname_trait_new(ccstructs_dtor_T, ccstr_buffer_t, embedded)(B);
    ccstructs_init_and_register_handler(L, B_H, DB);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_run_body_handlers(L);
  }
}

void
test_6_2 (cce_destination_t upper_L)
/* Test the "dtor" trait with embedded buffers, error handler. */
{
  cce_location_t		L[1];
  ccstr_buffer_t		B[1];
  ccstructs_error_handler_t	B_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstructs_dtor_T	DB;

    ccname_init(ccstr_buffer_t)(L, B, 64);
    DB = ccname_trait_new(ccstructs_dtor_T, ccstr_buffer_t, embedded)(B);
    ccstructs_init_and_register_handler(L, B_H, DB);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_raise(L, cctests_condition_new_signal_1());
  }
}

/* ------------------------------------------------------------------ */

void
test_6_3 (cce_destination_t upper_L)
/* Test the "dtor" trait with standalone buffers, clean handler. */
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccstr_buffer_t	*B;
    ccstructs_dtor_T	DB;

    B  = ccname_new(ccstr_buffer_t)(L, 64);
    DB = ccname_trait_new(ccstructs_dtor_T, ccstr_buffer_t, standalone)(B);
    ccstructs_init_and_register_handler(L, B_H, DB);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_run_body_handlers(L);
  }
}

void
test_6_4 (cce_destination_t upper_L)
/* Test the "dtor" trait with standalone buffers, error handler. */
{
  cce_location_t		L[1];
  ccstructs_clean_handler_t	B_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccstr_buffer_t	*B;
    ccstructs_dtor_T	DB;

    B  = ccname_new(ccstr_buffer_t)(L, 64);
    DB = ccname_trait_new(ccstructs_dtor_T, ccstr_buffer_t, standalone)(B);
    ccstructs_init_and_register_handler(L, B_H, DB);

    ccstr_buffer_format(L, B, "These are the buffer's contents (%s).\n", __func__);
    ccstructs_dumpable_dump
      (L, ccname_trait_new(ccstructs_dumpable_T, ccstr_buffer_t)(B));
    cce_raise(L, cctests_condition_new_signal_1());
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
    cctests_begin_group("initialisation and finalisation of embedded struct instances, plain constructors");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
      cctests_run(test_1_4);
      cctests_run(test_1_5);
      cctests_run(test_1_6);
    }
    cctests_end_group();

    cctests_begin_group("initialisation and finalisation of embedded struct instances, guarded constructors");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
      cctests_run(test_2_4);
    }
    cctests_end_group();

    cctests_begin_group("construction and destruction of standalone struct instances, plain constructors");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
      cctests_run(test_3_3);
    }
    cctests_end_group();

    cctests_begin_group("construction and destruction of standalone struct instances, guarded constructors");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
      cctests_run(test_4_3);
      cctests_run(test_4_4);
    }
    cctests_end_group();

    cctests_begin_group("buffer formatting");
    {
      cctests_run(test_5_1);
      cctests_run(test_5_2);
      cctests_run(test_5_3);
      cctests_run(test_5_4);
      cctests_run(test_5_5);
    }
    cctests_end_group();

    cctests_begin_group("dtor trait");
    {
      cctests_run(test_6_1);
      cctests_run(test_6_2);
      cctests_run(test_6_3);
      cctests_run(test_6_4);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
