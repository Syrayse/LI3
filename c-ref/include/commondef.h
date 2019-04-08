/**
 * @file commondef.h
 * \brief Ficheiro que contém pre-definições para o corrente modelo de SGV.
 */

#ifndef __COMMON_SGV_DEF__
#define __COMMON_SGV_DEF__

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
    CLT_ID = 1,       /**< Identificador de um cliente. */
    N_QUERIES = 12    /**< Número de queries do SGV. */
};

#endif