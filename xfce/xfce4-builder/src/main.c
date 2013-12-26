#include <gtk/gtk.h>
#include <builder-app.h>

int
main (int argc, char *argv[])
{
	return g_application_run (G_APPLICATION (builder_app_new ()), argc, argv);
}


/*
static void
print_hello (GtkWidget *widget,
			 gpointer data)
{
	g_print ("Hello world\n");
}

int
main(int   argc,
     char *argv[])
{
	GtkBuilder *builder;
	GObject *window;
	GObject *button;
	
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "builder.ui", NULL);
	
	window = gtk_builder_get_object (builder, "window");
	g_signal_connect ( GTK_WINDOW(window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	button = gtk_builder_get_object (builder, "button1");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	
	button = gtk_builder_get_object (builder, "button2");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	
	button = gtk_builder_get_object (builder, "quit");
	g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
	
	gtk_main ();
	
	return 0;
}
*/
