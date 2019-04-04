/**
 * @file CatProducts.h
 * \brief Define a interface útil para os metódos do catálogo de produtos. 
 */

#ifndef CAT_PRODUCTS_H
#define CAT_PRODUCTS_H

/**
 * \brief Estrutura de dados que define um catálogo de produtos.
 */
typedef struct cat_products *CatProducts;

/**
 * \brief Permite inicializar um catálogo de produtos.
 * 
 * @returns Um novo catálogo de produtos.
 */
CatProducts CatProducts_make();

/**
 * \brief Permite libertar a memória associada a um catálogo de produtos.
 * 
 * @param cp Catálogo de produtos que se pretende libertar.
 */
void CatProducts_destroy(CatProducts cp);

/**
 * \brief Verifica se um produto existe no catálogo de produtos.
 * 
 * @param cp Catálogo de produtos a considerar.
 * @param product Produto que se pretende verificar.
 * 
 * @returns 1 caso o produto exista no catálogo, 0 caso contrário.
 */
int CatProducts_exists(CatProducts cp, Product product);

/**
 * \brief Adiciona um produto a um catálogo de produtos.
 * 
 * @param cp Catálogo de produtos no qual se pretende adicionar.
 */
void CatProducts_add_product(CatProducts cp, Product product);

/**
 * \brief Função que permite transmitir ao catálogo de produtos que foi efetuada uma transaç
 * ão associada a um dado produto e filial.
 * 
 * Esta mensagem de efetuamento de transação é necessário para o tratamento de uma das queries
 * de forma eficiente.
 * 
 * @param cp Catálogo de produtos que se pretende utilizar.
 * @param product Produto que se pretende atualizar.
 * @param filial Filial na qual ocorreu a transação.
 */
void CatProduct_report_trans(CatProducts cp, Product product, int filial);

/**
 * \brief Cria uma lista com todos os códigos de produtos que começam com uma dada letra.
 * 
 * @param cp Catálogo de produtos que se pretende considerar.
 * @param let Primeira letra que se pretende considerar.
 * 
 * @returns Uma lista com todos os códigos de produtos que começam com uma dada letra.
 */
TAD_List CatProducts_dump_ordered(CatProducts cp, char let);

/**
 * \brief Calcula o número total de produtos do catálogo que nunca foram comprados.
 * 
 * @param cp Catálogo de produtos a considerar.
 * 
 * @returns O valor calculado.
 */
int CatProducts_get_total_not_bought(CatProducts cp);

/**
 * \brief Cria uma lista com todos os códigos de produtos do catálogo que nunca foram comprados.
 * 
 * @param cp Catálogo de produtos a considerar.
 * 
 * @returns A lista criada.
 */
TAD_List CatProducts_not_bought(CatProducts cp);

/**
 * \brief Cria uma lista com todos os códigos de produtos do catálogo que nunca foram comprados numa certa filial.
 * 
 * @param cp Catálogo de produtos a considerar.
 * @param filial Filial a considerar.
 * 
 * @returns A lista criada.
 */
TAD_List CatProducts_not_bought_fil(CatProducts cp, int filial);

#endif