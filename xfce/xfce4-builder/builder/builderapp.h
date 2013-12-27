#ifndef __BUILDER_APP__
#define __BUILDER_APP__

#include <gtk/gtk.h>

G_BEGIN_DECLS


struct BuilderApp
{
	GtkApplication parent;
};

struct BuilderAppClass
{
	GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(BuilderApp, builder_app, GTK_TYPE_APPLICATION);

BuilderApp * builder_app_new (void);


G_END_DECLS

#endif
