if PLATFORM_DARWIN
install-data-hook:
	- if `test ! -d "../MACOSX/gfast-copy_app/Contents/MacOS"` ; then $(MKDIR_P) "../MACOSX/gfast-copy_app/Contents/MacOS" ; fi
	- $(CP) $(DESTDIR)/$(bindir)/gfast-copy ../MACOSX/gfast-copy_app/Contents/MacOS
	- $(CP) -R ../MACOSX/gfast-copy_app /Applications/gfast-copy.app 

uninstall-hook:
	- $(RM) -rf /Applications/gfast-copy.app

endif


