/** ***********************************************************************************
  *                                                                                   *
  * gfast-copy an easy to use graphical fast copy tool for big files.                 *
  *                                                                                   *
  * Copyright (C) 2017 Brüggemann Eddie.                                              *
  *                                                                                   *
  * This file is part of gfast-copy.                                                  *
  * gfast-copy is free software: you can redistribute it and/or modify                *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * gfast-copy is distributed in the hope that it will be useful,                     *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with gfast-copy. If not, see <http://www.gnu.org/licenses/>                 *
  *                                                                                   *
  *************************************************************************************/

#ifndef GFAST_COPY_1_0_INCLUDE_HH
#define GFAST_COPY_1_0_INCLUDE_HH

#include "../config.h"

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>

#if HAVE_STDIO_H
#include <stdio.h>
#else
#error "No stdio.h header file available !"
#endif


#if HAVE_LIBGEN_H
#include <libgen.h>
#else
#error "No libgen.h header file available !"
#endif

#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#else
#error "No sys/types.h header file available !"
#endif

#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#else
#error "No sys/stat.h header file available !"
#endif

#if HAVE_FCNTL_H
#include <fcntl.h>
#else
#error "No fcntl.h header file available !"
#endif

#if HAVE_UNISTD_H
#include <unistd.h>
#else
#error "No unistd.h header file available !"
#endif

#if HAVE_LIMITS_H
#include <limits.h>
#else
#error "No limits.h header file available !"
#endif

#if HAVE_STDLIB_H
#include <stdlib.h>
#else
#error "No stdlib.h header file available !"
#endif

#if HAVE_STRING_H
#include <string.h>
#else
#error "No string.h header file available !"
#endif

#if HAVE_ERRNO_H
#include <errno.h>
#else
#error "No errno.h header file available !"
#endif

#if HAVE_STDINT_H
#include <stdint.h>
#else
#error "No stdint.h header file available !"
#endif

#if HAVE_STDBOOL_H
#include <stdbool.h>
#else
#error "No stdbool.h header file available !"
#endif

#ifdef __APPLE__
// For Mac OSX menu and dock support.
#include <gtkmacintegration/gtkosxapplication.h>
#endif


#endif

