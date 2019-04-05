/**
 * @file set.c
 * \brief Ficheiro que contém toda a codificação necessária à classe `Set`.
 * 
 * Esta classe permite que dada uma chave exista uma correspondência unívoca à mesma ou ao valor anexado a esta.
 */

#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `Set`.
 */
typedef struct set
{
    GHashTable *table; /**< Contentor onde é guardada toda a informação de chave e valores. */
    f_maker fm;        /**< Função que permite criar memória para os valores necessários. */
    f_update fu;       /**< Função de atualização que visa atualizar os valores do conjunto. */
} * Set;

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
Set set_make(GHashFunc hash_f, GEqualFunc key_equal_f, GFreeFunc ffkey, GFreeFunc ffvalue, f_maker fm, f_update fu);
void set_destroy(Set set);
int set_add(Set set, gpointer key, gpointer user_data);
int set_remove(Set set, gpointer key);
void set_foreach(Set set, GHFunc fer, gpointer user_data);
int set_contains(Set set, gpointer key);
int set_size(Set set);
gpointer set_lookup(Set set, gpointer key);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

Set set_make(GHashFunc hash_f, GEqualFunc key_equal_f, GFreeFunc ffkey, GFreeFunc ffvalue, f_maker fm, f_update fu)
{
    Set set = g_malloc(sizeof(struct set));

    set->table = g_hash_table_new_full(hash_f, key_equal_f, ffkey, ffvalue);

    set->fm = fm;

    set->fu = fu;

    return set;
}

void set_destroy(Set set)
{
    if (set)
    {
        g_hash_table_destroy(set->table);

        g_free(set);
    }
}

int set_add(Set set, gpointer key, gpointer user_data)
{
    int r = 1;
    gpointer dumkey, dumvalue;
    dumkey = dumvalue = NULL;

    if (!g_hash_table_lookup_extended(set->table, key, &dumkey, &dumvalue))
    {
        r = 0;

        if (set->fm)
        {
            dumvalue = (*set->fm)();
        }

        g_hash_table_insert(set->table, key, dumvalue);
    }

    if (dumvalue && user_data && set->fu)
    {

        (*set->fu)(dumvalue, user_data);
    }

    return r;
}

int set_contains(Set set, gpointer key)
{
    return g_hash_table_contains(set->table, key);
}

int set_remove(Set set, gpointer key)
{
    return g_hash_table_remove(set->table, key);
}

void set_foreach(Set set, GHFunc fe, gpointer user_data)
{
    g_hash_table_foreach(set->table, fe, user_data);
}

int set_size(Set set)
{
    return g_hash_table_size(set->table);
}

gpointer set_lookup(Set set, gpointer key)
{
    return g_hash_table_lookup(set->table, key);
}