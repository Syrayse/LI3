#include "Currier.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
Currier currier_make(void *key, void *value, void *user_data);
void currier_destroy(Currier cr);
void *uncurry_by_key(Currier cr);
void *uncurry_by_value(Currier cr);
void *uncurry_by_user(Currier cr);

/* Metodos privados */

/* ------------------------------------------------------------------------------ */

typedef struct currier
{
    void *key,
        *value,
        *user;
} * Currier;

/* ------------------------------------------------------------------------------ */

Currier currier_make(void *key, void *value, void *user_data)
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

void *uncurry_by_key(Currier cr)
{
    return cr->key;
}

void *uncurry_by_value(Currier cr)
{
    return cr->value;
}

void *uncurry_by_user(Currier cr)
{
    return cr->user;
}