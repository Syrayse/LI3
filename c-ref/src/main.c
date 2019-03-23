#include "Queries.h"
#include <time.h>
#include <stdio.h>
#include <glib.h>

#define cpu_time(start, end) (((double)(end - start)) / CLOCKS_PER_SEC)
#define show_cpu_time(start, end) (printf("CPU Time:%f\n", cpu_time(start, end)))
#define c_t(start) (show_cpu_time(start, clock()))

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
        for (j = 0; j < 5; j++)
        {
            printf("%s ", r[j]);
        }
        putchar('\n');
        g_free(r);
    }
    c_t(start);

    start = clock();
    printf("free:\n");
    store_destroy(s);
    c_t(start);

    printf("total:\n");
    c_t(defstart);
}