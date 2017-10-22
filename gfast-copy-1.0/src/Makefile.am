AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = gfast-copy$(EXEEXT)

gfast_copy_SOURCES =  callbacks.c           \
                      configuration.c       \
                      copy_files.c          \
                      documentation.c       \
                      global_vars.c         \
                      GtkSmartIconButton.c  \
                      GtkSmartMenuItem.c    \
                      main.c

EXTRA_DIST = ./*.h \
             ./headers/*.h



if PLATFORM_LINUX

  gfast_copy_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\"

  gfast_copy_CFLAGS = -Wno-missing-field-initializers -Wno-unused-parameter $(GTK_CFLAGS)

  gfast_copy_LDADD = $(GTK_LIBS)

endif

if PLATFORM_WIN32

if NATIVE_WIN32

gfast_copy_CFLAGS = -Wno-missing-field-initializers -Wno-unused-parameter -mwindows -Wl,--export-all-symbols  -static-libgcc -static-libstdc++ $(GTK_CFLAGS)

gfast_copy_LDADD = $(GTK_LIBS)

else

gfast_copy_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\"

gfast_copy_CFLAGS = -Wno-missing-field-initializers -Wno-unused-parameter $(GTK_CFLAGS)

gfast_copy_LDADD = $(GTK_LIBS)

endif

endif

if PLATFORM_DARWIN

gfast_copy_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\"

gfast_copy_CFLAGS = -Wno-missing-field-initializers -Wno-unused-parameter $(GTK_CFLAGS) $(GTK_MAC_INTEGRATION_CFLAGS)

gfast_copy_LDADD = $(GTK_LIBS) $(GTK_MAC_INTEGRATION_LIBS)

endif

install-exec-hook:
if HAVE_MD5
	echo `$(MD5SUM) $(DESTDIR)$(bindir)/$(PACKAGE)$(EXEEXT)` > $(pkgdatadir)/$(PACKAGE).md5
endif
if HAVE_SHA1
	echo `$(SHA1SUM) $(DESTDIR)$(bindir)/$(PACKAGE)$(EXEEXT)` > $(pkgdatadir)/$(PACKAGE).sha1
endif
if HAVE_SHA256
	echo `$(SHA256SUM) $(DESTDIR)$(bindir)/$(PACKAGE)$(EXEEXT)` > $(pkgdatadir)/$(PACKAGE).sha256
endif
if HAVE_SHA512
	echo `$(SHA512SUM) $(DESTDIR)$(bindir)/$(PACKAGE)$(EXEEXT)` > $(pkgdatadir)/$(PACKAGE).sha512
endif

