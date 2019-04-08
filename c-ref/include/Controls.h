/**
 * @file Controls.h
 * \brief Interface dos metódos utilizáveis para trabalhar com o menu do SGV. 
 */

#ifndef __CONTROLS__
#define __CONTROLS__

#include "TAD_List.h"

void menu();
void getDirVendas(int *i, char *vend);
void getDirCli(int *i, char *cli);
void getDirProd(int *i, char *prod);
void pLinhas(char *tipo, char *dir, int val, int tot);
int comunicaExt(int status);
void pMess(char *message);
void NaoVende(int i, int j);
void NaoComp(int i, int j);
void pMatriz(int **mat, char *cod);
void intMeses(int m1, int m2, int vendas, double fat);

void welcomeScreen();
void filiais(int i, int *fils[], double *dfils[]);
void fatura(int *geral, double *dgeral);
int pedirInteiro(char *mensagem);
char pedirChar(char *mensagem);
void pedirString(char *mensagem, char *buff);

int navegador(TAD_List tl, int i, int f, int size);

#endif
