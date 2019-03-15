/*
NOTA IMPORTANTE:

Utilizando com exemplo uma heap com 2 ramos, observa-se que todas as operações
ou são constante ou possuem uma componente logaritmica na base de 2.

O que acontece ao utilizar uma gestão com K ramos, todas as operações ou são
constante ou possuem um componente logaritmica na base de K, na mesma escala
do que a versão simplificada de K = 2.

Com K ramos, a Heap funciona como uma arvóre completa tal como quando K = 2.
*/
#include <stdlib.h>
#include <stdio.h>
#include "kheap.h"

//Numero de ramos.
#define K 6

//Macro uteis.
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ant(i, K) (((i)-1) / K)
#define succ(i, k, o) ((k) * (i) + (o))
#define BASESIZE 1

// Main struct
typedef struct kheap
{
    int size, used;
    fcompare fc;
    DATA *heap;
} * KHEAP;

// Listagem das funções ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Public
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

//Private
//Gestão
static int bubble_up(KHEAP);
static int bubble_down(KHEAP);
static void double_heap(KHEAP);
static void swap_arr(DATA *arr, int i, int j);
// Funções ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

KHEAP make_kheap(fcompare fc)
{
    KHEAP kh = NULL;
    if (fc)
    {
        kh = (KHEAP)malloc(sizeof(struct kheap));
        kh->fc = fc;
        kh->size = BASESIZE;
        kh->used = 0;
        kh->heap = (DATA *)malloc(sizeof(DATA) * BASESIZE);
    }
    return kh;
}

// O problema com a representação por void* é que para o heapify de array inteiro,
// deve se converter esse array para um array de void**.
KHEAP heapify_arr(DATA *d, fcompare fc, int length)
{
    int i;
    KHEAP kh = make_kheap(fc);
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
void insert_data(KHEAP kh, DATA d)
{
    if (kh->used == kh->size)
        double_heap(kh);
    kh->heap[kh->used] = d;
    bubble_up(kh);
    kh->used++;
}

DATA check_root(KHEAP kh)
{
    DATA d = NULL;

    if (kh && kh->used)
        d = kh->heap[0];

    return d;
}

DATA extract_root(KHEAP kh)
{
    DATA d = NULL;
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
static int bubble_up(KHEAP kh)
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

//Retorna a quantidade elementos que teve de passar ao fazer bubble down do primeiro elemento
//é preciso reduzir o tamanho primeiro.
static int bubble_down(KHEAP kh)
{
    int i, p, minI, r, order;
    p = r = order = 0;
    DATA min;

    while (succ(p, K, 1) < kh->used && !order)
    {
        minI = succ(p, K, 1);
        min = kh->heap[minI];

        for (i = minI + 1; i < kh->used && i <= succ(p, K, K); i++)
        {
            if (kh->fc(min, kh->heap[i]) < 0) //Encontrei um menor
            {
                min = kh->heap[i];
                minI = i;
            }
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

static void double_heap(KHEAP kh)
{
    kh->heap = (DATA *)realloc(kh->heap, sizeof(DATA) * kh->size * 2);
    kh->size *= 2;
}

static void swap_arr(DATA *arr, int i, int j)
{
    DATA tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}