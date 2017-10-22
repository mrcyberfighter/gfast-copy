#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([gfast-copy], [1.0], [mrcyberfighter@gmail.com], , [http://www.open-source-projects.net/gfast-copy/gfast-copy])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])

AC_LANG([C])

# Checks for programs.
AC_COPYRIGHT([GPLv3])

# Enable the -Ofast switch.
: ${CFLAGS="-g -Ofast"}

# COMPILER M4.
AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_CC_STDC
AC_PROG_CC_C99
AC_C_CONST

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_EXEEXT

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Checks the host.
case $host_os in

  *mingw*)
    platform_win32=yes
    native_win32=yes
    platform_linux=no
    platform_darwin=no
    ;;

  *linux-gnu*)
    platform_linux=yes
    platform_win32=no
    native_win32=no
     platform_darwin=no
    ;;

  pw32* | *cygwin*)
    # Case not work at my site.
    platform_win32=yes
    native_win32=no
    platform_linux=no
    platform_darwin=no
    ;;

  *darwin*)
    platform_darwin=yes
    platform_linux=no
    platform_win32=no
    native_win32=no
    ;;

esac

AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")
AM_CONDITIONAL(PLATFORM_LINUX, test x"$platform_linux" = "xyes")
AM_CONDITIONAL(PLATFORM_DARWIN, test x"$platform_darwin" = "xyes")


# Checks for programs.
# POSIX programs detection.
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LN_S
#AC_PROG_SED

# coreutils package
AC_PATH_PROG([CHMOD],       [chmod],      [no])
AC_PATH_PROG([RM],          [rm],         [no])
AC_PATH_PROG([MV],          [mv],         [no])
AC_PATH_PROG([CP],          [cp],         [no])
AC_PATH_PROG([UNLINK],      [unlink],     [no])
AC_PATH_PROG([RMDIR],       [rmdir],      [no])
AC_PATH_PROG([TOUCH],       [touch],      [no])

AC_PATH_PROG([MD5SUM],      [md5sum],      [no])
AC_PATH_PROG([SHA1SUM],     [sha1sum],     [no])
AC_PATH_PROG([SHA256SUM],   [sha256sum],   [no])
AC_PATH_PROG([SHA512SUM],   [sha512sum],   [no])


AM_CONDITIONAL(HAVE_MD5, test ! x"$MD5SUM" = "xno")
AM_CONDITIONAL(HAVE_SHA1, test ! x"$SHA1SUM" = "xno")
AM_CONDITIONAL(HAVE_SHA256, test ! x"$SHA256SUM" = "xno")
AM_CONDITIONAL(HAVE_SHA512, test ! x"$SHA512SUM" = "xno")


if test x"$CHMOD" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (chmod is missing) !, 1)

fi


if test x"$RM" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (rm is missing) !, 1)

fi


if test x"$MV" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (mv is missing) !, 1)

fi

if test x"$UNLINK" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (unlink is missing) !, 1)

fi

if test x"$RMDIR" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (rmdir is missing) !, 1)

fi

if test x"$TOUCH" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (touch is missing) !, 1)

fi


# desktop-file-utils package:
AC_PATH_PROG([UPDATE_DESKTOP_DATABASE],  [update-desktop-database],   [no])
AC_PATH_PROG([DESKTOP_FILE_INSTALL],     [desktop-file-install],      [no])
# xdg-utils package:
AC_PATH_PROG([XDG_DESKTOP_MENU],         [xdg-desktop-menu],          [no])


if test x"$DESKTOP_FILE_INSTALL" = xno ; then
if test x"$XDG_DESKTOP_MENU" = xno ; then

  AC_MSG_WARN(Install either the xdg-utils or desktop-file-utils package !)

  AC_MSG_WARN(This is not absolutely required.)

  AC_MSG_WARN(But recommand to install desktop files.)

fi
fi

destop_file_utils=no

if test x"$DESKTOP_FILE_INSTALL" = xno ; then

  AC_MSG_NOTICE(The desktop-file-install tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The desktop-file-install tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

else

desktop_file_utils=yes

fi

xdg_utils=no

if test x"$XDG_DESKTOP_MENU" = xno ; then

  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

else

xdg_utils=yes

update_desktop_database=no ;

fi

if test x"$UPDATE_DESKTOP_DATABASE" = xno ; then

  AC_MSG_NOTICE(This desktop-file-install tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

fi

AM_CONDITIONAL(UPDATE_DESKTOP_DATABASE_UTILS, test x"$destop_file_utils" = "xyes")
AM_CONDITIONAL(DESTOP_FILE_UTILS, test x"$destop_file_utils" = "xyes")
AM_CONDITIONAL(XDG_UTILS,         test x"$xdg_utils" = "xyes")

# install-info check.
AC_PATH_PROG([INSTALL_INFO],         [install-info],          [no])

#######################################################################
# I try to separate the graphical from the command-line tool so that  #
# You can install either one or the other but I fail.                 #
# Because basing the separation on the strings yes and no confuse me. #
# And to much amount of work for the others formats I can not sorry.  #
#######################################################################
#
# AC_ARG_ENABLE([gfast-copy], [AS_HELP_STRING([--disable-graphical-tool], [disable the gfast-copy program.]) ], [ fast_copy=no],  [ fast_copy=yes])
# AC_ARG_ENABLE([fast-copy],  [AS_HELP_STRING([--disable-cmdline-tool],   [disable the  fast-copy program.]) ], [ gfast_copy=no], [gfast_copy=yes])
# AM_CONDITIONAL(GFAST_COPY, test x"$gfast_copy" = "xyes")
# AM_CONDITIONAL(FAST_COPY, test x"$fast_copy" = "xyes")
#
#######################################################################
#                                                                     #
# The using the GFAST_COPY and FAST_COPY boolean values to separate   #
# the building of the 2 programs.                                     #
#                                                                     #
#######################################################################

# if test x"$gfast_copy" = xyes ; then

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-3.0], [ ], AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ****************** GTK 3 library required for gfast-copy ***************
   Install the GTK 3 library from your package manager or from source.

   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

# fi

# if test x"$fast_copy" = xyes ; then

# Checks for libraries.
PKG_CHECK_MODULES([GLIB], [glib-2.0], [   ], AC_MSG_ERROR(   glib-2.0 library not detected !!!

   ****************** GLIB library required for fast-copy ***************
   Install the GLIB library from your package manager or from source.

   WARNING: Take care to install the development files from glib-2.0 !!!
            Often call: libglib2.0-dev or libglib2.0-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

PKG_CHECK_MODULES([GIO], [gio-2.0], [  ], AC_MSG_ERROR(   gio-2.0 library not detected !!!

 ******************* GIO library required for fast-copy ***************
 Install the GIO library from your package manager or from source.

 WARNING: Take care to install the development files from gio-2.0 !!!
          Their is no package named libgio-2-dev !
          So it depends surely from libglib-2-dev ?

 Then retry to launch the ./configure script...
 ************************************************************************
 , 1))

# fi

if test x"$platform_darwin" = xyes ; then

  PKG_CHECK_MODULES([GTK_MAC_INTEGRATION], [gtk-mac-integration-gtk3], [], AC_MSG_ERROR(   gtk-mac-integration-gtk3 library not detected !!!

   ****** gtk-mac-integration-gtk3 library required for gfast-copy ********

   Install the gtk-mac-integration-gtk3 library.

   You can easily get it through the package manager brew on Mac OSX.

   $ brew install gtk-mac-integration

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

  PKG_CHECK_MODULES([GTK_QUARTZ], [gdk-quartz-3.0], [], AC_MSG_ERROR(   gdk-quartz-3.0 library not detected !!!

   ******** gdk-quartz-3.0 library required for it-edit *******************

   Install the gdk-quartz-3.0 library.

   You can easily get it through the package manager brew on Mac OSX.

   $ brew install gtk+3 # gdk-quartz-3.0 depends from gtk+3

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

fi



# Checks for header files.
AC_CHECK_HEADERS([fcntl.h libintl.h limits.h stdint.h stdlib.h string.h unistd.h stdio.h libgen.h sys/types.h sys/stat.h sys/ioctl.h unistd.h errno.h stdbool.h])



# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])

# Checks for library functions.
AC_CHECK_FUNCS([putenv setlocale])



AC_CONFIG_FILES([Makefile
                 src/Makefile
                 fast-copy/Makefile
                 data/Makefile
                 man_fast-copy/Makefile
                 man_gfast-copy/Makefile
                 texi/Makefile
                 desktop/Makefile
                 doc/Makefile
                 MACOSX/Makefile])
           
AC_MSG_NOTICE(System check OK !!!)

AC_OUTPUT

if test x"$platform_linux" = "xyes" ; then

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} an easy to use graphical fast copy tool for big files.

  Package dependencies: gtk+-3.

  Host:     ${host}
  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ gfast-copy [filepath]
  or from your desktop menu, the file manager: \"open with\" option works fine.

  You can use the command-line tool too:
  $ fast-copy -r src-file -w destination
"

elif test x"$platform_win32" = "xyes" ; then

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} an easy to use graphical fast copy tool for big files.

  Package dependencies: gtk+-3.

  Host:     ${host}
  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ gfast-copy [filepath]
  or from your desktop menu, the file manager: \"open with\" option works fine.

  You can use the command-line tool too:
  $ fast-copy -r src-file -w destination
"


elif test x"$platform_darwin" = "xyes" ; then

echo "
************************** ${PACKAGE_STRING} ************************

${PACKAGE_NAME} an easy to use graphical fast copy tool for big files.

Package dependencies: gtk+-3.

Host:     ${host}
  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ gfast-copy [filepath]
  or from your desktop menu, the file manager: \"open with\" option works fine.

  You can use the command-line tool too:
  $ fast-copy -r src-file -w destination
"

else

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} an easy to use graphical fast copy tool for big files.

  Package dependencies: gtk+-3.

  Host:     ${host}
  Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ gfast-copy [filepath]
  or from your desktop menu, the file manager: \"open with\" option works fine.

  You can use the command-line tool too:
  $ fast-copy -r src-file -w destination
"

fi
