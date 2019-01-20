/*
  Part of: CCStrings
  Contents: version functions
  Date: Thu Mar  1, 2012

  Abstract



  Copyright (C) 2017, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser General  Public
  License     along    with     this    program.      If    not,     see
  <http://www.gnu.org/licenses/>.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccstrings-internals.h"


char const *
ccstr_version_string (void)
{
  return ccstrings_VERSION_INTERFACE_STRING;
}
int
ccstr_version_interface_current (void)
{
  return ccstrings_VERSION_INTERFACE_CURRENT;
}
int
ccstr_version_interface_revision (void)
{
  return ccstrings_VERSION_INTERFACE_REVISION;
}
int
ccstr_version_interface_age (void)
{
  return ccstrings_VERSION_INTERFACE_AGE;
}

/* end of file */
