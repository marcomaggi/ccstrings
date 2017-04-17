/*
  Part of: CCStrings
  Contents: test for version functions
  Date: Apr 17, 2017

  Abstract

	Test file for version functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ccstrings.h>

int
main (int argc CCS_UNUSED, const char *const argv[] CCS_UNUSED)
{
  printf("version number string: %s\n", ccs_version_string());
  printf("libtool version number: %d:%d:%d\n",
	 ccs_version_interface_current(),
	 ccs_version_interface_revision(),
	 ccs_version_interface_age());
  exit(EXIT_SUCCESS);
}

/* end of file */
