#ifndef APPEND_H
#define APPEND_H

#include "util.h"

typedef struct append *Append;

void *append_make();
void append_destroy(void *e);
void append_add(void *a, void *b);
int append_is_empty(void *a);
int append_is_sold_in_all_fil(Append a);
gID *append_dump_month(Append a, int month, int *s);

#endif