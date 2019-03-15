#ifndef KHEAP_H
#define KHEAP_H

#include "util.h"

typedef struct kheap *KHeap;

KHeap kheap_make(fcompar);
KHeap kheap_heapify_array(void **, fcompar, int);
void kheap_destroy(KHeap);
void kheap_add(KHeap, void *);
void *kheap_check_root(KHeap);
void *kheap_extract_root(KHeap);
int kheap_size(KHeap);
int kheap_is_empty(KHeap);

#endif