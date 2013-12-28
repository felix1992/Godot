/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <builder/builder-private.h>
#include <builder/builder-application.h>
//#include <builder/builder-window.h>

static void        builder_application_finalize                  (GObject                   *object);

struct _BuilderApplicationClass
{
  GObjectClass __parent__;
};

struct _BuilderApplication
{
  GObject  __parent__;

  /* internal list of all the opened windows */
  GSList  *windows;
};



G_DEFINE_TYPE (BuilderApplication, builder_application, G_TYPE_OBJECT);



static void
builder_application_class_init (BuilderApplicationClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = builder_application_finalize;
}



static void
builder_application_init (BuilderApplication *application)
{
#ifdef NEVER
  gchar *filename;

  /* check if we have a saved accel map */
  filename = mousepad_util_get_save_location (MOUSEPAD_ACCELS_RELPATH, FALSE);
  if (G_LIKELY (filename != NULL))
    {
      /* load the accel map */
      gtk_accel_map_load (filename);

      /* cleanup */
      g_free (filename);
    }
#endif
}



static void
builder_application_finalize (GObject *object)
{
  BuilderApplication *application = BUILDER_APPLICATION (object);
  GSList             *li;
  gchar              *filename;

#ifdef NEVER
  /* flush the history items of the replace dialog
   * this is a bit of an ugly place, but cleaning on a window close
   * isn't a good option eighter */
  builder_replace_dialog_history_clean ();

  /* save the current accel map */
  filename = mousepad_util_get_save_location (MOUSEPAD_ACCELS_RELPATH, TRUE);
  if (G_LIKELY (filename != NULL))
    {
      /* save the accel map */
      gtk_accel_map_save (filename);

      /* cleanup */
      g_free (filename);
    }

  /* destroy the windows if they are still opened */
  for (li = application->windows; li != NULL; li = li->next)
    {
      g_signal_handlers_disconnect_by_func (G_OBJECT (li->data), G_CALLBACK (mousepad_application_window_destroyed), application);
      gtk_widget_destroy (GTK_WIDGET (li->data));
    }

  /* cleanup the list of windows */
  g_slist_free (application->windows);
#endif

  (*G_OBJECT_CLASS (builder_application_parent_class)->finalize) (object);
}


static GtkWidget *
builder_application_create_window (BuilderApplication *application)
{
  GtkWidget *window;

  /* create a new window */
  window = builder_window_new ();

  /* hook up the new window */
  builder_application_take_window (application, GTK_WINDOW (window));

#ifdef NEVER
  /* connect signals */
  g_signal_connect (G_OBJECT (window), "new-window-with-document", G_CALLBACK (mousepad_application_new_window_with_document), application);
  g_signal_connect (G_OBJECT (window), "new-window", G_CALLBACK (mousepad_application_new_window), application);
#endif

  return window;
}


BuilderApplication*
builder_application_get (void)
{
  static BuilderApplication *application = NULL;

  if (G_UNLIKELY (application == NULL))
  {
      application = g_object_new (BUILDER_TYPE_APPLICATION, NULL);
      g_object_add_weak_pointer (G_OBJECT (application), (gpointer) &application);
  }
  else
  {
      g_object_ref (G_OBJECT (application));
  }

  return application;
}
