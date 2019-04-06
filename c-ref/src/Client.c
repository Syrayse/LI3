/**
 * @file Client.c
 * \brief Ficheiro que contém o código associado à classe `Client`.
 */
#include "Client.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Define o tamanho de um código de cliente.
 */
#define CLIENT_LEN 5

/**
 * \brief Estrutura de dados que define a classe `Client`.
 * 
 * Atualmente esta classe é unicamente composta pelo respetivo código de cliente.
 */
typedef struct client
{
    char client_code[CLIENT_LEN + 1]; /**< Código de cliente. */
} * Client;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
Client client_make(char *client_code);
void client_destroy(Client c);
Client client_clone(Client c);
char *client_get_code(Client c);
guint client_hash(gconstpointer v);
gboolean client_equal(gconstpointer v1, gconstpointer v2);
void wrapclient_destroy(gpointer v);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

Client client_make(char *client_code)
{
    Client c = g_malloc(sizeof(struct client));

    strcpy(c->client_code, client_code);

    return c;
}

void client_destroy(Client c)
{
    if (c)
    {
        g_free(c);
    }
}

Client client_clone(Client c)
{
    return client_make(c->client_code);
}

char *client_get_code(Client c)
{
    return g_strdup(c->client_code);
}

guint client_hash(gconstpointer v)
{
    Client c = (Client)v;
    return g_str_hash(c->client_code);
}

gboolean client_equal(gconstpointer v1, gconstpointer v2)
{
    Client c1 = (Client)v1;
    Client c2 = (Client)v2;
    return g_str_equal(c1->client_code, c2->client_code);
}

void wrapclient_destroy(gpointer v)
{
    client_destroy((Client)v);
}