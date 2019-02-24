#include "parse.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

int main ()
{
    int i,r;
    FILE * fp = fopen("tests/Vendas_1M.txt","r");
    PRS_OBJ p = make_prs();
    char buff[100];
    SALE s = make_s();

    i = r = 0;
    if(fp) {
        while( fgets(buff,100,fp) ) {
            if ( prs_obj_str(p,s,buff,PRS_SALE) ) {
                i++;
                destroy_s(s);
                s = make_s();
            }
            else r++;
        }
    }

    destroy_s(s);
    destroy_prs(p);
    fclose(fp);

    printf("Valid:\t\t%d\ninvalid:\t%d\ntotal:\t\t%d\n",i,r,r+i);
}