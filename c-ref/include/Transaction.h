/**
 * @file Transaction.h
 * \brief Define a interface fornecida para interagir com a classe `Transaction`.
 * 
 * Esta classe visa armazenar toda a informação útil sobre uma transação.
 */

#ifndef __TRANS_H__
#define __TRANS_H__

#include "Client.h"

#include "Product.h"

/**
 * \brief Tipo opaco representativo de uma instância da classe `Transaction`.
 */
typedef struct transaction *Transaction;

/**
 * \brief Cria uma transação.
 * 
 * returns Transação criada.
 */
Transaction trans_make();

/**
 * \brief Destrói uma transação.
 * 
 * @param e Transação a destruir.
 */
void trans_destroy(Transaction t);

/**
 * \brief Calcula o cliente associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O cliente da transação.
 */
Client trans_get_client(Transaction t);

/**
 * \brief Calcula o produto associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O produto da transação.
 */
Product trans_get_product(Transaction t);

/**
 * \brief Calcula o mês a que se deu uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O mês da transação.
 */
unsigned char trans_get_month(Transaction t);

/**
 * \brief Calcula a filial onde se deu a transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns A filial calculada.
 */
unsigned char trans_get_filial(Transaction t);

/**
 * \brief Calcula o código promocional duma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O código promocional da transação.
 */
unsigned char trans_get_promo(Transaction t);

/**
 * \brief Calcula quantas unidades estão envolvidas na transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O número de unidades envolvidas.
 */
unsigned char trans_get_units(Transaction t);

/**
 * \brief Calcula o preço a que se deu a transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O preço realizado.
 */
double trans_get_price(Transaction t);

/**
 * \brief Calcula o cashflow obtido duma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O cashflow obtido.
 */
double trans_get_rev(Transaction t);

/**
 * \brief Atribui a uma transação um cliente;
 * 
 * @param t Transação a alterar.
 * @param c Cliente a que se pretende associar.
 */
void trans_set_client(Transaction t, Client c);

/**
 * \brief Atribui a uma transação um produto.
 * 
 * @param t Transação a alterar.
 * @param p Produto que se pretende associar.
 */
void trans_set_product(Transaction t, Product p);

/**
 * \brief Atribui a uma transação um mês.
 * 
 * @param t Transação a alterar.
 * @param month Mês a associar.
 */
void trans_set_month(Transaction t, unsigned char month);

/**
 * \brief Atribui a uma transação uma filial.
 * 
 * @param t Transação a alterar.
 * @param filial Filial a associar.
 */
void trans_set_filial(Transaction t, unsigned char filial);

/**
 * \brief Atribui a uma transação um código promocional.
 * 
 * @param t Transação a alterar.
 * @param promo Tipo de transação a associar.
 */
void trans_set_promo(Transaction t, unsigned char promo);

/**
 * \brief Atribui a uma transação as unidades envolvidas.
 * 
 * @param t Transação a alterar.
 * @param units Unidades a associar.
 */
void trans_set_units(Transaction t, unsigned char units);

/**
 * \brief Atribui a uma transação um preço.
 * 
 * @param t Transação a alterar.
 * @param price Preço a associar.
 */
void trans_set_price(Transaction t, double price);

#endif