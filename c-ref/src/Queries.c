#include "Queries.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "FilManager.h"
#include "Accounting.h"
#include "Verifier.h"
#include "statinfo.h"
#include "gArray.h"
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Store store_make();
void store_destroy(Store s);
void store_query1(Store s, int argc, char **argv);
char **store_query2(Store s, int *size, int flag);
StatInfo store_query3(Store s, char *product);
char **store_query4(Store s, int filial, int *size);
char **store_query5(Store s, int *size);
void store_query6(Store s, int *ncl, int *nprd);
int **store_query7(Store s, char *client);
void store_query8(Store s, int init, int end, int *nVendas, double *tot);
int store_query9(Store s, char *product, char ***holder, int *n1, int *n2, int filial);

/* Metodos privados */
static CatProducts load_products(char *product_file);
static CatClients load_clients(char *client_file);
static Accounting loads_transactions(char *transaction_file, CatProducts cp, CatClients cc, FilManager fm);
static void get_units_matrix(Transaction t, void *e);
static void process_promos_clients(Transaction t, void *e);

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

void store_query1(Store s, int argc, char **argv)
{
    if (argc != 4 && argc != 1)
        return;

    char *products, *clients, *transactions;
    products = clients = transactions = NULL;

    if (argc == 4)
    {
        products = argv[1];
        clients = argv[2];
        transactions = argv[3];
    }

    s->fil_manager = FilManager_make();

    s->cat_products = load_products(products ? products : "tests/Produtos.txt");

    s->cat_clients = load_clients(clients ? clients : "tests/Clientes.txt");

    s->accounting = loads_transactions(transactions ? transactions : "tests/Vendas_1M.txt", s->cat_products, s->cat_clients, s->fil_manager);
}

char **store_query2(Store s, int *size, int flag)
{
    return CatProducts_dump_ordered(s->cat_products, size, flag);
}

StatInfo store_query3(Store s, char *product)
{
    int i, sz = 0;
    StatInfo si = NULL;
    gID *ids;

    if (CatProducts_exists(s->cat_products, product))
    {
        si = statinfo_make();

        for (i = 1; i <= N_FILIAIS; i++)
        {
            ids = CatProducts_drop_trans(s->cat_products, product, i, &sz);
            Accounting_iter(s->accounting, ids, sz, statinfo_builder, si);
            g_free(ids);
        }
    }

    return si;
}

char **store_query4(Store s, int filial, int *size)
{
    char **r = NULL;

    if (is_between(filial, 0, N_FILIAIS))
    {
        if (!filial)
        {
            r = catProducts_t_all_not_sold(s->cat_products, size);
        }
        else
        {
            r = catProducts_t_not_sold_filial(s->cat_products, size, filial);
        }
    }

    return r;
}

char **store_query5(Store s, int *size)
{
    return CatClients_dump_all_fils(s->cat_clients, size);
}

void store_query6(Store s, int *ncl, int *nprd)
{
    *ncl = CatClients_t_not_sold(s->cat_clients);
    *nprd = CatProducts_t_not_sold(s->cat_products);
}

int **store_query7(Store s, char *client)
{
    int i, sz, **r = NULL;
    gID *ids;

    if (CatClients_exists(s->cat_clients, client))
    {
        r = g_malloc(sizeof(int *) * N_FILIAIS);

        for (i = 0; i < N_FILIAIS; i++)
        {
            r[i] = g_malloc0(sizeof(int) * N_MONTHS);
        }

        for (i = 1; i <= N_MONTHS; i++)
        {
            ids = CatClients_drop_trans(s->cat_clients, client, i, &sz);
            Accounting_iter(s->accounting, ids, sz, get_units_matrix, r);
        }
    }

    return r;
}

void store_query8(Store s, int init, int end, int *nVendas, double *tot)
{
    *nVendas = Accounting_n_trans_range(s->accounting, init, end);
    *tot = Accounting_n_cash_range(s->accounting, init, end);
}

int store_query9(Store s, char *product, char ***holder, int *n1, int *n2, int filial)
{
    int i, sz;
    gID *ids = CatProducts_drop_trans(s->cat_products, product, filial, &sz);

    GrowingArray v[N_PROMOS];

    for (i = 0; i < N_PROMOS; i++)
    {
        v[i] = garray_make(sizeof(char *), NULL);
    }

    Accounting_iter(s->accounting, ids, sz, process_promos_clients, v);

    holder[0] = (char **)garray_dump_elems(v[0], NULL, n1);
    holder[1] = (char **)garray_dump_elems(v[1], NULL, n2);

    for (i = 0; i < N_PROMOS; i++)
    {
        garray_destroy(v[i]);
    }
    g_free(ids);
    return sz;
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

static void get_units_matrix(Transaction t, void *e)
{
    if (!e)
        return;
    int **r, m, f, u = trans_get_units(t);
    f = trans_get_filial(t);
    m = trans_get_month(t);

    r = (int **)e;

    r[f - 1][m - 1] += u;
}

static void process_promos_clients(Transaction t, void *e)
{
    if (!e)
        return;

    GrowingArray *r = (GrowingArray *)e;
    garray_add(r[indP(trans_get_promo(t))], trans_get_client(t));
}