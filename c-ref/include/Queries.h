#ifndef __QUERIES__
#define __QUERIES__

typedef struct store *Store;

Store store_make();
void store_destroy(Store s);

#endif