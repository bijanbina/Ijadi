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
#include "ijadi-application.h"

# define BOX_ADD(x) 

typedef struct _IjadiWizardPrivate IjadiWizardPrivate;
struct _IjadiWizardPrivate
{
	GtkWidget* btn_next;
	GtkWidget* btn_back;
	GtkWidget* box_button;
	GtkWidget* box_main;
	GtkWidget* box_ui;//All of information widget inside here
	GtkWidget* bin_ui;
	GtkWidget* img_header;
	GtkWidget* swt_git;//Git Switch
	GtkWidget* btn_browse;
	GtkWidget* btn_browse_icon;
	GtkBuilder *ui_builder;//Create user interface from ui file
	gint 				page_num;//keep current page number
	
};

#define IJADI_WIZARD_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), IJADI_TYPE_WIZARD, IjadiWizardPrivate))

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

	g_type_class_add_private (klass, sizeof (IjadiWizardPrivate));
	
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
/*********************************** PRIVATE FUNCTION ****************************************/
//! run when git swich button changed
/*!
    \param button some made entery(you must initialize it befor invoke this finction)
    \return user_data box widget
*/
void
ijadi_wizard_swt_git_active (GtkSwitch *widget,gboolean value,gpointer   user_data)
{
/*	IjadiWizard *object = IJADI_WIZARD(user_data);
	IjadiWizardPrivate *priv = IJADI_WIZARD_PRIVATE(object);
	GtkWidget *entry_user = GTK_WIDGET (gtk_builder_get_object (priv->ui_builder, "entry7"));
	GtkWidget *entry_pass = GTK_WIDGET (gtk_builder_get_object (priv->ui_builder, "entry8"));

	gtk_editable_set_editable(GTK_EDITABLE(entry_user),FALSE);
	gtk_editable_set_editable           (GTK_EDITABLE(entry_pass),gtk_switch_get_active (GTK_SWITCH(priv->swt_git)));*/

}
//! create a box layout that contain a label and an entery
/*!
    \param txt some made entery(you must initialize it befor invoke this finction)
    \return a box widget
*/
void *
ijadi_gui_ui_init (IjadiWizard *object)
{
	IjadiWizardPrivate *priv = IJADI_WIZARD_PRIVATE(object);
	GError* error = NULL;
	
	priv->ui_builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (priv->ui_builder, LOCAL_UI"/new-wizard.ui", &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
}
//! return current page (relevant to page_num) that created from ui file
/*!
    \param txt some made entery(you must initialize it befor invoke this finction)
    \return a box widget
*/
GtkWidget *
ijadi_gui_get_page_from_ui (IjadiWizard *object)
{
	IjadiWizardPrivate *priv = IJADI_WIZARD_PRIVATE(object);
	GtkWidget *ui_widget;
	switch (priv->page_num)
	{
		case 1:
			//Create some widget that glade wont allow to use them :)
			priv->swt_git = gtk_switch_new ();
			priv->btn_browse = gtk_file_chooser_button_new ("Browse",GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
			priv->btn_browse_icon = gtk_file_chooser_button_new ("Browse Icon",GTK_FILE_CHOOSER_ACTION_OPEN);
			//Set New widget prpert
			gtk_switch_set_active(GTK_SWITCH(priv->swt_git),TRUE);
	
	
			/* connect signal handlers */
			g_signal_connect (priv->swt_git ,"notify::active", G_CALLBACK (ijadi_wizard_swt_git_active) , object);
			ui_widget = GTK_WIDGET (gtk_builder_get_object (priv->ui_builder, "page1"));
			//Add some widget that glade wont allow to use them :)
			gtk_container_add (GTK_CONTAINER(gtk_builder_get_object (priv->ui_builder, "box3")),priv->swt_git);
			gtk_container_add (GTK_CONTAINER(gtk_builder_get_object (priv->ui_builder, "box4")),priv->btn_browse);
			gtk_box_pack_start (GTK_BOX(gtk_builder_get_object (priv->ui_builder, "box5")),priv->btn_browse_icon,TRUE,TRUE,0);


			GtkWidget *textv = GTK_WIDGET (gtk_builder_get_object (priv->ui_builder, "textview1"));
			gtk_style_context_add_class (gtk_widget_get_style_context (textv),"ijadi-text-view");
			break;
		case 2:
			ui_widget = GTK_WIDGET (gtk_builder_get_object (priv->ui_builder, "page2"));
	}
	gtk_widget_unparent (ui_widget);
	return ui_widget;
}
//! create a box layout that contain a label and an entery
/*!
    \param txt some made entery(you must initialize it befor invoke this finction)
    \return a box widget
*/
GtkWidget *
ijadi_gui_create_form (GtkWidget *txt,gchar *label)
{
    GtkWidget *lbl_form = gtk_label_new (label);
	gtk_style_context_add_class (gtk_widget_get_style_context (lbl_form),"ijadi-label");
	GtkWidget *box_form = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);;
	//-----------------------Add Widget to layout ---------------------------
	gtk_box_pack_start (GTK_BOX(box_form),lbl_form,FALSE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(box_form),txt,FALSE,TRUE,0);
	//------------------------------------Finalize----------------------------------
	gtk_widget_set_margin_right(box_form,5);
	gtk_widget_set_margin_left(box_form,5);
	gtk_widget_set_margin_bottom(box_form,5);
	gtk_widget_set_margin_top(box_form,5);
    return box_form;
}
/********************************** CALLBACK FUNCTION **************************************/
//! run when next button clicked
/*!
    \param button some made entery(you must initialize it befor invoke this finction)
    \return user_data box widget
*/
void
ijadi_wizard_btn_next_clicked (GtkButton *button, gpointer user_data)
{
	IjadiWizard *object = IJADI_WIZARD(user_data);
	IjadiWizardPrivate *priv = IJADI_WIZARD_PRIVATE(object);
	if (priv->page_num == IJADI_MAX_PAGENUM)
		;//HERE PROJECT MUST CREATE;
	priv->page_num++;
	if (priv->page_num == IJADI_MAX_PAGENUM)
		gtk_button_set_label (GTK_BUTTON(priv->btn_next),"Finish");
		if (priv->page_num != IJADI_MIN_PAGENUM)
		gtk_button_set_label (GTK_BUTTON(priv->btn_back),"Back");
	//-----------Release Widget-------------
	gtk_container_remove (GTK_CONTAINER(priv->box_ui),priv->bin_ui);
	//gtk_widget_destroy (priv->bin_ui);
	//----------------Create UI-----------------
	priv->bin_ui = ijadi_gui_get_page_from_ui (object);
	gtk_container_add (GTK_CONTAINER(priv->box_ui),priv->bin_ui);
}
//! run when back button clicked
/*!
    \param button some made entery(you must initialize it befor invoke this finction)
    \return user_data box widget
*/
void
ijadi_wizard_btn_back_clicked (GtkButton *button, gpointer user_data)
{
	IjadiWizard *object = IJADI_WIZARD(user_data);
	IjadiWizardPrivate *priv = IJADI_WIZARD_PRIVATE(object);
	if (priv->page_num == IJADI_MIN_PAGENUM)
	{
		gtk_widget_hide (GTK_WIDGET(object));
		gtk_widget_destroy (GTK_WIDGET(object));
	}
	else
	{
		priv->page_num--;
		if (priv->page_num == IJADI_MIN_PAGENUM)
			gtk_button_set_label (GTK_BUTTON(priv->btn_back),"Cancel");
		if (priv->page_num != IJADI_MAX_PAGENUM)
			gtk_button_set_label (GTK_BUTTON(priv->btn_next),"Next");
		//-----------Release Widget-------------
		gtk_container_remove (GTK_CONTAINER(priv->box_ui),priv->bin_ui);
		//gtk_widget_destroy (priv->bin_ui);
		//----------------Create UI-----------------
		priv->bin_ui = ijadi_gui_get_page_from_ui (object);
		gtk_container_add (GTK_CONTAINER(priv->box_ui),priv->bin_ui);
	}
}
/************************************ PUBLIC FUNCTION ****************************************/
//! create main gui window 
/*!
    \return Pure instance from IjadiGui
*/
IjadiWizard* Ijadi_wizard_new()
{
	g_type_init ();
	IjadiWizard *object = g_object_new(IJADI_TYPE_WIZARD,
					   "type", GTK_WINDOW_TOPLEVEL,NULL);
	//create private data from objet
	IjadiWizardPrivate *priv = IJADI_WIZARD_PRIVATE(object);
	//--------------- Set default value -------------
	priv->page_num = 1;
	//Create Wizard Window
	//--------------- Set Window -------------
	gtk_style_context_add_class (gtk_widget_get_style_context (GTK_WIDGET(object)),"ijadi-wizard");
	gtk_window_set_position (GTK_WINDOW(object),GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW(object), "New Project");
	//------------Create Widget----------------
	priv->img_header = gtk_image_new_from_file(LOCAL_RESOURCES"/new-header.png");
	priv->btn_back  = gtk_button_new_with_label ("Cancel");
	priv->btn_next  = gtk_button_new_with_label ("Next");
	//------------Create Layout--------------
	//----------------Create UI-----------------
	ijadi_gui_ui_init (object);
	priv->box_ui = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL );
	priv->bin_ui = ijadi_gui_get_page_from_ui (object);
	gtk_container_add (GTK_CONTAINER(priv->box_ui),priv->bin_ui);
	//---------------------Button BOX--------------------------
	priv->box_button = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL );
	gtk_button_box_set_layout (GTK_BUTTON_BOX (priv->box_button),GTK_BUTTONBOX_END);
	gtk_box_pack_start (GTK_BOX(priv->box_button),priv->btn_back,FALSE,TRUE,3);
	gtk_box_pack_start (GTK_BOX(priv->box_button),priv->btn_next,FALSE,TRUE,3);
	gtk_widget_set_margin_right(priv->box_button,15);
	gtk_widget_set_margin_left(priv->box_button,5);
	gtk_widget_set_margin_bottom(priv->box_button,15);
	gtk_widget_set_margin_top(priv->box_button,5);

	//
	priv->box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->img_header,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->box_ui,TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->box_button,TRUE,TRUE,0);
	//Add layout to window
	gtk_container_add (GTK_CONTAINER(object),priv->box_main);
	//---------------------Connect Signal--------------------------
	g_signal_connect (priv->btn_back   , "clicked", G_CALLBACK (ijadi_wizard_btn_back_clicked), object);
	g_signal_connect (priv->btn_next    , "clicked", G_CALLBACK (ijadi_wizard_btn_next_clicked), object);
	//------------------Finalize-----------------
	gtk_window_set_application (GTK_WINDOW(object),GTK_APPLICATION(IJADI_APP));
	return object;
}

void	ijadi_wizard_start (IjadiWizard *object)
{
	gtk_widget_show_all(GTK_WIDGET(object));
}