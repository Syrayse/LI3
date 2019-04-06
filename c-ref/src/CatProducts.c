/**
 * @file CatProducts.c
 * \brief Módulo que define a classe que armazena o catálogo de produtos.
 * 
 * Nesta classe o catálogo é separado em 26 conjuntos de produtos, sendo que
 * cada um dos conjuntos corresponde a uma letra do alfabeto.
 */

#include "CatProducts.h"
#include "Product.h"
#include "TAD_List.h"
#include "set.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura que define a classe `CatProducts`.
 */
typedef struct cat_products
{
    Set product_set[N_LETTER],            /**< Contém todos os produtos, separados por conjuntos que estão indexados pela primeira letra. */
        not_bought_regist[N_FILIAIS + 1]; /**< Contém todos os produtos não comprados em global e por filial. */
} * CatProducts;

/* ------------------------------------------------------------------------------ */

/* Métodos publicos */
CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, Product product);
void CatProducts_add_product(CatProducts cp, Product product);
void CatProduct_report_trans(CatProducts cp, Product product, int filial);
TAD_List CatProducts_dump_ordered(CatProducts cp, char let);
int CatProducts_get_total_not_bought(CatProducts cp);
TAD_List CatProducts_not_bought(CatProducts cp);
TAD_List CatProducts_not_bought_fil(CatProducts cp, int filial);

/* Métodos privados */
static void foreach_add_code(gpointer key, gpointer value, gpointer data);
static TAD_List dump_not_bought_reg(CatProducts cp, int ind);
static int mystrcmp(gconstpointer v1, gconstpointer v2);

/* ------------------------------------------------------------------------------ */

CatProducts CatProducts_make()
{
    int i;

    CatProducts cp = g_malloc(sizeof(struct cat_products));

    for (i = 0; i < N_LETTER; i++)
    {
        cp->product_set[i] = set_make(product_hash, product_equal, wrapproduct_destroy, NULL, NULL, NULL);
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
            set_destroy(cp->product_set[i]);
        }

        for (i = 0; i <= N_FILIAIS; i++)
        {
            set_destroy(cp->not_bought_regist[i]);
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

    set_add(cp->product_set[get_i(p_copy)], p_copy, NULL);

    for (i = 0; i <= N_FILIAIS; i++)
    {
        set_add(cp->not_bought_regist[i], p_copy, NULL);
    }
}

void CatProduct_report_trans(CatProducts cp, Product product, int filial)
{
    set_remove(cp->not_bought_regist[0], product);
    set_remove(cp->not_bought_regist[filial], product);
}

TAD_List CatProducts_dump_ordered(CatProducts cp, char let)
{
    TAD_List tl = NULL;
    Set ref;

    if (is_between(let, 'A', 'Z'))
    {
        ref = cp->product_set[let - 'A'];

        tl = list_make(g_free, set_size(ref));

        set_foreach(ref, foreach_add_code, tl);

        list_sort(tl, mystrcmp);
    }

    return tl;
}

int CatProducts_get_total_not_bought(CatProducts cp)
{
    return set_size(cp->not_bought_regist[0]);
}

TAD_List CatProducts_not_bought(CatProducts cp)
{
    return dump_not_bought_reg(cp, 0);
}

TAD_List CatProducts_not_bought_fil(CatProducts cp, int filial)
{
    return dump_not_bought_reg(cp, filial);
}

static void foreach_add_code(gpointer key, gpointer value, gpointer data)
{
    list_add((TAD_List)data, product_get_code((Product)key));
}

static TAD_List dump_not_bought_reg(CatProducts cp, int ind)
{
    Set ref = cp->not_bought_regist[ind];

    TAD_List tl = list_make(g_free, set_size(ref));

    set_foreach(ref, foreach_add_code, tl);

    return tl;
}

static int mystrcmp(gconstpointer v1, gconstpointer v2)
{
    return strcmp(*(char **)v1, *(char **)v2);
}