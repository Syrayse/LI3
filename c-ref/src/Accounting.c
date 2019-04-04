#include "Accounting.h"
#include "statinfo.h"
#include "util.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_update(Accounting a, char *product, int month, int filial, int units, int promo, double spent);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_n_cash_range(Accounting a, int init, int end);
int Accounting_get_global_stats(Accounting a, char *product, int month, int *trans_vec, int *spent_vec);
int Accounting_get_per_filial_stats(Accounting a, char *product, int month, int **trans_vec, int **spent_vec);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

typedef struct accounting
{
    int nTrans[N_MONTHS];         /**< Número de transações mensais. */
    double totCashFlow[N_MONTHS]; /**< Fluxo monetário mensal. */
    StrSet products[N_LETTER];    /**< Conjunto que armazenada todos os produtos. */
} * Accounting;

/* ------------------------------------------------------------------------------ */

Accounting Accounting_make()
{
    int i;
    Accounting ac = g_malloc(sizeof(struct accounting));

    for (i = 0; i < N_MONTHS; i++)
    {
        ac->nTrans[i] = 0;
        ac->totCashFlow[i] = 0.0;
    }

    for (i = 0; i < N_LETTER; i++)
    {
        ac->products[i] = strset_make(g_free, statinfo_destroy, statinfo_make, statinfo_update, NULL);
    }

    return ac;
}

void Accounting_destroy(Accounting a)
{
    int i;

    if (a)
    {
        for (i = 0; i < N_LETTER; i++)
        {
            strset_destroy(a->products[i]);
        }

        g_free(a);
    }
}

void Accounting_update(Accounting a, char *product, int month, int filial, int units, int promo, double spent)
{
    void *tmp[5];
    int p = *product - 'A';
    char *ef_product = product;
    a->nTrans[month - 1]++;
    a->totCashFlow[month - 1] += units * spent;

    tmp[0] = &month;
    tmp[1] = &filial;
    tmp[2] = &units;
    tmp[3] = &promo;
    tmp[4] = &spent;

    if (!strset_contains(a->products[p], product))
    {
        ef_product = g_strdup(product);
    }

    strset_add(a->products[p], ef_product, tmp);
}

int Accounting_n_trans_range(Accounting a, int init, int end)
{
    int i, r = -1;

    if (is_between(init, 1, N_MONTHS) && is_between(end, 1, N_MONTHS) && init <= end)
    {
        r = 0;

        for (i = init; i <= end; r += a->nTrans[i], i++)
            ;
    }

    return r;
}

double Accounting_n_cash_range(Accounting a, int init, int end)
{
    int i;
    double r = -1.0;

    if (is_between(init, 1, N_MONTHS) && is_between(end, 1, N_MONTHS) && init <= end)
    {
        r = 0.0;

        for (i = init; i <= end; r += a->totCashFlow[i], i++)
            ;
    }

    return r;
}

int Accounting_get_global_stats(Accounting a, char *product, int month, int *trans_vec, int *spent_vec)
{
    int r = 0;
    void *val;
    StatInfo si;

    if ((val = strset_lookup(a->products[*product - 'A'], product)))
    {
        r = 1;
        si = (StatInfo)val;

        trans_vec[0] = get_t_month_vendas_no_promo(si, month);
        trans_vec[1] = get_t_month_vendas_promo(si, month);
        spent_vec[0] = get_t_month_rev_no_promo(si, month);
        spent_vec[1] = get_t_month_rev_promo(si, month);
    }

    return r;
}

int Accounting_get_per_filial_stats(Accounting a, char *product, int month, int **trans_vec, int **spent_vec)
{
    int i, r = 0;
    void *val;
    StatInfo si;

    if ((val = strset_lookup(a->products[*product - 'A'], product)))
    {
        r = 1;
        si = (StatInfo)val;

        for (i = 0; i < N_FILIAIS; i++)
        {
            trans_vec[i][0] = get_t_month_fil_vendas_no_promo(si, month, i + 1);
            trans_vec[i][1] = get_t_month_fil_vendas_promo(si, month, i + 1);
            spent_vec[i][0] = get_t_month_fil_rev_no_promo(si, month, i + 1);
            spent_vec[i][1] = get_t_month_fil_rev_promo(si, month, i + 1);
        }
    }

    return r;
}
