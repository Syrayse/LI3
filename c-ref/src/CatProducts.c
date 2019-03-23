#include "CatProducts.h"
#include "set.h"
#include "gArray.h"
#include "adition.h"
#include "record.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, char *product);
void CatProducts_add_product(CatProducts cp, char *product);
void CatProducts_add_trans(CatProducts cp, char *product, int filial, gID trans_id);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);
gID *CatProducts_drop_trans(CatProducts cp, char *product, int filial, int *s);
int CatProducts_t_not_sold(CatProducts cp);
char **catProducts_t_all_not_sold(CatProducts cp, int *s);
char **catProducts_t_not_sold_filial(CatProducts cp, int *s, int filial);

/* Metodos privados */
static void build_internal_arr(CatProducts a);
static void insert_not_bought(void *key, void *value, void *user_data);

// ------------------------------------------------------------------------------

typedef struct cat_products
{
    GrowingArray not_sold[N_FILIAIS + 1];
    StrSet products[N_LETTER];
} * CatProducts;

// ------------------------------------------------------------------------------

/* METODOS PUBLICOS BELOW */
CatProducts CatProducts_make()
{
    int i;

    CatProducts cp = g_malloc(sizeof(struct cat_products));

    cp->not_sold[0] = NULL;

    for (i = 0; i < N_LETTER; i++)
        cp->products[i] = strset_make(g_free, adition_destroy, adition_make, adition_add, adition_is_empty, -1);

    return cp;
}

void CatProducts_destroy(CatProducts cp)
{
    int i;

    if (cp)
    {
        for (i = 0; i < N_LETTER; i++)
            strset_destroy(cp->products[i]);

        if (cp->not_sold[0])
        {
            for (i = 0; i <= N_FILIAIS; i++)
                garray_destroy(cp->not_sold[i]);
        }

        g_free(cp);
    }
}

int CatProducts_exists(CatProducts cp, char *product)
{
    return strset_contains(cp->products[conv_str(product)], product);
}

void CatProducts_add_product(CatProducts cp, char *product)
{
    int p = conv_str(product);

    strset_add(cp->products[p], product, NULL);
}

void CatProducts_add_trans(CatProducts cp, char *product, int filial, gID trans_id)
{
    void *r = NULL;
    gID gg[2];
    int p = conv_str(product);

    if ((r = strset_lookup(cp->products[p], product)))
    {
        gg[0] = trans_id;
        gg[1] = filial;
        //printf("gg:%ld\n",gg);
        strset_add(cp->products[p], product, gg);
    }
}

char **CatProducts_dump_ordered(CatProducts cp, int *s, char let)
{
    char **r = NULL;

    if (is_between(let, 'A', 'Z'))
    {
        r = strset_dump_ordered(cp->products[let - 'A'], s);
    }

    return r;
}

gID *CatProducts_drop_trans(CatProducts cp, char *product, int filial, int *s)
{
    gID *r = NULL;
    int p = conv_str(product);
    void *val;

    if ((val = strset_lookup(cp->products[p], product)))
        r = adition_dump(val, filial, s);

    return r;
}

int CatProducts_t_not_sold(CatProducts cp)
{
    int i, r = 0;

    for (i = 0; i < N_LETTER; i++)
        r += strset_get_not_init_n(cp->products[i]);

    return r;
}

char **catProducts_t_all_not_sold(CatProducts cp, int *s)
{
    if (!cp->not_sold[0])
        build_internal_arr(cp);

    return (char **)garray_dump_elems(cp->not_sold[0], NULL, s);
}

char **catProducts_t_not_sold_filial(CatProducts cp, int *s, int filial)
{
    char **r = NULL;

    if (is_between(filial, 1, N_FILIAIS))
    {
        if (!cp->not_sold[0])
            build_internal_arr(cp);

        r = (char **)garray_dump_elems(cp->not_sold[filial], NULL, s);
    }

    return r;
}

/* METODOS PRIVADOS BELOW */

static void build_internal_arr(CatProducts cp)
{
    int i;

    if (cp && !cp->not_sold[0])
    {
        for (i = 0; i <= N_FILIAIS; i++)
            cp->not_sold[i] = garray_make(sizeof(char *), NULL);

        for (i = 0; i < N_LETTER; i++)
            strset_foreach(cp->products[i], insert_not_bought, cp->not_sold);

        for (i = 0; i <= N_FILIAIS; i++)
            garray_sort(cp->not_sold[i], mystrcmp);
    }
}

static void insert_not_bought(void *key, void *value, void *user_data)
{
    int filial, nst = 0;
    Adition r;
    GrowingArray *arr;

    if (user_data && value)
    {
        r = (Adition)value;
        arr = (GrowingArray *)user_data;

        for (filial = 1; filial <= N_FILIAIS; filial++)
        {
            if (!adition_rec_size(r, filial))
            {
                garray_add(arr[filial], key);
                ++nst;
            }
        }

        if (nst == N_FILIAIS)
            garray_add(arr[0], key);
    }
}