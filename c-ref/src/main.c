#include "validation.h"
#include "sale.h"
#include "vendasman.h"
#include <glib.h>
#include <stdio.h>
#include <time.h>

#define BUFF_SIZE 50

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

void doWork(char *produtos, char *clientes, char *vendas)
{
    MAN_b m = make_man();
    VRF_OBJ v = make_vrf();

    gettfile(m, v, produtos, VRF_PRODUCT);

    gettfile(m, v, clientes, VRF_CLIENT);

    getvendas(m, v, vendas);

    show_boletim_vendas(m);

    destroy_man(m);
    destroy_vrf(v);
}

// CPU TIME && Ler ficheiros
int main(int argc, char **argv)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    if (argc >= 4)
    {
        char *produtos = argv[1];
        char *clientes = argv[2];
        char *vendas = argv[3];
        doWork(produtos, clientes, vendas);
    }
    else
    {
        doWork("tests/Produtos.txt", "tests/Clientes.txt", "tests/Vendas_1M.txt");
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time:%f\n", cpu_time_used);
    return 0;
}