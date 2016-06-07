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

#ifndef _GBEE_STRING_H_
#define _GBEE_STRING_H_

#include <gbee-define.h>


typedef struct _GbeeIter           GbeeIter;
typedef struct _GbeeLine           GbeeLine;
typedef struct _GbeeWord           GbeeWord;

struct _GbeeIter
{
	int line;
	int char_offset;
};

typedef enum 
{
	GBEE_INSIDE_COMMENT,// a line that inside a multiline comment
	GBEE_MULTILINE_COMMENT_ONE,//a line that have multiline commment like /* hi*/ 
	GBEE_MULTILINE_COMMENT_START,
	GBEE_MULTILINE_COMMENT_END,
	GBEE_INDIVIDUAL_COMMENT,
	GBEE_NO_COMMENT
} GBeeComment;

typedef enum 
{
	GBEE_CM,     // Comment in all type (multiline and individual comment)
	GBEE_DM,     // Define mean (for example in #define hello mello , mello is Define mean)
	GBEE_DW,     // Define word (for example in #define hello mello , mello is Define word)
	GBEE_TYPE,   // Type such as int
	GBEE_KEYWORD,// for highlight use of define not for definistion
	GBEE_FP,     // Function name prototype
	GBEE_DP,     // Define Prototype
	GBEE_FN,     // Function Name (in use) it's defrent from function prototype name
	GBEE_UN      // Undefined
} GbeeWordType;

struct _GbeeLine
{
	gboolean        pre_flag;//preproccessor flag
	gboolean        include_flag;
	gboolean        pro_flag;//prototype flag
	gboolean        command_flag;
	gboolean        multiline_flag;//if line end with \ this flag change to true(still skip scape)
	gboolean        define_flag;
	gboolean        infunc_flag;//inside the function
	GBeeComment     comment_type;
	GbeeWord      **words;//all words of line save in a array (word are part of a line that take part with space)
	gchar          *value;
	gint            line_number;
	gint            comment_offset;
};

struct _GbeeWord
{
	GtkTextIter   start_iter;
	GtkTextIter   end_iter;
	GbeeWordType  type;
	gboolean      string_flag;//if word inside two " then this flag change to true
	gboolean      char_flag;//if word inside two " then this flag change to true
	gchar        *value;
};


gchar     *gbee_string_new             (const char *str);
gint       gbee_string_find            (const gchar *source,gchar *str,gint size);
gint       gbee_string_find_end        (const gchar *source,gchar *str,gint size);
gint       gbee_string_find_start      (const gchar *source,gchar *str,gint start);
void       gbee_string_change          (gchar *str,gchar old,gchar rep);
void       gbee_string_remove          (gchar *str,gchar *unvalid);
void       gbee_string_replace         (gchar *str,gchar *orig,gchar *rep);
gchar     *gbee_string_mk_oneline      (GbeeLine *lines,const int start);
gchar     *gbee_string_prepare         (GbeeLine *lines,const int number,int *jump);
gint       gbee_string_is_end_mcomment (const gchar *str);
gint       gbee_string_is_mcomment     (const gchar *str);
gboolean   gbee_string_is_include      (const gchar *str);
gboolean   gbee_string_is_define       (const gchar *str);
gint       gbee_string_is_comment      (const gchar *str);
gboolean   gbee_string_is_multiline    (const gchar *str);
gboolean   gbee_string_is_preprocessor (const gchar *str);
GbeeWord **gbee_string_fill_word       (gchar *str);
void       gbee_string_preparse        (GbeeLine *line);
void      *gbee_line_free              (GbeeLine *line);


#endif /* _GBEE_STRING_H_ */
