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

#include "ijadi-application.h"

#define IJADI_APPLICATION_NAME "allahsoft.ijadi"

G_DEFINE_TYPE (IjadiApplication, ijadi_application, GTK_TYPE_APPLICATION);

static void
ijadi_application_init (IjadiApplication *object)
{
	/* TODO: Add initialization code here */
}

static void
ijadi_application_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (ijadi_application_parent_class)->finalize (object);
}

static void
ijadi_application_activate (GApplication *application)
{
	ijadi_application_open_window (IJADI_APPLICATION (application));
}

static void
ijadi_application_class_init (IjadiApplicationClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GApplicationClass* parent_class = G_APPLICATION_CLASS (klass);

	object_class->finalize = ijadi_application_finalize;

	parent_class->activate = ijadi_application_activate;
}

/**
 * eog_application_open_window:
 * @application: An #EogApplication.
 * @timestamp: The timestamp of the user interaction which triggered this call
 * (see gtk_window_present_with_time()).
 * @flags: A set of #EogStartupFlags influencing a new windows' state.
 * @error: Return location for a #GError, or NULL to ignore errors.
 *
 * Opens and presents an empty #EogWindow to the user. If there is
 * an empty window already open, this will be used. Otherwise, a
 * new one will be instantiated.
 *
 * Returns: %FALSE if @application is invalid, %TRUE otherwise
 **/
gboolean
ijadi_application_open_window         (IjadiApplication* application)
{
	IjadiGui *gui  = Ijadi_gui_new ();
	
	ijadi_gui_start(gui);
gtk_window_set_application (GTK_WINDOW(gui), GTK_APPLICATION (application));
	return TRUE;
}

/**
 * eog_application_get_instance:
 *
 * Returns a singleton instance of #EogApplication currently running.
 * If not running yet, it will create one.
 *
 * Returns: (transfer none): a running #EogApplication.
 **/
IjadiApplication *
ijadi_application_get_instance (void)
{
	static IjadiApplication *instance;

	if (!instance) {
		instance = IJADI_APPLICATION (g_object_new (IJADI_TYPE_APPLICATION,
							  "application-id", "allahsoft.ijadi",
							  NULL));
	}

	return instance;
}






