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

#include "global_vars.h"

GUI *gui = NULL ;

Files *files = NULL ;

Configuration *configuration = NULL ;

#ifdef G_OS_WIN32

/** On Windows the preprocessor trick doesn't work: ./headers/defines.h **/

char *PREFIX = NULL ;

char *PATH_TO_CONF_FILE = NULL ;

char *PATH_TO_BUTTON_ACTION_ICON = NULL ;

char *PATH_TO_BUTTON_SRC_FILE_ICON = NULL ;

char *PATH_TO_BUTTON_DST_FILE_ICON = NULL ;

char *PATH_TO_BUTTON_RM_FILE_ON_ICON = NULL ;

char *PATH_TO_BUTTON_RM_FILE_OFF_ICON = NULL ;



char *PATH_TO_MENU_BUTTON_FILES = NULL ;

char *PATH_TO_MENU_SRC_FILE_ICON = NULL ;

char *PATH_TO_MENU_DST_FILE_ICON = NULL ;

char *PATH_TO_MENU_COPY_FILE_ICON = NULL ;

char *PATH_TO_MENU_README_ICON = NULL ;

char *PATH_TO_MENU_ABOUT_ICON = NULL ;

char *PATH_TO_MENU_QUIT_ICON = NULL ;

char *PATH_TO_MENU_BUTTON_DOC = NULL ;

char *PATH_TO_MENU_BUTTON_CONFIG = NULL ;

char *PATH_TO_MENU_DARK_ICON  = NULL ;

char *PATH_TO_MENU_LIGHT_ICON = NULL ;

char *PATH_TO_MENU_RM_FILE_ICON = NULL ;


char *PATH_TO_PROGRAM_ICON = NULL ;

char *PATH_TO_LICENSE_TEXT = NULL ;

char *PATH_TO_README ;

#endif // G_OS_WIN32

