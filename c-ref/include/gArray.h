#ifndef GARRAY_H
#define GARRAY_H

#include "util.h"
#include <glib.h>

typedef struct garray *GrowingArray;

GrowingArray make_garray(size_t key_size, freefunc ff);
void destroy_garray(GrowingArray g);
size_t get_size_garray(GrowingArray g);
void insert_elem_garray(GrowingArray g, void *entry);
void sort_garray(GrowingArray g, fcompar fc);
int is_sorted_garray(GrowingArray g);
void **dump_elems_garray(GrowingArray src, size_t *h);
int auto_resize_garray(GrowingArray g);

#endif