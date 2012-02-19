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

#include "ijadi-wizard.h"

enum
{
	CLOSE,

	LAST_SIGNAL
};


static guint wizard_signals[LAST_SIGNAL] = { 0 };

G_DEFINE_TYPE (IjadiWizard, ijadi_wizard, GTK_TYPE_WINDOW);

static void
ijadi_wizard_init (IjadiWizard *object)
{
	/* TODO: Add initialization code here */
}

static void
ijadi_wizard_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (ijadi_wizard_parent_class)->finalize (object);
}

static void
ijadi_wizard_close (IjadiWizard *self)
{
	/* TODO: Add default signal handler implementation here */
}

static void
ijadi_wizard_class_init (IjadiWizardClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GtkWindowClass* parent_class = GTK_WINDOW_CLASS (klass);

	object_class->finalize = ijadi_wizard_finalize;

	klass->close = ijadi_wizard_close;

	wizard_signals[CLOSE] =
		g_signal_new ("close",
		              G_OBJECT_CLASS_TYPE (klass),
		              G_SIGNAL_ACTION,
		              G_STRUCT_OFFSET (IjadiWizardClass, close),
		              NULL, NULL,NULL
		              ,G_TYPE_NONE, 0);
}

