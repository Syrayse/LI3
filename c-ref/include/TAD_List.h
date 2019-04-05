/**
 * @file TAD_List.h
 * \brief Define o mõdulo de armazenamento e apresentação de tipos abstratos de dados.
 * 
 * Isto é tornado possivél através de uma classe que armazena e permite transversar
 * tipos abstratos de dados.
 */
#ifndef _TAD_LIST_H_
#define _TAD_LIST_H_

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `TAD_List`.
 */
typedef struct tad_list *TAD_List;

/**
 * \brief Permite criar uma instância da classe `TAD_List`.
 * 
 * @param f Função de destruição dos elementos da lista.
 * @param size Capacidade máxima que se pretende fornecer à instância.
 * 
 * @returns Nova instância.
 */
TAD_List list_make(GFreeFunc f, unsigned int size);

/**
 * \brief Destrói uma instância da classe `TAD_List`.
 * 
 * @param tl Instância que se pretender destruir.
 */
void list_destroy(TAD_List tl);

/**
 * \brief Calcula o tamanho de uma `TAD_List`.
 * 
 * @param tl Instância que se pretende verificar.
 * 
 * @returns Tmananho da `TAD_List`.
 */
unsigned int list_size(TAD_List tl);

/**
 * \brief Obter um elemento da `TAD_List` segundo um indice.
 * 
 * @param tl Instância que se pretende utilizar.
 * @param index Indice do elemento.
 * 
 * @returns Elemento na posição `index`, ou NULL caso este não exista.
 */
gpointer list_get_index(TAD_List tl, unsigned int index);

/**
 * \brief Adiciona um novo elemento à `TAD_List`.
 * 
 * @param tl Instância na qual se pretende adicionar.
 * @param v Elemento que se pretende adicionar.
 * 
 * @returns 1 se for possivél adicionar, 0 caso contrário.
 */
int list_add(TAD_List tl, gpointer v);

/**
 * \brief Permite fazer a ordenação de uma lista.
 * 
 * @param tl Lista que se pretende ordenar.
 * @param fc Função de ordenação pela qual se deve ordenar.
 */
void list_sort(TAD_List tl, GCompareFunc fc);

#endif