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
 * Info: this file is for creating main window of the ijadi project
 */

#ifndef _IJADI_GUI_H_
#define _IJADI_GUI_H_

#include <glib-object.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define IJADI_TYPE_GUI             (ijadi_gui_get_type ())
#define IJADI_GUI(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), IJADI_TYPE_GUI, IjadiGui))
#define IJADI_GUI_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), IJADI_TYPE_GUI, IjadiGuiClass))
#define IJADI_IS_GUI(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IJADI_TYPE_GUI))
#define IJADI_IS_GUI_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), IJADI_TYPE_GUI))
#define IJADI_GUI_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), IJADI_TYPE_GUI, IjadiGuiClass))

/* This is exactly the style information you've been looking for */
#define GTK_STYLE_PROVIDER_PRIORITY_FORCE G_MAXUINT

typedef struct _IjadiGuiClass IjadiGuiClass;
typedef struct _IjadiGui IjadiGui;


struct _IjadiGuiClass
{
	GtkWindowClass parent_class;
};

struct _IjadiGui
{
	GtkWindow parent_instance;
};

GType ijadi_gui_get_type (void) G_GNUC_CONST;
void				 ijadi_gui_create_window (IjadiGui *);
void				ijadi_gui_start (IjadiGui *);
IjadiGui * 		Ijadi_gui_new();


G_END_DECLS

#endif /* _IJADI_GUI_H_ */
