/**
 * @file menu.c
 * \brief Ficheiro que contém o código do menu a apresentar ao utilizador.
 */

#include "menu.h"
#include "commondef.h"
#include "NavControl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Accounting.h"
#include "FilManager.h"
#include "TAD_List.h"
#include "Queries.h"
#include "util.h"
#include "Verifier.h"
#include "Controls.h"
#include <time.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura que armazena todas tipos necessários ao SGV.
 */
typedef struct sgv
{
    int is_freed;   /**< Indica se o sgv já foi libertado da memória ou não. */
    double start,   /**< Indica o tempo em que começou a última query. */
        end,        /**< Indica o tempo em que acabou a última query. */
        elapsed;    /**< Indica o tempo que demorou a última query. */
    CatClients cc;  /**< Catálogo de clientes necessário ao SGV. */
    CatProducts cp; /**< Catálogo de produtos necessário ao SGV. */
    Accounting ac;  /**< Contabilidade necessária ao SGV.*/
    FilManager fm;  /**< Gestor de filiais necessário ao SGV.*/
    NavControl nc;  /**< Controlador de apresentação de conteúdo em listas. */
} * SGV;

/**
 * \brief Simplifica a escrita de uma função que vai servir para ações separadas por menu.
 */
typedef void (*MenuAction)(SGV);

/**
 * \brief Estrutura que armazena todo o menu necessário para gerir o SGV na integra.
 */
typedef struct menu
{
    SGV main_sgv;                   /**< Estrutura principal que armazena todas as unidades necessárias pelo SGV. */
    MenuAction func_vec[N_QUERIES]; /**< Estrutura que armazena as funções de interação com cada menu. */
} * Menu;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
Menu menu_make();
void menu_run(Menu m);
void menu_destroy(Menu m);

/* Métodos privados */
static SGV build_sgv();
static void free_sgv(SGV s);
static void menu_query1(SGV s);
static void menu_query2(SGV s);
static void menu_query3(SGV s);
static void menu_query4(SGV s);
static void menu_query5(SGV s);
static void menu_query6(SGV s);
static void menu_query7(SGV s);
static void menu_query8(SGV s);
static void menu_query9(SGV s);
static void menu_query10(SGV s);
static void menu_query11(SGV s);
static void menu_query12(SGV s);
static CatClients build_catclients(char *filename, int *valids, int *total);
static CatProducts build_catproducts(char *filename, int *valids, int *total);
static Accounting build_transactions(char *filename, int *valids, int *total, CatProducts cp, CatClients cc, FilManager *fm);

/* ------------------------------------------------------------------------------ */

Menu menu_make()
{
    Menu m = g_malloc(sizeof(struct menu));

    m->main_sgv = build_sgv();

    m->func_vec[0] = menu_query1;
    m->func_vec[1] = menu_query2;
    m->func_vec[2] = menu_query3;
    m->func_vec[3] = menu_query4;
    m->func_vec[4] = menu_query5;
    m->func_vec[5] = menu_query6;
    m->func_vec[6] = menu_query7;
    m->func_vec[7] = menu_query8;
    m->func_vec[8] = menu_query9;
    m->func_vec[9] = menu_query10;
    m->func_vec[10] = menu_query11;
    m->func_vec[11] = menu_query12;

    return m;
}

void menu_run(Menu m)
{
    int status = -1;

    do
    {
        system("clear");

        show_menu();

        status = comunicaExt(status);

        if (is_between(status, 1, N_QUERIES))
        {
            (*m->func_vec[status - 1])(m->main_sgv);
        }

        show_cpu_time(m->main_sgv->elapsed);
    } while (status != 0);
}

void menu_destroy(Menu m)
{
    if (m)
    {
        free_sgv(m->main_sgv);
        g_free(m);
    }
}

static SGV build_sgv()
{
    SGV sgv = g_malloc(sizeof(struct sgv));

    sgv->is_freed = 0,

    sgv->cc = CatClients_make();

    sgv->cp = CatProducts_make();

    sgv->ac = Accounting_make();

    sgv->fm = filmanager_make();

    sgv->nc = NavControl_make();

    return sgv;
}

static void free_sgv(SGV s)
{
    if (s)
    {
        CatClients_destroy(s->cc);
        CatProducts_destroy(s->cp);
        Accounting_destroy(s->ac);
        filmanager_destroy(s->fm);
        NavControl_destroy(s->nc);
    }
}

static void menu_query1(SGV s)
{
    int lido, total, valid;
    char fich[1024];
    clock_t start, end;
    s->elapsed = 0;

    getDirProd(&lido, fich);

    if (lido == 1 && (fich[0] == 'O' || fich[0] == 'o'))
        strcpy(fich, "tests/Produtos.txt");
    start = clock();
    free_sgv(s);
    s->cp = build_catproducts(fich, &valid, &total);
    end = clock();
    s->elapsed += end - start;

    pLinhas("produtos", fich, valid, total);

    getDirCli(&lido, fich);
    if (lido == 1 && (fich[0] == 'O' || fich[0] == 'o'))
        strcpy(fich, "tests/Clientes.txt");
    start = clock();
    s->cc = build_catclients(fich, &valid, &total);
    end = clock();
    s->elapsed += end - start;
    pLinhas("clientes", fich, valid, total);

    getDirVendas(&lido, fich);
    if (lido == 1 && (fich[0] == 'O' || fich[0] == 'o'))
        strcpy(fich, "tests/Vendas_1M.txt");
    start = clock();
    s->ac = build_transactions(fich, &valid, &total, s->cp, s->cc, &s->fm);
    end = clock();
    s->elapsed += end - start;
    pLinhas("Vendas", fich, valid, total);

    pMess("\tFicheiros carregados");
}

static void menu_query2(SGV s)
{
    char letra = pedirChar("\tIndique a letra para a qual deseja ver a lista");
    TAD_List l;

    if (is_between(letra, 'a', 'z'))
        letra -= 32;

    if (is_between(letra, 'A', 'Z'))
    {
        s->start = clock();

        l = get_sorted_products(s->cp, letra);

        s->end = clock();

        controla(l);
    }
    else
        pMess("\tInput inválido\n");
}

static void menu_query3(SGV s)
{
    double *dfils[N_FILIAIS], dgeral[2];
    char fich[1024];
    int n, mes, modo, *fils[N_FILIAIS], geral[2];

    pedirString("\tIntroduza um código de produto: ", fich);
    mes = pedirInteiro("\tIntroduza um mês: ");
    modo = pedirInteiro("\tEscolha se prefere visualizar o resultado para as 3 filiais ou o resultado global\n\t0.Global  1.2.3.Filial ");
    if (!verify_product(fich))
        pMess("\tInput inválido\n");
    else
    {
        if (is_between(mes, 1, N_MONTHS) && modo == 0)
        {
            s->start = clock();
            n = get_product_global_stats(s->ac, fich, mes, geral, dgeral);
            s->end = clock();

            if (n)
            {
                pMess("\n\tResultado global: ");
                fatura(geral, dgeral);
            }
            else
                pMess("\tErro, o cliente não existe\n");
        }
        else if (is_between(mes, 1, N_MONTHS))
        {
            s->start = clock();
            n = get_product_per_filial_stats(s->ac, fich, mes, fils, dfils);
            s->end = clock();

            if (n)
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

static void menu_query4(SGV s)
{
    TAD_List l;
    int modo = pedirInteiro("\tPretende visualizar a lista global ou de uma filial?\n\t0. Global  1.2.3. Filial ");

    if (is_between(modo, 0, 3))
    {
        s->start = clock();
        l = get_not_bought_products(s->cp, modo);
        s->end = clock();
        NaoVende(list_size(l), modo);
        controla(l);
    }
    else
        pMess("\tInput inválido");
}

static void menu_query5(SGV s)
{
    TAD_List l;
    s->start = clock();
    l = (get_overall_clients(s->fm));
    s->end = clock();
    controla(l, printReg);
}

static void menu_query6(SGV s)
{
    int c, p;
    s->start = clock();
    c = (get_n_not_bought_clients(s->cc, s->fm));
    p = (get_n_not_bought_products(s->cp));
    s->end = clock();
    NaoComp(c, p);
}

static void menu_query7(SGV s)
{
    char cli[1024];
    int **r;
    pedirString("\tIntroduza um código de Cliente: ", cli);
    if (strlen(cli) != 5 || !(verify_client(cli)))
        pMess("\tInput inválido");
    else
    {
        s->start = clock();
        r = get_matrix(s->fm, cli);
        s->end = clock();
        if (r == NULL)
            pMess("\tErro, o cliente não existe");
        else
            pMatriz(r);
    }
}

static void menu_query8(SGV s)
{
    int mes1, mes2, t;
    double r;
    mes1 = pedirInteiro("\tIntroduza o primeiro mês: ");
    mes2 = pedirInteiro("\tIntroduza o segundo mês: ");
    if (mes1 <= mes2 && 0 < mes1 && mes1 < 13 && 0 < mes2 && mes2 < 13)
    {
        s->start = clock();
        t = get_interval_trans(s->ac, mes1, mes2);
        r = get_interval_rev(s->ac, mes1, mes2);
        s->end = clock();
        intMeses(mes1, mes2, t, r);
    }
    else
        pMess("\tInput inválido");
}

static void menu_query9(SGV s)
{
}

static void menu_query10(SGV s)
{
}

static void menu_query11(SGV s)
{
}

static void menu_query12(SGV s)
{
}

static CatClients build_catclients(char *filename, int *valids, int *total)
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

static CatProducts build_catproducts(char *filename, int *valids, int *total)
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

static Accounting build_transactions(char *filename, int *valids, int *total, CatProducts cp, CatClients cc, FilManager *fm)
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
