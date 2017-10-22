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


#include "./headers/includes.h"

#include "./headers/defines.h"

#include "./global_vars.h"

#include "./callbacks.h"

#include "./copy_files.h"

#include "./configuration.h"

#include "./GtkSmartMenuItem.h"

#include "./GtkSmartIconButton.h"

#include "./documentation.h"

static void activate(GApplication *application, gpointer user_data) ;

static void startup(GApplication *application, gpointer user_data) ;


static void open_files(GApplication  *application, GFile **args, gint n_files, const gchar *hint) ;

#ifdef G_OS_UNIX
static void about_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

#if 0
static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;
#endif

static void quit_activated(GSimpleAction *action, GVariant      *parameter, gpointer       app) ;
#endif

static void shutdown_app(GApplication *application, gpointer user_data) ;



static void destroy(GtkWidget *widget, GApplication *app) ;

static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) ;


static void set_tooltip_text_on_button(GtkWidget *widget, const gchar *tooltip_text, const guint accel_key, const GdkModifierType accel_modifier) ;

static GtkWidget *creat_and_fill_button_box(GtkWidget *label_button, GtkWidget *icon_button) ;

#ifdef G_OS_WIN32
static void initialize_constant(void) ;

static void free_constant(void) ;
#endif

int main(int argc, char *argv[]) {


  #ifdef G_OS_WIN32

  /** On Windows the preprocessor trick doesn't work: ./headers/defines.h **/

  initialize_constant() ;

  #endif // G_OS_WIN32

  GtkWidget *window ;

  GUI pgui ;

  gui = &pgui ;

  Files pfiles ;

  files = &pfiles ;

  files->src_filepath = NULL ;

  files->dst_filepath = NULL ;

  Configuration pconf ;

  configuration = &pconf ;

  configuration->use_light_theme = true ;
  configuration->delete_src_file = false ;

  // Given the program a name to displaying to the user through: g_get_application_name().
  g_set_application_name(PRGNAME) ;

  const char *app_id = "fast.copy.mrcyberfighter" ;

  if ( ! g_application_id_is_valid(app_id) ) {

    fprintf(stderr, "Wrong app id\n") ;
    exit(EXIT_FAILURE) ;

  }


  // Setting the applications flags
  int app_flags =  G_APPLICATION_NON_UNIQUE | G_APPLICATION_SEND_ENVIRONMENT | G_APPLICATION_HANDLES_OPEN ;


  GtkApplication *app = gtk_application_new(app_id, (GApplicationFlags) app_flags) ;

  // The ::activate signal is emitted on the primary instance when an activation occurs. When g_application_activate() is called.
  g_signal_connect( G_APPLICATION(app),  "activate",  G_CALLBACK(activate),   NULL) ;
  // The ::open signal is emitted on the primary instance when there are files to open.
  g_signal_connect( G_APPLICATION(app),  "open",      G_CALLBACK(open_files), NULL) ;
  // The ::startup signal is emitted on the primary instance immediately after registration. When g_application_register() is called.
  g_signal_connect( G_APPLICATION(app),  "startup",   G_CALLBACK(startup),    NULL) ;
  // The ::shutdown signal is emitted only on the registered primary instance immediately after the main loop terminates.
  g_signal_connect( G_APPLICATION(app),  "shutdown",   G_CALLBACK(shutdown_app),    NULL) ;

  GError *err = NULL ;

  g_application_register(G_APPLICATION(app), NULL, &err) ;

  if (err != NULL) {

    fprintf(stderr,"Cannot register app: %s\n", err->message) ;
    exit(EXIT_FAILURE) ;

  }

  #ifdef MAC_INTEGRATION  
  gtkosx_application_ready(gtkosx_application_get()) ;
  gtkosx_application_set_use_quartz_accelerators(gtkosx_application_get(), TRUE) ;
  #ifdef DEBUG
  fprintf(stdout,"Mac app use quartz accels: %d\n", gtkosx_application_use_quartz_accelerators(osx_application)) ;
  #endif
  g_set_prgname("gfast-copy") ; // Don't automatically set from the GtkApplication system like on Linux.
  
  GdkPixbuf *window_pixbuf = gdk_pixbuf_new_from_file(PATH_TO_PROGRAM_ICON, NULL) ;
  gtkosx_application_set_dock_icon_pixbuf(gtkosx_application_get(), window_pixbuf) ;
  g_object_unref(window_pixbuf) ;
  
  //gtkosx_application_attention_request(gtkosx_application_get(), INFO_REQUEST);
  gtkosx_application_attention_request(gtkosx_application_get(), CRITICAL_REQUEST);
  
  
  #endif
  
  
  #ifdef DEBUG
  fprintf(stdout,"mmp GtkApplication DBUS path: %s\n", g_application_get_dbus_object_path(G_APPLICATION(app)) ) ;
  #endif

  #ifdef G_OS_UNIX

  g_signal_connect( G_APPLICATION(app),  "activate",              G_CALLBACK(activate),       NULL) ;
  g_signal_connect( G_APPLICATION(app),  "open",                  G_CALLBACK(open_files),     NULL) ;
  g_signal_connect( G_APPLICATION(app),  "startup",               G_CALLBACK(startup),        NULL) ;
  g_signal_connect( G_APPLICATION(app),  "shutdown",              G_CALLBACK(shutdown_app),   NULL) ;

  if (gtk_application_prefers_app_menu(app)) { // Normally gtk_application_prefers_app_menu(app) -> The value returned by this function is purely advisory and you are free to ignore it.

    GtkBuilder *builder = NULL  ;
    GMenuModel *app_menu = NULL ;

    static GActionEntry app_entries[] = {
    { "about",        about_activated,        NULL, NULL, NULL },
    { "quit",         quit_activated,         NULL, NULL, NULL }

    };

    g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);

    builder = gtk_builder_new_from_string("<?xml version=\"1.0\"?>"
                                            "<interface>"
                                              "<menu id=\"appmenu\">"
                                                "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">About</attribute>"
                                                    "<attribute name=\"action\">app.about</attribute>"
                                                  "</item>"
                                                "</section>"
                                                "<section>"
                                                  "<item>"
                                                    "<attribute name=\"label\" translatable=\"no\">Quit</attribute>"
                                                    "<attribute name=\"action\">app.quit</attribute>"
                                                 "</item>"
                                               "</section>"
                                              "</menu>"
                                            "</interface>",

                                            -1) ;

    app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "appmenu"));

    gtk_application_set_app_menu(GTK_APPLICATION(app), app_menu);

    g_object_unref(builder) ;

  }

  #endif


  g_application_set_inactivity_timeout( G_APPLICATION(app), 100) ;


  window = gtk_application_window_new(app)  ;



  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;

  gtk_window_set_default_size(GTK_WINDOW(window), 512, -1) ;

  gtk_widget_set_size_request(window, 512, -1) ;

  g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(destroy), G_APPLICATION(app))  ;

  g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(delete_event),NULL) ;

  gtk_window_set_default_icon_from_file(PATH_TO_PROGRAM_ICON, NULL);

  


  GtkWidget *progressbar = gtk_progress_bar_new() ;

  gtk_widget_set_size_request(progressbar, 512, -1) ;

  g_object_set(progressbar, "margin-top", 8, "margin-bottom", 8, "margin-start", 4, "margin-end", 4, "show-text", TRUE, NULL) ;



  GtkWidget *menu_bar = gtk_menu_bar_new() ;



  gui->files_menu_button = gtk_smart_menu_item_new_all( _(" Files "), PATH_TO_MENU_BUTTON_FILES, NULL, 0, 0) ;

  GtkAccelGroup *accel_group = gtk_accel_group_new() ;


  GtkWidget *smart_menu_item_set_src_file   = gtk_smart_menu_item_new_all(SOURCE_MENU_LABEL, PATH_TO_MENU_SRC_FILE_ICON, accel_group, GDK_CONTROL_MASK, GDK_KEY_s) ;

  GtkWidget *menu_item_set_src_file = gtk_smart_menu_item_get_menuitem(smart_menu_item_set_src_file) ;
 
  gtk_widget_set_name(menu_item_set_src_file, SOURCE_MENU_LABEL) ;

  g_signal_connect(menu_item_set_src_file, "activate", G_CALLBACK(filepath_dialog), &files->src_filepath) ;

  GtkWidget *smart_menu_item_set_dst_file   = gtk_smart_menu_item_new_all(DEST_MENU_LABEL, PATH_TO_MENU_DST_FILE_ICON, accel_group, GDK_CONTROL_MASK, GDK_KEY_d) ;


  GtkWidget *menu_item_set_dst_file = gtk_smart_menu_item_get_menuitem(smart_menu_item_set_dst_file) ;

  gtk_widget_set_name(menu_item_set_dst_file, DEST_MENU_LABEL) ;

  g_signal_connect(menu_item_set_dst_file, "activate", G_CALLBACK(filepath_dialog), &files->dst_filepath) ;


  GtkWidget *smart_menu_item_run_copy_file   = gtk_smart_menu_item_new_all( _("  Run copying  "), PATH_TO_MENU_COPY_FILE_ICON, accel_group, GDK_CONTROL_MASK, GDK_KEY_Return) ;

  GtkWidget *menu_item_run_copy_file = gtk_smart_menu_item_get_menuitem(smart_menu_item_run_copy_file) ;

  g_signal_connect(menu_item_run_copy_file, "activate", G_CALLBACK(apply_copy), progressbar) ;


  GtkWidget *smart_menu_item_quit_program  = gtk_smart_menu_item_new_all( _("  Quit  "), PATH_TO_MENU_QUIT_ICON, accel_group, GDK_CONTROL_MASK, GDK_KEY_q) ;

  GtkWidget *menu_item_quit_program = gtk_smart_menu_item_get_menuitem(smart_menu_item_quit_program) ;

  g_signal_connect(menu_item_quit_program, "activate", G_CALLBACK(destroy), app) ;


  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), gtk_smart_menu_item_get_menuitem(gui->files_menu_button)) ;

  GtkWidget *menu_files = gtk_menu_new() ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(gtk_smart_menu_item_get_menuitem(gui->files_menu_button)), menu_files);


  gtk_menu_shell_append(GTK_MENU_SHELL(menu_files), menu_item_set_src_file) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_files), menu_item_set_dst_file) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_files), menu_item_run_copy_file) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_files), gtk_separator_menu_item_new()) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_files), menu_item_quit_program) ;


  


  GtkWidget *menu_button_config = gtk_smart_menu_item_new_all( _("  Configuration  "), PATH_TO_MENU_BUTTON_CONFIG, NULL, 0, 0) ;

  GtkWidget *smart_menu_item_light_theme  = gtk_smart_radio_menu_item_new_all( _("  Light theme  "), PATH_TO_MENU_LIGHT_ICON, NULL, 0, 0, NULL) ;

  GtkWidget *menu_item_light_theme = gtk_smart_menu_item_get_menuitem(smart_menu_item_light_theme) ;

  g_signal_connect(menu_item_light_theme, "activate", G_CALLBACK(set_theme), "light") ;



  GtkWidget *smart_menu_item_dark_theme  = gtk_smart_radio_menu_item_new_all( _("  Dark theme  "), PATH_TO_MENU_DARK_ICON, NULL, 0, 0, menu_item_light_theme) ;

  GtkWidget *menu_item_dark_theme = gtk_smart_menu_item_get_menuitem(smart_menu_item_dark_theme) ;

  g_signal_connect(menu_item_dark_theme, "activate", G_CALLBACK(set_theme), "dark") ;




  GtkWidget *smart_menu_item_rm_src_file  = gtk_smart_check_menu_item_new_all( _("  Delete source file  "), true, PATH_TO_MENU_RM_FILE_ICON, NULL, 0, 0) ;

  gui->rm_src_file_menuitem = gtk_smart_menu_item_get_menuitem(smart_menu_item_rm_src_file) ;

  g_signal_connect(G_OBJECT(gui->rm_src_file_menuitem), "activate", G_CALLBACK(switch_delete_src_file_menuitem), NULL) ;



  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), gtk_smart_menu_item_get_menuitem(menu_button_config)) ;

  GtkWidget *menu_config = gtk_menu_new() ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(gtk_smart_menu_item_get_menuitem(menu_button_config)), menu_config);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu_config), menu_item_light_theme) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_config), menu_item_dark_theme) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_config), gtk_separator_menu_item_new()) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_config), gui->rm_src_file_menuitem) ;



  /** ********************************************************************** **/

  get_configuration(window, menu_item_light_theme, menu_item_dark_theme, configuration) ;

  /** ********************************************************************** **/




  GtkWidget *smart_menu_item_readme = gtk_smart_menu_item_new_all( _("  Read me  "), PATH_TO_MENU_README_ICON, accel_group, GDK_CONTROL_MASK, GDK_KEY_n) ;

  GtkWidget *readme_menuitem = gtk_smart_menu_item_get_menuitem(smart_menu_item_readme) ;

  g_signal_connect(readme_menuitem, "activate", G_CALLBACK(launch_readme_html), window) ;


  GtkWidget *smart_menu_item_about_program  = gtk_smart_menu_item_new_all( _("  About ?  "), PATH_TO_MENU_ABOUT_ICON, accel_group, GDK_CONTROL_MASK, GDK_KEY_a) ;

  GtkWidget *menu_item_about_program = gtk_smart_menu_item_get_menuitem(smart_menu_item_about_program) ;

  g_signal_connect(menu_item_about_program, "activate", G_CALLBACK(display_about_dialog), window) ;


  GtkWidget *smart_menu_button_documentation = gtk_smart_menu_item_new_all( _(" Info ? "), PATH_TO_MENU_BUTTON_DOC, NULL, 0, 0) ;

  GtkWidget *menu_button_documentation = gtk_smart_menu_item_get_menuitem(smart_menu_button_documentation) ;

  GtkWidget *menu_documentation = gtk_menu_new() ;

  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_button_documentation) ;

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_button_documentation), menu_documentation);

  gtk_menu_shell_append(GTK_MENU_SHELL(menu_documentation), readme_menuitem) ;
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_documentation), menu_item_about_program) ;







  gui->src_button = gtk_button_new_with_label(SOURCE_BUTTON_LABEL) ;
 
  gtk_widget_set_name(gui->src_button, SOURCE_BUTTON_LABEL) ;
 
  gtk_widget_set_size_request(gui->src_button, 512, -1) ;

  g_signal_connect(gui->src_button, "clicked", G_CALLBACK(filepath_dialog), &files->src_filepath) ;

  GtkWidget *image_src_button = gtk_image_new_from_file(PATH_TO_BUTTON_SRC_FILE_ICON) ;

  gtk_button_set_image(GTK_BUTTON(gui->src_button), image_src_button) ;

  g_object_set(gui->src_button, "always-show-image", TRUE, NULL) ;

  set_tooltip_text_on_button(gui->src_button, _("File to copy."), GDK_KEY_s, GDK_CONTROL_MASK) ;




  gui->dst_button = gtk_button_new_with_label(DEST_BUTTON_LABEL) ;
 
  gtk_widget_set_name(gui->dst_button, DEST_BUTTON_LABEL) ;
 
  gtk_widget_set_size_request(gui->dst_button, 512, -1) ;

  g_signal_connect(gui->dst_button, "clicked", G_CALLBACK(filepath_dialog), &files->dst_filepath) ;

  GtkWidget *image_dst_button = gtk_image_new_from_file(PATH_TO_BUTTON_DST_FILE_ICON) ;

  gtk_button_set_image(GTK_BUTTON(gui->dst_button), image_dst_button) ;

  g_object_set(gui->dst_button, "always-show-image", TRUE, NULL) ;

  set_tooltip_text_on_button(gui->dst_button, _("Copy destination."), GDK_KEY_s, GDK_CONTROL_MASK) ;


  GtkWidget *action_copy_button = gtk_smart_icon_button_new_all(PATH_TO_BUTTON_ACTION_ICON, _("Copy Source to Destination !"), GDK_KEY_Return, GDK_CONTROL_MASK) ;

  g_signal_connect(action_copy_button, "clicked", G_CALLBACK(apply_copy), progressbar) ;




  gui->rm_src_file_button = gtk_smart_icon_toggle_button_new_all( (configuration->delete_src_file) ?
                                                                  PATH_TO_BUTTON_RM_FILE_ON_ICON :
                                                                  PATH_TO_BUTTON_RM_FILE_OFF_ICON,
                                                                  ((configuration->delete_src_file) ?
                                                                  _("<big><b>Remove</b> <i>source file</i> after copy <b>?</b></big>\n<i>Source file will <b>currently</b></i> be <b>deleted</b>.") :
                                                                   _("<big><b>Remove</b> <i>source file</i> after copy <b>?</b></big>\n<i>Source file will <b>currently</b></i> <b>not</b> be <b>deleted</b>.")) ,
                                                                   GDK_KEY_r,
                                                                   GDK_CONTROL_MASK) ;

  g_signal_connect(G_OBJECT(gui->rm_src_file_button), "toggled", G_CALLBACK(switch_delete_src_file_button), NULL) ;

  GtkWidget *button_box_hbox_1 = creat_and_fill_button_box(gui->src_button, gui->rm_src_file_button) ;

  GtkWidget *button_box_hbox_2 = creat_and_fill_button_box(gui->dst_button, action_copy_button) ;



  GtkWidget *main_button_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_box_set_spacing(GTK_BOX(main_button_vbox), 8) ;

  gtk_box_pack_start(GTK_BOX(main_button_vbox), button_box_hbox_1, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(main_button_vbox), button_box_hbox_2, TRUE, TRUE, 0) ;

  GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8) ;



  gtk_box_pack_start(GTK_BOX(main_vbox), menu_bar,           TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(main_vbox), main_button_vbox,   TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(main_vbox), progressbar,        TRUE, TRUE, 0) ;

  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group)   ;

  gtk_container_add(GTK_CONTAINER(window), main_vbox) ;

  gtk_widget_show_all(window) ;




  g_application_set_default(g_application_get_default()) ;

  g_application_activate(G_APPLICATION(app)) ;
  
  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  //        I cant' use gtkosx_application_insert_app_menu_item(...) properly. 
  gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif
  
  g_application_run(G_APPLICATION(app), argc, argv) ;

  g_object_unref(app);

  set_configuration() ;

  #ifdef G_OS_WIN32

  /** On Windows the preprocessor trick doesn't work: ./headers/defines.h **/

  free_constant() ;

  #endif

  exit(EXIT_SUCCESS) ;

}


void activate(GApplication *application, gpointer user_data) {

  #ifdef DEBUG
  g_print("activate\n");
  #endif

  /** @Note: when doing a longer-lasting action here that returns
   ** to the mainloop, you should use g_application_hold() and
   ** g_application_release() to keep the application alive until
   ** the action is completed.
   ** Only by not intern done things like file opening not by toplevel displaying .
   ********************************************************************************/

   return ;
}

void startup(GApplication *application, gpointer user_data) {

  #ifdef G_OS_WIN32
  #if HAVE_PUTENV
  putenv("GTK_DATA_PREFIX=./") ;
  #endif
  #endif

  #if HAVE_SETLOCALE
  setlocale(LC_ALL, "") ;
  #endif

  #ifdef DEBUG
  g_print("startup\n");
  #endif

  /** @Note: when doing a longer-lasting action here that returns
   ** to the mainloop, you should use g_application_hold() and
   ** g_application_release() to keep the application alive until
   ** the action is completed.
   ** Only by not intern done things like file opening not by toplevel displaying .
   ********************************************************************************/
}

#if 1
static void open_files(GApplication  *application, GFile **args, gint n_files, const gchar *hint) {

  gint i;

  for (i = 0; i < n_files; i++) {

    files->src_filepath = g_strdup(g_file_get_path(args[0])) ;

    gchar *src_file_basename = g_path_get_basename(files->src_filepath) ;

    gtk_button_set_label(GTK_BUTTON(gui->src_button), src_file_basename) ;

    g_free(src_file_basename) ;

    g_print ("open %s\n", files->src_filepath);

  }

  /** @Note: when doing a longer-lasting action here that returns
   ** to the mainloop, you should use g_application_hold() and
   ** g_application_release() to keep the application alive until
   ** the action is completed.
   ** Only by not intern done things like file opening not by toplevel displaying .
   ********************************************************************************/
}
#endif

#ifdef G_OS_UNIX
void about_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  display_about_dialog(NULL, GTK_WIDGET(gtk_application_get_active_window(app))) ;

  return ;

}

#if 0
void preferences_activated(GSimpleAction *action, GVariant *parameter, ) {

  //configure_program_dialog(NULL, NULL) ;

  return ;

}
#endif

void quit_activated(GSimpleAction *action, GVariant      *parameter, gpointer       app) {

  destroy(NULL, app) ;

  return ;

}
#endif

void shutdown_app(GApplication *app, gpointer user_data) {

  destroy(NULL, app) ;

  return ;

}


void destroy(GtkWidget *widget, GApplication *app) {

  g_application_quit(app) ;

}

gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) {

 return FALSE ;

}



static inline void set_tooltip_text_on_button(GtkWidget *widget, const gchar *tooltip_text, const guint accel_key, const GdkModifierType accel_modifier) {

  gchar *accel_text = gtk_accelerator_get_label(accel_key, accel_modifier) ;

  gchar *tooltip_txt = g_strdup_printf("%s -> [ <b>%s</b> ]", tooltip_text, accel_text) ;

  gtk_widget_set_tooltip_markup(widget, tooltip_txt) ;

  g_free(tooltip_txt) ;

  g_free(accel_text) ;

  return ;

}

static GtkWidget *creat_and_fill_button_box(GtkWidget *label_button, GtkWidget *icon_button) {

  GtkWidget *hbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;

  gtk_box_pack_start(GTK_BOX(hbox), label_button, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(hbox), icon_button, FALSE, FALSE, 0) ;

  gtk_button_box_set_layout(GTK_BUTTON_BOX(hbox), GTK_BUTTONBOX_SPREAD);

  gtk_box_set_spacing(GTK_BOX(hbox), 8) ;

  gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(hbox), icon_button,   TRUE) ;

  return hbox ;
}

#ifdef G_OS_WIN32
/** On Windows the preprocessor trick doesn't work: ./headers/defines.h **/

static void initialize_constant(void) {

  PREFIX = g_win32_get_package_installation_directory_of_module(NULL) ;

  PATH_TO_CONF_FILE = g_build_path(G_DIR_SEPARATOR_S, g_get_home_dir(), "AppData", "Roaming", PRGNAME, "gfast-copy-config.ini", NULL)  ;

  PATH_TO_BUTTON_ACTION_ICON =  g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "22x22", "folder-sync.png", NULL) ;

  PATH_TO_BUTTON_SRC_FILE_ICON =  g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "22x22", "folder-new.png", NULL) ;

  PATH_TO_BUTTON_DST_FILE_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "22x22", "folder-downloads.png", NULL) ;

  PATH_TO_BUTTON_RM_FILE_ON_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "22x22", "folder-important.png", NULL) ;

  PATH_TO_BUTTON_RM_FILE_OFF_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "22x22", "folder-temp.png", NULL) ;



  PATH_TO_MENU_BUTTON_FILES = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "folder-development.png", NULL) ;

  PATH_TO_MENU_SRC_FILE_ICON  = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "folder-new.png", NULL) ;

  PATH_TO_MENU_DST_FILE_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "folder-downloads.png", NULL) ;

  PATH_TO_MENU_COPY_FILE_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "folder-sync.png", NULL) ;

  PATH_TO_MENU_README_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "system-help.png", NULL) ;

  PATH_TO_MENU_ABOUT_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "help-about.png", NULL) ;

  PATH_TO_MENU_QUIT_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "application-exit.png", NULL) ;

  PATH_TO_MENU_BUTTON_DOC  = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "help-contents.png", NULL) ;

  PATH_TO_MENU_BUTTON_CONFIG  = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "run-build-configure.png", NULL) ;

  PATH_TO_MENU_DARK_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "preferences-theme-dark.png", NULL) ;

  PATH_TO_MENU_LIGHT_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "preferences-theme-light.png", NULL) ;

  PATH_TO_MENU_RM_FILE_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "icons", "16x16", "folder-locked.png", NULL) ;

  PATH_TO_PROGRAM_ICON =g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "images", "gfast-copy_icon.png", NULL) ;

  PATH_TO_LICENSE_TEXT = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "license", "gpl.txt", NULL) ;

  PATH_TO_README = g_build_path(G_DIR_SEPARATOR_S, PREFIX, "share", PRGNAME, "README", "html", "index.html", NULL) ;

  return ;
}


static void free_constant(void) {

  g_free(PREFIX) ;

  g_free(PATH_TO_CONF_FILE) ;

  g_free(PATH_TO_BUTTON_ACTION_ICON) ;

  g_free(PATH_TO_BUTTON_SRC_FILE_ICON) ;

  g_free(PATH_TO_BUTTON_DST_FILE_ICON) ;

  g_free(PATH_TO_BUTTON_RM_FILE_ON_ICON) ;

  g_free(PATH_TO_BUTTON_RM_FILE_OFF_ICON) ;

  g_free(PATH_TO_MENU_BUTTON_FILES) ;



  g_free(PATH_TO_MENU_SRC_FILE_ICON) ;

  g_free(PATH_TO_MENU_DST_FILE_ICON) ;

  g_free(PATH_TO_MENU_COPY_FILE_ICON) ;

  g_free(PATH_TO_MENU_README_ICON) ;

  g_free(PATH_TO_MENU_ABOUT_ICON) ;

  g_free(PATH_TO_MENU_QUIT_ICON) ;

  g_free(PATH_TO_MENU_BUTTON_DOC) ;

  g_free(PATH_TO_MENU_BUTTON_CONFIG) ;

  g_free(PATH_TO_MENU_DARK_ICON) ;

  g_free(PATH_TO_MENU_LIGHT_ICON) ;

  g_free(PATH_TO_MENU_RM_FILE_ICON) ;

  g_free(PATH_TO_PROGRAM_ICON) ;

  g_free(PATH_TO_LICENSE_TEXT) ;

  g_free(PATH_TO_README) ;

  return ;
}


#endif
