#include "validation.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

#define BUFF_SIZE   50

void print_s (SALE s) {
    puts("´´´´´´´´´´´´´´´´´´´´´´´´´´");
    printf("Product %s has bought by %s\n",get_product_s(s),get_client_s(s));
    printf("%d units by the price of %.2lf /unit\n",get_units_s(s),get_price_s(s));
    printf("%d month, %d filial, with promo %c\n",get_month_s(s),get_filial_s(s),get_promo_s(s));
    puts("´´´´´´´´´´´´´´´´´´´´´´´´´´");
}

/*
De momento a unica coisa que isto faz é ler de um dado ficheiro
e à medida que lê cada linha, constroi uma estrutura de dados correspondente.
e depois destroi.

Com isto é possivel verificar que atualmente o nosso código é capaz de:
    1) Verificar a validez de qualquer cliente/produto/venda.
    2) Criar uma estrutura correspondente a cada um destes itens

Porém de momento ainda não existe nenhuma estrutura que mantém e conseguia fazer a gestão
destas estruturas e as relações entre elas

Falta verificar se as vendas e clientes existem
talvez usar hashtables? Noutro módulo?
*/

int main ()
{

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
    fclose(fp);

    printf("biggest line is: %d\n",max);
    printf("Valid:\t\t%d\ninvalid:\t%d\ntotal:\t\t%d\n",i,r,r+i);
}
