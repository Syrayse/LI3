#include "transaction.h"
#include <string.h>
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Transaction trans_make();
void trans_destroy(void *e);

void trans_copy_product(Transaction src, char *dest);
void trans_copy_client(Transaction src, char *dest);
int trans_exists_efect(Transaction src, CatProducts cp, CatClients cc);

char *trans_get_client(Transaction t);
char *trans_get_product(Transaction t);
UChar trans_get_month(Transaction t);
UChar trans_get_filial(Transaction t);
UChar trans_get_promo(Transaction t);
UChar trans_get_units(Transaction t);
gID trans_get_id(Transaction t);
double trans_get_price(Transaction t);
double trans_get_rev(Transaction t);

void trans_set_client(Transaction t, char *client);
void trans_set_product(Transaction t, char *product);
void trans_set_month(Transaction t, UChar month);
void trans_set_filial(Transaction t, UChar filial);
void trans_set_promo(Transaction t, UChar promo);
void trans_set_units(Transaction t, UChar units);
void trans_set_id(Transaction t, gID id);
void trans_set_price(Transaction t, double price);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

typedef struct transaction
{
    char client[CLT_LEN + 1],
        product[PROD_LEN + 1];
    UChar month,
        filial,
        promo,
        units;
    gID id;
    double price;
} * Transaction;

// ------------------------------------------------------------------------------

Transaction trans_make()
{
    Transaction t = g_malloc(sizeof(struct transaction));
    t->month = t->filial = t->promo = t->units = 0;
    t->id = 0;
    t->price = 0.0;
    return t;
}

void trans_destroy(void *e)
{
    Transaction t;

    if (e)
    {
        t = (Transaction)e;
        g_free(t);
    }
}

void trans_copy_product(Transaction src, char *dest)
{
    strcpy(dest, src->product);
}

void trans_copy_client(Transaction src, char *dest)
{
    strcpy(dest, src->client);
}

int trans_exists_efect(Transaction src, CatProducts cp, CatClients cc)
{
    return (CatProducts_exists(cp, src->product) && CatClients_exists(cc, src->client));
}

char *trans_get_client(Transaction t)
{
    return g_strdup(t->client);
}

char *trans_get_product(Transaction t)
{
    return g_strdup(t->product);
}

UChar trans_get_month(Transaction t)
{
    return t->month;
}

UChar trans_get_filial(Transaction t)
{
    return t->filial;
}

UChar trans_get_promo(Transaction t)
{
    return t->promo;
}

UChar trans_get_units(Transaction t)
{
    return t->units;
}

gID trans_get_id(Transaction t)
{
    return t->id;
}

double trans_get_price(Transaction t)
{
    return t->price;
}

double trans_get_rev(Transaction t)
{
    return (trans_get_units(t) * trans_get_price(t));
}

void trans_set_client(Transaction t, char *client)
{
    strcpy(t->client, client);
}

void trans_set_product(Transaction t, char *product)
{
    strcpy(t->product, product);
}

void trans_set_month(Transaction t, UChar month)
{
    t->month = month;
}

void trans_set_filial(Transaction t, UChar filial)
{
    t->filial = filial;
}

void trans_set_promo(Transaction t, UChar promo)
{
    t->promo = promo;
}

void trans_set_units(Transaction t, UChar units)
{
    t->units = units;
}

void trans_set_id(Transaction t, gID id)
{
    t->id = id;
}

void trans_set_price(Transaction t, double price)
{
    t->price = price;
}