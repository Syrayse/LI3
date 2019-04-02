/**
 * @file CatClients.h
 * \brief Define a API fornecida ao utilizador desta classe. 
 */

#ifndef CAT_CLIENTS_H
#define CAT_CLIENTS_H

typedef struct cat_clients *CatClients;

CatClients CatClients_make();
void CatClients_destroy(CatClients cc);
int CatClients_exists(CatClients cc, char *client);
void CatClients_add_client(CatClients cc, char *client);

#endif