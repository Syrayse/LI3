#include "validation.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>
#include <time.h>

#define BUFF_SIZE   50

void print_s (SALE s) {
    puts("´´´´´´´´´´´´´´´´´´´´´´´´´´");
    printf("Product %s has bought by %s\n",get_product_s(s),get_client_s(s));
    printf("%d units by the price of %.2lf /unit\n",get_units_s(s),get_price_s(s));
    printf("%d month, %d filial, with promo %c\n",get_month_s(s),get_filial_s(s),get_promo_s(s));
    puts("´´´´´´´´´´´´´´´´´´´´´´´´´´");
}

void doWork() {
    int r,i,tmp,max,bs = BUFF_SIZE;
    r = i = max = 0;
    FILE * fp = fopen("tests/Vendas_1M.txt","r");
    VRF_OBJ v = make_vrf();
    char * buff = g_malloc(sizeof(char)*bs);
    SALE s = make_s();

    if(fp) {
        while ( fgets(buff,bs,fp) ) {
            tmp = strlen(buff);
            max = tmp > max ? tmp : max;
            if ( vrf_obj_str(v,s,buff,VRF_SALE) ) {
                i++;
                destroy_s(s);
                s = make_s();
            }
            else r++;
        }
    }

    g_free(buff);
    destroy_s(s);
    destroy_vrf(v);
    if(fp) fclose(fp);

    printf("biggest line is: %d\n",max);
    printf("Valid:\t\t%d\ninvalid:\t%d\ntotal:\t\t%d\n",i,r,r+i);
}

// CPU TIME
int main (void)
{
    clock_t start,end;
    double cpu_time_used;
    start = clock();
    doWork();
    end = clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("CPU Time:%f\n",cpu_time_used);
    return 0;
}