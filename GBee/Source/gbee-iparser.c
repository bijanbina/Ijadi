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

#include "gbee-iparser.h"
typedef struct _GbeeIparserPrivate GbeeIparserPrivate;
struct _GbeeIparserPrivate
{
	GFile         *base_dir;//save project base directory
	GList		  *includeD;//list of all directory for searching include file
	gboolean       sqlIsNull;
};

#define GBEE_IPARSER_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), GBEE_TYPE_IPARSER, GbeeIparserPrivate))



G_DEFINE_TYPE (GbeeIparser, gbee_iparser, G_TYPE_OBJECT);

static void
gbee_iparser_init (GbeeIparser *gbee_iparser)
{
    GbeeIparserPrivate *priv = GBEE_IPARSER_GET_PRIVATE(gbee_iparser);

	/* TODO: Add initialization code here */
}

static void
gbee_iparser_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (gbee_iparser_parent_class)->finalize (object);
}

static void
gbee_iparser_class_init (GbeeIparserClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (GbeeIparserPrivate));

	object_class->finalize = gbee_iparser_finalize;
}

//! determine file is exist or not
/*!
    \param  patch file patch
	\return return true if file is exist
*/
gboolean gbee_iparser_is_exist(gchar *filename)
{
	return g_file_test (filename,G_FILE_TEST_EXISTS);
}

//! get include filename from include line (gif refer to get include filename)
/*!
    \param  str line you want to extract include filename from it0
	\return return include filename
*/
gchar *gbee_iparser_gif(gchar *str)
{
	int i, start, end, lenght;
	for (i = 0 ; str[i] != '\0' && str[i] != '<'; i++)
		;
	if (str[i] != '\0')
	{
		i++;
		start = i;
		for ( ; str[i] != '\0' && str[i] != '>'; i++)
		;
		end    = i;
		lenght = end - start;
	}
	else
	{
		for (i = 0 ; str[i] != '\0' && str[i] != '\"'; i++)
			;
		if (str[i] == '\0')
			return NULL;
		i++;
		start = i;
		for ( ; str[i] != '\0' && str[i] != '\"'; i++)
			;
		end    = i;
		lenght = end - start;
		if (lenght < 1)
			return NULL;
	}
	gchar *return_data = g_strndup(&(str[start]),lenght);
	//g_strlcpy(return_data,&(str[start]),lenght+1);//String is \0 terminated so dont worry
	return return_data;
}

//! get include file full path (like stdlib.h)
/*!
    \param  object   instance from gbee_iparser
    \param  filename instance from gbee_iparser
	\return return   GFile point to include file
*/
gchar *gbee_iparser_get_include(GbeeIparser *object,gchar *filename)
{
	GbeeIparserPrivate *priv = GBEE_IPARSER_GET_PRIVATE(object);
	GList *list = priv->includeD;
	int i;
	for (i = 0; i < g_list_length(list) ; i++)
	{
		gchar *path = g_strconcat (g_list_nth_data(list,i),"/",filename,NULL);
		if (gbee_iparser_is_exist(path))
	    {
		    return path;
		}
		else
		{
			g_free(path);
		}
	}
	return NULL;
}

//! calculate filename line count
/*!
    \param  filename   path of file
*/
int gbee_file_linecount(gchar *filename)
{
	gchar *content;
	gchar **lines;
	GError         *error = NULL;
	g_file_get_contents(filename,&content,NULL,&error);
	if (error != NULL)
	{
		fprintf (stderr, "Unable to read file: %s\n", error->message);
		g_error_free (error);
		exit(1);
	}
	lines = g_strsplit(content,"\n",0);
	int i;
	for ( i = 0 ; lines[i] != NULL ; i++ )
	{
		;//caculate size of lines
	}
	g_strfreev(lines);
	return i;
}

//! calculate filename modifydate (in uint64 format)
/*!
    \param  filename   path of file
*/
guint64 gbee_file_modifydate(gchar *filename)
{
	GFile     *file = g_file_new_for_path (filename);
	GFileInfo *info = g_file_query_info (file,G_FILE_ATTRIBUTE_TIME_MODIFIED ,
											G_FILE_QUERY_INFO_NONE,NULL,NULL);
	return g_file_info_get_attribute_uint64 (info,G_FILE_ATTRIBUTE_TIME_MODIFIED);
}

//! calculate filename checksum(MD5)
/*!
    \param  filename   path of file
*/
gchar *gbee_file_checksum(gchar *filename)
{
	GError *err = NULL;
	gchar **lines,*buffer,*command;
	int exit_status;
	command = g_strconcat     ("md5sum ",filename, NULL);
	g_spawn_command_line_sync (command,&buffer,NULL,&exit_status,&err);
	if (err != NULL)
	{
		fprintf (stderr, "Unable to execute command %s: %s\nexit status:%d\n", command, err->message,exit_status);
		g_error_free (err);
		exit(1);
	}
	if (exit_status != 0)
	{
		g_printf("an error occurd when running %s and exit status is %d",command,exit_status);
		exit(1);
	}
	lines = g_strsplit        (buffer," ",0);
	g_free(command);
	g_free(buffer);
	g_free(lines[1]);
	return lines[0];
}	

//! add new define name to database
//! Example line:#define LOCAL "hi"
/*!
    \param  object     instance of GbeeIparser
    \param  definename LOCAL in example is defineto
    \param  defineto   "hi" in example is defineto
    \param  filename   filename of file wich include define 
    \param  linenumber line number of file wich include define 
*/
void gbee_add_define(GbeeIparser *object,gchar *Definename,gchar *defineto,gchar *filename,gint linenumber)
{
	gchar *linenum = g_strdup_printf ("%u", linenumber);
	gchar *command = g_strconcat ("INSERT INTO Defines VALUES ('",Definename,"','",defineto,"','",filename,"',",linenum,")", NULL);
	int rc = gbee_sql_exec(object, command);
	g_free(command);
}



static int gbee_sql_callback(void *arg1, int argc, char **argv, char **azColName)
{
    GbeeIparser *object = GBEE_IPARSER(arg1);
	GbeeIparserPrivate *priv = GBEE_IPARSER_GET_PRIVATE(object);
	priv->sqlIsNull = FALSE;
	return 0;
}

//! execute sql command and print error if it occur
/*!
    \param  object     instance of GbeeIparser
    \param  Filename   LOCAL in example is defineto
	\return return     return 0 if the command execute and have output
 *					   return 1 if the command execute and have no output
 *					   return 2 if the command executation got error
*/
int gbee_sql_exec(GbeeIparser *object,gchar *command)
{
	char *zErrMsg = 0;
	GbeeIparserPrivate *priv = GBEE_IPARSER_GET_PRIVATE(object);
	priv->sqlIsNull = TRUE;
	//puts(command);
	//printf("%lu\n",strlen(command));
	int rc = sqlite3_exec(object->db, command,gbee_sql_callback,object, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 2;
    }
	if (priv->sqlIsNull)
		return 1;
	return 0;
}

//! add new include name to database
/*!
    \param  object     instance of GbeeIparser
    \param  Filename   LOCAL in example is defineto
*/
void gbee_add_parsed_file(GbeeIparser *object,gchar *Filename)
{
	char *zErrMsg = 0;
	gchar *path        = gbee_iparser_get_include (object,Filename);
	gchar *linecount   = g_strdup_printf ("%u", gbee_file_linecount (path));
	gchar *checksum    = gbee_file_checksum(path);
	gchar *modifydate  = g_strdup_printf ("%lu", gbee_file_modifydate(path));
	gchar *command = g_strconcat ("INSERT INTO `Parsed File` VALUES ('",Filename,"',",linecount,",'",path,"','",checksum,"',",modifydate,")\0", NULL);
	int rc = gbee_sql_exec(object, command);
	g_free(command);
}

//! check include name is in database or not
/*!
    \param  object     instance of GbeeIparser
    \param  Filename   like "iostream.h"
*/
gboolean gbee_iparser_is_parsed(GbeeIparser *object,gchar *Filename)
{
	char *zErrMsg = 0;
	gchar *command = g_strconcat ("SELECT Filename FROM 'Parsed File' WHERE Filename = '",Filename,"'", NULL);
	//puts(command);
	int rc = gbee_sql_exec(object, command);
	g_free(command);
	if (rc == 0)//if have output
		return TRUE;
	else //not have output
		return FALSE;
}

//! recursive parser for include file (use this function you sure database is open)
/*!
    \param object instance of GbeeIparser
	\param IName  include name for example iostream.h
*/
void gbee_iparser_rparse(GbeeIparser *object,gchar *IName)
{	
	//create private data from objet
	GbeeIparserPrivate *priv = GBEE_IPARSER_GET_PRIVATE(object);
	//---------Open File and get content--------------
	gchar       *filename;
	gchar        *content;
	gchar   **split_lines;
	GbeeLine       *lines;
	GError         *error = NULL;
	filename = gbee_iparser_get_include (object,IName);
	g_file_get_contents(filename,&content,NULL,&error);
	if (error != NULL)
	{
		fprintf (stderr, "Unable to read file: %s\n", error->message);
		g_error_free (error);
	}
	if (content == NULL)
	{
		fprintf (stderr, "hey what's up men with file %s\n", filename);
		exit(1);
	}
	//-------------- set variable ----------------
	split_lines        = g_strsplit(content,"\n",-1);//0 : maximum token
	int i              = 0;
	for ( i = 0 ; split_lines[i] != NULL ; i++ )
	{
		;//caculate size of lines
	}
	lines = g_new(GbeeLine, i + 1);
	g_free(content);
	const int linecount = i;
	for ( i = 0 ; i < linecount ; i++ )
	{
		lines[i].value          = split_lines[i];
		lines[i].words          = NULL;
		lines[i].pre_flag       = FALSE;
		lines[i].include_flag   = FALSE;
		lines[i].pro_flag       = FALSE;
		lines[i].command_flag   = FALSE;
		lines[i].define_flag    = FALSE;
		lines[i].infunc_flag    = FALSE;
		lines[i].multiline_flag = FALSE;
		lines[i].comment_type   = GBEE_NO_COMMENT;
		lines[i].comment_offset = -1;
	}
	lines[linecount].value = NULL;
	//----------------------------------
	gbee_string_preparse(lines);
	//end preparsed
	for ( i = 0 ; i < linecount ; i++ )
	{
		#ifdef GBEE_VERBOSE
			g_printf("line %d: Preproccesor:%d Include:%d Define:%d Comment:%d Multiline:%d\n",i+1,lines[i].pre_flag,lines[i].include_flag,lines[i].define_flag,lines[i].comment_type,lines[i].multiline_flag);
		#endif
		gchar *str;
		if (i > 0)
			if (lines[i-1].multiline_flag)
				continue;
		if (lines[i].multiline_flag)
		{
			str = gbee_string_mk_oneline (lines,i);
		}
		else
		{
			str = lines[i].value;
		}
		if (lines[i].include_flag)
		{
			gchar *include_name = gbee_iparser_gif (str);
			#ifdef GBEE_DEBUG
				puts(include_name);
			#endif
			if (NULL != gbee_iparser_get_include (object,include_name))
			{
				if(!gbee_iparser_is_parsed (object,include_name))
				{
					gbee_add_parsed_file (object,include_name);
					gbee_iparser_rparse (object,include_name);
				}
			}
			g_free(include_name);
		}
	}
	g_strfreev(split_lines);
}
/************************************ PUBLIC FUNCTION ****************************************/
//! free resource that allocate for GBeeline 
//! note: GbeeLine must be null terminated and this function use for delete an array
/*!
    \param  GbeeLine a nullterminated GbeeLine array
*/
void         gbee_line_delete (GbeeLine *object)
{
	//FIXME 
}

//! main function for parsing include file
/*!
    \param object instance of GbeeIparser
	\param IName  include name for example iostream.h
*/
void gbee_iparser_parse(GbeeIparser *object,gchar *IName)
{	
	sqlite3_open_v2(LOCAL_DATABASE,&(object->db), SQLITE_OPEN_READWRITE,NULL);
	gbee_iparser_rparse(object,IName);
	sqlite3_close(object->db);
}

//! create instance from GbeeIparser
/*!
    \param  includes list of include directory or cflag (directory for finding adition includes)
    \return Pure     instance from GbeeIntece
*/
GbeeIparser *gbee_iparser_new (GList *includes)//gchar *content,GtkTextBuffer *buffer)
{
	g_type_init ();
	GbeeIparser *object = g_object_new(GBEE_TYPE_IPARSER,NULL);
	GbeeIparserPrivate *priv = GBEE_IPARSER_GET_PRIVATE(object);
	priv->includeD = includes;
	//----------Connect to Database------------
	char *zErrMsg = 0;
	if (gbee_iparser_is_exist (LOCAL_DATABASE))
	{
		int rc = sqlite3_open_v2(LOCAL_DATABASE,&(object->db), SQLITE_OPEN_READWRITE,NULL);
		if( rc )
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(object->db));
			exit(1);
		}
		gchar *include_name = gbee_iparser_gif ("#include <glib/goption.h>");
		gbee_iparser_is_parsed (object,include_name);
		sqlite3_close(object->db);
	}
	else
	{
		int rc = sqlite3_open_v2(LOCAL_DATABASE,&(object->db), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,NULL);//Create Database
		if( rc )
		{
		  fprintf(stderr, "Can't create database: %s\n", sqlite3_errmsg(object->db));
		  sqlite3_close(object->db);
		  exit(1);
		}
		//--------------read initial script------------------
		gchar *content;
		g_file_get_contents(LOCAL_RESOURCES"/InitScript.sql",&content,NULL,NULL);
		rc = gbee_sql_exec(object, content);
		g_free(content);
		sqlite3_close(object->db);
	}
	//-------------Return Object---------------
	return object;
}
