#ifndef CAT_PRODUCTS_H
#define CAT_PRODUCTS_H

#include "util.h"

typedef struct cat_products *CatProducts;

CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, char *product);
void CatProducts_add_product(CatProducts cp, char *product);
void CatProducts_add_trans(CatProducts cp, char *product, int filial, gID trans_id);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);
gID *CatProducts_drop_trans(CatProducts cp, char *product, int filial, int *s);
int CatProducts_t_not_sold(CatProducts cp);
char **catProducts_t_all_not_sold(CatProducts cp, int *s);
char **catProducts_t_not_sold_filial(CatProducts cp, int *s, int filial);

#endif