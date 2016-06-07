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

#ifndef _GBEE_PARSER_H_
#define _GBEE_PARSER_H_

#include "gbee-intercept.h"

G_BEGIN_DECLS

#define GBEE_TYPE_PARSER             (gbee_parser_get_type ())
#define GBEE_PARSER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GBEE_TYPE_PARSER, GbeeParser))
#define GBEE_PARSER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GBEE_TYPE_PARSER, GbeeParserClass))
#define GBEE_IS_PARSER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GBEE_TYPE_PARSER))
#define GBEE_IS_PARSER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GBEE_TYPE_PARSER))
#define GBEE_PARSER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GBEE_TYPE_PARSER, GbeeParserClass))

typedef struct _GbeeParserClass GbeeParserClass;
typedef struct _GbeeParser GbeeParser;
typedef struct _GbeeParserPrivate GbeeParserPrivate;


struct _GbeeParserClass
{
	GObjectClass parent_class;
};

struct _GbeeParser
{
	GObject parent_instance;

    GbeeParserPrivate *priv; 
};

GType gbee_parser_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* _GBEE_PARSER_H_ */
