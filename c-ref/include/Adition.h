/**
 * @file Adition.h
 * \brief Interface de todos os metódos utilizaveis da classe `Adition`.
 * 
 * Em módulo acima na hierarquia esta classe é utilizada de forma a armazenar todos
 * os clientes que estão associados a um dado produto, representando assim a relação
 * de um produto com todos os clientes que o compraram.
 * 
 * Para cada cliente presente no conjunto da instância é guardada a forma como este
 * interagiu com o produto ao qual está anexada esta instância.
 */

#ifndef _ADITION_
#define _ADITION_

#include "TAD_List.h"
#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `Adition`.
 */
typedef struct adition *Adition;

/**
 * \brief Cria uma instância da classe `Adition`.
 * 
 * @returns Uma nova instância.
 */
gpointer adition_make();

/**
 * \brief Liberta a memória associada a uma instância da classe `Adition`. 
 * 
 * @param e Instância que se pretender libertar.
 */
void adition_destroy(gpointer e);

/**
 * \brief Atualiza a informação interna de uma instância da classe `Adition` com a informação presente em `user_data`.
 * 
 * Assume-se que a informação utilizada para atualizar os valores internos da instância possui a seguinte formatação:
 * 
 * [cliente]+[filial]+[promoção]
 * 
 * @param e Instância a considerar.
 * @param user_data Informação utilizada para atualizar os valores internos da instância.
 */
void adition_update(gpointer e, gpointer user_data);

/**
 * \brief Cria uma lista com o código de todos os clientes que efetuaram numa dada filial compras com o código promocional referido.
 * 
 * @param ad Instância a considerar.
 * @param filial Filial que se pretende verificar.
 * @param promo Código promocional a considerar.
 * 
 * @returns Uma lista com o código de todos os clientes que efetuaram numa dada filial compras com o código promocional referido.
 */
TAD_List adition_dump_by_promo_fil(Adition ad, int filial, int promo);

/**
 * \brief Calcula o número de clientes que estão presentes na instância.
 * 
 * O número de clientes presentes na instância representa o número de clientes
 * que compraram o produto ao qual está anexada a instância em questão.
 * 
 * @param ad Instância a considerar.
 * 
 * @returns O número de clientes que estão presentes na instância.
 */
int adition_size(Adition ad);

#endif