#ifndef _FILMANAGER_
#define _FILMANAGER_

#include "TAD_List.h"
#include "Client.h"
#include "Product.h"

typedef struct filmanager *FilManager;

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

#endif