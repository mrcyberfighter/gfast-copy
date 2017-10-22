

bin_PROGRAMS = fast-copy$(EXEEXT)

fast_copy_SOURCES = fast-copy.c

if PLATFORM_LINUX

fast_copy_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS)

fast_copy_LDADD = $(GLIB_LIBS) $(GIO_LIBS)

endif

if PLATFORM_WIN32

if NATIVE_WIN32

fast_copy_CFLAGS = -Wl,--export-all-symbols  -static-libgcc -static-libstdc++ $(GLIB_CFLAGS) $(GIO_CFLAGS)

fast_copy_LDADD = $(GLIB_LIBS) $(GIO_LIBS)

else

fast_copy_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS)

fast_copy_LDADD = $(GLIB_LIBS) $(GIO_LIBS)

endif

endif

if PLATFORM_DARWIN

fast_copy_CFLAGS = $(GLIB_CFLAGS) $(GIO_CFLAGS)

fast_copy_LDADD = $(GLIB_LIBS) $(GIO_LIBS)
         
endif


install-exec-hook:
if HAVE_MD5
	echo `$(MD5SUM) "$(DESTDIR)$(bindir)/fast-copy$(EXEEXT)"` > "$(DESTDIR)$(pkgdatadir)/fast-copy$(EXEEXT).md5"
endif
if HAVE_SHA1
	echo `$(SHA1SUM) "$(DESTDIR)$(bindir)/fast-copy$(EXEEXT)"` > "$(DESTDIR)$(pkgdatadir)/fast-copy$(EXEEXT).sha1"
endif
if HAVE_SHA256
	echo `$(SHA256SUM) "$(DESTDIR)$(bindir)/fast-copy$(EXEEXT)"` > "$(DESTDIR)$(pkgdatadir)/fast-copy$(EXEEXT).sha256"
endif
if HAVE_SHA512
	echo `$(SHA512SUM) "$(DESTDIR)$(bindir)/fast-copy$(EXEEXT)"` > "$(DESTDIR)$(pkgdatadir)/fast-copy$(EXEEXT).sha512"
endif



