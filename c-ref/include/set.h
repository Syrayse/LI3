#ifndef SET_H
#define SET_H

#include "util.h"
#include <glib.h>

typedef struct set *StrSet;

StrSet strset_make(freefunc ff);
void strset_destroy(StrSet set);
int strset_add(StrSet set, char *elem);
int strset_remove(StrSet set, char *elem);
void strset_foreach(StrSet set, void (*fe)(void *, void *, void *), void *user_data);
int strset_contains(StrSet set, char *elem);
int strset_size(StrSet set);
char **strset_dump(StrSet set, size_t *n);
char **strset_dump_ordered(StrSet set, fcompar fc, size_t *n);

#endif
