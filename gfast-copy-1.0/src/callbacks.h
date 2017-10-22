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

#ifndef GFAST_COPY_1_0_CALLBACKS_HH
#define GFAST_COPY_1_0_CALLBACKS_HH

#include "./headers/includes.h"

#include "./headers/defines.h"

#include "./global_vars.h"

#include "./GtkSmartMenuItem.h"

#include "./GtkSmartIconButton.h"

extern void filepath_dialog(GtkWidget *widget, gchar **filepath) ;

extern void set_theme(GtkWidget *widget, const gchar *variant) ;

extern void switch_delete_src_file_button(GtkWidget *widget) ;

extern void switch_delete_src_file_menuitem(GtkWidget *widget) ;

#endif
