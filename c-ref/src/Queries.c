/**
 * @file Queries.c
 * \brief Ficheiro de código responsável pela codificação das Queries necessárias ao SGV.
 */

#include "Queries.h"

/* ------------------------------------------------------------------------------ */

/* Metódos publicos */
TAD_List get_sorted_products(CatProducts cp, char let);
int get_product_global_stats(Accounting a, char *product_code, int month, int *trans_vec, int *spent_vec);
int get_product_per_filial_stats(Accounting a, char *product_code, int month, int **trans_vec, int **spent_vec);
TAD_List get_not_bought_products(CatProducts cp, int filial);
TAD_List get_overall_clients(FilManager fm);
int get_n_not_bought_clients(CatClients cc, FilManager fm);
int get_n_not_bought_products(CatProducts cp, FilManager fm);
int **get_matrix(FilManager fm, char *client_code);
int get_interval_units(Accounting ac, int init, int end);
double get_interval_rev(Accounting ac, int init, int end);
TAD_List get_product_buyers(FilManager fm, char *product_code, int filial, int promo);
TAD_List get_clients_most_bought(FilManager fm, char *client_code, int month);
TAD_List get_topN_most_sold(Accounting ac, FilManager fm, int N);
TAD_List get_clients_top3(FilManager fm, char *client_code);

/* Metõdos privados */

/* ------------------------------------------------------------------------------ */

TAD_List get_sorted_products(CatProducts cp, char let)
{
    return NULL;
}

int get_product_global_stats(Accounting a, char *product_code, int month, int *trans_vec, int *spent_vec)
{
    return 0;
}

int get_product_per_filial_stats(Accounting a, char *product_code, int month, int **trans_vec, int **spent_vec)
{
    return 0;
}

TAD_List get_not_bought_products(CatProducts cp, int filial)
{
    return NULL;
}

TAD_List get_overall_clients(FilManager fm)
{
    return NULL;
}

int get_n_not_bought_clients(CatClients cc, FilManager fm)
{
    return 0;
}

int get_n_not_bought_products(CatProducts cp, FilManager fm)
{
    return 0;
}

int **get_matrix(FilManager fm, char *client_code)
{
    return NULL;
}

int get_interval_units(Accounting ac, int init, int end)
{
    return 0;
}

double get_interval_rev(Accounting ac, int init, int end)
{
    return 0.0;
}

TAD_List get_product_buyers(FilManager fm, char *product_code, int filial, int promo)
{
    return NULL;
}

TAD_List get_clients_most_bought(FilManager fm, char *client_code, int month)
{
    return NULL;
}

TAD_List get_topN_most_sold(Accounting ac, FilManager fm, int N)
{
    return NULL;
}

TAD_List get_clients_top3(FilManager fm, char *client_code)
{
    return NULL;
}