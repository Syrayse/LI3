/**
 * @file Accounting.h
 * \brief Interface de métodos públicos que permitem a interação com instâncias da classe `Accounting`.
 * 
 * Esta classe tem como objetivo tratar das contas do serviço SVG.
 */

#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "Product.h"

#include "TAD_List.h"

/**
 * \brief Tipo opaco representativo de uma instância da classe `Accounting`.
 */
typedef struct accounting *Accounting;

/**
 * \brief Permite criar uma instância da classe `Accounting`.
 * 
 * @returns Uma nova instância.
 */
Accounting Accounting_make();

/**
 * \brief Liberta a memória associada a uma instância da classe `Accounting`.
 * 
 * @param a instância a considerar.
 */
void Accounting_destroy(Accounting a);

/**
 * \brief Método que permite atualizar a informação interna da instância `Accounting`.
 * 
 * Nesta função são passados todos os valores necessários pelo `Accounting`
 * de forma a conseguir atualizar os seus dados internos com o máximo de informação útil.
 */
void Accounting_update(Accounting a, Product product, int month, int filial, int units, int promo, double spent);

/**
 * \brief Calcula o número de transações efetuadas entre dois meses.
 * 
 * @param a Instância a considerar.
 * @param init Primeiro mês.
 * @param end Segundo mês, deve ser maior ou igual ao primeiro.
 * 
 * @returns O valor calculado, -1 caso init > end.
 */
int Accounting_n_trans_range(Accounting a, int init, int end);

/**
 * \brief Calcula o total gasto entre dois meses.
 * 
 * @param a Instância a considerar.
 * @param init Primeiro mês.
 * @param end Segundo mês, deve ser maior ou igual ao primeiro.
 * 
 * @returns O valor calculado, -1.0 caso init > end.
 */
double Accounting_n_cash_range(Accounting a, int init, int end);

/**
 * \brief Calcula o valor global de transações e cashflow com e sem promoção naquele produto.
 * 
 * Todos os valores calculados são colocados nos endereços passados como argumento.
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
int Accounting_get_global_stats(Accounting a, Product product, int month, int *trans_vec, double *spent_vec);

/**
 * \brief Calcula o valor global de transações e cashflow com e sem promoção por filial naquele produto.
 * 
 * Todos os valores calculados são colocados nos endereços passados como argumento.
 * Logo, cada endereço deve possuir a capacidade para valores do seu respetivo tipo.
 * Por exemplo, o `trans_vec` deve ser capaz de armazenar `N_FILIAIS`*2 valores inteiros, de modo
 * a contemplar o caso sem promoção e com promoção, para todas as filiais.
 * 
 * @param a Instância a considerar.
 * @param product Produto do qual se pretende obter informação.
 * @param month Mês ao qual a informação é referente.
 * @param trans_vec Matriz onde serão armazenados os valores necessários, associados a inteiros.
 * @param spent_vec Matriz onde serão armazenados os valores necessários, associados a doubles.
 * 
 * @returns 1 caso o produto exista em `Accounting`, 0 caso contrário.
 */
int Accounting_get_per_filial_stats(Accounting a, Product product, int month, int **trans_vec, double **spent_vec);

/**
 * \brief Cria uma lista com o top N produtos mais vendidos, por ordem descendente.
 * 
 * @param a Instância a considerar.
 * @param N Precisão que se pretende.
 * 
 * @returns Uma lista com o top N produtos mais vendidos, por ordem descendente.
 */
TAD_List Accounting_get_top_N_most_bought(Accounting a, int N);

/**
 * \brief Dado um produto, preenche um vetor com as unidades vendidas daqueles produto por filial.
 * 
 * @param a Instância a considerar.
 * @param p Produto que se pretende verificar.
 * @param fil_vector Array onde serão armazenados os valores de unidades vendidas.
 */
void Accounting_get_fil_vec_units(Accounting a, Product p, int *fil_vector);

#endif