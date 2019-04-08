#include "menu.h"
#include "TAD_List.h"
#include <stdlib.h>
#include <stdio.h>

/* ------------------------------------------------------------------------------ */

/* Metódos publicos */
void getDirVendas(int *i, char *vend);
void getDirProd(int *i, char *prod);
void getDirCli(int *i, char *cli);
void pLinhas(char *tipo, char *dir, int val, int tot);
int comunicaExt(int status);
void pMess(char *message);
void NaoVende(int i, int j);
void NaoComp(int i, int j);
void pMatriz(int **mat, char *cod);
void intMeses(int m1, int m2, int vendas, double fat);
void welcomeScreen();
void filiais(int i, int *fils[], double *dfils[]);
void geral(int *geral, double *dgeral);
int pedirInteiro(char *mensagem);
char pedirChar(char *mensagem);
void pedirString(char *mensagem, char *buff);
int navegador(TAD_List tl, int i, int f, int size);

/* Metodos privados */
static void menu();

/* ------------------------------------------------------------------------------ */

static void menu()
{
	printf("     ___________________________________________________ \n");
	printf("    |                                                   |\n");
	printf("    |            Bem vindo ao gestor de Vendas          |\n");
	printf("    |___________________________________________________|\n");

	printf("	01. Fazer leitura dos ficheiros.\n");
	printf("	02. Apresentar Catálogo de Produtos.\n");
	printf("	03. Informações sobre as vendas de um produto num determinado mês.\n");
	printf("	04. Produtos não comprados.\n");
	printf("	05. Lista de clientes que realizaram compras em todas as filiais.\n");
	printf("	06. Clientes e produtos inativos.\n");
	printf("	07. Informações sobre as compras de um determinado cliente, por mês.\n");
	printf("	08. Resultados das vendas num intervalo de meses.\n");
	printf("	09. Lista de clientes que compraram um produto num determinado filial.\n");
	printf("	10. Produtos mais comprados por um cliente num determinado mês.\n");
	printf("	11. Lista dos N produtos mais comprados ao longo do ano.\n");
	printf("	12. Produtos em que um cliente gastou mais dinheiro.		0. Sair.\n\n");
}

void getDirVendas(int *lido, char *vend)
{
	printf("\tAgora das vendas\t\t\t\t O. Assume por omissão\n");
	*lido = scanf("%s", vend);
	while (fgetc(stdin) != '\n')
		;
}

void getDirCli(int *lido, char *cli)
{
	printf("\tAgora dos clientes\t\t\t\t O. Assume por omissão\n");
	*lido = scanf("%s", cli);
	while (fgetc(stdin) != '\n')
		;
}

void getDirProd(int *lido, char *prod)
{
	printf("\tColoque a diretoria do ficheiro de produtos\t O. Assume por omissão\n");
	*lido = scanf("%s", prod);
	while (fgetc(stdin) != '\n')
		;
}

void pLinhas(char *tipo, char *dir, int val, int tot)
{
	printf("\tO ficheiro de %s lido foi %s, com %d linhas válidas num total de %d.\n\n", tipo, dir, val, tot);
}

int comunicaExt(int status)
{
	char buffer[1024];
	int num_commando;
	menu();
	printf("\tIntroduza o número do comando desejado: ");
	scanf("%s", buffer);
	num_commando = atoi(buffer);

	if (num_commando == 0)
		return 0;

	if (num_commando == 1)
		return 1;
	if (status == -1)
	{
		printf("\tNão existem ficheiros carregados\n");
		getchar();
		getchar();
		return -1;
	}

	if (num_commando < 13 && num_commando > 1)
		return num_commando;

	else
	{
		printf("Este comando não é válido!\n");
		getchar();
		getchar();
		return -2;
	}
}

void filiais(int i, int **fils, double **dfils)
{
	printf("\tVendas com promoção %d, Vendas sem promoção %d\n", fils[i - 1][1], fils[i - 1][0]);
	printf("\tTotal faturado com promoção %f, Total faturado sem promoção %f\n\n", dfils[i - 1][1], dfils[i - 1][0]);
}

void fatura(int *geral, double *dgeral)
{
	printf("\tVendas com promoção %d, Vendas sem promoção %d\n", geral[1], geral[0]);
	printf("\tTotal faturado com promoção %f, Total faturado sem promoção %f\n\n", dgeral[1], dgeral[0]);
}

int pedirInteiro(char *mensagem)
{
	int a;
	printf("%s", mensagem);
	scanf("%d", &a);
	while (fgetc(stdin) != '\n')
		;
	return a;
}

char pedirChar(char *mensagem)
{
	char a;
	printf("%s:\n", mensagem);
	scanf(" %c", &a);
	while (fgetc(stdin) != '\n')
		;
	return a;
}

void pedirString(char *mensagem, char *buff)
{
	printf("%s", mensagem);
	scanf("%s", buff);
	while (fgetc(stdin) != '\n')
		;
}

void pMess(char *message)
{
	printf("%s\n", message);
	getchar();
}

void NaoVende(int tam, int fil)
{
	if (fil < 4 && fil > 0)
		printf("\tNúmero: %d, Filial %d\n", tam, fil);
	if (fil == 0)
		printf("\tNúmero: %d, Resultado Global\n", tam);
}

void NaoComp(int c, int p)
{
	printf("\n\t%d Produtos não foram comprados, bem como %d clientes não fizeram compras\n", p, c);
}

void pMatriz(int **matriz, char *cod)
{
	int i, j;
	printf("              _________________________________________ \n");
	printf("_____________|      1      |      2      |      3      |\n");
	for (i = 0; i < 12; i++)
	{
		printf(" %10d  |", i + 1);
		for (j = 0; j < 3; j++)
			printf(" %10d  |", matriz[j][i]);
		printf("\n");
	}
	printf("________________________________________________________ \n");
}

void intMeses(int m1, int m2, int vendas, double fat)
{
	if (m1 == m2)
		printf("\tNo mês %d houveram %d e a faturação foi %f\n", m1, vendas, fat);
	else
		printf("\tEntre o mês %d e o %d houveram %d e a faturação foi %f\n", m1, m2, vendas, fat);
}

int navegador(TAD_List tl, int i, int f, int size)
{
	printf("\n\tExistem %d Produtos\n", size);
	if (tl)
	{
		for (; i < f && i < size; i++)
			printf("%d:\t%s\n", i + 1, (char *)list_get_index(tl, i));
	}
	return (pedirInteiro("\t1. Próxima página  2.Página anterior  0.Sair  "));
}