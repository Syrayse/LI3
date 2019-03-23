#ifndef __QUERIES__
#define __QUERIES__

typedef struct store *Store;

Store store_make();
void store_destroy(Store s);
void store_query1(Store s, int argc, char **argv);
char **store_query2(Store s, int *size, int flag);

#endif