/*
NOTA IMPORTANTE:

Utilizando com exemplo uma heap com 2 ramos, observa-se que todas as operações
ou são constante ou possuem uma componente logaritmica na base de 2.

O que acontece ao utilizar uma gestão com K ramos, todas as operações ou são
constante ou possuem um componente logaritmica na base de K, na mesma escala
do que a versão simplificada de K = 2.

Com K ramos, a Heap funciona como uma arvóre completa tal como quando K = 2.
*/
#include "kheap.h"
#include <glib.h>

//Numero de ramos.
//#define     K               8

//Macro uteis.
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ant(i, K) (((i)-1) / K)
#define succ(i, k, o) ((k) * (i) + (o))
#define BASESIZE 1

// Main struct
typedef struct kheap
{
    int size, used, K;
    int (*fc)(const void *, const void *);
    void **heap;
} * KHEAP;

// Listagem das funções ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Public
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

//Private
//Gestão
int bubble_up(KHEAP);
int bubble_down(KHEAP);
void double_heap(KHEAP);
void swap_arr(void **, int, int);
// Funções ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

KHEAP make_kheap(int (*fc)(const void *, const void *), int K)
{
    KHEAP kh = NULL;
    if (fc && K > 0)
    {
        kh = g_malloc(sizeof(struct kheap));
        kh->fc = fc;
        kh->K = K;
        kh->size = BASESIZE;
        kh->used = 0;
        kh->heap = g_malloc(sizeof(void *) * BASESIZE);
    }
    return kh;
}

// O problema com a representação por void* é que para o heapify de array inteiro,
// deve se converter esse array para um array de void**.
KHEAP heapify_arr(void **d, int (*fc)(const void *, const void *), int length, int K)
{
    int i;
    KHEAP kh = make_kheap(fc, K);
    if (kh)
    {
        //heapify todos os elementos
        for (i = 0; i < length; i++)
            insert_data(kh, d[i]);
    }
    return kh;
}

void free_kheap(KHEAP kh)
{
    if (kh)
    {
        free(kh->heap);
        free(kh);
    }
}

//Operações base
void insert_data(KHEAP kh, void *d)
{
    if (kh)
    {
        if (kh->used == kh->size)
            double_heap(kh);
        kh->heap[kh->used] = d;
        bubble_up(kh);
        kh->used++;
    }
}

void *check_root(KHEAP kh)
{
    void *d = NULL;
    if (kh && kh->used)
        d = kh->heap[0];
    return d;
}

void *extract_root(KHEAP kh)
{
    void *d = NULL;
    if (kh && kh->used)
    {
        d = kh->heap[0];
        kh->heap[0] = kh->heap[kh->used - 1];
        --kh->used;
        bubble_down(kh);
    }
    return d;
}

//Inspecção
int get_size_kheap(KHEAP kh)
{
    return kh->used;
}

int is_empty_kheap(KHEAP kh)
{
    return (kh->used == 0);
}

//Private
//Gestão

//Retorna a quantidade de elementos que teve de passar por ao fazer bubble up do ultimo elemento.
//so preciso reduzir o tamanho depois.
int bubble_up(KHEAP kh)
{
    int p = kh->used, r = 0;
    while (p > 0 && kh->fc(kh->heap[p], kh->heap[ant(p, kh->K)]) > 0)
    {
        ++r;
        swap_arr(kh->heap, p, ant(p, kh->K));
        p = ant(p, kh->K);
    }

    return r;
}

//Retorna a quantidade elementos que teve de passar ao fazer bubble down do primeiro elemento
//é preciso reduzir o tamanho primeiro.
int bubble_down(KHEAP kh)
{
    int i, p, minI, r, order;
    p = r = order = 0;
    void *min;
    while (succ(p, kh->K, 1) < kh->used && !order)
    {
        minI = succ(p, kh->K, 1);
        min = kh->heap[minI];

        for (i = minI + 1; i < kh->used && i <= succ(p, kh->K, kh->K); i++)
            if (kh->fc(min, kh->heap[i]) < 0) //Encontrei um menor
            {
                min = kh->heap[i];
                minI = i;
            }

        //Se o menor dos filhos for menor que o pai, troca-se ambos
        //caso contrário implica que a arvore em questão já é uma heap.
        if (kh->fc(kh->heap[p], min) < 0)
        {
            swap_arr(kh->heap, p, minI);
            p = minI;
            ++r;
        }
        else
            order = 1;
    }
    return r;
}

void double_heap(KHEAP kh)
{
    kh->heap = g_realloc(kh->heap, sizeof(void *) * (kh->size * 2));
    kh->size *= 2;
}

void swap_arr(void **arr, int i, int j)
{
    void *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}