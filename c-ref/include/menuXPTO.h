/**
 * @file menuXPTO.h
 * \brief Interface de todos os metódos que podem ser usados para interagir com instâncias da classe `MenuXPTO`.
 */

#ifndef __MENU__XPTO__
#define __MENU__XPTO__

/**
 * \brief Tipo opaco representativo da classe `MenuXPTO`.
 */
typedef struct menuxpto *MenuXPTO;

/**
 * \brief Cria uma instância da classe `MenuXPTO` que permite interação com o menu.
 * 
 * @returns Uma nova instância.
 */
MenuXPTO menu_make();

/**
 * \brief Executa a instância `MenuXPTO`, esta corre até ser terminada internamente.
 * 
 * @param m Instância da classe que pretende correr.
 */
void menu_run(MenuXPTO m);

/**
 * \brief Destrói uma instância da classe `MenuXPTO`.
 * 
 * @param m Instância que se pretende destruir.
 */
void menu_destroy(MenuXPTO m);

#endif