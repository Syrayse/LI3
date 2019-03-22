#include "CatClients.h"
#include "util.h"
#include "set.h"
#include "append.h"
#include "gArray.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
CatClients CatClients_make();
void CatClients_destroy(CatClients cc);
int CatClients_exists(CatClients cc, char *client);
void CatClients_add_client(CatClients cc, char *client);
void CatClients_add_trans(CatClients cc, char *client, int filial, int month, gID trans_id);
gID *CatClients_drop_trans(CatClients cc, char *client, int month, int *s);
int CatClients_t_not_sold(CatClients cp);
char **CatClients_dump_all_fils(CatClients cp, int *size);

/* Metodos privados */
static void ins_bought_in_all(void *key, void *value, void *user_data);

// ------------------------------------------------------------------------------

typedef struct cat_clients
{
    StrSet clients;
} * CatClients;

// ------------------------------------------------------------------------------

CatClients CatClients_make()
{
    CatClients cc = g_malloc(sizeof(struct cat_clients));

    cc->clients = strset_make(g_free, append_destroy, append_make, append_add, -1);

    return cc;
}

void CatClients_destroy(CatClients cc)
{
    if (cc)
    {
        strset_destroy(cc->clients);
        g_free(cc);
    }
}

int CatClients_exists(CatClients cc, char *client)
{
    return strset_contains(cc->clients, client);
}

void CatClients_add_client(CatClients cc, char *client)
{
    strset_add(cc->clients, client, NULL);
}

void CatClients_add_trans(CatClients cc, char *client, int filial, int month, gID trans_id)
{
    if (is_between(filial, 1, N_FILIAIS) && is_between(month, 1, N_MONTHS))
    {
        gID d[3];
        d[0] = filial;
        d[1] = month;
        d[2] = trans_id;
        strset_add(cc->clients, client, d);
    }
}

gID *CatClients_drop_trans(CatClients cc, char *client, int month, int *s)
{
    gID *r = NULL;
    void *val;

    if ((val = strset_lookup(cc->clients, client)))
    {
        r = append_dump_month((Append)val, month, s);
    }

    return r;
}

int CatClients_t_not_sold(CatClients cp)
{
    return strset_get_not_init_n(cp->clients);
}

char **CatClients_dump_all_fils(CatClients cp, int *size)
{
    char **r;

    GrowingArray g = garray_make(sizeof(char *), NULL);

    strset_foreach(cp->clients, ins_bought_in_all, g);

    garray_sort(g, mystrcmp);

    r = (char **)garray_dump_elems(g, NULL, size);

    garray_destroy(g);

    return r;
}

static void ins_bought_in_all(void *key, void *value, void *user_data)
{
    if (user_data && append_is_sold_in_all_fil((Append)value))
    {
        garray_add((GrowingArray)user_data, key);
    }
}