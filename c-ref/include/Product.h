/**
 * @file Product.h
 * \brief Define a interface de metódos aplicáveis em instâncias da classe `Product`.
 * 
 * Esta interface visa facilitar a comunicação com entidades externa que pretendam obter informação
 * de um instância de `Product`. Este módulo está especificamente desenhado de forma a facilitar a sua integração
 * em tabelas de hash, através de metódos `product_hash` e `product_equal`.
 */
#ifndef __PRODUCT_ADT__
#define __PRODUCT_ADT__

#include <glib.h>

/**
 * \brief Define o tamanho de um código de produto.
 */
#define PRODUCT_LEN 6

/**
 * \brief Tipo opaco representativo da classe `Product`.
 */
typedef struct product *Product;

/**
 * \brief Permite criar uma instância da classe `Product`.
 * 
 * @param product_code O código associado a um certo produto.
 * 
 * @returns Um nova instância.
 */
Product product_make(char *product_code);

/**
 * \brief Destrói uma instância da classe `Product`.
 * 
 * @param p Instância a destruir.
 */
void product_destroy(Product p);

/**
 * \brief Permite criar uma instância que é uma cópia exata de outra instância.
 * 
 * @param p Instância que se pretende copiar.
 * 
 * @returns Instância cópia.
 */
Product product_clone(Product p);

/**
 * \brief Obtem uma cópia do código associado à instância.
 * 
 * @param p instância a considerar.
 * 
 * @returns Cópia do código associado à instância.
 */
char *product_get_code(Product p);

/**
 * \brief Indica qual é a primeira letra do código de um produto.
 * 
 * @param p Produto a considerar.
 * 
 * @returns Primeira letra do código do produto.
 */
int product_get_first_let(Product p);

/**
 * \brief Calcula o _hash code_ de uma instância da classe `Product`.
 * 
 * @param p Instância a considerar.
 * 
 * @returns _Hash code_ calculado.
 */
guint product_hash(gconstpointer v);

/**
 * \brief Verifica se duas instâncias são iguais.
 * 
 * @param v1 Primeira instância a considerar.
 * @param v2 Segunda instância a considerar.
 * 
 * @returns`TRUE` se as instâncias forem iguais, `FALSE` caso contrário.
 */
gboolean product_equal(gconstpointer v1, gconstpointer v2);

#endif