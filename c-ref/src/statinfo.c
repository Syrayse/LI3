#include "statinfo.h"
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
StatInfo statinfo_make();
void statinfo_destroy(StatInfo);
void statinfo_builder(Transaction t, void *e);
Vendas vendas_make();
void vendas_destroy(Vendas);
void vendas_builder(Transaction t, void *e);

char* get_t_product(Vendas);
int get_t_nVendas(Vendas);
int get_t_nVendas_filial(Vendas, int);
int get_n_actors(StatInfo);
int get_t_vendas(StatInfo);
int get_t_fil_vendas(StatInfo, int filial);
int get_t_fil_vendas_promo(StatInfo, int filial);
int get_t_fil_vendas_no_promo(StatInfo, int filial);
int get_t_month_fil_vendas(StatInfo, int month, int filial);
int get_t_month_fil_vendas_promo(StatInfo, int month, int filial);
int get_t_month_fil_vendas_no_promo(StatInfo, int month, int filial);
int get_t_month_vendas(StatInfo, int month);
int get_t_month_vendas_promo(StatInfo, int month);
int get_t_month_vendas_no_promo(StatInfo, int month);

double get_t_rev(StatInfo);
double get_t_fil_rev(StatInfo, int filial);
double get_t_fil_rev_promo(StatInfo, int filial);
double get_t_fil_rev_no_promo(StatInfo, int filial);
double get_t_month_fil_rev(StatInfo, int month, int filial);
double get_t_month_fil_rev_promo(StatInfo, int month, int filial);
double get_t_month_fil_rev_no_promo(StatInfo, int month, int filial);
double get_t_month_rev(StatInfo, int month);
double get_t_month_rev_promo(StatInfo, int month);
double get_t_month_rev_no_promo(StatInfo, int month);

/* Metodos privados */
static int get_t_vendas_month_iter(StatInfo a, int month, int (*)(StatInfo, int, int));
static double get_t_rev_month_iter(StatInfo a, int month, double (*)(StatInfo, int, int));

// ------------------------------------------------------------------------------

typedef struct statistical_info
{
    int nVendasTotal,
        nVendasFilialMonth[N_FILIAIS][N_MONTHS + 1][N_PROMOS];
    double totalCashFlow,
        monthlyFilialRev[N_FILIAIS][N_MONTHS + 1][N_PROMOS];
} * StatInfo;

typedef struct vendas_Prod
{
    char* product;
    int nVendas[N_FILIAIS];
} * Vendas;

// ------------------------------------------------------------------------------

StatInfo statinfo_make()
{
    int l, c, k;
    StatInfo a = g_malloc(sizeof(struct statistical_info));

    for (l = 0; l < N_FILIAIS; l++)
    {
        for (c = 0; c <= N_MONTHS; c++)
        {
            for (k = 0; k < N_PROMOS; k++)
            {
                a->nVendasFilialMonth[l][c][k] = 0;
                a->monthlyFilialRev[l][c][k] = 0.0;
            }
        }
    }

    a->nVendasTotal = 0;
    a->totalCashFlow = 0.0;

    return a;
}

void statinfo_destroy(StatInfo a)
{
    if (a)
    {
        g_free(a);
    }
}

void statinfo_builder(Transaction t, void *e)
{
    if (!e)
        return;
    StatInfo si = (StatInfo)e;

    double rev = trans_get_rev(t);
    int f, m, p = trans_get_promo(t);
    m = trans_get_month(t);
    f = trans_get_filial(t);

    si->nVendasTotal++;
    si->nVendasFilialMonth[f - 1][0][indP(p)]++;
    si->nVendasFilialMonth[f - 1][m][indP(p)]++;

    si->totalCashFlow += rev;
    si->monthlyFilialRev[f - 1][0][indP(p)] += rev;
    si->monthlyFilialRev[f - 1][m][indP(p)] += rev;
}

Vendas vendas_make()
{
    Vendas a = g_malloc(sizeof(struct vendas_Prod));

    a->product = NULL;
    a->nVendas[0] = 0;
    a->nVendas[1] = 0;
    a->nVendas[2] = 0;

    return a;
}

void vendas_destroy(Vendas a)
{
    if (a)
    {
        g_free(a);
    }
}

void vendas_builder(Transaction t, void *e)
{
    if (!e)
        return;
    Vendas si = (Vendas)e;

    si->product  = trans_get_product(t);
    si->nVendas[trans_get_filial(t) -1] ++;
}
char* get_t_product(Vendas si)
{
    return si->product;
}

int get_t_nVendas_filial(Vendas si, int fil)
{
    return si->nVendas[fil-1];
}

int get_t_nVendas(Vendas si)
{
    int i, r = 0;
    for (i = 0; i < N_FILIAIS; i++)
        r += si->nVendas[i];
    return r;
}

int get_t_vendas(StatInfo si)
{
    return si->nVendasTotal;
}

int get_t_fil_vendas(StatInfo a, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][0][0] + a->nVendasFilialMonth[filial - 1][0][1]);
}

int get_t_fil_vendas_promo(StatInfo a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][1];
}

int get_t_fil_vendas_no_promo(StatInfo a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][0];
}

int get_t_month_fil_vendas(StatInfo a, int month, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][month][0] +
            a->nVendasFilialMonth[filial - 1][month][1]);
}

int get_t_month_fil_vendas_promo(StatInfo a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][1];
}

int get_t_month_fil_vendas_no_promo(StatInfo a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][0];
}

int get_t_month_vendas(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas);
}

int get_t_month_vendas_promo(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_promo);
}

int get_t_month_vendas_no_promo(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_no_promo);
}

double get_t_rev(StatInfo a)
{
    return a->totalCashFlow;
}

double get_t_fil_rev(StatInfo a, int filial)
{
    return (a->monthlyFilialRev[filial - 1][0][0] +
            a->monthlyFilialRev[filial - 1][0][1]);
}

double get_t_fil_rev_promo(StatInfo a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][1];
}

double get_t_fil_rev_no_promo(StatInfo a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][0];
}

double get_t_month_fil_rev(StatInfo a, int month, int filial)
{
    return (a->monthlyFilialRev[filial - 1][month][0] +
            a->monthlyFilialRev[filial - 1][month][1]);
}

double get_t_month_fil_rev_promo(StatInfo a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][1];
}

double get_t_month_fil_rev_no_promo(StatInfo a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][0];
}

double get_t_month_rev(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev);
}

double get_t_month_rev_promo(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_promo);
}

double get_t_month_rev_no_promo(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_no_promo);
}

static int get_t_vendas_month_iter(StatInfo a, int month, int (*f)(StatInfo, int, int))
{
    int k, r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}

static double get_t_rev_month_iter(StatInfo a, int month, double (*f)(StatInfo, int, int))
{
    int k;
    double r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}