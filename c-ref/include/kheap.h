#ifndef KHEAP_H
#define KHEAP_H

typedef struct kheap *KHEAP;

//Criação && Remoção
KHEAP make_kheap(int (*)(const void *, const void *), int);
KHEAP heapify_arr(void **, int (*)(const void *, const void *), int, int);
void free_kheap(KHEAP);

//Operações base
void insert_data(KHEAP, void *);
void *check_root(KHEAP);
void *extract_root(KHEAP);

//Inspecção
int get_size_kheap(KHEAP);
int is_empty_kheap(KHEAP);

#endif
