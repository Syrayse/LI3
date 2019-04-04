#ifndef _ADITION_
#define _ADITION_

typedef struct adition *Adition;

void *adition_make();
void adition_destroy(void *e);
void adition_update(void *e, void *user_data);
char **adition_dump_by_promo_fil(Adition ad, int filial, int promo, int *size);
int adition_size(Adition ad);

#endif