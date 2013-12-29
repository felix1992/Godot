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

#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define BUILDER_TYPE_SETTINGS_DIALOG			(builder_settings_dialog_get_type ())
#define BUILDER_SETTINGS_DIALOG(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), BUILDER_TYPE_SETTINGS_DIALOG, BuilderSettingsDialog))
#define BUILDER_SETTINGS_DIALOG_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), BUILDER_TYPE_SETTINGS_DIALOG, BuilderSettingsDialogClass))
#define BUILDER_IS_SETTINGS_DIALOG(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), BUILDER_TYPE_SETTINGS_DIALOG))
#define BUILDER_IS_SETTINGS_DIALOG_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), BUILDER_TYPE_SETTINGS_DIALOG))
#define BUILDER_SETTINGS_DIALOG_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), BUILDER_TYPE_SETTINGS_DIALOG, BuilderSettingsDialogClass))

typedef struct _BuilderSettingsDialog BuilderSettingsDialog;

GType		 builder_settings_dialog_get_type			(void);
GtkWidget	*builder_settings_dialog_new				(GtkWindow *parent_window);
void		 builder_settings_dialog_run				(BuilderSettingsDialog *dialog);

G_END_DECLS

#endif /* !SETTINGS_DIALOG_H */
