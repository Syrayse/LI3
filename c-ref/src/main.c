/**
 * @file manin.c
 * \brief testfile.
 */

#include "CatProducts.h"
#include "CatClients.h"
#include "FilManager.h"
#include "Accounting.h"
#include "Transaction.h"
#include "Verifier.h"
#include "Queries.h"
#include <glib.h>
#include <time.h>
#include <stdio.h>
#include <TAD_List.h>
#include <stdlib.h>

#define cpu_time(start, end) (((double)(end - start)) / CLOCKS_PER_SEC)
#define show_cpu_time(start, end) (printf("\tCPU Time:%f\n", cpu_time(start, end)))
#define c_t(start) (show_cpu_time(start, clock()))

CatClients build_catclients(char *filename, int *valids, int *total)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return NULL;

    char buffer[1024];
    CatClients cc = CatClients_make();
    Client tmp;
    int v, t;
    v = t = 0;

    while (fgets(buffer, 1024, fp))
    {
        tmp = verify_client(buffer);

        if (tmp)
        {
            v++;
            CatClients_add_client(cc, tmp);
        }

        t++;
    }

    *valids = v;
    *total = t;

    fclose(fp);

    return cc;
}

CatProducts build_catproducts(char *filename, int *valids, int *total)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return NULL;

    char buffer[1024];
    CatProducts cp = CatProducts_make();
    Product tmp;
    int v, t;
    v = t = 0;

    while (fgets(buffer, 1024, fp))
    {
        tmp = verify_product(buffer);

        if (tmp)
        {
            v++;
            CatProducts_add_product(cp, tmp);
        }

        t++;
    }

    *valids = v;
    *total = t;

    fclose(fp);

    return cp;
}

Accounting build_transactions(char *filename, int *valids, int *total, CatProducts cp, CatClients cc, FilManager *fm)
{
    FILE *fp = fopen(filename, "r");

    if (!fp || !cp)
        return NULL;

    char buffer[1024];
    int valid, tot, filial, month, promo, units;
    double cost;
    Accounting ac = Accounting_make();
    FilManager new_fm = filmanager_make();
    Verifier vf = Verifier_make();
    Transaction tmp;
    Client c;
    Product p;
    valid = tot = 0;

    while (fgets(buffer, 1024, fp))
    {
        tmp = verify_sale(vf, buffer);

        if (tmp)
        {
            c = trans_get_client(tmp);
            p = trans_get_product(tmp);

            if (CatClients_exists(cc, c) && CatProducts_exists(cp, p))
            {
                valid++;
                filial = trans_get_filial(tmp);
                month = trans_get_month(tmp);
                promo = trans_get_promo(tmp);
                units = trans_get_units(tmp);
                cost = trans_get_price(tmp);

                /* Update do catalogo de produtos */
                CatProduct_report_trans(cp, p, filial);

                /* Update da contabilidade */
                Accounting_update(ac, p, month, filial, units, promo, cost);

                /* Update do gestor de filiais */
                filmanager_update(new_fm, p, c, filial, month, promo, units, cost);
            }

            trans_destroy(tmp);
        }

        tot++;
    }

    *valids = valid;
    *total = tot;
    *fm = new_fm;

    Verifier_destroy(vf);

    return ac;
}

void show10_elements(TAD_List tl)
{
    int i, s;
    if (tl)
    {
        s = list_size(tl);

        for (i = 0; i < 10 && i < s; i++)
        {
            printf("%s ", (char *)list_get_index(tl, i));
        }

        putchar('\n');
    }
}

int main()
{
    int valid1, valid2, valid3, total1, total2, total3, i;
    clock_t defstart, start, qstart;
    TAD_List l;

    defstart = start = clock();

    FilManager fm;
    CatProducts cp = build_catproducts("tests/Produtos.txt", &valid1, &total1);
    CatClients cc = build_catclients("tests/Clientes.txt", &valid2, &total2);
    Accounting ac = build_transactions("tests/Vendas_1M.txt", &valid3, &total3, cp, cc, &fm);

    printf("Just for building:\n");
    c_t(start);

    qstart = start = clock();
    puts("Query 2:");
    show10_elements(get_sorted_products(cp, 'A'));
    c_t(start);

    puts("Query 6:");
    start = clock();
    printf("\tIsto tem de dar 0 -> %d!\n", get_n_not_bought_clients(cc, fm));
    printf("\tIsto tem de dar 928 -> %d!\n", get_n_not_bought_products(cp));
    c_t(start);

    start = clock();
    puts("Query 10:");
    puts("\tFor client Z5000 and month 1");
    show10_elements(get_clients_most_bought(fm, "Z5000", 1));
    c_t(start);

    start = clock();
    puts("Query 11:");
    puts("\tFor client Z5000");
    show10_elements(get_clients_top3(fm, "Z5000"));
    c_t(start);

    puts("Just for the queries:");
    c_t(qstart);

    start = clock();
    CatProducts_destroy(cp);
    CatClients_destroy(cc);
    filmanager_destroy(fm);
    Accounting_destroy(ac);
    puts("Just for freeing:");
    c_t(start);

    puts("total:");
    c_t(defstart);
    return 0;
}