/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PURE
 * Copyright (C) bijan 2012 <bijan@bijan-P5KC>
 * 
PURE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * PURE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//fds fdsf sdf sd fsd fs fsd fsd fd h\

#include "gbee-intercept.h"

typedef struct _GbeeInterceptPrivate GbeeInterceptPrivate;
struct _GbeeInterceptPrivate
{
	gchar         *file_content;
	GbeeLine      *lines;
	GtkTextBuffer *buffer;
	gchar         *filename;
	gint           linecount;
	GbeeIparser   *Iparser;//include parser (parse type, define and etc in hedear file)
	GFile         *base_dir;//save project base directory
	GList		  *includeD;//list of all directory for searching include file
};

#define GBEE_INTERCEPT_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), GBEE_TYPE_INTERCEPT, GbeeInterceptPrivate))



G_DEFINE_TYPE (GbeeIntercept, gbee_intercept, G_TYPE_OBJECT);

static void
gbee_intercept_init (GbeeIntercept *object)
{
	/* TODO: Add initialization code here */
}

//! simply join two string 
/*!
    \return a pointer to first element pf string
*/

static void
gbee_intercept_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (gbee_intercept_parent_class)->finalize (object);
}

static void
gbee_intercept_class_init (GbeeInterceptClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (GbeeInterceptPrivate));

	object_class->finalize = gbee_intercept_finalize;
}

/*********************************** PRIVATE FUNCTION ****************************************/
//! find offset of char that has offset char_num in line "linenumber"
/*!
    \param object instance of GbeeIntercept
	\param linenumber the line that your char is there
	\param char_num ofset of char in the line
*/
gint gbee_intercept_get_offset (GbeeIntercept *object,int linenumber,int char_num)
{
	//create private data from objet
	GbeeInterceptPrivate *priv = GBEE_INTERCEPT_PRIVATE(object);
	int i,buffer = 0;
	
	for (i = 0 ; i < linenumber ; i++ )
	{
		buffer += strlen(priv->lines[i].value) + 1;
	}
	buffer += char_num + 1;
	return buffer;
}

//! determine file is exist or not
/*!
    \param  patch file patch
	\return return true if file is exist
*/
gboolean gbee_intercept_is_exist(gchar *filename)
{
	return g_file_test (filename,G_FILE_TEST_EXISTS);
}

//! find offset of char that has offset char_num in line "linenumber"
/*!
    \param object instance of GbeeIntercept
	\param linenumber the line that your char is there
	\param char_num ofset of char in the line
*/
void gbee_intercept_get_iter (GbeeIntercept *object,GbeeIter iter,GtkTextIter *return_iter)
{
	//create private data from objet
	GbeeInterceptPrivate *priv = GBEE_INTERCEPT_PRIVATE(object);
	gtk_text_buffer_get_iter_at_line_offset(priv->buffer,return_iter,iter.line,iter.char_offset);
}

//! get include filename from include line (gif refer to get include filename)
/*!
    \param  line line you want to extract include filename from it0
	\return return include filename
*/
gchar *gbee_intercept_gif(GbeeLine line)
{
	gchar *value = line.value;
	int i;
	for (i = 0 ; value[i] != '\0' && value[i] != '<' ; i++)
		;
	i++;
	int start = i;
	for ( ; value[i] != '\0' && value[i] != '>' ; i++)
		;
	int end    = i;
	int lenght = end - start;
	if (lenght < 1)//check whethere it's local include or not
	{
		for (i = 0 ; value[i] != '\0' && value[i] != '\"' ; i++)
			;
		i++;
		start = i;
		for ( ; value[i] != '\0' && value[i] != '\"' ; i++)
			;
		end    = i;
		lenght = end - start;
		if (lenght < 1)
			return NULL;
	}
	gchar *return_data = g_strndup(&(value[start]),lenght);
	//g_strlcpy(return_data,&(str[start]),lenght+1);//String is \0 terminated so dont worry
	return return_data;
}


//! get include GFile object (filename must start with /)
/*!
    \param  object   instance from gbee_intercept
    \param  filename instance from gbee_intercept
	\return return   GFile point to include file
*/
GFile *gbee_intercept_get_include(GbeeIntercept *object,gchar *filename)
{
	GbeeInterceptPrivate *priv = GBEE_INTERCEPT_PRIVATE(object);
	GList *list = priv->includeD;
	int i;
	for (i = 0; i < g_list_length(list) ; i ++)
	{
		gchar *path = g_strconcat (g_list_nth_data(list,i),filename,NULL);
		if (gbee_intercept_is_exist(path))
	    {
		    return g_file_new_for_path(path);
		}
	}
	return NULL;
}

//! update project base directory
/*!
    \param  object instance from gbee_intercept
*/
void gbee_intercept_update_base(GbeeIntercept *object)
{
	GbeeInterceptPrivate *priv = GBEE_INTERCEPT_PRIVATE(object);
	priv->base_dir    = g_file_new_for_path(priv->filename);
	GFile    *file    = priv->base_dir;
	file = g_file_get_parent(file);
	while (g_file_has_parent(file,NULL))
	{
		//check for configure.ac
		GFile *child = g_file_get_child (file,"configure.ac");
		if (gbee_intercept_is_exist (g_file_get_parse_name(child)))
			break;
		//check for configure
		child = g_file_get_child (file,"configure");
		if (gbee_intercept_is_exist (g_file_get_parse_name(child)))
		   break;
		file = g_file_get_parent(file);
	}
	priv->base_dir = file;
}

//! update project include directory list
/*!
    \param  includes list of include directory or cflag (directory for finding adition includes)
    \param  object   instance from gbee_intercept
*/
void gbee_intercept_update_includeD(GbeeIntercept *object,GList *includes)
{
	GbeeInterceptPrivate *priv   = GBEE_INTERCEPT_PRIVATE(object);
	GFile                *folder = g_file_new_for_path(priv->filename);//source folder or current directory
	folder = g_file_get_parent(folder);
	GList *list = priv->includeD;
	g_list_free (list);
	list = g_list_append(list,"/usr/include");
	list = g_list_append(list,"/usr/local/include");
	list = g_list_append(list,"/usr/include/linux");
	list = g_list_append(list,"/usr/include/c++/4.6");
	list = g_list_append(list,"/usr/include/c++/4.6/tr1");
	list = g_list_append(list,"/usr/include/c++/4.6/x86_64-linux-gnu");
	list = g_list_append(list,g_file_get_parse_name(priv->base_dir));
	list = g_list_append(list,g_file_get_parse_name(folder));
	int i = 0;
	for ( i = 0 ; i < g_list_length (includes) ; i++ )
	{
		list = g_list_append(list,g_list_nth_data (includes,i));
	}
	priv->includeD = list;
}

//! main function that parse text
/*!
    \param object instance of GbeeIntercept
	\param linenumber the line that your char is there
	\param char_num ofset of char in the line
*/
void gbee_intercept_parse(GbeeIntercept *object)
{
	//create private data from objet
	GbeeInterceptPrivate *priv = GBEE_INTERCEPT_PRIVATE(object);
	gboolean              incomment = FALSE;//if we are inside a multiline comment it set to true
	int                   i;
	gbee_string_preparse(priv->lines);
}
/************************************ PUBLIC FUNCTION ****************************************/
//! create instance from GbeeIntec
/*!
    \param  filename patch of file you want to intercept it
    \param  includes list of include directory or cflag (directory for finding adition includes)
    \return Pure     instance from GbeeIntece
*/
GbeeIntercept *gbee_intercept_new (char *filename,GList *includes)//gchar *content,GtkTextBuffer *buffer)
{
	//------------- Variable Definition ----------------
	gchar *content;
	GtkTextBuffer *buffer;
	gchar **lines;
	int i = 0;
	//open file 
	g_file_get_contents(filename,&content,NULL,NULL);
	//create a new textbuffer
	buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text (buffer,content,-1);
	//--------- Begin Preproccess for parsing-----------
	
	g_type_init ();
	GbeeIntercept *object = g_object_new(GBEE_TYPE_INTERCEPT,NULL);
	GbeeInterceptPrivate *priv = GBEE_INTERCEPT_PRIVATE(object);
	
	//-------------- set variable ----------------
	priv->filename     = filename;
	priv->file_content = content;
	priv->buffer       = buffer;
	lines              = g_strsplit(priv->file_content,"\n",0);
	gbee_intercept_update_base    (object);
	gbee_intercept_update_includeD(object,includes);
	LOCAL_DATABASE = g_strconcat(g_file_get_path (priv->base_dir),"/IncludeDB",NULL);
	for ( i = 0 ; lines[i] != NULL ; i++ )
	{
		;//caculate size of lines
	}
	priv->lines = g_new(GbeeLine, i);
	for ( i = 0 ; lines[i] != NULL ; i++ )
	{
		priv->lines[i].value          = lines[i];
		priv->lines[i].words          = NULL;
		priv->lines[i].pre_flag       = FALSE;
		priv->lines[i].include_flag   = FALSE;
		priv->lines[i].pro_flag       = FALSE;
		priv->lines[i].command_flag   = FALSE;
		priv->lines[i].define_flag    = FALSE;
		priv->lines[i].infunc_flag    = FALSE;
		priv->lines[i].multiline_flag = FALSE;
		priv->lines[i].comment_type   = GBEE_NO_COMMENT;
		priv->lines[i].comment_offset = -1;
		gbee_string_fill_word   (&priv->lines[i]);
	}
	priv->linecount = i;
	//gbee_intercept_parse(object);
	
/*	g_printf("%d%c\n",gbee_intercept_get_offset(object,10,14),priv->lines[10].value[14]);*/
	priv->Iparser = gbee_iparser_new (priv->includeD);
	gbee_iparser_parse (priv->Iparser,"gbee-define.h");
	//gbee_iparser_parse (priv->Iparser,"bits/stdio.h");
	//-------------Return Object---------------
	return object;
}

