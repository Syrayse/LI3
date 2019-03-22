#ifndef CAT_CLIENTS_H
#define CAT_CLIENTS_H

#include "util.h"

typedef struct cat_clients *CatClients;

CatClients CatClients_make();
void CatClients_destroy(CatClients cc);
int CatClients_exists(CatClients cc, char *client);
void CatClients_add_client(CatClients cc, char *client);
void CatClients_add_trans(CatClients cc, char *client, int filial, int month, gID trans_id);
gID *CatClients_drop_trans(CatClients cc, char *client, int month, int *s);
int CatClients_t_not_sold(CatClients cp);
char **CatClients_dump_all_fils(CatClients cp, int *size);

#endif