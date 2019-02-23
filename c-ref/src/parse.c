#include "validation.h"
#include "sale.h"
#include <glib.h>
#include <stdio.h>

// public methods
SALE parse_sale (char** holder, char * salestr);
// Private methods
void free_token_array (char** holder, int c);
int get_token_array (char** holder, char* str, char* delim);

//USEFUL DEFINES
#define BASE_SIZE 7
#define BASE_DELIM " \n"


// CODE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SALE parse_sale (char** holder, char * salestr)
{
    SALE s = NULL;
    int n = get_token_array(holder,salestr,BASE_DELIM);
    if( is_valid_sale(holder,n) ) {
        s = make_s();
        set_product_s(s,holder[0]);
        set_price_s(s,atof(holder[1]));
        set_units_s(s,atoi(holder[2]));
        set_promo_s(s,holder[3][0]);
        set_client_s(s,holder[4]);
        set_month_s(s,atoi(holder[5]));
        set_filial_s(s,atoi(holder[6]));
    }
    
    return s;
}

// recebe a string, os delimatores, a flag onde coloca o numero de elmentos lidos.
void free_token_array (char** holder, int c)
{
    int i;
    for (i = 0; i < BASE_SIZE && holder[i] ; i++){
        g_free(holder[i]);
        holder[i] = NULL;
    }
    if(c) g_free(holder);
}

/*
holder serve para evitar demasiados mallocs desnecessários.

se retornar -1 então é porque leu mais que o BASE_SIZE
*/
int get_token_array (char** holder, char* str, char* delim)
{
    int i; 
    char* token = strtok(str,delim);

    free_token_array(holder,0);

    for (i = 0; token && i < BASE_SIZE; i++, token = strtok(NULL,delim))
        holder[i] = g_strdup(token);
    
    return ( (i >= BASE_SIZE && token) ? -1 : i );
} 

void print_sale(SALE s) {
    if (s) {
        puts("~~~~~~~~~~~~~~~~~~~~~");
        printf("client %s purchased product %s!\n",get_client_s(s),get_product_s(s));
        printf("%d units by the price of %.2lf\n",get_units_s(s),get_price_s(s));
        printf("In the month %d in store %d with promo code %c\n",get_month_s(s),get_filial_s(s),get_promo_s(s));
        puts("~~~~~~~~~~~~~~~~~~~~~");
    }
}


int main () {
    FILE * fp = fopen("tests/Vendas_1M.txt","r");
    SALE s;
    int n = 0,i=0;
    char **d,m[1000];
    d = g_malloc0(sizeof(char*)*BASE_SIZE);
    while ( fgets(m,1000,fp) ) {
        s = parse_sale(d,m);
        if(!s) {
            n++;
        }
        i++;         
        //print_sale(s);
        destroy_s(s);
    }

    printf("Found %d valid entries and %d invalid!\n",i-n,n);

    free_token_array(d,1);
    fclose(fp);
}