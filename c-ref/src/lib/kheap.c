/**
 * @file kheap.c
 * \brief Módulo de código associado à estrutura de dados heap.
 */
#include "kheap.h"

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
KHeap kheap_make(fcompare, freefunc);
KHeap kheap_heapify_array(void **d, int length, fcompare fc, freefunc ff);
void kheap_destroy(KHeap);
void kheap_add(KHeap, void *);
void *kheap_check_root(KHeap);
void *kheap_extract_root(KHeap);
size_t kheap_size(KHeap);
int kheap_is_empty(KHeap);

/* Metodos privados */
static int bubble_up(KHeap);
static int bubble_down(KHeap);
static void double_heap(KHeap);
static void swap_arr(void **arr, int i, int j);

/* ------------------------------------------------------------------------------ */

typedef struct kheap
{
    size_t size, used;
    fcompare fc;
    freefunc ff;
    void **heap;
} * KHeap;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Define o número de ramos da Heap.
 */
#define K 6

/**
 * \brief Calcula o antecessor de um elemento da Heap.
 */
#define ant(i, K) (((i)-1) / K)

/**
 * \brief Calcula um n-ésimo sucessor de um elemento da Heap.
 */
#define succ(i, k, n) ((k) * (i) + (n))

/**
 * \brief Tamanho inicial da estrutura de dados onde se encontra armazenada a Heap.
 */
#define BASESIZE 10

/* ------------------------------------------------------------------------------ */

KHeap kheap_make(fcompare fc, freefunc ff)
{
    KHeap kh = NULL;
    if (fc)
    {
        kh = g_malloc(sizeof(struct kheap));
        kh->fc = fc;
        kh->ff = ff;
        kh->size = BASESIZE;
        kh->used = 0;
        kh->heap = g_malloc(sizeof(void *) * BASESIZE);
    }
    return kh;
}

KHeap kheap_heapify_array(void **d, int length, fcompare fc, freefunc ff)
{
    int i;
    KHeap kh = kheap_make(fc, ff);
    if (kh)
    {
        for (i = 0; i < length; i++)
            kheap_add(kh, d[i]);
    }
    return kh;
}

void kheap_destroy(KHeap kh)
{
    int i;

    if (kh)
    {
        if (kh->ff)
        {
            for (i = 0; i < kh->used; i++)
                (*kh->ff)(kh->heap[i]);
        }

        g_free(kh->heap);
        g_free(kh);
    }
}

void kheap_add(KHeap kh, void *d)
{
    if (kh->used == kh->size)
        double_heap(kh);
    kh->heap[kh->used] = d;
    bubble_up(kh);
    kh->used++;
}

void *kheap_check_root(KHeap kh)
{
    void *d = NULL;

    if (kh && kh->used)
        d = kh->heap[0];

    return d;
}

void *kheap_extract_root(KHeap kh)
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

size_t kheap_size(KHeap kh)
{
    return kh->used;
}

int kheap_is_empty(KHeap kh)
{
    return (kh->used == 0);
}

static int bubble_up(KHeap kh)
{
    int p = kh->used, r = 0;

    while (p > 0 && kh->fc(kh->heap[p], kh->heap[ant(p, K)]) > 0)
    {
        ++r;
        swap_arr(kh->heap, p, ant(p, K));
        p = ant(p, K);
    }

    return r;
}

static int bubble_down(KHeap kh)
{
    int i, p, minI, r, order;
    p = r = order = 0;
    void *min;

    while (succ(p, K, 1) < kh->used && !order)
    {
        minI = succ(p, K, 1);
        min = kh->heap[minI];

        for (i = minI + 1; i < kh->used && i <= succ(p, K, K); i++)
        {
            if (kh->fc(min, kh->heap[i]) < 0)
            {
                min = kh->heap[i];
                minI = i;
            }
        }
      
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

static void double_heap(KHeap kh)
{
    kh->heap = g_realloc(kh->heap, sizeof(void *) * kh->size * 2);
    kh->size *= 2;
}

static void swap_arr(void **arr, int i, int j)
{
    void *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}