/**
 * @file Adition.c
 * \brief Ficheiro de código necessário a todos metódos da classe `Adition`.
 * 
 * Em módulos acima na hierarquia esta classe é utilizada de forma a armazenar todos
 * os clientes que estão associados a um dado produto, representando, assim, a relação
 * de um produto com todos os clientes que o compraram.
 * 
 * Para cada cliente presente no conjunto da instância é guardada a forma como este
 * interagiu com o produto ao qual está anexada esta instância.
 */

#include "Adition.h"
#include "ClntInfo.h"
#include "Client.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `Adition`.
 */
typedef struct adition
{
    Set client_set; /**< Conjunto que armazena todos clientes. */
} * Adition;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
gpointer adition_make();
void adition_destroy(gpointer e);
void adition_update(gpointer e, gpointer user_data);
TAD_List adition_dump_by_promo_fil(Adition ad, int filial, int promo);
int adition_size(Adition ad);

/* Métodos privados */
static void foreach_add(gpointer key, gpointer value, gpointer user_data);

/* ------------------------------------------------------------------------------ */

gpointer adition_make()
{
    Adition ad = g_malloc(sizeof(struct adition));

    ad->client_set = set_make(client_hash, client_equal, NULL, clntinfo_destroy, clntinfo_make, clntinfo_update);

    return ad;
}

void adition_destroy(gpointer e)
{
    Adition ad;

    if (e)
    {
        ad = (Adition)e;
        set_destroy(ad->client_set);
        g_free(ad);
    }
}

void adition_update(gpointer e, gpointer user_data)
{
    Adition ad = (Adition)e;
    gpointer *user = (gpointer *)user_data;
    set_add(ad->client_set, (Client)user[0], user + 1);
}

TAD_List adition_dump_by_promo_fil(Adition ad, int filial, int promo)
{
    gpointer tmp[3];
    TAD_List tl = list_make(g_free, set_size(ad->client_set));

    tmp[0] = tl;
    tmp[1] = &promo;
    tmp[2] = &filial;
    set_foreach(ad->client_set, foreach_add, tmp);

    return tl;
}

int adition_size(Adition ad)
{
    return set_size(ad->client_set);
}

static void foreach_add(gpointer key, gpointer value, gpointer user_data)
{
    gpointer *holder = (gpointer *)user_data;
    TAD_List tl = (TAD_List)holder[0];
    int catched_promo, used_promo, filial;
    used_promo = *(int *)holder[1];
    filial = *(int *)holder[2];
    catched_promo = clntinfo_promo((ClntInfo)value, filial);

    if (used_promo == catched_promo || catched_promo == 2)
    {
        list_add(tl, client_get_code((Client)key));
    }
}