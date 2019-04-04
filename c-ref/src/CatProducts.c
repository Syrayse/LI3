/**
 * @file CatProducts.c
 * \brief Módulo que define a classe que armazena o catálogo de produtos.
 * 
 * Nesta classe o catálogo é separados em 26 conjuntos de produtos, sendo que
 * cada um dos conjuntos corresponde a uma letra do alfabeto.
 */

#include "CatProducts.h"
#include "set.h"
#include "gArray.h"
#include <gmodule.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, Product product);
void CatProducts_add_product(CatProducts cp, Product product);
void CatProduct_report_trans(CatProducts cp, char *product, int filial);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);
int CatProducts_get_total_not_bought(CatProducts cp);
char **CatProducts_not_bought(CatProducts cp, int *size);
char **CatProducts_not_bought_fil(CatProducts cp, int filial, int *size);
Product Product_make(char *product_code);
void Product_destroy(void *p);

/* Metodos privados */
static gint wrap_mystrcmp(gconstpointer a, gconstpointer b, gpointer user_data);
static gboolean foreach_add_tree(gpointer key, gpointer value, gpointer data);
static void foreach_add_set(gpointer key, gpointer value, gpointer data);
static char **dump_not_bought_reg(CatProducts cp, int ind, int *size);

/* ------------------------------------------------------------------------------ */

/**
 * \brief Define o tamanho de um código de produto.
 */
#define PROD_LEN 6

/* ------------------------------------------------------------------------------ */

/**
 * \brief Definição da classe que armazena o catálogo de produtos.
 */
typedef struct cat_products
{
    GTree *products[N_LETTER]; /**< _Array_ de conjuntos cada um correspondente a uma letra, por ordem alfabética. */
    StrSet not_bought_regist[N_FILIAIS + 1];
} * CatProducts;

/**
 * \brief Define a estrutura associada a um `Product`.
 */
typedef struct product
{
    char product_code[PROD_LEN + 1]; /**< Código do produto. */
} * Product;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Cria uma instância da classe `CatProducts`.
 * 
 * Para além de criar a instância, inicializa todos os `StrSet`s necessários.
 * 
 * @returns Uma instância da classe `CatProducts`.
 */
CatProducts CatProducts_make()
{
    int i;

    CatProducts cp = g_malloc(sizeof(struct cat_products));

    for (i = 0; i < N_LETTER; i++)
    {
        cp->products[i] = g_tree_new_full(wrap_mystrcmp, NULL, Product_destroy, NULL);
    }

    for (i = 0; i <= N_FILIAIS; i++)
    {
        cp->not_bought_regist[i] = strset_make(NULL, NULL, NULL, NULL, NULL);
    }

    return cp;
}

/**
 * \brief Destrói uma instância da classe `CatProducts`.
 * 
 * @param cp Instância a destruir.
 */
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
    void *trash1, *trash2;
    return g_tree_lookup_extended(cp->products[*product->product_code - 'A'], product->product_code, &trash1, &trash2);
}

/**
 * \brief Adiciona um produto ao catalogo de produtos.
 * 
 * @param cp Instância a considerar.
 * @param product Produto a adicionar ao catalogo.
 */
void CatProducts_add_product(CatProducts cp, Product product)
{
    int i;
    char *copy_product_code = g_strdup(product->product_code);

    g_tree_insert(cp->products[*product->product_code - 'A'], copy_product_code, NULL);

    for (i = 0; i <= N_FILIAIS; i++)
    {
        strset_add(cp->not_bought_regist[i], copy_product_code,NULL);
    }
}

void CatProduct_report_trans(CatProducts cp, char *product, int filial)
{
    strset_remove(cp->not_bought_regist[0], product);
    strset_remove(cp->not_bought_regist[filial], product);
}

/**
 * \brief Efetua uma dump de um conjunto de cópias de todos os produtos que começam com uma dada letra.
 * 
 * @param cp Instância a considerar.
 * @param s Endereço onde será colocado o número de elementos despejados.
 * @param let Primeira letra a considerar.
 * 
 * @returns O array de cópia de _Strings_ , NULL caso a letra seja inválida.
 */
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let)
{
    int i = 0;
    char **r = NULL;
    GTree *ref;
    void *holder[2];

    if (is_between(let, 'A', 'Z'))
    {
        ref = cp->products[let - 'A'];
        r = g_malloc(sizeof(char *) * g_tree_nnodes(ref));
        holder[0] = r;
        holder[1] = &i;
        g_tree_foreach(ref, foreach_add_tree, holder);
        *s = i;
    }

    return r;
}

int CatProducts_get_total_not_bought(CatProducts cp)
{
    return strset_size(cp->not_bought_regist[0]);
}

char **CatProducts_not_bought(CatProducts cp, int *size)
{
    return dump_not_bought_reg(cp, 0, size);
}

char **CatProducts_not_bought_fil(CatProducts cp, int filial, int *size)
{
    return dump_not_bought_reg(cp, filial, size);
}

/**
 * \brief 
 */
Product Product_make(char *product_code)
{
    Product product = g_malloc(sizeof(struct product));

    strcpy(product->product_code, product_code);

    return product;
}

/**
 * \brief 
 */
void Product_destroy(void *p)
{
    if (p)
    {
        g_free((Product)p);
    }
}

/**
 * \brief Função de comparação que envolve a função `mystrcmp` é estritamente necessária para comparação em arvóres.
 */
static gint wrap_mystrcmp(gconstpointer a, gconstpointer b, gpointer user_data)
{
    return strcmp(((Product)a)->product_code, ((Product)b)->product_code);
}

static gboolean foreach_add_tree(gpointer key, gpointer value, gpointer data)
{
    void **holder = (void **)data;

    ((char **)holder[0])[(*(int *)holder[1])++] = g_strdup(((Product)key)->product_code);

    return FALSE;
}

static void foreach_add_set(gpointer key, gpointer value, gpointer data)
{
    void **holder = (void **)data;
    ((char **)holder[0])[(*(int *)holder[1])++] = g_strdup(key);
}

static char **dump_not_bought_reg(CatProducts cp, int ind, int *size)
{
    int i = 0;
    char **r = NULL;
    void *holder[2];

    r = g_malloc(sizeof(char *) * strset_size(cp->not_bought_regist[ind]));
    holder[0] = r;
    holder[1] = &i;
    strset_foreach(cp->not_bought_regist[ind], foreach_add_set, holder);
    *size = i;

    return r;
}