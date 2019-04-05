/**
 * @file Accounting.h
 * \brief Interface de metódos públicos que permitem a interação com instâncias da classe `Accounting`.
 * 
 * Esta classe tem como objetivo tratar das contas do serviço SVG.
 */

#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "Product.h"

/**
 * \brief Tipo opaco representativo de uma instância da classe `Accounting`.
 */
typedef struct accounting *Accounting;

/**
 * \brief Permite criar uma instància da classe `Accounting`.
 * 
 * @returns Uma nova instância.
 */
Accounting Accounting_make();

/**
 * \brief Liberta a memória associada a uma instância da classe `Accounting`.
 * 
 * @param a Instância a considerar.
 */
void Accounting_destroy(Accounting a);

/**
 * \brief Metódo que permite atualizar a informação interna da instância `Accounting`.
 * 
 * Nesta função são passados todos os valores necessários por pelo `Accounting`
 * de forma a conseguir atualizar os seus dados internos com o máximo de informação util.
 */
void Accounting_update(Accounting a, Product product, int month, int filial, int units, int promo, double spent);

/**
 * \brief Calcula o número de transações efetuadas entre dois meses.
 * 
 * @param a Instância a considerar.
 * @param init Primeiro mês.
 * @param end Segundo mês, deve ser mais ou igual ao primeiro.
 * 
 * @returns O valor calculado.
 */
int Accounting_n_trans_range(Accounting a, int init, int end);

/**
 * \brief Calcula o total gasto entre dois meses.
 * 
 * @param a Instância a considerar.
 * @param init Primeiro mês.
 * @param end Segundo mês, deve ser mais ou igual ao primeiro.
 * 
 * @returns O valor calculado.
 */
double Accounting_n_cash_range(Accounting a, int init, int end);

/**
 * \brief Calcula o valor global de transações e cashflow com e sem promoção naquele produto.
 * 
 * Todos os valores calculados são colocados nos endereçoes passados como argumento
 * Logo, cada endereço deve possuir a capacidade para valores do seu respetivo tipo.
 * Por exemplo, o `trans_vec` deve ser capaz de armazenar 2 valores inteiros, de modo
 * a contemplar o caso sem promoção e com promoção.
 * 
 * @param a Instância a considerar.
 * @param product Produto do qual se pretende obter informação.
 * @param month Mês ao qual a informação é referente.
 * @param trans_vec Array onde serão armazenados os valores necessários, associados a inteiros.
 * @param spent_vec Array onde serão armazenados os valores necessários, associados a doubles.
 * 
 * @returns 1 caso o produto exista em `Accounting`, 0 caso contrário.
 */
int Accounting_get_global_stats(Accounting a, Product product, int month, int *trans_vec, int *spent_vec);

/**
 * \brief Calcula o valor global de transações e cashflow com e sem promoção por filial naquele produto.
 * 
 * Todos os valores calculados são colocados nos endereçoes passados como argumento
 * Logo, cada endereço deve possuir a capacidade para valores do seu respetivo tipo.
 * Por exemplo, o `trans_vec` deve ser capaz de armazenar `N_FILIAIS`*2 valores inteiros, de modo
 * a contemplar o caso sem promoção e com promoção para todas as filiais.
 * 
 * @param a Instância a considerar.
 * @param product Produto do qual se pretende obter informação.
 * @param month Mês ao qual a informação é referente.
 * @param trans_vec Matriz onde serão armazenados os valores necessários, associados a inteiros.
 * @param spent_vec Matriz onde serão armazenados os valores necessários, associados a doubles.
 * 
 * @returns 1 caso o produto exista em `Accounting`, 0 caso contrário.
 */
int Accounting_get_per_filial_stats(Accounting a, Product product, int month, int **trans_vec, int **spent_vec);

#endif