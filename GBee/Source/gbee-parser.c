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

#include "gbee-parser.h"
struct _GbeeParserPrivate
{
	GbeeIntercept interceptor;
};

#define GBEE_PARSER_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), GBEE_TYPE_PARSER, GbeeParserPrivate))



G_DEFINE_TYPE (GbeeParser, gbee_parser, G_TYPE_OBJECT);

static void
gbee_parser_init (GbeeParser *gbee_parser)
{
    GbeeParserPrivate *priv = GBEE_PARSER_GET_PRIVATE(gbee_parser);

	/* TODO: Add initialization code here */
}

static void
gbee_parser_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (gbee_parser_parent_class)->finalize (object);
}

static void
gbee_parser_class_init (GbeeParserClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (GbeeParserPrivate));

	object_class->finalize = gbee_parser_finalize;
}

