#ifndef VENDASMAN_H
#define VENDASMAN_H

#include "sale.h"
#include "statinfo.h"

typedef struct manb *MAN_b;
MAN_b make_man(void);
void destroy_man(MAN_b);
void insert_client_man(MAN_b, char *);
void insert_product_man(MAN_b, char *);
int insert_sale_man(MAN_b, Sale);

int get_maior_linha(MAN_b);
int get_n_produtos(MAN_b);
int get_n_vendas_total(MAN_b);
int get_n_vendas_filial(MAN_b, int);
int get_n_vendas_month(MAN_b, int);
double get_n_faturacao_month(MAN_b, int);
int get_n_clientes_total(MAN_b);
double get_cashflow_total(MAN_b);
char *get_last_client(MAN_b);
int get_not_sold_client(MAN_b);
int get_not_sold_product(MAN_b);

int get_n_vendas_range(MAN_b, int, int);
double get_n_faturacao_range(MAN_b, int, int);

void set_maior_linha(MAN_b, int);

void show_boletim_vendas(MAN_b mn);
void set_maior_linha(MAN_b, int);

char **get_ordered_dbase_dump_products(MAN_b, size_t *n, int flag);
StatInfo search_product(MAN_b mn, char *product);
char **get_products_not_bought(MAN_b mn, size_t *n, int filial);
char **get_clients_not_buying(MAN_b mn, size_t *n);
StatInfo search_client(MAN_b mn, char *client);

#endif