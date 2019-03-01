#include <stdio.h>
#include <stdlib.h> // Podes usar esta biblioteca? Só está aqui para não dar warning no exit
#define MAX_BUFFER 32768 // Quantidade de bytes que vão ser lidos de uma só vez

int max_length() {
    int at, i, max, bit;

    char buff [MAX_BUFFER];
    FILE * fp = fopen("tests/Vendas_1M.txt","r"); // Ficheiro a ler
    
    at = max = 0;

    if (fp){
    	while ((bit = fread(buff, sizeof(char), MAX_BUFFER, fp))) { // Usei o fread, porque podemos ler a quantidade de bits que quisermos..
			for (i = 0; i < bit ; ++i, at++) {
				if (buff[i]=='\n'){
					at--;
	           		max=(max<at)? at : max;
	           		at=-1;
	           	}
	    	}
    	}
    }

    else exit(1); // Caso o ficheiro não exista

    max=(max<at)? at : max;

    //printf("%d\n", max);
    fclose(fp);
    
    return max;
}

/*
int main () {
    max_length();
    //printf("max length:%d\n",max_length());
}*/