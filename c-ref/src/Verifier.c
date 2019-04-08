/**
 * @file Verifier.c
 * \brief Módulo que define a classe de validação, `Verifier`, e todas as necessárias funções de validação.
 * 
 * Neste módulo encontram-se definidas todas as necessárias funções de serviços de validação.
 * 
 * Sendo o principal deles, a classe `Verifier`, que corresponde a um agregado de métodos encadeados, de tal
 * forma, que permitem a criação de uma _stream_ de métodos que são aplicados sucessivamente, à medida que se pretende
 * validar um código de transação e criar a respetiva `Transaction`. Isto permite, assim, uma fluidez computacional ao ser utilizada a função `strtok`.
 * 
 * Para além disso, permite também que o cliente faça validação semântica dos seus produtos
 * e cliente, criando também as suas respetivas instâncias.
 */
#include "Verifier.h"
#include "Client.h"
#include "Product.h"
#include "Transaction.h"
#include "commondef.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Typedef utilizado de forma a simplificar parametrização de funções.
 */
typedef int (*scompare)(char *, Transaction);

/**
 * \brief Classe `Verifier` contendo todas as variáveis de instâncias necessárias
 * ao seu bom funcionamento.
 * 
 * Internamente a classe `Verifier`, que tem como objetivo final validar unicamente
 * registos de transação e formar a `Transaction` correspondente, é formada apenas
 * por um _array_ de tantas funções como argumentos num registos de transações. Sendo que
 * este número de argumentos se encontra descrito por `N_TRANS_ARGS`.
 * 
 * Cada posição _n_ neste _array_ deve conter uma função, tal que esta seja capaz
 * de validar e adicionar a uma `Transaction` o n-ésimo parâmetro da ordem estabelecida para
 * registos de transação, que segue a seguinte formatação:
 * 
 *  [PRODUTO] [PREÇO] [UNIDADES VENDIDAS] [PROMOÇÃO] [CLIENTE] [MÊS] [FILIAL]
 * 
 * Logo, por exemplo, o índice 2 do array na classe `Verifier`, deverá corresponder univocamente
 * a um função capaz de validar e atribuir a uma `Transaction` o número de unidades que foram
 * transacionadas naquele registo.
 * 
 * @see scompare
 * @see Transaction
 */
typedef struct verifier
{
    scompare fa[N_TRANS_ARGS]; /**< Array com funções de validação e atribuição. */
} * Verifier;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
Verifier Verifier_make();
void Verifier_destroy(Verifier v);
Client verify_client(char *client);
Product verify_product(char *product);
Transaction verify_sale(Verifier v, char *trans_code);

/* Métodos privados */
static int is_valid_client(char *client);
static int is_valid_product(char *product);
static int _set_trans_valid_product(char *product, Transaction t);
static int is_valid_price(char *price, Transaction t);
static int is_valid_units(char *units, Transaction t);
static int is_valid_promo(char *promo, Transaction t);
static int _set_trans_valid_client(char *client, Transaction t);
static int is_valid_month(char *month, Transaction t);
static int is_valid_filial(char *filial, Transaction t);

/* ------------------------------------------------------------------------------ */

/**
 * \brief Delimitadores base que permitem compatibilidade com maioria dos sistemas operativos.
 */
#define BASE_DELIM " \n\r"

/* ------------------------------------------------------------------------------ */

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

Client verify_client(char *client)
{
    Client c = NULL;

    char *token = strtok(client, BASE_DELIM);

    if (is_valid_client(token))
    {
        c = client_make(token);
    }

    return c;
}

Product verify_product(char *product)
{
    Product p = NULL;

    char *token = strtok(product, BASE_DELIM);

    if (is_valid_product(token))
    {
        p = product_make(token);
    }

    return p;
}

Transaction verify_sale(Verifier v, char *trans_code)
{
    if (!v || !trans_code)
        return NULL;

    int t, i, r = 1;
    Transaction dest = trans_make();
    char *token = strtok(trans_code, BASE_DELIM);

    for (i = 0; r && token && i < N_TRANS_ARGS; i++, token = strtok(NULL, BASE_DELIM))
    {
        t = (*v->fa[i])(token, dest);
        r = min(r, t);
    }

    if (token && i >= N_TRANS_ARGS)
    {
        r = 0;
    }

    return dest;
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

static int _set_trans_valid_product(char *product, Transaction t)
{
    int r = is_valid_product(product);

    if (r)
    {
        trans_set_product(t, product_make(product));
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
        trans_set_client(t, client_make(client));
    }

    return r;
}

static int is_valid_month(char *month, Transaction t)
{
    int r, f = atoi(month);
    r = is_between(f, 1, 12);

    if (r)
    {
        trans_set_month(t, f);
    }
    return r;
}

static int is_valid_filial(char *filial, Transaction t)
{
    int r, f = atoi(filial);
    r = is_between(f, 1, 3);

    if (r)
    {
        trans_set_filial(t, f);
    }

    return r;
}