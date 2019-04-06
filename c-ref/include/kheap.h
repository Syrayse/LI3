/**
 * @file kheap.h
 * \brief Interface de todos os métodos que permitem a interação com instâncias da classe `KHeap`.
 */
#ifndef KHEAP_H
#define KHEAP_H

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `KHeap`.
 */
typedef struct kheap *KHeap;

/**
 * \brief Cria e inicializa uma `KHeap`.
 * 
 * @param fc Função de comparação utilizada.
 * @param ff Função de destruição dos elementos da kheap.
 * 
 * @returns Uma nova `KHeap`.
 */
KHeap kheap_make(GCompareFunc fc, GFreeFunc ff);

/**
 * \brief Liberta a memória associada a uma `KHeap`.
 * 
 * @param kh `KHeap` que se pretende libertar.
 */
void kheap_destroy(KHeap kh);

/**
 * \brief Adiciona um elemento à `KHeap`.
 * 
 * @param kh Instância a considerar.
 * @param v Elemento que se pretender adicionar.
 */
void kheap_add(KHeap kh, gpointer v);

/**
 * \brief Indica qual é o elemento que se encontra na raiz da `KHeap`, sem o retirar da heap.
 * 
 * @param kh Instância a considerar.
 * 
 * @returns O elemento na raiz da `KHeap`, ou NULL caso não exista.
 */
gpointer kheap_check_root(KHeap kh);

/**
 * \brief Indica e retira da mesma o elemento que se encontra na raiz da `KHeap`.
 * 
 * @param kh Instância a considerar.
 * 
 * @returns O elemento que estava na raiz, ou NULL caso não exista.
 */
gpointer kheap_extract_root(KHeap kh);

/**
 * \brief Calcula quantos elementos existem na `KHeap`.
 * 
 * @param kh Instância a considerar.
 * 
 * @returns O número de elementos na `KHeap`.
 */
size_t kheap_size(KHeap kh);

/**
 * \brief Verifica se uma `KHeap` é vazia.
 * 
 * @param kh Instância a considerar.
 * 
 * @returns 1 se a `KHeap` for vazia, 0 caso contrário.
 */
int kheap_is_empty(KHeap);

#endif