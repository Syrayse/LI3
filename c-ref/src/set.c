#include "set.h"
#include "gArray.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
StrSet strset_make(freefunc ff);
void strset_destroy(StrSet set);
int strset_add(StrSet set, char *elem, void *value);
int strset_remove(StrSet set, char *elem);
void strset_foreach(StrSet set, f_foreach fer, void *user_data);
int strset_contains(StrSet set, char *elem);
int strset_size(StrSet set);
int strset_update_elem(StrSet set, char *elem, void (*f_up)(void *, void *), void *user_data);
void *strset_value_of(StrSet set, char *elem);
char **strset_dump(StrSet set, size_t *n);
char **strset_dump_ordered(StrSet set, fcompar fc, size_t *n);

/* Metodos privados */
static void insert_str(void *key, void *value, void *user_data);
static char **generic_dump(StrSet set, size_t *n, int flag);

// ------------------------------------------------------------------------------

typedef struct set
{
    GHashTable *table;
} * StrSet;

// ------------------------------------------------------------------------------

/**
 * \brief Cria um set.
 * 
 * @param ff Função a ser utilizada para libertar os elementos do set.
 * 
 * @returns O set criado.
 **/
StrSet strset_make(freefunc ff)
{
    StrSet set = g_malloc(sizeof(struct set));
    set->table = g_hash_table_new_full(g_str_hash, g_str_equal, ff, g_free);
    return set;
}

/**
 * \brief Destroi um set.
 * 
 * @param set Set que será destruido.
 **/
void strset_destroy(StrSet set)
{
    if (set)
    {
        g_hash_table_destroy(set->table);
        g_free(set);
    }
}

/**
 * \brief Adiciona uma chave ao Set.
 * 
 * @param set Set onde irá ser adicionado o elemento.
 * @param elem Elemento a ser adicionado.
 * @param value Informação associada ao elemento adicionado.
 * 
 * @returns 1 se o elemento for adicionado com sucesso, 0 se ele já existir no Set.
 **/
int strset_add(StrSet set, char *elem, void *value)
{
    return g_hash_table_insert(set->table, elem, value);
}

/**
 * \brief Remove um elemento do Set.
 * 
 * @param set Set de onde será removido o elemento.
 * @param elem Elemento a ser removido.
 * 
 * @returns 1 se o elemento for removido com sucesso, 0 se ele não existir no Set.
 **/
int strset_remove(StrSet set, char *elem)
{
    return g_hash_table_remove(set->table, elem);
}

/**
 * \brief Aplica uma dada função a todos os elementos do Set.
 * 
 * @param set Set onde irá ser aplicada a função.
 * @param fe Função de mapeamento a ser utilizada.
 **/
void strset_foreach(StrSet set, void (*fe)(void *, void *, void *), void *user_data)
{
    g_hash_table_foreach(set->table, fe, user_data);
}

/**
 * \brief Verifica se um elemento existe no Set.
 * 
 * @param set Set onde se pretende verificar.
 * @param elem Elemento que se pretende verificar.
 * 
 * @returns 0 se o elemento não existir, 1 caso contrário.
 **/
int strset_contains(StrSet set, char *elem)
{
    return g_hash_table_contains(set->table, elem);
}

/**
 * \brief Calcula o número de elementos do Set.
 * 
 * @param set Set que se pretender verificar.
 * 
 * @returns O número de elementos do Set.
 **/
int strset_size(StrSet set)
{
    return g_hash_table_size(set->table);
}

/**
 * \brief Retorna um array contendo todos os elementos do Set.
 * 
 * @param set Set no qual se pretende verificar.
 * @param n Endereço onde será colocado o número de elementos obtido.
 * 
 * @returns Array contendo todos os elementos do Set original.
 **/
char **strset_dump(StrSet set, size_t *n)
{
    return generic_dump(set, n, 1);
}

/**
 * \brief Retorna um array contendo todos elementos do Set de forma ordenada.
 * 
 * @param set Set no qual se pretende verificar.
 * @param fc Função de comparação.
 * @param n Endereço onde será colocado o número de elementos obtido.
 * 
 * @returns Array contendo todos os elementos do Set original de forma ordenada.
 **/
char **strset_dump_ordered(StrSet set, fcompar fc, size_t *n)
{
    return generic_dump(set, n, 0);
}

/**
 * \brief Atualiza um elemento no Set, consoante uma dada função de comparação que recebe um value e user_data.
 * 
 * @param set Set a verificar.
 * @param elem Elemento que se pretende atualizar.
 * @param f_up Função de atualização utilizada.
 * @param user_data Informação necessára à função de atualização.
 * 
 * @returns 1 se o elemento existir, 0 caso contrário.
 **/
int strset_update_elem(StrSet set, char *elem, void (*f_up)(void *, void *), void *user_data)
{
    void *tmp;

    if ((tmp = g_hash_table_lookup(set->table, elem)))
    {
        (*f_up)(tmp, user_data);
    }

    return tmp ? 1 : 0;
}

/**
 * \brief Calcula o endereço da informação associada ao elemento.
 * 
 * @param set Set que se pretende verificar.
 * @param elem Elemento do qual se pretende obter a informação.
 * 
 * @returns A informação associada ao elemento.
 **/
void *strset_value_of(StrSet set, char *elem)
{
    return g_hash_table_lookup(set->table, elem);
}

/**
 * \brief Função que coloca um elemento num GrowingArray.
 * 
 * @param key Elemento a ser colocado.
 * @param value Valor do elemento a ser colocado.
 * @param user_data GrowingArray onde serão colocados os elementos.
 **/
static void insert_str(void *key, void *value, void *user_data)
{
    if (user_data)
        insert_elem_garray((GrowingArray)user_data, key);
}

/**
 * \brief Efetua um dump generico, dependendo do valor da flag efetua ou não ordenação.
 * 
 * @param set Set que irá ser verificado.
 * @param n Endereço onde será colocado o número de elementos obtido.
 * @param flag Flag que explicita a ordenanão ou não-ordenação.
 * 
 * @returns Array contendo todos os valores obtidos do Set original segundo a flag.
 **/
static char **generic_dump(StrSet set, size_t *n, int flag)
{
    GrowingArray ga = make_garray(sizeof(char *), g_free);

    strset_foreach(set, insert_str, ga);

    if (!flag)
        sort_garray(ga, strcmp_client);

    return (char **)dump_elems_garray(ga, n);
}