#include "mainstruct.h"
#include "appender.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
MainStructB make_msb();
void destroy_msb(MainStructB);
int insert_msb(MainStructB, void *, void *);
int remove_msb(MainStructB, void *);
int get_size_msb(MainStructB);
int exists_msb(MainStructB, void *);

/* Metodos privados */

// ------------------------------------------------------------------------------

typedef struct mainstructb
{
    GHashTable *table;
} * MainStructB;

// ------------------------------------------------------------------------------

MainStructB make_msb()
{
    MainStructB m = g_malloc(sizeof(struct mainstructb));
    m->table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroy_appender);
    return m;
}

void destroy_msb(MainStructB m)
{
    if (m)
    {
        g_hash_table_destroy(m->table);
        //g_hash_table_destroy(m->table);
        g_free(m);
    }
}

int insert_msb(MainStructB m, void *key, void *value)
{
    void *tmp;
    //Se já existir o elemento
    if ((tmp = g_hash_table_lookup(m->table, key)))
        update_appender(tmp, value);
    else
        g_hash_table_insert(m->table, key, make_appender());
    return tmp ? 1 : 0;
}

int remove_msb(MainStructB m, void *key)
{
    return g_hash_table_remove(m->table, key);
}

int get_size_msb(MainStructB m)
{
    return g_hash_table_size(m->table);
}

int exists_msb(MainStructB m, void *key)
{
    return g_hash_table_contains(m->table, key);
}

int get_client_v(MainStructB b, char *s)
{
    int r = -1;
    void *tmp = g_hash_table_lookup(b->table, s);
    if (tmp)
        r = get_app_vendas(tmp);
    return r;
}