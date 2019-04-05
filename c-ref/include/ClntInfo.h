#ifndef _CLNTINFO_
#define _CLNTINFO_

/**
 * \brief Tipo opaco representativo de uma instância da classe `ClntInfo`.
 */
typedef struct clntinfo *ClntInfo;

void *clntinfo_make();
void clntinfo_destroy(void *e);
void clntinfo_update(void *e, void *user_data);
int clntinfo_promo(ClntInfo ci, int filial);

#endif