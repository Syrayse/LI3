#include "sale.h"
#include "appender.h"
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
APPENDER make_appender();
void update_appender(APPENDER, void *);
int is_sold_by_all(APPENDER);
int get_t_vendas(APPENDER);
int get_t_fil_vendas(APPENDER, int filial);
int get_t_fil_vendas_promo(APPENDER, int filial);
int get_t_fil_vendas_no_promo(APPENDER, int filial);
int get_t_month_fil_vendas(APPENDER, int month, int filial);
int get_t_month_fil_vendas_promo(APPENDER, int month, int filial);
int get_t_month_fil_vendas_no_promo(APPENDER, int month, int filial);
int get_t_month_vendas(APPENDER, int month);
int get_t_month_vendas_promo(APPENDER, int month);
int get_t_month_vendas_no_promo(APPENDER, int month);
double get_t_rev(APPENDER);
double get_t_fil_rev(APPENDER, int filial);
double get_t_fil_rev_promo(APPENDER, int filial);
double get_t_fil_rev_no_promo(APPENDER, int filial);
double get_t_month_fil_rev(APPENDER, int month, int filial);
double get_t_month_fil_rev_promo(APPENDER, int month, int filial);
double get_t_month_fil_rev_no_promo(APPENDER, int month, int filial);
double get_t_month_rev(APPENDER, int month);
double get_t_month_rev_promo(APPENDER, int month);
double get_t_month_rev_no_promo(APPENDER, int month);
void destroy_appender(void *);

/* Metodos privados */
static int get_t_vendas_month_iter(APPENDER a, int month, int (*)(APPENDER, int, int));
static double get_t_rev_month_iter(APPENDER a, int month, double (*)(APPENDER, int, int));

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de dados que contém informção estatistica de cada cliente/produto.
 **/
typedef struct appendix
{
    int nVendasTotal,                                   /**< Número de registos de vendas associados */
        nVendasFilialMonth[N_FILIAIS][N_MONTHS + 1][2]; /**< Numero de registos de vendas associados por filial e mễs */
    double totalRevenue,                                 /**< Rendimento total associado */
        monthlyFilialRev[N_FILIAIS][N_MONTHS + 1][2];   /**< Rendimento total associado por filial e mês*/
} * APPENDER;

// ------------------------------------------------------------------------------

/**
 * \brief Criar em memória estrutura onde são armazenados os dados estatisticos.
 * 
 * @returns A estrutura alocada.
 **/
APPENDER make_appender()
{
    int l, c, k;
    APPENDER a = g_malloc(sizeof(struct appendix));

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
 * \brief Atualiza os dados estatisticos consoante um registo de venda.
 * 
 * @param a Contentor de informação estatistica que ira ser atualizado.
 * @param e Registo de venda que servirá para atualizar a informação.
 **/
void update_appender(APPENDER a, void *e)
{
    if (!e)
        return;
    SALE s = (SALE)e;
    double rev = get_rev_s(s);
    int f, m, p = get_promo_s(s);
    m = get_month_s(s);
    f = get_filial_s(s);

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
int is_sold_by_all(APPENDER a)
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
int get_t_vendas(APPENDER a)
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
int get_t_fil_vendas(APPENDER a, int filial)
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
int get_t_fil_vendas_promo(APPENDER a, int filial)
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
int get_t_fil_vendas_no_promo(APPENDER a, int filial)
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
int get_t_month_fil_vendas(APPENDER a, int month, int filial)
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
int get_t_month_fil_vendas_promo(APPENDER a, int month, int filial)
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
int get_t_month_fil_vendas_no_promo(APPENDER a, int month, int filial)
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
static int get_t_vendas_month_iter(APPENDER a, int month, int (*f)(APPENDER, int, int))
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
static double get_t_rev_month_iter(APPENDER a, int month, double (*f)(APPENDER, int, int))
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
int get_t_month_vendas(APPENDER a, int month)
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
int get_t_month_vendas_promo(APPENDER a, int month)
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
int get_t_month_vendas_no_promo(APPENDER a, int month)
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
double get_t_rev(APPENDER a)
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
double get_t_fil_rev(APPENDER a, int filial)
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
double get_t_fil_rev_promo(APPENDER a, int filial)
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
double get_t_fil_rev_no_promo(APPENDER a, int filial)
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
double get_t_month_fil_rev(APPENDER a, int month, int filial)
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
double get_t_month_fil_rev_promo(APPENDER a, int month, int filial)
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
double get_t_month_fil_rev_no_promo(APPENDER a, int month, int filial)
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
double get_t_month_rev(APPENDER a, int month)
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
double get_t_month_rev_promo(APPENDER a, int month)
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
double get_t_month_rev_no_promo(APPENDER a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_no_promo);
}

/**
 * \brief Liberta a memória de um dado contento de informção estatistica.
 * 
 * @param a Contentor a libertar.
 **/
void destroy_appender(void *a)
{
    if (a)
        g_free((APPENDER)a);
}