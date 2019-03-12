#include "util.h"
#include <glib.h>
#include <stdio.h>

/**
 * \brief Função usada para evitar warning com o tipo de dados fcompar.
 **/
int strcmp_client(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int conv_str(const void *key)
{
    return (((int)(*(const char *)key)) - 'A');
}