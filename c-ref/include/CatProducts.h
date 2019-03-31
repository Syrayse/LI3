/**
 * @file CatProducts.h
 * Define a API fornecida ao utilizador desta classe. 
 */

#ifndef CAT_PRODUCTS_H
#define CAT_PRODUCTS_H

#include "util.h"

typedef struct cat_products *CatProducts;

CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
int CatProducts_exists(CatProducts cp, char *product);
void CatProducts_add_product(CatProducts cp, char *product);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);

#endif