#include "sale.h"
#include "statinfo.h"
#include "specinfo.h"
#include "set.h"
#include "sale.h"
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
StatInfo statinfo_make(int flag);
void statinfo_destroy(StatInfo);
void statinfo_update(StatInfo, void *);
int statinfo_is_sold_by_all(StatInfo);
int get_t_vendas(StatInfo);
int get_t_fil_vendas(StatInfo, int filial);
int get_t_fil_vendas_promo(StatInfo, int filial);
int get_t_fil_vendas_no_promo(StatInfo, int filial);
int get_t_month_fil_vendas(StatInfo, int month, int filial);
int get_t_month_fil_vendas_promo(StatInfo, int month, int filial);
int get_t_month_fil_vendas_no_promo(StatInfo, int month, int filial);
int get_t_month_vendas(StatInfo, int month);
int get_t_month_vendas_promo(StatInfo, int month);
int get_t_month_vendas_no_promo(StatInfo, int month);
double get_t_rev(StatInfo);
double get_t_fil_rev(StatInfo, int filial);
double get_t_fil_rev_promo(StatInfo, int filial);
double get_t_fil_rev_no_promo(StatInfo, int filial);
double get_t_month_fil_rev(StatInfo, int month, int filial);
double get_t_month_fil_rev_promo(StatInfo, int month, int filial);
double get_t_month_fil_rev_no_promo(StatInfo, int month, int filial);
double get_t_month_rev(StatInfo, int month);
double get_t_month_rev_promo(StatInfo, int month);
double get_t_month_rev_no_promo(StatInfo, int month);

/* Metodos privados */
static int get_t_vendas_month_iter(StatInfo a, int month, int (*)(StatInfo, int, int));
static double get_t_rev_month_iter(StatInfo a, int month, double (*)(StatInfo, int, int));
static void *my_specinfo_make(int flag);
static void my_specinfo_destroy(void *si);
static void my_specinfo_update(void *si, void *e);

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de dados que contém informção estatistica de cada cliente/produto.
 **/
typedef struct statistical_info
{
    int identity,
        nVendasTotal,                                   /**< Número de registos de vendas associados */
        nVendasFilialMonth[N_FILIAIS][N_MONTHS + 1][2]; /**< Numero de registos de vendas associados por filial e mễs */
    double totalRevenue,                                /**< Rendimento total associado */
        monthlyFilialRev[N_FILIAIS][N_MONTHS + 1][2];   /**< Rendimento total associado por filial e mês*/
    StrSet historic;
} * StatInfo;

// ------------------------------------------------------------------------------

/**
 * \brief Criar em memória estrutura onde são armazenados os dados estatisticos.
 * 
 * @returns A estrutura alocada.
 **/
StatInfo statinfo_make(int flag)
{
    int l, c, k;
    StatInfo a = g_malloc(sizeof(struct statistical_info));
    a->historic = strset_make(g_free, my_specinfo_destroy, my_specinfo_make, my_specinfo_update, flag);

    a->identity = flag;

    a->nVendasTotal = 0;

    for (l = 0; l < N_FILIAIS; l++)
    {
        for (c = 0; c <= N_MONTHS; c++)
        {
            for (k = 0; k < N_PROMOS; k++)
            {
                a->nVendasFilialMonth[l][c][k] = 0;
                a->monthlyFilialRev[l][c][k] = 0;
            }
        }
    }

    a->totalRevenue = 0;

    return a;
}

/**
 * \brief Liberta a memória de um dado contento de informção estatistica.
 * 
 * @param a Contentor a libertar.
 **/
void statinfo_destroy(StatInfo a)
{
    if (a)
    {
        strset_destroy(a->historic);
        g_free(a);
    }
}

/**
 * \brief Atualiza os dados estatisticos consoante um registo de venda.
 * 
 * @param a Contentor de informação estatistica que ira ser atualizado.
 * @param e Registo de venda que servirá para atualizar a informação.
 **/
void statinfo_update(StatInfo a, void *e)
{
    if (!e)
        return;
    Sale s = (Sale)e;
    double rev = sale_get_rev(s);
    int f, m, p = sale_get_promo(s);
    m = sale_get_month(s);
    f = sale_get_filial(s);

    sale_id_check(s, a->historic, e, a->identity);

    // Vendas
    a->nVendasTotal++;
    a->nVendasFilialMonth[f - 1][0][indP(p)]++;
    a->nVendasFilialMonth[f - 1][m][indP(p)]++;

    // Profit
    a->totalRevenue += rev;
    a->monthlyFilialRev[f - 1][0][indP(p)] += rev;
    a->monthlyFilialRev[f - 1][m][indP(p)] += rev;
}

/**
 * \brief verifica se há um registo em cada uma das filiais.
 **/
int statinfo_is_sold_by_all(StatInfo a)
{
    int i, r = 1;
    for (i = 1; r && i <= N_FILIAIS; i++)
    {
        if (get_t_fil_vendas(a, i) == 0)
            r = 0;
    }
    return r;
}

/**
 * \brief Calcula o número de vendas da `key`.
 * 
 * @param a Informação estátistica associada à `key`.
 * 
 * @returns O número total de vendas da `key`.
 **/
int get_t_vendas(StatInfo a)
{
    return a->nVendasTotal;
}

/**
 * \brief Calcula o número total de vendas da `key` numa certa filial.
 * 
 * @param a Informação estátistica associada à `key`.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O nḿero total de vendas da `key` numa certa filial.
 **/
int get_t_fil_vendas(StatInfo a, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][0][0] + a->nVendasFilialMonth[filial - 1][0][1]);
}

/**
 * \brief Calcula o número total de vendas com promoção da `key` numa certa filial.
 * 
 * @param a Informação estátistica associada à `key`.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de vendas com promoção da `key` numa certa filial.
 **/
int get_t_fil_vendas_promo(StatInfo a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][1];
}

/**
 * \brief Calcula o número total de vendas sem promoção da `key` numa certa filial.
 * 
 * @param a Informação estátistica associada à `key`.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de vendas sem promoção da `key` numa certa filial.
 **/
int get_t_fil_vendas_no_promo(StatInfo a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][0];
}

/**
 * \brief Calcula o número total de vendas efetuadas num dado mês numa dada filial.
 * 
 * @param a Informação estátistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de vendas efetuadas num dados mês numa dada filial.
 **/
int get_t_month_fil_vendas(StatInfo a, int month, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][month][0] +
            a->nVendasFilialMonth[filial - 1][month][1]);
}

/**
 * \brief Calcula o número total de vendas com promoção efetuadas num dado mês numa dada filial.
 * 
 * @param a Informação estátistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de vendas com promoção efetuadas num dados mês e filial.
 **/
int get_t_month_fil_vendas_promo(StatInfo a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][1];
}

/**
 * \brief Calcula o número total de vendas sem promoção efetuadas num dado mês numa dada filial.
 * 
 * @param a Informação estátistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de vendas sem promoção efetuadas num dado mês e filial.
 **/
int get_t_month_fil_vendas_no_promo(StatInfo a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][0];
}

/**
 * \brief Calcula o número total de vendas duma dada estatistica mensal, consoante uma função que itera sobre todos os meses. 
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês do qual se pretende obter informação.
 * @param f Função de iteração por mês.
 * 
 * @returns O valor calculado.
 **/
static int get_t_vendas_month_iter(StatInfo a, int month, int (*f)(StatInfo, int, int))
{
    int k, r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}

/**
 * \brief Calcula o número total de lucro duma dada estatistica mensal, consoante uma função que itera sobre todos o lucro. 
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês do qual se pretende obter informação.
 * @param f Função de iteração por mês.
 * 
 * @returns O valor calculado.
 **/
static double get_t_rev_month_iter(StatInfo a, int month, double (*f)(StatInfo, int, int))
{
    int k;
    double r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}

/**
 * \brief Calcula o número total de vendas efetuadas num dado mês.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês do qual se pretende obter informação.
 * 
 * @returns O número total de vendas efetuadas no mês.
 * 
 * @see get_t_vendas_month_iter
 **/
int get_t_month_vendas(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas);
}

/**
 * \brief Calcula o número total de vendas com promoção efetuadas num dado mês.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês do qual se pretende obter informação.
 * 
 * @returns O número total de vendas com promoção efetuadas no mês.
 * 
 * @see get_t_vendas_month_iter
 **/
int get_t_month_vendas_promo(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_promo);
}

/**
 * \brief Calcula o número total de vendas sem promoção efetuadas num dado mês.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês do qual se pretende obter informação.
 * 
 * @returns O número total de vendas sem promoção efetuadas no mês.
 * 
 * @see get_t_vendas_month_iter
 **/
int get_t_month_vendas_no_promo(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_no_promo);
}

/**
 * \brief Calcula o lucro total associado à `key`.
 * 
 * @param a Informação estatistica associada à `key`.
 * 
 * @returns O lucro total obtido.
 **/
double get_t_rev(StatInfo a)
{
    return a->totalRevenue;
}

/**
 * \brief Calcula o lucro total associado à `key` numa filial.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O lucro total obtido em dada filial.
 **/
double get_t_fil_rev(StatInfo a, int filial)
{
    return (a->monthlyFilialRev[filial - 1][0][0] +
            a->monthlyFilialRev[filial - 1][0][1]);
}

/**
 * \brief Calcula o lucro total com promoções associado à `key` numa filial.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O lucro total com promoções obtido em dada filial.
 **/
double get_t_fil_rev_promo(StatInfo a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][1];
}

/**
 * \brief Calcula o lucro total sem promoções associado à `key` numa filial.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O lucro total sem promoções obtido em dada filial.
 **/
double get_t_fil_rev_no_promo(StatInfo a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][0];
}

/**
 * \brief Calcula o lucro total obtido num dado mês e filial.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O lucro total obtido num dado mês e filial.
 **/
double get_t_month_fil_rev(StatInfo a, int month, int filial)
{
    return (a->monthlyFilialRev[filial - 1][month][0] +
            a->monthlyFilialRev[filial - 1][month][1]);
}

/**
 * \brief Calcula o lucro total com promoção obtido num dado mês e filial.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O lucro total com promoção obtido num dado mês e filial.
 **/
double get_t_month_fil_rev_promo(StatInfo a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][1];
}

/**
 * \brief Calcula o lucro total sem promoção obtido num dado mês e filial.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O lucro total sem promoção obtido num dado mês e filial.
 **/
double get_t_month_fil_rev_no_promo(StatInfo a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][0];
}

/**
 * \brief Calcula o lucro total obtido num dado mês.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O lucro total obtido num dado mês. 
 **/
double get_t_month_rev(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev);
}

/**
 * \brief Calcula o lucro total com promoção obtido num dado mês.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O lucro total com promoção obtido num dado mês. 
 **/
double get_t_month_rev_promo(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_promo);
}

/**
 * \brief Calcula o lucro total sem promoção obtido num dado mês.
 * 
 * @param a Informação estatistica associada à `key`.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O lucro total sem promoção obtido num dado mês. 
 **/
double get_t_month_rev_no_promo(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_no_promo);
}

static void *my_specinfo_make(int flag)
{
    return (void *)specinfo_make(flag);
}

static void my_specinfo_destroy(void *si)
{
    specinfo_destroy((SpecInfo)si);
}

static void my_specinfo_update(void *si, void *e)
{
    specinfo_update((SpecInfo)si, e);
}
