#include "MemoryManager.h"
#include "kheap.h"
#include <stdlib.h>
#include <glib.h>

// ------------------------------------------------------------------------------

typedef struct memory_manager
{
    size_t nBlocks;
    size_t predfsize;
    KHeap mem_heap;
} * MemoryManager;

typedef struct memory_block
{
    size_t used;
    size_t nfree;
    void *mem_block;
} * MemoryBlock;

// ------------------------------------------------------------------------------

/* Metodos publicos */
MemoryManager MemoryManager_make();
void MemoryManager_destroy(MemoryManager m);
void *man_malloc(MemoryManager m, size_t size);

/* Metodos privados */
static MemoryBlock MemoryBlock_make(size_t size);
static void MemoryBlock_destroy(void *e);
static void add_new_block(MemoryManager m, size_t size);
static int compare_nfree(const void *a, const void *b);

// ------------------------------------------------------------------------------

#define max(a, b) ((a) > (b) ? (a) : (b))

// ------------------------------------------------------------------------------

MemoryManager MemoryManager_make()
{
    MemoryManager m = g_malloc(sizeof(struct memory_manager));
    m->mem_heap = kheap_make(compare_nfree, MemoryBlock_destroy);
    m->nBlocks = 0;
    m->predfsize = 1200000000;
    add_new_block(m, m->predfsize);
    return m;
}

void MemoryManager_destroy(MemoryManager m)
{
    void *r;
    if (m)
    {
        while ((r = kheap_extract_root(m->mem_heap)))
            MemoryBlock_destroy(r);

        kheap_destroy(m->mem_heap);
        g_free(m);
    }
}

void *man_malloc(MemoryManager m, size_t size)
{
    void *r;

    MemoryBlock rt = (MemoryBlock)kheap_check_root(m->mem_heap);

    if (size > rt->nfree)
    {
        add_new_block(m, max(size, m->predfsize));
    }

    rt = (MemoryBlock)kheap_extract_root(m->mem_heap);

    r = (void *)((char *)(rt->mem_block) + rt->used);

    rt->used += size;

    rt->nfree -= size;

    kheap_add(m->mem_heap, rt);

    return r;
}

static MemoryBlock MemoryBlock_make(size_t size)
{
    MemoryBlock m = g_malloc(sizeof(struct memory_block));

    m->used = 0;
    m->nfree = size;
    m->mem_block = g_malloc(size);

    return m;
}

static void MemoryBlock_destroy(void *e)
{
    MemoryBlock m;

    if (e)
    {
        m = (MemoryBlock)e;
        g_free(m->mem_block);
        g_free(m);
    }
}

static void add_new_block(MemoryManager m, size_t size)
{
    kheap_add(m->mem_heap, MemoryBlock_make(size));
    m->nBlocks++;
}

static int compare_nfree(const void *a, const void *b)
{
    size_t sa = ((MemoryBlock)a)->nfree;
    size_t sb = ((MemoryBlock)b)->nfree;
    return (int)(sa - sb);
}
