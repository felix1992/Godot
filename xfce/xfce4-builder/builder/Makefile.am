NULL = 

INCLUDES =								\
	-I$(top_srcdir)							\
	-DG_LOG_DOMAIN=\"xfce4-builder\"				\
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
	$(GTK_LIBS)							\
	$(CAIRO_LIBS)							\
	$(WNCK_LIBS)							\
	$(GKSU_LIBS)							\
	$(NULL)

xfce4_builder_SOURCES =						\
	main.c								
	$(NULL)


