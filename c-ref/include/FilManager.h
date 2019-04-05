/**
 * @file FilManager.h
 * \brief Interface dos metódos que podem aplicados a instâncias da classe `FilManager`.
 * 
 * Este classe tem como objetivo representar todas as relações existentes entre clientes
 * e os produtos que comprou, ou, produtos e os clientes que o compraram. Esta classe efetua o tratamento
 * de todas as filiais de uma só vez. Sendo que para um dado produto ou cliente está presente
 * toda a informação útil necessária para representar as diferentes ligações para todas as filiais.
 */

#ifndef _FILMANAGER_
#define _FILMANAGER_

#include "TAD_List.h"
#include "Client.h"
#include "Product.h"

/**
 * \brief Tipo opaco representativo de uma instância da classe `FilManager`.
 */
typedef struct filmanager *FilManager;

/**
 * \brief Cria e inicializa uma instância da classe `FilManager`.
 * 
 * @returns Uma nova instância.
 */
FilManager filmanager_make();

/**
 * \brief Liberta a memória associada a uma instância da classe `FilManager`.
 * 
 * @param fm Instância que se pretende libertar.
 */
void filmanager_destroy(FilManager fm);

/**
 * \brief Permite atualizar o valores internos de uma instància da classe `FilManager`.
 * 
 * Esta atualização dos valores internos é feita de forma a permitir respostas corretas às queries necessárias
 * e que são resolvidas por esta classe. Este valores utilizados na atualização corresponde as valores
 * que se obtem normalmente de uma estrutura que representa um tipo de transação.
 * 
 * @param fm Instância a considerar.
 * @param product Produto transacionado.
 * @param client Cliente que efetuou a transação.
 * @param filial Filial onde ocorreu a transação.
 * @param month Mês em que se deu a transação.
 * @param promo Código corresponde à promoção usada.
 * @param units Número de unidades envolvidas.
 * @param spent Preço unitário envolvido.
 */
void filmanager_update(FilManager fm, Product product, Client client, int filial, int month, int promo, int units, double spent);

/**
 * \brief Produz uma lista que contém os códigos de todos os clientes que efetuaram compras em todas as filiais.
 * 
 * @param fm Instância a considerar.
 * 
 * @returns A nova lista criada.
 */
TAD_List filmanager_get_overall_clients(FilManager fm);

/**
 * \brief Calcula uma matriz de dimensão [`N_FILIAIS`][`N_MONTHS`] que para cada posição contém o número de unidades compradas por um dado cliente, numa certa filial e mês.
 *
 * @param fm Instância a considerar.
 * @param client Cliente do qual se pretende obter informação.
 * 
 * @returns A matriz que representa as interações do cliente, ou NULL caso este cliente não exista na instância.
 */
int **filmanager_get_units_matrix(FilManager fm, Client client);

/**
 * \brief Produz uma lista com o código de todos os clientes, que compraram um certo produto, numa certa filial com um respetivo código promocional.
 * 
 * @param fm Instância a considerar.
 * @param product Produto que se pretende considerar.
 * @param filial Filial onde se foi comprado o produto.
 * @param promo Código promocional com que foi comprado o produto.
 * 
 * @returns A nova lista criada, ou NULL caso o produto não exista na instância.
 */
TAD_List filmanager_get_client_at_fil(FilManager fm, Product product, int filial, int promo);

/**
 * \brief Produz uma lista com o código dos produtos mais comprados por um certo cliente num mês, por ordem descendente segundo a quantidade comprada. 
 *
 * @param fm Instância a considerar.
 * @param product Produto do qual se pretende obter informação.
 * 
 * @returns A nova lista criada, ou NULL caso o cliente não exista na instância.
 */
TAD_List filmanager_get_most_bought(FilManager fm, Client client, int month);

/**
 * \brief Calcula o número de clientes que compraram um certo produto.
 *
 * @param fm Instância a considerar.
 * @param product Produto do qual se pretende obter informação.
 * 
 * @returns O número de clientes que compraram um certo produto, -1 caso esse produto não exista na instância.
 */
int filmanager_get_n_of_clients(FilManager fm, Product product);

/**
 * \brief Produz uma lista com o código dos _top 3_ produtos em que um dado cliente gastou mais dinheiro.
 * 
 * @param fm Instância a considerar.
 * @param cliente Cliente do qual se pretende obter informação.
 * 
 * @returns A nova lista criada, ou NULL caso o cliente não exista na instância.
 */
TAD_List filmanager_get_top3(FilManager fm, Client client);

/**
 * \brief Calcula o número de clientes que efetuaram compras.
 * 
 * @param fm Instância a considerar.
 * 
 * @returns O número de clientes que efetuaram compras. 
 */
int filmanager_get_active_n_clients(FilManager fm);

/**
 * \brief Calcula o número de produtos que foram comprados.
 * 
 * @param fm Instância a considerar.
 * 
 * @returns O número de produtos que foram comprados. 
 */
int filmanager_get_active_n_products(FilManager fm);

#endif