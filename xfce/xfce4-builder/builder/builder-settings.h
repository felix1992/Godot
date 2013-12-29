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

#ifndef __BUILDER_SETTINGS_H__
#define __BUILDER_SETTINGS_H__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib-object.h>


G_BEGIN_DECLS

#define BUILDER_TYPE_SETTINGS			(builder_settings_get_type ())
#define BUILDER_SETTINGS(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), BUILDER_TYPE_SETTINGS, BuilderSettings))
#define BUILDER_SETTINGS_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), BUILDER_TYPE_SETTINGS, BuilderSettingsClass))
#define BUILDER_IS_SETTINGS(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), BUILDER_TYPE_SETTINGS))
#define BUILDER_IS_SETTINGS_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), BUILDER_TYPE_SETTINGS))
#define BUILDER_SETTINGS_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), BUILDER_TYPE_SETTINGS, BuilderSettingsClass))


typedef struct _BuilderSettings BuilderSettings;

GType			 builder_settings_get_type				(void);
BuilderSettings *builder_settings_get_default			();

typedef enum
{
	BUILDER_TOOLBAR_STYLE_DEFAULT,
	BUILDER_TOOLBAR_STYLE_SMALL,
	BUILDER_TOOLBAR_STYLE_LARGE,
	BUILDER_TOOLBAR_STYLE_TEXT,
} BuilderToolbarStyle;

GType builder_toolbar_style_get_type (void);
#define BUILDER_TYPE_TOOLBAR_STYLE (builder_toolbar_style_get_type ())

G_END_DECLS

#endif /* !__BUILDER_SETTINGS_H__ */
