/**
 * @file Appender.c
 * \brief Ficheiro com o código relativo a todos os metódos da classe `Appender`.
 * 
 * Em módulos acima na hierarquia esta classe representa a ligação entre clientes e os produtos
 * que este cliente comprou. Cada instância da classe `Appender` representa uma diferente ligação
 * entre cliente e produto. Sendo que, para cada uma destas ligações é armazenada informação útil de modo
 * a conseguir, de forma eficiente, responder às queries apresentadas.
 */

#include "Appender.h"
#include "PrdtInfo.h"
#include "set.h"
#include "Currier.h"
#include "kheap.h"
#include "Product.h"
#include "TAD_List.h"
#include "util.h"

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `Appender`.
 */
typedef struct appender
{
    int matrix[N_FILIAIS][N_MONTHS + 1]; /**< Matriz que armazenada as quantidades compradas pelo cliente, ordenadas por filial e mês. */
    Set product_set;                     /**< Conjunto de todos os produtos comprados pelo cliente. */
} * Appender;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
gpointer appender_make();
void appender_destroy(gpointer v);
void appender_update(gpointer e, gpointer user_data);
int appender_get_quantity(Appender ap, int filial, int month);
int appender_get_num_product(Appender ap);
double appender_get_prod_spent(Appender ap, Product product);
int appender_get_prod_quant_month(Appender ap, Product product, int month);
int appender_get_quantity_fil(Appender ap, int filial);
int **appender_clone_matrix(Appender ap);
TAD_List appender_get_most_bought(Appender ap, int month);
TAD_List appender_get_top3(Appender ap);
int is_bought_in_all(Appender ap);

/* Métodos privados */
static void foreach_add_by_month(gpointer key, gpointer value, gpointer user_data);
static void foreach_add_to_heap(gpointer key, gpointer value, gpointer user_data);
static int compare_curr_quants(gconstpointer a, gconstpointer b);
static int compare_curr_spent(gconstpointer a, gconstpointer b);
static void mycurrier_destroy(gpointer a);

/* ------------------------------------------------------------------------------ */

gpointer appender_make()
{
    int i, j;

    Appender ap = g_malloc(sizeof(struct appender));

    for (i = 0; i < N_FILIAIS; i++)
    {
        for (j = 0; j < N_MONTHS + 1; j++)
        {
            ap->matrix[i][j] = 0;
        }
    }

    ap->product_set = set_make(product_hash, product_equal, NULL, prdtinfo_destroy, prdtinfo_make, prdtinfo_update);

    return ap;
}

void appender_destroy(gpointer v)
{
    Appender ap;

    if (v)
    {
        ap = (Appender)v;
        set_destroy(ap->product_set);
        g_free(ap);
    }
}

void appender_update(gpointer e, gpointer user_data)
{
    Appender ap = (Appender)e;
    gpointer new[3], *user = (gpointer *)user_data;
    Product product = (Product)user[0];
    int filial, units, month = *(int *)user[2];
    units = *(int *)user[3];
    filial = *(int *)user[1] - 1;
    ap->matrix[filial][0] += units;
    ap->matrix[filial][month] += units;
    new[0] = user[4];
    new[1] = user[3];
    new[2] = user[2];
    set_add(ap->product_set, product, new);
}

int appender_get_quantity(Appender ap, int filial, int month)
{
    return ap->matrix[filial - 1][month];
}

int appender_get_num_product(Appender ap)
{
    return set_size(ap->product_set);
}

double appender_get_prod_spent(Appender ap, Product product)
{
    double r = -1.0;
    gpointer val;

    if ((val = set_lookup(ap->product_set, product)))
    {
        r = prdtinfo_total_spent((PrdtInfo)val);
    }

    return r;
}

int appender_get_prod_quant_month(Appender ap, Product product, int month)
{
    int r = -1;
    gpointer val;

    if ((val = set_lookup(ap->product_set, product)))
    {
        r = prdtinfo_month_units((PrdtInfo)val, month);
    }

    return r;
}

int appender_get_quantity_fil(Appender ap, int filial)
{
    return ap->matrix[filial - 1][0];
}

int **appender_clone_matrix(Appender ap)
{
    int i, j, **r = g_malloc(sizeof(int *) * N_FILIAIS);

    for (i = 0; i < N_FILIAIS; i++)
    {
        r[i] = g_malloc(sizeof(int) * N_MONTHS);
    }

    for (i = 0; i < N_FILIAIS; i++)
    {
        for (j = 0; j < N_MONTHS; j++)
        {
            r[i][j] = ap->matrix[i][j + 1];
        }
    }

    return r;
}

TAD_List appender_get_most_bought(Appender ap, int month)
{
    int j, i = 0;
    TAD_List tl = NULL;
    gpointer tmp[3];
    Currier *c_arr = g_malloc(sizeof(Currier) * set_size(ap->product_set));

    tmp[0] = c_arr;
    tmp[1] = &i;
    tmp[2] = &month;
    set_foreach(ap->product_set, foreach_add_by_month, tmp);

    if (i != 0)
    {
        qsort(c_arr, i, sizeof(Currier), compare_curr_quants);

        tl = list_make(g_free, i);
        for (j = 0; j < i; j++)
        {
            list_add(tl, product_get_code((Product)uncurry_by_key(c_arr[j])));
            currier_destroy(c_arr[j]);
        }
    }

    g_free(c_arr);

    return tl;
}

TAD_List appender_get_top3(Appender ap)
{
    int i, m;
    TAD_List tl;
    KHeap kh = kheap_make(compare_curr_spent, mycurrier_destroy);
    Currier val;

    set_foreach(ap->product_set, foreach_add_to_heap, kh);

    m = min(3, kheap_size(kh));
    tl = list_make(g_free, m);

    for (i = 0; i < m; i++)
    {
        val = (Currier)kheap_extract_root(kh);
        list_add(tl, product_get_code((Product)uncurry_by_key(val)));
        currier_destroy(val);
    }

    return tl;
}

int is_bought_in_all(Appender ap)
{
    int i, r = 1;

    for (i = 0; r && i < N_FILIAIS; i++)
    {
        r = min(r, ap->matrix[i][0]);
    }

    return r;
}

static void foreach_add_by_month(gpointer key, gpointer value, gpointer user_data)
{
    gpointer *holder = (gpointer *)user_data;
    int month = *(int *)holder[2];
    Currier *arr = (Currier *)holder[0];
    Currier c;

    if (prdtinfo_month_units((PrdtInfo)value, month) > 0)
    {
        arr[(*(int *)holder[1])++] = currier_make(key, value, holder[2]);
    }
}

static void foreach_add_to_heap(gpointer key, gpointer value, gpointer user_data)
{
    kheap_add((KHeap)user_data, currier_make(key, value, NULL));
}

static int compare_curr_quants(gconstpointer a, gconstpointer b)
{
    Currier ca = *(Currier *)a;
    Currier cb = *(Currier *)b;

    int month = *(int *)uncurry_by_user(ca);

    return (prdtinfo_month_units((PrdtInfo)uncurry_by_value(cb), month) - prdtinfo_month_units((PrdtInfo)uncurry_by_value(ca), month));
}

static int compare_curr_spent(gconstpointer a, gconstpointer b)
{
    Currier ca = (Currier)a;
    Currier cb = (Currier)b;

    double dif = prdtinfo_total_spent((PrdtInfo)uncurry_by_value(cb)) - prdtinfo_total_spent((PrdtInfo)uncurry_by_value(ca));

    return ((dif > 0.0) ? -1 : (dif < 0.0));
}

static void mycurrier_destroy(gpointer a)
{
    currier_destroy((Currier)a);
}