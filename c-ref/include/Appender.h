/**
 * @file Appender.h
 * \brief Interface que contém os métodos fornecidos para interagir com instâncias da classe `Appender`.
 * 
 * Em módulos acima na hierarquia esta classe representa a ligação entre clientes e os produtos
 * que este cliente comprou. Cada instância da classe `Appender` representa uma diferente ligação
 * entre cliente e produto. Sendo que, para cada uma destas ligações é armazenada informação útil de modo
 * a conseguir, de forma eficiente, responder às queries apresentadas.
 */

#ifndef _APPENDER_
#define _APPENDER_

#include "Product.h"
#include "TAD_List.h"
#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `Appender`.
 */
typedef struct appender *Appender;

/**
 * \brief Cria uma instância da classe `Appender`.
 * 
 * @returns Uma nova instância.
 */
gpointer appender_make();

/**
 * \brief Liberta a memória associada a uma instância da classe `Appender`. 
 * 
 * @param v Instância que se pretender libertar.
 */
void appender_destroy(gpointer v);

/**
 * \brief Atualiza a informação interna de uma instância da classe `Appender` com a informação presente em `user_data`.
 * 
 * Assume-se que a informação utilizada para atualizar os valores internos da instância possui a seguinte formatação:
 * 
 * [produto]+[filial]+[mes]+[units]+[cost]
 * 
 * @param e Instância a considerar.
 * @param user_data Informação utilizada para atualizar os valores internos da instância.
 */
void appender_update(gpointer e, gpointer user_data);

/**
 * \brief Calcula a quantidade de produtos comprada pelo cliente numa dada filial e mês.
 * 
 * @param ap Instância a considerar.
 * @param filial Filial que se pretende verificar.
 * @param month Mês que se pretende verificar.
 * 
 * @returns A quantidade de produtos comprada pelo cliente numa dada filial e mês.
 */
int appender_get_quantity(Appender ap, int filial, int month);

/**
 * \brief Calcula o número de produtos comprados pelo cliente.
 * 
 * @param ap Instância a considerar.
 * 
 * @returns O número de produtos comprados pelo cliente.
 */
int appender_get_num_product(Appender ap);

/**
 * \brief Calcula o total gasto num certo produto pelo cliente.
 * 
 * @param ap Instância a considerar.
 * @param product Produto que se pretende verificar.
 * 
 * @returns O total gasto num certo produto, ou -1.0 caso o produto não tenha sido comprado pelo cliente.
 */
double appender_get_prod_spent(Appender ap, Product product);

/**
 * \brief Calcula o número de unidades de um certo produto que foram compradas num certo mês pelo cliente.
 * 
 * @param ap Instância a considerar.
 * @param product Produto que se pretende verificar.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número de unidades compradas do produto num dado mês, ou -1 caso o produto não tenha sido comprado pelo cliente.
 */
int appender_get_prod_quant_month(Appender ap, Product product, int month);

/**
 * \brief Calcula o número de unidades compradas pelo cliente numa dada filial.
 * 
 * @param ap Instância a considerar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número de unidades compradas pelo cliente numa dada filial.
 */
int appender_get_quantity_fil(Appender ap, int filial);

/**
 * \brief Cria uma matriz com dimensões [N_FILIAIS][N_MONTHS], que para cada posição indica quantas unidades foram compradas pelo cliente numa dada filial e mês.
 * 
 * @param ap Instância a considerar.
 * 
 * @returns A matriz indicada.
 */
int **appender_clone_matrix(Appender ap);

/**
 * \brief Cria uma lista com os códigos dos produtos comprados num certo mês pelo cliente, por ordem descendente no número de unidades compradas.
 *
 * @param ap Instância a considerar.
 * @param month Mês que se pretende verificar.
 * 
 * @returns Uma lista com os códigos dos produtos comprados num certo mês pelo cliente, por ordem descendente no número de unidades compradas.
 */
TAD_List appender_get_most_bought(Appender ap, int month);

/**
 * \brief Cria uma lista com os códigos dos _top 3_ produtos em que o cliente gastou mais dinheiro.
 * 
 * @param ap Instância a considerar.
 * 
 * @returns Uma lista com os códigos dos _top 3_ produtos em que o cliente gastou mais dinheiro.
 */
TAD_List appender_get_top3(Appender ap);

/**
 * \brief Verifica se o cliente efetuou compras em todas as filiais.
 * 
 * @param ap Instância a considerar.
 * 
 * @returns 1 se o cliente efetuou compras em todas as filiais, 0 caso contrário.
 */
int is_bought_in_all(Appender ap);

#endif
