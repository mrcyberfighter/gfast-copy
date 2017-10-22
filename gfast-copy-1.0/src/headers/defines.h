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

#ifndef GFAST_COPY_1_0_DEFINES_HH /** Inclusion guard **/
#define GFAST_COPY_1_0_DEFINES_HH

#include "./includes.h"

/** About definition: **/
#define AUTHOR      "Brüggeman Eddie"
#define MAIL        "<mrcyberfighter@gmail.com>"

#ifdef PACKAGE
#define PRGNAME     PACKAGE
#else
#define PRGNAME     "gfast-copy"
#endif

#define VERSION     "1.0"
#define LICENSE     "gpl"
#define PRGWEBURL   "http://www.open-source-projects.net/splash/splash"
#define COPYRIGHT   "Copyright (C) 2017 Brüggeman Eddie GPLv3"



#ifdef G_OS_UNIX

/** Conditional Prefix definition. **/
#ifndef PREFIX
#define ROOT
#define PREFIX ".."

/** You can define PREFIX by distributing with a preprocessor directive:
  *
  * $(MAKE) -B CPPFLAGS="-D'PREFIX=\"$(prefix)\"'"
  *
  ***********************************************************************/

#endif


/** Path definitions: **/
#ifdef ROOT
#define DATADIR                 PREFIX  "/share/" PRGNAME
#else
#define DATADIR                 PREFIX "/share/"  PRGNAME
#endif


#define PATH_TO_CONF_FILE               DATADIR "/config" "/gfast-copy-config.ini"


#define PATH_TO_ICONS                   DATADIR "/images" "/icons"

#define PATH_TO_BUTTON_ICONS            PATH_TO_ICONS "/22x22"

#define PATH_TO_BUTTON_ACTION_ICON      PATH_TO_BUTTON_ICONS "/folder-sync.png"

#define PATH_TO_BUTTON_SRC_FILE_ICON    PATH_TO_BUTTON_ICONS "/folder-new.png"

#define PATH_TO_BUTTON_DST_FILE_ICON    PATH_TO_BUTTON_ICONS "/folder-downloads.png"

#define PATH_TO_BUTTON_RM_FILE_ON_ICON  PATH_TO_BUTTON_ICONS "/folder-important.png"

#define PATH_TO_BUTTON_RM_FILE_OFF_ICON PATH_TO_BUTTON_ICONS "/folder-temp.png"



#define PATH_TO_MENU_ICONS              PATH_TO_ICONS "/16x16"

#define PATH_TO_MENU_BUTTON_FILES       PATH_TO_MENU_ICONS "/folder-development.png"

#define PATH_TO_MENU_SRC_FILE_ICON      PATH_TO_MENU_ICONS "/folder-new.png"

#define PATH_TO_MENU_DST_FILE_ICON      PATH_TO_MENU_ICONS "/folder-downloads.png"

#define PATH_TO_MENU_COPY_FILE_ICON     PATH_TO_MENU_ICONS "/folder-sync.png"

#define PATH_TO_MENU_README_ICON        PATH_TO_MENU_ICONS "/system-help.png"

#define PATH_TO_MENU_ABOUT_ICON         PATH_TO_MENU_ICONS "/help-about.png"

#define PATH_TO_MENU_QUIT_ICON          PATH_TO_MENU_ICONS "/application-exit.png"

#define PATH_TO_MENU_BUTTON_DOC         PATH_TO_MENU_ICONS "/help-contents.png"


#define PATH_TO_MENU_BUTTON_CONFIG      PATH_TO_MENU_ICONS "/run-build-configure.png"

#define PATH_TO_MENU_DARK_ICON          PATH_TO_MENU_ICONS "/preferences-theme-dark.png"

#define PATH_TO_MENU_LIGHT_ICON         PATH_TO_MENU_ICONS "/preferences-theme-light.png"

#define PATH_TO_MENU_RM_FILE_ICON       PATH_TO_MENU_ICONS "/folder-locked.png"


#define PATH_TO_PROGRAM_ICON            DATADIR "/images" "/gfast-copy_icon.png"

#define PATH_TO_LICENSE_TEXT            DATADIR "/license" "/gpl.txt"


#define PATH_TO_README                  DATADIR "/README"  "/html" "/index.html"

/** Example definition based on DATADIR and so PREFIX
  *
  * #define PATH_TO_ICON            DATADIR "/icons/prgname.png"
  *
  *
  * @Info: You don't have a make a define for every file:
  *        simply concatenate the define and the differents filenames.
  *
  * #define PATH_TO_MENU_ICON       DATADIR "/icons/16x16"
  *
  * #define PATH_TO_BUTTON_ICON     DATADIR "/icons/24x24"
  *
  *
  * #define PATH_TO_README          DATADIR "/README"
  *
  * #define PATH_TO_LICENSE_TEXT    DATADIR "/license/" LICENSE ".txt"
  *
  * #define PATH_TO_LICENSE_HTML    DATADIR "/license/" LICENSE ".html"
  *
  **********************************************************************/

#endif // G_OS_UNIX



/** Uncomment to use gettext **/
#define GETTEXT_SUPPORT

#ifdef GETTEXT_SUPPORT
#include <libintl.h>

#ifdef ROOT

#ifdef  PACKAGE
#undef  PACKAGE
#endif

#ifndef PACKAGE
#define PACKAGE    "./"   PRGNAME
#endif



#ifdef  LOCALEDIR
#undef  LOCALEDIR
#endif

#else

#ifndef PACKAGE
#define PACKAGE  PREFIX "/bin" "/" PRGNAME
#endif


#endif /* ROOT */

#define LOCALEDIR  PREFIX "/share" "/locale"

#define _(String) gettext       (String)
#define gettext_noop(String)     String
#define N_(String) gettext_noop (String)

#endif /* GETTEXT_SUPPORT */


#define SOURCE_BUTTON_LABEL     _("       Source    ")

#define DEST_BUTTON_LABEL       _("  Destination  ")

#define SOURCE_MENU_LABEL       _("  Set source file  ")

#define DEST_MENU_LABEL         _("  Set destination file  ")


/** Uncomment to use debug features or use the target: make ddebug
#define DEBUG */

#ifdef DEBUG

#include <stdio.h>

#define DEBUG_PT          fprintf(stderr,"\n%s:%s(...) at line: %d\n", __FILE__, __func__, __LINE__) ;
#define DEBUG_FUNC_MARK   fprintf(stderr,"\n%s:%s(...) called\n",__FILE__, __func__) ;

#define DEBUG_INT(x)      fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;
#define DEBUG_LINT(x)     fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;
#define DEBUG_LLINT(x)    fprintf(stderr,"DEBUG PT N° %d\n",   (x)) ;

#define DEBUG_FLOAT(x)    fprintf(stderr,"DEBUG PT N° %f\n",   (x)) ;
#define DEBUG_DOUBLE(x)   fprintf(stderr,"DEBUG PT N° %lf\n",  (x)) ;
#define DEBUG_LDOUBLE(x)  fprintf(stderr,"DEBUG PT N° %llf\n", (x)) ;

#define DEBUG_STR(str)    fprintf(stderr,"%s\n", (str)) ;
#define DEBUG_PTR(ptr)    fprintf(stderr,"%p\n", (ptr)) ;


/** Extended DEBUGGING **/
#define EDEBUG_INT(str, x)      fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LINT(str, x)     fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LLINT(str, x)    fprintf(stderr,"%s(line:%d): %s %d\n",   __func__, __LINE__, (str), (x)) ;

#define EDEBUG_FLOAT(str, x)    fprintf(stderr,"%s(line:%d): %s %f\n",   __func__, __LINE__, (str), (x)) ;
#define EDEBUG_DOUBLE(str, x)   fprintf(stderr,"%s(line:%d): %s %lf\n",  __func__, __LINE__, (str), (x)) ;
#define EDEBUG_LDOUBLE(str, x)  fprintf(stderr,"%s(line:%d): %s %llf\n", __func__, __LINE__, (str), (x)) ;

#define EDEBUG_STR(str)         fprintf(stderr,"%s(%d): %s\n", __func__, __LINE__, (str)) ;
#define EDEBUG_PTR(ptr)         fprintf(stderr,"%s(%d): %p\n", __func__, __LINE__, (ptr)) ;

#endif




#endif /** Inclusion guard **/
