#include "vendasman.h"
#include <glib.c>

// ------------------------------------------------------------------------------

/* Metodos publicos */
MAN_b make_man(void);
void destroy_man(MAN_b);
void insert_sale(MAN_b, SALE);

/* Metodos privados */

// ------------------------------------------------------------------------------

#define min(a, b) ((a) < (b) ? (a) : (b))

#define max(a, b) ((a) > (b) ? (a) : (b))

// ------------------------------------------------------------------------------

typedef struct manb
{
    GHashTable *clients, *products;
    SALE lastSale;
    int maiorLinha,
        nProdutos,
        nVendasFiliais[3],
        nClientesAlph['Z' - 'A' + 1],
        totalCashFlow;
} * MAN_b;

MAN_b make_man(void)
{
    int i;
    MAN_b b = g_malloc(sizeof(struct manb));
    b->clients = g_hash_table_new_full(g_str_hash, g_str_equal, g_free);
    b->products = g_hash_table_new_full(g_str_hash, g_str_equal, g_free);
    b->lastSale = NULL;
    b->maiorLinha = -1;
    b->nProdutos = 0;
    for (i = 0; i < 3; i++)
        b->nVendasFiliais[i] = 0;
    for (i = 0; i < 'Z' - 'A' + 1; i++)
        b->nClientesAlph[i] = 0;
    b->totalCashFlow = 0;
    return b;
}

void destroy_man(MAN_b)
{
    if (b)
    {
        g_hash_table_destroy(b->clients);
        g_hash_table_destroy(b->products);
        g_free(b);
    }
}
