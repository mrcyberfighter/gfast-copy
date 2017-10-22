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

#ifndef GFAST_COPY_1_0_COPY_FILES_HH
#define GFAST_COPY_1_0_COPY_FILES_HH

#include "./headers/includes.h"

#include "./headers/defines.h"

#include "./global_vars.h"

extern void apply_copy(GtkWidget *widget, GtkWidget *progressbar) ;

extern void generate_message_dialog(GtkWidget *window, const char *text, const char *secondary_text, GtkMessageType type) ;

#endif
