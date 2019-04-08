#include "menuXPTO.h"
#include "commondef.h"
#include "NavControl.h"
#include "CatClients.h"
#include "CatProducts.h"
#include "Accounting.h"
#include "FilManager.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

typedef struct sgv
{
    int is_freed;
    CatClients cc;
    CatProducts cp;
    Accounting ac;
    FilManager fm;
    NavControl nc;
} * SGV;

typedef void (*MenuAction)(SGV);

typedef struct menuxpto
{
    int menuID;
    SGV main_sgv;
    MenuAction func_vec[N_QUERIES + 1];
} * MenuXPTO;

/* ------------------------------------------------------------------------------ */

/* Metódos publicos */
MenuXPTO menu_make();
void menu_run(MenuXPTO m);
void menu_destroy(MenuXPTO m);

/* Metódos privados */
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

    m->menuID = -1;

    m->main_sgv = build_sgv();

    m->func_vec[0] = free_sgv;
    m->func_vec[1] = menu_query1;
    m->func_vec[2] = menu_query2;
    m->func_vec[3] = menu_query3;
    m->func_vec[4] = menu_query4;
    m->func_vec[5] = menu_query5;
    m->func_vec[6] = menu_query6;
    m->func_vec[7] = menu_query7;
    m->func_vec[8] = menu_query8;
    m->func_vec[9] = menu_query9;
    m->func_vec[10] = menu_query10;
    m->func_vec[11] = menu_query11;
    m->func_vec[12S] = menu_query12;

    return m;
}

void menu_run(MenuXPTO m)
{
}

void menu_destroy(MenuXPTO m)
{
}
