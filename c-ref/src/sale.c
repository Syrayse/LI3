#include "sale.h"
#include <glib.h>

// Type defs
typedef struct sale {
    char *client                //Código do cliente
        ,*product;              //Código do produto
    unsigned char month                  //Mes do registo    
        ,filial                 //Filial do registo
        ,promo                  //Booleano do registo
        ,units;                  //unidades do registo
    float price;                //Preco do registo
} *SALE;

//publico
//Construtores e desconstrutores
SALE make_s (void);
void destroy_s (SALE);

//setters e getters
//getters
char* get_client_s (SALE);
char* get_product_s (SALE);
unsigned char get_month_s (SALE);
unsigned char get_filial_s (SALE);
unsigned char get_promo_s (SALE);
unsigned char get_units_s (SALE);
float get_price_s (SALE);

//setters
void set_client_s (SALE, char*);
void set_product_s (SALE, char*);
void set_month_s (SALE, unsigned char);
void set_filial_s (SALE, unsigned char);
void set_promo_s (SALE, unsigned char);
void set_units_s (SALE, unsigned char);
void set_price_s (SALE, float);

//privado
//None

// Code ------------------------------------------------------
// for the builders
SALE make_s (void)
{
    SALE r = g_malloc(sizeof(struct sale));
    r->client = r->product = NULL;
    r->month = r->filial = r->promo = r->units = 0;
    r->price = -1;
    return r;
}

void destroy_s (SALE s)
{
    if(s) {
        g_free(s->product);
        g_free(s->client);
    }
    g_free(s);
}

// for the setters and getters
//getters
char* get_client_s (SALE s)
{
    return g_strdup(s->client);
}

char* get_product_s (SALE s)
{
    return g_strdup(s->product);
}

unsigned char get_month_s (SALE s)
{
    return s->month;
}

unsigned char get_filial_s (SALE s)
{
    return s->filial;
}

unsigned char get_promo_s (SALE s)
{
    return s->promo;
}

unsigned char get_units_s (SALE s)
{   
    return s->units;
}

float get_price_s (SALE s)
{
    return s->price;
}

//setters
void set_client_s (SALE s, char* client)
{
    s->client = g_strdup(client);
}

void set_product_s (SALE s, char* product)
{
    s->product = g_strdup(product);
}

void set_month_s (SALE s, unsigned char month)
{
    s->month = month;
}

void set_filial_s (SALE s, unsigned char filial)
{
    s->filial = filial;
}

void set_promo_s (SALE s, unsigned char promo)
{
    s->promo = promo;
}

void set_units_s (SALE s, unsigned char units)
{
    s->units = units;
}

void set_price_s (SALE s, float price)
{
    s->price = price;
}