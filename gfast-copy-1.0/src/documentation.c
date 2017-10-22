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

#include "documentation.h"

static GError *error = NULL ;

#ifdef G_OS_WIN32

static void readme_thread(GtkWidget *window) ;

static void readme_thread(GtkWidget *window) {

  // Used as a method to make busy wait less evil.
  g_thread_yield();

  /** The GAppInfo feature of Gio quasi not work on windows, nor on Mac.
    *
    * For displaying the README I have try all:
    * From g_spawn_* to g_app_info_launch_* nothing works
    * This finally works: once installed it has a different behavior as launched from cmd.exe  **/

  GAppInfo *app_for_html = g_app_info_get_default_for_type(g_content_type_from_mime_type("text/html"), FALSE) ;

  //fprintf(stdout,"Find the default program for HTML %p\nOoouuuuuufff it was very hard !\n", (void *) app_for_html) ;

  #ifdef DEBUG
  fprintf(stdout,"Default application for html: %s\n", g_app_info_get_name(app_for_html)) ;
  #endif

  // Using the cmd.exe "start program + file[path|uri]"  works.
  GString *gstring_cmdline = g_string_new("start ");

  // This would using the Netscape navigator (v9) on my system instead of the default for HTML.
  //gstring_cmdline = g_string_append(gstring_cmdline, g_app_info_get_name(app_for_html) ) ;
  //gstring_cmdline = g_string_append(gstring_cmdline, " ") ;

  gstring_cmdline = g_string_append(gstring_cmdline,  g_filename_to_uri(PATH_TO_README, NULL, NULL) ) ;

  gchar *cmdline = g_string_free(gstring_cmdline, FALSE) ;

  #ifdef DEBUG
  fprintf(stdout,"cmdline:\n%s\n", cmdline) ;
  fflush(stdout) ;
  #endif

  if ( system( cmdline ) != 0) { // The command line "start + (PROGRAM +) MY_HTML_FILE" work's well except that the Windows console is display a mini moment at launching but disappear as fast.
  
    generate_message_dialog(window, _("Error launching readme !"),
                                    _("Error by launching the HTML README \n"
                                      "Sorry ! You can type \"gfast-copy readme\" into your\n"
                                      "Windows O.S search bar.\nTo find the readme of this program."),
                                       GTK_MESSAGE_ERROR) ;


  }

  if (cmdline != NULL) {

    g_free(cmdline) ;

  }

  g_object_unref(app_for_html) ;

  g_thread_exit(NULL) ;

  return ;
}

#endif

#ifdef MAC_INTEGRATION

static void readme_thread(GtkWidget *window) ;

static void readme_thread(GtkWidget *window) {

  // Used as a method to make busy wait less evil.
  g_thread_yield();

  // Try: Using the cmd.exe "open + file[path|uri]"  works.
  GString *gstring_cmdline = g_string_new("open ");

  GFile *gfile_readme =	g_file_new_for_path( PATH_TO_README ) ;

  gfile_readme = g_file_resolve_relative_path(gfile_readme, PATH_TO_README) ;

  gstring_cmdline = g_string_append(gstring_cmdline,  g_file_get_uri(gfile_readme)) ;

  g_object_unref(gfile_readme) ;

  gchar *cmdline = g_string_free(gstring_cmdline, FALSE) ;

  #ifdef DEBUG
  fprintf(stdout,"cmdline:\n%s\n", cmdline) ;
  fflush(stdout) ;
  #endif


  if ( system( cmdline ) != 0) { // The command line "open PROGRAM MY_HTML_FILE" work's well except that the Windows console is display a mini moment at launching but disappear as fast.
  
    generate_message_dialog(window, _("Error launching readme !"), _("Sorry ! You can find the HTML readme into the installation folder\nof the application: surely \"/usr(/local)/share/gfast-copy\"."), GTK_MESSAGE_ERROR) ;
  
  }


  if (cmdline != NULL) {

    g_free(cmdline) ;

  }

  g_thread_exit(NULL) ;

  return ;
}

#endif


void launch_readme_html(GtkWidget *widget, GtkWidget *window) {

  /** Launch the README file to display it to the user through the GUI. **/

  if (! g_file_test(PATH_TO_README, G_FILE_TEST_EXISTS) ) {


    fprintf(stderr,"Error find readme file\n%s", error->message) ;

    g_clear_error(&error) ;

    return ;

  }






  #ifdef G_OS_UNIX

  #ifndef MAC_INTEGRATION

  // This doesn't work on MACOSX !
  GFile *g_file_readme = g_file_new_for_path(PATH_TO_README) ;

  gchar *readme_uri = g_file_get_uri(g_file_readme) ;


  GAppLaunchContext *app_launch_context = g_app_launch_context_new() ;

  g_app_info_launch_default_for_uri(readme_uri, app_launch_context, NULL) ;





  g_object_unref(app_launch_context) ;

  g_free(readme_uri) ;

  g_object_unref(g_file_readme) ;

  #else

  // Using Glib threads on Mac and Windows for displaying the readme without blocking the interface:
  // it's freaking because the Gio methods deosn't works on Mac and Windows !

  GThread *readme_display_thread = g_thread_try_new("launch_readme_thread",
                                                    (GThreadFunc) readme_thread,
                                                    window,
                                                    &error) ;

  if (error != NULL) {
  
    generate_message_dialog(window, _("Error launching readme !"), error->message, GTK_MESSAGE_ERROR) ;

    g_clear_error(&error) ;

  }

  g_thread_unref(readme_display_thread) ;

  #endif
  #endif





  #ifdef G_OS_WIN32

  // Using Glib threads on Mac and Windows for displaying the readme without blocking the interface:
  // it's freaking because the Gio methods deosn't works on Mac and Windows !

  GThread *readme_display_thread = g_thread_try_new("launch_readme_thread",
                                                    (GThreadFunc) readme_thread,
                                                    window,
                                                    &error) ;

  if (error != NULL) {

    generate_message_dialog(window, _("Error launching readme !"), error->message, GTK_MESSAGE_ERROR) ;
  
    g_clear_error(&error) ;

  }

  g_thread_unref(readme_display_thread) ;

  #endif



  return ;

}

void display_about_dialog(GtkWidget *widget, GtkWidget *window) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  GtkWidget *about_dialog = gtk_about_dialog_new() ;

  gtk_window_set_transient_for(GTK_WINDOW(about_dialog), GTK_WINDOW(window)) ;

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), PRGNAME) ;

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog),      VERSION)   ;

  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),    COPYRIGHT)   ;



  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),     _("gfast-copy - a graphical fast easy to use copy tool.\n" "A fast chunk single file copy program.") ) ;

  gchar *file_content ;

  g_file_get_contents(PATH_TO_LICENSE_TEXT, &file_content, NULL, NULL) ;

  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), file_content) ;

  g_free(file_content) ;

  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(about_dialog), TRUE);

  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), PRGWEBURL) ;

  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), PRGNAME " Website") ;

  const gchar *author[2] = {AUTHOR " " MAIL, NULL} ;

  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), author);

  gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(about_dialog), author);

  gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(about_dialog), author);

  #if 0
  gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(about_dialog), AUTHOR " " MAIL);
  #endif

  gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL) ;

  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), NULL);

  const gchar *thanks[2] = { _("Thanks to my beloved mother, my family and the doctors."), NULL} ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), _("Thanks"), thanks);

  const gchar *advice[2] = { _("Stay away from drugs: drugs destroy your brain and your life."), NULL} ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), _("Advice:"), advice);

  gtk_dialog_run(GTK_DIALOG(about_dialog)) ;

  gtk_widget_destroy(about_dialog) ;

  return ;

}
