/**
 * @file ProdDescriptor.c
 * \brief Contém o código associado aos metódos da classe `ProdDescriptor`.
 */

#include "ProdDescriptor.h"
#include "Product.h"
#include "commondef.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `ProdDescriptor`.
 */
typedef struct proddescriptor
{
    Product product;         /**< Produto que se pretende descrever. */
    int nClients,            /**< Número de clientes do produto descrito. */
        filUnits[N_FILIAIS]; /**< Número de unidades compradas do produto, por filial. */
} * ProdDescriptor;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
ProdDescriptor proddescrip_make(Product p, int nclients, int *vec_filial);
void proddescrip_destroy(ProdDescriptor pd);
int proddescrip_get_fil_units(ProdDescriptor pd, int filial);
int proddescrip_get_n_clients(ProdDescriptor pd);
Product proddescrip_get_product(ProdDescriptor pd);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

ProdDescriptor proddescrip_make(Product p, int nclients, int *vec_filial)
{
    int i;

    ProdDescriptor pd = g_malloc(sizeof(struct proddescriptor));

    pd->nClients = nclients;

    pd->product = p;

    for (i = 0; i < N_FILIAIS; i++)
    {
        pd->filUnits[i] = vec_filial[i];
    }

    return pd;
}

void proddescrip_destroy(ProdDescriptor pd)
{
    if (pd)
    {
        product_destroy(pd->product);
        g_free(pd);
    }
}

Product proddescrip_get_product(ProdDescriptor pd)
{
    return pd->product;
}

int proddescrip_get_fil_units(ProdDescriptor pd, int filial)
{
    return pd->filUnits[filial - 1];
}

int proddescrip_get_n_clients(ProdDescriptor pd)
{
    return pd->nClients;
}