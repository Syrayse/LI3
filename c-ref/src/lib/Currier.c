/**
 * @file Currier.c
 * \brief Ficheiro que contém a codificação da classe `Currier`.
 * 
 * Esta classe permite fazer a junção de vários valores diferentes numa só estrutura,
 * isto permite tratar vários valores como se só de um se tratassem.
 */

#include "Currier.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura que define a classe `Currier`.
 * 
 * Atualmente esta classe armazena 3 valores distintos, desenhada
 * de forma a ser fácil de utilizar com valores que estejam indexados por chave.
 */
typedef struct currier
{
    gpointer key, /**< Chave armazenada. */
        value,    /**< Valor armazenado. */
        user;     /**< Informação adicional armazenada. */
} * Currier;

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
Currier currier_make(gpointer key, gpointer value, gpointer user_data);
void currier_destroy(Currier cr);
gpointer uncurry_by_key(Currier cr);
gpointer uncurry_by_value(Currier cr);
gpointer uncurry_by_user(Currier cr);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

Currier currier_make(gpointer key, gpointer value, gpointer user_data)
{
    Currier cr = g_malloc(sizeof(struct currier));

    cr->key = key;

    cr->value = value;

    cr->user = user_data;

    return cr;
}

void currier_destroy(Currier cr)
{
    if (cr)
    {
        g_free(cr);
    }
}

gpointer uncurry_by_key(Currier cr)
{
    return cr->key;
}

gpointer uncurry_by_value(Currier cr)
{
    return cr->value;
}

gpointer uncurry_by_user(Currier cr)
{
    return cr->user;
}