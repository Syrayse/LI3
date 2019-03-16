#ifndef VENDASMAN_H
#define VENDASMAN_H

#include "sale.h"

typedef struct manb *MAN_b;

MAN_b make_man(void);
void destroy_man(MAN_b);
void insert_client_man(MAN_b, char *);
void insert_product_man(MAN_b, char *);
int insert_sale_man(MAN_b, SALE);

int get_maior_linha(MAN_b);
int get_n_produtos(MAN_b);
int get_n_vendas_total(MAN_b);
int get_n_vendas_filial(MAN_b, int);
int get_n_clientes_total(MAN_b);
int get_n_clientes_alph(MAN_b, char);
double get_cashflow_total(MAN_b);
char *get_last_client(MAN_b);
int get_client_n_vendas(MAN_b, char *);

int get_not_sold_client(MAN_b);
int get_not_sold_product(MAN_b);

void set_maior_linha(MAN_b, int);

void show_boletim_vendas(MAN_b mn);

#endif