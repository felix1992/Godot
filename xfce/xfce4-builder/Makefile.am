SUBDIRS =							\
	po								\
	builder

desktopdir = $(datadir)/applications
desktop_in_files = xfce4-builder.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

ChangeLog: Makefile
	ChangeLog-git.sh > $(srcdir)/ChangeLog || touch $(srcdir)/ChangeLog

EXTRA_DIST =								\
	intltool-extract.in						\
	intltool-merge.in						\
	intltool-update.in						\
	$(desktop_in_files)
	
DISTCLEANFILES =							\
	intltool-extract						\
	intltool-merge							\
	intltool-update							\
	$(desktop_DATA)

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
