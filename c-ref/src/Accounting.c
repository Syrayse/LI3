/**
 * @file Accounting.c
 * \brief Ficheiro de código necessário para os metódos da classe `Accounting`.
 * 
 * Esta classe tem como objetivo tratar das contas do serviço SVG.
 */

#include "Accounting.h"
#include "statinfo.h"
#include "Product.h"
#include "TAD_List.h"
#include "Currier.h"
#include "kheap.h"
#include "commondef.h"
#include "util.h"
#include "set.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `Accounting`.
 */
typedef struct accounting
{
    int nTrans[N_MONTHS];         /**< Número de transações mensais. */
    double totCashFlow[N_MONTHS]; /**< Fluxo monetário mensal. */
    Set products[N_LETTER];       /**< Conjunto que armazena todos os produtos. */
} * Accounting;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_update(Accounting a, Product product, int month, int filial, int units, int promo, double spent);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_n_cash_range(Accounting a, int init, int end);
int Accounting_get_global_stats(Accounting a, Product product, int month, int *trans_vec, double *spent_vec);
int Accounting_get_per_filial_stats(Accounting a, Product product, int month, int **trans_vec, double **spent_vec);
TAD_List Accounting_get_top_N_most_bought(Accounting a, int N);
void Accounting_get_fil_vec_units(Accounting a, Product p, int *fil_vector);

/* Métodos privados */
static gpointer wrapstatinfo_make();
static void wrapstatinfo_destroy(gpointer v);
static void wrapstatinfo_update(gpointer v1, gpointer v2);
static void foreach_add_to_heap(gpointer key, gpointer value, gpointer user_data);
static int compare_curr_quants(gconstpointer a, gconstpointer b);
static void mycurrier_destroy(gpointer a);

/* ------------------------------------------------------------------------------ */

Accounting Accounting_make()
{
    int i;
    Accounting ac = g_malloc(sizeof(struct accounting));

    for (i = 0; i < N_MONTHS; i++)
    {
        ac->nTrans[i] = 0;
        ac->totCashFlow[i] = 0.0;
    }

    for (i = 0; i < N_LETTER; i++)
    {
        ac->products[i] = set_make(product_hash, product_equal, wrapproduct_destroy, wrapstatinfo_destroy, wrapstatinfo_make, wrapstatinfo_update);
    }

    return ac;
}

void Accounting_destroy(Accounting a)
{
    int i;

    if (a)
    {
        for (i = 0; i < N_LETTER; i++)
        {
            set_destroy(a->products[i]);
        }

        g_free(a);
    }
}

void Accounting_update(Accounting a, Product product, int month, int filial, int units, int promo, double spent)
{
    gpointer tmp[5];
    int p = get_i(product);
    Product ef_product = product;

    a->nTrans[month - 1]++;
    a->totCashFlow[month - 1] += units * spent;

    tmp[0] = &month;
    tmp[1] = &filial;
    tmp[2] = &units;
    tmp[3] = &promo;
    tmp[4] = &spent;

    if (!set_contains(a->products[p], product))
    {
        ef_product = product_clone(product);
    }

    set_add(a->products[p], ef_product, tmp);
}

int Accounting_n_trans_range(Accounting a, int init, int end)
{
    int i, r = -1;

    if (init <= end)
    {
        r = 0;

        for (i = init - 1; i < end; i++)
            r += a->nTrans[i];
    }

    return r;
}

double Accounting_n_cash_range(Accounting a, int init, int end)
{
    int i;
    double r = -1.0;

    if (init <= end)
    {
        r = 0.0;

        for (i = init - 1; i < end; i++)
            r += a->totCashFlow[i];
    }

    return r;
}

int Accounting_get_global_stats(Accounting a, Product product, int month, int *trans_vec, double *spent_vec)
{
    int r = 0;
    gpointer val;
    StatInfo si;

    if ((val = set_lookup(a->products[get_i(product)], product)))
    {
        r = 1;
        si = (StatInfo)val;

        trans_vec[0] = get_t_month_vendas_no_promo(si, month);
        trans_vec[1] = get_t_month_vendas_promo(si, month);
        spent_vec[0] = get_t_month_rev_no_promo(si, month);
        spent_vec[1] = get_t_month_rev_promo(si, month);
    }

    return r;
}

int Accounting_get_per_filial_stats(Accounting a, Product product, int month, int **trans_vec, double **spent_vec)
{
    int i, r = 0;
    gpointer val;
    StatInfo si;

    if ((val = set_lookup(a->products[get_i(product)], product)))
    {
        r = 1;
        si = (StatInfo)val;

        for (i = 0; i < N_FILIAIS; i++)
        {
            trans_vec[i][0] = get_t_month_fil_vendas_no_promo(si, month, i + 1);
            trans_vec[i][1] = get_t_month_fil_vendas_promo(si, month, i + 1);
            spent_vec[i][0] = get_t_month_fil_rev_no_promo(si, month, i + 1);
            spent_vec[i][1] = get_t_month_fil_rev_promo(si, month, i + 1);
        }
    }

    return r;
}

TAD_List Accounting_get_top_N_most_bought(Accounting a, int N)
{
    int i, m;

    TAD_List tl;
    Currier tmp;
    KHeap kh = kheap_make(compare_curr_quants, mycurrier_destroy);

    for (i = 0; i < N_LETTER; i++)
    {
        set_foreach(a->products[i], foreach_add_to_heap, kh);
    }

    m = min(N, kheap_size(kh));
    tl = list_make(NULL, m);

    for (i = 0; i < m; i++)
    {
        tmp = (Currier)kheap_extract_root(kh);
        list_add(tl, product_clone((Product)uncurry_by_key(tmp)));
    }

    return tl;
}

void Accounting_get_fil_vec_units(Accounting a, Product p, int *fil_vector)
{
    gpointer v;

    if ((v = set_lookup(a->products[get_i(p)], p)))
    {
        get_t_units_forall_fil((StatInfo)v, fil_vector);
    }
}

static gpointer wrapstatinfo_make()
{
    return statinfo_make();
}

static void wrapstatinfo_destroy(gpointer v)
{
    statinfo_destroy((StatInfo)v);
}

static void wrapstatinfo_update(gpointer v1, gpointer v2)
{
    statinfo_update((StatInfo)v1, v2);
}

static void foreach_add_to_heap(gpointer key, gpointer value, gpointer user_data)
{
    kheap_add((KHeap)user_data, currier_make(key, value, NULL));
}

static int compare_curr_quants(gconstpointer a, gconstpointer b)
{
    Currier ca = (Currier)a;
    Currier cb = (Currier)b;

    return (get_t_units((StatInfo)uncurry_by_value(ca)) - get_t_units((StatInfo)uncurry_by_value(cb)));
}

static void mycurrier_destroy(gpointer a)
{
    currier_destroy((Currier)a);
}