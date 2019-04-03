/**
 * @file FilManager.h
 * \brier Interface dos metódos públicos fornecidos para instância da classe `FilManager`.
 * 
 * Na corrente versão esta classe `FilManager` possui o invariante de ser capaz de representar
 * relações explicitas entre produtos e clientes.
 */

#ifndef __FIL_MANGER__
#define __FIL_MANGER__

#include "Verifier.h"

typedef struct fil_manager *FilManager;

FilManager FilManager_make();
void FilManager_destroy(FilManager fm);
void FilManager_add_product(FilManager fm, char *product);
void FilManager_add_client(FilManager fm, char *client);
void FilManager_add_transaction(FilManager fm, Transaction t);
char **FilManager_all_filial_clients(FilManager fm);
unsigned int FilManager_N_empty_clients(FilManager fm);
unsigned int FilManager_N_empty_products(FilManager fm);
int FilManager_N_buyers_filial(FilManager fm, char *product, int filial);

static void foreach_check_all_filial(void *key, void *value, void *user_data);

#endif