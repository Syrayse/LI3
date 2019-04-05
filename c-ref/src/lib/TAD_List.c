/**
 * @file TAD_List.c
 * \brief Define o mõdulo de armazenamento e apresentação de tipos abstratos de dados, e todas as funções necessárias.
 * 
 * Isto é tornado possivél através de uma classe que armazena e permite transversar
 * tipos abstratos de dados.
 */
#include "TAD_List.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Definição da estrutura da classe `TAD_List`.
 */
typedef struct tad_list
{
    unsigned int next_ind, /**< Próximo elemento a ser retirado da lista.  */
        used,              /**< Número de elementos utilizados.  */
        max;               /**< Máxima capacidade da lista. */
    gpointer *array;       /**< Contentor de informação da lista. */
    GDestroyNotify f;
} * TAD_List;

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
TAD_List list_make(GDestroyNotify f, unsigned int size);
void list_destroy(TAD_List tl);
unsigned int list_size(TAD_List tl);
gpointer list_get_next(TAD_List tl);
int list_add(TAD_List tl, gpointer v);
void list_sort(TAD_List tl, GCompareFunc fc);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

TAD_List list_make(GDestroyNotify f, unsigned int size)
{
    TAD_List tl = g_malloc(sizeof(struct tad_list));

    tl->next_ind = tl->used = 0;

    tl->max = size;

    tl->array = g_malloc(sizeof(gpointer) * size);

    tl->f = f;

    return tl;
}

void list_destroy(TAD_List tl)
{
    int i;

    if (tl)
    {
        if (tl->f)
        {
            for (i = 0; i < tl->used; i++)
            {
                (*tl->f)(tl->array[i]);
            }
        }

        g_free(tl->array);
        g_free(tl);
    }
}

unsigned int list_size(TAD_List tl)
{
    return tl->used;
}

gpointer list_get_next(TAD_List tl)
{
    return (tl->next_ind < tl->used) ? tl->array[tl->used++] : NULL;
}

int list_add(TAD_List tl, gpointer v)
{
    int r = 0;

    if (tl->used < tl->max)
    {
        r = 1;

        tl->array[tl->used++] = v;
    }

    return r;
}

void list_sort(TAD_List tl, GCompareFunc fc)
{
    qsort(tl->array, tl->used, sizeof(gpointer), fc);
}
