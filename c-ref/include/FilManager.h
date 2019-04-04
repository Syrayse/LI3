#ifndef _FILMANAGER_
#define _FILMANAGER_

typedef struct filmanager *FilManager;

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

#endif