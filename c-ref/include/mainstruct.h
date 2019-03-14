#ifndef MAINSTRUCT_H
#define MAINSTRUCT_H

#include <glib.h>

typedef struct data_base *DBase;

DBase make_dbase();
void destroy_dbase(DBase);
int insert_dbase(DBase, void *, void *);
int remove_dbase(DBase, void *);
int get_total_size_dbase(DBase);
int get_letter_size_dbase(DBase m, char flag);
int get_not_sold_dbase(DBase);
int exists_dbase(DBase, void *);
int get_client_v(DBase b, char *s);
void **get_overall_clients(DBase b, size_t *h, char flag);
void **dump_ordered_abstract(DBase b, GHFunc f, size_t *h, char flag);
void **get_ordered_not_bought(DBase db, size_t *n, int filial);
void build_dbase_arrays(DBase db);

#endif