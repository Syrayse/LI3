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
int **store_query7(Store s, char *client);
void store_query8(Store s, int init, int end, int *nVendas, double *tot);
int store_query9(Store s, char *product, char ***holder, int *n1, int *n2, int filial);
char **store_query10(Store s, char *client, int month, int *sz);
char **store_query11(Store s, int N);
char **store_query12(Store s, char *client, int *sz);

#endif