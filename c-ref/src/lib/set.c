#include "set.h"
#include "util.h"
#include "gArray.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
StrSet strset_make(freefunc ffkey, freefunc ffvalue, f_maker fm, f_update fu, f_empty fe);
void strset_destroy(StrSet set);
int strset_add(StrSet set, void *elem, void *user_data);
int strset_remove(StrSet set, void *elem);
void strset_foreach(StrSet set, f_foreach fer, void *user_data);
int strset_contains(StrSet set, void *elem);
int strset_size(StrSet set);
void *strset_lookup(StrSet set, void *key);
void *strset_value_of(StrSet set, void *elem);
char **strset_dump_ordered(StrSet set, int *n);
int strset_get_not_init_n(StrSet set);
char **strset_generic_dump(StrSet set, f_foreach ffor, int *n, int flag);
char **strset_dump_if(StrSet set, fcompare fc, int *n);
char **strset_dump_n_ordered(StrSet set, int n);

/* Metodos privados */
static void foreach_add(void *key, void *value, void *user_data);

// ------------------------------------------------------------------------------

typedef struct set
{
    int not_init;
    GHashTable *table;
    f_maker fm;
    f_update fu;
    f_empty fe;
} * StrSet;

// ------------------------------------------------------------------------------

StrSet strset_make(freefunc ffkey, freefunc ffvalue, f_maker fm, f_update fu, f_empty fe)
{
    StrSet set = g_malloc(sizeof(struct set));
    set->not_init = 0;
    set->table = g_hash_table_new_full(g_str_hash, g_str_equal, ffkey, ffvalue);
    set->fm = fm;
    set->fu = fu;
    set->fe = fe;
    return set;
}

void strset_destroy(StrSet set)
{
    if (set)
    {
        g_hash_table_destroy(set->table);
        g_free(set);
    }
}

int strset_get_not_init_n(StrSet set)
{
    return set->not_init;
}

int strset_add(StrSet set, void *elem, void *user_data)
{
    if (!elem)
        return -1;

    int r = 1;
    void *val = NULL;

    if (!(val = g_hash_table_lookup(set->table, elem)))
    {
        if (set->fm)
        {
            val = (*set->fm)();
            set->not_init++;
            g_hash_table_insert(set->table, elem, val);
        }
    }

    if (user_data && set->fu)
    {
        if (set->fe && (*set->fe)(val))
        {
            set->not_init--;
        }

        (*set->fu)(val, user_data);
    }

    return r;
}

int strset_remove(StrSet set, void *elem)
{
    return g_hash_table_remove(set->table, elem);
}

void strset_foreach(StrSet set, void (*fe)(void *, void *, void *), void *user_data)
{
    g_hash_table_foreach(set->table, fe, user_data);
}

int strset_contains(StrSet set, void *elem)
{
    return g_hash_table_contains(set->table, elem);
}

int strset_size(StrSet set)
{
    return g_hash_table_size(set->table);
}

char **strset_dump_ordered(StrSet set, int *n)
{
    return strset_generic_dump(set, foreach_add, n, 0);
}

int strset_update_elem(StrSet set, char *elem, void (*f_up)(void *, void *), void *user_data)
{
    void *tmp;

    if ((tmp = g_hash_table_lookup(set->table, elem)))
    {
        (*f_up)(tmp, user_data);
    }

    return tmp ? 1 : 0;
}

void *strset_lookup(StrSet set, void *key)
{
    return g_hash_table_lookup(set->table, key);
}

void *strset_value_of(StrSet set, void *elem)
{
    return g_hash_table_lookup(set->table, elem);
}

char **strset_generic_dump(StrSet set, f_foreach ffor, int *n, int flag)
{
    char **r;
    GrowingArray ga = garray_make(sizeof(char *), NULL);

    strset_foreach(set, ffor, ga);

    if (!flag)
        garray_sort(ga, mystrcmp);

    r = (char **)garray_dump_elems(ga, NULL, n);

    garray_destroy(ga);

    return r;
}

char **strset_dump_if(StrSet set, fcompare fc, int *n)
{
    char **r;

    GrowingArray ga = garray_make(sizeof(Currier), currier_destroy);

    g_hash_table_foreach(set->table, foreach_add_g_currier, ga);

    if (fc)
        garray_sort(ga, fc);

    r = (char **)garray_dump_elems(ga, uncurry_by_key, n);

    garray_destroy(ga);

    return r;
}

char **strset_dump_n_ordered(StrSet set, int n)
{
    if (n <= 0)
        return NULL;

    int trash;
    char **r;
    GrowingArray ga = garray_make_sized(sizeof(char *), n, NULL);

    strset_foreach(set, foreach_add, ga);

    garray_sort(ga, mystrcmp);

    r = (char **)garray_dump_elems(ga, NULL, &trash);

    garray_destroy(ga);

    return r;
}

static void foreach_add(void *key, void *value, void *user_data)
{
    garray_add((GrowingArray)user_data, g_strdup((char *)key));
}