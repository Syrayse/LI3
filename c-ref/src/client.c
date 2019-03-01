#include "client.h"
#include <glib.h>
#include <gmodule.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
ATOM make_atom(char *);
void destroy_atom(ATOM);

void insert_atom(ATOM);

int get_hist_size(ATOM);
char *get_atom_name(ATOM);
guint get_hash_name(ATOM);

/* Metodos privados */
int compare_str(const void *, const void *);
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------

typedef struct atom
{
    char *name;
    GTree *hist;
} * ATOM;

// ------------------------------------------------------------------------------

ATOM make_atom(char *name)
{
    ATOM r = g_malloc(sizeof(struct atom));
    r->name = g_strdup(name);
    r->hist = g_tree_new(compare_str);
    return r;
}

void destroy_atom(ATOM a)
{
    if (a)
    {
        g_free(a->name);
        g_tree_destroy(a->hist);
        g_free(a);
    }
}

int get_hist_size(ATOM a)
{
    return g_tree_nnodes(a->hist);
}

char *get_atom_name(ATOM a)
{
    return g_strdup(a->name);
}

guint get_hash_atom(ATOM a)
{
    return g_str_hash(a->name);
}

int compare_str(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}