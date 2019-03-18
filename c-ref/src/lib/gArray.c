#include "gArray.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metódos publicos */
GrowingArray garray_make(size_t key_size, freefunc ff);
void garray_destroy(GrowingArray g);
size_t garray_size(GrowingArray g);
void garray_add(GrowingArray g, void *entry);
void garray_sort(GrowingArray g, fcompare fc);
int garray_is_sorted(GrowingArray g);
void **garray_dump_elems(GrowingArray src, void *(*f_map)(void *), size_t *h);
int garray_auto_resize(GrowingArray g);
void **garray_take_n(GrowingArray g, size_t *hold, size_t N);

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

GrowingArray garray_make(size_t key_size, freefunc ff)
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

void garray_destroy(GrowingArray g)
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

size_t garray_size(GrowingArray g)
{
    return g->used;
}

void garray_add(GrowingArray g, void *entry)
{
    if (g->used >= g->max_size)
        double_garray(g);
    g->array[g->used++] = entry;
}

void garray_sort(GrowingArray g, fcompare fc)
{
    if (!g->sorted)
    {
        qsort(g->array, g->used, g->key_size, fc);
        g->sorted = 1;
    }
}

int garray_is_sorted(GrowingArray g)
{
    return g->sorted;
}

void **garray_dump_elems(GrowingArray src, void *(*f_map)(void *), size_t *h)
{
    size_t i;

    void **e_arr = g_malloc(sizeof(void *) * src->used);

    for (i = 0; i < src->used; i++)
        e_arr[i] = f_map ? (*f_map)(src->array[i]) : src->array[i];

    *h = src->used;

    return e_arr;
}

int garray_auto_resize(GrowingArray g)
{
    int r = g->used < g->max_size;

    if (r)
    {
        g->array = g_realloc(g->array, sizeof(void *) * g->used);
        g->max_size = g->used;
    }

    return r;
}

void **garray_take_n(GrowingArray g, size_t *hold, size_t N)
{
    size_t i, max = min(N, g->used);
    void **e_arr = NULL;

    if (max > 0)
    {
        e_arr = g_malloc(sizeof(void *) * max);

        for (i = 0; i < max; i++)
            e_arr[i] = g->array[i];
    }

    *hold = max;

    return e_arr;
}

static void double_garray(GrowingArray g)
{
    g->array = g_realloc(g->array, sizeof(void *) * g->max_size * 2);
    g->max_size *= 2;
}