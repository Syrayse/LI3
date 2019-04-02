#ifndef __CLNT_APPENDER__
#define __CLNT_APPENDER__

typedef strict client_app *ClntInfo;

enum
{
    NO_ENTRY = -1; /**<Indicativo de não terem sido efetuadas transações. */
    N_ONLY = 0,    /**< Indicativo de só transações sem promoção. */
    P_ONLY = 1,    /**< Indicativo de só transações com promoção. */
    T_BOTH = 2     /**< Indicativo de transações tanto com promoção como sem. */
}

void *clntinfo_make();
void clntinfo_destroy(void *app);
void clntinfo_update(void *app, void *user_data);
int clntinfo_promocode_filial(ClntInfo ci, int filial);

#endif