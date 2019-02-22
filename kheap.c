#include "kheap.h"
#include <stdio.h>
#include <string.h>

// TYPE DEFS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct kheap {
    int size,used;
    char * dummy,*min;               //dummy used to swap mem's
    fcompare fc;
    size_t nb;
    char * heap;
}*KHEAP;

// Listagem das Methods  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

KHEAP           make_kheap          (fcompare,size_t);
KHEAP           heapify_arr         (DATA,fcompare,size_t,int);
void            free_kheap          (KHEAP);
void            insert_data         (KHEAP, DATA);
int             check_root          (KHEAP, DATA);
int             extract_root        (KHEAP, DATA);
int             get_size_kheap      (KHEAP);
int             is_empty_kheap      (KHEAP);

//private
int             bubble_up           (KHEAP);
int             bubble_down         (KHEAP);
void            double_heap         (KHEAP);
void            swap_arr            (char*,char*,size_t,int,int);

// USEFUL macros

#define     min(a,b)        ((a)<(b)?(a):(b))
#define     max(a,b)        ((a)>(b)?(a):(b))
#define     ant(i)          (((i)-1)/K)
#define     succ(i,o)       ((K)*(i)+(o))
#define     BASESIZE        1
#define     addr(heap,i,nb)     ((heap)+((i)*(nb)))
#define     addre(kh,i)     (addr(((kh)->heap),(i),((kh)->nb)))
#define     K               6

// Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

KHEAP           make_kheap          (fcompare fc,size_t nb)
    {
        KHEAP kh = NULL;
        if(fc)
            {
                kh = (KHEAP)malloc(sizeof(struct kheap));
                kh->fc = fc;
                kh->size = BASESIZE;
                kh->used = 0;
                kh->nb = nb;
                kh->heap = (char*)malloc(sizeof(char)*nb*BASESIZE);
                kh->dummy = (char*)malloc(sizeof(char)*nb);
                kh->min = (char*)malloc(sizeof(char)*nb);
            }
        else
            perror("Invalid compare function");
        return kh;
    }

KHEAP           heapify_arr         (DATA v,fcompare fc,
                                        size_t nb, int length)
    {
        KHEAP kh = NULL;
        if(fc)
            {
                kh = (KHEAP)malloc(sizeof(struct kheap));
                kh->fc = fc;
                kh->size = length;
                kh->used = 0;
                kh->nb = nb;
                kh->heap = (char*)malloc(sizeof(char)*nb*length);
                kh->dummy = (char*)malloc(sizeof(char)*nb);
                kh->min = (char*)malloc(sizeof(char)*nb);
                memcpy(kh->heap,v,nb*length);   
            }
        else
            perror("Invalid compare function");
        return kh;
    }

void            free_kheap          (KHEAP kh)
    {
        if(kh)
            {
                free(kh->min);
                free(kh->dummy);
                free(kh->heap);
                free(kh);
            }
        else
            perror("There is nothing to free");
    }

void            insert_data         (KHEAP kh, DATA d)
    {
        if(kh)
            {
                if(kh->used==kh->size)
                    double_heap(kh);
                memcpy(addre(kh,kh->used),d,kh->nb);
                bubble_up(kh);
                kh->used++;
            }
        else
            perror("Trying to insert in NULL heap");
    }

int             check_root          (KHEAP kh, DATA d)
    {
        int r = 0;
        if(kh)
            {
                r=1;
                memcpy(d,kh->heap,kh->nb);
            }
        return r;

    }

int             extract_root        (KHEAP kh, DATA d)
    {
        int r = 0;
        if(kh && kh->used)
            {
                r=1;
                memcpy(d,kh->heap,kh->nb);
                memcpy(kh->heap,addr(kh->heap,kh->used-1,kh->nb),kh->nb);
                --kh->used;
                bubble_down(kh);
            }
        return r;
    }

int             get_size_kheap      (KHEAP kh)
    {
        return kh->used;
    }

int             is_empty_kheap      (KHEAP kh)
    {
        return (kh->used==0);
    }

int             bubble_up           (KHEAP kh)
    {
        int p=kh->used,r=0;
        while(p>0 && kh->fc(addre(kh,p),addre(kh,ant(p)))>0 )
            {
                ++r;
                swap_arr(kh->heap,kh->dummy,kh->nb,p,ant(p));
                p = ant(p);
            }
        
        return r;   
    }

int             bubble_down         (KHEAP kh)
    {
        int i, p, minI, r, order;
        p = r = order = 0;
        char *min = kh->min;

        while(succ(p,1)<kh->used && !order)
            {
                minI = succ(p,1);
                memcpy(min,addre(kh,minI),kh->nb);

                for(i = minI + 1; i < kh->used && i <= succ(p,K); i++)
                    if(kh->fc(min,addre(kh,i))<0)
                        {
                            memcpy(min,addre(kh,i),kh->nb);
                            minI = i;
                        }

                if(kh->fc(addre(kh,p),min)<0)
                    {
                        swap_arr(kh->heap,kh->dummy,kh->nb,p,minI);
                        p = minI;
                        ++r;
                    }
                else
                    order = 1;
            }
        return r;
    }

void            double_heap         (KHEAP kh)
    {
        kh->heap = (char*)realloc(kh->heap,sizeof(char)*kh->size*2*kh->nb);
        kh->size *= 2;
        //puts("double in size");
    }

void            swap_arr            (char* heap,char* dummy, size_t nb, int i, int j)
    {
        memcpy(dummy,addr(heap,i,nb),nb);
        memcpy(addr(heap,i,nb),addr(heap,j,nb),nb);//*
        memcpy(addr(heap,j,nb),dummy,nb);
    }