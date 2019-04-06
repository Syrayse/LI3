/**
 * @file FilManager.c
 * \brief Ficheiro que contém toda a condificação associada à classe `FilManager`.
 * 
 * Esta classe tem como objetivo representar todas as relações existentes entre clientes
 * e os produtos que este comprou, ou, produtos e os clientes que o compraram. Esta classe efetua o tratamento
 * de todas as filiais de uma só vez. Sendo que, para um dado produto ou cliente está presente
 * toda a informação útil necessária para representar as diferentes ligações para todas as filiais.
 */
#include "FilManager.h"
#include "Appender.h"
#include "Adition.h"
#include "set.h"
#include "TAD_List.h"
#include "Client.h"
#include "Product.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `FilManager`.
 * 
 * Esta classe possui dois `Set`'s, um dos _sets_ tem como objetivo representar todos os clientes que efetuaram transações
 * e a forma como eles se ligam a todos os produtos que possam vir a ter comprado em qualquer uma das filiais.
 * O outro conjunto, tem como objetivo representar todos os produtos que foram transacionados e a forma como estes se ligam
 * a todos os clientes que os possam vir a ter transacionado em qualquer uma das filiais.
 */
typedef struct filmanager
{
    Set client_set,  /**< Conjunto de clientes. */
        product_set; /**< Conjunto de produtos. */
} * FilManager;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
FilManager filmanager_make();
void filmanager_destroy(FilManager fm);
void filmanager_update(FilManager fm, Product product, Client client, int filial, int month, int promo, int units, double spent);
TAD_List filmanager_get_overall_clients(FilManager fm);
int **filmanager_get_units_matrix(FilManager fm, Client client);
TAD_List filmanager_get_client_at_fil(FilManager fm, Product product, int filial, int promo);
TAD_List filmanager_get_most_bought(FilManager fm, Client client, int month);
int filmanager_get_n_of_clients(FilManager fm, Product product);
TAD_List filmanager_get_top3(FilManager fm, Client client);
int filmanager_get_active_n_clients(FilManager fm);
int filmanager_get_active_n_products(FilManager fm);

/* Métodos privados */
static void foreach_add_overall(gpointer key, gpointer value, gpointer user_data);
static int mystrcmp(gconstpointer v1, gconstpointer v2);

/* ------------------------------------------------------------------------------ */

FilManager filmanager_make()
{
    FilManager fm = g_malloc(sizeof(struct filmanager));

    fm->client_set = set_make(client_hash, client_equal, wrapclient_destroy, appender_destroy, appender_make, appender_update);

    fm->product_set = set_make(product_hash, product_equal, wrapproduct_destroy, adition_destroy, adition_make, adition_update);

    return fm;
}

void filmanager_destroy(FilManager fm)
{
    if (fm)
    {
        set_destroy(fm->client_set);
        set_destroy(fm->product_set);
        g_free(fm);
    }
}

void filmanager_update(FilManager fm, Product product, Client client, int filial, int month, int promo, int units, double spent)
{
    void *tmp[5];
    Product copy_product = product_clone(product);
    Client copy_client = client_clone(client);

    /* Adicionar aos produtos */
    tmp[0] = copy_client;
    tmp[1] = &filial;
    tmp[2] = &promo;
    set_add(fm->product_set, copy_product, tmp);

    /* Adicionar aos clients */
    tmp[0] = copy_product;
    tmp[1] = &filial;
    tmp[2] = &month;
    tmp[3] = &units;
    tmp[4] = &spent;
    set_add(fm->client_set, copy_client, tmp);
}

TAD_List filmanager_get_overall_clients(FilManager fm)
{
    TAD_List tl = list_make(g_free, set_size(fm->client_set));

    set_foreach(fm->client_set, foreach_add_overall, tl);

    list_sort(tl, mystrcmp);

    return tl;
}

int **filmanager_get_units_matrix(FilManager fm, Client client)
{
    int **r = NULL;
    gpointer val;

    if ((val = set_lookup(fm->client_set, client)))
    {
        r = appender_clone_matrix((Appender)val);
    }

    return r;
}

TAD_List filmanager_get_client_at_fil(FilManager fm, Product product, int filial, int promo)
{
    TAD_List tl = NULL;
    gpointer val;

    if (promo >= 0 && (val = set_lookup(fm->product_set, product)))
    {
        tl = adition_dump_by_promo_fil((Adition)val, filial, promo);
    }

    return tl;
}

TAD_List filmanager_get_most_bought(FilManager fm, Client client, int month)
{
    TAD_List tl = NULL;
    gpointer val;

    if ((val = set_lookup(fm->client_set, client)))
    {
        tl = appender_get_most_bought((Appender)val, month);
    }

    return tl;
}

int filmanager_get_n_of_clients(FilManager fm, Product product)
{
    int r = -1;
    gpointer val;

    if ((val = set_lookup(fm->product_set, product)))
    {
        r = adition_size((Adition)val);
    }

    return r;
}

TAD_List filmanager_get_top3(FilManager fm, Client client)
{
    TAD_List tl = NULL;
    gpointer val;

    if ((val = set_lookup(fm->client_set, client)))
    {
        tl = appender_get_top3((Appender)val);
    }

    return tl;
}

int filmanager_get_active_n_clients(FilManager fm)
{
    return set_size(fm->client_set);
}

int filmanager_get_active_n_products(FilManager fm)
{
    return set_size(fm->product_set);
}

static void foreach_add_overall(gpointer key, gpointer value, gpointer user_data)
{
    TAD_List tl = (TAD_List)user_data;

    if (is_bought_in_all((Appender)value))
    {
        list_add(tl, client_get_code((Client)key));
    }
}

static int mystrcmp(gconstpointer v1, gconstpointer v2)
{
    return strcmp(*(char **)v1, *(char **)v2);
}