#include "mainstruct.h"
#include "appender.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
DBase make_dbase();
void destroy_dbase(DBase);
int insert_dbase(DBase, void *, void *);
int remove_dbase(DBase, void *);
int get_size_dbase(DBase);
int exists_dbase(DBase, void *);

/* Metodos privados */

// ------------------------------------------------------------------------------

typedef struct data_base
{
    GHashTable *table;  /**< Estrutura de dados em uso */
} * DBase;

// ------------------------------------------------------------------------------

/**
 * \brief Aloca espaço em memória para a a estrutura de base de dados.
 **/
DBase make_dbase()
{
    DBase m = g_malloc(sizeof(struct data_base));
    m->table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroy_appender);
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
    void *tmp;
    //Se já existir o elemento
    if ((tmp = g_hash_table_lookup(m->table, key)))
        update_appender(tmp, value);
    else
        g_hash_table_insert(m->table, key, make_appender());
    return tmp ? 1 : 0;
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