/**
 * @file kheap.c
 * \brief Ficheiro de código direccionado para a classe `KHeap`.
 * 
 * KHeap é um tipo de _heap_ porém, ao contrário da normal _heap_ com dois filhos
 * a KHeap consegue lidar com um número arbitrário de filhos, que está definido a 6.
 */
#include "kheap.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura da classe `KHeap`.
 */
typedef struct kheap
{
    size_t size,     /**< Indica a capacidade máxima atual da kheap. */
        used;        /**< Indica quantos elementos estão inseridos. */
    GCompareFunc fc; /**< A função de comparação entre elementos. */
    GFreeFunc ff;    /**< Função usada para liberta os elementos da kheap. */
    gpointer *heap;  /**< Contentor onde são armazenados os elementos da kheap. */
} * KHeap;

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
KHeap kheap_make(GCompareFunc, GFreeFunc);
void kheap_destroy(KHeap);
void kheap_add(KHeap, gpointer);
gpointer kheap_check_root(KHeap);
gpointer kheap_extract_root(KHeap);
size_t kheap_size(KHeap);
int kheap_is_empty(KHeap);

/* Metodos privados */
static int bubble_up(KHeap);
static int bubble_down(KHeap);
static void double_heap(KHeap);
static void swap_arr(gpointer *arr, int i, int j);

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

KHeap kheap_make(GCompareFunc fc, GFreeFunc ff)
{
    KHeap kh = NULL;
    if (fc)
    {
        kh = g_malloc(sizeof(struct kheap));
        kh->fc = fc;
        kh->ff = ff;
        kh->size = BASESIZE;
        kh->used = 0;
        kh->heap = g_malloc(sizeof(gpointer) * BASESIZE);
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

void kheap_add(KHeap kh, gpointer v)
{
    if (kh->used == kh->size)
        double_heap(kh);
    kh->heap[kh->used] = v;
    bubble_up(kh);
    kh->used++;
}

gpointer kheap_check_root(KHeap kh)
{
    gpointer d = NULL;

    if (kh && kh->used)
        d = kh->heap[0];

    return d;
}

gpointer kheap_extract_root(KHeap kh)
{
    gpointer d = NULL;

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
    gpointer min;

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
    kh->heap = g_realloc(kh->heap, sizeof(gpointer) * kh->size * 2);
    kh->size *= 2;
}

static void swap_arr(gpointer *arr, int i, int j)
{
    gpointer tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}