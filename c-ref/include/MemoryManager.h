#ifndef _MEMORYMAN_
#define _MEMORYMAN_

#include <stdlib.h>

typedef struct memory_manager *MemoryManager;

MemoryManager MemoryManager_make();
void MemoryManager_destroy(MemoryManager m);
void *man_malloc(MemoryManager m, size_t size);

#endif