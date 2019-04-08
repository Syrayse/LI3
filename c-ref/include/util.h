/**
 * @file util.h 
 * \brief Ficheiro que contém funções e macros que podem ser úteis ao longo do projeto.
 */

#ifndef UTIL_H
#define UTIL_H

/**
 * \brief Verifica se x se encontra entre dois limites.
 * 
 * @param x Valor a verificar.
 * @param min Limite inferior.
 * @param max Limite superior.
 * 
 * @returns 1 se x se encontra min e max, 0 caso contrário.
 */
#define is_between(x, min, max) ((x >= min) && (x <= max))

/**
 * \brief Mínimo entre dois números.
 * 
 * @param a Primeiro número.
 * @param b Segundo número.
 * 
 * @returns O menor dos dois.
 */
#define min(a, b) ((a) < (b) ? (a) : (b))

/**
 * \brief Máximo entre dois números.
 * 
 * @param a Primeiro número.
 * @param b Segundo número.
 * 
 * @returns O maior dos dois.
 */
#define max(a, b) ((a) > (b) ? (a) : (b))

#endif