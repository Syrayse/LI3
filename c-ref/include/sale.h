#ifndef SALE_H
#define SALE_H

typedef struct sale *SALE;

//Construtores e desconstrutores
SALE make_s(void);
void destroy_s(SALE);

//setters e getters
//getters
char *get_client_s(SALE s);
char *get_product_s(SALE s);
unsigned char get_month_s(SALE s);
unsigned char get_filial_s(SALE s);
unsigned char get_promo_s(SALE s);
unsigned char get_units_s(SALE s);
float get_price_s(SALE s);

//setters
void set_client_s(SALE s, char *client);
void set_product_s(SALE s, char *product);
void set_month_s(SALE s, unsigned char month);
void set_filial_s(SALE s, unsigned char filial);
void set_promo_s(SALE s, unsigned char promo);
void set_units_s(SALE s, unsigned char units);
void set_price_s(SALE s, float price);

#endif