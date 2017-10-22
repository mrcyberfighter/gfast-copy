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

#include "GtkSmartIconButton.h"

struct _GtkSmartIconButtonPrivate {

  /** This structure contains all the members of the new type: **/

  GtkWidget *toggle_button ;

} ;

static void gtk_smart_icon_button_class_init(GtkSmartIconButtonClass *class);
static void gtk_smart_icon_button_init(GtkSmartIconButton *smart_icon_button); // Constructor
static void gtk_smart_icon_button_dispose(GObject *object);
static void gtk_smart_icon_button_finalize(GObject *object); // Destructor

G_DEFINE_TYPE_WITH_PRIVATE(GtkSmartIconButton, gtk_smart_icon_button, GTK_TYPE_BUTTON)

static void gtk_smart_icon_button_class_init(GtkSmartIconButtonClass *class) {

  /** Class initialize. **/

  g_return_if_fail(class != NULL);

  GObjectClass *object_class = G_OBJECT_CLASS(class);


  object_class->dispose  = gtk_smart_icon_button_dispose ; // Destructor
  object_class->finalize = gtk_smart_icon_button_finalize ; // Destructor
}

static void gtk_smart_icon_button_init(GtkSmartIconButton *smart_icon_button) {

  /** Initialize the members. **/

  g_return_if_fail(smart_icon_button != NULL);

  /** Permit to access object private data. **/
  GtkSmartIconButtonPrivate *priv = gtk_smart_icon_button_get_instance_private(smart_icon_button);

  /** Initialize private data. **/

  priv->toggle_button = NULL ;

}

static void gtk_smart_icon_button_dispose(GObject *object) {

  #ifdef DEBUG
  GtkSmartIconButtonPrivate *priv = gtk_smart_icon_button_get_instance_private(GTK_SMART_ICON_BUTTON(object));
  #endif

  G_OBJECT_CLASS(gtk_smart_icon_button_parent_class)->dispose(object);

  #ifdef DEBUG
  fprintf(stderr,"%s -> %p\n", __func__, (void *) priv->toggle_button) ;
  #endif
}


static void gtk_smart_icon_button_finalize(GObject *object) {

  #ifdef DEBUG
  GtkSmartIconButtonPrivate *priv = gtk_smart_icon_button_get_instance_private(GTK_SMART_ICON_BUTTON(object));
  #endif

  /** Private data destructor if necessary. **/
  G_OBJECT_CLASS(gtk_smart_icon_button_parent_class)->finalize(object);

  #ifdef DEBUG
  fprintf(stderr,"%s -> %p\n", __func__, (void *) priv->toggle_button) ;
  #endif

}

GtkWidget* gtk_smart_icon_button_new_all(const gchar *filepath, const gchar *tooltip_text, const guint accel_key, const GdkModifierType accel_modifier) {

  if (filepath == NULL) {

    return NULL ;

  }

  GFile *g_file = g_file_new_for_path(filepath) ;

  char *image_realpath = g_file_get_path(g_file) ;

  g_object_unref(g_file) ;

  errno = 0 ;

  if (! g_file_test(image_realpath, G_FILE_TEST_IS_REGULAR)) {

    g_printerr("%s", g_strerror(g_file_error_from_errno(errno)) ) ;

    return NULL ;

  }

  /** Initialize private data. **/

  GtkSmartIconButton *smart_icon_button = NULL ;

  smart_icon_button = g_object_new(GTK_TYPE_SMART_ICON_BUTTON, NULL);

  GtkWidget *image = gtk_image_new_from_file(image_realpath); /** The menu_item   **/

  free(image_realpath) ;

  gtk_button_set_image(GTK_BUTTON(smart_icon_button), image) ;

  g_object_set(smart_icon_button, "always-show-image", TRUE, NULL) ;

  if (tooltip_text != NULL) {

    if (accel_key > 0) {

      gchar *accel_text = gtk_accelerator_get_label(accel_key, accel_modifier) ;

      gchar *tooltip_txt = g_strdup_printf("%s -> [ <b>%s</b> ]",tooltip_text, accel_text) ;

      gtk_widget_set_tooltip_markup(GTK_WIDGET(smart_icon_button), tooltip_txt) ;

      g_free(tooltip_txt) ;

      g_free(accel_text) ;

    }
    else {

      gtk_widget_set_tooltip_text(GTK_WIDGET(smart_icon_button), tooltip_text) ;

    }

  }

  return GTK_WIDGET(smart_icon_button) ;

}

GtkWidget* gtk_smart_icon_toggle_button_new_all(const gchar *filepath, const gchar *tooltip_text, const guint accel_key, const GdkModifierType accel_modifier) {

  if (filepath == NULL) {

    return NULL ;

  }

  GFile *g_file = g_file_new_for_path(filepath) ;

  char *image_realpath = g_file_get_path(g_file) ;

  g_object_unref(g_file) ;

  errno = 0 ;

  if (! g_file_test(image_realpath, G_FILE_TEST_IS_REGULAR)) {

    g_printerr("%s", g_strerror(g_file_error_from_errno(errno)) ) ;

    return NULL ;

  }

  /** Initialize private data. **/

  GtkSmartIconButton *smart_icon_button = NULL ;

  smart_icon_button = g_object_new(GTK_TYPE_SMART_ICON_BUTTON, NULL);

  /** Accessing private data **/
  GtkSmartIconButtonPrivate *priv = gtk_smart_icon_button_get_instance_private(smart_icon_button);

  priv->toggle_button = gtk_toggle_button_new() ;

  GtkWidget *image = gtk_image_new_from_file(image_realpath);

  free(image_realpath) ;

  gtk_button_set_image(GTK_BUTTON(priv->toggle_button), image) ;

  g_object_set(priv->toggle_button, "always-show-image", TRUE, NULL) ;

  if (tooltip_text != NULL) {

    if (accel_key > 0) {

      gchar *accel_text = gtk_accelerator_get_label(accel_key, accel_modifier) ;

      gchar *tooltip_txt = g_strdup_printf("%s -> [ <b>%s</b> ]",tooltip_text, accel_text) ;

      gtk_widget_set_tooltip_markup(GTK_WIDGET(priv->toggle_button), tooltip_txt) ;

      g_free(tooltip_txt) ;

      g_free(accel_text) ;

    }
    else {

      gtk_widget_set_tooltip_text(GTK_WIDGET(priv->toggle_button), tooltip_text) ;

    }

  }

  return GTK_WIDGET(priv->toggle_button) ;

}

GtkWidget* gtk_smart_icon_button_new_with_tooltip(const gchar *filepath, const gchar *tooltip_text) {

  if (filepath == NULL) {

    return NULL ;

  }

  GFile *g_file = g_file_new_for_path(filepath) ;

  char *image_realpath = g_file_get_path(g_file) ;

  g_object_unref(g_file) ;

  errno = 0 ;

  if (! g_file_test(image_realpath, G_FILE_TEST_IS_REGULAR)) {

    g_printerr("%s", g_strerror(g_file_error_from_errno(errno)) ) ;

    return NULL ;

  }

  /** Initialize private data. **/

  GtkSmartIconButton *smart_icon_button = NULL ;

  smart_icon_button = g_object_new(GTK_TYPE_SMART_ICON_BUTTON, NULL);

  GtkWidget *image = gtk_image_new_from_file(image_realpath); /** The menu_item   **/

  free(image_realpath) ;

  gtk_button_set_image(GTK_BUTTON(smart_icon_button), image) ;

  g_object_set(smart_icon_button, "always-show-image", TRUE, NULL) ;

  if (tooltip_text != NULL) {

      gtk_widget_set_tooltip_text(GTK_WIDGET(smart_icon_button), tooltip_text) ;

  }

  return GTK_WIDGET(smart_icon_button) ;

}

