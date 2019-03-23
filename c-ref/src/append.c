#include "append.h"
#include "record.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
void *append_make();
void append_destroy(void *e);
void append_add(void *a, void *b);
int append_is_empty(void *a);
int append_is_sold_in_all_fil(Append a);
gID *append_dump_month(Append a, int month, int *s);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

typedef struct append
{
    char empty;
    int nVendas[N_FILIAIS];
    Record reg[N_MONTHS];
} * Append;

// ------------------------------------------------------------------------------

void *append_make()
{
    int i;
    Append a = g_malloc(sizeof(struct append));

    for (i = 0; i < N_FILIAIS; i++)
    {
        a->nVendas[i] = 0;
    }

    for (i = 0; i < N_MONTHS; i++)
    {
        a->reg[i] = rec_make();
    }

    a->empty = 1;

    return a;
}

void append_destroy(void *e)
{
    if (!e)
        return;
    int i;
    Append a = (Append)e;

    for (i = 0; i < N_MONTHS; i++)
    {
        rec_destroy(a->reg[i]);
    }

    g_free(a);
}

void append_add(void *a, void *b)
{
    if (a && b)
    {
        gID *d = (gID *)b;
        Append ap = (Append)a;
        ap->nVendas[d[0] - 1]++;
        rec_add(ap->reg[d[1] - 1], d[2]);
        ap->empty = 0;
    }
}

int append_is_empty(void *a)
{
    return ((Append)a)->empty;
}

int append_is_sold_in_all_fil(Append a)
{
    int i, r = 0;

    if (a && !a->empty)
    {
        for (i = 0; i < N_FILIAIS && !r; i++)
        {
            r = max(r, a->nVendas[i]);
        }
    }

    return r;
}

gID *append_dump_month(Append a, int month, int *s)
{
    return rec_dump(a->reg[month - 1], s);
}