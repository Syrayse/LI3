/**
 * @file ProdDescriptor.h
 * \brief Interface que contem todos os metódos da classe `ProdDescriptor`. 
 * 
 * Permitir descrever informação considerada útil na query11, associada a um produto.
 */

#ifndef _PROD_DESCRIPTOR_H_
#define _PROD_DESCRIPTOR_H_

#include "Product.h"

/**
 * \brief Tipo opaco representativo de instâncias da classe `ProdDescriptor`.
 */
typedef struct proddescriptor *ProdDescriptor;

/**
 * \brief Cria uma instância da classe `ProdDescriptor`.
 * 
 * @param p Produto que se pretende descrever.
 * @param nclients Número de clientes associados ao produto que se pretende descrever.
 * @param vec_filial Conjunto de valores que se pretende adicionar ao descritor.
 * 
 * @returns Uma nova instância da classe `ProdDescriptor`.
 */
ProdDescriptor proddescrip_make(Product p, int nclients, int *vec_filial);

/**
 * \brief Destrói uma instância da classe `ProdDescriptor`.
 * 
 * @param pd Instância a considerar.
 */
void proddescrip_destroy(ProdDescriptor pd);

/**
 * \brief Calcula o número de unidades vendidas associadas a uma filial e produto.
 * 
 * @param pd Instância a considerar.
 * @param filial Filial que se pretende verificar.
 * 
 * @returns O número de unidades vendidas naquela filial.
 */
int proddescrip_get_fil_units(ProdDescriptor pd, int filial);

/**
 * \brief Calcula o número de clientes associados a um produto.
 * 
 * @param pd Instância a considerar.
 * 
 * @returns Número de clientes associados a um produto.
 */
int proddescrip_get_n_clients(ProdDescriptor pd);

/**
 * \brief Indica o produto que se está a descrever.
 * 
 * @param pd Instância a considerar.
 * 
 * @returns O produto que se está a descrever.
 */
Product proddescrip_get_product(ProdDescriptor pd);

#endif