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

typedef struct verifier *Verifier;
typedef struct transaction *Transaction;

Verifier Verifier_make();
void Verifier_destroy(Verifier v);
char *verify_client(char *client);
char *verify_product(char *product);
Transaction verify_sale(Verifier v, char *trans_code);

Transaction trans_make();
void trans_destroy(void *e);

void trans_copy_product(Transaction src, char *dest);
void trans_copy_client(Transaction src, char *dest);

char *trans_get_client(Transaction t);
char *trans_get_product(Transaction t);
unsigned char trans_get_month(Transaction t);
unsigned char trans_get_filial(Transaction t);
unsigned char trans_get_promo(Transaction t);
unsigned char trans_get_units(Transaction t);
double trans_get_price(Transaction t);
double trans_get_rev(Transaction t);

#endif