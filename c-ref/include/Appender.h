#ifndef _APPENDER_
#define _APPENDER_

#include "Client.h"
#include "Product.h"
#include "TAD_List.h"
#include <glib.h>

typedef struct appender *Appender;

gpointer appender_make();
void appender_destroy(gpointer v);
void appender_update(gpointer e, gpointer user_data);
int appender_get_quantity(Appender ap, int filial, int month);
int appender_get_num_product(Appender ap);
double appender_get_prod_spent(Appender ap, Product product);
int appender_get_prod_quant_month(Appender ap, Product product, int month);
int appender_get_quantity_fil(Appender ap, int filial);
int **appender_clone_matrix(Appender ap);
TAD_List appender_get_most_bought(Appender ap, int month);
TAD_List appender_get_top3(Appender ap);
int is_bought_in_all(Appender ap);

#endif
