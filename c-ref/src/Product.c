/**
 * @file Product.c
 * \brief Ficheiro que contém o código associado à classe `Product`.
 */
#include "Product.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Define o tamanho de um código de produto.
 */
#define PRODUCT_LEN 6

/**
 * \brief Estrutura de dados que define a classe `Product`.
 * 
 * Esta classe é atualmente composta unicamente pelo código do produto.
 */
typedef struct product
{
    char product_code[PRODUCT_LEN + 1]; /**< Código do produto correspondente. */
} * Product;

/* ------------------------------------------------------------------------------ */

/* Metódos publicos */
Product product_make(char *product_code);
void product_destroy(Product p);
Product product_clone(Product p);
char *product_get_code(Product p);
int product_get_first_let(Product p);
guint product_hash(gconstpointer v);
gboolean product_equal(gconstpointer v1, gconstpointer v2);
void wrapproduct_destroy(gpointer v);
int get_i(Product p);

/* Metódos privados */

/* ------------------------------------------------------------------------------ */

Product product_make(char *product_code)
{
    Product p = g_malloc(sizeof(struct product));

    strcpy(p->product_code, product_code);

    return p;
}

void product_destroy(Product p)
{
    if (p)
    {
        g_free(p);
    }
}

Product product_clone(Product p)
{
    return product_make(p->product_code);
}

char *product_get_code(Product p)
{
    return g_strdup(p->product_code);
}

guint product_hash(gconstpointer v)
{
    Product p = (Product)v;
    return g_str_hash(p->product_code);
}

gboolean product_equal(gconstpointer v1, gconstpointer v2)
{
    Product p1 = (Product)v1;
    Product p2 = (Product)v2;
    return g_str_equal(p1->product_code, p2->product_code);
}

void wrapproduct_destroy(gpointer v)
{
    product_destroy((Product)v);
}

int get_i(Product p)
{
    return (*(p->product_code) - 'A');
}