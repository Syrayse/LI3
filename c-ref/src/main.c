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

    int N = 6; //O número + vendidos

    int i, j, **m, n1, n2, size = 0;
    char **r;
    clock_t defstart, start;
    double tot;

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
    printf("query4:\n");
    r = store_query4(s, 0, &size);
    printf("\tIn total weren\'t bought %d, examples: ", size);
    for (j = 0; j < 5 && j < size; j++)
    {
        printf("%s ", r[j]);
    }
    putchar('\n');
    g_free(r);
    for (i = 1; i <= N_FILIAIS; i++)
    {
        r = store_query4(s, i, &size);
        printf("\tFilial %d, weren\'t bought %d, examples: ", i, size);
        for (j = 0; j < 5 && j < size; j++)
        {
            printf("%s ", r[j]);
        }
        putchar('\n');
        g_free(r);
    }
    c_t(start);

    start = clock();
    printf("query5:\n");
    r = store_query5(s, &size);
    printf("\tA total of %d clients bought in all, examples: ", size);
    for (i = 0; i < 5 && i < size; i++)
    {
        printf("%s ", r[i]);
    }
    putchar('\n');
    g_free(r);
    c_t(start);

    start = clock();
    printf("query6:\n");
    store_query6(s, &i, &j);
    printf("\tA total of %d clients didn\'t buy\n", i);
    printf("\tA total of %d products weren\'t sold\n", j);
    c_t(start);

    start = clock();
    printf("query7:\n");
    m = store_query7(s, "Z5000");
    if (m)
    {
        puts("\t\t|1|\t|2|\t|3|\n");
        for (i = 0; i < N_MONTHS; i++)
        {
            printf("\tmes%d\t%d\t%d\t%d\n", i + 1, m[0][i], m[1][i], m[2][i]);
        }
    }
    for (i = 0; i < N_FILIAIS; i++)
    {
        g_free(m[i]);
    }
    g_free(m);
    c_t(start);

    start = clock();
    printf("query8:\n");
    store_query8(s, 1, 3, &i, &tot);
    printf("\tIn the range [1,3], %d transactions were registred\n", i);
    printf("\tIn the range [1,3], the cashflow was %f\n", tot);
    c_t(start);

    start = clock();
    printf("query9:\n");
    char **holder[N_PROMOS];
    store_query9(s, "AF1184", holder, &n1, &n2, 2);
    printf("\t-> %d For transactions without promotion, examples: ", n1);
    for (i = 0; i < 5 && i < n1; i++)
    {
        printf("%s ", holder[0][i]);
    }
    putchar('\n');
    printf("\t-> %d For transactions with promotion, examples: ", n2);
    for (i = 0; i < 5 && i < n2; i++)
    {
        printf("%s ", holder[1][i]);
    }
    putchar('\n');
    c_t(start);

    start = clock();
    printf("Query 11:\n");
    r=(char**)store_query11(s, N);
    for (i = 0; i < N; i++)
        printf("O produto %s, foi o %dº mais vendido\n", r[i], i+1);

    putchar('\n');
    c_t(start);

    start = clock();
    printf("free:\n");
    store_destroy(s);
    c_t(start);

    printf("total:\n");
    c_t(defstart);
}