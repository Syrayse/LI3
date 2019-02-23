#include "validation.h"
#include <glib.h>

// USEFUL MACROS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define     is_between(x,min,max)   ((x>=min) && (x<=max))

// PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int         is_valid_client         (char*);
int         is_valid_product        (char*);
int         is_valid_sale           (char**,int);

// CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int         is_valid_client         (char* s)
    {
        return (
            g_ascii_isupper(s[0])                                           //Vejo se a primeira letra e maiuscula
            && is_between(atoi(s+1),1000,5000)                      //Vejo se esse numero esta entre 1000 e 5000
            && (s[5] == '\0')                                       //Vejo se a frase de facto termina quando eu acho que ela deve terminar
        );
    }

int         is_valid_product        (char* s)
    {
        return (
            g_ascii_isupper(s[0])
            && g_ascii_isupper(s[1])
            && is_between(atoi(s+2),1000,9999)
            && (s[6] == '\0')
        );
    }

int         is_valid_sale           (char** placer, int N)
    {
        int r = 1;
        if (N == 7) {
            r = is_valid_product(placer[0])
                && is_between(atof(placer[1]),0.0,999.99)
                && is_between(atoi(placer[2]),1,200)
                && (placer[3][0] == 'N' || placer[3][0] == 'P')
                && is_valid_client(placer[4])
                && is_between(atoi(placer[5]),1,12)
                && is_between(atoi(placer[6]),1,3);
        }
        else
            r = 0;
        return r;
    }