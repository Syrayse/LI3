#include "Verifier.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Verifier Verifier_make();
void Verifier_destroy(Verifier v);
char *verify_client(char *client);
char *verify_product(char *product);
Transaction verify_sale(Verifier v, char *trans_code, CatProducts cp, CatClients cc, gID id);

/* Metodos privados */
static int is_valid_client(char *client);
static int is_valid_product(char *product);
static char *verify_word(char *word, int (*fv)(char *));
static int _set_trans_valid_product(char *product, Transaction t);
static int is_valid_price(char *price, Transaction t);
static int is_valid_units(char *units, Transaction t);
static int is_valid_promo(char *promo, Transaction t);
static int _set_trans_valid_client(char *client, Transaction t);
static int is_valid_month(char *month, Transaction t);
static int is_valid_filial(char *filial, Transaction t);

// ------------------------------------------------------------------------------

typedef int (*scompare)(char *, Transaction);

typedef struct verifier
{
    scompare fa[N_TRANS_ARGS];
} * Verifier;

// ------------------------------------------------------------------------------

#define BASE_DELIM " \n\r"

// ------------------------------------------------------------------------------

Verifier Verifier_make()
{
    Verifier v = g_malloc(sizeof(struct verifier));
    v->fa[0] = _set_trans_valid_product;
    v->fa[1] = is_valid_price;
    v->fa[2] = is_valid_units;
    v->fa[3] = is_valid_promo;
    v->fa[4] = _set_trans_valid_client;
    v->fa[5] = is_valid_month;
    v->fa[6] = is_valid_filial;
    return v;
}

void Verifier_destroy(Verifier v)
{
    if (v)
    {
        g_free(v);
    }
}

char *verify_client(char *client)
{
    return verify_word(client, is_valid_client);
}

char *verify_product(char *product)
{
    return verify_word(product, is_valid_product);
}

Transaction verify_sale(Verifier v, char *trans_code, CatProducts cp, CatClients cc, gID id)
{
    int t, i, r = 1;
    Transaction tr = trans_make();
    char *token = strtok(trans_code, BASE_DELIM);

    for (i = 0; r && token && i < N_TRANS_ARGS; i++, token = strtok(NULL, BASE_DELIM))
    {
        t = (*v->fa[i])(token, tr);
        r = min(r, t);
    }

    if (((token && i >= N_TRANS_ARGS) || !r) || !(trans_exists_efect(tr, cp, cc)))
    {
        trans_destroy((void *)tr);
        tr = NULL;
    }

    if (tr)
    {
        trans_set_id(tr, id);
    }

    return tr;
}

static int is_valid_client(char *client)
{
    return (g_ascii_isupper(client[0]) &&
            is_between(atoi(client + 1), 1000, 5000) &&
            (client[5] == '\0'));
}

static int is_valid_product(char *product)
{
    return (g_ascii_isupper(product[0]) &&
            g_ascii_isupper(product[1]) &&
            is_between(atoi(product + 2), 1000, 9999) &&
            (product[6] == '\0'));
}

static char *verify_word(char *word, int (*fv)(char *))
{
    char *token, *r = NULL;

    token = strtok(word, BASE_DELIM);

    if (fv && (*fv)(token))
    {
        r = g_strdup(token);
    }

    token = strtok(NULL, BASE_DELIM);

    if (token)
    {
        g_free(r);
        r = NULL;
    }

    return r;
}

static int _set_trans_valid_product(char *product, Transaction t)
{
    int r = is_valid_product(product);

    if (r)
    {
        trans_set_product(t, product);
    }

    return r;
}

static int is_valid_price(char *price, Transaction t)
{
    double f = (double)atof(price);
    int r = is_between(f, 0.0, 999.99);

    if (r)
    {
        trans_set_price(t, f);
    }

    return r;
}

static int is_valid_units(char *units, Transaction t)
{
    int r, f = atoi(units);
    r = is_between(f, 1, 200);

    if (r)
    {
        trans_set_units(t, f);
    }

    return r;
}

static int is_valid_promo(char *promo, Transaction t)
{
    int r = (*promo == 'N' || *promo == 'P');

    if (r)
    {
        trans_set_promo(t, *promo);
    }

    return r;
}

static int _set_trans_valid_client(char *client, Transaction t)
{
    int r = is_valid_client(client);

    if (r)
    {
        trans_set_client(t, client);
    }

    return r;
}

static int is_valid_month(char *month, Transaction t)
{
    int r, f = atoi(month);
    r = is_between(f, 1, 12);
    if (r)
        trans_set_month(t, f);
    return r;
}

static int is_valid_filial(char *filial, Transaction t)
{
    int r, f = atoi(filial);
    r = is_between(f, 1, 3);
    if (r)
        trans_set_filial(t, f);
    return r;
}