#include "PrdtInfo.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
void *prdtinfo_make();
void prdtinfo_destroy(void *e);
void prdtinfo_update(void *e, void *user_data);
double prdtinfo_total_spent(PrdtInfo pi);
int prdtinfo_month_units(PrdtInfo pi, int month);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

typedef struct prdtinfo
{
    double total_spent;
    int month_units[N_MONTHS];
} * PrdtInfo;

/* ------------------------------------------------------------------------------ */

void *prdtinfo_make()
{
    int i;

    PrdtInfo pi = g_malloc(sizeof(struct prdtinfo));

    pi->total_spent = 0.0;

    for (i = 0; i < N_MONTHS; i++)
    {
        pi->month_units[i] = 0;
    }

    return pi;
}

void prdtinfo_destroy(void *e)
{
    if (e)
    {
        g_free((PrdtInfo)e);
    }
}

void prdtinfo_update(void *e, void *user_data)
{
    PrdtInfo pi = (PrdtInfo)e;
    void **user = (void **)user_data;
    int month = *(int *)user[2] - 1;
    pi->total_spent += *(double *)user[0];
    pi->month_units[month] += *(int *)user[1];
}

double prdtinfo_total_spent(PrdtInfo pi)
{
    return pi->total_spent;
}

int prdtinfo_month_units(PrdtInfo pi, int month)
{
    return pi->month_units[month - 1];
}
