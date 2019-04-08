/**
 * @file Controls.h
 * \brief Interface dos métodos utilizáveis para trabalhar com o menu do SGV. 
 */

#ifndef __CONTROLS__
#define __CONTROLS__

#include "TAD_List.h"
#include "NavControl.h"

/**
 * \brief Imprime o menu atual.
 */
void menu();

/**
 * \brief Obtém a diretoria do ficheiro das vendas.
*/
void getDirVendas(int *lido, char *vend);

/**
 * \brief Obtém a diretoria do ficheiros dos clientes.
*/
void getDirCli(int *lido, char *cli);

/**
 * \brief Obtém a diretoria do ficheiros dos produtos.
*/
void getDirProd(int *lido, char *prod);

/**
 * \brief Imprime a diretoria do ficheiro, linhas lidas e válidas.
*/
void pLinhas(char *tipo, char *dir, int val, int tot);

/**
 * \brief Deteta os erros no programa e encaminha para o percurso certo.
 * 
 * @returns Estado em que está o menu.
 */
int comunicaExt(int status);

/**
 * \brief Imprime uma mensagem.
*/
void pMess(char *message);

/**
 * \brief Imprime uma mensagem com os produtos não vendidos.
*/
void NaoVende(int i, int j);

/**
 * \brief Imprime uma mensagem com os produtos não comprados.
*/
void NaoComp(int i, int j);

/**
 * \brief Imprime a tabela das compras de um determinado cliente, por mês.
*/
void pMatriz(int **matriz);

/**
 * \brief Imprime a faturação entre um intervalo de meses.
*/
void intMeses(int m1, int m2, int vendas, double fat);

/**
 * \brief Informações sobre as vendas de um produto, num determinado mês, por filial.
*/
void filiais(int i, int **fils, double **dfils);

/**
 * \brief Informações sobre as vendas de um produto, num determinado mês, globalmente.
*/
void fatura(int *geral, double *dgeral);

/**
 * \brief Imprime uma string, que necessita de um inteiro para poder comunicar com o programa.
 * 
 * @returns O inteiro pedido.
 */
int pedirInteiro(char *mensagem);

/**
 * \brief Imprime uma string, que necessita de um char para poder comunicar com o programa.
 * 
 * @returns O char pedido.
 */
char pedirChar(char *mensagem);

/**
 * \brief Imprime uma string, com um dado tamanho.
*/
void pedirString(char *mensagem, char *buff);

/**
 * \brief Permite navegar pelas páginas das listas de algumas queries.
 * 
 * @returns Número que permite avançar ou retroceder na página, ou sair.
 */
int navegador(TAD_List tl, int i, int f, int size, f_print fp_elem);

/**
 * \brief Imprime um elemento do tipo string.
 * 
 * @param e String a imprimir.
 */
void printReg(gpointer e);

/**
 * \brief Imprime um elemento do tipo ProdDescriptor
 * 
 * @param e ProdDescriptor a imprimir.
 */
void printTop(gpointer e);
#endif
