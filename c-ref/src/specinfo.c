#include "specinfo.h"
#include "util.h"
#include "sale.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metódos publicos */
SpecInfo specinfo_make(int flag);
void specinfo_destroy(SpecInfo si);
void specinfo_update(SpecInfo si, void *e);
int specinfo_get_promo_fil(SpecInfo si, int filial);
int specinfo_get_no_promo_fil(SpecInfo si, int filial);
int specinfo_get_units_month(SpecInfo si, int month);
double specinfo_get_cost(SpecInfo si);

/* Metódos privados */
// None

// ------------------------------------------------------------------------------

typedef struct specific_info
{
    int identity,
        filial[N_FILIAIS][N_PROMOS],
        monthly[N_MONTHS];
    double cost;
} * SpecInfo;

// ------------------------------------------------------------------------------

SpecInfo specinfo_make(int flag)
{
    int i, j;
    SpecInfo si = g_malloc(sizeof(struct specific_info));

    si->identity = flag;

    for (i = 0; i < N_FILIAIS; i++)
        for (j = 0; j < N_PROMOS; j++)
            si->filial[i][j] = 0;

    for (i = 0; i < N_MONTHS; i++)
        si->monthly[i] = 0;

    si->cost = 0.0;

    return si;
}

void specinfo_destroy(SpecInfo si)
{
    g_free(si);
}

void specinfo_update(SpecInfo si, void *e)
{
    int units, month, filial, promo;
    Sale sale;

    if (e)
    {
        sale = (Sale)e;
        units = sale_get_units(sale);
        month = sale_get_month(sale);
        filial = sale_get_filial(sale);
        promo = sale_get_promo(sale);

        si->filial[filial - 1][indP(promo)] += units;
        si->monthly[month - 1] += units;

        si->cost += sale_get_rev(sale);
    }
}

int specinfo_get_promo_fil(SpecInfo si, int filial)
{
    return si->filial[filial - 1][indP('P')];
}

int specinfo_get_no_promo_fil(SpecInfo si, int filial)
{
    return si->filial[filial - 1][indP('N')];
}

int specinfo_get_units_month(SpecInfo si, int month)
{
    return si->monthly[month - 1];
}

double specinfo_get_cost(SpecInfo si)
{
    return si->cost;
}
