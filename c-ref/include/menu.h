/**
 * @file Menu.h
 * \brief Interface de todos os métodos que podem ser usados para interagir com instâncias da classe `Menu`.
 */

#ifndef __MENU__
#define __MENU__

/**
 * \brief Tipo opaco representativo da classe `Menu`.
 */
typedef struct menu * Menu;

/**
 * \brief Cria uma instância da classe `Menu` que permite interação com o menu.
 * 
 * @returns Uma nova instância.
 */
Menu menu_make();

/**
 * \brief Executa a instância `Menu`, esta corre até ser terminada internamente.
 * 
 * @param m Instância da classe que pretende correr.
 */
void menu_run(Menu m);

/**
 * \brief Destrói uma instância da classe `Menu`.
 * 
 * @param m Instância que se pretende destruir.
 */
void menu_destroy(Menu m);

#endif