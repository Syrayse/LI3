#ifndef SALE_H
#define SALE_H

#include "dbase.h"

/**
 * \brief Typedef para função que recebe dois tipos abstratos e retorna um booleano.
 **/
typedef int (*pc)(DBase, void *);

typedef struct sale *Sale;

Sale sale_make();
void sale_destroy(Sale);
void sale_wipe(Sale);
int sale_paralel_proc(DBase, DBase, Sale, pc, pc);
void sale_insert_self(DBase, DBase, Sale);
void sale_copy_client(Sale, char *);

char *sale_get_client(Sale);
char *sale_get_product(Sale);
int sale_get_month(Sale s);
int sale_get_filial(Sale s);
int sale_get_promo(Sale s);
int sale_get_units(Sale s);
double sale_get_price(Sale s);
double sale_get_rev(Sale);

void sale_set_client(Sale s, char *client);
void sale_set_product(Sale s, char *product);
void sale_set_month(Sale s, int month);
void sale_set_filial(Sale s, int filial);
void sale_set_promo(Sale s, int promo);
void sale_set_units(Sale s, int units);
void sale_set_price(Sale s, double price);

#endif