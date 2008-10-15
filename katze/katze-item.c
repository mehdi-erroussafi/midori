/*
 Copyright (C) 2008 Christian Dywan <christian@twotoasts.de>

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 See the file COPYING for the full license text.
*/

#include "katze-item.h"

#include "katze-utils.h"

#include <glib/gi18n.h>

/**
 * SECTION:katze-item
 * @short_description: A useful item
 * @see_also: #KatzeArray
 *
 * #KatzeItem is a particularly useful item that provides
 * several commonly needed properties.
 */

G_DEFINE_TYPE (KatzeItem, katze_item, G_TYPE_OBJECT)

enum
{
    PROP_0,

    PROP_NAME,
    PROP_TEXT,
    PROP_URI,
    PROP_ICON,
    PROP_TOKEN,
    PROP_ADDED,
    PROP_VISITS
};

static void
katze_item_finalize (GObject* object);

static void
katze_item_set_property (GObject*      object,
                         guint         prop_id,
                         const GValue* value,
                         GParamSpec*   pspec);

static void
katze_item_get_property (GObject*    object,
                         guint       prop_id,
                         GValue*     value,
                         GParamSpec* pspec);

static void
katze_item_class_init (KatzeItemClass* class)
{
    GObjectClass* gobject_class;
    GParamFlags flags;

    gobject_class = G_OBJECT_CLASS (class);
    gobject_class->finalize = katze_item_finalize;
    gobject_class->set_property = katze_item_set_property;
    gobject_class->get_property = katze_item_get_property;

    flags = G_PARAM_READWRITE | G_PARAM_CONSTRUCT;

    g_object_class_install_property (gobject_class,
                                     PROP_NAME,
                                     g_param_spec_string (
                                     "name",
                                     "Name",
                                     "The name of the item",
                                     NULL,
                                     flags));

    g_object_class_install_property (gobject_class,
                                     PROP_TEXT,
                                     g_param_spec_string (
                                     "text",
                                     "Text",
                                     "The descriptive text of the item",
                                     NULL,
                                     flags));

    g_object_class_install_property (gobject_class,
                                     PROP_URI,
                                     g_param_spec_string (
                                     "uri",
                                     "URI",
                                     "The URI of the item",
                                     NULL,
                                     flags));

    g_object_class_install_property (gobject_class,
                                     PROP_ICON,
                                     g_param_spec_string (
                                     "icon",
                                     "Icon",
                                     "The icon of the item",
                                     NULL,
                                     flags));

    g_object_class_install_property (gobject_class,
                                     PROP_TOKEN,
                                     g_param_spec_string (
                                     "token",
                                     "Token",
                                     "The token of the item",
                                     NULL,
                                     flags));

    g_object_class_install_property (gobject_class,
                                     PROP_ADDED,
                                     g_param_spec_string (
                                     "added",
                                     "Added",
                                     "When the item was added",
                                     NULL,
                                     flags));

    g_object_class_install_property (gobject_class,
                                     PROP_VISITS,
                                     g_param_spec_int (
                                     "visits",
                                     "Visits",
                                     "The number of visits of the item",
                                     G_MININT,
                                     G_MAXINT,
                                     0,
                                     flags));

}



static void
katze_item_init (KatzeItem* item)
{
    /* Nothing to do here */
}

static void
katze_item_finalize (GObject* object)
{
    KatzeItem* item = KATZE_ITEM (object);

    g_free (item->name);
    g_free (item->text);
    g_free (item->uri);
    g_free (item->icon);
    g_free (item->token);
    g_free (item->added);

    G_OBJECT_CLASS (katze_item_parent_class)->finalize (object);
}

static void
katze_item_set_property (GObject*      object,
                         guint         prop_id,
                         const GValue* value,
                         GParamSpec*   pspec)
{
    KatzeItem* item = KATZE_ITEM (object);

    switch (prop_id)
    {
    case PROP_NAME:
        katze_assign (item->name, g_value_dup_string (value));
        break;
    case PROP_TEXT:
        katze_assign (item->text, g_value_dup_string (value));
        break;
    case PROP_URI:
        katze_assign (item->uri, g_value_dup_string (value));
        break;
    case PROP_ICON:
        katze_assign (item->icon, g_value_dup_string (value));
        break;
    case PROP_TOKEN:
        katze_assign (item->token, g_value_dup_string (value));
        break;
    case PROP_ADDED:
        katze_assign (item->added, g_value_dup_string (value));
        break;
    case PROP_VISITS:
        item->visits = g_value_get_int (value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
katze_item_get_property (GObject*    object,
                         guint       prop_id,
                         GValue*     value,
                         GParamSpec* pspec)
{
    KatzeItem* item = KATZE_ITEM (object);

    switch (prop_id)
    {
    case PROP_NAME:
        g_value_set_string (value, item->name);
        break;
    case PROP_TEXT:
        g_value_set_string (value, item->text);
        break;
    case PROP_URI:
        g_value_set_string (value, item->uri);
        break;
    case PROP_ICON:
        g_value_set_string (value, item->icon);
        break;
    case PROP_TOKEN:
        g_value_set_string (value, item->token);
        break;
    case PROP_ADDED:
        g_value_set_string (value, item->added);
        break;
    case PROP_VISITS:
        g_value_set_int (value, item->visits);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

/**
 * katze_item_new:
 *
 * Creates a new #KatzeItem.
 *
 * Return value: a new #KatzeItem
 **/
KatzeItem*
katze_item_new (void)
{
    KatzeItem* item = g_object_new (KATZE_TYPE_ITEM, NULL);

    return item;
}

/**
 * katze_item_get_name:
 * @item: a #KatzeItem
 *
 * Retrieves the name of @item.
 *
 * Return value: the name of the item
 **/
const gchar*
katze_item_get_name (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->name;
}

/**
 * katze_item_set_name:
 * @item: a #KatzeItem
 * @name: a string
 *
 * Sets the name of @item.
 **/
void
katze_item_set_name (KatzeItem*   item,
                     const gchar* name)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    katze_assign (item->name, g_strdup (name));
    g_object_notify (G_OBJECT (item), "name");
}

/**
 * katze_item_get_text:
 * @item: a #KatzeItem
 *
 * Retrieves the descriptive text of @item.
 *
 * Return value: the text of the item
 **/
const gchar*
katze_item_get_text (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->text;
}

/**
 * katze_item_set_text:
 * @item: a #KatzeItem
 * @description: a string
 *
 * Sets the descriptive text of @item.
 **/
void
katze_item_set_text (KatzeItem*   item,
                     const gchar* text)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    katze_assign (item->text, g_strdup (text));
    g_object_notify (G_OBJECT (item), "text");
}

/**
 * katze_item_get_uri:
 * @item: a #KatzeItem
 *
 * Retrieves the URI of @item.
 *
 * Return value: the URI of the item
 **/
const gchar*
katze_item_get_uri (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->uri;
}

/**
 * katze_item_set_uri:
 * @item: a #KatzeItem
 * @uri: a string
 *
 * Sets the URI of @item.
 **/
void
katze_item_set_uri (KatzeItem*   item,
                    const gchar* uri)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    katze_assign (item->uri, g_strdup (uri));
    g_object_notify (G_OBJECT (item), "uri");
}

/**
 * katze_item_get_icon:
 * @item: a #KatzeItem
 *
 * Retrieves the icon of @item.
 *
 * Return value: the icon of the item
 **/
const gchar*
katze_item_get_icon (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->icon;
}

/**
 * katze_item_set_icon:
 * @item: a #KatzeItem
 * @icon: a string
 *
 * Sets the icon of @item.
 **/
void
katze_item_set_icon (KatzeItem*   item,
                     const gchar* icon)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    katze_assign (item->icon, g_strdup (icon));
    g_object_notify (G_OBJECT (item), "icon");
}

/**
 * katze_item_get_token:
 * @item: a #KatzeItem
 *
 * Retrieves the token of @item.
 *
 * Return value: the token of the item
 **/
const gchar*
katze_item_get_token (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->token;
}

/**
 * katze_item_set_token:
 * @item: a #KatzeItem
 * @token: a string
 *
 * Sets the token of @item.
 **/
void
katze_item_set_token (KatzeItem*   item,
                      const gchar* token)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    katze_assign (item->token, g_strdup (token));
    g_object_notify (G_OBJECT (item), "token");
}

/**
 * katze_item_get_added:
 * @item: a #KatzeItem
 *
 * Determines when @item was added.
 *
 * Return value: a timestamp
 **/
const gchar*
katze_item_get_added (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->added;
}

/**
 * katze_item_set_added:
 * @item: a #KatzeItem
 * @added: a timestamp
 *
 * Sets when @item was added.
 **/
void
katze_item_set_added (KatzeItem*   item,
                      const gchar* added)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    katze_assign (item->added, g_strdup (added));
    g_object_notify (G_OBJECT (item), "added");
}

/**
 * katze_item_get_visits:
 * @item: a #KatzeItem
 *
 * Retrieves the number of visits of @item.
 *
 * Return value: the number of visits
 **/
gint
katze_item_get_visits (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), -1);

    return item->visits;
}

/**
 * katze_item_set_visits:
 * @item: a #KatzeItem
 * @visits: an integer
 *
 * Sets the number of visits of @item.
 **/
void
katze_item_set_visits (KatzeItem* item,
                       gint       visits)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    item->visits = visits;
    g_object_notify (G_OBJECT (item), "visits");
}

/**
 * katze_item_get_parent:
 * @item: a #KatzeItem
 *
 * Determines the parent of @item.
 *
 * Return value: the parent of the item
 **/
gpointer
katze_item_get_parent (KatzeItem* item)
{
    g_return_val_if_fail (KATZE_IS_ITEM (item), NULL);

    return item->parent;
}

/**
 * katze_item_set_parent:
 * @item: a #KatzeItem
 * @parent: the new parent
 *
 * Sets the parent of @item.
 *
 * This is intended for item container implementations and
 * should not be used otherwise.
 **/
void
katze_item_set_parent (KatzeItem* item,
                       gpointer   parent)
{
    g_return_if_fail (KATZE_IS_ITEM (item));

    if (parent)
        g_object_ref (parent);
    katze_object_assign (item->parent, parent);
    /* g_object_notify (G_OBJECT (item), "parent"); */
}

