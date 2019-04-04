#ifndef _APPENDER_
#define _APPENDER_

typedef struct appender *Appender;

void *appender_make();
void appender_destroy(void *e);
void appender_update(void *e, void *user_data);
int appender_get_quantity(Appender ap, int filial, int month);
int appender_get_num_product(Appender ap);
double appender_get_prod_spent(Appender ap, char *product);
int appender_get_prod_quant_month(Appender ap, char *product, int month);
int appender_get_quantity_fil(Appender ap, int filial);
int **appender_clone_matrix(Appender ap);
char **appender_get_most_bought(Appender ap, int month, int *size);
char **appender_get_top3(Appender ap, int *size);
int is_bought_in_all(Appender ap);

#endif
