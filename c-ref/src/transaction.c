/**
@file transaction.c
\brief Módulo encarregue da estrutura de transação.
*/

#include "transaction.h"
#include <string.h>
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Transaction trans_make();
void trans_destroy(void *e);

void trans_copy_product(Transaction src, char *dest);
void trans_copy_client(Transaction src, char *dest);
int trans_exists_efect(Transaction src, CatProducts cp, CatClients cc);

char *trans_get_client(Transaction t);
char *trans_get_product(Transaction t);
UChar trans_get_month(Transaction t);
UChar trans_get_filial(Transaction t);
UChar trans_get_promo(Transaction t);
UChar trans_get_units(Transaction t);
gID trans_get_id(Transaction t);
double trans_get_price(Transaction t);
double trans_get_rev(Transaction t);

void trans_set_client(Transaction t, char *client);
void trans_set_product(Transaction t, char *product);
void trans_set_month(Transaction t, UChar month);
void trans_set_filial(Transaction t, UChar filial);
void trans_set_promo(Transaction t, UChar promo);
void trans_set_units(Transaction t, UChar units);
void trans_set_id(Transaction t, gID id);
void trans_set_price(Transaction t, double price);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura que armazena toda a informação necessária para um registo de transação.
 */
typedef struct transaction
{
    char client[CLT_LEN + 1],  /**< Cliente associado à transação. */
        product[PROD_LEN + 1]; /**< Produto associado à transação. */
    UChar month,               /**< Mês da transação. */
        filial,                /**< Filial onde se deu a transação. */
        promo,                 /**< Código promocional associado à transação.  */
        units;                 /**< Unidades envolvidas na transação. */
    gID id;                    /**< ID da transação. */
    double price;              /**< Preço do produto da transação. */
} * Transaction;

// ------------------------------------------------------------------------------

/**
 * \brief Cria uma transação.
 * 
 * returns Transação criada.
 */
Transaction trans_make()
{
    Transaction t = g_malloc(sizeof(struct transaction));
    t->month = t->filial = t->promo = t->units = 0;
    t->id = 0;
    t->price = 0.0;
    return t;
}

/**
 * \brief Destrói uma transação.
 * 
 * @param e Transação a destruir.
 */
void trans_destroy(void *e)
{
    Transaction t;

    if (e)
    {
        t = (Transaction)e;
        g_free(t);
    }
}

/**
 * \brief Cópia o código de produto para um dado endereço.
 * 
 * @param src Transação a ser utilizada.
 * @param dest Endereço onde irá ser colocada uma cópia do código do produto.
 */
void trans_copy_product(Transaction src, char *dest)
{
    strcpy(dest, src->product);
}

/**
 * \brief Cópia o código de cliente para um dado endereço.
 * 
 * @param src Transação a ser utilizada.
 * @param dest Endereço onde irá ser colocada uma cópia do código do cliente.
 */
void trans_copy_client(Transaction src, char *dest)
{
    strcpy(dest, src->client);
}

/**
 * \brief Verifica se uma venda é efetivamente válida.
 * 
 * Uma transação considera-se efetivamente válida se existir no catálogo de produtos
 * e catálogo de clientes utilizados.
 * 
 * @param src Transação que se pretende verificar.
 * @param cp Catálogo de produtos utilizado.
 * @param cc Catálogo de clientes utilizado.
 * 
 * @returns 1 se a transação for efetivamente válida, 0 caso contrário.
 * 
 * @see CatProducts_exists
 * @see CatClients_exists
 */
int trans_exists_efect(Transaction src, CatProducts cp, CatClients cc)
{
    return (CatProducts_exists(cp, src->product) && CatClients_exists(cc, src->client));
}

/**
 * \brief Calcula o cliente associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O cliente da transação.
 */
char *trans_get_client(Transaction t)
{
    return g_strdup(t->client);
}

/**
 * \brief Calcula o produto associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O produto da transação.
 */
char *trans_get_product(Transaction t)
{
    return g_strdup(t->product);
}

/**
 * \brief Calcula o mês a que se deu uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O mês da transação.
 */
UChar trans_get_month(Transaction t)
{
    return t->month;
}

/**
 * \brief Calcula a filial onde se deu a transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns A filial calculada.
 */
UChar trans_get_filial(Transaction t)
{
    return t->filial;
}

/**
 * \brief Calcula o código promocional duma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O código promocional da transação.
 */
UChar trans_get_promo(Transaction t)
{
    return t->promo;
}

/**
 * \brief Calcula quantas unidades estão envolvidas na transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O número de unidades envolvidas.
 */
UChar trans_get_units(Transaction t)
{
    return t->units;
}

/**
 * \brief Calcula o ID associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O ID da transação.
 */
gID trans_get_id(Transaction t)
{
    return t->id;
}

/**
 * \brief Calcula o preço a que se deu a transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O preço realizado.
 */
double trans_get_price(Transaction t)
{
    return t->price;
}

/**
 * \brief Calcula o cashflow obtido duma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O cashflow obtido.
 */
double trans_get_rev(Transaction t)
{
    return (t->units * t->price);
}

/**
 * \brief Atribui à transação o cliente envolvido.
 * 
 * @param t Transação a alterar.
 * @param client Cliente envolvido.
 */
void trans_set_client(Transaction t, char *client)
{
    strcpy(t->client, client);
}

/**
 * \brief Atribui à transação o produto envolvido.
 * 
 * @param t Transação a alterar.
 * @param product Produto envolvido.
 */
void trans_set_product(Transaction t, char *product)
{
    strcpy(t->product, product);
}

/**
 * \brief Atribui à transação o mês em que foi realizada.
 * 
 * @param t Transação a alterar.
 * @param month Mês onde foi realizada a transação.
 */
void trans_set_month(Transaction t, UChar month)
{
    t->month = month;
}

/**
 * \brief Atribui à transação a filial onde se deu.
 * 
 * @param t Transação a alterar.
 * @param filial Filial onde se deu a transação.
 */
void trans_set_filial(Transaction t, UChar filial)
{
    t->filial = filial;
}

/**
 * \brief Atribui à transação o código promocional utilizado.
 * 
 * @param t Transação a alterar.
 * @param promo Código promocional utilizado.
 */
void trans_set_promo(Transaction t, UChar promo)
{
    t->promo = promo;
}

/**
 * \brief Atribui à transação o número de unidades envolvidas.
 * 
 * @param t Transação a alterar.
 * @param units Unidades a atribuir.
 */
void trans_set_units(Transaction t, UChar units)
{
    t->units = units;
}

/**
 * \brief Atribui à transação o ID que lhe é correspondente.
 * 
 * @param t Transação a alterar.
 * @param id ID a atribuir.
 */
void trans_set_id(Transaction t, gID id)
{
    t->id = id;
}

/**
 * \brief Atribui à transação o preço a que foi realizada.
 * 
 * @param t Transação a alterar.
 * @param price Preço a atribuir.
 */
void trans_set_price(Transaction t, double price)
{
    t->price = price;
}