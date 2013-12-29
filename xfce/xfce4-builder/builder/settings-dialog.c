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

#include <glib-object.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "builder-settings.h"
#include "settings-dialog.h"
#include "settings-dialog_ui.h"



typedef struct _BuilderSettingsDialogClass BuilderSettingsDialogClass;
struct _BuilderSettingsDialogClass
{
	GtkWidgetClass		parent_class;
};
struct _BuilderSettingsDialog
{
	GtkWidget		 parent;
	/*<private>*/
	GtkWidget		*window;
	BuilderSettings	*settings;
};
G_DEFINE_TYPE (BuilderSettingsDialog, builder_settings_dialog, GTK_TYPE_WIDGET)

static void	builder_settings_dialog_finalize	(GObject *object);
static void	builder_settings_dialog_show		(GtkWidget *widget);
static void	builder_settings_dialog_hide		(GtkWidget *widget);



static void
builder_settings_dialog_class_init (BuilderSettingsDialogClass *klass)
{
	GObjectClass *class;
	GtkWidgetClass *widget_class;
	builder_settings_dialog_parent_class = g_type_class_peek_parent (klass);
	class = G_OBJECT_CLASS (klass);
	class->finalize = builder_settings_dialog_finalize;
	widget_class = GTK_WIDGET_CLASS (klass);
	widget_class->show = builder_settings_dialog_show;
	widget_class->hide = builder_settings_dialog_hide;
}

static void
button_toggled (GtkToggleButton *button, BuilderSettings *settings)
{
	gboolean active = gtk_toggle_button_get_active (button);
	gchar *setting_name = g_object_get_data (G_OBJECT (button), "setting-name");
	g_object_set (settings, setting_name, active, NULL);
}

static void
builder_bind_toggle_button (GtkBuilder *builder, gchar *widget_name, BuilderSettings *settings, gchar *setting_name)
{
	gboolean active;
	GtkWidget *button;

	g_object_get (settings, setting_name, &active, NULL);

	button = GTK_WIDGET (gtk_builder_get_object (builder, widget_name));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), active);
	g_object_set_data (G_OBJECT (button), "setting-name", setting_name);
	g_signal_connect (button, "toggled", G_CALLBACK (button_toggled), settings);
}
/*
static void
combobox_changed (GtkComboBox *combobox, XtmSettings *settings)
{
	guint active = gtk_combo_box_get_active (combobox);
	gchar *setting_name = g_object_get_data (G_OBJECT (combobox), "setting-name");
	g_object_set (settings, setting_name, active, NULL);
}
*/
static void
builder_settings_dialog_init (BuilderSettingsDialog *dialog)
{
	GtkBuilder *builder;

	g_object_ref_sink (dialog);

	dialog->settings = builder_settings_get_default ();

	builder = gtk_builder_new ();
	gtk_builder_add_from_string (builder, settings_dialog_ui, settings_dialog_ui_length, NULL);

	dialog->window = GTK_WIDGET (gtk_builder_get_object (builder, "settings-dialog"));

#ifndef HAVE_WNCK
	gtk_widget_hide (GTK_WIDGET (gtk_builder_get_object (builder, "button-show-application-icons")));
#endif

//	builder_bind_toggle_button (builder, "button-show-application-icons", dialog->settings, "show-application-icons");
//	builder_bind_toggle_button (builder, "button-full-command-line", dialog->settings, "full-command-line");
//	builder_bind_toggle_button (builder, "button-more-precision", dialog->settings, "more-precision");
//	builder_bind_toggle_button (builder, "button-monitor-paint-box", dialog->settings, "monitor-paint-box");
//	builder_bind_toggle_button (builder, "button-prompt-terminate-task", dialog->settings, "prompt-terminate-task");
//	builder_bind_toggle_button (builder, "button-show-status-icon", dialog->settings, "show-status-icon");

/*	{
		guint n;
		GEnumClass *klass;
		GtkWidget *box;
		GtkWidget *combobox;
		XtmToolbarStyle toolbar_style;

		box = GTK_WIDGET (gtk_builder_get_object (builder, "hbox-toolbar-style"));
		combobox = gtk_combo_box_new_text ();
		gtk_box_pack_start (GTK_BOX (box), combobox, FALSE, FALSE, 0);
		gtk_widget_show (combobox);

		klass = g_type_class_ref (XTM_TYPE_TOOLBAR_STYLE);
		for (n = 0; n < klass->n_values; ++n)
			gtk_combo_box_append_text (GTK_COMBO_BOX (combobox), _(klass->values[n].value_nick));
		g_type_class_unref (klass);

		g_object_get (dialog->settings, "toolbar-style", &toolbar_style, NULL);
		g_object_set_data (G_OBJECT (combobox), "setting-name", "toolbar-style");
		gtk_combo_box_set_active (GTK_COMBO_BOX (combobox), toolbar_style);
		g_signal_connect (combobox, "changed", G_CALLBACK (combobox_changed), dialog->settings);
	}*/

	g_object_unref (builder);
}

static void
builder_settings_dialog_finalize (GObject *object)
{
	BuilderSettingsDialog *dialog = BUILDER_SETTINGS_DIALOG (object);
	gtk_widget_destroy (dialog->window);
	g_object_unref (dialog->settings);
}



GtkWidget *
builder_settings_dialog_new (GtkWindow *parent_window)
{
	GtkWidget *dialog = g_object_new (BUILDER_TYPE_SETTINGS_DIALOG, NULL);
	gtk_window_set_transient_for (GTK_WINDOW (BUILDER_SETTINGS_DIALOG (dialog)->window), parent_window);
	return dialog;
}

static void
builder_settings_dialog_show (GtkWidget *widget)
{
	g_return_if_fail (GTK_IS_WIDGET (widget));
	g_return_if_fail (GTK_IS_WIDGET (BUILDER_SETTINGS_DIALOG (widget)->window));
	gtk_widget_show (BUILDER_SETTINGS_DIALOG (widget)->window);
	gtk_window_present (GTK_WINDOW (BUILDER_SETTINGS_DIALOG (widget)->window));
	GTK_WIDGET_SET_FLAGS (widget, GTK_VISIBLE);
}

static void
builder_settings_dialog_hide (GtkWidget *widget)
{
	gint winx, winy;
	g_return_if_fail (GTK_IS_WIDGET (widget));
	if (!GTK_IS_WIDGET (BUILDER_SETTINGS_DIALOG (widget)->window))
		return;
	gtk_window_get_position (GTK_WINDOW (BUILDER_SETTINGS_DIALOG (widget)->window), &winx, &winy);
	gtk_widget_hide (BUILDER_SETTINGS_DIALOG (widget)->window);
	gtk_window_move (GTK_WINDOW (BUILDER_SETTINGS_DIALOG (widget)->window), winx, winy);
	GTK_WIDGET_UNSET_FLAGS (widget, GTK_VISIBLE);
}

void
builder_settings_dialog_run (BuilderSettingsDialog *dialog)
{
	gtk_dialog_run (GTK_DIALOG (dialog->window));
}
