#ifndef SALE_H
#define SALE_H

#include "mainstruct.h"

/**
 * \brief Typedef para função que recebe dois tipos abstratos e retorna um booleano.
 **/
typedef int (*pc)(DBase, void*);

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
unsigned char get_month_s(SALE s);
unsigned char get_filial_s(SALE s);
unsigned char get_promo_s(SALE s);
unsigned char get_units_s(SALE s);
float get_price_s(SALE s);

//setters
void set_client_s(SALE s, char *client);
void set_product_s(SALE s, char *product);
void set_month_s(SALE s, unsigned char month);
void set_filial_s(SALE s, unsigned char filial);
void set_promo_s(SALE s, unsigned char promo);
void set_units_s(SALE s, unsigned char units);
void set_price_s(SALE s, float price);

#endif