#include "adition.h"
#include "util.h"
#include "record.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
void *adition_make();
void adition_destroy(void *v);
void adition_add(void *v, void *user_data);
int adition_is_empty(void *v);
gID *adition_dump(void *v, int filial, int *s);
int adition_rec_size(Adition a, int filial);

// ------------------------------------------------------------------------------

typedef struct adition
{
    char empty;
    Record recs[N_FILIAIS];
} * Adition;

// ------------------------------------------------------------------------------

void *adition_make()
{
    int i;

    Adition a = g_malloc(sizeof(struct adition));
    a->empty = 1;

    for (i = 0; i < N_FILIAIS; i++)
        a->recs[i] = rec_make();

    return a;
}

void adition_destroy(void *v)
{
    int i;
    Adition a = (Adition)v;

    if (a)
    {
        for (i = 0; i < N_FILIAIS; i++)
            rec_destroy(a->recs[i]);

        g_free(a);
    }
}

void adition_add(void *v, void *user_data)
{
    Adition a = (Adition)v;
    gID *g = (gID *)user_data;
    rec_add(a->recs[g[1] - 1], g[0]);
    a->empty = 0;
}

int adition_is_empty(void *v)
{
    return ((Adition)v)->empty;
}

gID *adition_dump(void *v, int filial, int *s)
{
    return rec_dump(((Adition)v)->recs[filial - 1], s);
}

int adition_rec_size(Adition a, int filial)
{
    return rec_size(a->recs[filial - 1]);
}