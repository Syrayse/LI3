#ifndef VENDASMAN_H
#define VENDASMAN_H

#include "sale.h"

typedef struct manb *MAN_b;

MAN_b make_man(void);
void destroy_man(MAN_b);
int insert_client_man(MAN_b, char *);
int insert_product_man(MAN_b, char *);
int insert_sale_man(MAN_b, SALE);

int get_maior_linha(MAN_b);
int get_n_produtos(MAN_b);
int get_n_vendas_total(MAN_b);
int get_n_vendas_filial(MAN_b, int);
int get_n_clientes_total(MAN_b);
int get_n_clientes_alph(MAN_b, char);
float get_cashflow_total(MAN_b);
char *get_last_client(MAN_b);
int get_client_n_vendas(MAN_b, char *);

void set_maior_linha(MAN_b, int);
void set_last_client(MAN_b, SALE);

void show_boletim_vendas(MAN_b mn);

#endif