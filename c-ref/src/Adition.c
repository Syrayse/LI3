#include "Adition.h"
#include "ClntInfo.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
void *adition_make();
void adition_destroy(void *e);
void adition_update(void *e, void *user_data);
char **adition_dump_by_promo_fil(Adition ad, int filial, int promo, int *size);
int adition_size(Adition ad);

/* Metodos privados */
static void foreach_add(gpointer key, gpointer value, gpointer user_data);

/* ------------------------------------------------------------------------------ */

typedef struct adition
{
    StrSet client_set;
} * Adition;

/* ------------------------------------------------------------------------------ */

void *adition_make()
{
    Adition ad = g_malloc(sizeof(struct adition));

    ad->client_set = strset_make(NULL, clntinfo_destroy, clntinfo_make, clntinfo_update, NULL);

    return ad;
}

void adition_destroy(void *e)
{
    Adition ad;

    if (e)
    {
        ad = (Adition)e;
        strset_destroy(ad->client_set);
        g_free(ad);
    }
}

void adition_update(void *e, void *user_data)
{
    Adition ad = (Adition)e;
    void **user = (void **)user_data;
    strset_add(ad->client_set, (char *)user[0], user + 1);
}

int adition_get_promo(Adition ad, char *client, int filial)
{
    int r = -1;
    void *val;

    if ((val = strset_lookup(ad->client_set, client)))
    {
        r = clntinfo_promo((ClntInfo)val, filial);
    }

    return r;
}

char **adition_dump_by_promo_fil(Adition ad, int filial, int promo, int *size)
{
    int i = 0;
    void *tmp[4];
    char **r = g_malloc(sizeof(char *) * strset_size(ad->client_set));

    tmp[0] = r;
    tmp[1] = &i;
    tmp[2] = &promo;
    tmp[3] = &filial;

    strset_foreach(ad->client_set, foreach_add, tmp);

    *size = i;

    if (i == 0)
    {
        g_free(r);
        r = NULL;
    }

    return r;
}

int adition_size(Adition ad)
{
    return strset_size(ad->client_set);
}

static void foreach_add(gpointer key, gpointer value, gpointer user_data)
{
    void **holder = (void **)user_data;
    int catched_promo, used_promo, filial;
    used_promo = *(int *)holder[2];
    filial = *(int *)holder[3];
    catched_promo = clntinfo_promo((ClntInfo)value, filial);

    if (used_promo == catched_promo || catched_promo == 2)
    {
        ((char **)holder[0])[(*(int *)holder[1])++] = g_strdup((char *)key);
    }
}