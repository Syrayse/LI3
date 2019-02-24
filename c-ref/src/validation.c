/**
 * @file validation.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c VALIDATION.
 **/

#include "validation.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
VRF_OBJ make_vrf (void);
int vrf_obj_str (VRF_OBJ,char*,int);
void destroy_vrf (VRF_OBJ);

/* Metodos privados */
int is_valid_client (char*);
int is_valid_product (char*);
int is_valid_sale (VRF_OBJ,char*);
int is_valid_price (char*);
int is_valid_units (char*);
int is_valid_promo (char*);
int is_valid_month (char*);
int is_valid_filial (char*);

// ------------------------------------------------------------------------------

/**
 * \brief Verifica se x se encontra entre dois limites.
 **/
#define     is_between(x,min,max)   ((x>=min) && (x<=max))

/**
 * \brief Mínimo entre dois números.
 **/
#define     min(a,b)    ((a)<(b)?(a):(b))

// ------------------------------------------------------------------------------

typedef int (*scompare) (char*);

/**
 * \brief Estrutura que armazena o objeto de verificação.
 **/
typedef struct verifier {
    scompare fa[7];             /**< Array que contém a stream de funções de validação */
} *VRF_OBJ;

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
VRF_OBJ make_vrf (void)
{
    VRF_OBJ v = g_malloc(sizeof(struct verifier));
    v->fa[0] = is_valid_product;
    v->fa[1] = is_valid_price;
    v->fa[2] = is_valid_units;
    v->fa[3] = is_valid_promo;
    v->fa[4] = is_valid_client;
    v->fa[5] = is_valid_month;
    v->fa[6] = is_valid_filial;
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
int vrf_obj_str (VRF_OBJ v,char* str, int c)
{

    int r = 0;
    if(v) {
        if (c == -1)
            r = is_valid_sale(v,str);
        else if (is_between(c,0,6)) r = (*v->fa[c])(str);
    }
    return r;
}

/**
 * \brief
 *      Função que um destrói o objeto de verificação.
 * 
 * @param v O objeto de verificação a destruir.
 **/
void destroy_vrf (VRF_OBJ v)
{
    g_free(v);
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de cliente é válida.
 * 
 * @param s A string associada ao cliente.
 * 
 * @returns A validade da string associada ao cliente.
 **/
int is_valid_client (char *s)
{
    return (
        g_ascii_isupper(s[0])          
        && is_between(atoi(s+1),1000,5000)  
        && (s[5] == '\0')              
    );
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de produto é válida.
 * 
 * @param s A string associada ao produto.
 * 
 * @returns A validade da string associada ao produto.
 **/
int is_valid_product (char *s)
{
    return (
        g_ascii_isupper(s[0])
        && g_ascii_isupper(s[1])
        && is_between(atoi(s+2),1000,9999)
        && (s[6] == '\0')
    );
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
int is_valid_sale (VRF_OBJ v, char* s)
    {
        int i,tmp,r = 1;
        char *token = strtok(s,BASE_DELIM);
        
        for (i = 0; r && token && i < 7; i++, token = strtok(NULL,BASE_DELIM)){
            tmp = (*v->fa[i])(token);
            r = min(r,tmp);
        }

        return ( ( token && i >= 7 ) ? 0 : r  );
    }

/**
 * \brief
 *      Função que verifica que a string associada a um preço é válida.
 * 
 * @param s A string associada ao preço.
 * 
 * @returns A validade da string associada ao preço.
 **/
int is_valid_price  (char* s)
{
    return is_between(atof(s),0.0,999.99);
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de unidades é válida.
 * 
 * @param s A string associada à unidades.
 * 
 * @returns A validade da string associada à unidades.
 **/
int is_valid_units  (char* s)
{
    return is_between(atoi(s),1,200);
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de promoção é válida.
 * 
 * @param s A string associada à promoção.
 * 
 * @returns A validade da string associada à promoção.
 **/
int is_valid_promo  (char* s)
{
    return (*s == 'N' || *s == 'P');
}
/**
 * \brief
 *      Função que verifica que a string associada a um código de mês é válida.
 * 
 * @param s A string associada à mês.
 * 
 * @returns A validade da string associada à mês.
 **/
int is_valid_month  (char* s)
{
    return is_between(atoi(s),1,12);
}

/**
 * \brief
 *      Função que verifica que a string associada a um código de filial é válida.
 * 
 * @param s A string associada à filial.
 * 
 * @returns A validade da string associada à filial.
 **/
int is_valid_filial (char* s)
{
    return is_between(atoi(s),1,3);
}