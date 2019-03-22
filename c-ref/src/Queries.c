#include "Queries.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "FilManager.h"
#include "Accounting.h"
#include "Verifier.h"
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Store store_make();
void store_destroy(Store s);
void store_query1(Store s, int argc, char **argv);

/* Metodos privados */
static CatProducts load_products(char *product_file);
static CatClients load_clients(char *client_file);
static Accounting loads_transactions(char *transaction_file, CatProducts cp, CatClients cc, FilManager fm);
// ------------------------------------------------------------------------------

typedef struct store
{
    int read;
    CatClients cat_clients;
    CatProducts cat_products;
    FilManager fil_manager;
    Accounting accounting;
} * Store;

// ------------------------------------------------------------------------------

#define S_BUFF 50
#define B_BUFF 100

// ------------------------------------------------------------------------------

Store store_make()
{
    Store s = g_malloc(sizeof(struct store));
    s->read = 0;
    s->cat_clients = NULL;
    s->cat_products = NULL;
    s->fil_manager = NULL;
    s->accounting = NULL;
    return s;
}

void store_destroy(Store s)
{
    if (s)
    {
        CatClients_destroy(s->cat_clients);
        CatProducts_destroy(s->cat_products);
        FilManager_destroy(s->fil_manager);
        Accounting_destroy(s->accounting);
        g_free(s);
    }
}

static CatProducts load_products(char *product_file)
{
    FILE *fp = fopen(product_file, "r");

    if (!fp)
        return NULL;

    char *tmp, product[S_BUFF];
    int nValid, nTotal;
    nValid = nTotal = 0;

    CatProducts cp = CatProducts_make();

    while (fgets(product, S_BUFF, fp))
    {
        if ((tmp = verify_product(product)))
        {
            CatProducts_add_product(cp, tmp);
            nValid++;
        }

        nTotal++;
    }

    printf("\tSucessfully read file product %s, with %d valids and %d in total!\n", product_file, nValid, nTotal);

    return cp;
}

static CatClients load_clients(char *client_file)
{
    FILE *fp = fopen(client_file, "r");

    if (!fp)
        return NULL;

    char *tmp, client[S_BUFF];
    int nValid, nTotal;
    nValid = nTotal = 0;

    CatClients cc = CatClients_make();

    while (fgets(client, S_BUFF, fp))
    {
        if ((tmp = verify_client(client)))
        {
            CatClients_add_client(cc, tmp);
            nValid++;
        }

        nTotal++;
    }

    printf("\tSucessfully read file client %s, with %d valids and %d in total!\n", client_file, nValid, nTotal);

    return cc;
}

static Accounting loads_transactions(char *transaction_file, CatProducts cp, CatClients cc, FilManager fm)
{
    FILE *fp = fopen(transaction_file, "r");

    if (!fp)
        return NULL;

    int f, m, nValid, nTotal;
    char prod[PROD_LEN + 1], clt[CLT_LEN + 1], transaction[B_BUFF];
    Accounting ac = Accounting_make();
    Verifier vr = Verifier_make();
    Transaction tmp;
    gID id_tag;

    nValid = nTotal = 0;

    while (fgets(transaction, B_BUFF, fp))
    {
        id_tag = Accounting_get_next_id(ac);

        if ((tmp = verify_sale(vr, transaction, cp, cc, id_tag)))
        {
            trans_copy_product(tmp, prod);
            trans_copy_client(tmp, clt);
            f = trans_get_filial(tmp);
            m = trans_get_month(tmp);

            CatClients_add_trans(cc, clt, f, m, id_tag);
            CatProducts_add_trans(cp, prod, f, id_tag);
            FilManager_add_trans(fm, f, id_tag);
            Accounting_add(ac, tmp);

            nValid++;
        }

        nTotal++;
    }

    Verifier_destroy(vr);

    printf("\tSucessfully read file sale %s, with %d valids and %d in total!\n", transaction_file, nValid, nTotal);

    return ac;
}

int main()
{
    Store s = store_make();

    s->fil_manager = FilManager_make();

    s->cat_clients = load_clients("tests/Clientes.txt");

    s->cat_products = load_products("tests/Produtos.txt");

    s->accounting = loads_transactions("tests/Vendas_1M.txt", s->cat_products, s->cat_clients, s->fil_manager);

    store_destroy(s);
}