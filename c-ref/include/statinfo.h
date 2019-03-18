#ifndef STATINFO_H
#define STATINFO_H

// Information append to keys.
typedef struct statistical_info *StatInfo;

StatInfo statinfo_make(int flag);
void statinfo_destroy(StatInfo);
void statinfo_update(StatInfo, void *);
int statinfo_is_sold_by_all(StatInfo);

char **get_top_N_actors(StatInfo si, size_t *hold, size_t N);

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

int get_t_units(StatInfo);
int get_t_fil_units(StatInfo, int filial);
int get_t_fil_units_promo(StatInfo, int filial);
int get_t_fil_units_no_promo(StatInfo, int filial);
int get_t_month_fil_units(StatInfo, int month, int filial);
int get_t_month_fil_units_promo(StatInfo, int month, int filial);
int get_t_month_fil_units_no_promo(StatInfo, int month, int filial);
int get_t_month_units(StatInfo, int month);
int get_t_month_units_promo(StatInfo, int month);
int get_t_month_units_no_promo(StatInfo, int month);

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