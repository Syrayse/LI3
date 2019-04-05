/**
 * @file set.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `StrSet`.
 */

#ifndef SET_H
#define SET_H

#include <glib.h>

typedef struct set *Set;

/**
 * \brief Redefine uma função que deve ser usada como atualizador de um elemento.
 */
typedef void (*f_update)(gpointer, gpointer);

/**
 * \brief Redefine uma função que deve ser usada como criadora da instância pretendida.
 */
typedef gpointer (*f_maker)();

Set set_make(GHashFunc hash_f, GEqualFunc key_equal_f, GFreeFunc ffkey, GFreeFunc ffvalue, f_maker fm, f_update fu);
void set_destroy(Set set);
int set_add(Set set, gpointer key, gpointer user_data);
int set_remove(Set set, gpointer key);
void set_foreach(Set set, GHFunc fe, gpointer user_data);
int set_contains(Set set, gpointer key);
int set_size(Set set);
gpointer set_lookup(Set set, gpointer key);

#endif