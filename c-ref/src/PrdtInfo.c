/**
 * @file PrdtInfo.c
 * \brief Ficheiro que contém toda a codificação associada à classe `PrdtInfo`.
 * 
 * Esta classe tem como objetivo principal ser utilizada por classes acima na hierarquia,
 * classes essas que necessitam de informação guardada numa classe do tipo `PrdtInfo`.
 * 
 * Possui capacidade de armazenar informação útil que, dado um Produto, seja capaz de indicar
 * quanto dinheiro foi gasto no total nesse produto, e quantas unidades foram compradas mensalmente.
 * 
 * Pretende-se que esta classe seja utilizada como uma forma de representar informação
 * entre um cliente e um produto, sendo que contém toda a informação para que este meio seja
 * alcançado da forma mais eficiente, segundo as queries pedidas.
 */

#include "PrdtInfo.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
gpointer prdtinfo_make();
void prdtinfo_destroy(gpointer e);
void prdtinfo_update(gpointer e, gpointer user_data);
double prdtinfo_total_spent(PrdtInfo pi);
int prdtinfo_month_units(PrdtInfo pi, int month);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `PrdtInfo`
 * 
 * Implicitamente, pela hierarquia composta no serviço SVG, uma instância da classe `PrdtInfo`
 * é representativa de toda a informação útil entre um dado cliente um produto especifico.
 */
typedef struct prdtinfo
{
    double total_spent;        /**< Total gasto naquele produto. */
    int month_units[N_MONTHS]; /**< Número de unidades mensais transacionadas entre os intervenientes. */
} * PrdtInfo;

/* ------------------------------------------------------------------------------ */

gpointer prdtinfo_make()
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

void prdtinfo_destroy(gpointer e)
{
    if (e)
    {
        g_free((PrdtInfo)e);
    }
}

void prdtinfo_update(gpointer e, gpointer user_data)
{
    PrdtInfo pi = (PrdtInfo)e;
    gpointer *user = (gpointer *)user_data;
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
