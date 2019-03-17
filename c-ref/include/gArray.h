#ifndef GARRAY_H
#define GARRAY_H

#include "util.h"
#include <glib.h>

typedef struct garray *GrowingArray;

GrowingArray garray_make(size_t key_size, freefunc ff);
void garray_destroy(GrowingArray g);
size_t garray_size(GrowingArray g);
void garray_add(GrowingArray g, void *entry);
void garray_sort(GrowingArray g, fcompare fc);
int garray_is_sorted(GrowingArray g);
void **garray_dump_elems(GrowingArray src, void *(*f_map)(void *), size_t *h);
int garray_auto_resize(GrowingArray g);

#endif