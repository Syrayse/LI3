/**
 * @file CatProducts.h
 * \brief Define a API fornecida ao utilizador desta classe. 
 */

#ifndef CAT_PRODUCTS_H
#define CAT_PRODUCTS_H

typedef struct cat_products *CatProducts;

typedef struct product *Product;

CatProducts CatProducts_make();
void CatProducts_destroy(CatProducts cp);
void CatProducts_add_product(CatProducts cp, Product product);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);
Product Product_make(char *product_code);
void Product_destroy(void *p);

#endif