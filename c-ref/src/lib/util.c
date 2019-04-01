/**
 * @file util.c 
 * \brief Ficheiro que contèm funções e macros que podem ser úteis e ao longo do projeto.
 */
#include "util.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
int mystrcmp(const void *a, const void *b);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

/**
 * \brief Efetua a comparação alfabética de duas _Strings_.
 * 
 * @param a Primeira _String_.
 * @param b Segunda _String_.
 * 
 * @returns O mesmo resultado que a função `strcmp`.
 */
int mystrcmp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}