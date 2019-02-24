#include "parse.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

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
    int i,r;
    FILE * fp = fopen("tests/products1.txt","r");
    PRS_OBJ p = make_prs();
    char buff[100];
    char *v;
    SALE s = make_s();

    i = r = 0;
    if(fp) {
        while( fgets(buff,100,fp) ) {
            if ( prs_obj_str(p,&v,buff,PRS_PRODUCT) ) {
                i++;
                //printf("!%s!\n",v);
                //print_s(s);
                free(v);
                //destroy_s(s);
                //s = make_s();
            }
            else r++;
        }
    }

    destroy_s(s);
    destroy_prs(p);
    fclose(fp);

    printf("Valid:\t\t%d\ninvalid:\t%d\ntotal:\t\t%d\n",i,r,r+i);
}
