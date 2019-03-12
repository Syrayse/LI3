#ifndef SALE_H
#define SALE_H

#include "mainstruct.h"

/**
 * \brief Typedef para função que recebe dois tipos abstratos e retorna um booleano.
 **/
typedef int (*pc)(DBase, void *);

typedef struct sale *SALE;

//Construtores e desconstrutores
SALE make_s(void);
void destroy_s(SALE);
void clean_s(SALE);
int process_paralelo_s(DBase, DBase, SALE, pc, pc);
void insert_self_s(DBase, DBase, SALE);

//setters e getters
//getters
void copy_client_s(SALE src, char *dest);
char *get_client_s(SALE s);
char *get_product_s(SALE s);
int get_month_s(SALE s);
int get_filial_s(SALE s);
int get_promo_s(SALE s);
int get_units_s(SALE s);
double get_price_s(SALE s);
double get_rev_s(SALE);

//setters
void set_client_s(SALE s, char *client);
void set_product_s(SALE s, char *product);
void set_month_s(SALE s, int month);
void set_filial_s(SALE s, int filial);
void set_promo_s(SALE s, int promo);
void set_units_s(SALE s, int units);
void set_price_s(SALE s, double price);

#endif