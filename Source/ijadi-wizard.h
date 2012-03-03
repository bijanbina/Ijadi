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
 * Info: Stylish wizard for creating new project
 */

#ifndef _IJADI_WIZARD_H_
#define _IJADI_WIZARD_H_

#include "ijadi-define.h"
#include <glib-object.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define IJADI_TYPE_WIZARD             (ijadi_wizard_get_type ())
#define IJADI_WIZARD(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), IJADI_TYPE_WIZARD, IjadiWizard))
#define IJADI_WIZARD_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), IJADI_TYPE_WIZARD, IjadiWizardClass))
#define IJADI_IS_WIZARD(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IJADI_TYPE_WIZARD))
#define IJADI_IS_WIZARD_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), IJADI_TYPE_WIZARD))
#define IJADI_WIZARD_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), IJADI_TYPE_WIZARD, IjadiWizardClass))

typedef struct _IjadiWizardClass IjadiWizardClass;
typedef struct _IjadiWizard IjadiWizard;

struct _IjadiWizardClass
{
	GtkWindowClass parent_class;

	/* Signals */
	void (* close) (IjadiWizard *self);
};

struct _IjadiWizard
{
	GtkWindow parent_instance;
};

GType 					ijadi_wizard_get_type (void) G_GNUC_CONST;
IjadiWizard * 		Ijadi_wizard_new();
void						ijadi_wizard_start (IjadiWizard *);

G_END_DECLS

#endif /* _IJADI_WIZARD_H_ */
