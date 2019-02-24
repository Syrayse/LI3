#include "parse.h"
#include "validation.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

// STRUCTS / TYPEDEFS
typedef void (*fchanger)(void*,char*);

typedef struct parser {
    VRF_OBJ verif;
    fchanger fv[7];
    fchanger str_o;
}*PRS_OBJ;

// useful defines
#define min(a,b) ((a)<(b)?(a):(b))

// METODOS PUBLICOS
PRS_OBJ make_prs (void);
int prs_obj_str (PRS_OBJ,void*,char*,int);
void destroy_prs (PRS_OBJ);

// METODOS PRIVADOS
// main
int prs_single_str (PRS_OBJ p, void* s, char* token, int c);
int prs_sale_str (PRS_OBJ p, void* s, char * token);
int prs_client_str (PRS_OBJ p, void* s, char* token);
int prs_product_str (PRS_OBJ p, void* s, char * token);

// sub
void __est_str (void* e, char* str);
void __est_pdct_s (void* e, char* str);
void __est_price_s (void* e, char* str);
void __est_units_s (void* e, char* str);
void __est_promo_s (void* e, char* str);
void __est_clnt_s (void* e, char* str);
void __est_mnth_s (void* e, char* str);
void __est_filial_s (void* e, char* str);

// CODIGO -----------------------------------------------

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

void destroy_prs (PRS_OBJ p)
{
    if(p)
        destroy_vrf(p->verif);
    g_free(p);
}

// private
// main
int prs_sale_str (PRS_OBJ p, void* s, char * token)
{
    int tmp,i,r;
    i = r = 0;

    if(p && token) {
        r = 1;
        for (i = 0; r && token && i < 7; i++, token = strtok(NULL,BASE_DELIM)){
            if((tmp = vrf_obj_str(p->verif,token,i)))
                (*p->fv[i])(s,token);
            r = min(r,tmp);
        }
    }

    return ( token && i>=7 ? 0 : r );
}

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

int prs_product_str (PRS_OBJ p, void* s, char* token)
{
    return prs_single_str(p,s,token,VRF_PRODUCT);
}

int prs_client_str (PRS_OBJ p, void* s, char* token)
{
    return prs_single_str(p,s,token,VRF_CLIENT);
}

PRS_OBJ make_prs (void)
{
    PRS_OBJ p = g_malloc(sizeof(struct parser));
    p->verif = make_vrf();

    // Sub funcs here
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

// sub - enstructures
void __est_str (void* e, char* str)
{
    *((char**)e) = g_strdup(str);
}

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
