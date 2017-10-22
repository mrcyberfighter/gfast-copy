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

#include "./callbacks.h"

static void setup_style(GtkCssProvider *provider) ;

static void update_toggle_button_state(GtkWidget *widget) ;

static void switch_delete_src_file(GtkWidget *widget, bool *delete_src_file) ;

void set_theme(GtkWidget *widget, const gchar *variant) {

  GtkWidget *window = gtk_widget_get_toplevel(widget) ;

  /** We force the dark theme because we make some Gtk CSS after... **/
  GtkSettings *gtk_settings_for_screen = gtk_settings_get_for_screen(gtk_window_get_screen(GTK_WINDOW(window))) ;

  GtkCssProvider *provider = NULL ;

  char *theme_name = NULL ;

  g_object_get(G_OBJECT(gtk_settings_for_screen), "gtk-theme-name", &theme_name, NULL) ;

  if (theme_name != NULL) {

    provider = gtk_css_provider_get_named(theme_name, variant) ;

    g_free(theme_name) ;

  }

  if (provider != NULL) {

    setup_style(provider) ;

  }

  /** ********************************************************************** **/
  // Here we make some basic Gtk CSS:
  provider = gtk_css_provider_new();

  gchar *css = g_strdup_printf( "window {"
                                "background-color: %s;"
                                "}\n"
                                "menu {"
                                "background-color: %s;"
                                "}\n",
                                (! g_strcmp0(variant, "dark")) ? "#2f2f2f" : "#d9d9d9",
                                (! g_strcmp0(variant, "dark")) ? "#2f2f2f" : "#d9d9d9") ;


  configuration->use_light_theme = (! g_strcmp0(variant, "light")) ;

  gtk_css_provider_load_from_data(provider,css,-1, NULL);

  setup_style(provider) ;

  g_free(css) ;

  g_object_unref(provider);


  return ;

}


void filepath_dialog(GtkWidget *widget, gchar **filepath) {

  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN ;

  gchar *text = NULL ;

  bool is_src_file = true ;

  GtkWidget *button = NULL ;

  if (GTK_IS_BUTTON(widget)) {

    if (g_strcmp0(gtk_widget_get_name(widget), SOURCE_BUTTON_LABEL) == 0) {

      action = GTK_FILE_CHOOSER_ACTION_OPEN ;

      text = _("Choose file to copy") ;

    }
    else if (g_strcmp0(gtk_widget_get_name(widget), DEST_BUTTON_LABEL) == 0) {

      action = GTK_FILE_CHOOSER_ACTION_SAVE ;

      text = _("Choose the destination") ;

      is_src_file = false ;

    }

    button = widget ;

  }
  else if (GTK_IS_MENU_ITEM(widget)) {

    if (g_strcmp0(gtk_widget_get_name(widget), SOURCE_MENU_LABEL) == 0) {

      action = GTK_FILE_CHOOSER_ACTION_OPEN ;

      text = _("Choose file to copy") ;

      button = gui->src_button ;

    }
    else if (g_strcmp0(gtk_widget_get_name(widget), DEST_MENU_LABEL) == 0) {

      action = GTK_FILE_CHOOSER_ACTION_SAVE ;

      text = _("Choose the destination") ;

      is_src_file = false ;

      button = gui->dst_button ;

    }

  }

  GtkWidget *window = gtk_widget_get_toplevel(widget) ;

  #ifdef G_OS_UNIX
  GtkWidget *dst_file_chooser_dialog = gtk_file_chooser_dialog_new(text, GTK_WINDOW(window), action,  _("Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      _("OK"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

  #endif

  #ifdef G_OS_WIN32
  #ifdef NATIVE_WIN32

  /** @WARNING: This don't work into the Windows system using
    *
    * action = GTK_FILE_CHOOSER_ACTION_SAVE ;
    *
    *********************************************************/

  GtkFileChooserNative  *dst_file_chooser_dialog = gtk_file_chooser_native_new(text, GTK_WINDOW(window), action, _("OK"), _("Cancel"))  ;
  #else
  GtkWidget *dst_file_chooser_dialog = gtk_file_chooser_dialog_new(text, GTK_WINDOW(window), action,  _("Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      _("OK"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
  #endif
  #endif


  if (! is_src_file) {

    gchar *src_basename = g_path_get_basename(files->src_filepath) ;

    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dst_file_chooser_dialog), src_basename) ;

    g_free(src_basename) ;

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dst_file_chooser_dialog), TRUE);

  }

  #ifdef G_OS_UNIX
  gint ret = gtk_dialog_run(GTK_DIALOG(dst_file_chooser_dialog)) ;
  #endif

  #ifdef G_OS_WIN32
  #ifdef NATIVE_WIN32
  gint ret = gtk_native_dialog_run(GTK_NATIVE_DIALOG(dst_file_chooser_dialog)) ;
  #else
  gint ret = gtk_dialog_run(GTK_DIALOG(dst_file_chooser_dialog)) ;
  #endif
  #endif
 
  if (ret == GTK_RESPONSE_ACCEPT) {

    *filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dst_file_chooser_dialog)) ;

    gchar *filename = g_path_get_basename(*filepath) ;

    gtk_button_set_label(GTK_BUTTON(button), filename) ;

    GtkWidget *image = gtk_button_get_image(GTK_BUTTON(button)) ;

    gtk_image_clear(GTK_IMAGE(image)) ;

    g_free(filename) ;

  }
  else {

    *filepath = NULL ;

  }

  #ifdef G_OS_UNIX
  gtk_widget_destroy(dst_file_chooser_dialog) ;
  #endif

  #ifdef G_OS_WIN32
  gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(dst_file_chooser_dialog)) ;
  #endif

  return ;

}

static bool delete_src_file_anti_toggle_echo = true ;

void switch_delete_src_file_menuitem(GtkWidget *widget) {

  if (!  delete_src_file_anti_toggle_echo) {

    delete_src_file_anti_toggle_echo = true ;

    return ;

  }

  configuration->delete_src_file = ! configuration->delete_src_file ;

  switch_delete_src_file(gui->rm_src_file_button,  &configuration->delete_src_file) ;

  delete_src_file_anti_toggle_echo = false ;

  update_toggle_button_state(gui->rm_src_file_button) ;

  delete_src_file_anti_toggle_echo = true ;

  return ;

}


void switch_delete_src_file_button(GtkWidget *widget) {

  if (!  delete_src_file_anti_toggle_echo) {

    delete_src_file_anti_toggle_echo = true ;

    return ;

  }

  gtk_menu_item_activate(GTK_MENU_ITEM(gui->rm_src_file_menuitem)) ;

}

static void switch_delete_src_file(GtkWidget *widget, bool *delete_src_file) {

  GtkWidget *image = gtk_button_get_image(GTK_BUTTON(widget)) ;

  gtk_image_clear(GTK_IMAGE(image)) ;

  if ( *delete_src_file )   {

    image = gtk_image_new_from_file(PATH_TO_BUTTON_RM_FILE_ON_ICON) ;

    gtk_button_set_image(GTK_BUTTON(widget), image) ;

  }
  else {

    image = gtk_image_new_from_file(PATH_TO_BUTTON_RM_FILE_OFF_ICON) ;

    gtk_button_set_image(GTK_BUTTON(widget), image) ;

  }

  gchar *tooltip_markup = gtk_widget_get_tooltip_markup(widget) ;

  gchar **strv = g_strsplit(tooltip_markup,"->", 2);

  g_free(tooltip_markup) ;

  gchar *new_tooltip_markup = g_strdup_printf("%s -> %s", ((*delete_src_file) ?
                                                          _("<big><b>Remove</b> <i>source file</i> after copy <b>?</b></big>\n<i>Source file will <b>currently</b></i> be <b>deleted</b>.") :
                                                          _("<big><b>Remove</b> <i>source file</i> after copy <b>?</b></big>\n<i>Source file will <b>currently</b></i> <b>not</b> be <b>deleted</b>.")) ,strv[1]) ;

  gtk_widget_set_tooltip_markup(widget, new_tooltip_markup) ;

  g_free(new_tooltip_markup) ;

  g_strfreev(strv) ;

  return ;

}

static void update_toggle_button_state(GtkWidget *widget) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), ! gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) ;

  return ;

}

static inline void setup_style(GtkCssProvider *provider) {

  GdkDisplay *display = gdk_display_get_default() ;

  GdkScreen *screen = gdk_display_get_default_screen(display) ;

  gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION) ;

  return ;

}

