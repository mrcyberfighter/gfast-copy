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

#include "./copy_files.h"

static void error_message(GtkWidget *window, const gchar *primary_text, const gchar *secondary_text) ;

static void free_filepathes(gchar *src_filepath, gchar *dst_filepath) ;

static void src_file_empty(GtkWidget *widget, GtkWidget *progressbar) ;

static void reset_button_labels(GtkWidget *src_button, GtkWidget *dst_button) ;

static void on_copy_success(GtkWidget *widget, GtkWidget *progressbar, Files *files);

static void update_gui(void) ;

void generate_message_dialog(GtkWidget *window, const char *text, const char *secondary_text, GtkMessageType type) {

  GtkWidget *message_dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                     GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_USE_HEADER_BAR,
                                                     type, GTK_BUTTONS_OK, text, NULL) ;


  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(message_dialog),  "%s", secondary_text) ;

  gtk_dialog_run(GTK_DIALOG(message_dialog)) ;

  gtk_widget_destroy(message_dialog) ;

}

static inline void error_message(GtkWidget *window, const gchar *primary_text, const gchar *secondary_text) {

  generate_message_dialog(window, primary_text, secondary_text,  GTK_MESSAGE_ERROR) ;

  return ;

}

static inline void free_filepathes(gchar *src_filepath, gchar *dst_filepath) {

  g_free(src_filepath) ;

  g_free(dst_filepath) ;

  files->src_filepath = NULL ;
  files->dst_filepath = NULL ;

  return ;

}

static inline void on_copy_success(GtkWidget *widget, GtkWidget *progressbar, Files *files) {

  gchar *text_secondary = g_strdup_printf( _("File: %s\ncopy to: %s\n"), files->src_filepath, files->dst_filepath) ;

  generate_message_dialog(gtk_widget_get_toplevel(widget), _("Copy file success !!!") , text_secondary, GTK_MESSAGE_INFO) ;

  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), 0.0) ;

  reset_button_labels(gui->src_button, gui->dst_button) ;

  return ;
}

static void reset_button_labels(GtkWidget *src_button, GtkWidget *dst_button) {

  GtkWidget *image_src_button = gtk_image_new_from_file(PATH_TO_BUTTON_SRC_FILE_ICON) ;

  gtk_button_set_image(GTK_BUTTON(src_button), image_src_button) ;

  gtk_button_set_label(GTK_BUTTON(src_button), SOURCE_BUTTON_LABEL) ;


  GtkWidget *image_dst_button = gtk_image_new_from_file(PATH_TO_BUTTON_DST_FILE_ICON) ;

  gtk_button_set_image(GTK_BUTTON(dst_button), image_dst_button) ;

  gtk_button_set_label(GTK_BUTTON(dst_button), DEST_BUTTON_LABEL) ;

  return ;

}

static inline void update_gui(void) {

  while (g_main_context_pending(NULL)) {

    g_main_context_iteration(NULL, FALSE) ;

  }

  return ;
}

static void src_file_empty(GtkWidget *widget, GtkWidget *progressbar) {

  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), 1.0) ;

  update_gui() ;

  on_copy_success(widget, progressbar, files) ;

  free_filepathes(files->src_filepath, files->dst_filepath) ;

  reset_button_labels(gui->src_button, gui->dst_button) ;

  return ;

}

void apply_copy(GtkWidget *widget, GtkWidget *progressbar) {

  GtkWidget *window = gtk_widget_get_toplevel(widget) ;

  if (files->src_filepath == NULL) {

    error_message(window,  _("Source file not specified !"), _("Use the \"Source\" button to choose a file to copy.")) ;

    return ;
  }

  if (files->dst_filepath == NULL) {

    error_message(window, _("Destination file not specified !"), _("Use the \"Destination\" button to choose the copy location.")) ;

    return ;
  }

  GStatBuf buf ;

  errno = 0 ;

  if (g_stat(files->src_filepath, &buf) == -1) {

    #ifdef DEBUG
    perror("stat") ;
    #endif

    generate_message_dialog(window, _("Error source file:"),  g_strerror(errno), GTK_MESSAGE_ERROR) ;

    free_filepathes(files->src_filepath, files->dst_filepath) ;

    reset_button_labels(gui->src_button, gui->dst_button) ;

    return ;
  }

  #if HAVE_STRUCT_STAT_ST_BLKSIZE
  // bug.st_blksize is the best size for buffer for this file
  size_t blocksize = buf.st_blksize ;
  #else
  #ifdef BUFSIZ
  size_t blocksize = (BUFSIZ < (4096 * 2)) ? (4096 * 2) : BUFSIZ ;
  #else
  size_t blocksize = (4096 * 2)
  #endif
  #endif




  size_t sizeof_file = buf.st_size ;

  mode_t mode = buf.st_mode ;

  if (sizeof_file == 0) {

    creat(files->dst_filepath, mode) ;

    src_file_empty(widget, progressbar) ;

    return ;

  }

  errno = 0 ;

  FILE *fp_r  = g_fopen(files->src_filepath, "r") ;

  if (fp_r == NULL) {

    generate_message_dialog(window, _("Error source file:"),  g_strerror(errno), GTK_MESSAGE_ERROR) ;

    free_filepathes(files->src_filepath, files->dst_filepath) ;

    reset_button_labels(gui->src_button, gui->dst_button) ;

    return ;

  }

  errno = 0 ;

  FILE *fp_w =  g_fopen(files->dst_filepath, "w") ;

  if (fp_w == NULL) {

    generate_message_dialog(window, _("Error destination file:"),  g_strerror(errno), GTK_MESSAGE_ERROR) ;

    free_filepathes(files->src_filepath, files->dst_filepath) ;

    return ;

  }

  double scrollbar_unit = 1.0 / sizeof_file ;

  size_t cur_offset = 0 ;


  ssize_t ret = -1 ;


  char *buffer[blocksize] ;

  gtk_widget_set_state_flags(gui->src_button, GTK_STATE_FLAG_INSENSITIVE, TRUE);
  gtk_widget_set_state_flags(gui->dst_button, GTK_STATE_FLAG_INSENSITIVE, TRUE);

  gtk_widget_set_state_flags(gui->files_menu_button, GTK_STATE_FLAG_INSENSITIVE, TRUE);


  while ((ret = fread(buffer,  sizeof(gchar), blocksize, fp_r)) > 0) {

    cur_offset += fwrite(buffer, sizeof(gchar), ret, fp_w) ;

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), scrollbar_unit * cur_offset  ) ;

    update_gui() ;

  }

  fclose(fp_r) ;

  fflush(fp_w) ;

  fclose(fp_w) ;

  gtk_widget_set_state_flags(gui->src_button, GTK_STATE_FLAG_NORMAL, TRUE);
  gtk_widget_set_state_flags(gui->dst_button, GTK_STATE_FLAG_NORMAL, TRUE);

  gtk_widget_set_state_flags(gui->files_menu_button, GTK_STATE_FLAG_NORMAL, TRUE);

  on_copy_success(widget, progressbar, files) ;

  if (configuration->delete_src_file) {

    errno = 0 ;

    if (g_remove(files->src_filepath) == -1) {

      error_message(window, _("Error removing source file !"), g_strerror(errno)) ;

    }

  }

  free_filepathes(files->src_filepath, files->dst_filepath) ;

  return ;

}

