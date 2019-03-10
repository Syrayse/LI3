#ifndef APPENDER_H
#define APPENDER_H

// Information append to keys.
typedef struct appendix *APPENDER;

APPENDER make_appender();
void update_appender(APPENDER, void *);
int is_sold_by_all(APPENDER);
int get_t_vendas(APPENDER);
int get_t_fil_vendas(APPENDER, int filial);
int get_t_fil_vendas_promo(APPENDER, int filial);
int get_t_fil_vendas_no_promo(APPENDER, int filial);
int get_t_month_fil_vendas(APPENDER, int month, int filial);
int get_t_month_fil_vendas_promo(APPENDER, int month, int filial);
int get_t_month_fil_vendas_no_promo(APPENDER, int month, int filial);
int get_t_month_vendas(APPENDER, int month);
int get_t_month_vendas_promo(APPENDER, int month);
int get_t_month_vendas_no_promo(APPENDER, int month);
float get_t_rev(APPENDER);
float get_t_fil_rev(APPENDER, int filial);
float get_t_fil_rev_promo(APPENDER, int filial);
float get_t_fil_rev_no_promo(APPENDER, int filial);
float get_t_month_fil_rev(APPENDER, int month, int filial);
float get_t_month_fil_rev_promo(APPENDER, int month, int filial);
float get_t_month_fil_rev_no_promo(APPENDER, int month, int filial);
float get_t_month_rev(APPENDER, int month);
float get_t_month_rev_promo(APPENDER, int month);
float get_t_month_rev_no_promo(APPENDER, int month);
void destroy_appender(void *);

#endif