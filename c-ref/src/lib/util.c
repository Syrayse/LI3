/**
 * @file util.c 
 * \brief Ficheiro contendo funções que podem ser uteis úteis ao longo do projeto.
 **/
#include "util.h"
#include <glib.h>

/**
 * \brief Função usada para evitar warning com o tipo de dados fcompar.
 **/
int mystrcmp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

/**
 * \brief Calcula o indice de uma certa key.
 **/
int conv_str(const void *key)
{
    return (((int)(*(const char *)key)) - 'A');
}