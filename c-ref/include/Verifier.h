/**
 * @file Verifier.h
 * \brief Interface da classe de validação, `Verifier`, e todas as necessárias funções de validação.
 * 
 * Contem todas as funções utilizaveis pelo utilizador deste API.
 * 
 * @see Transaction
 */

#ifndef __VERIFF__
#define __VERIFF__

#include "transaction.h"

typedef struct verifier *Verifier;

Verifier Verifier_make();
void Verifier_destroy(Verifier v);
char *verify_client(char *client);
char *verify_product(char *product);
Transaction verify_sale(Verifier v, char *trans_code, CatProducts cp, CatClients cc, gID id);

#endif