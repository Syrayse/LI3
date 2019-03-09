#include "sale.h"
#include "appender.h"
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
APPENDER make_appender();
void update_appender(APPENDER, void *);
int get_t_vendas(APPENDER);
int get_t_fil_vendas(APPENDER, int filial);
int get_t_fil_vendas_promo(APPENDER, int filial);
int get_t_fil_vendas_no_promo(APPENDER, int filial);
int get_t_month_fil_vendas(APPENDER, int month, int filial);
int get_t_month_fil_vendas_promo(APPENDER, int month, int filial);
int get_t_month_fil_vendas_no_promo(APPENDER, int month, int filial);
int get_t_month_vendas(APPENDER, int month);
int get_t_month_vendas_promo(APPENDER, int month);
int get_t_month_vendas_no_promo(APPENDER, int month);
float get_t_rev(APPENDER);
float get_t_fil_rev(APPENDER, int filial);
float get_t_fil_rev_promo(APPENDER, int filial);
float get_t_fil_rev_no_promo(APPENDER, int filial);
float get_t_month_fil_rev(APPENDER, int month, int filial);
float get_t_month_fil_rev_promo(APPENDER, int month, int filial);
float get_t_month_fil_rev_no_promo(APPENDER, int month, int filial);
float get_t_month_rev(APPENDER, int month);
float get_t_month_rev_promo(APPENDER, int month);
float get_t_month_rev_no_promo(APPENDER, int month);
void destroy_appender(void *);

/* Metodos privados */
int get_t_vendas_month_iter(APPENDER a, int month, int (*)(APPENDER, int, int));
float get_t_rev_month_iter(APPENDER a, int month, float (*)(APPENDER, int, int));

// ------------------------------------------------------------------------------

typedef struct appendix
{
    int nVendasTotal,
        nVendasFilialMonth[N_FILIAIS][N_MONTHS + 1][2];
    float totalRevenue,
        monthlyFilialRev[N_FILIAIS][N_MONTHS + 1][2];
} * APPENDER;

// ------------------------------------------------------------------------------

APPENDER make_appender()
{
    int l, c, k;
    APPENDER a = g_malloc(sizeof(struct appendix));

    a->nVendasTotal = 0;

    for (l = 0; l < N_FILIAIS; l++)
    {
        for (c = 0; c <= N_MONTHS; c++)
        {
            for (k = 0; k < N_PROMOS; k++)
            {
                a->nVendasFilialMonth[l][c][k] = 0;
                a->monthlyFilialRev[l][c][k] = 0;
            }
        }
    }

    a->totalRevenue = 0;

    return a;
}

void update_appender(APPENDER a, void *e)
{
    if (!e)
        return;
    SALE s = (SALE)e;
    float rev = (get_units_s(s) * get_price_s(s));
    int f, m, p = get_promo_s(s);
    m = get_month_s(s);
    f = get_filial_s(s);

    // Vendas
    a->nVendasTotal++;
    a->nVendasFilialMonth[f - 1][0][indP(p)]++;
    a->nVendasFilialMonth[f - 1][m][indP(p)]++;

    // Profit
    a->totalRevenue += rev;
    a->monthlyFilialRev[f - 1][0][indP(p)] += rev;
    a->monthlyFilialRev[f - 1][m][indP(p)] += rev;
}

int get_t_vendas(APPENDER a)
{
    return a->nVendasTotal;
}

int get_t_fil_vendas(APPENDER a, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][0][0] + a->nVendasFilialMonth[filial - 1][0][1]);
}

int get_t_fil_vendas_promo(APPENDER a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][1];
}

int get_t_fil_vendas_no_promo(APPENDER a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][0];
}

int get_t_month_fil_vendas(APPENDER a, int month, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][month][0] +
            a->nVendasFilialMonth[filial - 1][month][1]);
}

int get_t_month_fil_vendas_promo(APPENDER a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][1];
}

int get_t_month_fil_vendas_no_promo(APPENDER a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][0];
}

int get_t_vendas_month_iter(APPENDER a, int month, int (*f)(APPENDER, int, int))
{
    int k, r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}

float get_t_rev_month_iter(APPENDER a, int month, float (*f)(APPENDER, int, int))
{
    int k;
    float r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}

int get_t_month_vendas(APPENDER a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas);
}

int get_t_month_vendas_promo(APPENDER a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_promo);
}

int get_t_month_vendas_no_promo(APPENDER a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_no_promo);
}

float get_t_rev(APPENDER a)
{
    return a->totalRevenue;
}

float get_t_fil_rev(APPENDER a, int filial)
{
    return (a->monthlyFilialRev[filial - 1][0][0] +
            a->monthlyFilialRev[filial - 1][0][1]);
}

float get_t_fil_rev_promo(APPENDER a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][1];
}

float get_t_fil_rev_no_promo(APPENDER a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][0];
}

float get_t_month_fil_rev(APPENDER a, int month, int filial)
{
    return (a->monthlyFilialRev[filial - 1][month][0] +
            a->monthlyFilialRev[filial - 1][month][1]);
}

float get_t_month_fil_rev_promo(APPENDER a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][1];
}

float get_t_month_fil_rev_no_promo(APPENDER a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][0];
}

float get_t_month_rev(APPENDER a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev);
}

float get_t_month_rev_promo(APPENDER a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_promo);
}

float get_t_month_rev_no_promo(APPENDER a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_no_promo);
}

void destroy_appender(void *a)
{
    if (a)
        g_free((APPENDER)a);
}