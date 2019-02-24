#include "validation.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

int main () {
    int i,n,k;
    i = n = k = 0;
    char str[1000];

    VRF_OBJ v = make_vrf();
    FILE *fp = fopen("tests/1m_sell2.txt","r");
    
    while( fgets(str,1000,fp) ){
        if ( vrf_obj_str(v,str,VRF_SALE) )
            ++i;
        else ++n;
    }
    
    printf("valid:\t\t%d\ninvalid:\t%d\ntotal:\t\t%d\n",i,n,n+i);

    destroy_vrf(v);
}