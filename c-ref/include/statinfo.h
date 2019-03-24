#ifndef STATINFO_H
#define STATINFO_H

#include "transaction.h"

typedef struct statistical_info *StatInfo;
typedef struct vendas_Prod *Vendas;

StatInfo statinfo_make();
void statinfo_destroy(StatInfo);
void statinfo_builder(Transaction t, void *e);
Vendas vendas_make();
void vendas_destroy(Vendas);
void vendas_builder(Transaction t, void *e);

char* get_t_product(Vendas);
int get_t_nVendas(Vendas);
int get_t_nUnits(Vendas);
int get_n_actors(StatInfo);
int get_t_vendas(StatInfo);
int get_t_fil_vendas(StatInfo, int filial);
int get_t_fil_vendas_promo(StatInfo, int filial);
int get_t_fil_vendas_no_promo(StatInfo, int filial);
int get_t_month_fil_vendas(StatInfo, int month, int filial);
int get_t_month_fil_vendas_promo(StatInfo, int month, int filial);
int get_t_month_fil_vendas_no_promo(StatInfo, int month, int filial);
int get_t_month_vendas(StatInfo, int month);
int get_t_month_vendas_promo(StatInfo, int month);
int get_t_month_vendas_no_promo(StatInfo, int month);

double get_t_rev(StatInfo);
double get_t_fil_rev(StatInfo, int filial);
double get_t_fil_rev_promo(StatInfo, int filial);
double get_t_fil_rev_no_promo(StatInfo, int filial);
double get_t_month_fil_rev(StatInfo, int month, int filial);
double get_t_month_fil_rev_promo(StatInfo, int month, int filial);
double get_t_month_fil_rev_no_promo(StatInfo, int month, int filial);
double get_t_month_rev(StatInfo, int month);
double get_t_month_rev_promo(StatInfo, int month);
double get_t_month_rev_no_promo(StatInfo, int month);

#endif