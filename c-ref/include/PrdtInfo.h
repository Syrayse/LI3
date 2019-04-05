/**
 * @file PrdtInfo.h
 * \brief Interface de todos os metódos publicos para interagir com instância da classe `PrdtInfo`.
 * 
 * Esta classe tem como objetivo principal ser utilizada por classes acima na hierarquia,
 * classes essas necessitam de informação guardada numa classe do tipo `PrdtInfo`.
 * 
 * Possui capacidade de armazenar informação útil, que dado um Produto seja capaz de indicar
 * quanto dinheiro foi gasto no total nesse produto, e quantas unidades compradas mensalmente.
 * 
 * Pretende-se que esta classe seja utilizada como uma forma de representar informação
 * entre um cliente e um produto, sendo que contém toda a informação para que este meio seja
 * alcançado da forma mais eficiente, segundo as queries pedidas.
 */

#ifndef _PRDTINFO_
#define _PRDTINFO_

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `PrdtInfo`.
 */
typedef struct prdtinfo *PrdtInfo;

/**
 * \brief Permite criar uma instância da classe `PrdtInfo`.
 *
 * @returns Uma nova instância.
 */
gpointer prdtinfo_make();

/**
 * \brief Liberta a memória associada a uma instância da classe `PrdtInfo.h`.
 * 
 * @param e Instância que se pretende destruir.
 */
void prdtinfo_destroy(gpointer e);

/**
 * \brief Atualiza a informação interna da instância.
 * 
 * Esta função assume que a informação necessária a sua atualização interna
 * é passada no seguinte formato: [spent]+[units]+[month].
 * 
 * Ou seja deve ser passado como argumento um array que esteja indexado com os valores
 * acima indicados.
 * 
 * @param e Instância que se pretende atualizar.
 * @param user_data Informação utilizada na atualização dos valores internos.
 */
void prdtinfo_update(gpointer e, gpointer user_data);

/**
 * \brief Calcula o total gasto em um dado produto.
 * 
 * @param pi Instância representativa do produto a considerar.
 * 
 * @returns O total gasto naquele produto.
 */
double prdtinfo_total_spent(PrdtInfo pi);

/**
 * \brief Calcula quantas unidades foram transacionadas de um certo produto num dado mês.
 * 
 * @param pi Instância que se pretende considerar.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número de unidades transacionadas em um dado mês.
 */
int prdtinfo_month_units(PrdtInfo pi, int month);

#endif