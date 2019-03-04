#ifndef MAINSTRUCT_H
#define MAINSTRUCT_H

typedef struct mainstructb *MainStructB;

MainStructB make_msb();
void destroy_msb(MainStructB);
int insert_msb(MainStructB, void *, void *);
int remove_msb(MainStructB, void *);
int get_size_msb(MainStructB);
int exists_msb(MainStructB, void *);
int get_client_v(MainStructB, char *);

#endif