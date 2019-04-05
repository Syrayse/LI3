/**
* @file Verifier.h
* \brief Interface da classe de validação, `Verifier`, e todas as necessárias funções de validação.
* 
* Neste módulo encontram-se definidas todas as necessárias funções de serviços de validação.
* 
* Sendo o principal deles, a classe `Verifier`, que corresponde a um agregado de metódos encadeados de tal
* forma que permit em a criação de uma _stream_ de metódos que são aplicados sucessivamente à medida que se pretende
* validar um código de transação e criar a respetiva`Transaction`. Permitindo assim uma fluidez computacional ao ser utilizada a função `strtok`.
* 
* Para além disso, permite também que o cliente faça validação semântica dos seus produtos
* e cliente, criando também as suas respetivas instâncias.
*/

#ifndef __VERIFF__
#define __VERIFF__

#include "Client.h"

#include "Product.h"

#include "Transaction.h"

/**
 * \brief Tipo opaco representativo de uma instância da classe `Verifier`.
 */
typedef struct verifier *Verifier;

/**
 * \brief Criar uma instância da classe `Verifier`.
 * 
 * Ao criar a instância da classe `Verifier`, são a estas atribuidas todas as funções
 * de validação internamente necessárias para o correto processamento da validaçao de uma venda.
 * Mantendo sempre em mente a correspondência unívoca que deve exister entre indíce do array
 * e posição no registo de transação.
 * 
 * @returns Uma nova instância.
 */
Verifier Verifier_make();

/**
 * \brief Destrói uma instância da classe `Verifier`.
 */
void Verifier_destroy(Verifier v);

/**
 * \brief Permite validar semânticamente um cliente e criar a respectiva estrutura.
 * 
 * @returns Uma instância de `Client` caso este seja válido, NULL caso contrário.
 */
Client verify_client(char *client);

/**
 * \brief Permite validar semânticamente um produto e criar a respectiva estrutura.
 * 
 * @returns Uma instância de `Product` caso este seja válido, NULL caso contrário.
 */
Product verify_product(char *product);

/**
 * \brief Metódo da classe `Verifier` que permite realizar a validação e criação de uma `Transaction` apartir da sua _String_ representativa.
 * 
 * Este metódo tira partido das propriedades da classe `Verifier` de tal modo que usa o seu metódo
 * de verificação eficiente de registos de transação de forma a conseguir paralelamente
 * verificar e atribuir a uma dada instância da classe `Transaction` todos os parametros a esta necessários.
 * 
 * Este metódo de validação permite validar todos os registos de transações seguindo os pressupostos estabelecidos
 * pela classe `Verifier` sobre a estruturação de um registo  de transação. E para além disso, verifica também
 * se o número de argumentos da _String_ representativa é de facto válido.
 * 
 * @param v Instância da classe `Verifier` a ser utilizada na verificação.
 * @param trans_code _String_ representativa de uma transação.
 *
 * @returns Uma instância da classe `Transaction` se a sua _String_ representativa for considerada válida, NULL caso contrário.
 */
Transaction verify_sale(Verifier v, char *trans_code);

#endif