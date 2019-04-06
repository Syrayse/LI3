/**
 * @file NavControl.h
 * \brief Define a interface dos métodos públicos associados à classe `NavControl`.
 * 
 * Através desta classe é possível transversar informação de uma forma mais dinâmica,
 * seguindo a ideia de páginas, sendo possível passar uma página para trás ou para a frente.
 * 
 * De forma a ser utilizável é preciso passar um dicionário a partir do qual vai ser feita a leitura dinâmica, e como se pretende
 * que este seja imprimido. Depois disso, este é interpretado como se de um livro se tratasse, estando limitado a um número
 * fixo de entradas por cada página.
 */

#ifndef __CONTROL_NAVIGATOR__
#define __CONTROL_NAVIGATOR__

#include "TAD_List.h"

/**
 * \brief Typedef para simplificar a escrita de uma função que tem a capacidade de impressão.
 */
typedef void (*f_print)(gpointer);

/**
 * \brief Tipo opaco representativo de uma instância da classe `NavControl`.
 */
typedef struct nav_control *NavControl;

/**
 * \brief Cria uma instância da classe `NavControl`.
 * 
 * @returns Uma nova instância da classe `NavControl`.
 */
NavControl NavControl_make();

/**
 * \brief Destrói uma instância da classe `NavControl`.
 * 
 * @param nc Instância a ser destruída. 
 */
void NavControl_destroy(NavControl nc);

/**
 * \brief Altera o dicionário em vigor no `NavControl`.
 * 
 * Permite alterar o dicionário que se pretende verificar através do `NavControl`.
 * Se um dicionário já estiver em vigor este é discartado.
 * 
 * Para além disso, é passada um função de impressão que permite ao utilizador
 * deste método escolher como permite imprimir cada elemento.
 * 
 * @param nc Instância a ser considerada.
 * @param tl Novo dicionário a ser colocado.
 * @param user_data Informação pertinente ao conteúdo do dicionário.
 * @param fp_elem Função de impressão do novo dicionário, a ser aplicada a cada elemento deste. 
 * @param fp_user Função de impressão de informação pertinente ao conteúdo do dicionário.
 */
void NavControl_change_dict(NavControl nc, TAD_List tl, gpointer user_data, f_print fp_elem, f_print fp_user);

/**
 * \brief Permite passar para a próxima página de elementos que se pretende visualizar.
 * 
 * Dependendo da variável de instância de `NavControl`, `nPerPage`, são alterados os parâmetros
 * `init` e `end` de forma a tentar simular o que seria o passar de uma página.
 * 
 * @returns 1 se foi possível avançar para a próxima página, 0 caso contrário.
 */
int NavControl_next_page(NavControl nc);

/**
 * \brief Permite retroceder para a página anterior de elementos que se pretende visualizar.
 * 
 * Dependendo da variável de instância de `NavControl`, `nPerPage`, são alterados os parâmetros
 * `init` e `end` de forma a tentar simular o que seria retroceder uma página.
 * 
 * @returns 1 se foi possível retroceder para a página anterior, 0 caso contrário.
 */
int NavControl_previous_page(NavControl nc);

/**
 * \brief Imprime no ecrã o correspondente a uma página.
 * 
 * A formatação desta página possui, um _header_ com informação útil à
 * página corrente, os elementos da página, segundo a aplicação da função
 * `f_print` e para além disso um rodapé, também com informação útil.
 * 
 * @param nc Instância a considerar.
 */
void NavControl_show(NavControl nc);

/**
 * \brief Calcula o índice do primeiro elemento da página atual.
 * 
 * @param nc Instância a considerar.
 * 
 * @returns O índice do primeiro elemento da página atual.
 */
int NavControl_get_init(NavControl nc);

/**
 * \brief Calcula o índice do último elemento da página atual.
 * 
 * @param nc Instância a considerar.
 * 
 * @returns O índice do último elemento da página atual.
 */
int NavControl_get_end(NavControl nc);

/**
 * \brief Calcula a página atual em que se encontra o navegador.
 * 
 * @param nc Instância a considerar.
 * 
 * @returns A página atual.
 */
int NavControl_get_page(NavControl nc);

#endif