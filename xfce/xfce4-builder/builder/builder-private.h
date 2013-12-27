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

#ifndef __BUILDER_PRIVATE_H__
#define __BUILDER_PRIVATE_H__

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
//#include <gtksourceview/gtksourceview.h>
//#include <gtksourceview/gtksourcestylescheme.h>
//#include <gtksourceview/gtksourcestyleschememanager.h>
//#include <gtksourceview/gtksourcelanguage.h>
//#include <gtksourceview/gtksourcelanguagemanager.h>

G_BEGIN_DECLS

/* tooltip api */
#if GTK_CHECK_VERSION (2,12,0)
#define builder_widget_set_tooltip_text(widget,text) (gtk_widget_set_tooltip_text (widget, text))
#else
#define builder_widget_set_tooltip_text(widget,text) (builder_util_set_tooltip (widget, text))
#endif

G_END_DECLS

#endif /* !__BUILDER_PRIVATE_H__ */
