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
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, char *product);
void CatProducts_add_product(CatProducts cp, char *product);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

/**
 * \brief Definição da classe que armazena o catálogo de produtos.
 */
typedef struct cat_products
{
    StrSet products[N_LETTER]; /**< _Array_ de conjuntos cada um correspondente a uma letra, por ordem alfabética. */
} * CatProducts;

// ------------------------------------------------------------------------------

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
        cp->products[i] = strset_make(g_free, NULL, NULL, NULL, NULL);

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
            strset_destroy(cp->products[i]);

        g_free(cp);
    }
}

/**
 * \brief Verifica se um produto existe no catalogo de produtos.
 * 
 * @param cp Instância a considerar.
 * @param product Produto que se pretende verificar.
 * 
 * @returns 1 caso o produto exista, 0 caso contrário.
 */
int CatProducts_exists(CatProducts cp, char *product)
{
    return strset_contains(cp->products[conv_str(product)], product);
}

/**
 * \brief Adiciona um produto ao catalogo de produtos.
 * 
 * @param cp Instância a considerar.
 * @param product Produto a adicionar ao catalogo.
 */
void CatProducts_add_product(CatProducts cp, char *product)
{
    strset_add(cp->products[conv_str(product)], g_strdup(product), NULL);
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
    char ** r = NULL;

    if (is_between(let,'A','Z'))
    {
        *s = strset_size(cp->products[let-'A']);
        r = strset_dump_n_ordered(cp->products[let - 'A'], *s);
    }

    return r;
}