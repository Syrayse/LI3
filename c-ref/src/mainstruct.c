#include "mainstruct.h"
#include "appender.h"
#include "gArray.h"
#include "util.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
DBase make_dbase();
void destroy_dbase(DBase);
int insert_dbase(DBase, void *, void *);
int remove_dbase(DBase, void *);
int get_size_dbase(DBase);
int get_not_sold_dbase(DBase);
int exists_dbase(DBase, void *);
int get_client_v(DBase b, char *s);
void **get_overall_clients(DBase b, size_t *h);
void **dump_ordered_abstract(DBase b, GHFunc f, size_t *h);

/* Metodos privados */
static void insert_sold_by_all(void *key, void *value, void *user_data);
// ------------------------------------------------------------------------------

typedef struct data_base
{
    int n_notsold;
    GHashTable *table; /**< Estrutura de dados em uso */
} * DBase;

// ------------------------------------------------------------------------------

/**
 * \brief Aloca espaço em memória para a a estrutura de base de dados.
 **/
DBase make_dbase()
{
    DBase m = g_malloc(sizeof(struct data_base));
    m->table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroy_appender);
    m->n_notsold = 0;
    return m;
}

/**
 * \brief Liberta o espaço em memória alocado para a estrutura de base de dados.
 **/
void destroy_dbase(DBase m)
{
    if (m)
    {
        g_hash_table_destroy(m->table);
        g_free(m);
    }
}

/**
 * \brief Coloca na base de dados, numa dada key, um value, ou utilzia este para atualizar a informação que já lá se encontra.
 **/
int insert_dbase(DBase m, void *key, void *value)
{
    int r = 1;
    void *tmp = g_hash_table_lookup(m->table, key);
    APPENDER t = NULL;
    //Se já existir o elemento

    if (!tmp)
    {
        r = 0;
        t = make_appender();
        g_hash_table_insert(m->table, key, t);
        m->n_notsold++;
        tmp = (void *)t;
    }

    if (value)
    {
        if (!get_t_vendas(tmp))
            m->n_notsold--;
        update_appender(tmp, value);
    }

    return r;
}

/**
 * \brief Remove uma `key` da base de dados. 
 **/
int remove_dbase(DBase m, void *key)
{
    return g_hash_table_remove(m->table, key);
}

/**
 * \brief Calcula o tamanho da base de dados.
 **/
int get_size_dbase(DBase m)
{
    return g_hash_table_size(m->table);
}

int get_not_sold_dbase(DBase m)
{
    return m->n_notsold;
}

/**
 * \brief Verifica se uma chave existe na base de dados.
 **/
int exists_dbase(DBase m, void *key)
{
    return g_hash_table_contains(m->table, key);
}
/**
 * \brief Retorna o numero de vendas de um elemento na base de dados.
 * 
 * retorna -1 se o cliente não existir.
 **/
int get_client_v(DBase b, char *s)
{
    int r = -1;
    void *tmp = g_hash_table_lookup(b->table, s);
    if (tmp)
        r = get_t_vendas(tmp);
    return r;
}

void **get_overall_clients(DBase b, size_t *h)
{
    return dump_ordered_abstract(b, insert_sold_by_all, h);
}

void **dump_ordered_abstract(DBase b, GHFunc f, size_t *h)
{
    void **tmp;

    GrowingArray g = make_garray(sizeof(char *), NULL);

    g_hash_table_foreach(b->table, f, g);

    sort_garray(g, strcmp_client);

    tmp = dump_elems_garray(g, h);

    destroy_garray(g);

    return tmp;
}

static void insert_sold_by_all(void *key, void *value, void *user_data)
{
    if (user_data && is_sold_by_all((APPENDER)value))
        insert_elem_garray((GrowingArray)user_data, key);
}