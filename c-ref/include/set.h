#ifndef SET_H
#define SET_H

#include "util.h"
#include <glib.h>

typedef struct set *StrSet;

typedef void (*f_foreach)(void *, void *, void *);

typedef void (*f_update)(void *, void *);

typedef void *(*f_maker)(int);

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

char **get_all_promo_fil(StrSet set, size_t *n, int filial);
char **get_all_no_promo_fil(StrSet set, size_t *n, int filial);
char **get_sort_quant_month(StrSet set, size_t *n, int month);

#endif