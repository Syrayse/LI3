#include "set.h"
#include "gArray.h"
#include "specinfo.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
StrSet strset_make(freefunc ffkey, freefunc ffvalue, f_maker fm, f_update fu, int flag);
void strset_destroy(StrSet set);
int strset_add(StrSet set, void *elem, void *user_data);
int strset_remove(StrSet set, void *elem);
void strset_foreach(StrSet set, f_foreach fer, void *user_data);
int strset_contains(StrSet set, void *elem);
int strset_size(StrSet set);
void *strset_lookup(StrSet set, void *key);
void *strset_value_of(StrSet set, void *elem);
char **strset_dump(StrSet set, size_t *n);
char **strset_dump_ordered(StrSet set, fcompare fc, size_t *n);
int strset_get_not_init_n(StrSet set);

char **get_all_promo_fil(StrSet set, size_t *n, int filial);
char **get_all_no_promo_fil(StrSet set, size_t *n, int filial);
char **get_sort_quant_month(StrSet set, size_t *n, int month);

/* Metodos privados */
static char **strset_dump_if(StrSet set, Predicate p, fcompare fc, void *user_data, size_t *n);
static int filter_filial_promo(const void *a, const void *b);
static int filter_filial_no_promo(const void *a, const void *b);
static int filter_month(const void *a, const void *b);
static void *uncurry_dummy(void *d);
static int strcmp_dummy(const void *a, const void *b);
static int compare_quants(const void *a, const void *b);

// ------------------------------------------------------------------------------

typedef struct set
{
    int not_init;
    GHashTable *table;
    f_maker fm;
    f_update fu;
    int identity;
} * StrSet;

typedef struct dummy
{
    void *key;
    void *value;
    void *user_data;
} * Dummy;

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

    if (!(val = g_hash_table_lookup(set->table, elem)) && set->fm)
    {
        r = 1;
        val = (*set->fm)(set->identity);
        g_hash_table_insert(set->table, elem, val);
        set->not_init++;
    }

    if (set->fu && user_data && val)
    {
        if (r == 1)
            set->not_init--;
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
    return strset_dump_if(set, NULL, strcmp_dummy, NULL, n);
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
    return strset_dump_if(set, NULL, strcmp_dummy, NULL, n);
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

void *strset_lookup(StrSet set, void *key)
{
    return g_hash_table_lookup(set->table, key);
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
    GrowingArray ga = garray_make(sizeof(char *), NULL);

    strset_foreach(set, ffor, ga);

    if (!flag)
        garray_sort(ga, mystrcmp);

    r = (char **)garray_dump_elems(ga, NULL, n);

    garray_destroy(ga);

    return r;
}

char **get_all_promo(StrSet set, size_t *n, int filial)
{
    char **r = NULL;
    int f = filial;

    if (is_between(f, 1, 3))
    {
        r = strset_dump_if(set, filter_filial_promo, strcmp_dummy, &f, n);
    }

    return r;
}

char **get_all_no_promo(StrSet set, size_t *n, int filial)
{
    char **r = NULL;
    int f = filial;

    if (is_between(f, 1, 3))
    {
        r = strset_dump_if(set, filter_filial_no_promo, strcmp_dummy, &f, n);
    }

    return r;
}

char **get_sort_quant(StrSet set, size_t *n, int month)
{
    char **r = NULL;
    int m = month;

    if (is_between(m, 1, 12))
    {
        r = strset_dump_if(set, filter_month, compare_quants, &m, n);
    }

    return r;
}

static char **strset_dump_if(StrSet set, Predicate p, fcompare fc, void *user_data, size_t *n)
{
    char **r = NULL;

    GHashTableIter iter;
    gpointer key, value;

    GrowingArray ga = garray_make(sizeof(char *), NULL);
    Dummy du = g_malloc(sizeof(struct dummy));

    g_hash_table_iter_init(&iter, set->table);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        du->key = key;
        du->value = value;
        du->user_data = user_data;
        if (!p || (value && user_data && (*p)(value, user_data)))
            garray_add(ga, du);
    }

    if (fc)
        garray_sort(ga, fc);

    r = (char **)garray_dump_elems(ga, uncurry_dummy, n);

    garray_destroy(ga);
    g_free(du);

    return r;
}

static int filter_filial_promo(const void *a, const void *b)
{
    return (specinfo_get_promo_fil((SpecInfo)a, *(int *)b) > 0);
}

static int filter_filial_no_promo(const void *a, const void *b)
{
    return (specinfo_get_no_promo_fil((SpecInfo)a, *(int *)b) > 0);
}

static int filter_month(const void *a, const void *b)
{
    return (specinfo_get_units_month((SpecInfo)a, *(int *)b) > 0);
}

static void *uncurry_dummy(void *d)
{
    return ((Dummy)d)->value;
}

static int strcmp_dummy(const void *a, const void *b)
{
    Dummy da = (Dummy)a;
    Dummy db = (Dummy)b;
    return strcmp(*(const char **)da->key, *(const char **)db->key);
}

static int compare_quants(const void *a, const void *b)
{
    Dummy da = (Dummy)a;
    Dummy db = (Dummy)b;

    return ((specinfo_get_units_month((SpecInfo)db->value, *(int *)db->user_data)) - (specinfo_get_units_month((SpecInfo)da->value, *(int *)da->user_data)));
}
