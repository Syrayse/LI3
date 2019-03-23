#ifndef _ADITION_
#define _ADITION_

#include "util.h"

typedef struct adition *Adition;

void *adition_make();
void adition_destroy(void *v);
void adition_add(void *v, void *user_data);
int adition_is_empty(void *v);
gID *adition_dump(void *v, int filial, int *s);
int adition_rec_size(Adition a, int filial);

#endif