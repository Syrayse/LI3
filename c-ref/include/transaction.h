/**
 * @file transaction.h
 * \brief Módulo encarregue da estrutura de transação.
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "util.h"
#include "CatProducts.h"
#include "CatClients.h"

typedef struct transaction *Transaction;

Transaction trans_make();
void trans_destroy(void *e);

void trans_copy_product(Transaction src, char *dest);
void trans_copy_client(Transaction src, char *dest);
int trans_exists_efect(Transaction src, CatProducts cp, CatClients cc);

char *trans_get_client(Transaction t);
char *trans_get_product(Transaction t);
UChar trans_get_month(Transaction t);
UChar trans_get_filial(Transaction t);
UChar trans_get_promo(Transaction t);
UChar trans_get_units(Transaction t);
gID trans_get_id(Transaction t);
double trans_get_price(Transaction t);
double trans_get_rev(Transaction t);

void trans_set_client(Transaction t, char *client);
void trans_set_product(Transaction t, char *product);
void trans_set_month(Transaction t, UChar month);
void trans_set_filial(Transaction t, UChar filial);
void trans_set_promo(Transaction t, UChar promo);
void trans_set_units(Transaction t, UChar units);
void trans_set_id(Transaction t, gID id);
void trans_set_price(Transaction t, double price);

#endif
