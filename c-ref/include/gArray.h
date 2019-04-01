/**
 * @file gArray.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `gArray`.
 */
#ifndef GARRAY_H
#define GARRAY_H

#include "util.h"
#include <glib.h>

typedef struct garray *GrowingArray;

GrowingArray garray_make(int key_size, freefunc ff);
GrowingArray garray_make_sized(int key_size, int len, freefunc ff);
void garray_destroy(GrowingArray g);
int garray_size(GrowingArray g);
void garray_add(GrowingArray g, void *entry);
void garray_sort(GrowingArray g, fcompare fc);
int garray_is_sorted(GrowingArray g);
void *garray_get_index(GrowingArray g, unsigned int index);
void **garray_dump_elems(GrowingArray src, void *(*f_map)(void *), int *h);
void **garray_take_n(GrowingArray g, int *hold, int N);

#endif