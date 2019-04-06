/**
 * @file ClntInfo.h
 * \brief Interface fornecida para interagir com a instâncias da classe `ClntInfo`.
 * 
 * Esta classe tem como objetivo relacionar os produtos com os clientes que o compraram.
 * 
 * Em módulos acima na hierarquia esta classe é utilizada de modo a representar de que forma
 * é que um dado produto foi comprado por um dado cliente em uma dada filial.
 */

#ifndef _CLNTINFO_
#define _CLNTINFO_

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `ClntInfo`.
 */
typedef struct clntinfo *ClntInfo;

/**
 * \brief Cria uma instância da classe `ClntInfo`.
 * 
 * @returns A nova instância.
 */
gpointer clntinfo_make();

/**
 * \brief Destrói uma instância da classe `ClntInfo`.
 * 
 * @param e Instância a destruir.
 */
void clntinfo_destroy(gpointer e);

/**
 * \brief Atualiza a informação interna a uma instância da classe `ClntInfo`.
 * 
 * Assume que a informação utilizada para atualizar a instância é fornecida da seguinte forma:
 * 
 * [filial]+[promo]
 * 
 * @param e Instância a considerar.
 * @param user_data Informação utilizada para atualizar a instância.
 */
void clntinfo_update(gpointer e, gpointer user_data);

/**
 * \brief Calcula o código de promoções de uma instância numa dada filial.
 * 
 * O código de promoções varia no seguinte conjunto de valores:
 * 
 * -1: O Cliente que `ClntInfo` representa nunca comprou naquela filial.
 * 0: Só efetuou compras sem promoção.
 * 1: Só efetuou compras com promoção.
 * 2: Efetuou compras tanto com promoção como sem.
 * 
 * @param ci Instância a considerar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O código de promoções de uma instância numa dada filial.
 */
int clntinfo_promo(ClntInfo ci, int filial);

#endif