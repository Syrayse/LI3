#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "validation.h"

// USEFUL MACROS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define     is_between(x,min,max)   ((x>=min) && (x<=max))

// PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int         is_valid_client         (char*, int*);
int         is_valid_product        (char*, int*);
int         is_valid_sale           (char*, int*);  //Recieves a tokenized string.

// PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static int  v_price                  (char*,int*);

// CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// What makes a client word valid?
int         is_valid_client         (char* s, int* flag)
    {
        *flag = strlen(s);
        return ( (*flag == 5 || (*flag == 6 && s[5] == '\n'))
                && isupper(s[0])
                && is_between(atoi(s+1),1000,5000)
         );
    }

// What makes a product Word valid?
int         is_valid_product        (char* s, int* flag)
    {
        *flag = strlen(s);
        int i;
        /*puts("~~~~~");
        for(i=0;s[i];i++)
        	printf("%d:%c\n",i,s[i]);
        puts("~~~~~");*/
        return ( /*(*flag == 6 || (*flag == 8 && s[6] == '\n'))
                && */isupper(s[0])
                && isupper(s[1])
                && is_between(atoi(s+2),1000,9999)
         );        
    }


/*
int         main ()
    {
        int r,tmp = 0;
        char client[20] = "f0216";
        char product[20] = "AB9012";

        r = is_valid_client(client,&tmp);
        printf("Client %s is %d, with size %d\n",client,r,tmp);

        r = is_valid_product(product,&tmp);
        printf("Product %s is %d, with size %d\n",product,r,tmp);
    
        printf("%d\n",isupper('A'));
        printf("atof %f\n",atof("323f3"));    
    }
*/