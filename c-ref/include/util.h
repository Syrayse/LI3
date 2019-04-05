/**
 * @file util.h 
 * \brief Ficheiro que contèm funções e macros que podem ser úteis e ao longo do projeto.
 */

#ifndef UTIL_H
#define UTIL_H

/**
 * \brief Indexador dos códigos promocionais.
 */
#define indP(a) ((a) == ('N') ? 0 : 1)

/**
 * \brief Estrutura que contém informação essencial à estruturização das diferentes componentes pré-definidas do projeto.
 */
enum utils
{
    N_MONTHS = 12,    /**< Número de meses considerados. */
    N_FILIAIS = 3,    /**< Número de filiais existentes. */
    N_PROMOS = 2,     /**< Número de promoções existentes. */
    PROD_LEN = 6,     /**< Comprimento de um código de produto. */
    CLT_LEN = 5,      /**< Comprimento de um código de cliente. */
    N_LETTER = 26,    /**< Número de letras no alfabeto. */
    N_TRANS_ARGS = 7, /**< Número de argumentos que um registo de transação deve possuir. */
    PROD_ID = 0,      /**< Identificador de um produto */
    CLT_ID = 1        /**< Identificador de um cliente. */
};

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
 * \brief Maximo entre dois números.
 */
#define max(a, b) ((a) > (b) ? (a) : (b))

#endif