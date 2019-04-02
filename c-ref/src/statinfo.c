/**
 * @file statinfo.c
 * \brief Módulo que define a classe `StatInfo` que é utilizada como meio de obtenção de informação estatística.
 * 
 * Através da utilização desta classe é possivél armazenar informação considerada útil para comunicar ao utilizador
 * do SGV importantes detalhes sobre compras e registos de transações.
 * 
 * Este módulo vê a sua utilidade quando se pretende comunicar com o utilizador do SGV quando este pretende obter
 * valores contabilisticos associados a um dado cliente ou um dado produto.
 */

#include "statinfo.h"
#include "util.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
void *statinfo_make();
void statinfo_destroy(void *);
void statinfo_builder(void *e, void *t);
StatInfo statinfo_clone(StatInfo si);

int get_n_actors(StatInfo);
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

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `StatInfo`.
 * 
 * Contem a definação de todos os recipientes de informação possivelmente util.
 * 
 * Em matrizes de recipientes de informação há uma posição extra (que surge por `N_MONTHS + 1`), esta posição
 * adicional que corresponde ao indice 0 corresponde ao valor total para aquela filial com ou sem promoção.
 */
typedef struct statistical_info
{
    int nVendasTotal,                                          /**< Número de transações */
        nVendasFilialMonth[N_FILIAIS][N_MONTHS + 1][N_PROMOS]; /**< Matriz que contem o número de transações separados por Filial, mês e a utilização de código promocional. */
    double totalCashFlow,                                      /**< Fluxo monetário total realizado. */
        monthlyFilialRev[N_FILIAIS][N_MONTHS + 1][N_PROMOS];   /**< Fluxo monetário contabilizador por Filial, Mês, com ou sem promoção ou só Filial com ou sem promoção. */
} * StatInfo;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Cria uma instância da classe `StatInfo` com valores zerados.
 * 
 * @returns Uma nova instância.
 */
void *statinfo_make()
{
    int l, c, k;
    StatInfo a = g_malloc(sizeof(struct statistical_info));

    for (l = 0; l < N_FILIAIS; l++)
    {
        for (c = 0; c <= N_MONTHS; c++)
        {
            for (k = 0; k < N_PROMOS; k++)
            {
                a->nVendasFilialMonth[l][c][k] = 0;
                a->monthlyFilialRev[l][c][k] = 0.0;
            }
        }
    }

    a->nVendasTotal = 0;
    a->totalCashFlow = 0.0;

    return a;
}

/**
 * \brief Destrói uma instância da classe `StatInfo`.
 * 
 * @param a Instância que se pretende destruir.
 */
void statinfo_destroy(void *a)
{
    if (a)
    {
        g_free((StatInfo)a);
    }
}

/**
 * \brief Dada uma venda, que é utilizada como um recurso de obtenção de informação estatistica, permite obter informação considerada contabilisticamente útil sobre esta.
 *
 * @param t `Transaction` usada como meio de obtenção de informação.
 * @param e Instância de `StatInfo` a ser utilizada como recipiente de informação.
 */
void statinfo_builder(void *e, void *t)
{
    if (!e || !t)
        return;
    StatInfo si = (StatInfo)e;
    Transaction tr = (Transaction)t;

    double rev = trans_get_rev(tr);
    int f, m, p = trans_get_promo(tr);
    m = trans_get_month(tr);
    f = trans_get_filial(tr);

    si->nVendasTotal++;
    si->nVendasFilialMonth[f - 1][0][indP(p)]++;
    si->nVendasFilialMonth[f - 1][m][indP(p)]++;

    si->totalCashFlow += rev;
    si->monthlyFilialRev[f - 1][0][indP(p)] += rev;
    si->monthlyFilialRev[f - 1][m][indP(p)] += rev;
}

/**
 * \brief Retorna uma cópia da instância.
 * 
 * @returns A cópia criada, ou NULL caso a instância seja inválida.
 */
StatInfo statinfo_clone(StatInfo si)
{
    if (!si)
        return NULL;

    int l, c, k;
    StatInfo sc = g_malloc(sizeof(struct statistical_info));

    for (l = 0; l < N_FILIAIS; l++)
    {
        for (c = 0; c <= N_MONTHS; c++)
        {
            for (k = 0; k < N_PROMOS; k++)
            {
                sc->nVendasFilialMonth[l][c][k] = si->nVendasFilialMonth[l][c][k];
                sc->monthlyFilialRev[l][c][k] = si->monthlyFilialRev[l][c][k];
            }
        }
    }

    sc->nVendasTotal = si->nVendasTotal;
    sc->totalCashFlow = si->totalCashFlow;

    return sc;
}

/**
 * \brief Calcula o número total de transações.
 * 
 * @param si Instância a ser considerada.
 * 
 * @returns O número total de transações.
 */
int get_t_vendas(StatInfo si)
{
    return si->nVendasTotal;
}

/**
 * \brief Calcula o número total de transações por filial
 * 
 * @param a Instância a ser considerada.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por filial.
 */
int get_t_fil_vendas(StatInfo a, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][0][0] + a->nVendasFilialMonth[filial - 1][0][1]);
}

/**
 * \brief Calcula o número total de transações por filial, com promoção
 * 
 * @param a Instância a ser considerada.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por filial, com promoção.
 */
int get_t_fil_vendas_promo(StatInfo a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][1];
}

/**
 * \brief Calcula o número total de transações por filial, sem promoção
 * 
 * @param a Instância a ser considerada.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por filial, sem promoção.
 */
int get_t_fil_vendas_no_promo(StatInfo a, int filial)
{
    return a->nVendasFilialMonth[filial - 1][0][0];
}

/**
 * \brief Calcula o número total de transações por mês e filial.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por mês e filial.
 */
int get_t_month_fil_vendas(StatInfo a, int month, int filial)
{
    return (a->nVendasFilialMonth[filial - 1][month][0] +
            a->nVendasFilialMonth[filial - 1][month][1]);
}

/**
 * \brief Calcula o número total de transações por mês e filial, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por mês e filial, com promoção.
 */
int get_t_month_fil_vendas_promo(StatInfo a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][1];
}

/**
 * \brief Calcula o número total de transações por mês e filial, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número total de transações por mês e filial, sem promoção.
 */
int get_t_month_fil_vendas_no_promo(StatInfo a, int month, int filial)
{
    return a->nVendasFilialMonth[filial - 1][month][0];
}

/**
 * \brief Calcula o número total de transações por mês.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número total de transações por mês.
 */
int get_t_month_vendas(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas);
}

/**
 * \brief Calcula o número total de transações por mês, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número total de transações por mês, com promoção.
 */
int get_t_month_vendas_promo(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_promo);
}

/**
 * \brief Calcula o número total de transações por mês, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O número total de transações por mês, sem promoção.
 */
int get_t_month_vendas_no_promo(StatInfo a, int month)
{
    return get_t_vendas_month_iter(a, month, get_t_month_fil_vendas_no_promo);
}

/**
 * \brief Calcula o fluxo monetário total associado à instância.
 * 
 * @param a Instância a ser considerada.
 * 
 * @returns O Fluxo monetário total.
 */
double get_t_rev(StatInfo a)
{
    return a->totalCashFlow;
}

/**
 * \brief Calcula o fluxo monetário total associado a uma dada filial.
 * 
 * @param a Instância a ser considerada.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O Fluxo monetário total associado a uma dada filial.
 */
double get_t_fil_rev(StatInfo a, int filial)
{
    return (a->monthlyFilialRev[filial - 1][0][0] +
            a->monthlyFilialRev[filial - 1][0][1]);
}

/**
 * \brief Calcula o fluxo monetário total associado a uma dada filial, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O Fluxo monetário total associado a uma dada filial, com promoção.
 */
double get_t_fil_rev_promo(StatInfo a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][1];
}

/**
 * \brief Calcula o fluxo monetário total associado a uma dada filial, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O Fluxo monetário total associado a uma dada filial, sem promoção.
 */
double get_t_fil_rev_no_promo(StatInfo a, int filial)
{
    return a->monthlyFilialRev[filial - 1][0][0];
}

/**
 * \brief Calcula o fluxo monetário total de um dado mês e filial.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O fluxo monetário total associado a um dado mês e filial.
 */
double get_t_month_fil_rev(StatInfo a, int month, int filial)
{
    return (a->monthlyFilialRev[filial - 1][month][0] +
            a->monthlyFilialRev[filial - 1][month][1]);
}

/**
 * \brief Calcula o fluxo monetário total de um dado mês e filial, com promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O fluxo monetário total associado a um dado mês e filial, com promoção.
 */
double get_t_month_fil_rev_promo(StatInfo a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][1];
}

/**
 * \brief Calcula o fluxo monetário total de um dado mês e filial, sem promoção.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O fluxo monetário total associado a um dado mês e filial, sem promoção.
 */
double get_t_month_fil_rev_no_promo(StatInfo a, int month, int filial)
{
    return a->monthlyFilialRev[filial - 1][month][0];
}

/**
 * \brief Calcula o fluxo monetário total de um dado mês.
 * 
 * Este método tira partido de uma função que permite a iteração sobre a matriz
 * recipiente atual utilizada, de forma a calcular os valores pretendidos.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O fluxo monetário total de um dado mês.
 */
double get_t_month_rev(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev);
}

/**
 * \brief Calcula o fluxo monetário total de um dado mês, com promoção.
 * 
 * Este método tira partido de uma função que permite a iteração sobre a matriz
 * recipiente atual utilizada, de forma a calcular os valores pretendidos.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O fluxo monetário total de um dado mês, com promoção.
 * 
 * @see get_t_rev_month_iter
 * @see get_t_month_fil_rev_promo
 */
double get_t_month_rev_promo(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_promo);
}

/**
 * \brief Calcula o fluxo monetário total de um dado mês, sem promoção.
 * 
 * Este método tira partido de uma função que permite a iteração sobre a matriz
 * recipiente atual utilizada, de forma a calcular os valores pretendidos.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * 
 * @returns O fluxo monetário total de um dado mês, sem promoção.
 *
 * @see get_t_rev_month_iter
 * @see get_t_month_fil_rev_no_promo
 */
double get_t_month_rev_no_promo(StatInfo a, int month)
{
    return get_t_rev_month_iter(a, month, get_t_month_fil_rev_no_promo);
}

/**
 * \brief Permite iterar uma dada função sobre todos os valores que formam o número de vendas total de um mês e obter informação sobre estes.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param f Função de obtenção de informação de um dado ponto por mês e filial.
 * 
 * @returns O valor calculado através da função de obtenção de informação.
 */
static int get_t_vendas_month_iter(StatInfo a, int month, int (*f)(StatInfo, int, int))
{
    int k, r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}

/**
 * \brief Permite iterar uma dada função sobre todos os valores que formam o fluxo monetário de um mês e obter informação sobre estes.
 * 
 * @param a Instância a ser considerada.
 * @param month Mês que se pretende verificar.
 * @param f Função de obtenção de informação de um dado ponto por mês e filial.
 * 
 * @returns O valor calculado através da função de obtenção de informação.
 */
static double get_t_rev_month_iter(StatInfo a, int month, double (*f)(StatInfo, int, int))
{
    int k;
    double r = 0;

    for (k = 1; k <= N_FILIAIS; k++)
        r += (*f)(a, month, k);

    return r;
}