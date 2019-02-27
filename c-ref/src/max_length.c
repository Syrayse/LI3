#include <stdio.h>
#include <stdlib.h> // Podes usar esta biblioteca? Só está aqui para não dar warning no exit
#define MAX_BUFFER 512 // Quantidade de bytes que vão ser lidos de uma só vez

int max_length() {
    int at, i, max;

    char buff [MAX_BUFFER];
    FILE * fp = fopen("linhas.txt","r"); // Ficheiro a ler

    at=max=0;
    if (fp){
    	while (fread(buff, sizeof(char), MAX_BUFFER, fp)) { // Usei o fread, porque podemos ler a quantidade de bits que quisermos..
					for (i = 0; i < MAX_BUFFER ; ++i) {
	    	           	if (buff[i]=='\n' || buff[i]=='\0') {
	    	           		max=(max<at)? at : max;
							at=-1;
	    	           	}
	    	           	at++;
	    	    }
    	}
    }
    else exit(1); // Caso o ficheiro não exista	
    
    printf("%d\n", max-1);
    fclose(fp);
    
    return max-1;
}