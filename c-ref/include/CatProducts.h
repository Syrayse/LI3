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
int CatProducts_exists(CatProducts cp, Product product);
void CatProducts_add_product(CatProducts cp, Product product);
void CatProduct_report_trans(CatProducts cp, char *product, int filial);
char **CatProducts_dump_ordered(CatProducts cp, int *s, char let);
int CatProducts_get_total_not_bought(CatProducts cp);
char **CatProducts_not_bought(CatProducts cp, int *size);
char **CatProducts_not_bought_fil(CatProducts cp, int filial, int *size);
Product Product_make(char *product_code);
void Product_destroy(void *p);

#endif