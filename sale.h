#ifndef SALE_H
#define SALE_H

typedef struct sale * SALE;

//Construtores e desconstrutores
SALE make_s (void);
void destroy_s (SALE);

//setters e getters
//getters
char* get_client_s (SALE s);
char* get_product_s (SALE s);
unsigned char get_month_s (SALE s);
unsigned char get_filial_s (SALE s);
unsigned char get_promo_s (SALE s);
unsigned char get_units_s (SALE s);
float get_price_s (SALE s);

//setters
SALE set_client_s (SALE s, char* client);
SALE set_product_s (SALE s, char* product);
SALE set_month_s (SALE s, unsigned char month);
SALE set_filial_s (SALE s, unsigned char filial);
SALE set_promo_s (SALE s, unsigned char promo);
SALE set_units_s (SALE s, unsigned char units);
SALE set_price_s (SALE s, float price);

#endif