#include "FilManager.h"
#include "kheap.h"
#include "record.h"
#include "set.h"

// ------------------------------------------------------------------------------

/* Metodos publicos */
FilManager FilManager_make();
void FilManager_destroy(FilManager fm);
void FilManager_add_trans(FilManager fm, int filial, gID id);
int FilManager_size_trans_filial(FilManager fm, int filial);
gID *FilManager_get_trans_filial(FilManager fm, int *size, int filial);

/* Metodos privados */
// Nenhum

// ------------------------------------------------------------------------------

typedef struct fil_manager
{
    Record fil[N_FILIAIS];
} * FilManager;

// ------------------------------------------------------------------------------

FilManager FilManager_make()
{
    int i;
    FilManager fm = g_malloc(sizeof(struct fil_manager));

    for (i = 0; i < N_FILIAIS; i++)
        fm->fil[i] = rec_make_fixed_size(300000);

    return fm;
}

void FilManager_destroy(FilManager fm)
{
    int i;
    if (fm)
    {
        for (i = 0; i < N_FILIAIS; i++)
            rec_destroy(fm->fil[i]);
        g_free(fm);
    }
}

void FilManager_add_trans(FilManager fm, int filial, gID id)
{
    rec_add(fm->fil[filial - 1], id);
}

int FilManager_size_trans_filial(FilManager fm, int filial)
{
    return rec_size(fm->fil[filial - 1]);
}

gID *FilManager_get_trans_filial(FilManager fm, int *size, int filial)
{
    return rec_dump(fm->fil[filial - 1], size);
}