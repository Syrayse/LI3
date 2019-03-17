#include "set.h"
#include "gArray.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
StrSet strset_make(freefunc ffkey, freefunc ffvalue, f_maker fm, f_update fu, int flag);
void strset_destroy(StrSet set);
int strset_add(StrSet set, void *elem, void *user_data);
int strset_remove(StrSet set, void *elem);
void strset_foreach(StrSet set, f_foreach fer, void *user_data);
int strset_contains(StrSet set, void *elem);
int strset_size(StrSet set);
void *strset_value_of(StrSet set, void *elem);
char **strset_dump(StrSet set, size_t *n);
char **strset_dump_ordered(StrSet set, fcompare fc, size_t *n);
char **strset_dump_if(StrSet set, Predicate p, size_t *n, int flag);

/* Metodos privados */
//None

// ------------------------------------------------------------------------------

typedef struct set
{
    int not_init;
    GHashTable *table;
    f_maker fm;
    f_update fu;
    int identity;
} * StrSet;

// ------------------------------------------------------------------------------

/**
 * \brief Cria um set.
 * 
 * @param ff Função a ser utilizada para libertar os elementos do set.
 * 
 * @returns O set criado.
 **/
StrSet strset_make(freefunc ffkey, freefunc ffvalue, f_maker fm, f_update fu, int flag)
{
    StrSet set = g_malloc(sizeof(struct set));
    set->not_init = 0;
    set->table = g_hash_table_new_full(g_str_hash, g_str_equal, ffkey, ffvalue);
    set->fm = fm;
    set->fu = fu;
    set->identity = flag;
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

int strset_get_not_init_n(StrSet set)
{
    return set->not_init;
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
int strset_add(StrSet set, void *elem, void *user_data)
{
    int r = -1;
    void *val = NULL;

    if (set->fm && !(val = g_hash_table_lookup(set->table, elem)))
    {
        r = 1;
        val = (*set->fm)(set->identity);
        g_hash_table_insert(set->table, elem, val);
        set->not_init++;
    }

    if (set->fu && user_data && val)
    {
        r++;
        (*set->fu)(val, user_data);
    }

    return r;
}

/**
 * \brief Remove um elemento do Set.
 * 
 * @param set Set de onde será removido o elemento.
 * @param elem Elemento a ser removido.
 * 
 * @returns 1 se o elemento for removido com sucesso, 0 se ele não existir no Set.
 **/
int strset_remove(StrSet set, void *elem)
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
int strset_contains(StrSet set, void *elem)
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
    return strset_dump_if(set, NULL, n, 1);
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
char **strset_dump_ordered(StrSet set, fcompare fc, size_t *n)
{
    return strset_dump_if(set, NULL, n, 0);
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
void *strset_value_of(StrSet set, void *elem)
{
    return g_hash_table_lookup(set->table, elem);
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
char **strset_generic_dump(StrSet set, f_foreach ffor, size_t *n, int flag)
{
    char **r;
    GrowingArray ga = garray_make(sizeof(char *), g_free);

    strset_foreach(set, ffor, ga);

    if (!flag)
        garray_sort(ga, mystrcmp);

    r = (char **)garray_dump_elems(ga, n);

    garray_destroy(ga);

    return r;
}

char **strset_dump_if(StrSet set, Predicate p, size_t *n, int flag)
{
    char **r = NULL;

    GHashTableIter iter;
    gpointer key, value;

    GrowingArray ga = garray_make(sizeof(char *), g_free);

    g_hash_table_iter_init(&iter, set->table);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        if (!p || (value && (*p)(value)))
            garray_add(ga, key);
    }

    if (!flag)
        garray_sort(ga, mystrcmp);

    r = (char **)garray_dump_elems(ga, n);

    garray_destroy(ga);

    return r;
}
