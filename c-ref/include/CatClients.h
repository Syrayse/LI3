/**
 * @file CatClients.h
 * \brief Define a interface fornecida ao utilizador que pretenda manuseado o catálogo de clientes.
 */

#ifndef CAT_CLIENTS_H
#define CAT_CLIENTS_H

#include "Client.h"

/**
 * \brief Estrutura de dados que define o catálogo de clientes.
 */
typedef struct cat_clients *CatClients;

/**
 * \brief Inicializa um novo catálogo de clientes.
 * 
 * @returns Um novo catálogo inicializado.
 */
CatClients CatClients_make();

/**
 * \brief Liberta a memória associado a um catálogo de clientes.
 * 
 * @param cc Catálogo de clientes a considerar.
 */
void CatClients_destroy(CatClients cc);

/**
 * \brief Verifica se um cliente existe no catálogo de clientes.
 * 
 * @param cc Catálogo de clientes a considerar.
 * @param client Cliente a considerar.
 * 
 * @returns 1 se o cliente existe no catálogo de clientes, 0 caso contrário.
 */
int CatClients_exists(CatClients cc, Client client);

/**
 * \brief Adiciona um cliente ao catálogo de clientes.
 * 
 * @param cc Catálogo de clientes a considerar.
 * @param client Cliente que se pretende adicionar.
 */
void CatClients_add_client(CatClients cc, Client client);

#endif