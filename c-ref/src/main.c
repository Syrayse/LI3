/**
 * @file main.c
 * \brief testfile.
 */

#include "CatProducts.h"
#include "CatClients.h"
#include "FilManager.h"
#include "Accounting.h"
#include "Transaction.h"
#include "Verifier.h"
#include "Queries.h"
#include "util.h"
#include <glib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "commondef.h"
#include "menu.h"
#include "ProdDescriptor.h"
#include "TAD_List.h"

#define cpu_time(start, end) (((double)(end - start)) / CLOCKS_PER_SEC)
#define show_cpu_time(start, end) (printf("\tCPU Time:%f\n", cpu_time(start, end)))
#define c_t(start) (show_cpu_time(start, clock()))
#define TAM_PAG 24

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

                /* Update do catálogo de produtos. */
                CatProduct_report_trans(cp, p, filial);

                /* Update da contabilidade. */
                Accounting_update(ac, p, month, filial, units, promo, cost);

                /* Update do gestor de filiais. */
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

void show_prodescript(ProdDescriptor pd)
{
    char *str = product_get_code(proddescrip_get_product(pd));

    printf("\tProduto %s, total clients %d, vendas fil1:%d | fil2:%d | fil3:%d\n",
           str, proddescrip_get_n_clients(pd), proddescrip_get_fil_units(pd, 1), proddescrip_get_fil_units(pd, 2), proddescrip_get_fil_units(pd, 3));
}

void show_n_proddescrips(TAD_List tl)
{
    int i, s = list_size(tl);

    for (i = 0; i < s; i++)
    {
        show_prodescript((ProdDescriptor)list_get_index(tl, i));
    }
}

void controla(TAD_List l)
{
    int status = -1;

    int inicio = 0;
    int fim = TAM_PAG;
    if (!l)
    {
        pMess("\tErro, o cliente ou o produto não existe");
        return;
    }
    int s = list_size(l);
    while (1)
    {
        status = navegador(l, inicio, fim, s);
        if (status == 1)
        {
            if (fim > s)
            {
                inicio = 0;
                fim = TAM_PAG;
            }
            else
            {
                inicio += TAM_PAG;
                fim += TAM_PAG;
            }
        }
        else if (status == 2)
        {
            if (inicio < TAM_PAG)
            {
                fim = (s / TAM_PAG + 1) * TAM_PAG;
                inicio = fim - TAM_PAG;
            }
            else
            {
                inicio -= TAM_PAG;
                fim -= TAM_PAG;
            }
        }
        else
            break;
    }
}

int main(int argc, char const *argv[])
{
    int valid, total, **r, i;
    int *fils[N_FILIAIS], geral[2];
    double *dfils[N_FILIAIS], dgeral[2];

    for (i = 0; i < N_FILIAIS; i++)
    {
        fils[i] = g_malloc(sizeof(int) * 2);
        dfils[i] = g_malloc(sizeof(double) * 2);
    }

    TAD_List l;

    int mes;
    char letra;
    char fich[1024];
    int lido;

    FilManager fm;
    Accounting ac;
    CatClients cc;
    CatProducts cp;

    int status = -1;
    while (status)
    {
        status = comunicaExt(status);

        if (status == 1)
        {

            getDirProd(&lido, fich);
            if (lido == 1 && (fich[0] == 'O' || fich[0] == 'o'))
                strcpy(fich, "tests/Produtos.txt");
            cp = build_catproducts(fich, &valid, &total);
            pLinhas("produtos", fich, valid, total);

            getDirCli(&lido, fich);
            if (lido == 1 && (fich[0] == 'O' || fich[0] == 'o'))
                strcpy(fich, "tests/Clientes.txt");
            cc = build_catclients(fich, &valid, &total);
            pLinhas("clientes", fich, valid, total);

            getDirVendas(&lido, fich);
            if (lido == 1 && (fich[0] == 'O' || fich[0] == 'o'))
                strcpy(fich, "tests/Vendas_1M.txt");
            ac = build_transactions(fich, &valid, &total, cp, cc, &fm);
            pLinhas("Vendas", fich, valid, total);

            pMess("\tFicheiros carregados");
        }
        int modo;

        switch (status)
        {
        case 2:
        {
            letra = pedirChar("\tIndique a letra para a qual deseja ver a lista");
            if (letra <= 'z' && letra >= 'a')
                letra -= 32;
            if (letra <= 'Z' && letra >= 'A')
            {
                l = get_sorted_products(cp, letra);
                controla(l);
            }
            else
                pMess("\tInput inválido\n");
        }
        break;

        case 3:
        {
            pedirString("\tIntroduza um código de produto: ", fich);
            mes = pedirInteiro("\tIntroduza um mês: ");
            modo = pedirInteiro("\tEscolha se prefere visualizar o resultado para as 3 filiais ou o resultado global\n\t0.Global  1.2.3.Filial ");
            if (!verify_product(fich))
                pMess("\tInput inválido\n");
            else
            {
                if (mes >= 1 && mes <= 12 && modo == 0)
                {
                    if (get_product_global_stats(ac, fich, mes, geral, dgeral))
                    {
                        pMess("\n\tResultado global: ");
                        fatura(geral, dgeral);
                    }
                    else
                        pMess("\tErro, o cliente não existe\n");
                }

                else if (mes >= 1 && mes <= 12)
                {
                    if (get_product_per_filial_stats(ac, fich, mes, fils, dfils))
                    {
                        pMess("\n\tResultado por filial: ");
                        filiais(modo, fils, dfils);
                    }
                    else
                        pMess("\tErro, o cliente não existe\n");
                }
                else
                    pMess("\tInput inválido\n");
            }
        }
        break;

        case 4:
        {
            modo = pedirInteiro("\tPretende visualizar a lista global ou de uma filial?\n\t0. Global  1.2.3. Filial ");
            if (modo < 4 && modo > -1)
            {
                l = get_not_bought_products(cp, modo);
                NaoVende(list_size(l), modo);
                controla(l);
            }
            else
                pMess("\tInput inválido");
        }
        break;

        case 5:
        {
            controla(get_overall_clients(fm));
        }
        break;

        case 6:
        {
            NaoComp(get_n_not_bought_clients(cc, fm), get_n_not_bought_products(cp));
        }
        break;

        case 7:
        {
            pedirString("\tIntroduza um código de Cliente: ", fich);
            if (strlen(fich) != 5 || !(verify_client(fich)))
                pMess("\tInput inválido");
            else
            {
                r = get_matrix(fm, fich);
                if (r == NULL)
                    pMess("\tErro, o cliente não existe");
                else
                    pMatriz(r, fich);
            }
        }
        break;

        case 8:
        {
            mes = pedirInteiro("\tIntroduza o primeiro mês: ");
            i = pedirInteiro("\tIntroduza o segundo mês: ");
            if (mes <= i && 0 < mes && mes < 13 && 0 < i && i < 13)
                intMeses(mes, i, get_interval_trans(ac, mes, i), get_interval_rev(ac, mes, i));
            else
                pMess("\tInput inválido");
        }
        break;

        case 9:
        {
            pedirString("\tIntroduza o código de produto: ", fich);
            i = pedirInteiro("\tIntroduza uma filial: ");
            mes = pedirInteiro("\tEscolha se quer resultados para promoção ou sem promoção\n\t0.Sem promoção  1.Com promoção ");
            if ((mes != 0 && mes != 1) || i > 3 || i < 1 || !(verify_product(fich)))
                pMess("\tInput inválido");
            else
                controla(get_product_buyers(fm, fich, i, mes));
        }
        break;

        case 10:
        {
            mes = pedirInteiro("\tIntroduza um mês: ");
            pedirString("\tIntroduza o código de cliente: ", fich);
            if (!(verify_client(fich)) || mes < 1 || mes > 12)
                pMess("\tInput inválido");
            else
                controla(get_clients_most_bought(fm, fich, mes));
        }
        break;

        case 11:
        {
            i = pedirInteiro("\tIntroduza o número de elementos: ");
            if (i > 0)
                show_n_proddescrips(get_topN_most_sold(ac, fm, i));
            else
                pMess("\tInsira um número positivo");
        }
        break;

        case 12:
        {
            pedirString("\tIntroduza o código de cliente: ", fich);
            if (verify_client(fich))
                controla(get_clients_top3(fm, fich));
            else
                pMess("\tInput inválido");
        }
        break;

        default:
            break;

            if (status == 0)
            {
                CatProducts_destroy(cp);
                CatClients_destroy(cc);
                filmanager_destroy(fm);
                Accounting_destroy(ac);
            }
        }
    }
    return 0;
}
