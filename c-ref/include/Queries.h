#ifndef __QUERIES__
#define __QUERIES__

#include "statinfo.h"

typedef struct store *Store;

Store store_make();
void store_destroy(Store s);
void store_query1(Store s, int argc, char **argv);
char **store_query2(Store s, int *size, int flag);
StatInfo store_query3(Store s, char *product);
char **store_query4(Store s, int filial, int *size);
char **store_query5(Store s, int *size);
void store_query6(Store s, int *ncl, int *nprd);

#endif