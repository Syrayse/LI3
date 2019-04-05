/**
 * @file statinfo.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `StatInfo`.
 * 
 * Através da utilização desta classe é possivél armazenar informação considerada útil para comunicar ao utilizador
 * do SGV importantes detalhes sobre registos de transações.
 * 
 * Este módulo vê a sua utilidade quando se pretende comunicar com o utilizador do SGV quando este pretende obter
 * valores contabilisticos associados a um dado cliente ou um dado produto.
 */

#ifndef STATINFO_H
#define STATINFO_H

/**
 * \brief Tipo opaco representativo de uma instância da classe `StatInfo`.
 */
typedef struct statistical_info *StatInfo;

/**
 * \brief Cria uma instância da classe `StatInfo` com valores inicializados.
 * 
 * @returns Uma nova instância.
 */
StatInfo statinfo_make();

/**
 * \brief Destrói uma instância da classe `StatInfo`.
 * 
 * @param a Instância que se pretende destruir.
 */
void statinfo_destroy(StatInfo si);

/**
 * \brief Permite atualizar a informação presente na instância da classe `StatInfo`.
 * 
 * Assume-se que o valor utilizado na atualização se encontra no formato, correspondente aos indices:
 * 
 * [month]+[filial]+[units]+[promo]+[spent].
 * 
 * @param si Instància que se pretende atualizar.
 * @param uset_data Valores utilizados na atualização.
 */
void statinfo_update(StatInfo si, void *user_data);

/**
 * \brief Calcula o número de unidades totais vendidas.
 * 
 * @param si Instància a considerar.
 * 
 * @returns O valor calculado.
 */
int get_t_units(StatInfo si);

/**
 * \brief Calcula o número de unidades vendidas numa dada filial.
 * 
 * @param si Instância a considerar.
 * @param filial Da qual se pretende obter informação.
 * 
 * @returns O valor calculado.
 */
int get_t_units_fil(StatInfo si, int filial);

/**
 * \brief Calcula o número total de transações.
 * 
 * @param si Instância a ser considerada.
 * 
 * @returns O número total de transações.
 */
int get_t_vendas(StatInfo);

/**
 * \brief Calcula o número total de transações por mês e filial.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por mês e filial.
 */
int get_t_month_fil_vendas(StatInfo, int month, int filial);

/**
 * \brief Calcula o número total de transações por mês e filial, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por mês e filial, com promoção.
 */
int get_t_month_fil_vendas_promo(StatInfo, int month, int filial);

/**
 * \brief Calcula o número total de transações por mês e filial, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por mês e filial, sem promoção.
 */
int get_t_month_fil_vendas_no_promo(StatInfo, int month, int filial);

/**
 * \brief Calcula o número total de transações por mês.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número total de transações por mês.
 */
int get_t_month_vendas(StatInfo, int month);

/**
 * \brief Calcula o número total de transações por mês, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número total de transações por mês, com promoção.
 */
int get_t_month_vendas_promo(StatInfo, int month);

/**
 * \brief Calcula o número total de transações por mês, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número total de transações por mês, sem promoção.
 */
int get_t_month_vendas_no_promo(StatInfo, int month);

/**
 * \brief Calcula o fluxo monetário total associado à instância.
 * 
 * @param a Instância a ser considerada.
 * 
 * @returns O Fluxo monetário total.
 */
double get_t_rev(StatInfo);

/**
 * \brief Calcula o fluxo monetário total de um dado mês e filial.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O fluxo monetário total associado a um dado mês e filial.
 */
double get_t_month_fil_rev(StatInfo, int month, int filial);

/**
 * \brief Calcula o fluxo monetário total de um dado mês e filial, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O fluxo monetário total associado a um dado mês e filial, com promoção.
 */
double get_t_month_fil_rev_promo(StatInfo, int month, int filial);

/**
 * \brief Calcula o fluxo monetário total de um dado mês e filial, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O fluxo monetário total associado a um dado mês e filial, sem promoção.
 */
double get_t_month_fil_rev_no_promo(StatInfo, int month, int filial);

/**
 * \brief Calcula o fluxo monetário total de um dado mês.
 * 
 * Este método tira partido de uma função que permite a iteração sobre a matriz
 * recipiente atual utilizada, de forma a calcular os valores pretendidos.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O fluxo monetário total de um dado mês.
 */
double get_t_month_rev(StatInfo, int month);

/**
 * \brief Calcula o fluxo monetário total de um dado mês, com promoção.
 * 
 * Este método tira partido de uma função que permite a iteração sobre a matriz
 * recipiente atual utilizada, de forma a calcular os valores pretendidos.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O fluxo monetário total de um dado mês, com promoção.
 */
double get_t_month_rev_promo(StatInfo, int month);

/**
 * \brief Calcula o fluxo monetário total de um dado mês, sem promoção.
 * 
 * Este método tira partido de uma função que permite a iteração sobre a matriz
 * recipiente atual utilizada, de forma a calcular os valores pretendidos.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O fluxo monetário total de um dado mês, sem promoção.
 */
double get_t_month_rev_no_promo(StatInfo, int month);

#endif