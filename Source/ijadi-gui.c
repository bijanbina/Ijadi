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

#include "ijadi-gui.h"
#include "ijadi-application.h"
#include "ijadi-wizard.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>


typedef struct _IjadiGuiPrivate IjadiGuiPrivate;
struct _IjadiGuiPrivate
{
	GtkWidget* btn_import_url;
	GtkWidget* btn_new_project;
	GtkWidget* btn_open_project;
	GtkWidget* btn_import_project;
	GtkWidget* img_import_url;
	GtkWidget* img_new_project;
	GtkWidget* img_open_project;
	GtkWidget* img_import_project;
	GtkWidget* btn_urlimport_project;
	GtkWidget *img_welcome;
	GtkWidget* box_button_1;
	GtkWidget* box_button_2;
	GtkWidget* box_main;
	GtkWidget* menu_bar;
	GtkWidget* toolbar;
	IjadiWizard *wizard;
};

#define IJADI_GUI_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), IJADI_TYPE_GUI, IjadiGuiPrivate))

enum
{
	PROP_0,

	PROP_WINDOW
};

G_DEFINE_TYPE (IjadiGui, ijadi_gui, GTK_TYPE_WINDOW);

static void
ijadi_gui_init (IjadiGui *object)
{
	/* TODO: Add initialization code here */
}

static void
ijadi_gui_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (ijadi_gui_parent_class)->finalize (object);
}

static void
ijadi_gui_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (IJADI_IS_GUI (object));

	switch (prop_id)
	{
	case PROP_WINDOW:
		/* TODO: Add setter for "window" property here */
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
ijadi_gui_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (IJADI_IS_GUI (object));

	switch (prop_id)
	{
	case PROP_WINDOW:
		/* TODO: Add getter for "window" property here */
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
ijadi_gui_class_init (IjadiGuiClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (IjadiGuiPrivate));

	object_class->finalize = ijadi_gui_finalize;
	object_class->set_property = ijadi_gui_set_property;
	object_class->get_property = ijadi_gui_get_property;

	g_object_class_install_property (object_class,
	                                 PROP_WINDOW,
	                                 g_param_spec_object ("window",
	                                                      "window",
	                                                      "main window of the ijadi",
	                                                      GTK_TYPE_WIDGET,
	                                                      G_PARAM_READABLE));
}
/********************************** CALLBACK FUNCTION **************************************/
void
ijadi_gui_btn_new_project_clicked (GtkButton *button, gpointer user_data)
{
	IjadiGui *object = IJADI_GUI(user_data);
	IjadiGuiPrivate *priv = IJADI_GUI_PRIVATE(object);
	priv->wizard = Ijadi_wizard_new ();
	ijadi_wizard_start (priv->wizard);
}

void
ijadi_gui_btn_update_source_clicked (GtkButton *button,gpointer  user_data)
{
	IjadiGui *object = IJADI_GUI(user_data);
	IjadiGuiPrivate *priv = IJADI_GUI_PRIVATE(object);
	printf (LOCAL_RESOURCES"/Hello World Project\n");
}

void
ijadi_gui_tool_new_clicked ()
{
	printf ("Hello World Project\n");
}
/*********************************** PRIVATE FUNCTION ****************************************/
//! create action (use to create toolbar item and also add them to toolbar)
/*!
    \param toolbar object add to it
    \param name name of the action and also display it in tooltip
    \param icon_path Address of the icon (It can be NULL)
*/
GtkAction*
ijadi_gui_create_action_menu (GtkWidget *menu,const gchar *name)
{
	GtkAction *action = gtk_action_new(name, name,name,NULL);
	GtkWidget *menuItem = gtk_action_create_menu_item(action);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuItem);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem), NULL);
	return action;
}

GtkWidget *
ijadi_gui_create_menu_file ()
{
    GtkWidget *menu;
    menu = gtk_menu_new ();

    GtkAction *menu_file_new = ijadi_gui_create_action_menu (menu,"New");
    GtkAction *menu_file_open = ijadi_gui_create_action_menu (menu,"Open");
    GtkAction *menu_file_quit = ijadi_gui_create_action_menu (menu,"Quit");

    return menu;
}

GtkWidget*
ijadi_gui_create_menubar ()
{
	GtkWidget *menubar;
	GtkWidget *menuitem;
	GtkWidget *menu;

	menubar = gtk_menu_bar_new ();
	menuitem = gtk_menu_item_new_with_label ("File");
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), menuitem);
	menu = ijadi_gui_create_menu_file();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

  return menubar;
}
//! create action (use to create toolbar item and also add them to toolbar)
/*!
    \param toolbar object add to it
    \param name name of the action and also display it in tooltip
    \param icon_path Address of the icon (It can be NULL)
*/
GtkAction*
ijadi_gui_create_action (GtkWidget *toolbar,const gchar *name, const gchar *icon_path)
{
	GIcon *icon = g_icon_new_for_string (icon_path,NULL);
	GtkAction *action = gtk_action_new(name, name,name,NULL);
	gtk_action_set_gicon (action,icon);
	GtkWidget *toolItem = gtk_action_create_tool_item(action);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolItem),-1);
	return action;
}
//! create action (use to create toolbar item and also add them to toolbar) forstock icon(Like new open and etc)
/*!
    \param toolbar object add to it
    \param name name of the action and also display it in tooltip
    \param icon_path Address of the icon (It can be NULL)
*/
GtkAction*
ijadi_gui_create_action_s (GtkWidget *toolbar,const gchar *name, const gchar *stock_id)
{
	GtkAction *action = gtk_action_new(name, name,name,stock_id);
	GtkWidget *toolItem = gtk_action_create_tool_item(action);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolItem),-1);
	return action;
}

GtkWidget*
ijadi_gui_create_toolbar ()
{
	GtkWidget *toolbar;

	toolbar = gtk_toolbar_new();
	gtk_style_context_add_class (gtk_widget_get_style_context (toolbar),GTK_STYLE_CLASS_PRIMARY_TOOLBAR);
	
	GtkAction *act_new = ijadi_gui_create_action_s(toolbar,"New",GTK_STOCK_NEW);
	GtkAction *act_open = ijadi_gui_create_action_s(toolbar,"Open",GTK_STOCK_OPEN);
	GtkAction *act_save = ijadi_gui_create_action_s(toolbar,"Save",GTK_STOCK_SAVE);
	GtkAction *act_home = ijadi_gui_create_action(toolbar,"Compile",GTK_STOCK_EXECUTE);
	
	g_signal_connect (act_new, "activate", G_CALLBACK (ijadi_gui_tool_new_clicked), NULL);
  return toolbar;
}

GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}
 
/************************************ PUBLIC FUNCTION ****************************************/
//! Start gui 
void ijadi_gui_start (IjadiGui *object)
{
	gtk_widget_show_all(GTK_WIDGET(object));
}

//! create main gui window 
/*!
    \return Pure instance from IjadiGui
*/
IjadiGui * 		Ijadi_gui_new()
{
	IjadiGui *object = g_object_new(IJADI_TYPE_GUI,
					   "type", GTK_WINDOW_TOPLEVEL,NULL);

	//Style Provider
	GtkStyleProvider *provider;
	provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
	gtk_style_context_add_provider_for_screen (gdk_screen_get_default (),provider,GTK_STYLE_PROVIDER_PRIORITY_FORCE);
	//Private creator
	IjadiGuiPrivate *priv = IJADI_GUI_PRIVATE(object);
	//Prepare Window
	gtk_window_set_position (GTK_WINDOW(object),GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW(object), "Ijadi");
	//gtk_window_set_icon (GTK_WINDOW(object),create_pixbuf("/home/bijan/Source/Ijadi/PURE/Resourses/e.png"));

	//Style for window
	//gtk_style_context_add_class (gtk_widget_get_style_context (GTK_WIDGET(object)), "ijadi-window");
	//gtk_css_provider_load_from_path (GTK_CSS_PROVIDER(provider),LOCAL_RESOURCES"/style.css",NULL);
	//gtk_style_context_reset_widgets (gdk_screen_get_default ());
	//------------Create Widget----------------
	//Add welcome image
	priv->img_welcome = gtk_image_new_from_file ("/home/bijan/Project/Ijadi/PURE/Resources/mainwindow-welcome.png");
	//Add Button
	priv->btn_new_project = gtk_button_new_with_label("New Project");
	priv->img_new_project = gtk_image_new_from_file ("/home/bijan/Pictures/Icons/Files-Edit-file-icon.png");
	gtk_button_set_always_show_image(GTK_BUTTON(priv->btn_new_project),TRUE);
	gtk_button_set_image (GTK_BUTTON(priv->btn_new_project),priv->img_new_project);
	//
	priv->btn_open_project = gtk_button_new_with_label("Open Project");
	priv->img_open_project = gtk_image_new_from_file ("/home/bijan/Pictures/Icons/folder-open-icon.png");
	gtk_button_set_always_show_image(GTK_BUTTON(priv->btn_open_project),TRUE);
	gtk_button_set_image (GTK_BUTTON(priv->btn_open_project),priv->img_open_project);
	//
	priv->btn_import_project = gtk_button_new_with_label("Import Project");
	priv->img_import_project = gtk_image_new_from_file ("/home/bijan/Pictures/Icons/import-icon.png");
	gtk_button_set_always_show_image(GTK_BUTTON(priv->btn_import_project),TRUE);
	gtk_button_set_image (GTK_BUTTON(priv->btn_import_project),priv->img_import_project);
	//
	priv->btn_import_url = gtk_button_new_with_label ("Import URL");
	priv->img_import_url = gtk_image_new_from_file ("/home/bijan/Pictures/Icons/1372885853_folder_apollon.png");
	gtk_button_set_always_show_image(GTK_BUTTON(priv->btn_import_url),TRUE);
	gtk_button_set_image (GTK_BUTTON(priv->btn_import_url),priv->img_import_url);
	//--------------Create Menu--------------
	priv->menu_bar = ijadi_gui_create_menubar ();
	//------------Create ToolBar-------------
	priv->toolbar = ijadi_gui_create_toolbar();
	//------------Create Layout--------------
	//Create Button Box row 1
	priv->box_button = gtk_grid_new ();
	gtk_grid_attach (GTK_GRID(box_button),priv->btn_new_project,0,0,1,1);
	gtk_grid_attach (GTK_GRID(box_button),priv->btn_open_project,1,0,1,1);
	gtk_box_pack_start (GTK_BOX(priv->box_button_1),priv->btn_new_project,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_button_1),priv->btn_open_project,TRUE,TRUE,0);
	gtk_widget_set_margin_right(priv->box_button_1,5);
	gtk_widget_set_margin_left(priv->box_button_1,5);
	gtk_widget_set_margin_bottom(priv->box_button_1,5);
	gtk_widget_set_margin_top(priv->box_button_1,5);
	//Create Button Box row 2
	priv->box_button = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start (GTK_BOX(priv->box_button_2),priv->btn_import_project,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_button_2),priv->btn_import_url,TRUE,TRUE,0);
	gtk_widget_set_margin_right(priv->box_button_2,5);
	gtk_widget_set_margin_left(priv->box_button_2,5);
	gtk_widget_set_margin_bottom(priv->box_button_2,5);
	gtk_widget_set_margin_top(priv->box_button_2,5);
	//
	
	priv->box_main = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->menu_bar,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->toolbar,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->img_welcome,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->box_button_1,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->box_button_2,TRUE,TRUE,0);
	
	//Add layout to window
	gtk_container_add (GTK_CONTAINER (object), priv->box_main);
	//-----------Connect Signal-------------
	g_signal_connect (GTK_WIDGET(object), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (priv->btn_new_project, "clicked", G_CALLBACK (ijadi_gui_btn_new_project_clicked), object);
	//------------------Finalize-----------------
	gtk_window_set_application (GTK_WINDOW(object),GTK_APPLICATION(IJADI_APP));
	return object;
}





