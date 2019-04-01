/**
 * @file Accounting.h
 * \brief Módulo que define a classe `Accounting` destinada ao uso como contabilidade.
 */
#include "Accounting.h"
#include "statinfo.h"
#include "util.h"
#include "Verifier.h"
#include "set.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_update(Accounting a, Transaction t);
void Accounting_add_product(Accounting a, char *product);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_n_cash_range(Accounting A, int init, int end);
StatInfo Accounting_get_statinfo(Accounting a, char *product);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

/**
 * \brief Define a estrutura da classe `Accounting`.
 * 
 * Esta estrutura tem como prioridade ser utilizada na prespectiva de metódo
 * de contabilidade eficiente para os serviços SGV.
 */
typedef struct accounting
{
    int nTrans[N_MONTHS];         /**< Número de transações mensais. */
    double totCashFlow[N_MONTHS]; /**< Fluxo monetário mensal. */
    StrSet products;              /**< Conjunto que armazenada todos os produtos. */
} * Accounting;

// ------------------------------------------------------------------------------

/**
 * \brief Cria uma instância da classe `Accounting`.
 * 
 * Para além de criar a instância, inicializa todos as variavéis necessárias.
 * 
 * @returns Uma instância da classe `Accounting`.
 */
Accounting Accounting_make()
{
    int i;
    Accounting a = g_malloc(sizeof(struct accounting));

    for (i = 0; i < N_MONTHS; i++)
    {
        a->totCashFlow[i] = 0.0;
        a->nTrans[i] = 0;
    }

    a->products = strset_make(g_free, statinfo_destroy, statinfo_make, statinfo_builder, NULL);

    return a;
}

/**
 * \brief Destrói uma instância da classe `Accounting`.
 * 
 * @param a Instância a destruir.
 */
void Accounting_destroy(Accounting a)
{
    if (a)
    {
        strset_destroy(a->products);
        g_free(a);
    }
}

/**
 * \brief Atualiza os valores da contabilidade de acordo com uma transação.
 * 
 * @param a Instância a considerar.
 * @param t Transação usada na atualização de valores.
 */
void Accounting_update(Accounting a, Transaction t)
{
    if (!t)
        return;

    int month = trans_get_month(t) - 1;

    char product[PROD_LEN + 1];

    trans_copy_product(t, product);

    strset_add(a->products, product, t);

    a->nTrans[month]++;

    a->totCashFlow[month] += trans_get_rev(t);
}

/**
 * \brief Calcula o número de transações efetuadas entre dois meses.
 * 
 * @param a Instância a considerar.
 * @param init Mês inicial.
 * @param end Mês final.
 * 
 * @returns O valor calculado, ou -1 caso os meses sejam inválidos.
 */
int Accounting_n_trans_range(Accounting a, int init, int end)
{
    int i, r = -1;

    if (is_between(init, 1, N_MONTHS) && is_between(end, 1, N_MONTHS) && init <= end)
    {
        r = 0;

        for (i = init; i <= end; r += a->nTrans[i], i++)
            ;
    }

    return r;
}

/**
 * \brief Calcula o fluxo monetário entre dois meses.
 * 
 * @param a Instância a considerar.
 * @param init Mês inicial.
 * @param end Mês final.
 * 
 * @returns O valor calculado, ou -1.0 caso os meses sejam inválidos.
 */
double Accounting_n_cash_range(Accounting a, int init, int end)
{
    int i;
    double r = -1.0;

    if (is_between(init, 1, N_MONTHS) && is_between(end, 1, N_MONTHS) && init <= end)
    {
        r = 0.0;

        for (i = init; i <= end; r += a->totCashFlow[i], i++)
            ;
    }

    return r;
}

/**
 * \brief Cria uma cópia da informação contabilistica associada a um produto.
 * 
 * @param a Instância a considerar.
 * @param product Produto que se pretende verificar.
 * 
 * @returns A cópia formada, ou NULL caso o produto não exista.
 * 
 * @see statinfo_clone
 */
StatInfo Accounting_get_statinfo(Accounting a, char *product)
{
    void *tmp = strset_lookup(a->products, product);
    return tmp ? statinfo_clone((StatInfo)tmp) : NULL;
}