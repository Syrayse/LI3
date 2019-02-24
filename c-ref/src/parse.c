/**
 * @file sale.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c SALE.
 **/

#include "parse.h"
#include "validation.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
PRS_OBJ make_prs (void);
int prs_obj_str (PRS_OBJ,void*,char*,int);
void destroy_prs (PRS_OBJ);

/* Metodos privados */
int prs_single_str (PRS_OBJ p, void* s, char* token, int c);
int prs_sale_str (PRS_OBJ p, void* s, char * token);
int prs_client_str (PRS_OBJ p, void* s, char* token);
int prs_product_str (PRS_OBJ p, void* s, char * token);
void __est_str (void* e, char* str);
void __est_pdct_s (void* e, char* str);
void __est_price_s (void* e, char* str);
void __est_units_s (void* e, char* str);
void __est_promo_s (void* e, char* str);
void __est_clnt_s (void* e, char* str);
void __est_mnth_s (void* e, char* str);
void __est_filial_s (void* e, char* str);

// ------------------------------------------------------------------------------

/**
 * \brief Mínimo entre dois números.
 **/
#define min(a,b) ((a)<(b)?(a):(b))

// ------------------------------------------------------------------------------

/**
 * \brief Facilita a utilização de uma função de ordem superior.
 **/
typedef void (*fchanger)(void*,char*);

typedef struct parser {
    VRF_OBJ verif;      /**< Objeto de verificaçao */
    fchanger fv[7];     /**< Stream de funções de alteração, para serem futuramente encadeadas */
    fchanger str_o;     /**< Função de alteração auxiliar, para casos para além das vendas*/
}*PRS_OBJ;

// ------------------------------------------------------------------------------

/**
 * \brief Cria um objeto de parsing.
 * 
 * As funções na Stream de funções de alteração ficam ordenadas na ordem duma string de venda.
 * 
 * @returns O objeto de parsing criado.
 **/
PRS_OBJ make_prs (void)
{
    PRS_OBJ p = g_malloc(sizeof(struct parser));
    p->verif = make_vrf();

    // Atribuição de funções a cada posição do array.
    p->str_o = __est_str;
    p->fv[0] = __est_pdct_s;
    p->fv[1] = __est_price_s;
    p->fv[2] = __est_units_s;
    p->fv[3] = __est_promo_s;
    p->fv[4] = __est_clnt_s;
    p->fv[5] = __est_mnth_s;
    p->fv[6] = __est_filial_s;
    return p;
}

/**
 * \brief Faz parse de uma dada string e salva a informação lida.
 * 
 * Importante denotar que existem três flags às quais um utilizador deste interface tem acesso
 * que se encontram descritas em parse.h.
 * 
 * Esta função permite fazer parse de clientes,produtos e registos de venda. Sendo que após
 * ser passada a string, consoante a flag é passado como argumento das sub-funções de verificação
 * um token que contém o primeiro elemento encontrado consoante os delimatores base.
 * 
 * @param p Objeto de parsing utilizado.
 * @param entry Lugar onde irá ser guardada a informção obtida.
 * @param str String à qual se vai aplicar o parse.
 * @param flag Indica o tipo de conteúdo da string.
 * 
 * @returns Um booleano indicativo da validade da str consoante o que pretendia segundo a flag.
 * 
 * @see parse.h
 * @see prs_product_str
 * @see prs_sale_str
 * @see prs_client_str
 * @see PRS_PRODUCT
 * @see PRS_SALE
 * @see PRS_CLIENT
 * @see BASE_DELIM
 **/
int prs_obj_str (PRS_OBJ p, void* entry, char* str, int flag)
{
    int r = 0;
    char*token;

    if(p && entry && flag >= -1 && flag <= 1) {
        token = strtok(str,BASE_DELIM);
        switch(flag) {
            case -1: r = prs_product_str(p,entry,token); break;
            case 0: r = prs_sale_str(p,entry,token); break;
            case 1: r = prs_client_str(p,entry,token); break;
        }
    }

    return r;
}

/**
 * \brief Destrói um objeto de parsing. 
 **/
void destroy_prs (PRS_OBJ p)
{
    if(p)
        destroy_vrf(p->verif);
    g_free(p);
}

/**
 * \brief Efetua parse de um registo de venda.
 * 
 * A função utilza o objeto de verificação para a cada momento obter
 * se o token corrente é válido consoante o que se pretende naquela posição,
 * se o mesmo for válido então este vai ser colocado no endereço onde é guardada a informação.
 * Permitindo assim criar um estrutura em concreto através da verificação e construção em cascata.
 * 
 * @param p Objeto de parsing utilizado.
 * @param s Endereço onde é colocada a informação.
 * @param token Aponta para o primeira elemento da string de venda.
 * 
 * @returns A validade da string que se acabou de ler.
 * 
 * @see vrf_obj_str
 * @see BASE_DELIM
 **/
int prs_sale_str (PRS_OBJ p, void* s, char * token)
{
    int tmp,i,r;
    i = r = 0;

    if(p && token) {
        r = 1;
        for (i = 0; r && token && i < 7; i++, token = strtok(NULL,BASE_DELIM)){
            if((tmp = vrf_obj_str(p->verif,token,i)))   // Verifica se o objeto é válido.
                (*p->fv[i])(s,token);   // Aplica a função de alteração.
            r = min(r,tmp);
        }
    }

    // Contempla o caso em que a string da qual se pretende fazer parse tem mais do que 7 tokens.
    // Acho que falta o caso em que a string tem tokens a menos?????????
    return ( token && i>=7 ? 0 : r );
}

/**
 * \brief Função que assume que se pretende ler uma única letra, consoante uma flag.
 * 
 * @param p Objeto de parsing.
 * @param s Endereço onde é colocada a informação.
 * @param token Aponta para o primeiro elemento da string que se pretende avaliar.
 * @param c Flag que indica que tipo de dados se pretender verificar.
 * 
 * @returns A validade da string lida consoante a flag. 
 **/
int prs_single_str (PRS_OBJ p, void* s, char* token, int c)
{
    int r = 0;

    if(p && token) {
        r = vrf_obj_str(p->verif,token,c);
        if (r) (*p->str_o)(s,token);
        token = strtok(NULL,BASE_DELIM);
    }

    return (token ? 0 : r);
}

/**
 * \brief Verifica se uma string corresponde a código de produto válido.
 * 
 * @param p Objeto de parsing-
 * @param s Endereço onde é colocada a informação.
 * @param token Aponta para o primeiro elemento da string que se pretende avaliar.
 * 
 * @returns A validade da string como um código de produto.
 **/
int prs_product_str (PRS_OBJ p, void* s, char* token)
{
    return prs_single_str(p,s,token,VRF_PRODUCT);
}

/**
 * \brief Verifica se uma string corresponde a código de cliente válido.
 * 
 * @param p Objeto de parsing-
 * @param s Endereço onde é colocada a informação.
 * @param token Aponta para o primeiro elemento da string que se pretende avaliar.
 * 
 * @returns A validade da string como um código de cliente.
 **/
int prs_client_str (PRS_OBJ p, void* s, char* token)
{
    return prs_single_str(p,s,token,VRF_CLIENT);
}

/**
 * \brief Guarda em @ e uma cópia duma string.
 * 
 * @param e Endereço onde é colocada a informação.
 * @param str String da qual se pretende obter uma cópia.
 **/
void __est_str (void* e, char* str)
{
    *((char**)e) = g_strdup(str);
}

// As funções abaixo fazem a conversão adequada às funções presentes no módulo SALE.
void __est_pdct_s (void* e, char* str)
{
    set_product_s((SALE)e,str);
}

void __est_price_s (void* e, char* str)
{
    set_price_s((SALE)e,atof(str));
}

void __est_units_s (void* e, char* str)
{
    set_units_s((SALE)e,(unsigned char)atoi(str));
}

void __est_promo_s (void* e, char* str)
{
    set_promo_s((SALE)e,*str);
}

void __est_clnt_s (void* e, char* str)
{
    set_client_s((SALE)e,str);
}

void __est_mnth_s (void* e, char* str)
{
    set_month_s((SALE)e,(unsigned char)atoi(str));
}

void __est_filial_s (void* e, char* str)
{
    set_filial_s((SALE)e,(unsigned char)atoi(str));
}