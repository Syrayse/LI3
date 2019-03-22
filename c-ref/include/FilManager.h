#ifndef FIL_MAN
#define FIL_MAN

#include "util.h"

typedef struct fil_manager *FilManager;

FilManager FilManager_make();
void FilManager_destroy(FilManager fm);
void FilManager_add_trans(FilManager fm, int filial, gID id);
int FilManager_size_trans_filial(FilManager fm, int filial);
gID *FilManager_get_trans_filial(FilManager fm, int *size, int filial);

#endif