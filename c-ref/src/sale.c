/**
 * @file sale.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c SALE.
 **/

#include "sale.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
SALE make_s(void);
void destroy_s(SALE);
void clean_s(SALE);
int validate_s(DBase, DBase, SALE);
int process_paralelo_s(DBase, DBase, SALE, pc, pc);

/* Getters */
void copy_client_s(SALE, char *);
char *get_client_s(SALE);
char *get_product_s(SALE);
unsigned char get_month_s(SALE);
unsigned char get_filial_s(SALE);
unsigned char get_promo_s(SALE);
unsigned char get_units_s(SALE);
float get_price_s(SALE);

/* Setters */
void set_client_s(SALE, char *);
void set_product_s(SALE, char *);
void set_month_s(SALE, unsigned char);
void set_filial_s(SALE, unsigned char);
void set_promo_s(SALE, unsigned char);
void set_units_s(SALE, unsigned char);
void set_price_s(SALE, float);

/* Metodos privados */
// None

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de dados que descreve um registo de venda/compra. 
 **/
typedef struct sale
{
    char *client /**< Código do cliente */
        ,
        *product;       /**< Código do produto */
    unsigned char month /**< Mes da venda */
        ,
        filial /**< Filial da venda */
        ,
        promo /**< Código promocional da venda */
        ,
        units;   /**< unidades vendidas */
    float price; /**< Preco de cada unidade vendida */
} * SALE;

// ------------------------------------------------------------------------------

/**
 * \brief Cria estrutura onde é armazenado um registo de venda.
 * 
 * @returns Um registo de venda utilizavél.
 **/
SALE make_s(void)
{
    SALE r = g_malloc(sizeof(struct sale));
    r->client = r->product = NULL;
    r->month = r->filial = r->promo = r->units = 0;
    r->price = -1;
    return r;
}

/**
 * \brief Liberta todas os elementos da estrutura `SALE` alocados dinamicamente, sem destruir a propria estrutura.
 *
 * @param s Registo de venda a limpar.
 **/
void clean_s(SALE s)
{
    if (s)
    {
        g_free(s->product);
        g_free(s->client);
        s->product = s->client = NULL;
    }
}

/**
 * \brief Destrói estrutura de dados que armazena um registo de venda.
 * 
 * @param s Registo de venda a libertar da memória.
 **/
void destroy_s(SALE s)
{
    clean_s(s);
    g_free(s);
}

/**
 * \brief Função que efetua um processamento duplo de duas funções associadas associado a `DBase`.
 * 
 * @param prd_st Base de dados dos produtos.
 * @param cl_st Base de dados dos clientes.
 * @param s Registo de vendas usado no processamento.
 * @param prdct Função que processa o registo de venda na base de dados dos produtos.
 * @param clt Função que processa o registo de venda na base de dados dos clientes.
 * 
 * @returns O resultado do operador lógico `&&` aplicado às funções processadas.
 * 
 * @see DBase
 * @see validate_s 
 **/
int process_paralelo_s(DBase prd_st, DBase cl_st, SALE s, pc prdct, pc clt)
{
    return ((*prdct)(prd_st, s->product) && (*clt)(cl_st, s->client));
}

/**
 * \brief Cópia o nome de um cliente para uma string.
 * 
 * @param src Registo de venda que contem o código do cliente.
 * @param dest String onde será colocado o código do cliente.
 **/
void copy_client_s(SALE src, char *dest)
{
    strcpy(dest, src->client);
}

/**
 * \brief Processa a introdução de um registo de venda nas bases de dados necessárias.
 * 
 * @param products Base de dados associada aos produtos.
 * @param clients Base de dados associada aos clientes.
 * @param s Registo que se pretende colocar na base de dados. 
 **/
void insert_self_s(DBase products, DBase clients, SALE s)
{
    insert_dbase(products, s->product, s);
    insert_dbase(clients, s->client, s);
}

/**
 * \brief Indica o cliente que efeutou a compra.
 * 
 * @param s Registo de venda.
 * 
 * @returns O cliente que efetuou a compra.
 **/
char *get_client_s(SALE s)
{
    return g_strdup(s->client);
}

/**
 * \brief Indica o código de produto associado a uma venda.
 * 
 * @param s Registo de venda.
 * 
 * @returns O código do produto.
 **/
char *get_product_s(SALE s)
{
    return g_strdup(s->product);
}

/**
 * \brief Indica o mês em que se deu a venda.
 * 
 * @param s Registo de venda.
 * 
 * @returns O mẽs da venda.
 **/
unsigned char get_month_s(SALE s)
{
    return s->month;
}

/**
 * \brief Indica a filial onde se deu a venda.
 * 
 * @param s Registo de venda.
 * 
 * @returns Filial onde ocorreu a venda.
 **/
unsigned char get_filial_s(SALE s)
{
    return s->filial;
}

/**
 * \brief Indica o código promocional de uma venda.
 * 
 * @param s Registo de venda.
 * 
 * @returns O código promocional de uma venda.
 **/
unsigned char get_promo_s(SALE s)
{
    return s->promo;
}

/**
 * \brief Indica o número de unidades vendidas.
 * 
 * @param s Registo de venda.
 * 
 * @returns O número de unidades vendidas.
 **/
unsigned char get_units_s(SALE s)
{
    return s->units;
}

/**
 * \brief Indica o preço a que uma venda se efetuou.
 * 
 * @param s Registo de venda.
 * 
 * @returns O preço da venda.
 **/
float get_price_s(SALE s)
{
    return s->price;
}

/**
 * \brief Atribui o código de cliente a um registo de venda.
 * 
 * @param s Registo de venda.
 * @param client Código do comprador.
 **/
void set_client_s(SALE s, char *client)
{
    s->client = g_strdup(client);
}

/**
 * \brief Atribui o código de produto a um registo de venda.
 * 
 * @param s Registo de venda.
 * @param product Código do produto vendido.
 **/
void set_product_s(SALE s, char *product)
{
    s->product = g_strdup(product);
}

/**
 * \brief Atribui o mês da venda.
 * 
 * @param s Registo de venda.
 * @param month Mês associado à venda.
 **/
void set_month_s(SALE s, unsigned char month)
{
    s->month = month;
}

/**
 * \brief Atribui a filial na qual se deu a venda.
 * 
 * @param s Registo de venda.
 * @param filial Identificador da filial.
 **/
void set_filial_s(SALE s, unsigned char filial)
{
    s->filial = filial;
}

/**
 * \brief Atribui o código promocional a uma dada venda.
 * 
 * @param s Registo de venda.
 * @param promo Código promocional.
 **/
void set_promo_s(SALE s, unsigned char promo)
{
    s->promo = promo;
}

/**
 * \brief Atribui as unidades associadas a uma venda.
 * 
 * @param s Registo de venda.
 * @param units Unidades vendidas.
 **/
void set_units_s(SALE s, unsigned char units)
{
    s->units = units;
}

/**
 * \brief Atribui o preço a que uma venda foi efetuada.
 * 
 * @param s Registo de venda.
 * @param price Preço ao qual a venda foi efetuada.
 **/
void set_price_s(SALE s, float price)
{
    s->price = price;
}