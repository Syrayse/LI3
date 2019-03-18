#include "currier.h"
#include <glib.h>

// ------------------------------------------------------------------------------

Currier currier_make(void *key, void *value, void *user_data);
void currier_destroy(void *c);
void *uncurry_by_key(Currier c);
void *uncurry_by_value(Currier c);
void *uncurry_by_user(Currier c);

// ------------------------------------------------------------------------------

typedef struct currier
{
    void *key,
        *value,
        *user_data;
} * Currier;

// ------------------------------------------------------------------------------

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

void *uncurry_by_key(Currier c)
{
    return c->key;
}

void *uncurry_by_value(Currier c)
{
    return c->value;
}

void *uncurry_by_user(Currier c)
{
    return c->user_data;
}