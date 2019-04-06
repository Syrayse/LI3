/**
 * @file Queries.c
 * \brief Ficheiro de código responsável pela codificação das Queries necessárias ao SGV.
 */

#include "Queries.h"

/* ------------------------------------------------------------------------------ */

/* Metódos publicos */
TAD_List get_sorted_products(CatProducts cp, char let);                                                          /* Q2 */
int get_product_global_stats(Accounting a, char *product_code, int month, int *trans_vec, int *spent_vec);       /* Q3 */
int get_product_per_filial_stats(Accounting a, char *product_code, int month, int **trans_vec, int **spent_vec); /* Q3 */
TAD_List get_not_bought_products(CatProducts cp, int filial);                                                    /* Q4 */
TAD_List get_overall_clients(FilManager fm);                                                                     /* Q5 */
int get_n_not_bought_clients(CatClients cc, FilManager fm);                                                      /* Q6 */
int get_n_not_bought_products(CatProducts cp, FilManager fm);                                                    /* Q6 */
int **get_matrix(FilManager fm, char *client_code);                                                              /* Q7 */
int get_interval_units(Accounting ac, int init, int end);                                                        /* Q8 */
double get_interval_rev(Accounting ac, int init, int end);                                                       /* Q8 */
TAD_List get_product_buyers(FilManager fm, char *product_code, int filial, int promo);                           /* Q9 */
TAD_List get_clients_most_bought(FilManager fm, char *client_code, int month);                                   /* Q10 */
TAD_List get_topN_most_sold(Accounting ac, FilManager fm, int N);                                                /* Q11 */
TAD_List get_clients_top3(FilManager fm, char *client_code);                                                     /* Q12 */

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