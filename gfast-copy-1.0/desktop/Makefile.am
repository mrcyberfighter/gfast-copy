###

DESKTOP_DIR = $(prefix)/share/applications

DESKTOP_FILE_NAME_BASE_ON_ID = gfast.copy.mrcyberfighter.desktop


update-desktop:
if DESTOP_FILE_UTILS
	- $(DESKTOP_FILE_INSTALL) --rebuild-mime-info-cache "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
else if XDG_UTILS
	- $(XDG_DESKTOP_MENU) install --novendor --mode system "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	- $(XDG_DESKTOP_MENU) forceupdate --mode system
else if UPDATE_DESKTOP_DATABASE_UTILS
	- $(UPDATE_DESKTOP_DATABASE) "$(DESTDIR)$(DESKTOP_DIR)"
endif


unupdate-desktop:
if DESTOP_FILE_UTILS
	- $(DESKTOP_FILE_INSTALL) --rebuild-mime-info-cache
else if XDG_UTILS
	- $(XDG_DESKTOP_MENU)  uninstall --novendor --mode system "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	- $(XDG_DESKTOP_MENU) forceupdate --mode system
else if UPDATE_DESKTOP_DATABASE_UTILS
	- $(UPDATE_DESKTOP_DATABASE) "$(DESTDIR)$(DESKTOP_DIR)"
endif


.PHONY: desktop update-desktop unupdate-desktop

# it were good to use a tool like xdg-desktop-icon or desktop-file-install for installing the *.desktop file.
desktop:
	if `test ! -d "$(DESTDIR)$(DESKTOP_DIR)"` ; then $(MKDIR_P) "$(DESTDIR)$(DESKTOP_DIR)" ; fi
	@echo "[Desktop Entry]"  > "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Name=$(PACKAGE)"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Version=$(VERSION)"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "GenericName=$(PACKAGE)"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Comment=A graphical easy to use fast chunk copy program." >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Exec=$(bindir)/$(PACKAGE) %u"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Icon=$(pkgdatadir)/images/gfast-copy_icon.png"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Terminal=false"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "X-MultipleArgs=false"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "StartupNotify=true"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Type=Application"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "MimeType="  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Keywords=Fast;Copy;Chunk;Video;Files;"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	@echo "Categories=Application;System;GNOME;GTK;"  >> "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"

install-data-hook:
	- $(MAKE) desktop
	- $(MAKE) update-desktop


uninstall-hook:
	- if `test -d "$(DESTDIR)$(pkgdatadir)"` ; then $(RM) -rf "$(DESTDIR)$(pkgdatadir)" ; fi
	- $(RM) -f "$(DESTDIR)$(DESKTOP_DIR)/$(DESKTOP_FILE_NAME_BASE_ON_ID)"
	- $(MAKE) unupdate-desktop



