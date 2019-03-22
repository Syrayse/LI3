#include "record.h"
#include <glib.h>
#include <stdio.h>
// ------------------------------------------------------------------------------

/* Metodos publicos */
void *rec_make();
void *rec_make_fixed_size(int size);
void rec_destroy(void *e);
void rec_add(Record r, gID id);
gID rec_size(Record r);
gID *rec_dump(Record r, int *n);

/* Metodos privados */
static gID *rec_double(Record r);

// ------------------------------------------------------------------------------

typedef struct record
{
    int used, max;
    gID *record;
} * Record;

// ------------------------------------------------------------------------------

#define INIT_S 3

// ------------------------------------------------------------------------------

void *rec_make()
{
    Record r = g_malloc(sizeof(struct record));
    r->used = 0;
    r->max = INIT_S;
    r->record = g_malloc(sizeof(gID) * INIT_S);
    return r;
}

void *rec_make_fixed_size(int size)
{
    Record r = g_malloc(sizeof(struct record));
    r->used = 0;
    r->max = size;
    r->record = g_malloc(sizeof(gID) * size);
    return r;
}

void rec_destroy(void *e)
{
    Record r;
    if (e)
    {
        r = (Record)e;
        g_free(r->record);
        g_free(r);
    }
}

void rec_add(Record r, gID id)
{
    if (r)
    {
        //printf("used:%d,max:%d\n", r->used, r->max);
        if (r->used >= r->max)
            r->record = rec_double(r);

        r->record[r->used++] = id;
    }
}

gID rec_size(Record r)
{
    return r->used;
}

gID *rec_dump(Record r, int *n)
{
    *n = r->used;
    return g_memdup(r->record, sizeof(gID) * r->used);
}

static gID *rec_double(Record r)
{
    r->max *= 2;
    return g_realloc(r->record, sizeof(gID) * r->max);
}