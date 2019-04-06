/**
 * @file Queries.h
 * \brief Módulo responsável pela resposta das queries necessárias ao SGV.
 */

#ifndef __QUERIES_H__
#define __QUERIES_H__

#include "CatProducts.h"

#include "CatClients.h"

#include "Accounting.h"

#include "FilManager.h"

#include "TAD_List.h"

/**
 * \brief Cria uma lista com todos os produtos que comecem por uma dada letra, por ordem alfabética.
 * 
 * Esta função tem como objetivo resolver a QUERY nº2 do SGV.
 * 
 * @param cp Catálogo de produtos de onde se obtém a informação.
 * @param let Primeira letra pretendida.
 * 
 * @returns Uma lista com todos os produtos que comecem por uma dada letra, por ordem alfabética, ou NULL caso a letra seja inválida.
 */
TAD_List get_sorted_products(CatProducts cp, char let);

/**
 * \brief Calcula o valor global de transações e cashflow com e sem promoção naquele produto.
 * 
 * Juntamente com a função `get_product_per_filial_stats` permite resolver a QUERY nº3 do SGV.
 * 
 * Todos os valores calculados são colocados nos endereços passados como argumento.
 * Logo, cada endereço deve possuir a capacidade para valores do seu respetivo tipo.
 * Por exemplo, o `trans_vec` deve ser capaz de armazenar 2 valores inteiros, de modo
 * a contemplar o caso sem promoção e com promoção.
 * 
 * @param a Instância a considerar.
 * @param product_code Código do produto do qual se pretende obter informação.
 * @param month Mês ao qual a informação é referente.
 * @param trans_vec Array onde serão armazenados os valores necessários, associados a inteiros.
 * @param spent_vec Array onde serão armazenados os valores necessários, associados a doubles.
 * 
 * @returns 1 caso o produto exista em `Accounting`, 0 caso contrário.
 */
int get_product_global_stats(Accounting a, char *product_code, int month, int *trans_vec, int *spent_vec);

/**
 * \brief Calcula o valor global de transações e cashflow com e sem promoção por filial naquele produto.
 * 
 * Juntamente com a função `get_product_global_stats` permite resolver a QUERY nº3 do SGV.
 * 
 * Todos os valores calculados são colocados nos endereços passados como argumento.
 * Logo, cada endereço deve possuir a capacidade para valores do seu respetivo tipo.
 * Por exemplo, o `trans_vec` deve ser capaz de armazenar `N_FILIAIS`*2 valores inteiros, de modo
 * a contemplar o caso sem promoção e com promoção para todas as filiais.
 * 
 * @param a Instância a considerar.
 * @param product_code Código do produto do qual se pretende obter informação.
 * @param month Mês ao qual a informação é referente.
 * @param trans_vec Matriz onde serão armazenados os valores necessários, associados a inteiros.
 * @param spent_vec Matriz onde serão armazenados os valores necessários, associados a doubles.
 * 
 * @returns 1 caso o produto exista em `Accounting`, 0 caso contrário.
 */
int get_product_per_filial_stats(Accounting a, char *product_code, int month, int **trans_vec, int **spent_vec);

/**
 * \brief Cria uma lista com todos os produtos que não foram comprados, no total ou por filial.
 * 
 * Esta função tem como objetivo resolver a QUERY nº4 do SGV.
 * 
 * Se for passado 0 como `filial` então a função retornar os valores gerais, caso contrário só os valores da respetiva
 * filial
 * 
 * @param cp Catálogo de produtos de onde se obtém a informação.
 * @param filial Filial que se pretende considerar.
 * 
 * @returns Uma lista com todos os produtos que não foram comprados, no total ou por filial.
 */
TAD_List get_not_bought_products(CatProducts cp, int filial);

/**
 * \brief Cria uma lista com os códigos dos clientes que efetuaram compras em todas as filiais.
 * 
 * Esta função tem como objetivo resolver a QUERY nº5 do SGV.
 * 
 * @param fm Gestor de filiais utilizado.
 * 
 * @returns Uma lista com todos os produtos que comecem por uma dada letra, por ordem alfabética.
 */
TAD_List get_overall_clients(FilManager fm);

/**
 * \brief Calcula o número de clientes que não realizaram nenhuma compra.
 * 
 * Juntamente com a função `get_n_not_bought_products` permite resolver a QUERY nº6 do SGV.
 * 
 * @param cc Catálogo de clientes utilizado.
 * @param fm Gestor de filiais utilizado.
 * 
 * @returns O número de clientes que não realizaram nenhuma compra.
 */
int get_n_not_bought_clients(CatClients cc, FilManager fm);

/**
 * \brief Calcula o número de produtos que não foram comprados.
 * 
 * Juntamente com a função `get_n_not_bought_clients` permite resolver a QUERY nº6 do SGV.
 * 
 * @param cp Catálogo de produtos utilizado.
 * 
 * @returns O número de produtos que não foram comprados.
 */
int get_n_not_bought_products(CatProducts cp);

/**
 * \brief Cria uma matriz com dimensão [N_FILIAIS][N_MONTHS] com todos os valores necessários.
 * 
 * Esta função tem como objetivo resolver a QUERY nº7 do SGV.
 * 
 * @param fm Gestor de filiais utilizado.
 * @param client_code Código do produto que se pretende verificar.
 *
 * @returns Uma matriz de inteiros com o número de filiais (3 colunas) e o total de produtos vendidos, por mês (12 linhas).
 */
int **get_matrix(FilManager fm, char *client_code);

/**
 * \brief Calcula o número total de transações entre 2 meses.
 * 
 * Juntamente com a função `get_interval_rev` permite realizar a QUERY nº8 do SGV.
 * 
 * @param ac Contabilidade utilizada.
 * @param init Mês inicial.
 * @param end Mês final.
 * 
 * @returns O número total de transações entre 2 meses, -1 caso os meses sejam inválidos.
 */
int get_interval_trans(Accounting ac, int init, int end);

/**
 * \brief Calcula o fluxo monetário total entre 2 meses.
 * 
 * Juntamente com a função `get_interval_trans` permite realizar a QUERY nº8 do SGV.
 * 
 * @param ac Contabilidade utilizada.
 * @param init Mês inicial.
 * @param end Mês final.
 * 
 * @returns O fluxo monetário total entre 2 meses, -1 caso os meses sejam inválidos.
 */
double get_interval_rev(Accounting ac, int init, int end);

/**
 * \brief Cria uma lista com todos os códigos de todos os clientes que compraram um certo produto com um certo código promocional.
 * 
 * Esta função tem como objetivo resolver a QUERY nº9 do SGV.
 * 
 * @param fm Gestor de filiais utilizado.
 * @param product_code Código do produto que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * @param promo Código promocional utilizado.
 * 
 * @returns Uma lista com todos os códigos de todos os clientes que compraram um certo produto com um certo código promocional.
 */
TAD_List get_product_buyers(FilManager fm, char *product_code, int filial, int promo);

/**
 * \brief Cria uma lista com o código de todos os produtos mais comprados por quantidade, por ordem descendente, por um dado cliente, em certo mês.
 * 
 * Esta função tem como objetivo resolver a QUERY nº10 do SGV.
 * 
 * @param fm Gestor de filiais utilizado.
 * @param client_code Código do cliente que se pretende verificar.
 * @param month Mês que se pretende verificar.
 * 
 * @returns Uma lista com o código de todos os produtos mais comprados por quantidade, por ordem descendente, por um dado cliente, em certo mês, ou NULL caso o cliente não exista ou seja inválido.
 */
TAD_List get_clients_most_bought(FilManager fm, char *client_code, int month);

/**
 * \brief Cria uma lista com o código dos _top N_ produtos mais vendidos por quantidade, indicando o número total de clientes e o número de unidades vendidadas, filial a filial, para cada produto.
 * 
 * Esta função tem como objetivo resolver a QUERY nº11 do SGV.
 * 
 * @param ac Contabilidade utilizada.
 * @param fm Gestor de filiais utilizado.
 * @param N Indica o número de elementos a incluir.
 * 
 * @returns Uma lista com o código dos _top N_ produtos mais vendidos por quantidade, indicando o número total de clientes e o número de unidades vendidadas, filial a filial, para cada produto.
 */
TAD_List get_topN_most_sold(Accounting ac, FilManager fm, int N);

/**
 * \brief Cria uma lista com o código dos _top 3_ produtos em que um dado cliente gastou mais dinheiro.
 * 
 * Esta função tem como objetivo resolver a QUERY nº12 do SGV.
 * 
 * @param fm Gestor de filiais utilizado.
 * @param client_code Código do cliente que se pretende verificar.
 * 
 * @returns Uma lista com o código dos _top 3_ produtos em que um dado cliente gastou mais dinheiro, ou NULL caso o cliente não exista ou seja inválido.
 */
TAD_List get_clients_top3(FilManager fm, char *client_code);

#endif