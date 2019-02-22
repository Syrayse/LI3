#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "validation.h"

// USEFUL MACROS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define     is_between(x,min,max)   ((x>=min) && (x<=max))

// PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int         is_valid_client         (char*);
int         is_valid_product        (char*);
int         is_valid_sale           (char*);

// PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int     get_token_length (char* token, char** placer);
void    free_placer (char ** placer, int n);
// CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int         is_valid_client         (char* s)
    {
        return (
            isupper(s[0])                                           //Vejo se a primeira letra e maiuscula
            && is_between(atoi(s+1),1000,5000)                      //Vejo se esse numero esta entre 1000 e 5000
            && (s[5] == '\0')                                       //Vejo se a frase de facto termina quando eu acho que ela deve terminar
        );
    }

int         is_valid_product        (char* s)
    {
        return (
            isupper(s[0])
            && isupper(s[1])
            && is_between(atoi(s+2),1000,9999)
            && (s[6] == '\0')
        );
    }

/*
Recebe um token da strtok
produto + preco + unidades + promo + cliente + mes + filial
*/
int         is_valid_sale           (char* str)
    {
        int n,r = 1;
        char **placer,*token = strtok(str," ");
        placer = (char**)malloc(sizeof(char*)*7);
        if ((n = get_token_length(token,placer)) == 7) {
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

        for(r = 0; r < 7; r++)
            printf("%s\n",placer[r]);
        free_placer(placer,n);
        return r;
        
    }

int     get_token_length (char* token, char** placer) 
{
    int r = 0;
    while (token != NULL && r < 7) {
        placer[r++] = strdup(token);
        strtok(NULL," ");
    }
    if (r > 7) r = -1;
    return r;
}

void    free_placer (char ** placer, int n)
{
    int i;
    for (i = 0; i < n; i++)
        free(placer[i]);
    free(placer);
}

int main () {
    int i;
    char str[80] = "US1761 832.36 170 P W3608 11 3";
    char **placer = (char**)malloc(sizeof(char*)*7);
    char *saver;
    char *token = strtok_r(str," ",&saver);
    while(token){
        printf("%s | %d\n",token,strlen(token));
        placer[i] = (char*)malloc(sizeof(char)*(strlen(token) + 1));
        strcpy(placer[i],token);
        token = strtok_r(NULL," ",&saver);
    }

    for (i = 0; i < 7; i++)
        printf("%s!\n",placer[i]);
   return(0);
}