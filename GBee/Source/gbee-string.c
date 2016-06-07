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

#include "gbee-string.h"

/************************************ Private FUNCTION ****************************************/
//! parse the line and return word in GbeeWord type;
/*!
    \param line line you want to fill GbeeWord array flag
*/
GbeeWord **gbee_string_fill_word(gchar *str)
{
	int       lenght,i,start,end;
	gboolean  instring = FALSE;
	gboolean  inword   = FALSE;
	gboolean  inchar   = FALSE;
	GList    *words    = NULL;
	GbeeWord *word_buffer;
	lenght = strlen(str);
	for ( i = 0 ; i < lenght ; i++ )
	{
		if ( i < lenght - 1)
		{
			if (instring)
			{
				if (str[i] == '\\')
				{
					i++;
				}
				else if (str[i] == '\"')
				{
					end        = i;
					instring   = FALSE;
					inword     = FALSE;
					word_buffer = g_new(GbeeWord,1);
					word_buffer->string_flag = TRUE;
					word_buffer->type        = GBEE_UN;
					word_buffer->value = g_strndup(&(str[start]),end - start + 1);
					words = g_list_append(words,word_buffer);
				}
			}
			else if (inchar)
			{
				if(str[i] == '\\')
				{
					i++;
				}
				else if (str [i] == '\'')
				{
					end        = i;
					inchar     = FALSE;
					inword     = FALSE;
					word_buffer = g_new(GbeeWord,1);
					word_buffer->string_flag = FALSE;
					word_buffer->char_flag   = TRUE;
					word_buffer->type        = GBEE_UN;
					word_buffer->value = g_strndup(&(str[start]),end - start + 1);
					words = g_list_append(words,word_buffer);
				}
			}
			else if (str[i] == '/' && str[i+1] == '*' )
			{
				start = i;
				end = gbee_string_find_start (str,"*/",i);
				end++; //just think
				if ( end < i )
					end = lenght - 1;
				i          = end;
				inchar     = FALSE;
				inword     = FALSE;
				word_buffer = g_new(GbeeWord,1);
				word_buffer->string_flag = FALSE;
				word_buffer->char_flag   = FALSE;
				word_buffer->type        = GBEE_CM;
				word_buffer->value = g_strndup(&(str[start]),end - start + 1);
				words = g_list_append(words,word_buffer);
			}
			else if (str[i] == '\\' && str[i+1] == '\\' )
			{
				start      = i;
				end        = lenght - 1;
				i          = end;
				inchar     = FALSE;
				inword     = FALSE;
				word_buffer = g_new(GbeeWord,1);
				word_buffer->string_flag = FALSE;
				word_buffer->char_flag   = FALSE;
				word_buffer->type        = GBEE_CM;
				word_buffer->value = g_strndup(&(str[start]),end - start + 1);
				words = g_list_append(words,word_buffer);
			}
			else if (str[i] == ' ')
			{
				if (inword)
				{
						end     = i;
						inword = FALSE;
						word_buffer = g_new(GbeeWord,1);
						word_buffer->string_flag = FALSE;
						word_buffer->char_flag   = FALSE;
						word_buffer->type        = GBEE_UN;
						word_buffer->value = g_strndup(&(str[start]),end - start);
						words = g_list_append(words,word_buffer);
				}
				else
				{
					start  = i + 1;
					inword = TRUE;
				}
			}
			else if (str[i] == '\"')
			{
				start     = i;
				inword   = TRUE;
				instring = TRUE;
			}
			else if (str[i] == '\'')
			{
				start  = i;
				inword = TRUE;
				inchar = TRUE;
			}
			else if (!inword)
			{
				start = i;
				inword = TRUE;
			}
		}
		else
		{
			if (inword)
			{
				end = i;
				inchar     = FALSE;
				inword     = FALSE;
				word_buffer = g_new(GbeeWord,1);
				word_buffer->string_flag = FALSE;
				word_buffer->char_flag   = FALSE;
				word_buffer->type        = GBEE_UN;
				word_buffer->value = g_strndup(&(str[start]),end - start + 1);
				words = g_list_append(words,word_buffer);
			}
			else
			{
				start = i;
				word_buffer = g_new(GbeeWord,1);
				word_buffer->string_flag = FALSE;
				word_buffer->char_flag   = FALSE;
				word_buffer->type        = GBEE_UN;
				word_buffer->value = g_strndup(&(str[start]),1);
				words = g_list_append(words,word_buffer);
			}
		}
	}
	lenght = g_list_length (words);
	GbeeWord **return_data = g_new(GbeeWord*, lenght);
#ifdef GBEE_DEBUG_1
	g_printf("string: %s\n",str);
#endif
	for (i = 0; i < g_list_length (words) ; i++)
	{
		return_data[i] = g_list_nth_data (words,i);
#ifdef GBEE_DEBUG_1
		g_printf("word: %s\n",return_data[i]->value);
#endif
	}
	return return_data;
}
/************************************ PUBLIC  FUNCTION ****************************************/
//! simply allocate memory for string 
/*!
    \return a pointer to first element pf string
*/
gchar *gbee_string_new (const char *str)//gchar *content,GtkTextBuffer *buffer)
{
	gchar *object = g_new(gchar, strlen(str));
	strcpy(object,str);
	return object;
}

//! simply join two string to gether (this function free the input string)
/*!
    \return connected string
*//*
gchar *gbee_string_con (char *str1,char *str2)
{
	gchar *buffer = g_new(gchar,strlen(str1) + strlen(str2) -1);
	strcpy(buffer,str1);
	strcat(buffer,str2);
	g_free(str1);
	return object;
}
*/

//! find offset of str in source (start to search from begin of source)
/*!
    \param source text to use for find str within
    \param str    string tou want to find offset in source
    \param size   how much character you want to go forward and search (pass -1 for unlimited)
*/
gint gbee_string_find (const gchar *source,gchar *str,gint size)
{
	int i;
	gchar buffer[strlen(str)+1];	
	for (i = 0; source[i] != '\0' && (size == -1 || i < size) ; i++)
	{
		strncpy(buffer,&source[i],strlen(str));
		buffer[strlen(str)] = '\0';//terminate with end character
		if (g_strcmp0 (buffer,str) == 0)
		{
			return i;
		}
	}
	return -1;
}

//! find offset of str in source (start to search from end of source)
/*!FIXME:HERE MAYBE SOME BUG LIED!!!!!!!!
    \param source text to use for find str within
    \param str    string tou want to find offset in source
    \param size   how much character you want to go forward and search from end of string (pass -1 for unlimited)
*/
gint gbee_string_find_end (const gchar *source,gchar *str,gint size)
{
	int i,lenght,max;
	gchar buffer[strlen(str)+1];
	lenght = strlen(source);
	max = lenght - strlen(str);
	if (size == -1 || lenght <= size)
		size = lenght -1;
	for (i = 0; (size - i) > 0 ; i--)
	{
		strncpy(buffer,&source[max - i],strlen(str));
		buffer[strlen(str)] = '\0';//terminate with end character
		if (g_strcmp0 (buffer,str) == 0)
		{
			return i;
		}
	}
	return -1;
}

//! find offset of str in source (start to search from end of source)
/*!
    \param source text to use for find str within
    \param str    string tou want to find offset in source
    \param size   start character in source string
*/
gint gbee_string_find_start (const gchar *source,gchar *str,gint start)
{
	int i,lenght;
	gchar buffer[strlen(str)+1];
	lenght = strlen(source);
	if (start < 0 || start <= lenght)
		start = 0;	
	for (i = start;  i < lenght ; i++)
	{
		strncpy(buffer,&source[i],strlen(str));
		buffer[strlen(str)] = '\0';//terminate with end character
		if (g_strcmp0 (buffer,str) == 0)
		{
			return i;
		}
	}
	return -1;
}

//! replace all of "old" char to "new_one" char
/*!
    \param str text you want to replace with new char
	\param old char that replace with new_one
	\param rep char that replaced!!
*/
void gbee_string_change (gchar *str,gchar old,gchar rep)
{
	int i;
	for (i = 0; str[i] != '\0' ; i++)
	{
		if (str[i] ==  old)
			str[i] = rep;
	}
}
//! remolve all of "unvalid" string from str
/*!
    \param str     text you want to replace with new char
	\param unvalid text you want remove from context
*/
void gbee_string_remove (gchar *str,gchar *unvalid)
{
	int i,k;
	gchar buffer[strlen(unvalid)+1];
	gchar str_buffer[strlen(str)];
	for (i = 0; str[i] != '\0' ; i++)
	{
		str_buffer[i-k] = str[i];
		strncpy(buffer,&str[i],strlen(unvalid));
		buffer[strlen(unvalid)] = '\0';//terminate with end character
		if (g_strcmp0 (buffer,unvalid) == 0)
		{
			
		}
	}
	strcpy(str,str_buffer);
}

//! remove all string between start and end number (start from 0 like array index)
/*!
    \param str     text
	\param start   number of start chat
	\param end     number of end chat
	\param return  string that removed all character between start and end number (this should be freed)
*/
gchar *gbee_string_nremove (const gchar *str,const int start,const int end)
{
	int lenght = strlen(str);
	if (end < start || end > lenght - 1)
	{
		fprintf(stderr, "invalid use of function gbee_string_nremove, argument are end:%d\tstart:%d\n", start,end);
		exit(1);
	}
	lenght = lenght - (end - start);
	gchar *buffer     = g_strndup(str,start + 1);
	gchar *return_str = g_strconcat(buffer,str[end],NULL);
	free (buffer);
	return return_str;
}

//! remove multi line comment
/*!
    \param str     text
	\param start   number of start chat
	\param end     number of end chat
	\param return  string that remove multi comment from it (this should be freed)
				   if an error occurd it return a copy from input string
*/
gchar *gbee_remove_mcomment (const gchar *str)
{
	int start = gbee_string_find (str,"/*",-1);
	int end   = gbee_string_find_end (str,"*/",-1);
	if (start < 0 || end < 0 || end <= start)
		return g_strdup(str);
	return gbee_string_nremove(str,start,end);
}

//! remove comment from passed line
/*!
    \param str     text
	\param start   number of start chat
	\param end     number of end chat
	\param return  string that remove comment from it (this should be freed)
*/
gchar *gbee_remove_comment (const gchar *str)
{
	int start = gbee_string_find (str,"//",-1);
	int end   = strlen(str) - 1;
	if (start < 0 || end < 0 || end <= start)
		return g_strdup(str);
	return gbee_string_nremove(str,start,end);
}

//! replace old string with new one
/*!
    \param str  text you want to replace with new char
	\param orig char that replace with new_one
	\param rep  char that placed!!
*/
void gbee_string_replace (gchar *str,gchar *orig,gchar *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  strcpy(str,buffer);
}


//! determine this line is end of multiline comment or not (multiline comment end with */)
/*!
    \param  str line you want to determine is it coment or not
	\return return true if line is a multiline comment
*/
gint gbee_string_is_end_mcomment(const gchar *str)
{
	return gbee_string_find (str,"*/",-1);
}

//! determine this line is multiline comment or not (multiline comment start with /*)
/*!
    \param  str line you want to determine is it coment or not
	\return return offset of commet or -1 if line is not comment
*/
gint gbee_string_is_mcomment(const gchar *str)
{
	return gbee_string_find (str,"/*",-1);
}

//! determine this line is include or not
/*!
    \param  str line you want to determine is it include or not
	\return return true if line is a include
*/
gboolean gbee_string_is_include(const gchar *str)
{
	int i = gbee_string_find (str,"include",-1);
	if ( i == -1 )
		return FALSE;
	i--;
	for ( ; i >= 0 && str[i] == ' ' ; i--)
	{
		;//skip space
	}
	if (str[i] == '#')
		return TRUE;
	return FALSE;
}

//! determine this line is define or not
/*!
    \param  str line you want to determine is it include or not
	\return return true if line is a define
*/
gboolean gbee_string_is_define(const gchar *str)
{
	int i = gbee_string_find (str,"define",-1);
	if ( i == -1 )
		return FALSE;
	i--;
	for ( ; i >= 0 && str[i] == ' ' ; i--)
	{
		;//skip space
	}
	if (str[i] == '#')
	{
		return TRUE;
	}
	return FALSE;
}

//! determine this line is individual line comment or not (individual line comment start with //)
/*!
    \param  str line you want to determine is it coment or not
	\return return true if line is a individual line comment
*/
gint gbee_string_is_comment(const gchar *str)
{
	return gbee_string_find (str,"//",-1);
}

//! determine this line is multiline or not (have \ or not)
/*!
    \param  str line you want to determine is it multiline or not
	\return return true if line is a multiline
*/
gboolean gbee_string_is_multiline(const gchar *str)
{
	int i = strlen(str);
	if ( i == -1 || i == 0 )
		return FALSE;
	i--;
	//puts(str);
	for ( ; i > 0 && str[i] == ' ' ; i--)
	{
		;//skip space
	}
	if (str[i] == '\\')
	{
		return TRUE;
	}
	return FALSE;
}

//! determine this line is preprocessor or not
/*!
    \param  str line you want to determine is it preprocessor or not
	\return return true if line is a preprocessor
*/
gboolean gbee_string_is_preprocessor (const gchar *str)
{
	gchar *buffer = g_new(gchar,strlen(str) + 1);
	strcpy(buffer,str);
	g_strchug (buffer);
	gboolean return_data = g_str_has_prefix(buffer,"#");
	g_free(buffer);
	return return_data;
}

//! start filling all line flag
/*!
    \param  line   instance from GBeeLine (must be null terminated in value (line.value))
*/
void gbee_string_preparse (GbeeLine *lines)
{
	int i;
	gboolean incomment = FALSE;//if we are inside a multiline comment it set to true
	for ( i = 0 ; lines[i].value != NULL ; i++ )
	{
		if (incomment)
		{
			lines[i].comment_type   = GBEE_INSIDE_COMMENT;
			lines[i].comment_offset = gbee_string_is_end_mcomment(lines[i].value);
			if (lines[i].comment_offset != -1)
			{
				incomment                    = FALSE;
				lines[i].comment_type = GBEE_MULTILINE_COMMENT_END;
			}
			else
			{
				continue;
			}
		}
		lines[i].comment_offset = gbee_string_is_mcomment(lines[i].value);
		if (lines[i].comment_offset != -1)
		{
			incomment = TRUE;
			lines[i].comment_type   = GBEE_MULTILINE_COMMENT_START;
			if (gbee_string_is_end_mcomment(lines[i].value) != -1)
			{
				incomment                    = FALSE;
				lines[i].comment_type = GBEE_MULTILINE_COMMENT_ONE;
			}
		}
		else
		{
			lines[i].comment_offset = gbee_string_is_comment(lines[i].value);
			if (lines[i].comment_offset != -1)
			{
				lines[i].comment_type = GBEE_INDIVIDUAL_COMMENT;
			}
		}
		if (gbee_string_is_preprocessor(lines[i].value))
		{
			lines[i].pre_flag = TRUE;
			if (gbee_string_is_include(lines[i].value))
			{
				lines[i].include_flag = TRUE;
			}
			if (gbee_string_is_define(lines[i].value))
			{
			   lines[i].define_flag = TRUE;
			}
		}
		if (gbee_string_is_multiline (lines[i].value))
		{
			lines[i].multiline_flag = TRUE;
			while (gbee_string_is_multiline (lines[i].value))
			{
				lines[i+1].pre_flag       = lines[i].pre_flag;
				lines[i+1].include_flag   = lines[i].include_flag;
				lines[i+1].pro_flag       = lines[i].pro_flag;
				lines[i+1].command_flag   = lines[i].command_flag;
				lines[i+1].define_flag    = lines[i].define_flag;
				lines[i+1].infunc_flag    = lines[i].infunc_flag;
				lines[i+1].multiline_flag = lines[i].multiline_flag;
				lines[i+1].comment_type   = lines[i].comment_type;
				i++;
			}
		}
		else
		{
			;
		}
	}
}

//! change multiline to one line 
/*!
    \param  line   instance from GBeeLine (must be null terminated)
    \param  start  start number of multiline 
	\return return one line that contain all multilined flag after start number
*/
gchar *gbee_string_mk_oneline(GbeeLine *lines,const int start)
{
	int k,lenght = 1,j;
	k = 0;
	//puts(lines[start].value);
	for (k = 0 ; lines[start+k+1].value != NULL && (gbee_string_is_multiline (lines[start+k].value)); k++)
	{
		lenght += strlen(lines[start+k].value);
	}
	lenght += strlen(lines[start+k].value);
	int sLash_offset[k];
	const int end = start + k ;
	for (k = start; k < end  ; k++)
	{
		for (j = strlen(lines[k].value) - 1; j >= 0 ; j--)
		{
  			if (lines[k].value[j] == '\\')
  			{
  				sLash_offset[k - start] = j;
			    break;
			}
		}
	}
	gchar *str = g_new(gchar,lenght+end-start+1);
	str[0] = '\0';
	for (k = start; k < end  ; k++)
	{
		#ifdef GBEE_DEBUG
			printf("%d: %d ->%s\n",k - start,sLash_offset[k - start],lines[k].value);
		#endif
		strncat(str,lines[k].value,sLash_offset[k - start]);
		strcat(str," ");
	}
	strcat(str,lines[end].value);
	return str;
}

//! get line number and prepare it for parsing
//! this function remove comment and connect multiline to one line using 
//! function gbee_string_mk_oneline
/*!
    \param  line   instance from GBeeLine (must be null terminated)
    \param  number line number 
    \param  jump   retuen how many line parser should jump
	\return return one line that contain all multilined flag after start number
*/
gchar *gbee_string_prepare(GbeeLine *lines,const int number,int *jump)
{
	gchar *str;
	if (lines[number].multiline_flag || lines[number].command_flag == GBEE_MULTILINE_COMMENT_START)
		str = gbee_string_mk_oneline(lines,number);
	else
		str = g_strdup(lines[number].value);
	if (gbee_string_is_mcomment(str))
	{
		gchar *buffer = gbee_remove_mcomment(str);
		g_free(str);
		buffer = str;
	}
	if (gbee_string_is_comment(str))
	{
		gchar *buffer = gbee_remove_comment(str);
		g_free(str);
		buffer = str;
	}
	return str;
}

//! destroy or free all resource for GbeeLine
/*!
    \param  line   an instance from GBeeLine
*/
void *gbee_line_free(GbeeLine *line)
{
	;
}