#ifndef REG_H
#define REG_H

#include "util.h"

typedef struct record *Record;

void *rec_make();
void *rec_make_fixed_size(int size);
void rec_destroy(void *e);
void rec_add(Record r, gID id);
gID rec_size(Record r);
gID *rec_dump(Record r, int *n);

#endif