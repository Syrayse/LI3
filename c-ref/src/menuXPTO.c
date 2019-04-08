#include "menuXPTO.h"
#include "commondef.h"
#include "NavControl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Accounting.h"
#include "FilManager.h"
#include "util.h"
#include "menu.h"
#include "Queries.h"
#include "Verifier.h"
#include <stdio.h>
#include <time.h>
#include <glib.h>

/* ------------------------------------------------------------------------------ */

typedef struct sgv
{
    int is_freed;
    double start, end, elapsed;
    CatClients cc;
    CatProducts cp;
    Accounting ac;
    FilManager fm;
    NavControl nc;
} * SGV;

typedef void (*MenuAction)(SGV);

typedef struct menuxpto
{
    SGV main_sgv;
    MenuAction func_vec[N_QUERIES];
} * MenuXPTO;

/* ------------------------------------------------------------------------------ */

/* Metódos públicos */
MenuXPTO menu_make();
void menu_run(MenuXPTO m);
void menu_destroy(MenuXPTO m);

/* Metódos privados */
static void menu();
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

/* ------------------------------------------------------------------------------ */

MenuXPTO menu_make()
{
    MenuXPTO m = g_malloc(sizeof(struct menuxpto));

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

void menu_run(MenuXPTO m)
{
    int userMenu;

    do
    {
        system("clear");

        menu();

    }

    while (scanf("%d", &userMenu) >= 0)
    {
        system("clear");

        menu();

        if (is_between(userMenu, 1, N_QUERIES))
        {
        }
    }
}

void menu_destroy(MenuXPTO m)
{
    if (m)
    {
        free_sgv(m->main_sgv);
        g_free(m);
    }
}

static void menu()
{
    printf("     ___________________________________________________ \n");
    printf("    |                                                   |\n");
    printf("    |            Bem vindo ao gestor de Vendas          |\n");
    printf("    |___________________________________________________|\n");

    printf("	01. Fazer leitura dos ficheiros.\n");
    printf("	02. Apresentar Catálogo de Produtos.\n");
    printf("	03. Informações sobre as vendas de um produto num determinado mês.\n");
    printf("	04. Produtos não comprados.\n");
    printf("	05. Lista de clientes que realizaram compras em todas as filiais.\n");
    printf("	06. Clientes e produtos inativos.\n");
    printf("	07. Informações sobre as compras de um determinado cliente, por mês.\n");
    printf("	08. Resultados das vendas num intervalo de meses.\n");
    printf("	09. Lista de clientes que compraram um produto num determinado filial.\n");
    printf("	10. Produtos mais comprados por um cliente num determinado mês.\n");
    printf("	11. Lista dos N produtos mais comprados ao longo do ano.\n");
    printf("	12. Produtos em que um cliente gastou mais dinheiro.		0. Sair.\n\n");
}

static SGV build_sgv()
{
    SGV sgv = g_malloc(sizeof(struct sgv));

    sgv->is_freed = 0,

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
}

static void menu_query2(SGV s)
{
}

static void menu_query3(SGV s)
{
}

static void menu_query4(SGV s)
{
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
	        pMatriz(r, cli);
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
