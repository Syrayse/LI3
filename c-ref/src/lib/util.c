/**
 * @file util.c 
 * \brief Ficheiro contendo funções que podem ser uteis úteis ao longo do projeto.
 **/
#include "util.h"
#include "gArray.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
void is_null(void *a);
int mystrcmp(const void *a, const void *b);
int conv_str(const void *key);
Currier currier_make(void *key, void *value);
void currier_destroy(void *c);
void *uncurry_by_key(void *c);
void *uncurry_by_value(void *c);
int compare_quants(const void *a, const void *b);
int compare_ntrans(const void *a, const void *b);
void foreach_add_g_currier(void *key, void *value, void *user_data);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

typedef struct currier
{
    void *key,
        *value;
} * Currier;

// ------------------------------------------------------------------------------

void is_null(void *a)
{
    if (a)
    {
        g_free(a);
    }
}

int mystrcmp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int conv_str(const void *key)
{
    return (((int)(*(const char *)key)) - 'A');
}

Currier currier_make(void *key, void *value)
{
    Currier c = g_malloc(sizeof(struct currier));
    c->key = key;
    c->value = value;
    return c;
}

void currier_destroy(void *e)
{
    if (e)
        g_free((Currier)e);
}

void *uncurry_by_key(void *c)
{
    return ((Currier)c)->key;
}

void *uncurry_by_value(void *c)
{
    return ((Currier)c)->value;
}

int compare_quants(const void *a, const void *b)
{
    Currier ca = *(Currier *)a;
    Currier cb = *(Currier *)b;
    return ((*(int *)cb->value) - (*(int *)ca->value));
}

void foreach_add_g_currier(void *key, void *value, void *user_data)
{
    Currier c = currier_make(key, value);
    garray_add((GrowingArray)user_data, c);
}