/**
 * @file sale.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c SALE.
 **/

#include "sale.h"
#include "set.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Sale sale_make();
void sale_destroy(Sale);
void sale_wipe(Sale);
int sale_paralel_proc(DBase, DBase, Sale, pc, pc);
void sale_insert_self(DBase, DBase, Sale);
void sale_copy_client(Sale, char *);
int sale_exists_abs(Sale, DBase, int);
void sale_id_check(Sale, StrSet, void *, int);

char *sale_get_client(Sale);
char *sale_get_product(Sale);
int sale_get_month(Sale s);
int sale_get_filial(Sale s);
int sale_get_promo(Sale s);
int sale_get_units(Sale s);
double sale_get_price(Sale s);
double sale_get_rev(Sale);

void sale_set_client(Sale s, char *client);
void sale_set_product(Sale s, char *product);
void sale_set_month(Sale s, int month);
void sale_set_filial(Sale s, int filial);
void sale_set_promo(Sale s, int promo);
void sale_set_units(Sale s, int units);
void sale_set_price(Sale s, double price);

/* Metodos privados */
// None

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de dados que descreve um registo de venda/compra. 
 **/
typedef struct sale
{
    char *client, /**< Código do cliente */
        *product; /**< Código do produto */
    int month,    /**< Mes da venda */
        filial,   /**< Filial da venda */
        promo,    /**< Código promocional da venda */
        units;    /**< unidades vendidas */
    double price; /**< Preco de cada unidade vendida */
} * SALE;

// ------------------------------------------------------------------------------

/**
 * \brief Cria estrutura onde é armazenado um registo de venda.
 * 
 * @returns Um registo de venda utilizavél.
 **/
Sale sale_make()
{
    SALE r = g_malloc(sizeof(struct sale));
    r->client = r->product = NULL;
    r->month = r->filial = r->promo = r->units = 0;
    r->price = 0.0;
    return r;
}

/**
 * \brief Liberta todas os elementos da estrutura `SALE` alocados dinamicamente, sem destruir a propria estrutura.
 *
 * @param s Registo de venda a limpar.
 **/
void sale_wipe(Sale s)
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
void sale_destroy(Sale s)
{
    sale_wipe(s);
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
int sale_paralel_proc(DBase prd_st, DBase cl_st, SALE s, pc prdct, pc clt)
{
    return ((*prdct)(prd_st, s->product) && (*clt)(cl_st, s->client));
}

/**
 * \brief Cópia o nome de um cliente para uma string.
 * 
 * @param src Registo de venda que contem o código do cliente.
 * @param dest String onde será colocado o código do cliente.
 **/
void sale_copy_client(Sale src, char *dest)
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
void sale_insert_self(DBase products, DBase clients, Sale s)
{
    dbase_add(products, s->product, s);
    dbase_add(clients, s->client, s);
}

int sale_exists_abs(Sale s, DBase db, int flag)
{
    int r;
    if (flag)
        r = dbase_contains(db, s->client);
    else
        r = dbase_contains(db, s->product);
    return r;
}

void sale_id_check(Sale s, StrSet set, void *e, int flag)
{
    char *tmp = flag ? s->product : s->client;

    if (!strset_contains(set, tmp))
    {
        tmp = g_strdup(tmp);
    }

    strset_add(set, tmp, e);
}

/**
 * \brief Indica o cliente que efeutou a compra.
 * 
 * @param s Registo de venda.
 * 
 * @returns O cliente que efetuou a compra.
 **/
char *sale_get_client(Sale s)
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
char *sale_get_product(Sale s)
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
int sale_get_month(Sale s)
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
int sale_get_filial(Sale s)
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
int sale_get_promo(Sale s)
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
int sale_get_units(Sale s)
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
double sale_get_price(Sale s)
{
    return s->price;
}

double sale_get_rev(Sale s)
{
    return (s->price * s->units);
}

/**
 * \brief Atribui o código de cliente a um registo de venda.
 * 
 * @param s Registo de venda.
 * @param client Código do comprador.
 **/
void sale_set_client(Sale s, char *client)
{
    s->client = g_strdup(client);
}

/**
 * \brief Atribui o código de produto a um registo de venda.
 * 
 * @param s Registo de venda.
 * @param product Código do produto vendido.
 **/
void sale_set_product(Sale s, char *product)
{
    s->product = g_strdup(product);
}

/**
 * \brief Atribui o mês da venda.
 * 
 * @param s Registo de venda.
 * @param month Mês associado à venda.
 **/
void sale_set_month(Sale s, int month)
{
    s->month = month;
}

/**
 * \brief Atribui a filial na qual se deu a venda.
 * 
 * @param s Registo de venda.
 * @param filial Identificador da filial.
 **/
void sale_set_filial(Sale s, int filial)
{
    s->filial = filial;
}

/**
 * \brief Atribui o código promocional a uma dada venda.
 * 
 * @param s Registo de venda.
 * @param promo Código promocional.
 **/
void sale_set_promo(Sale s, int promo)
{
    s->promo = promo;
}

/**
 * \brief Atribui as unidades associadas a uma venda.
 * 
 * @param s Registo de venda.
 * @param units Unidades vendidas.
 **/
void sale_set_units(Sale s, int units)
{
    s->units = units;
}

/**
 * \brief Atribui o preço a que uma venda foi efetuada.
 * 
 * @param s Registo de venda.
 * @param price Preço ao qual a venda foi efetuada.
 **/
void sale_set_price(Sale s, double price)
{
    s->price = price;
}