SUBDIRS = . src fast-copy data man_fast-copy man_gfast-copy texi desktop doc MACOSX

nobase_pkgdata_DATA = ./src/callbacks.c \
                      ./src/callbacks.h \
                      ./src/configuration.c \
                      ./src/configuration.h \
                      ./src/copy_files.c \
                      ./src/copy_files.h \
                      ./src/documentation.c \
                      ./src/documentation.h \
                      ./src/global_vars.c \
                      ./src/global_vars.h \
                      ./src/GtkSmartIconButton.c \
                      ./src/GtkSmartIconButton.h \
                      ./src/GtkSmartMenuItem.c \
                      ./src/GtkSmartMenuItem.h \
                      ./src/headers/includes.h \
                      ./src/headers/defines.h \
                      ./src/main.c \
                      ./fast-copy/fast-copy.c \
                      ./Makefile.mk


EXTRA_DIST =  ./Makefile.mk \
              ./user_info.sh \
              ./MACOSX/gfast-copy_app/Contents/Info.plist \
              ./MACOSX/gfast-copy_app/Contents/Resources/gfast-copy.icns \
              ./WHOAMI \
              ./TODO \
              ./HACKME \
              ./CONTRIBUTORS \
              ./whoami.info

install-data-hook:
	$(MV) "$(DESTDIR)$(pkgdatadir)/Makefile.mk" "$(DESTDIR)$(pkgdatadir)/Makefile"
	$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/bin"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/src"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/bin"
	$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/config"
	$(CHMOD) a+rwx "$(DESTDIR)$(pkgdatadir)/config"
