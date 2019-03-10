#ifndef MAINSTRUCT_H
#define MAINSTRUCT_H

typedef struct data_base *DBase;

DBase make_dbase();
void destroy_dbase(DBase);
int insert_dbase(DBase, void *, void *);
int remove_dbase(DBase, void *);
int get_size_dbase(DBase);
int get_not_sold_dbase(DBase);
int exists_dbase(DBase, void *);
int get_client_v(DBase, char *);

#endif