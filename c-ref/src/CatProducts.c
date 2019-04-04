/**
 * @file CatProducts.c
 * \brief Módulo que define a classe que armazena o catálogo de produtos.
 * 
 * Nesta classe o catálogo é separados em 26 conjuntos de produtos, sendo que
 * cada um dos conjuntos corresponde a uma letra do alfabeto.
 */

#include "CatProducts.h"
#include "Product.h"
#include "TAD_List.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, Product product);
void CatProducts_add_product(CatProducts cp, Product product);
void CatProduct_report_trans(CatProducts cp, Product product, int filial);
TAD_List CatProducts_dump_ordered(CatProducts cp, char let);
int CatProducts_get_total_not_bought(CatProducts cp);
TAD_List CatProducts_not_bought(CatProducts cp);
TAD_List CatProducts_not_bought_fil(CatProducts cp, int filial);

/* Metodos privados */
static int get_i(Product p);
static void foreach_add_code(gpointer key, gpointer value, gpointer data);
static TAD_List dump_not_bought_reg(CatProducts cp, int ind);
static int mystrcmp(gpointer v1, gpointer v2);

/* ------------------------------------------------------------------------------ */

typedef struct cat_products
{
    Set product_set[N_LETTER],            /**< Contem todos os produtos, separados por conjuntos que estão indexados por primeira letra. */
        not_bought_regist[N_FILIAIS + 1]; /**< Contem todos os produtos não comprados em global e por filial     */
} * CatProducts;

/* ------------------------------------------------------------------------------ */

CatProducts CatProducts_make()
{
    int i;

    CatProducts cp = g_malloc(sizeof(struct cat_products));

    for (i = 0; i < N_LETTER; i++)
    {
        cp->product_set[i] = set_make(product_hash, product_equal, NULL, NULL, NULL, NULL);
    }

    for (i = 0; i <= N_FILIAIS; i++)
    {
        cp->not_bought_regist[i] = set_make(product_hash, product_equal, NULL, NULL, NULL, NULL);
    }

    return cp;
}

void CatProducts_destroy(CatProducts cp)
{
    int i;

    if (cp)
    {
        for (i = 0; i < N_LETTER; i++)
        {
            g_tree_destroy(cp->products[i]);
        }

        for (i = 0; i <= N_FILIAIS; i++)
        {
            strset_destroy(cp->not_bought_regist[i]);
        }

        g_free(cp);
    }
}

int CatProducts_exists(CatProducts cp, Product product)
{
    return set_contains(cp->product_set[get_i(product)], product);
}

void CatProducts_add_product(CatProducts cp, Product product)
{
    int i;
    Product p_copy = product_clone(product);

    strset_add(cp->product_set[get_i(p_copy)], p_copy);

    for (i = 0; i <= N_FILIAIS; i++)
    {
        strset_add(cp->not_bought_regist[i], p_copy, NULL);
    }
}

void CatProduct_report_trans(CatProducts cp, Product product, int filial)
{
    strset_remove(cp->not_bought_regist[0], product);
    strset_remove(cp->not_bought_regist[filial], product);
}

TAD_List CatProducts_dump_ordered(CatProducts cp, char let)
{
    int i = 0;
    TAD_List tl = NULL;
    Set ref;

    if (is_between(let, 'A', 'Z'))
    {
        ref = cp->product_set[let - 'A'];

        tl = list_make(g_free, set_size(ref));

        set_foreach(ref, foreach_add, tl);

        list_sort(tl, mystrcmp);
    }

    return tl;
}

int CatProducts_get_total_not_bought(CatProducts cp)
{
    return strset_size(cp->not_bought_regist[0]);
}

TAD_List CatProducts_not_bought(CatProducts cp)
{
    return dump_not_bought_reg(cp, 0);
}

TAD_List CatProducts_not_bought_fil(CatProducts cp, int filial)
{
    return dump_not_bought_reg(cp, filial);
}

static int get_i(Product p)
{
    return (product_get_first_let(p) - 'A');
}

static void foreach_add_code(gpointer key, gpointer value, gpointer data)
{
    list_add((TAD_List)data, product_get_code((Product)key));
}

static TAD_List dump_not_bought_reg(CatProducts cp, int ind)
{
    int i = 0;

    Set ref = cp->not_bought_regist[ind];

    TAD_List tl = list_make(g_free, set_size(ref));

    strset_foreach(ref, foreach_add_code, tl);

    return r;
}

static int mystrcmp(gpointer v1, gpointer v2)
{
    return strcmp((char *)v1, (char *)v2);
}