/* --------------------------------------- Besm Allah rahman rahim   ----------------------------------------------------
 *
 * Copyright (C) 2011 AllahSoft Std.
 *
 * Bijan Binaee   <bijanbina@gmail.com>             
 * Reza Faramarzi <faramarzi.reza14@gmail.com>
 *
*  ijadi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Info: Manage running window ands set global value 
 */

#ifndef _IJADI_APPLICATION_H_
#define _IJADI_APPLICATION_H_

#include <glib-object.h>
#include "ijadi-gui.h"
G_BEGIN_DECLS

#define IJADI_TYPE_APPLICATION             (ijadi_application_get_type ())
#define IJADI_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), IJADI_TYPE_APPLICATION, IjadiApplication))
#define IJADI_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), IJADI_TYPE_APPLICATION, IjadiApplicationClass))
#define IJADI_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IJADI_TYPE_APPLICATION))
#define IJADI_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), IJADI_TYPE_APPLICATION))
#define IJADI_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), IJADI_TYPE_APPLICATION, IjadiApplicationClass))

#define IJADI_APP				(ijadi_application_get_instance ())

typedef struct _IjadiApplicationClass IjadiApplicationClass;
typedef struct _IjadiApplication IjadiApplication;

struct _IjadiApplicationClass
{
	GtkApplicationClass parent_class;
};

struct _IjadiApplication
{
	GtkApplication parent_instance;
};

GType						ijadi_application_get_type (void) G_GNUC_CONST;
IjadiApplication*   ijadi_application_get_instance();
gboolean    			   ijadi_application_open_window         (IjadiApplication* application);
G_END_DECLS

#endif /* _IJADI_APPLICATION_H_ */
