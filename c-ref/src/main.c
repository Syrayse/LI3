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
#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int valid1, valid2, valid3, total1, total2, total3;

    FilManager fm;
    CatProducts cp = build_catproducts("tests/Produtos.txt", &valid1, &total1);
    CatClients cc = build_catclients("tests/Clientes.txt", &valid2, &total2);
    Accounting ac = build_transactions("tests/Vendas_1M.txt", &valid3, &total3, cp, cc, &fm);

    printf("total %d valids %d\n", total3, valid3);

    /*
    puts("Para os produtos");

    printf("\tRead %d, total valids %d!\n", total1, valid1);

    printf("\ttotal not bought:%d!\n", CatProducts_get_total_not_bought(cp));

    printf("\tExiste o client AF1184? %d (e suposto dar 1).\n", CatProducts_exists(cp, product_make("AF1184")));

    printf("\tExiste o client OS1139? %d (e suposto dar 0).\n", CatProducts_exists(cp, product_make("OS1139")));

    puts("Para os clientes");

    printf("\tRead %d, total valids %d!\n", total2, valid2);

    printf("\tNúmero total de clientes:%d!\n", CatClients_size(cc));

    printf("\tExiste o client Z5000? %d (e suposto dar 1).\n", CatClients_exists(cc, client_make("Z5000")));

    printf("\tExiste o client Q2719? %d (e suposto dar 0).\n", CatClients_exists(cc, client_make("Q2719")));
    */

    printf("Isto tem de dar 0 -> %d!\n", get_n_not_bought_clients(cc, fm));
    printf("Isto tem de dar 928 -> %d!\n", get_n_not_bought_products(cp));

    CatProducts_destroy(cp);
    CatClients_destroy(cc);
    filmanager_destroy(fm);
    Accounting_destroy(ac);
    return 0;
}