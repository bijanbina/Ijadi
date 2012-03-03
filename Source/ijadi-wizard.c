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
	GtkWidget* btn_create;
	GtkWidget* btn_cancel;
	GtkWidget* box_button;
	GtkWidget* box_main;
	GtkWidget* box_info;//All of information widget inside here
	GtkWidget* img_header;
	GtkWidget* txt_name;
	GtkWidget* txt_author;
	GtkWidget* txt_version;
	GtkWidget* txt_dir;
	GtkWidget* txt_email;
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
	//Create Wizard Window
	//--------------- Set Window -------------
	gtk_style_context_add_class (gtk_widget_get_style_context (GTK_WIDGET(object)),"ijadi-wizard");
	gtk_window_set_position (GTK_WINDOW(object),GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW(object), "New Project");
	//------------Create Widget----------------
	priv->img_header = gtk_image_new_from_file(LOCAL_RESOURCES"/new-header.png");
	priv->btn_cancel  = gtk_button_new_with_label ("Cancel");
	priv->btn_create  = gtk_button_new_with_label ("Create");
	//------------Create Layout--------------
	//---------------------Button BOX--------------------------
	priv->box_button = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL );
	gtk_button_box_set_layout (GTK_BUTTON_BOX (priv->box_button),GTK_BUTTONBOX_END);
	gtk_box_pack_start (GTK_BOX(priv->box_button),priv->btn_cancel,FALSE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_button),priv->btn_create,FALSE,TRUE,0);
	gtk_widget_set_margin_right(priv->box_button,5);
	gtk_widget_set_margin_left(priv->box_button,5);
	gtk_widget_set_margin_bottom(priv->box_button,5);
	gtk_widget_set_margin_top(priv->box_button,5);
	priv->txt_name = gtk_entry_new ();
	priv->txt_author = gtk_entry_new ();
	priv->txt_version = gtk_entry_new ();
	priv->txt_dir = gtk_entry_new ();
	priv->txt_email = gtk_entry_new ();

	//
	priv->box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->img_header,TRUE,TRUE,0);
	//---------------------Info BOX--------------------------
	gtk_box_pack_start (GTK_BOX(priv->box_main),ijadi_gui_create_form(priv->txt_name,"Project Name : "),TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),ijadi_gui_create_form(priv->txt_author,"Author Name : "),TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),ijadi_gui_create_form(priv->txt_version,"Version : "),TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),ijadi_gui_create_form(priv->txt_dir,"Directory : "),TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),ijadi_gui_create_form(priv->txt_email,"Author Email : "),TRUE,TRUE,0);
	gtk_box_pack_start (GTK_BOX(priv->box_main),priv->box_button,TRUE,TRUE,0);
	//gtk_box_pack_start (GTK_BOX(priv->box_main),priv->box_button,TRUE,TRUE,0);
	//Add layout to window
	gtk_container_add (GTK_CONTAINER (object), priv->box_main);
	//------------------Finalize-----------------
	gtk_window_set_application (GTK_WINDOW(object),GTK_APPLICATION(IJADI_APP));
	return object;
}

void	ijadi_wizard_start (IjadiWizard *object)
{
	gtk_widget_show_all(GTK_WIDGET(object));
}