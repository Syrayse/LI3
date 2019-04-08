/**
 * @file ClntInfo.c
 * \brief Código necessário aos metódos da classe `ClntInfo`.
 * 
 * Esta classe tem como objetivo relacionar os produtos com os clientes que o compraram.
 * 
 * Em módulos acima na hierarquia esta classe é utilizada de modo a representar de que forma
 * é que um dado produto foi comprado por um dado cliente em uma dada filial.
 */

#include "ClntInfo.h"
#include "commondef.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `ClntInfo`.
 */
typedef struct clntinfo
{
    signed char promo_code[N_FILIAIS]; /**< Array de código de promoções para todas as filiais. */
} * ClntInfo;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
gpointer clntinfo_make();
void clntinfo_destroy(gpointer e);
void clntinfo_update(gpointer e, gpointer user_data);
int clntinfo_promo(ClntInfo ci, int filial);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

gpointer clntinfo_make()
{
    int i;

    ClntInfo ci = g_malloc(sizeof(struct clntinfo));

    for (i = 0; i < N_FILIAIS; i++)
    {
        ci->promo_code[i] = -1;
    }

    return ci;
}

void clntinfo_destroy(gpointer e)
{
    if (e)
    {
        g_free((ClntInfo)e);
    }
}

void clntinfo_update(gpointer e, gpointer user_data)
{
    ClntInfo ci = (ClntInfo)e;
    gpointer *user = (gpointer *)user_data;
    int promo, filial = *(int *)user[0] - 1;
    promo = *(int *)user[1];

    if (ci->promo_code[filial] != promo && ci->promo_code[filial] < 2)
    {
        ci->promo_code[filial] += promo + 1;
    }
}

int clntinfo_promo(ClntInfo ci, int filial)
{
    signed char tmp = ci->promo_code[filial - 1];
    return (tmp < 0) ? -1 : tmp;
}