/**
 * @file statinfo.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `StatInfo`.
 */

#ifndef STATINFO_H
#define STATINFO_H

typedef struct statistical_info *StatInfo;

StatInfo statinfo_make();
void statinfo_destroy(StatInfo si);
void statinfo_update(StatInfo si, void *user_data);

int get_t_units(StatInfo si);
int get_t_units_fil(StatInfo si, int filial);

int get_n_actors(StatInfo);
int get_t_vendas(StatInfo);
int get_t_month_fil_vendas(StatInfo, int month, int filial);
int get_t_month_fil_vendas_promo(StatInfo, int month, int filial);
int get_t_month_fil_vendas_no_promo(StatInfo, int month, int filial);
int get_t_month_vendas(StatInfo, int month);
int get_t_month_vendas_promo(StatInfo, int month);
int get_t_month_vendas_no_promo(StatInfo, int month);

double get_t_rev(StatInfo);
double get_t_month_fil_rev(StatInfo, int month, int filial);
double get_t_month_fil_rev_promo(StatInfo, int month, int filial);
double get_t_month_fil_rev_no_promo(StatInfo, int month, int filial);
double get_t_month_rev(StatInfo, int month);
double get_t_month_rev_promo(StatInfo, int month);
double get_t_month_rev_no_promo(StatInfo, int month);

#endif