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

#ifndef __BUILDER_WINDOW_H__
#define __BUILDER_WINDOW_H__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

G_BEGIN_DECLS

#define BUILDER_TYPE_WINDOW            (builder_window_get_type ())
#define BUILDER_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), BUILDER_TYPE_WINDOW, BuilderWindow))
#define BUILDER_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), BUILDER_TYPE_WINDOW, BuilderWindowClass))
#define BUILDER_IS_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BUILDER_TYPE_WINDOW))
#define BUILDER_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), BUILDER_TYPE_WINDOW))
#define BUILDER_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), BUILDER_TYPE_WINDOW, BuilderWindowClass))

typedef struct _BuilderWindow      BuilderWindow;

GType           builder_window_get_type         (void) G_GNUC_CONST;
GtkWidget      *builder_window_new              (void);
//GtkTreeModel *	xtm_process_window_get_model			(XtmProcessWindow *window);

G_END_DECLS

#endif /* !__BUILDER_WINDOW_H__ */
