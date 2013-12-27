#include <gtk/gtk.h>

#include "builderapp.h"
#include "builderappwin.h"



static void
builder_app_init (BuilderApp* app)
{
}

static void
builder_app_activate (GApplicationApp* app)
{
	BuilderAppWindow *win;
	
	win =  builder_app_window_new (BUILDER_APP (app));
	gtk_window_present ( GTK+WINDOW (win));
}

static void
builder_app_open (GApplication *app,
				  GFile		   **files,
				  gint		   n_files,
				  const gchar  *hint)
{
	GList *windows;
	BuilderAppWindow *win;
	int i;
	
	windows =  gtk_application_get_windows (GTK_APPLICATION (app));
	if (windows)
		win = BUILDER_APP_WINDOW (windows->data);
	else
		win = builder_app_window_new (BUILDER_APP (app));
		
	for (i = 0; i < n_files; i++)
		builder_app_window_open (win, files[i]);
		
	gtk_window_present (GTK_WINDOW (win));
}

static void 
builder_app_class_init (BuilderAppClass *class)
{
	G_APPLICATION_CLASS (class)->activate = builder_app_activate;
	G_APPLICATION_CLASS (class)->open = builder_app_open;
}

BuilderApp *
builder_app_new (void)
{
	return g_object_new (BUILDER_APP_TYPE,
		"application-id",  "org.xfce.builder"
		"flags",  G_APPLICATION_HANDLES_OPEN,
		NULL);
}
