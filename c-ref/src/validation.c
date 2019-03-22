/**
 * @file validation.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c VALIDATION.
 **/

#include "validation.h"
#include "vendasman.h"
#include "util.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
VRF_OBJ make_vrf(void);
int vrf_obj_str(VRF_OBJ, void *, void *, char *, int);
void destroy_vrf(VRF_OBJ);
int validate_s(DBase, DBase, Sale);

/* Metodos privados */
static int cover_is_valid_sale(VRF_OBJ v, char *s, void *main, void *entry);
static int _set_v_client_str_only(char *s, void *entry);
static int _set_v_product_str_only(char *s, void *entry);
static int _set_sale_valid_client(char *, void *);
static int _set_sale_valid_product(char *, void *);
static int is_valid_client(char *);
static int is_valid_product(char *);
static int is_valid_sale(VRF_OBJ, void *, char *);
static int is_valid_price(char *, void *);
static int is_valid_units(char *, void *);
static int is_valid_promo(char *, void *);
static int is_valid_month(char *, void *);
static int is_valid_filial(char *, void *);

// ------------------------------------------------------------------------------

typedef int (*scompare)(char *, void *);

typedef struct verifier
{
    scompare fa[7]; /**< Array que contém a stream de funções de validação */
    scompare fv_cl, fv_pct;
} * VRF_OBJ;

// ------------------------------------------------------------------------------

VRF_OBJ make_vrf(void)
{
    VRF_OBJ v = g_malloc(sizeof(struct verifier));
    v->fa[0] = _set_sale_valid_product;
    v->fa[1] = is_valid_price;
    v->fa[2] = is_valid_units;
    v->fa[3] = is_valid_promo;
    v->fa[4] = _set_sale_valid_client;
    v->fa[5] = is_valid_month;
    v->fa[6] = is_valid_filial;
    v->fv_cl = _set_v_client_str_only;
    v->fv_pct = _set_v_product_str_only;
    return v;
}

int vrf_obj_str(VRF_OBJ v, void *main, void *entry, char *str, int c)
{

    int r = 0;
    char *token;
    if (v && is_between(c, -1, 1))
    {
        token = strtok(str, BASE_DELIM);
        switch (c)
        {
        case -1:
            r = cover_is_valid_sale(v, token, main, entry);
            break;
        case 0:
            r = (*v->fv_pct)(token, main);
            break;
        case 1:
            r = (*v->fv_cl)(token, main);
            break;
        }
    }
    return r;
}

void destroy_vrf(VRF_OBJ v)
{
    g_free(v);
}

int validate_s(DBase products, DBase clients, Sale s)
{
    return sale_paralel_proc(products, clients, s, dbase_contains, dbase_contains);
}

static int cover_is_valid_sale(VRF_OBJ v, char *token, void *main, void *entry)
{
    int tmp, r = is_valid_sale(v, entry, token);

    if (r)
    {
        tmp = insert_sale_man((MAN_b)main, (Sale)entry);
        r = min(r, tmp);
    }

    return r;
}

static int _set_v_client_str_only(char *token, void *entry)
{
    int r = is_valid_client(token);
    if (r)
        insert_client_man((MAN_b)entry, g_strdup(token));
    return r;
}

static int _set_v_product_str_only(char *token, void *entry)
{
    int r = is_valid_product(token);
    if (r)
        insert_product_man((MAN_b)entry, g_strdup(token));
    return r;
}

static int _set_sale_valid_client(char *s, void *entry)
{
    int r = is_valid_client(s);
    if (r)
        sale_set_client((Sale)entry, s);
    return r;
}

static int _set_sale_valid_product(char *s, void *entry)
{
    int r = is_valid_product(s);
    if (r)
        sale_set_product((Sale)entry, s);
    return r;
}

static int is_valid_client(char *s)
{
    return (g_ascii_isupper(s[0]) && is_between(atoi(s + 1), 1000, 5000) && (s[5] == '\0'));
}

static int is_valid_product(char *s)
{
    return (g_ascii_isupper(s[0]) && g_ascii_isupper(s[1]) && is_between(atoi(s + 2), 1000, 9999) && (s[6] == '\0'));
}

static int is_valid_sale(VRF_OBJ v, void *entry, char *token)
{
    int i, tmp, r = 1;

    for (i = 0; r && token && i < 7; i++, token = strtok(NULL, BASE_DELIM))
    {
        tmp = (*v->fa[i])(token, entry);
        r = min(r, tmp);
    }

    return ((token && i >= 7) ? 0 : r);
}

static int is_valid_price(char *s, void *entry)
{
    double f = (double)atof(s);
    int r = is_between(f, 0.0, 999.99);
    if (r)
        sale_set_price((Sale)entry, f);
    return r;
}

static int is_valid_units(char *s, void *entry)
{
    int r, f = atoi(s);
    r = is_between(f, 1, 200);
    if (r)
        sale_set_units((Sale)entry, f);
    return r;
}

static int is_valid_promo(char *s, void *entry)
{
    int r = (*s == 'N' || *s == 'P');
    if (r)
        sale_set_promo((Sale)entry, *s);
    return r;
}

static int is_valid_month(char *s, void *entry)
{
    int r, f = atoi(s);
    r = is_between(f, 1, 12);
    if (r)
        sale_set_month((Sale)entry, f);
    return r;
}

static int is_valid_filial(char *s, void *entry)
{
    int r, f = atoi(s);
    r = is_between(f, 1, 3);
    if (r)
        sale_set_filial((Sale)entry, f);
    return r;
}