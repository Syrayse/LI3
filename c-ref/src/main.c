#include "validation.h"
#include "sale.h"
#include "vendasman.h"
#include <glib.h>
#include <stdio.h>
#include <time.h>

#define BUFF_SIZE 50

void print_s(SALE s)
{
    puts("´´´´´´´´´´´´´´´´´´´´´´´´´´");
    printf("Product %s has bought by %s\n", get_product_s(s), get_client_s(s));
    printf("%d units by the price of %.2lf /unit\n", get_units_s(s), get_price_s(s));
    printf("%d month, %d filial, with promo %c\n", get_month_s(s), get_filial_s(s), get_promo_s(s));
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

void gettfile(MAN_b m, VRF_OBJ v, char *file, int flag)
{
    char buff[50];
    FILE *fp = fopen(file, "r");
    if (fp)
    {
        while (fgets(buff, 50, fp))
            vrf_obj_str(v, m, NULL, buff, flag);

        fclose(fp);
    }
}

void getvendas(MAN_b m, VRF_OBJ v, char *file)
{
    int tmp, max = 0;
    char buff[100];
    FILE *fp = fopen(file, "r");
    SALE s = make_s();

    if (fp)
    {

        while (fgets(buff, 100, fp))
        {
            tmp = strlen(buff);
            max = tmp > max ? tmp : max;

            vrf_obj_str(v, m, s, buff, VRF_SALE);

            clean_s(s);
        }

        set_maior_linha(m, max);

        fclose(fp);

        destroy_s(s);
    }
}

void doWork()
{
    MAN_b m = make_man();
    VRF_OBJ v = make_vrf();

    gettfile(m, v, "tests/Produtos.txt", VRF_PRODUCT);

    gettfile(m, v, "tests/Clientes.txt", VRF_CLIENT);

    getvendas(m, v, "tests/Vendas_1M.txt");

    show_boletim_vendas(m);

    destroy_man(m);
    destroy_vrf(v);
}

// CPU TIME
int main(void)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    doWork();
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time:%f\n", cpu_time_used);
    return 0;
}
