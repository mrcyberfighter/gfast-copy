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

#include "./configuration.h"

static GError *error = NULL ;

static gboolean configuration_file_exists(const gchar *filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (! g_file_test(filepath, G_FILE_TEST_EXISTS)) {

    /** create the configuration folder if doesn't exist. **/

    gchar *config_dirpath = g_path_get_dirname(filepath) ;

    g_mkdir_with_parents(config_dirpath, 0766) ;

    g_free(config_dirpath) ;

    int fd = g_creat(filepath, 0777) ;

    g_close(fd, NULL) ;

    return FALSE ;

  }

  return TRUE ;

}


static void set_default_configuration(GtkWidget *window, Configuration *config) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GKeyFile *conf_file = g_key_file_new() ;

  config->use_light_theme = true ;

  g_key_file_set_boolean(conf_file,   "gfast-copy-config", "use_light_theme", (gboolean) config->use_light_theme);

  g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

  if (error != NULL) {

    generate_message_dialog(window, _("Error saving configuration file !"), error->message, GTK_MESSAGE_ERROR) ;

    g_clear_error(&error) ;

    return ;

  }

  g_key_file_unref(conf_file) ;

}

void get_configuration(GtkWidget *window, GtkWidget *light, GtkWidget *dark, Configuration *config) {

  if (! configuration_file_exists(PATH_TO_CONF_FILE)) {

    set_default_configuration(window, config) ;

    config->use_light_theme = true ;

    return ;

  }

  /** Program configuration file. **/
  GKeyFile *conf_file = g_key_file_new() ;

  GError *error = NULL ;

  g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &error) ;

  if (error != NULL) {

    generate_message_dialog(window, _("Error getting configuration !"), error->message, GTK_MESSAGE_ERROR) ;

    g_clear_error(&error)  ;

    return ;
  }

  /** Read the configuration file: getting boolean or integer values. **/
  config->use_light_theme = (bool) g_key_file_get_boolean(conf_file,  "gfast-copy-config", "use_light_theme", NULL) ;

  g_key_file_unref(conf_file) ;

  if (config->use_light_theme) {
   
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(light), TRUE) ;
  }
  else {
   
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(dark), TRUE) ;
  }
     
  
  return ;
}

void set_configuration(void) {

  GKeyFile *conf_file = g_key_file_new() ;

  g_key_file_set_boolean(conf_file,   "gfast-copy-config", "use_light_theme", (gboolean) configuration->use_light_theme);

  g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, NULL);
 
  g_key_file_unref(conf_file) ;

  return ;
}

