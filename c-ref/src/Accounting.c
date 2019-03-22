#include "Accounting.h"
#include "gArray.h"
#include "set.h"
#include "record.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_add(Accounting a, Transaction t);
int Accounting_n_trans(Accounting a);
int Accounting_n_trans_month(Accounting a, int month);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_t_cash(Accounting a);
double Accounting_t_cash_month(Accounting a, int month);
double Accounting_n_cash_range(Accounting A, int init, int end);
void Accounting_iter(Accounting a, gID *id_arr, int N, void (*f_iter)(Transaction, void *), void *user_data);
StatInfo Accounting_get_statinfo(Accounting a, gID *id_arr, int N);
gID Accounting_get_next_id(Accounting a);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

typedef struct accounting
{
    int nTrans[N_MONTHS + 1];
    double totCashFlow[N_MONTHS + 1];
    GrowingArray treg;
} * Accounting;

// ------------------------------------------------------------------------------

#define BASE_SIZE 900000

// ------------------------------------------------------------------------------

Accounting Accounting_make()
{
    int i;
    Accounting a = g_malloc(sizeof(struct accounting));

    for (i = 0; i < N_MONTHS + 1; i++)
    {
        a->totCashFlow[i] = 0.0;
        a->nTrans[i] = 0;
    }

    a->treg = garray_make_sized(sizeof(Transaction), BASE_SIZE, trans_destroy);

    return a;
}

void Accounting_destroy(Accounting a)
{
    if (a)
    {
        garray_destroy(a->treg);
        g_free(a);
    }
}

void Accounting_add(Accounting a, Transaction t)
{
    garray_add(a->treg, t);
}

int Accounting_n_trans(Accounting a)
{
    return a->nTrans[0];
}

int Accounting_n_trans_month(Accounting a, int month)
{
    int r = -1;

    if (is_between(month, 1, N_MONTHS))
        r = a->nTrans[month];

    return r;
}

int Accounting_n_trans_range(Accounting a, int init, int end)
{
    int i, r = -1;

    if (is_between(init, 1, N_MONTHS) && is_between(end, 1, N_MONTHS))
    {
        r = 0;

        for (i = init; i <= end; r += a->nTrans[i], i++)
            ;
    }

    return r;
}

double Accounting_t_cash(Accounting a)
{
    return a->totCashFlow[0];
}

double Accounting_t_cash_month(Accounting a, int month)
{
    double r = -1.0;

    if (is_between(month, 1, N_MONTHS))
        r = a->totCashFlow[month];

    return r;
}

double Accounting_n_cash_range(Accounting a, int init, int end)
{
    int i;
    double r = -1.0;

    if (is_between(init, 1, N_MONTHS) && is_between(end, 1, N_MONTHS))
    {
        r = 0.0;

        for (i = init; i <= end; r += a->totCashFlow[i], i++)
            ;
    }

    return r;
}

void Accounting_iter(Accounting a, gID *id_arr, int N, void (*f_iter)(Transaction, void *), void *user_data)
{
    int i;
    void *r = NULL;

    if (f_iter && user_data)
    {
        for (i = 0; i < N; i++)
        {
            if ((r = garray_get_index(a->treg, id_arr[i])))
            {
                (*f_iter)((Transaction)r, user_data);
            }
        }
    }
}

StatInfo Accounting_get_statinfo(Accounting a, gID *id_arr, int N)
{
    if (N <= 0)
        return NULL;

    StatInfo si = statinfo_make();

    Accounting_iter(a, id_arr, N, statinfo_builder, si);

    return si;
}

gID Accounting_get_next_id(Accounting a)
{
    return garray_size(a->treg);
}