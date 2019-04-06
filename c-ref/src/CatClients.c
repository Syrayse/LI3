/**
 * @file CatClients.c
 * \brief Módulo que define a classe que armazena o catálogo de clientes.
 */

#include "CatClients.h"
#include "Client.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Definição da classe que armazena o catálogo de clientes. 
 */
typedef struct cat_clients
{
    Set clients; /**< Conjunto onde são armazenados os clientes. */
} * CatClients;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
CatClients CatClients_make();
void CatClients_destroy(CatClients cc);
int CatClients_exists(CatClients cc, Client client);
void CatClients_add_client(CatClients cc, Client client);
int CatClients_size(CatClients cc);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

CatClients CatClients_make()
{
    CatClients cc = g_malloc(sizeof(struct cat_clients));

    cc->clients = set_make(client_hash, client_equal, wrapclient_destroy, NULL, NULL, NULL);

    return cc;
}

void CatClients_destroy(CatClients cc)
{
    if (cc)
    {
        set_destroy(cc->clients);
        g_free(cc);
    }
}

int CatClients_exists(CatClients cc, Client client)
{
    return set_contains(cc->clients, client);
}

void CatClients_add_client(CatClients cc, Client client)
{
    set_add(cc->clients, client, NULL);
}

int CatClients_size(CatClients cc)
{
    return set_size(cc->clients);
}