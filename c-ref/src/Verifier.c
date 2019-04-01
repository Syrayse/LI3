/**
 * @file Verifier.c
 * \brief Módulo que define a classe de validação, `Verifier`, e todas as necessárias funções de validação.
 * 
 * Neste módulo encontram-se definidas todas as necessárias funções de serviços de validação.
 * 
 * Sendo o principal deles, a classe `Verifier`, que corresponde a um agregado de metódos encadeados de tal
 * forma que permitem a criação de um _stream_ de metódos que são aplicados sucessivamente à medida que se pretende
 * validar uma `Transaction`. Permitindo assim uma fluidez de códigos e computacional ao ser utilizada a função `strtok`.
 * 
 * Para além disso, permite também que o cliente faça validação semântica dos seus produtos
 * e cliente.
 * 
 * @see Transaction
 */

#include "Verifier.h"
#include "util.h"
#include <glib.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
Verifier Verifier_make();
void Verifier_destroy(Verifier v);
char *verify_client(char *client);
char *verify_product(char *product);
Transaction verify_sale(Verifier v, char *trans_code);

Transaction trans_make();
void trans_destroy(void *e);

void trans_copy_product(Transaction src, char *dest);
void trans_copy_client(Transaction src, char *dest);

char *trans_get_client(Transaction t);
char *trans_get_product(Transaction t);
unsigned char trans_get_month(Transaction t);
unsigned char trans_get_filial(Transaction t);
unsigned char trans_get_promo(Transaction t);
unsigned char trans_get_units(Transaction t);
double trans_get_price(Transaction t);
double trans_get_rev(Transaction t);

/* Metodos privados */
static int is_valid_client(char *client);
static int is_valid_product(char *product);
static char *verify_word(char *word, int (*fv)(char *));
static int _set_trans_valid_product(char *product, Transaction t);
static int is_valid_price(char *price, Transaction t);
static int is_valid_units(char *units, Transaction t);
static int is_valid_promo(char *promo, Transaction t);
static int _set_trans_valid_client(char *client, Transaction t);
static int is_valid_month(char *month, Transaction t);
static int is_valid_filial(char *filial, Transaction t);

// ------------------------------------------------------------------------------

/**
 * \brief Typedef utilizado de forma a simplificar parametrização de funções.
 */
typedef int (*scompare)(char *, Transaction);

/**
 * \brief Classe `Verifier` contendo todas as variavéis de instâncias necessárias
 * ao seu bom funcionamento.
 * 
 * Internamente a classe `Verifier`, que tem como objetivo final validar unicamente
 * registos de transação e formar a `Transaction` correspondente, é formada unicamente
 * por um _array_ de tantas funções como argumentos num registos de transações. Sendo que
 * este número de argumento se encontra descrito por `N_TRANS_ARGS`.
 * 
 * Cada posição _n_ neste _array_ deve conter uma função, tal que esta seja capaz
 * de validar e adicionar a uma `Transaction` o n-ésimo parametro da ordem estabelecida para
 * registos de transação, que segue a seguinte formatação:
 * 
 *  [PRODUTO] [PREÇO] [UNIDADES VENDIDAS] [PROMOÇÃO] [CLIENTE] [MÊS] [FILIAL]
 * 
 * Logo, por exemplo, o indice 2 do array na classe `Verifier`, deverá corresponder univocamente
 * a um função capaz de validar e atribuir a uma `Transaction` o número de unidades que foram
 * transacionadas naquele registo.
 * 
 * @see scompare
 * @see Transaction
 */
typedef struct verifier
{
    scompare fa[N_TRANS_ARGS];
} * Verifier;

/**
 * \brief Estrutura que armazena toda a informação necessária para um registo de transação.
 */
typedef struct transaction
{
    char client[CLT_LEN + 1],  /**< Cliente associado à transação. */
        product[PROD_LEN + 1]; /**< Produto associado à transação. */
    unsigned char month,       /**< Mês da transação. */
        filial,                /**< Filial onde se deu a transação. */
        promo,                 /**< Código promocional associado à transação.  */
        units;                 /**< Unidades envolvidas na transação. */
    double price;              /**< Preço do produto da transação. */
} * Transaction;

// ------------------------------------------------------------------------------

/**
 * \brief Delimitadores base que permitem compatibilidade com maioria dos sistemas operativos.
 */
#define BASE_DELIM " \n\r"

// ------------------------------------------------------------------------------

/**
 * \brief Criar uma instância da classe `Verifier`.
 * 
 * Ao criar a instância da classe `Verifier`, são a estas atribuidas todas as funções
 * de validação internamente necessárias para o correto processamento da validaçao de uma venda.
 * Mantendo sempre em mente a correspondência unívoca que deve exister entre indíce do array
 * e posição no registo de transação.
 * 
 * @returns Uma nova instância.
 * 
 * @see _set_trans_valid_product;
 * @see is_valid_price;
 * @see is_valid_units;
 * @see is_valid_promo;
 * @see _set_trans_valid_client;
 * @see is_valid_month;
 * @see is_valid_filial;
 */
Verifier Verifier_make()
{
    Verifier v = g_malloc(sizeof(struct verifier));
    v->fa[0] = _set_trans_valid_product;
    v->fa[1] = is_valid_price;
    v->fa[2] = is_valid_units;
    v->fa[3] = is_valid_promo;
    v->fa[4] = _set_trans_valid_client;
    v->fa[5] = is_valid_month;
    v->fa[6] = is_valid_filial;
    return v;
}

/**
 * \brief Destrói uma instância da classe `Verifier`.
 */
void Verifier_destroy(Verifier v)
{
    if (v)
    {
        g_free(v);
    }
}

/**
 * \brief Permite validar semânticamente um cliente.
 * 
 * De forma a permitir a correta validação semântica do cliente é utilizada
 * a função `verify_word` passando como argumento o cliente que se pretende
 * validar em conjunto com a função `is_valid_client`.
 * 
 * @returns Uma cópia do cliente se este for válido, NULL caso contrário.
 *
 * @see verify_word
 * @see is_valid_client
 */
char *verify_client(char *client)
{
    return client ? verify_word(client, is_valid_client) : NULL;
}

/**
 * \brief Permite validar semânticamente um produto.
 * 
 * De forma a permitir a correta validação semântica do produto é utilizada
 * a função `verify_word` passando como argumento o produto que se pretende
 * validar em conjunto com a função `is_valid_product`.
 * 
 * @returns Uma cópia do produto se este for válido, NULL caso contrário.
 *
 * @see verify_word
 * @see is_valid_client
 */
char *verify_product(char *product)
{
    return product ? verify_word(product, is_valid_product) : NULL;
}

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
 * @param cp Catálogo de produtos em vigor.
 * @param cc Catálogo de cliente em vigor.
 * @param id ID de identificação a ser atribuido à `Transaction`.
 * 
 * @returns Uma instância da classe `Transaction` se a sua _String_ representativa for considerada válida, NULL caso contrário.
 * 
 * @see trans_make
 * @see trans_exists_efect
 * @see trans_destroy
 * @see trans_set_id
 */
Transaction verify_sale(Verifier v, char *trans_code)
{
    if (!v || !trans_code)
        return NULL;

    int t, i, r = 1;
    Transaction dest = trans_make();
    char *token = strtok(trans_code, BASE_DELIM);

    for (i = 0; r && token && i < N_TRANS_ARGS; i++, token = strtok(NULL, BASE_DELIM))
    {
        t = (*v->fa[i])(token, dest);
        r = min(r, t);
    }

    if (token && i >= N_TRANS_ARGS)
    {
        r = 0;
    }

    return dest;
}

/**
 * \brief Cria uma transação.
 * 
 * returns Transação criada.
 */
Transaction trans_make()
{
    Transaction t = g_malloc(sizeof(struct transaction));
    t->month = t->filial = t->promo = t->units = 0;
    t->price = 0.0;
    return t;
}

/**
 * \brief Destrói uma transação.
 * 
 * @param e Transação a destruir.
 */
void trans_destroy(void *e)
{
    Transaction t;

    if (e)
    {
        t = (Transaction)e;
        g_free(t);
    }
}

/**
 * \brief Cópia o código de produto para um dado endereço.
 * 
 * @param src Transação a ser utilizada.
 * @param dest Endereço onde irá ser colocada uma cópia do código do produto.
 */
void trans_copy_product(Transaction src, char *dest)
{
    strcpy(dest, src->product);
}

/**
 * \brief Cópia o código de cliente para um dado endereço.
 * 
 * @param src Transação a ser utilizada.
 * @param dest Endereço onde irá ser colocada uma cópia do código do cliente.
 */
void trans_copy_client(Transaction src, char *dest)
{
    strcpy(dest, src->client);
}

/**
 * \brief Calcula o cliente associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O cliente da transação.
 */
char *trans_get_client(Transaction t)
{
    return g_strdup(t->client);
}

/**
 * \brief Calcula o produto associado a uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O produto da transação.
 */
char *trans_get_product(Transaction t)
{
    return g_strdup(t->product);
}

/**
 * \brief Calcula o mês a que se deu uma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O mês da transação.
 */
unsigned char trans_get_month(Transaction t)
{
    return t->month;
}

/**
 * \brief Calcula a filial onde se deu a transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns A filial calculada.
 */
unsigned char trans_get_filial(Transaction t)
{
    return t->filial;
}

/**
 * \brief Calcula o código promocional duma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O código promocional da transação.
 */
unsigned char trans_get_promo(Transaction t)
{
    return t->promo;
}

/**
 * \brief Calcula quantas unidades estão envolvidas na transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O número de unidades envolvidas.
 */
unsigned char trans_get_units(Transaction t)
{
    return t->units;
}

/**
 * \brief Calcula o preço a que se deu a transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O preço realizado.
 */
double trans_get_price(Transaction t)
{
    return t->price;
}

/**
 * \brief Calcula o cashflow obtido duma transação.
 * 
 * @param t Transação a verificar.
 * 
 * @returns O cashflow obtido.
 */
double trans_get_rev(Transaction t)
{
    return (t->units * t->price);
}

/**
 * \brief Permite validar a _String_ representativa de um cliente.
 * 
 * Esta função utiliza pressupostos pré-estabelecidos de forma a verificar se
 * a _String_ representativa do cliente se encontra semanticamente correta.
 * 
 * @param client Cliente que se pretende verificar.
 * 
 * @returns 1 se o cliente for válido, 0 caso contrário.
 */
static int is_valid_client(char *client)
{
    return (g_ascii_isupper(client[0]) &&
            is_between(atoi(client + 1), 1000, 5000) &&
            (client[5] == '\0'));
}

/**
 * \brief Permite validar a _String_ representativa de um produto.
 * 
 * Esta função utiliza pressupostos pré-estabelecidos de forma a verificar se
 * a _String_ representativa do produto se encontra semanticamente correta.
 * 
 * @param product Produto que se pretende verificar.
 * 
 * @returns 1 se o produto for válido, 0 caso contrário.
 */
static int is_valid_product(char *product)
{
    return (g_ascii_isupper(product[0]) &&
            g_ascii_isupper(product[1]) &&
            is_between(atoi(product + 2), 1000, 9999) &&
            (product[6] == '\0'));
}

/**
 * \brief Função que procede à validação de uma só palavra, segundo uma dada função de validação.
 * 
 * Para esta função proceder corretamente, deve ser passado como argumento uma função de validação
 * que dada uma só palavra `word` permite realizar a validação semântica que se pretende desta.
 * 
 * @param word Palavra que se pretende verificar.
 * @param fv Função de validação da palavra.
 * 
 * @returns A própria palavra caso esta seja válida, NULL caso contrário.
 */
static char *verify_word(char *word, int (*fv)(char *))
{
    return ((word && fv && (*fv)(word)) ? word : NULL);
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` um produto.
 * 
 * O metódo efetua a validação semântica da _String_ representativa do produto,
 * através da função `is_valid_product` e para além disso, no caso de esta ser válida é
 * atribuida à `Transaction` o seu respetivo produto.
 * 
 * @param product _String_ representativa do produto em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se o produto é válido e foi atribuido, 0 caso contrário.
 * 
 * @see is_valid_product
 */
static int _set_trans_valid_product(char *product, Transaction t)
{
    int r = is_valid_product(product);

    if (r)
    {
        strcpy(t->product, product);
    }

    return r;
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` um preço.
 * 
 * O metódo faz a conversão entre uma _String_ representativa de um preço 
 * e o respetivo preço, procedendo à sua validação segundo pressupostos
 * pré-estabelecidos.
 * 
 * @param price _String_ representativa do preço em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se o preço é válido e foi atribuido, 0 caso contrário.
 */
static int is_valid_price(char *price, Transaction t)
{
    double f = (double)atof(price);
    int r = is_between(f, 0.0, 999.99);

    if (r)
    {
        t->price = f;
    }

    return r;
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` um número de unidades transacionadas.
 * 
 * O metódo faz a conversão entre uma _String_ representativa de um número de unidades 
 * e o respetivo número de unidades, procedendo à sua validação segundo pressupostos
 * pré-estabelecidos.
 *
 * @param units _String_ representativa do número de unidades em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se o número de unidades é válido e foi atribuido, 0 caso contrário.
 */
static int is_valid_units(char *units, Transaction t)
{
    int r, f = atoi(units);
    r = is_between(f, 1, 200);

    if (r)
    {
        t->units = f;
    }

    return r;
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` uma promoção.
 * 
 * O metódo faz a conversão entre uma _String_ representativa de uma promoção
 * e a respetiva promoção, procedendo à sua validação segundo pressupostos
 * pré-estabelecidos.
 * 
 * @param promo _String_ representativa da promoção em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se a promoção é válida e foi atribuida, 0 caso contrário.
 */
static int is_valid_promo(char *promo, Transaction t)
{
    int r = (*promo == 'N' || *promo == 'P');

    if (r)
    {
        t->promo = *promo;
    }

    return r;
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` um cliente.
 * 
 * O metódo efetua a validação semântica da _String_ representativa do cliente,
 * através da função `is_valid_client` e para além disso, no caso de esta ser válida é
 * atribuido à `Transaction` o seu respetivo cliente.
 * 
 * @param client _String_ representativa do cliente em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se o cliente é válido e foi atribuido, 0 caso contrário.
 * 
 * @see is_valid_client
 */
static int _set_trans_valid_client(char *client, Transaction t)
{
    int r = is_valid_client(client);

    if (r)
    {
        strcpy(t->client, client);
    }

    return r;
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` um mês.
 * 
 * O metódo faz a conversão entre uma _String_ representativa de um mês
 * e o respetivo mês, procedendo à sua validação segundo pressupostos
 * pré-estabelecidos.
 * 
 * @param month _String_ representativa do mês em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se o mês é válido e foi atribuido, 0 caso contrário.
 */
static int is_valid_month(char *month, Transaction t)
{
    int r, f = atoi(month);
    r = is_between(f, 1, 12);
    if (r)
        t->month = f;
    return r;
}

/**
 * \brief Metódo que verifica e atribui a uma `Transaction` uma filial.
 * 
 * O metódo faz a conversão entre uma _String_ representativa de uma filial
 * e a respetiva filial, procedendo à sua validação segundo pressupostos
 * pré-estabelecidos.
 * 
 * @param filial _String_ representativa da filial em questão.
 * @param t `Transaction` que irá ser o recepiente de possivéis atribuições.
 * 
 * @returns 1 se a filial é válida e foi atribuida, 0 caso contrário.
 */
static int is_valid_filial(char *filial, Transaction t)
{
    int r, f = atoi(filial);
    r = is_between(f, 1, 3);
    if (r)
        t->filial = f;
    return r;
}