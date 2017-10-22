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

#ifndef GFAST_COPY_1_0_GLOBAL_VARS_HH  /** Inclusion guard **/
#define GFAST_COPY_1_0_GLOBAL_VARS_HH

#include "./headers/defines.h"
#include "./headers/includes.h"

/** Usage example: declaration of a global variable as extern in the header file (*.h). */

typedef struct {

  GtkWidget *src_button ;

  GtkWidget *dst_button ;

  GtkWidget *files_menu_button ;

  GtkWidget *rm_src_file_button ;

  GtkWidget *rm_src_file_menuitem ;

} GUI ;

typedef struct {

  gchar *src_filepath ;

  gchar *dst_filepath ;

} Files ;

typedef struct {

  bool use_light_theme ;

  bool delete_src_file ;

} Configuration ;

extern GUI *gui ;

extern Files *files ;

extern Configuration *configuration ;

#ifdef G_OS_WIN32

/** On Windows the preprocessor trick doesn't work: ./headers/defines.h **/

extern char *PREFIX ;

extern char *PATH_TO_CONF_FILE ;

extern char *PATH_TO_BUTTON_ACTION_ICON  ;

extern char *PATH_TO_BUTTON_SRC_FILE_ICON  ;

extern char *PATH_TO_BUTTON_DST_FILE_ICON  ;

extern char *PATH_TO_BUTTON_RM_FILE_ON_ICON  ;

extern char *PATH_TO_BUTTON_RM_FILE_OFF_ICON  ;



extern char *PATH_TO_MENU_BUTTON_FILES  ;

extern char *PATH_TO_MENU_SRC_FILE_ICON   ;

extern char *PATH_TO_MENU_DST_FILE_ICON  ;

extern char *PATH_TO_MENU_COPY_FILE_ICON  ;

extern char *PATH_TO_MENU_README_ICON  ;

extern char *PATH_TO_MENU_ABOUT_ICON  ;

extern char *PATH_TO_MENU_QUIT_ICON  ;

extern char *PATH_TO_MENU_BUTTON_DOC   ;

extern char *PATH_TO_MENU_BUTTON_CONFIG  ;

extern char *PATH_TO_MENU_DARK_ICON  ;

extern char *PATH_TO_MENU_LIGHT_ICON  ;

extern char *PATH_TO_MENU_RM_FILE_ICON  ;


extern char *PATH_TO_PROGRAM_ICON  ;

extern char *PATH_TO_LICENSE_TEXT  ;

extern char *PATH_TO_README ;

#endif // G_OS_WIN32

#endif /** Inclusion guard **/

