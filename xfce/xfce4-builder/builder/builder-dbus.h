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

#ifndef __BUILDER_DBUS_H__
#define __BUILDER_DBUS_H__

G_BEGIN_DECLS

typedef struct _BuilderDBusServiceClass BuilderDBusServiceClass;
typedef struct _BuilderDBusService      BuilderDBusService;

#define BUILDER_TYPE_DBUS_SERVICE            (builder_dbus_service_get_type ())
#define BUILDER_DBUS_SERVICE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), BUILDER_TYPE_DBUS_SERVICE, BuilderDBusService))
#define BUILDER_DBUS_SERVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), BUILDER_TYPE_DBUS_SERVICE, BuilderDBusServiceClass))
#define BUILDER_IS_DBUS_SERVICE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BUILDER_TYPE_DBUS_SERVICE))
#define BUILDER_IS_DBUS_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BUILDER_TYPE_DBUS_BRIGDE))
#define BUILDER_DBUS_SERVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), BUILDER_TYPE_DBUS_SERVICE, BuilderDBusServiceClass))

GType     builder_dbus_service_get_type    (void) G_GNUC_CONST;

gboolean  builder_dbus_client_terminate    (GError      **error);

gboolean  builder_dbus_client_launch_files (const gchar  *working_directory,
                                            GError      **error);

G_END_DECLS

#endif /* !__BUILDER_DBUS_H__ */
