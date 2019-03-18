#include "validation.h"
#include "sale.h"
#include "statinfo.h"
#include "vendasman.h"
#include <glib.h>
#include <stdio.h>
#include <time.h>

#define BUFF_SIZE 50

#define cpu_time(start, end) (((double)(end - start)) / CLOCKS_PER_SEC)
#define show_cpu_time(start, end) (printf("CPU Time:%f\n", cpu_time(start, end)))
#define c_t(start) (show_cpu_time(start, clock()))

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
    Sale s = sale_make();

    if (fp)
    {

        while (fgets(buff, 100, fp))
        {
            tmp = strlen(buff);
            max = tmp > max ? tmp : max;

            vrf_obj_str(v, m, s, buff, VRF_SALE);

            sale_wipe(s);
        }

        set_maior_linha(m, max);

        fclose(fp);

        sale_destroy(s);
    }
}

MAN_b doWork(char *produtos, char *clientes, char *vendas)
{
    MAN_b m = make_man();
    VRF_OBJ v = make_vrf();

    gettfile(m, v, produtos, VRF_PRODUCT);

    gettfile(m, v, clientes, VRF_CLIENT);

    getvendas(m, v, vendas);

    destroy_vrf(v);

    return m;
}

MAN_b tarefa1(int argc, char **argv)
{
    MAN_b m = NULL;

    if (argc >= 4)
    {
        char *produtos = argv[1];
        char *clientes = argv[2];
        char *vendas = argv[3];
        m = doWork(produtos, clientes, vendas);
    }
    else
    {
        m = doWork("tests/Produtos.txt", "tests/Clientes.txt", "tests/Vendas_1M.txt");
    }

    return m;
}

void tarefa2(MAN_b mn)
{
    int i, j;
    char **arr;
    size_t n = 0;

    for (i = 0; i < 26; i++)
    {
        arr = get_ordered_dbase_dump_products(mn, &n, 'A' + i);
        printf("\t%c: size -> %ld\n", 'A' + i, n);
        printf("\tExamples: ");
        for (j = 0; j < n && j < 5; j++)
            printf("%s ", arr[j]);
        putchar('\n');
        g_free(arr);
    }
}

void tarefa3(MAN_b mn, char *product)
{
    StatInfo si = search_product(mn, product);

    if (si)
    {
        printf("\tProduct:\t%s\n", product);
        printf("\tVendas:\t\t%d\n", get_t_vendas(si));
        printf("\tRevenue:\t%f\n", get_t_rev(si));
        printf("\tBuyers:\t\t%d\n", get_n_actors(si));
    }
}

void tarefa4(MAN_b mn)
{
    int i, j;
    size_t n = 0;
    char **r = get_products_not_bought(mn, &n, 0);
    printf("\tIn total %ld products were not bought, examples: ", n);

    for (i = 0; i < n && i < 5; i++)
        printf("%s ", r[i]);
    putchar('\n');

    for (i = 1; i <= 3; i++)
    {
        r = get_products_not_bought(mn, &n, i);
        printf("\tfilial %d, %ld not bought, examples: ", i, n);
        for (j = 0; j < n && j < 5; j++)
            printf("%s ", r[j]);
        putchar('\n');
    }
}

void tarefa5(MAN_b mn)
{
    int i;
    size_t n = 0;
    char **r = get_clients_not_buying(mn, &n);
    printf("\tIn total %ld clients didn't buy, examples: ", n);

    for (i = 0; i < n && i < 5; i++)
        printf("%s ", r[i]);

    putchar('\n');
}

void tarefa6(MAN_b mn)
{
    printf("\tIn total %d products didn't sell\n", get_not_sold_product(mn));
    printf("\tIn total %d clients didn't buy\n", get_not_sold_client(mn));
}

void tarefa7(MAN_b mn, char *client)
{
    int i, j, r;
    StatInfo si = search_client(mn, client);

    for (i = 1; i <= N_FILIAIS; i++)
    {
        for (j = 1; j <= N_MONTHS; j++)
        {
            r = get_t_month_fil_vendas(si, j, i);
            if (r)
            {
                printf("\tmes %d filial %d bought %d!\n", j, i, r);
            }
        }
        putchar('\n');
    }

    for (j = 1; j <= N_MONTHS; j++)
    {
        printf("\tmes %d bought %d!\n", j, get_t_month_vendas(si, j));
    }
}

void tarefa8(MAN_b mn, int init, int max)
{
    printf("\tEntre %d e %d houve %d vendas registadas\n", init, max, get_n_vendas_range(mn, init, max));
    printf("\tEntre %d e %d facturou-se %lf!\n", init, max, get_n_faturacao_range(mn, init, max));
}

// CPU TIME && Ler ficheiros
int main(int argc, char **argv)
{
    MAN_b m;
    clock_t defstart, start;

    defstart = start = clock();

    m = tarefa1(argc, argv);
    printf("tarefa 1:\t");
    show_cpu_time(start, clock());

    start = clock();
    tarefa2(m);
    printf("tarefa 2:\t");
    c_t(start);

    start = clock();
    tarefa3(m, "NR1091");
    printf("tarefa 3:\t");
    c_t(start);

    start = clock();
    tarefa4(m);
    printf("tarefa 4:\t");
    c_t(start);

    start = clock();
    tarefa5(m);
    printf("tarefa 5:\t");
    c_t(start);

    start = clock();
    tarefa6(m);
    printf("tarefa 6:\t");
    c_t(start);

    start = clock();
    tarefa7(m, "Z5000");
    printf("tarefa 7:\t");
    c_t(start);

    start = clock();
    tarefa8(m, 1, 3);
    printf("tarefa 8:\t");
    c_t(start);

    start = clock();
    destroy_man(m);
    printf("destroy:\t");
    c_t(start);

    printf("total:\t\t");
    c_t(defstart);
    return 0;
}