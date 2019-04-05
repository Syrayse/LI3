/**
 * @file kheap.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `KHeap`.
 */
#ifndef KHEAP_H
#define KHEAP_H

#include <glib.h>

typedef struct kheap *KHeap;

KHeap kheap_make(GCompareFunc, GFreeFunc);
KHeap kheap_heapify_array(void **d, int length, GCompareFunc fc, GFreeFunc ff);
void kheap_destroy(KHeap);
void kheap_add(KHeap, void *);
void *kheap_check_root(KHeap);
void *kheap_extract_root(KHeap);
size_t kheap_size(KHeap);
int kheap_is_empty(KHeap);

#endif