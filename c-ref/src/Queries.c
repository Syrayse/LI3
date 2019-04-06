/**
 * @file Queries.c
 * \brief Ficheiro de código responsável pela codificação das Queries necessárias ao SGV.
 */

#include "Queries.h"

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
TAD_List get_sorted_products(CatProducts cp, char let);                                                          /* Q2 */
int get_product_global_stats(Accounting a, char *product_code, int month, int *trans_vec, int *spent_vec);       /* Q3 */
int get_product_per_filial_stats(Accounting a, char *product_code, int month, int **trans_vec, int **spent_vec); /* Q3 */
TAD_List get_not_bought_products(CatProducts cp, int filial);                                                    /* Q4 */
TAD_List get_overall_clients(FilManager fm);                                                                     /* Q5 */
int get_n_not_bought_clients(CatClients cc, FilManager fm);                                                      /* Q6 */
int get_n_not_bought_products(CatProducts cp);                                                                   /* Q6 */
int **get_matrix(FilManager fm, char *client_code);                                                              /* Q7 */
int get_interval_trans(Accounting ac, int init, int end);                                                        /* Q8 */
double get_interval_rev(Accounting ac, int init, int end);                                                       /* Q8 */
TAD_List get_product_buyers(FilManager fm, char *product_code, int filial, int promo);                           /* Q9 */
TAD_List get_clients_most_bought(FilManager fm, char *client_code, int month);                                   /* Q10 */
TAD_List get_topN_most_sold(Accounting ac, FilManager fm, int N);                                                /* Q11 */
TAD_List get_clients_top3(FilManager fm, char *client_code);                                                     /* Q12 */

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

TAD_List get_sorted_products(CatProducts cp, char let)
{
    return CatProducts_dump_ordered(cp, let);
}

int get_product_global_stats(Accounting a, char *product_code, int month, int *trans_vec, int *spent_vec)
{
    Product p = product_make(product_code);

    int r = Accounting_get_global_stats(a, p, month, trans_vec, spent_vec);

    product_destroy(p);

    return r;
}

int get_product_per_filial_stats(Accounting a, char *product_code, int month, int **trans_vec, int **spent_vec)
{
    Product p = product_make(product_code);

    int r = Accounting_get_per_filial_stats(a, p, month, trans_vec, spent_vec);

    product_destroy(p);

    return r;
}

TAD_List get_not_bought_products(CatProducts cp, int filial)
{
    return (filial) ? CatProducts_not_bought_fil(cp, filial) : CatProducts_not_bought(cp);
}

TAD_List get_overall_clients(FilManager fm)
{
    return filmanager_get_overall_clients(fm);
}

int get_n_not_bought_clients(CatClients cc, FilManager fm)
{
    return CatClients_size(cc) - filmanager_get_active_n_clients(fm);
}

int get_n_not_bought_products(CatProducts cp)
{
    return CatProducts_get_total_not_bought(cp);
}

int **get_matrix(FilManager fm, char *client_code)
{
    Client c = client_make(client_code);

    int **r = filmanager_get_units_matrix(fm, c);

    client_destroy(c);

    return r;
}

int get_interval_trans(Accounting ac, int init, int end)
{
    return Accounting_n_trans_range(ac, init, end);
}

double get_interval_rev(Accounting ac, int init, int end)
{
    return Accounting_n_cash_range(ac, init, end);
}

TAD_List get_product_buyers(FilManager fm, char *product_code, int filial, int promo)
{
    Product p = product_make(product_code);

    TAD_List l = filmanager_get_client_at_fil(fm, p, filial, promo);

    product_destroy(p);

    return l;
}

TAD_List get_clients_most_bought(FilManager fm, char *client_code, int month)
{
    Client c = client_make(client_code);

    TAD_List l = filmanager_get_most_bought(fm, c, month);

    client_destroy(c);

    return l;
}

TAD_List get_topN_most_sold(Accounting ac, FilManager fm, int N)
{
    return NULL;
}

TAD_List get_clients_top3(FilManager fm, char *client_code)
{
    Client c = client_make(client_code);

    TAD_List l = filmanager_get_top3(fm, c);

    client_destroy(c);

    return l;
}