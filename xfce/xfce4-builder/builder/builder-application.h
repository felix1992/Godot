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

#ifndef __BUILDER_APPLICATION_H__
#define __BUILDER_APPLICATION_H__

//G_BEGIN_DECLS

typedef struct _BuilderApplicationClass BuilderApplicationClass;
typedef struct _BuilderApplication      BuilderApplication;

#define BUILDER_TYPE_APPLICATION            (builder_application_get_type ())
#define BUILDER_APPLICATION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), BUILDER_TYPE_APPLICATION, BuilderApplication))
#define BUILDER_APPLICATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), BUILDER_TYPE_APPLICATION, BuilderApplicationClass))
#define BUILDER_IS_APPLICATION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BUILDER_TYPE_APPLICATION))
#define BUILDER_IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BUILDER_TYPE_APPLICATION))
#define BUILDER_APPLICATION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), BUILDER_TYPE_APPLICATION, BuilderApplicationClass))

GType                builder_application_get_type               (void) G_GNUC_CONST;

BuilderApplication  *builder_application_get                    (void);

gboolean             builder_application_has_windows            (BuilderApplication  *application);

void                 builder_application_take_window            (BuilderApplication  *application,
                                                                 GtkWindow           *window);

void                 builder_application_new_window_with_files  (BuilderApplication  *application,
                                                                 GdkScreen           *screen,
                                                                 const gchar         *working_directory);

G_END_DECLS

#endif /* !__BUILDER_APPLICATION_H__ */
