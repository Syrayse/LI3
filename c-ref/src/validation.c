#include "validation.h"
#include <glib.h>
#include <stdio.h>

typedef int (*scompare) (char*);

typedef struct verifier {
    scompare fa[7];
} *VRF_OBJ;

// USEFUL MACROS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define     is_between(x,min,max)   ((x>=min) && (x<=max))
#define     min(a,b)    ((a)<(b)?(a):(b))

// Public methods
VRF_OBJ make_vrf (void);
int vrf_obj_str (VRF_OBJ,char*,int);
void destroy_vrf (VRF_OBJ);

// Private METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int is_valid_client (char*);
int is_valid_product (char*);
int is_valid_sale (VRF_OBJ,char*);
int is_valid_price (char*);
int is_valid_units (char*);
int is_valid_promo (char*);
int is_valid_month (char*);
int is_valid_filial (char*);

// CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

int vrf_obj_str (VRF_OBJ v,char* str, int c)
{

    int r = 0;
    if(v) {
        switch(c) {
            case 0: r = (*v->fa[4])(str); break;
            case 1: r = (*v->fa[0])(str); break;
            case 2: r = is_valid_sale(v,str); break;
        }
    }
    return r;
}

void destroy_vrf (VRF_OBJ v)
{
    g_free(v);
}

int is_valid_client (char *s)
{
    return (
        g_ascii_isupper(s[0])          
        && is_between(atoi(s+1),1000,5000)  
        && (s[5] == '\0')              
    );
}

int is_valid_product (char *s)
{
    return (
        g_ascii_isupper(s[0])
        && g_ascii_isupper(s[1])
        && is_between(atoi(s+2),1000,9999)
        && (s[6] == '\0')
    );
}
int is_valid_sale (VRF_OBJ v, char* s)
    {
        int i,tmp,r = 1;
        char *token = strtok(s," \n");
        
        for (i = 0; r && token && i < 7; i++, token = strtok(NULL," \n")){
            tmp = (*v->fa[i])(token);
            r = min(r,tmp);
        }

        return ( ( token && i >= 7 ) ? 0 : r  );
    }

// Private
int is_valid_price  (char* s)
{
    return is_between(atof(s),0.0,999.99);
}

int is_valid_units  (char* s)
{
    return is_between(atoi(s),1,200);
}

int is_valid_promo  (char* s)
{
    return (*s == 'N' || *s == 'P');
}

int is_valid_month  (char* s)
{
    return is_between(atoi(s),1,12);
}

int is_valid_filial (char* s)
{
    return is_between(atoi(s),1,3);
}