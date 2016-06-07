/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PURE
 * Copyright (C) bijan 2012 <bijan@bijan-P5KC>
 * 
 * PURE is free software: you can redistribute it and/or modify it
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
 * 
 * GbeeIntercept: it's an object for open source file, get include directory
 * ,get project base directory, split buffer to line and word, detect comment,
 * include, define,function name in prototype, parse include file for define list
 * and etc
 * 
 */

#ifndef _GBEE_INTERCEPT_H_
#define _GBEE_INTERCEPT_H_

#include <glib-object.h>
#include <gbee-define.h>
#include <gbee-string.h>
#include <gbee-iparser.h>

G_BEGIN_DECLS

#define GBEE_TYPE_INTERCEPT             (gbee_intercept_get_type ())
#define GBEE_INTERCEPT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GBEE_TYPE_INTERCEPT, GbeeIntercept))
#define GBEE_INTERCEPT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GBEE_TYPE_INTERCEPT, GbeeInterceptClass))
#define GBEE_IS_INTERCEPT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GBEE_TYPE_INTERCEPT))
#define GBEE_IS_INTERCEPT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GBEE_TYPE_INTERCEPT))
#define GBEE_INTERCEPT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GBEE_TYPE_INTERCEPT, GbeeInterceptClass))

typedef struct _GbeeInterceptClass GbeeInterceptClass;
typedef struct _GbeeIntercept      GbeeIntercept;


struct _GbeeInterceptClass
{
	GObjectClass parent_class;
};

struct _GbeeIntercept
{
	GObject parent_instance;
};

GType          gbee_intercept_get_type    (void) G_GNUC_CONST;
GbeeIntercept *gbee_intercept_new         (char *filename,GList *includes);
int            gbee_intercept_get_offset  (GbeeIntercept *object,int linenumber,int char_num);
void           gbee_intercept_get_iter    (GbeeIntercept *object,GbeeIter iter,GtkTextIter *return_iter);
gint           gbee_intercept_find        (gchar *source,gchar *str,gint size);

G_END_DECLS

#endif /* _GBEE_INTERCEPT_H_ */