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

#ifndef _GBEE_IPARSER_H_
#define _GBEE_IPARSER_H_

#include <gbee-define.h>
#include <gbee-string.h>
#include <sqlite3.h>

G_BEGIN_DECLS

#define GBEE_TYPE_IPARSER             (gbee_iparser_get_type ())
#define GBEE_IPARSER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GBEE_TYPE_IPARSER, GbeeIparser))
#define GBEE_IPARSER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GBEE_TYPE_IPARSER, GbeeIparserClass))
#define GBEE_IS_IPARSER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GBEE_TYPE_IPARSER))
#define GBEE_IS_IPARSER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GBEE_TYPE_IPARSER))
#define GBEE_IPARSER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GBEE_TYPE_IPARSER, GbeeIparserClass))

typedef struct _GbeeIparserClass   GbeeIparserClass;
typedef struct _GbeeIparser        GbeeIparser;
typedef struct _GbeeIparserPrivate GbeeIparserPrivate;
typedef struct _GbeeIdata          GbeeIdata;


struct _GbeeIparserClass
{
	GObjectClass parent_class;
};

struct _GbeeIdata
{
	GData **Included;
	GData **Define;
	GData **Types;
	GData **Functions;
};

struct _GbeeIparser
{
	GObject             parent_instance;
	sqlite3            *db;
    GbeeIparserPrivate *priv; 
};


GType        gbee_iparser_get_type (void) G_GNUC_CONST;
void         gbee_iparser_parse(GbeeIparser *object,gchar *IName);
GbeeIparser *gbee_iparser_new (GList *includes);
void         gbee_line_delete (GbeeLine *object);

G_END_DECLS

#endif /* _GBEE_IPARSER_H_ */
