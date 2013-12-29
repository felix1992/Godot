NULL = 

INCLUDES =									\
	-I$(top_srcdir)							\
	-DG_LOG_DOMAIN=\"xfce4-builder\"		\
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\"

bin_PROGRAMS =								\
	xfce4-builder

xfce4_builder_CFLAGS =						\
	$(GTK_CFLAGS)							\
	$(CAIRO_CFLAGS)							\
	$(WNCK_CFLAGS)							\
	$(GKSU_CFLAGS)							\
	$(NULL)

xfce4_builder_LDADD = 						\
	$(GTK_LIBS)								\
	$(CAIRO_LIBS)							\
	$(WNCK_LIBS)							\
	$(GKSU_LIBS)							\
	$(NULL)

xfce4_builder_SOURCES =							\
	builder-window_ui.h							\
	builder-window.c		builder-window.h	\
	builder-settings.c		builder-settings.h	\
	settings-dialog_ui.h						\
	settings-dialog.c		settings-dialog.h	\
	main.c			
	$(NULL)

if MAINTAINER_MODE
BUILT_SOURCES = builder-window_ui.h settings-dialog_ui.h
process-window_ui.h: builder-window.ui
	$(AM_V_GEN) exo-csource --static --strip-comments --strip-content --name=builder_window_ui $< >$@
settings-dialog_ui.h: settings-dialog.ui
	$(AM_V_GEN) exo-csource --static --strip-comments --strip-content --name=settings_dialog_ui $< >$@
endif

EXTRA_DIST = builder-window.ui settings-dialog.ui
