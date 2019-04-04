#include "Appender.h"
#include "PrdtInfo.h"
#include "util.h"
#include "set.h"
#include "Currier.h"
#include "kheap.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
void *appender_make();
void appender_destroy(void *e);
void appender_update(void *e, void *user_data);
int appender_get_quantity(Appender ap, int filial, int month);
int appender_get_num_product(Appender ap);
double appender_get_prod_spent(Appender ap, char *product);
int appender_get_prod_quant_month(Appender ap, char *product, int month);
int appender_get_quantity_fil(Appender ap, int filial);
int **appender_clone_matrix(Appender ap);
char **appender_get_most_bought(Appender ap, int month, int *size);
char **appender_get_top3(Appender ap, int *size);
int is_bought_in_all(Appender ap);

/* Metodos privados */
static void foreach_add_by_month(gpointer key, gpointer value, gpointer user_data);
static void foreach_add_to_heap(gpointer key, gpointer value, gpointer user_data);
static int compare_curr_quants(const void *a, const void *b);
static int compare_curr_spent(const void *a, const void *b);
static void mycurrier_destroy(void *a);

/* ------------------------------------------------------------------------------ */

typedef struct appender
{
    int matrix[N_FILIAIS][N_MONTHS + 1];
    StrSet product_set;
} * Appender;

/* ------------------------------------------------------------------------------ */

void *appender_make()
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

    ap->product_set = strset_make(NULL, prdtinfo_destroy, prdtinfo_make, prdtinfo_update, NULL);

    return ap;
}

void appender_destroy(void *e)
{
    Appender ap;

    if (e)
    {
        ap = (Appender)e;
        strset_destroy(ap->product_set);
        g_free(ap);
    }
}

void appender_update(void *e, void *user_data)
{
    Appender ap = (Appender)e;
    void *new[3], **user = (void **)user_data;
    char *product = (char *)user[0];
    int filial, units, month = *(int *)user[2];
    units = *(int *)user[3];
    filial = *(int *)user[1] - 1;
    ap->matrix[filial][0] += units;
    ap->matrix[filial][month] += units;
    new[0] = user[4];
    new[1] = user[3];
    new[2] = user[2];
    strset_add(ap->product_set, product, new);
}

int appender_get_quantity(Appender ap, int filial, int month)
{
    return ap->matrix[filial - 1][month - 1];
}

int appender_get_num_product(Appender ap)
{
    return strset_size(ap->product_set);
}

double appender_get_prod_spent(Appender ap, char *product)
{
    double r = -1.0;
    void *val;

    if ((val = strset_lookup(ap->product_set, product)))
    {
        r = prdtinfo_total_spent((PrdtInfo)val);
    }

    return r;
}

int appender_get_prod_quant_month(Appender ap, char *product, int month)
{
    int r = -1;
    void *val;

    if ((val = strset_lookup(ap->product_set, product)))
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

char **appender_get_most_bought(Appender ap, int month, int *size)
{
    int j, i = 0;
    char **r = NULL;
    void *tmp[3];
    Currier *c_arr = g_malloc(sizeof(Currier) * strset_size(ap->product_set));

    tmp[0] = c_arr;
    tmp[1] = &i;
    tmp[2] = &month;

    strset_foreach(ap->product_set, foreach_add_by_month, tmp);

    if (i != 0)
    {
        *size = i;

        qsort(c_arr, i, sizeof(Currier), compare_curr_quants);

        r = g_malloc(sizeof(char *) * i);

        for (j = 0; j < i; j++)
        {
            r[i] = g_strdup((char *)uncurry_by_key(c_arr[i]));
            currier_destroy(c_arr[i]);
        }
    }

    g_free(c_arr);

    return r;
}

char **appender_get_top3(Appender ap, int *size)
{
    int i, m;
    char **r = NULL;
    KHeap kh = kheap_make(compare_curr_spent, mycurrier_destroy);
    void *val;

    strset_foreach(ap->product_set, foreach_add_to_heap, kh);

    i = kheap_size(kh);
    *size = m = min(3, i);

    r = g_malloc(sizeof(char *) * m);

    for (i = 0; i < m; i++)
    {
        val = kheap_extract_root(kh);
        r[i] = g_strdup((char *)uncurry_by_key((Currier)val));
        currier_destroy((Currier)val);
    }

    return r;
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
    void **holder = (void **)user_data;
    int month = *(int *)holder[2];

    if (prdtinfo_month_units((PrdtInfo)value, month) > 0)
    {
        ((Currier *)holder[0])[(*(int *)holder[1])++] = currier_make(key, value, holder[2]);
    }
}

static void foreach_add_to_heap(gpointer key, gpointer value, gpointer user_data)
{
    kheap_add((KHeap)user_data, currier_make(key, value, NULL));
}

static int compare_curr_quants(const void *a, const void *b)
{
    Currier ca = *(Currier *)a;
    Currier cb = *(Currier *)b;

    int month = *(int *)uncurry_by_user(ca);

    return (prdtinfo_month_units((PrdtInfo)uncurry_by_value(cb), month) - prdtinfo_month_units((PrdtInfo)uncurry_by_value(ca), month));
}

static int compare_curr_spent(const void *a, const void *b)
{
    Currier ca = (Currier)a;
    Currier cb = (Currier)b;

    double dif = prdtinfo_total_spent((PrdtInfo)uncurry_by_value(cb)) - prdtinfo_total_spent((PrdtInfo)uncurry_by_value(ca));

    return ((dif > 0.0) ? -1 : (dif < 0.0));
}

static void mycurrier_destroy(void *a)
{
    currier_destroy((Currier)a);
}