/**
 * @file Transaction.c
 * \brief Define toda a codificação dos métodos para interagir com a classe `Transaction`.
 */
#include "Transaction.h"
#include "Client.h"
#include "Product.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura que armazena toda a informação necessária para um registo de transação.
 */
typedef struct transaction
{
    Client client;       /**< Cliente associado à transação. */
    Product product;     /**< Produto associado à transação. */
    unsigned char month, /**< Mês da transação. */
        filial,          /**< Filial onde se deu a transação. */
        promo,           /**< Código promocional associado à transação. */
        units;           /**< Unidades envolvidas na transação. */
    double price;        /**< Preço do produto da transação. */
} * Transaction;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
Transaction trans_make();
void trans_destroy(Transaction t);
Client trans_get_client(Transaction t);
Product trans_get_product(Transaction t);
unsigned char trans_get_month(Transaction t);
unsigned char trans_get_filial(Transaction t);
unsigned char trans_get_promo(Transaction t);
unsigned char trans_get_units(Transaction t);
double trans_get_price(Transaction t);
double trans_get_rev(Transaction t);
void trans_set_client(Transaction t, Client c);
void trans_set_product(Transaction t, Product p);
void trans_set_month(Transaction t, unsigned char month);
void trans_set_filial(Transaction t, unsigned char filial);
void trans_set_promo(Transaction t, unsigned char promo);
void trans_set_units(Transaction t, unsigned char units);
void trans_set_price(Transaction t, double price);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

Transaction trans_make()
{
    Transaction t = g_malloc(sizeof(struct transaction));
    t->month = t->filial = t->promo = t->units = 0;
    t->price = 0.0;
    return t;
}

void trans_destroy(Transaction t)
{
    if (t)
    {
        client_destroy(t->client);
        product_destroy(t->product);
        g_free(t);
    }
}

Client trans_get_client(Transaction t)
{
    return t->client;
}

Product trans_get_product(Transaction t)
{
    return t->product;
}

unsigned char trans_get_month(Transaction t)
{
    return t->month;
}

unsigned char trans_get_filial(Transaction t)
{
    return t->filial;
}

unsigned char trans_get_promo(Transaction t)
{
    return t->promo;
}

unsigned char trans_get_units(Transaction t)
{
    return t->units;
}

double trans_get_price(Transaction t)
{
    return t->price;
}

double trans_get_rev(Transaction t)
{
    return (t->units * t->price);
}

void trans_set_client(Transaction t, Client c)
{
    t->client = c;
}

void trans_set_product(Transaction t, Product p)
{
    t->product = p;
}

void trans_set_month(Transaction t, unsigned char month)
{
    t->month = month;
}

void trans_set_filial(Transaction t, unsigned char filial)
{
    t->filial = filial;
}

void trans_set_promo(Transaction t, unsigned char promo)
{
    t->promo = (promo == 'N') ? 0 : 1;
}

void trans_set_units(Transaction t, unsigned char units)
{
    t->units = units;
}

void trans_set_price(Transaction t, double price)
{
    t->price = price;
}