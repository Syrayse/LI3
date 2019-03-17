#include "dbase.h"
#include "statinfo.h"
#include "gArray.h"
#include "util.h"
#include "set.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
DBase dbase_make(int flag);
void dbase_destroy(DBase);
void dbase_add(DBase, void *, void *);
int dbase_remove(DBase, void *);
int dbase_size(DBase);
int dbase_size_specific(DBase, char);
int dbase_contains(DBase, void *);
char **dbase_get_overall(DBase, size_t *, char);
char **dbase_get_not_sold(DBase, size_t *, int);

/* Metodos privados */
static void **dump_ordered_abstract(DBase b, GHFunc f, size_t *h, char flag);
static void insert_sold_by_all(void *key, void *value, void *user_data);
static void insert_in_dbase_arr(DBase db, int ind, void *key);
static void insert_not_bought(void *key, void *value, void *user_data);
static void dbase_build_arrays(DBase db);
static void *my_statinfo_make(int flag);
static void my_statinfo_update(void *, void *);
static void my_statinfo_destroy(void *a);

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de base de dados principal.
 * 
 * Atual contentor de toda a informação do projeto.
 **/
typedef struct data_base
{
    int identity,
        total_size,
        not_init_n,
        max_size;
    StrSet *table; /**< Estrutura de dados em uso */
    GrowingArray not_bought[4];
} * DBase;

// ------------------------------------------------------------------------------

/**
 * \brief Aloca espaço em memória para a a estrutura de base de dados.
 **/
DBase dbase_make(int flag)
{
    int i;
    DBase db = g_malloc(sizeof(struct data_base));
    db->total_size = 0;
    db->not_init_n = 0;
    db->max_size = 'Z' - 'A' + 1;
    db->identity = flag;

    db->table = g_malloc(sizeof(StrSet) * db->max_size);

    for (i = 0; i < db->max_size; i++)
        db->table[i] = strset_make(g_free, my_statinfo_destroy, my_statinfo_make, my_statinfo_update, flag);

    db->not_bought[0] = NULL;

    return db;
}

/**
 * \brief Liberta o espaço em memória alocado para a estrutura de base de dados.
 **/
void dbase_destroy(DBase db)
{
    int i;

    if (db)
    {
        for (i = 0; i < db->max_size; i++)
            strset_destroy(db->table[i]);

        if (db->not_bought[0])
        {
            for (i = 0; i < 4; i++)
                garray_destroy(db->not_bought[i]);
        }

        g_free(db->table);
        g_free(db);
    }
}

/**
 * \brief Coloca na base de dados, numa dada key, um value, ou utilzia este para atualizar a informação que já lá se encontra.
 **/
void dbase_add(DBase db, void *key, void *user_data)
{
    int r = strset_add(db->table[conv_str(key)], key, user_data);

    if (r)
    {
        db->total_size++;
        db->not_init_n++;
    }
    else if (!r)
    {
        db->not_init_n--;
    }
}

/**
 * \brief Remove uma `key` da base de dados. 
 **/
int dbase_remove(DBase db, void *key)
{
    return strset_remove(db->table[conv_str(key)], key);
}

/**
 * \brief Calcula o tamanho da base de dados.
 **/
int dbase_size(DBase m)
{
    int i, r = 0;

    for (i = 0; i < m->max_size; i++)
    {
        r += strset_size(m->table[i]);
    }

    return r;
}

/**
 * \brief Calcula o numero de chaves com que começam com uma dada letra.
 **/
int dbase_size_specific(DBase db, char flag)
{
    return strset_size(db->table[flag - 'A']);
}

/**
 * \brief Verifica se uma chave existe na base de dados.
 **/
int dbase_contains(DBase db, void *key)
{
    return strset_contains(db->table[conv_str(key)], key);
}

char **dbase_get_overall(DBase db, size_t *h, char flag)
{
    return (char **)dump_ordered_abstract(db, insert_sold_by_all, h, flag);
}

char **dbase_get_not_sold(DBase db, size_t *n, int filial)
{
    if (!db->not_bought[0])
        dbase_build_arrays(db);

    return (char **)garray_dump_elems(db->not_bought[filial], n);
}

static void **dump_ordered_abstract(DBase b, GHFunc f, size_t *h, char flag)
{
    int i;
    void **tmp;

    GrowingArray g = garray_make(sizeof(char *), NULL);

    if (flag)
        strset_foreach(b->table[flag - 'A'], f, g);
    else
    {
        for (i = 0; i < b->max_size; i++)
            strset_foreach(b->table[i], f, g);
    }

    garray_sort(g, mystrcmp);

    tmp = garray_dump_elems(g, h);

    garray_destroy(g);

    return tmp;
}

static void insert_sold_by_all(void *key, void *value, void *user_data)
{
    if (user_data && statinfo_is_sold_by_all((StatInfo)value))
        garray_add((GrowingArray)user_data, key);
}

static void insert_in_dbase_arr(DBase db, int ind, void *key)
{
    if (db && is_between(ind, 0, 4))
    {
        garray_add(db->not_bought[ind], key);
    }
}

static void insert_not_bought(void *key, void *value, void *user_data)
{
    int filial, nst = 0;
    if (user_data)
    {
        for (filial = 1; filial <= N_FILIAIS; filial++)
        {
            if (!get_t_fil_vendas((StatInfo)value, filial))
            {
                insert_in_dbase_arr((DBase)user_data, filial, key);
                ++nst;
            }

            if (nst == N_FILIAIS)
                insert_in_dbase_arr((DBase)user_data, 0, key);
        }
    }
}

static void dbase_build_arrays(DBase db)
{
    int i;

    if (!db->not_bought[0])
    {
        for (i = 0; i < 4; i++)
            db->not_bought[i] = garray_make(sizeof(char *), NULL);

        for (i = 0; i < db->max_size; i++)
            strset_foreach(db->table[i], insert_not_bought, db);

        for (i = 0; i < 4; i++)
            garray_sort(db->not_bought[i], mystrcmp);
    }
}

static void *my_statinfo_make(int flag)
{
    return (void *)statinfo_make(flag);
}

static void my_statinfo_update(void *app, void *user)
{
    statinfo_update((StatInfo)app, user);
}

static void my_statinfo_destroy(void *a)
{
    statinfo_destroy((StatInfo)a);
}