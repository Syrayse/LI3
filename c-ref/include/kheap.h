#ifndef KHEAP_H
#define KHEAP_H

typedef void *DATA;
typedef void (*fremove)(DATA);
typedef int (*fcompare)(const DATA, const DATA);

typedef struct kheap *KHEAP;

//Criação && Remoção
KHEAP make_kheap(fcompare);
KHEAP heapify_arr(DATA *, fcompare, int);
void free_kheap(KHEAP);

//Operações base
void insert_data(KHEAP, DATA);
DATA check_root(KHEAP);
DATA extract_root(KHEAP);

//Inspecção
int get_size_kheap(KHEAP);
int is_empty_kheap(KHEAP);

#endif