/**
 * @file set.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `StrSet`.
 */

#ifndef SET_H
#define SET_H

#include "util.h"
#include <glib.h>

typedef struct set *StrSet;

/**
 * \brief Redefine uma função que deve ser usada num metódo foreach.
 */
typedef void (*f_foreach)(void *, void *, void *);

/**
 * \brief Redefine uma função que deve ser usada como atualizador de um elemento.
 */
typedef void (*f_update)(void *, void *);

/**
 * \brief Redefine uma função que deve ser usada como criadora da instância pretendida.
 */
typedef void *(*f_maker)();

/**
 * \brief Redefine uma função que deve ser usada de modo a verificar se um elemento é vazio.
 */
typedef int (*f_empty)(void *);

StrSet strset_make(freefunc ffkey, freefunc ffvalue, f_maker fm, f_update fu, f_empty fe);
void strset_destroy(StrSet set);
int strset_add(StrSet set, void *elem, void *user_data);
int strset_remove(StrSet set, void *elem);
void strset_foreach(StrSet set, f_foreach fer, void *user_data);
int strset_contains(StrSet set, void *elem);
int strset_size(StrSet set);
void *strset_lookup(StrSet set, void *key);
void *strset_value_of(StrSet set, void *elem);
char **strset_dump_ordered(StrSet set, int *n);
int strset_get_not_init_n(StrSet set);
char **strset_generic_dump(StrSet set, f_foreach ffor, int *n, int flag);
char **strset_dump_if(StrSet set, fcompare fc, int *n);
char **strset_dump_n_ordered(StrSet set, int n);

#endif