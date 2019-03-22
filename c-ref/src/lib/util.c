/**
 * @file util.c 
 * \brief Ficheiro contendo funções que podem ser uteis úteis ao longo do projeto.
 **/
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
int mystrcmp(const void *a, const void *b);
int conv_str(const void *key);
Currier currier_make(void *key, void *value, void *user_data);
void currier_destroy(void *c);
void *uncurry_by_key(void *c);
void *uncurry_by_value(void *c);
void *uncurry_by_user(void *c);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

typedef struct currier
{
    void *key,
        *value,
        *user_data;
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

Currier currier_make(void *key, void *value, void *user_data)
{
    Currier c = g_malloc(sizeof(struct currier));
    c->key = key;
    c->value = value;
    c->user_data = user_data;
    return c;
}

void currier_destroy(void *e)
{
    Currier c = (Currier)e;
    if (c)
        g_free(c);
}

void *uncurry_by_key(void *c)
{
    return ((Currier)c)->key;
}

void *uncurry_by_value(void *c)
{
    return ((Currier)c)->value;
}

void *uncurry_by_user(void *c)
{
    return ((Currier)c)->user_data;
}