#ifndef MAINSTRUCT_H
#define MAINSTRUCT_H

#include <glib.h>

typedef struct data_base *DBase;

DBase dbase_make(int flag);
void dbase_destroy(DBase);
void dbase_add(DBase, void *, void *);
int dbase_remove(DBase, void *);
int dbase_size(DBase);
int dbase_size_specific(DBase, char);
int dbase_contains(DBase, void *);
void *dbase_lookup(DBase db, void *key);
char **dbase_get_overall(DBase, size_t *, char);
char **dbase_get_not_sold(DBase, size_t *, int);
char **dbase_get_ordered(DBase db, size_t *n, int flag);
int dbase_get_not_init(DBase db);

#endif