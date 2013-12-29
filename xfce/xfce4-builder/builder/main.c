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

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "builder-window.h"
#include "builder-settings.h"

static BuilderSettings *settings;
static GtkWidget *window;
static GtkStatusIcon *status_icon;
//static XtmTaskManager *task_manager;

static void
status_icon_activated (void)
{
	if (!(GTK_WIDGET_VISIBLE (window)))
		gtk_widget_show (window);
	else
		gtk_widget_hide (window);
}

static void
status_icon_popup_menu (GtkStatusIcon *_status_icon, guint button, guint activate_time)
{
	static GtkWidget *menu = NULL;

	if (menu == NULL)
	{
		GtkWidget *mi;
		
		menu = gtk_menu_new ();
		mi = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
		g_signal_connect (mi, "activate", G_CALLBACK (gtk_main_quit), NULL);
		gtk_container_add (GTK_CONTAINER (menu), mi);
		gtk_widget_show_all (menu);
	}

	gtk_menu_popup (GTK_MENU (menu), NULL, NULL, gtk_status_icon_position_menu, _status_icon, button, activate_time);
}

static void
show_hide_status_icon (void)
{
	gboolean show_status_icon;
	g_object_get (settings, "show-status-icon", &show_status_icon, NULL);
	gtk_status_icon_set_visible (status_icon, show_status_icon);
}

static void
destroy_window (void)
{
	if (gtk_main_level () > 0)
		gtk_main_quit ();
}

static gboolean
delete_window (void)
{
	if (!gtk_status_icon_get_visible (status_icon))
	{
		gtk_main_quit ();
		return FALSE;
	}
	gtk_widget_hide (window);
	return TRUE;
}

int main (int argc, char *argv[])
{
#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	gtk_init (&argc, &argv);
	g_set_application_name (_("XFCE Builder"));

	settings = builder_settings_get_default ();

	status_icon = gtk_status_icon_new_from_icon_name ("utilities-system-monitor");
	show_hide_status_icon ();
	g_signal_connect (status_icon, "activate", G_CALLBACK (status_icon_activated), NULL);
	g_signal_connect (status_icon, "popup-menu", G_CALLBACK (status_icon_popup_menu), NULL);

	window = builder_window_new ();
	gtk_widget_show (window);

	g_signal_connect (settings, "notify::show-status-icon", G_CALLBACK (show_hide_status_icon), NULL);
	g_signal_connect (window, "destroy", G_CALLBACK (destroy_window), NULL);
	g_signal_connect (window, "delete-event", G_CALLBACK (delete_window), NULL);

	gtk_main ();

	g_object_unref (window);
	g_object_unref (status_icon);
	g_object_unref (settings);

	return 0;
}
