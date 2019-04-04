#include "FilManager.h"
#include "Appender.h"
#include "Adition.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metódos publicos */
FilManager filmanager_make();
void filmanager_destroy(FilManager fm);
void filmanager_update(FilManager fm, char *product, char *client, int filial, int month, int promo, int units, double spent);
char **filmanager_get_overall_clients(FilManager fm, int *size);
int **filmanager_get_units_matrix(FilManager fm, char *client);
char **filmanager_get_client_at_fil(FilManager fm, char *product, int filial, int promo, int *size);
char **filmanager_get_most_bought(FilManager fm, char *client, int month, int *size);
int filmanager_get_n_of_clients(FilManager fm, char *product);
char **filmanager_get_top3(FilManager fm, char *client, int *size);
int filmanager_get_active_n_clients(FilManager fm);
int filmanager_get_active_n_products(FilManager fm);

/* Metódos privados */
static void foreach_add_overall(gpointer key, gpointer value, gpointer user_data);
/* ------------------------------------------------------------------------------ */

typedef struct filmanager
{
    StrSet client_set,
        product_set;
} * FilManager;

/* ------------------------------------------------------------------------------ */

FilManager filmanager_make()
{
    FilManager fm = g_malloc(sizeof(struct filmanager));

    fm->client_set = strset_make(g_free, appender_destroy, appender_make, appender_update, NULL);

    fm->product_set = strset_make(g_free, adition_destroy, adition_make, adition_update, NULL);

    return fm;
}

void filmanager_destroy(FilManager fm)
{
    if (fm)
    {
        strset_destroy(fm->client_set);
        strset_destroy(fm->product_set);
        g_free(fm);
    }
}

void filmanager_update(FilManager fm, char *product, char *client, int filial, int month, int promo, int units, double spent)
{
    void *tmp[5];
    char *copy_product, *copy_client;
    copy_product = g_strdup(product);
    copy_client = g_strdup(client);

    /* Adicionar aos produtos */
    tmp[0] = copy_client;
    tmp[1] = &filial;
    tmp[2] = &promo;
    strset_add(fm->product_set, copy_product, tmp);

    /* Adicionar aos clients */
    tmp[0] = copy_product;
    tmp[1] = &filial;
    tmp[2] = &month;
    tmp[3] = &units;
    tmp[4] = &spent;
    strset_add(fm->client_set, copy_client, tmp);
}

char **filmanager_get_overall_clients(FilManager fm, int *size)
{
    int i = 0;
    char **r = g_malloc(sizeof(char *) * strset_size(fm->client_set));
    void *tmp[2];

    tmp[0] = r;
    tmp[1] = &i;

    strset_foreach(fm->client_set, foreach_add_overall, tmp);

    *size = i;

    if (i == 0)
    {
        g_free(r);
        r = NULL;
    }

    return r;
}

int **filmanager_get_units_matrix(FilManager fm, char *client)
{
    int **r = NULL;
    void *val;

    if ((val = strset_lookup(fm->client_set, client)))
    {
        r = appender_clone_matrix((Appender)val);
    }

    return r;
}

char **filmanager_get_client_at_fil(FilManager fm, char *product, int filial, int promo, int *size)
{
    char **r = NULL;
    void *val;

    if (promo >= 0 && (val = strset_lookup(fm->product_set, product)))
    {
        r = adition_dump_by_promo_fil((Adition)val, filial, promo, size);
    }

    return r;
}

char **filmanager_get_most_bought(FilManager fm, char *client, int month, int *size)
{
    char **r = NULL;
    void *val;

    if ((val = strset_lookup(fm->client_set, client)))
    {
        r = appender_get_most_bought((Appender)val, month, size);
    }

    return r;
}

int filmanager_get_n_of_clients(FilManager fm, char *product)
{
    int r = -1;
    void *val;

    if ((val = strset_lookup(fm->product_set, product)))
    {
        r = adition_size((Adition)val);
    }

    return r;
}

char **filmanager_get_top3(FilManager fm, char *client, int *size)
{
    char **r = NULL;
    void *val;

    if ((val = strset_lookup(fm->client_set, client)))
    {
        r = appender_get_top3((Appender)val, size);
    }

    return r;
}

int filmanager_get_active_n_clients(FilManager fm)
{
    return strset_size(fm->client_set);
}

int filmanager_get_active_n_products(FilManager fm)
{
    return strset_size(fm->product_set);
}

static void foreach_add_overall(gpointer key, gpointer value, gpointer user_data)
{
    void **holder = (void **)user_data;

    if (is_bought_in_all((Appender)value))
    {
        ((char **)holder[0])[(*(int *)holder[1])++] = g_strdup((char *)key);
    }
}