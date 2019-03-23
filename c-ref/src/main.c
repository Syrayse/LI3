#include "Queries.h"
#include "statinfo.h"
#include <time.h>
#include <stdio.h>
#include <glib.h>

#define cpu_time(start, end) (((double)(end - start)) / CLOCKS_PER_SEC)
#define show_cpu_time(start, end) (printf("CPU Time:%f\n", cpu_time(start, end)))
#define c_t(start) (show_cpu_time(start, clock()))

void show_statinfo(StatInfo si, int month)
{
    if (si)
    {
        int i;
        printf("\n\tMonth %d\n", month);
        for (i = 1; i <= N_FILIAIS; i++)
        {
            printf("\tFor filial %d:\n", i);
            printf("\t\tSales, Promo %d, No Promo %d\n", get_t_month_fil_vendas_promo(si, month, i), get_t_month_fil_vendas_no_promo(si, month, i));
            printf("\t\tRevenue, Promo %f, No Promo %f\n", get_t_month_fil_rev_promo(si, month, i), get_t_month_fil_rev_no_promo(si, month, i));
        }

        printf("\tIn all:\n");
        printf("\t\tSales, Promo %d, No Promo %d\n", get_t_month_vendas_promo(si, month), get_t_month_vendas_no_promo(si, month));
        printf("\t\tRevenue, Promo %f, No Promo %f\n", get_t_month_rev_promo(si, month), get_t_month_rev_no_promo(si, month));
        statinfo_destroy(si);
    }
}

int main(int argc, char *argv[])
{
    Store s = store_make();

    int i, j, size = 0;
    char **r;
    clock_t defstart, start;

    defstart = start = clock();
    printf("query1:\n");
    store_query1(s, argc, argv);
    c_t(start);

    start = clock();
    printf("query2:\n");
    for (i = 0; i < 26; i++)
    {
        r = store_query2(s, &size, 'A' + i);
        printf("\t%c -> %d\n\texamples: ", 'A' + i, size);
        for (j = 0; j < 5 && j < size; j++)
        {
            printf("%s ", r[j]);
        }
        putchar('\n');
        g_free(r);
    }
    c_t(start);

    start = clock();
    printf("query3:");
    show_statinfo(store_query3(s, "AF1184"), 6);
    c_t(start);

    start = clock();
    printf("query4:");
    r = store_query4(s, 0, &size);
    printf("\tIn total weren\'t bought %d, examples: ", size);

    for (j = 0; j < 5 && j < size; j++)
    {
        printf("%s ", r[j]);
    }
    putchar('\n');

    for (i = 1; i <= N_FILIAIS; i++)
    {
        r = store_query4(s, i, &size);
        printf("\tFilial %d, weren\'t bought %d, examples: ", i, size);
        for (j = 0; j < 5 && j < size; j++)
        {
            printf("%s ", r[j]);
        }
        putchar('\n');
    }
    c_t(start);

    start = clock();
    printf("free:\n");
    store_destroy(s);
    c_t(start);

    printf("total:\n");
    c_t(defstart);
}