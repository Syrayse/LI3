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
StatInfo statinfo_make();
void statinfo_destroy(StatInfo si);
void statinfo_update(StatInfo si, void *user);

int get_t_units(StatInfo si);
int get_t_units_fil(StatInfo si, int filial);

int get_n_actors(StatInfo);
int get_t_vendas(StatInfo);
int get_t_month_fil_vendas(StatInfo, int month, int filial);
int get_t_month_fil_vendas_promo(StatInfo, int month, int filial);
int get_t_month_fil_vendas_no_promo(StatInfo, int month, int filial);
int get_t_month_vendas(StatInfo, int month);
int get_t_month_vendas_promo(StatInfo, int month);
int get_t_month_vendas_no_promo(StatInfo, int month);

double get_t_rev(StatInfo);
double get_t_month_fil_rev(StatInfo, int month, int filial);
double get_t_month_fil_rev_promo(StatInfo, int month, int filial);
double get_t_month_fil_rev_no_promo(StatInfo, int month, int filial);
double get_t_month_rev(StatInfo, int month);
double get_t_month_rev_promo(StatInfo, int month);
double get_t_month_rev_no_promo(StatInfo, int month);

/* Metodos privados */

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
        nVendasFilialMonth[N_MONTHS][N_FILIAIS + 1][N_PROMOS], /**< Matriz que contem o número de transações separados por Filial, mês e a utilização de código promocional. */
        totalUnits,
        nQuantFilial[N_FILIAIS];
    double totalCashFlow,                                    /**< Fluxo monetário total realizado. */
        monthlyFilialRev[N_MONTHS][N_FILIAIS + 1][N_PROMOS]; /**< Fluxo monetário contabilizador por Filial, Mês, com ou sem promoção ou só Filial com ou sem promoção. */
} * StatInfo;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Cria uma instância da classe `StatInfo` com valores zerados.
 * 
 * @returns Uma nova instância.
 */
StatInfo statinfo_make()
{
    int l, c, k;
    StatInfo a = g_malloc(sizeof(struct statistical_info));

    for (l = 0; l < N_MONTHS; l++)
    {
        for (c = 0; c <= N_FILIAIS; c++)
        {
            for (k = 0; k < N_PROMOS; k++)
            {
                a->nVendasFilialMonth[l][c][k] = 0;
                a->monthlyFilialRev[l][c][k] = 0.0;
            }
        }
    }

    for (l = 0; l < N_FILIAIS; l++)
    {
        a->nQuantFilial[l] = 0;
    }

    a->nVendasTotal = 0;
    a->totalCashFlow = 0.0;
    a->totalUnits = 0;

    return a;
}

/**
 * \brief Destrói uma instância da classe `StatInfo`.
 * 
 * @param a Instância que se pretende destruir.
 */
void statinfo_destroy(StatInfo si)
{
    if (si)
    {
        g_free(si);
    }
}

/* Assume que recebe [month]+[filial]+[units]+[promo]+[spent] */
void statinfo_update(StatInfo si, void *user_data)
{
    void **holder = (void **)user_data;
    double spent = *(double *)holder[4];
    int units, filial, month, promo = *(int *)holder[3];
    units = *(int *)holder[2];
    filial = *(int *)holder[1];
    month = *(int *)holder[0] - 1;

    si->nVendasTotal++;
    si->nVendasFilialMonth[month][0][promo]++;
    si->nVendasFilialMonth[month][filial][promo]++;

    si->totalCashFlow += spent;
    si->monthlyFilialRev[month][0][promo] += spent;
    si->monthlyFilialRev[month][filial][promo] += spent;

    si->totalUnits += units;
    si->nQuantFilial[filial - 1] += units;
}

int get_t_units(StatInfo si)
{
    return si->totalUnits;
}

int get_t_units_fil(StatInfo si, int filial)
{
    return si->nQuantFilial[filial - 1];
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
    return (a->nVendasFilialMonth[month - 1][filial][0] +
            a->nVendasFilialMonth[month - 1][filial][1]);
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
    return a->nVendasFilialMonth[month - 1][filial][1];
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
    return a->nVendasFilialMonth[month - 1][filial][0];
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
    return (a->nVendasFilialMonth[month - 1][0][0] + a->nVendasFilialMonth[month - 1][0][1]);
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
    return a->nVendasFilialMonth[month - 1][0][1];
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
    return a->nVendasFilialMonth[month - 1][0][0];
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
    return (a->monthlyFilialRev[month - 1][filial][0] +
            a->monthlyFilialRev[month - 1][filial][1]);
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
    return a->monthlyFilialRev[month - 1][filial][1];
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
    return a->monthlyFilialRev[month - 1][filial][0];
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
    return (a->monthlyFilialRev[month - 1][0][0] + a->monthlyFilialRev[month - 1][0][1]);
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
    return a->monthlyFilialRev[month - 1][0][1];
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
    return a->monthlyFilialRev[month - 1][0][0];
}