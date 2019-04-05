#ifndef _ADITION_
#define _ADITION_

#include "TAD_List.h"
#include <glib.h>

typedef struct adition *Adition;

gpointer adition_make();
void adition_destroy(gpointer e);
void adition_update(gpointer e, gpointer user_data);
TAD_List adition_dump_by_promo_fil(Adition ad, int filial, int promo);
int adition_size(Adition ad);

#endif