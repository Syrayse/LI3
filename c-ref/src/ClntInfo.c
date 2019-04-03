#include "ClntInfo.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
void *clntinfo_make();
void clntinfo_destroy(void *e);
void clntinfo_update(void *e, void *user_data);
int clntinfo_promo(ClntInfo ci, int filial);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

typedef struct clntinfo
{
    signed char promo_code[N_FILIAIS];
} * ClntInfo;

/* ------------------------------------------------------------------------------ */

void *clntinfo_make()
{
    int i;

    ClntInfo ci = g_malloc(sizeof(struct clntinfo));

    for (i = 0; i < N_FILIAIS; i++)
    {
        ci->promo_code[i] = -1;
    }

    return ci;
}

void clntinfo_destroy(void *e)
{
    if (e)
    {
        g_free((ClntInfo)e);
    }
}

void clntinfo_update(void *e, void *user_data)
{
    ClntInfo ci = (ClntInfo)e;
    void **user = (void *)user_data;
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