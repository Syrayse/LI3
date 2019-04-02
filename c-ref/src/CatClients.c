/**
 * @file CatClients.c
 * \brief Módulo que define a classe que armazena o catálogo de clientes.
 */

#include "CatClients.h"
#include "set.h"

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
CatClients CatClients_make();
void CatClients_destroy(CatClients cc);
int CatClients_exists(CatClients cc, char *client);
void CatClients_add_client(CatClients cc, char *client);

/* Metodos privados */
/* Nenhum */

/* ------------------------------------------------------------------------------ */

/**
 * \brief Definição da classe que armazena o catálogo de clientes. 
 */
typedef struct cat_clients
{
    StrSet clients; /**< Conjunto onde são armazenados os clientes. */
} * CatClients;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Cria uma instância da classe `CatClients`.
 * 
 * Para além de criar a instância, inicializa o conjunto necessário.
 * 
 * @returns Uma instância da classe `CatClients`.
 */
CatClients CatClients_make()
{
    CatClients cc = g_malloc(sizeof(struct cat_clients));

    cc->clients = strset_make(g_free, NULL, NULL, NULL, NULL);

    return cc;
}

/**
 * \brief Destrói uma instância da classe `CatClients`.
 * 
 * @param cc Instância a destruir.
 */
void CatClients_destroy(CatClients cc)
{
    if (cc)
    {
        strset_destroy(cc->clients);
        g_free(cc);
    }
}

/**
 * \brief Verifica se um cliente existe no catalogo de clientes.
 * 
 * @param cp Instância a considerar.
 * @param client Cliente que se pretende verificar.
 * 
 * @returns 1 caso o cliente exista, 0 caso contrário.
 */
int CatClients_exists(CatClients cc, char *client)
{
    return strset_contains(cc->clients, client);
}

/**
 * \brief Adiciona um cliente ao catalogo de clientes.
 * 
 * @param cp Instância a considerar.
 * @param client Cliente a adicionar ao catálogo.
 */
void CatClients_add_client(CatClients cc, char *client)
{
    strset_add(cc->clients, client, NULL);
}