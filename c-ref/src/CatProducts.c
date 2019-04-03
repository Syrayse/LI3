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
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);
Product Product_make(char *product_code);
void Product_destroy(void *p);

/* Metodos privados */
static gint wrap_mystrcmp(gconstpointer a, gconstpointer b, gpointer user_data);
static gboolean foreach_add(gpointer key, gpointer value, gpointer data);

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
            g_tree_destroy(cp->products[i]);

        g_free(cp);
    }
}

int CatProducts_exists(CatProducts cp, Product product)
{
    
}

/**
 * \brief Adiciona um produto ao catalogo de produtos.
 * 
 * @param cp Instância a considerar.
 * @param product Produto a adicionar ao catalogo.
 */
void CatProducts_add_product(CatProducts cp, Product product)
{
    g_tree_insert(cp->products[*product->product_code - 'A'], g_strdup(product->product_code), NULL);
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
        g_tree_foreach(ref, foreach_add, holder);
        *s = i;
    }

    return r;
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

static gboolean foreach_add(gpointer key, gpointer value, gpointer data)
{
    void **holder = (void **)data;

    ((char **)holder[0])[(*(int *)holder[1])++] = g_strdup(((Product)key)->product_code);

    return FALSE;
}