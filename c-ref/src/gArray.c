#include "gArray.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

GrowingArray make_garray(size_t key_size, freefunc ff);
void destroy_garray(GrowingArray g);
size_t get_size_garray(GrowingArray g);
void insert_elem_garray(GrowingArray g, void *entry);
void sort_garray(GrowingArray g, fcompar fc);
int is_sorted_garray(GrowingArray g);
void **dump_elems_garray(GrowingArray src, size_t *h);

/* Metodos privados */
static void double_garray(GrowingArray g);

// ------------------------------------------------------------------------------

typedef struct garray
{
    int sorted;
    size_t key_size,
        used,
        max_size;
    void **array;
    freefunc ff;
} * GrowingArray;

// ------------------------------------------------------------------------------

#define BASE_SIZE 10

// ------------------------------------------------------------------------------

GrowingArray make_garray(size_t key_size, freefunc ff)
{
    GrowingArray g = g_malloc(sizeof(struct garray));
    g->sorted = 0;
    g->key_size = key_size;
    g->used = 0;
    g->max_size = BASE_SIZE;
    g->array = g_malloc(sizeof(void *) * BASE_SIZE);
    g->ff = ff;
    return g;
}

void destroy_garray(GrowingArray g)
{
    size_t i;

    if (g->ff)
    {
        for (i = 0; i < g->used; i++)
        {
            (*g->ff)(g->array[i]);
        }
    }

    g_free(g->array);

    g_free(g);
}

size_t get_size_garray(GrowingArray g)
{
    return g->used;
}

void insert_elem_garray(GrowingArray g, void *entry)
{
    if (g->used >= g->max_size)
        double_garray(g);
    g->array[g->used++] = entry;
}

void sort_garray(GrowingArray g, fcompar fc)
{
    if (!g->sorted)
    {
        qsort(g->array, g->used, sizeof(char *), fc);
        g->sorted = 1;
    }
}

int is_sorted_garray(GrowingArray g)
{
    return g->sorted;
}

void **dump_elems_garray(GrowingArray src, size_t *h)
{
    size_t i;

    void **e_arr = g_malloc(sizeof(void *) * src->used);

    for (i = 0; i < src->used; i++)
        e_arr[i] = src->array[i];

    *h = src->used;

    return e_arr;
}

static void double_garray(GrowingArray g)
{
    g->array = g_realloc(g->array, g->key_size * g->max_size * 2);
    g->max_size *= 2;
}