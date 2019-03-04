/**
 * @file validation.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c VALIDATION.
 **/

#include "validation.h"
#include "sale.h"
#include "vendasman.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
VRF_OBJ make_vrf(void);
int vrf_obj_str(VRF_OBJ, void *, void *, char *, int);
void destroy_vrf(VRF_OBJ);

/* Metodos privados */
int cover_is_valid_sale(VRF_OBJ v, char *s, void *main, void *entry);
int _set_v_client_str_only(char *s, void *entry);
int _set_v_product_str_only(char *s, void *entry);
int _set_sale_valid_client(char *, void *);
int _set_sale_valid_product(char *, void *);
int is_valid_client(char *);
int is_valid_product(char *);
int is_valid_sale(VRF_OBJ, void *, char *);
int is_valid_price(char *, void *);
int is_valid_units(char *, void *);
int is_valid_promo(char *, void *);
int is_valid_month(char *, void *);
int is_valid_filial(char *, void *);

// ------------------------------------------------------------------------------

/**
 * \brief Verifica se x se encontra entre dois limites.
 **/
#define is_between(x, min, max) ((x >= min) && (x <= max))

/**
 * \brief Mínimo entre dois números.
 **/
#define min(a, b) ((a) < (b) ? (a) : (b))

// ------------------------------------------------------------------------------

typedef int (*scompare)(char *, void *);

/**
 * \brief Estrutura que armazena o objeto de verificação.
 **/
typedef struct verifier
{
    scompare fa[7]; /**< Array que contém a stream de funções de validação */
    scompare fv_cl, fv_pct;
} * VRF_OBJ;

// ------------------------------------------------------------------------------

/**
 * \brief Cria um objeto de verificação.
 * 
 * Cria um objeto de verificação que contém um array de funções 
 * de validação que servem de stream para permitir a validação de uma string.
 * este objeto é utilizado de forma a permitir um encadeamento entre verificações sucessivas.
 * Esta ordenado no formato de uma string correspondente a uma venda de forma a permitir
 * uma validação sequencial de cada um dos parametros.
 * 
 * @returns Um objeto de verificação.
 **/
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

/**
 * \brief
 *      Utiliza o objeto de verificação para qualquer uso pretendido.
 * 
 * Utilizado o objeto de verificação de tal forma que, consoante o argumento c é
 * possivél é obter se qualquer uma das string é válida.
 * 
 * @param v Objeto de verificação utilizado.
 * @param str String a verificar.
 * @param c Código indicativo de verificação.
 * 
 * @returns A validade da string segundo c.
 **/
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

/**
 * \brief
 *      Função que um destrói o objeto de verificação.
 * 
 * @param v O objeto de verificação a destruir.
 **/
void destroy_vrf(VRF_OBJ v)
{
    g_free(v);
}

int cover_is_valid_sale(VRF_OBJ v, char *token, void *main, void *entry)
{
    int tmp, r = is_valid_sale(v, entry, token);

    if (r)
    {
        tmp = insert_sale_man((MAN_b)main, (SALE)entry);
        r = min(r, tmp);
    }

    return r;
}

int _set_v_client_str_only(char *token, void *entry)
{
    int r = is_valid_client(token);
    if (r)
        insert_client_man((MAN_b)entry, g_strdup(token));
    return r;
}

int _set_v_product_str_only(char *token, void *entry)
{
    int r = is_valid_product(token);
    if (r)
        insert_product_man((MAN_b)entry, g_strdup(token));
    return r;
}

int _set_sale_valid_client(char *s, void *entry)
{
    int r = is_valid_client(s);
    if (r)
        set_client_s((SALE)entry, s);
    return r;
}

int _set_sale_valid_product(char *s, void *entry)
{
    int r = is_valid_product(s);
    if (r)
        set_product_s((SALE)entry, s);
    return r;
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de cliente é válida.
 * 
 * @param s A string associada ao cliente.
 * 
 * @returns A validade da string associada ao cliente.
 **/
int is_valid_client(char *s)
{
    return (
        g_ascii_isupper(s[0]) && is_between(atoi(s + 1), 1000, 5000) && (s[5] == '\0'));
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de produto é válida.
 * 
 * @param s A string associada ao produto.
 * 
 * @returns A validade da string associada ao produto.
 **/
int is_valid_product(char *s)
{
    return (
        g_ascii_isupper(s[0]) && g_ascii_isupper(s[1]) && is_between(atoi(s + 2), 1000, 9999) && (s[6] == '\0'));
}

/**
 * \brief
 *      Função que verifica se string associada a uma venda é válida.
 * 
 * @param v Objeto de verificação utilizado.
 * @param s A string associada à venda.
 * 
 * @returns A validade da string associada à venda.
 **/
int is_valid_sale(VRF_OBJ v, void *entry, char *token)
{
    int i, tmp, r = 1;

    for (i = 0; r && token && i < 7; i++, token = strtok(NULL, BASE_DELIM))
    {
        tmp = (*v->fa[i])(token, entry);
        r = min(r, tmp);
    }

    return ((token && i >= 7) ? 0 : r);
}

/**
 * \brief
 *      Função que verifica que a string associada a um preço é válida.
 * 
 * @param s A string associada ao preço.
 * 
 * @returns A validade da string associada ao preço.
 **/
int is_valid_price(char *s, void *entry)
{
    float f = atof(s);
    int r = is_between(f, 0.0, 999.99);
    if (r)
        set_price_s((SALE)entry, f);
    return r;
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de unidades é válida.
 * 
 * @param s A string associada à unidades.
 * 
 * @returns A validade da string associada à unidades.
 **/
int is_valid_units(char *s, void *entry)
{
    int r, f = atoi(s);
    r = is_between(f, 1, 200);
    if (r)
        set_units_s((SALE)entry, (unsigned char)f);
    return r;
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de promoção é válida.
 * 
 * @param s A string associada à promoção.
 * 
 * @returns A validade da string associada à promoção.
 **/
int is_valid_promo(char *s, void *entry)
{
    int r = (*s == 'N' || *s == 'P');
    if (r)
        set_promo_s((SALE)entry, *s);
    return r;
}
/**
 * \brief
 *      Função que verifica que a string associada a um código de mês é válida.
 * 
 * @param s A string associada à mês.
 * 
 * @returns A validade da string associada à mês.
 **/
int is_valid_month(char *s, void *entry)
{
    int r, f = atoi(s);
    r = is_between(f, 1, 12);
    if (r)
        set_month_s((SALE)entry, (unsigned char)f);
    return r;
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de filial é válida.
 * 
 * @param s A string associada à filial.
 * 
 * @returns A validade da string associada à filial.
 **/
int is_valid_filial(char *s, void *entry)
{
    int r, f = atoi(s);
    r = is_between(f, 1, 3);
    if (r)
        set_filial_s((SALE)entry, (unsigned char)f);
    return r;
}