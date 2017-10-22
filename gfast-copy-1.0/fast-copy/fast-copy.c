/** ***********************************************************************************
  *                                                                                   *
  * fast-copy - a fast single chunk file copy program.                                *
  *                                                                                   *
  * Copyright (C) 2017 Brüggemann Eddie.                                              *
  *                                                                                   *
  * This file is part of gfast-copy.                                                  *
  * fast-copy is free software: you can redistribute it and/or modify                 *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * fast-copy is distributed in the hope that it will be useful,                      *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with gfast-copy. If not, see <http://www.gnu.org/licenses/>                 *
  *                                                                                   *
  *************************************************************************************/

#include "../config.h"

#if 0
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE // For getopt().
#endif
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 2 // For getopt().
#endif

/** @NOTE: glib-2.0 and gio-2.0 are used for compatibility purpose **/
#include <glib.h>
#include <glib/gstdio.h>
#include <gio/gio.h>

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

#if HAVE_SYS_IOCTL_H
/** Used for progress-bar displaying **/
#include <sys/ioctl.h>
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


#if HAVE_STDLIB_H
#include <stdlib.h>
#else
#error "No stdlib.h header file available !"
#endif

#if HAVE_STDIO_H
#include <stdio.h>
#else
#error "No stdio.h header file available !"
#endif

#if HAVE_LIMITS_H
#include <limits.h>
#else
#error "No limits.h header file available !"
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

/** To compile with command-line :
  *
  * $ cc -std=c11 -Wall -Wextra -Wpedantic -pedantic fast-copy.c `pkg-config --cflags --libs glib-2.0 gio-2.0` -o fast-copy
  *
  ***************************************************************************************************************/

static void print_help(const char *prgname) {

  char *basename = g_path_get_basename(prgname) ;

  fprintf(stdout,"%s - a fast chunk file copy program.\n\n", basename) ;
  fprintf(stdout,"Usage : %s -r input-file -w output-file [-o] [-s] [-e] [-h]\n\n", basename) ;
  fprintf(stdout,"\t-r Read from file (required).\n") ;
  fprintf(stdout,"\t-w Write to file  (required).\n") ;
  fprintf(stdout,"\t-o Overwrite destination file (optional).\n") ;
  fprintf(stdout,"\t-e Erase source file (optional).\n") ;
  fprintf(stdout,"\t-s Use syscalls instead of streams (optional only UNIX).\n") ;
  fprintf(stdout,"\t-h Print this help message.\n\n") ;
  fprintf(stdout,"- Copyright (©) 2017 Brüggemann Eddie <mrcyberfighter@gmail.com> GPLv3.\n\n") ;
  fflush(stdout) ;

  g_free(basename) ;

  return ;

}

extern int optind, opterr, optopt;

int main(int argc, char *argv[]) {

  const char usage_string[] = "Usage : %s -r input-file -w output-file [-o] [-s] [-e] [-h]\n" ;

  if (argc == 1) {

    fprintf(stderr, usage_string, argv[0]);

    exit(EXIT_FAILURE);

  }

  char *opt_src_filepath = NULL ;

  char *opt_dst_filepath = NULL ;

  bool syscalls = false ;

  bool overwrite = false ;

  bool erase_src_file = false ;

  bool have_set_src_file = false ;

  bool have_set_dst_file = false ;

  int opt ;

  while ((opt = getopt(argc, argv, "r:w:hsoe")) != -1) {

   switch (opt) {

     case 'r':

         opt_src_filepath   = optarg ;
         have_set_src_file  = true ;
         break;

     case 'w':

         opt_dst_filepath   = optarg ;
         have_set_dst_file  = true ;
         break;

     case 's' :

       syscalls = true ;
       break ;

     case 'o' :

       overwrite = true ;
       break ;

     case 'e' :

       erase_src_file = true ;
       break ;

     case 'h' :

       print_help(argv[0]) ;

       exit(EXIT_SUCCESS) ;

     case '?' :

       fprintf(stderr, usage_string, argv[0]);

       exit(EXIT_FAILURE);

     default:

       fprintf(stderr, usage_string, argv[0]);

       exit(EXIT_FAILURE);
    }

  }

  if (optind == 1) {

    fprintf(stderr, usage_string, argv[0]);

    exit(EXIT_FAILURE);

  }

  if (! have_set_src_file) {

    fprintf(stderr,"Source file not set !\nUse the -r switch to set the file to copy.\n\n") ;

    fprintf(stderr, usage_string, argv[0]);

    exit(EXIT_FAILURE) ;
  }

  if (! have_set_dst_file) {

    fprintf(stderr,"Destination file not set !\nUse the -w switch to set the destination.\n\n") ;

    fprintf(stderr, usage_string, argv[0]);

    exit(EXIT_FAILURE) ;
  }



  /** @NOTE: Minimal use of the practice @GFile* for getting the absolute path.
    *
    * Because @realpath() is an extension and so not portable !
    *
    * And some basic @GLib functionalities.
    *
    ************************************************************************/

  GFile *g_file = g_file_new_for_path(opt_src_filepath) ;

  char *src_filepath = g_file_get_path(g_file) ;

  g_object_unref(g_file) ;

  g_file = g_file_new_for_path(opt_dst_filepath) ;

  char *dst_filepath = g_file_get_path(g_file) ;

  g_object_unref(g_file) ;

  if ( g_file_test(dst_filepath, G_FILE_TEST_IS_DIR) ) {

    char *src_basename = g_path_get_basename(src_filepath) ;

    char *new_dst_filepath = g_strdup_printf("%s/%s", dst_filepath, src_basename) ;

    g_free(src_basename) ;

    g_free(dst_filepath) ;

    dst_filepath = new_dst_filepath ;

  }

  bool output_file_exists = false ;


  if (g_file_test(dst_filepath, G_FILE_TEST_EXISTS) && (! overwrite)) {

    /** Interactively ask the user if he wants to overwrite the destination file. Because it exists. **/

    if (g_file_test(dst_filepath, G_FILE_TEST_IS_REGULAR) ) {

      char *filename = g_path_get_basename(dst_filepath) ;

      fprintf(stdout,"\nOutput file : %s exist.\nOverwrite it [y|n] : ", filename) ;

      char answer = '\0' ;

      while ( ((answer = getchar()) != 'y') && (answer != 'n') ) {

        fprintf(stdout,"\nOutput file : %s exist.\nOverwrite it [y|n] : ", filename) ;

      }

      if (answer == 'n') {

        fprintf(stdout,"Don't overwrite file : %s\nWe abort !\n", filename) ;

        g_free(filename) ;

        exit(EXIT_SUCCESS) ;

      }

      g_free(filename) ;

    }
    else {

      fprintf(stderr,"output-file is not a regular file.\nWe abort !\n") ;

      exit(EXIT_FAILURE) ;

    }

  }
  else if (! g_file_test(src_filepath, G_FILE_TEST_EXISTS)) {

    fprintf(stderr,"Source file does nnot exists !\nUse the -r switch to set the file to copy.\n\n") ;

    fprintf(stderr, usage_string, argv[0]);

    exit(EXIT_FAILURE) ;
  }




  fprintf(stderr," Copy filepath  : %s\n  To  filepath  : %s\n", src_filepath, dst_filepath) ;

  GStatBuf buf ;

  if (g_stat(src_filepath, &buf) == -1) {

    perror("stat") ;

    exit(EXIT_FAILURE) ;

  }

  size_t blocksize = 4096 * 2 ;

  #ifdef G_OS_UNIX
  if (syscalls) {

    #if HAVE_STRUCT_STAT_ST_BLKSIZE
    blocksize = buf.st_blksize ;
    #else
    blocksize = 4096 * 2 ;
    #endif
  }
  else {

    blocksize = (BUFSIZ < (4096 * 2)) ? (4096 * 2) : BUFSIZ  ;
  }
  #endif

  #ifdef G_OS_WIN32

  blocksize = (BUFSIZ < (4096 * 2)) ? (4096 * 2) : BUFSIZ  ;

  #endif

  size_t sizeof_file = buf.st_size ;

  mode_t mode = buf.st_mode ;

  // Check how to display file-size:
  if (sizeof_file <= 1024) {

    fprintf(stdout," File size      : %zu\n", sizeof_file) ;

  }
  else if (sizeof_file > 1024 && sizeof_file <= 1024 * 1024) {

    fprintf(stdout," File size      : %zu Kio\n", sizeof_file / 1024) ;

  }
  else if (sizeof_file > 1024 * 1024 && sizeof_file <= 1024 * 1024 * 1024) {

    fprintf(stdout," File size      : %zu Mio\n", sizeof_file / 1024 / 1024) ;

  }
  else {

    fprintf(stdout," File size      : %zu Gio\n", sizeof_file / 1024 / 1024 / 1024) ;

  }

  if (sizeof_file == 0) {

    g_creat(dst_filepath, mode) ;

    exit(EXIT_SUCCESS) ;
  }

  #ifdef G_OS_UNIX

  int fd_r = -1 ;

  int fd_w = -1 ;

  FILE *fp_r  = NULL ;

  FILE *fp_w = NULL ;

  if (syscalls) {

    /** @NOTE: The syscall(s) are more cache efficient but they are not portable !
     *
     ******************************************************************************/

    errno = 0 ;

    fd_r = g_open(src_filepath, O_RDONLY) ;

    free(src_filepath) ;

    if (fd_r < 0) {

      fprintf(stderr,"%s",  g_strerror(errno)) ;

      exit(EXIT_FAILURE) ;

    }

    int flags = O_WRONLY   ;

    if (! output_file_exists) {

      flags |= O_CREAT ;

    }
    else {

      flags |= O_CREAT | O_TRUNC  ;

    }

    errno = 0 ;

    fd_w = g_open(dst_filepath, flags, mode) ;

    free(dst_filepath) ;

    if (fd_w < 0) {

      fprintf(stderr,"%s",  g_strerror(errno)) ;

      exit(EXIT_FAILURE) ;

    }

  }
  else {

    errno = 0 ;

    fp_r = g_fopen(src_filepath, "rb") ;

    if (fp_r == NULL) {

      fprintf(stderr,"%s",  g_strerror(errno)) ;

      g_free(src_filepath) ;

      g_free(dst_filepath) ;

      exit(EXIT_FAILURE) ;

    }

    errno = 0 ;

    fp_w = g_fopen(dst_filepath, "wb") ;

    if (fp_w == NULL) {

      fprintf(stderr,"%s",  g_strerror(errno)) ;

      fclose(fp_w) ;

      g_free(src_filepath) ;

      g_free(dst_filepath) ;

      exit(EXIT_FAILURE) ;

    }

  }
  #endif

  #ifdef G_OS_WIN32

  // Windows only support FILE * pointers at my site.

  int fd_r = -1 ;

  int fd_w = -1 ;

  errno = 0 ;

  FILE *fp_r  = g_fopen(src_filepath, "rb") ;

  if (fp_r == NULL) {

    fprintf(stderr,"%s",  g_strerror(errno)) ;

    g_free(src_filepath) ;

    g_free(dst_filepath) ;

    exit(EXIT_FAILURE) ;

  }

  errno = 0 ;

  FILE *fp_w =  g_fopen(dst_filepath, "wb") ;

  if (fp_w == NULL) {

    fprintf(stderr,"%s",  g_strerror(errno)) ;

    fclose(fp_r) ;

    g_free(src_filepath) ;

    g_free(dst_filepath) ;

    exit(EXIT_FAILURE) ;

  }

  #endif

  ssize_t ret = -1 ;

  char *buffer[blocksize] ;

  bool have_progressbar = false ;

  #ifdef HAVE_SYS_IOCTL_H
  #if HAVE_SYS_IOCTL_H
  // @NOTE: Must check if a progressbar is needed:
  have_progressbar = (sizeof_file > (blocksize * 8 * 16 * 16)) ;
  #endif
  #endif

  double progressbar_unit = 0 ;

  #ifdef HAVE_SYS_IOCTL_H
  #if HAVE_SYS_IOCTL_H
  // @NOTE: winsize[0] and winsize[1] character size winsize[2] and winsize[3] size in pixels.
  short winsize[4] ;
  ioctl(0,TIOCGWINSZ,&winsize) ;

  if (have_progressbar) {

    // Compute a progressbar unit number according the current terminal width.
    progressbar_unit = sizeof_file / (winsize[1]-2) ;

  }
  #endif
  #endif

  if (have_progressbar) {

    fprintf(stdout,"[") ;
    fflush(stdout) ;

  }

  uint16_t nb_of_progressbar_units = 1 ;

  size_t cur_offset = 0 ;


  if (syscalls) {

    // This can only happend on UNIX systems.

    while ((ret = read(fd_r, buffer,  blocksize)) > 0) {

      #ifdef DEBUG
      fprintf(stdout,"read %zu bytes\n", ret) ;
      #endif

      cur_offset += write(fd_w, buffer, ret) ;

      if (have_progressbar) {

        double cur_pos = cur_offset  ;

        if (cur_pos >= progressbar_unit * nb_of_progressbar_units) {

          /** We only set a progressbar unit when needed !
            *
            * If the current offset is bigger than progressbar units.
            *
            * We make no ioctl() call for getting the current
            * terminal size for the sake of efficienz.
            *
            * So if the user change the terminal size
            * the progressbar won't be adjusted.
            *
            *******************************************************/

          fprintf(stdout,"#") ; // Add a unit.
          fflush(stdout) ;      // Mustbe done even if it's expensive.

          ++nb_of_progressbar_units ; // Increment for the next turn.

        }
      }
    }
  }
  else {

    while ((ret = fread(buffer,  sizeof(gchar), blocksize, fp_r)) > 0) {

      cur_offset += fwrite(buffer, sizeof(gchar), ret, fp_w) ;

      if (have_progressbar) {

        double cur_pos = cur_offset  ;

        if (cur_pos >= progressbar_unit * nb_of_progressbar_units) {

          /** We only set a progressbar unit when needed !
            *
            * If the current offset is bigger than progressbar units.
            *
            * We make no ioctl() call for getting the current
            * terminal size for the sake of efficienz.
            *
            * So if the user change the terminal size
            * the progressbar won't be adjusted.
            *
            *******************************************************/

          fprintf(stdout,"#") ; // Add a unit.

          fflush(stdout) ; // Must be done even if it is expensive.

          ++nb_of_progressbar_units ; // Increment for the next turn.

        }
      }

    }

  }

  if (have_progressbar) {

    fprintf(stdout,"]\n") ;

  }


  fprintf(stdout," Please wait    : Synchronize file-system...\n") ;
  fflush(stdout) ;


  // Clean up and synchronize file-system:
  if (syscalls) {

    close(fd_r) ;

    #ifdef G_OS_UNIX
    fsync(fd_w) ;
    #endif

    close(fd_w) ;
  }
  else {


    fclose(fp_r) ;

    fflush(fp_w) ;

    fclose(fp_w) ;

  }


  // Erase source file if wanted.
  if (erase_src_file) {

    errno = 0 ;

    if (g_remove(src_filepath)) {

      // Removing has failed:
      fprintf(stderr,"%s", g_strerror(errno)) ;

      free(src_filepath) ;

      free(dst_filepath) ;

      exit(EXIT_FAILURE) ;

    }

  }

  free(src_filepath) ;
  free(dst_filepath) ;

  exit(EXIT_SUCCESS) ;

}

