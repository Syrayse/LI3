/**
 * @file Currier.h
 * \brief Interface da classe `Currier`.
 * 
 * Esta classe permite fazer a junção de vários valores diferentes numa só estrutura,
 * isto permite tratar vários valores como se só de um se tratassem.
 */

#ifndef _CURRIER_
#define _CURRIER_

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `Currier`.
 */
typedef struct currier *Currier;

/**
 * \brief Cria e inicializa uma instância da classe `Currier` com os valores passados com argumento.
 *
 * @returns Uma nova instância que contém os valores passados como argumento.
 */
Currier currier_make(gpointer key, gpointer value, gpointer user_data);

/**
 * \brief Liberta a memória associada à instância `Currier`, sem libertar a sua informação interna.
 * 
 * @param cr Instância que se pretende libertar.
 */
void currier_destroy(Currier cr);

/**
 * \brief Indica o elemento considerado como chave da instância.
 * 
 * @param cr Instância a considerar.
 * 
 * @returns O elemento considerado como chave da instância.
 */
gpointer uncurry_by_key(Currier cr);

/**
 * \brief Indica o elemento considerado como valor da instância.
 * 
 * @param cr Instância a considerar.
 * 
 * @returns O elemento considerado como valor da instância.
 */
gpointer uncurry_by_value(Currier cr);

/**
 * \brief Indica o elemento considerado como informação adicional da instância.
 * 
 * @param cr Instância a considerar.
 * 
 * @returns o elemento considerado como informação adicional da instância.
 */
gpointer uncurry_by_user(Currier cr);

#endif