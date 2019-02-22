#ifndef KHEAP_H
#define KHEAP_H

typedef struct kheap *KHEAP;

typedef void* DATA;
typedef int  (*fcompare) (const DATA, const DATA);

        //Criação && Remoção
KHEAP           make_kheap          (fcompare,size_t);
KHEAP           heapify_arr         (DATA,fcompare,size_t,int);
void            free_kheap          (KHEAP);

        //Operações base
void            insert_data         (KHEAP, DATA);
int             check_root          (KHEAP, DATA);
int             extract_root        (KHEAP, DATA);

        //Inspecção
int             get_size_kheap      (KHEAP);
int             is_empty_kheap      (KHEAP);

#endif 