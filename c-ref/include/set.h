#ifndef SET_H
#define SET_H

#include "util.h"
#include <glib.h>

typedef struct set *StrSet;

typedef void (*f_foreach)(void *, void *, void *);

typedef void (*f_update)(void *, void *);

typedef void (*f_maker)(void);

StrSet strset_make(freefunc ff);
void strset_destroy(StrSet set);
int strset_add(StrSet set, char *elem, void *value);
int strset_remove(StrSet set, char *elem);
void strset_foreach(StrSet set, f_foreach fer, void *user_data);
int strset_contains(StrSet set, char *elem);
int strset_size(StrSet set);
int strset_update_elem(StrSet set, char *elem, void (*f_up)(void *, void *), void *user_data);
char **strset_dump(StrSet set, size_t *n);
char **strset_dump_ordered(StrSet set, fcompar fc, size_t *n);

#endif
