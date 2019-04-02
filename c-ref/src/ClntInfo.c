/**
 * @file ClntInfo.c
 * \brief Define a classe `ClntInfo` e todos os seus metódos utéis.
 * 
 * Esta classe tem o objetivo de permitir uma facilidade na representação
 * de relações pela classe `FilManager`.
 */

#include "ClntInfo.h"
#include "util.h"
#include "Verifier.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
void *clntinfo_make();
void clntinfo_destroy(void *app);
void clntinfo_update(void *app, void *user_data);
int clntinfo_promocode_filial(ClntInfo ci, int filial);

/* Metódos privados */
/* Nenhum */

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `ClntInfo`.
 * 
 * Após a analise das várias _Queries_ chegou-se à conclusão
 * que aliada à construção fornecida pela classe `FilManager`, que a classe
 * `ClntInfo` pouca informação deve conter, que se apresenta apenas útil para uma query (8).
 * 
 * Esta classe é composta por um array com  `N_FILIAIS` elementos, sendo que cada posição possui
 * do tipo de transações que já foram efetuadas por um dado cliente em uma dada filial.
 * 
 * Segue a seguinte pré-definição.
 * 
 *  N_ONLY -> Só efetuou compras sem promoção.
 *  P_ONLY -> Só efetuou compras com promoção.
 *  T_BOTH -> Efetuou tanto compras com promoção.
 * 
 * Aquando da criação de uma instância desta classe todos os valores são inicializados
 * a -1, sendo esta a representação de não terem sido efetuadas transações naquela filial.
 */
typedef struct client_app
{
    signed char promo_regist[N_FILIAIS];
} * ClntInfo;

/* ------------------------------------------------------------------------------ */

enum
{
    NO_ENTRY = -1; /**<Indicativo de não terem sido efetuadas transações. */
    N_ONLY = 0,    /**< Indicativo de só transações sem promoção. */
    P_ONLY = 1,    /**< Indicativo de só transações com promoção. */
    T_BOTH = 2     /**< Indicativo de transações tanto com promoção como sem. */
}

/* ------------------------------------------------------------------------------ */

/**
 * \brief
 */
void *clntinfo_make()
{
    int i;

    ClntInfo ci = g_malloc(sizeof(struct client_app));

    for (i = 0; i < N_FILIAIS; i++)
    {
        ci->promo_regist[i] = -1;
    }

    return ci;
}

/**
 * \brief
 */
void clntinfo_destroy(void *app)
{
    if(app)
    {
        g_free(app);
    }
}

/**
 * \brief
 */
void clntinfo_update(void *app, void *user_data)
{
    if(!user_data)
        return;
    

    Transaction t = (Transaction)user_data;
    int filial = trans_get_filial(t) - 1;

    switch()
}

/**
 * \brief
 */
int clntinfo_promocode_filial(ClntInfo ci, int filial)
{

}