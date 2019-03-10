#include "validation.h"
#include "vendasman.h"
#include "mainstruct.h"
#include "util.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
MAN_b make_man(void);
void destroy_man(MAN_b);
int insert_client_man(MAN_b, char *);
int insert_product_man(MAN_b, char *);
int insert_sale_man(MAN_b, SALE);

int get_maior_linha(MAN_b);
int get_n_produtos(MAN_b);
int get_n_vendas_total(MAN_b);
int get_n_vendas_filial(MAN_b, int);
int get_n_clientes_total(MAN_b);
int get_n_clientes_alph(MAN_b, char);
float get_cashflow_total(MAN_b);
char *get_last_client(MAN_b);
int get_client_n_vendas(MAN_b, char *);
int get_not_sold_client(MAN_b);
int get_not_sold_product(MAN_b);

void set_maior_linha(MAN_b, int);
void set_last_client(MAN_b, SALE);

void show_boletim_vendas(MAN_b mn);

/* Metodos privados */

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de dados que encapsula a gestão principal.
 **/
typedef struct manb
{
    DBase clients,                    /**< Base de dados dos clientes */
        products;                     /**< Base de dados dos produtos */
    char lastClient[7];               /**< Ultimo cliente lido */
    int maiorLinha,                   /**< Maior linha lida */
        nVendasFiliais[3],            /**< Numero de vendas por filial */
        nClientesAlph['Z' - 'A' + 1]; /**< Numero de clientes letra */
    float totalCashFlow;              /**< Lucro total da empresa */
} * MAN_b;

// ------------------------------------------------------------------------------

/**
 * \brief Cria em memória uma estrutura de gestão principal.
 **/
MAN_b make_man(void)
{
    int i;
    MAN_b b = g_malloc(sizeof(struct manb));
    b->clients = make_dbase();
    b->products = make_dbase();
    b->lastClient[0] = '\0';
    b->maiorLinha = -1;
    for (i = 0; i < 3; i++)
        b->nVendasFiliais[i] = 0;
    for (i = 0; i < 'Z' - 'A' + 1; i++)
        b->nClientesAlph[i] = 0;
    b->totalCashFlow = 0;
    return b;
}

/**
 * \brief Liberta de memoria uma estrutura de gestão principal.
 **/
void destroy_man(MAN_b b)
{
    if (b)
    {
        destroy_dbase(b->clients);
        destroy_dbase(b->products);
        g_free(b);
    }
}

/**
 * \brief Insere uma dado cliente na respetiva base de dados.
 **/
int insert_client_man(MAN_b b, char *s)
{
    int r = insert_dbase(b->clients, s, NULL);
    if (!r)
        b->nClientesAlph[(int)(*s - 'A')]++;
    return r;
}

/**
 * \brief Insere uma dado produto na respetiva base de dados.
 **/
int insert_product_man(MAN_b b, char *s)
{
    return insert_dbase(b->products, s, NULL);
}

/**
 * \brief Tenta inserir uma venda na base de dados, só se esta for válida.
 **/
int insert_sale_man(MAN_b b, SALE s)
{
    int r = validate_s(b->products, b->clients, s);
    if (r)
    {
        insert_self_s(b->products, b->clients, s);

        copy_client_s(s, b->lastClient);

        b->nVendasFiliais[get_filial_s(s) - 1]++;

        b->totalCashFlow += (get_units_s(s) * get_price_s(s));
    }

    return r;
}

/**
 * \brief Calcula a maior linha lida.
 **/
int get_maior_linha(MAN_b b)
{
    return b->maiorLinha;
}

/**
 * \brief Retorna o numero de produtos na base de dados.
 **/
int get_n_produtos(MAN_b b)
{
    return get_size_dbase(b->products);
}

/**
 * \brief Calcula o numero de vendas lidas.
 **/
int get_n_vendas_total(MAN_b b)
{
    int i, r = 0;
    for (i = 0; i < 3; i++)
        r += b->nVendasFiliais[i];
    return r;
}

/**
 * \brief Calcula o numero de vendas por filial.
 **/
int get_n_vendas_filial(MAN_b b, int filial)
{
    int r = -1;
    if (is_between(filial, 1, 3))
        r = b->nVendasFiliais[filial - 1];
    return r;
}

/**
 * \brief Retorna o numero de clientes na base de dados.
 **/
int get_n_clientes_total(MAN_b b)
{
    return get_size_dbase(b->clients);
}

/**
 * \brief Calcula o numero de clientes que começa por uma dada letra.
 **/
int get_n_clientes_alph(MAN_b b, char inicial)
{
    int r = -1;
    if (is_between(inicial, 'A', 'Z'))
        r = b->nClientesAlph[inicial - 'A'];
    return r;
}

/**
 * \brief Calcula o numero total obtido.
 **/
float get_cashflow_total(MAN_b b)
{
    return b->totalCashFlow;
}

/**
 * \brief Retorna o ultimo cliente lido.
 **/
char *get_last_client(MAN_b b)
{
    return b->lastClient;
}

/**
 * \brief Calcula o numero de vendas de um dado client.
 **/
int get_client_n_vendas(MAN_b b, char *client)
{
    return get_client_v(b->clients, client);
}

/**
 * \brief Atribui a maior linha à gestão principal.
 **/
void set_maior_linha(MAN_b m, int l)
{
    m->maiorLinha = l;
}

int get_not_sold_client(MAN_b m)
{
    return get_not_sold_dbase(m->clients);
}

int get_not_sold_product(MAN_b m)
{
    return get_not_sold_dbase(m->products);
}

// DEBUG functions below and should not be included in a final version.
void show_number_sales(MAN_b mn)
{
    char c;
    for (c = 'A'; c <= 'Z'; c++)
        printf("%c:%d\n", c, get_n_clientes_alph(mn, c));
}

void show_boletim_vendas(MAN_b mn)
{
    printf("FIM DA LEITURA DO Vendas_1M.txt\n");
    printf("A maior linha tem tamanho %d\n", get_maior_linha(mn));
    printf("Produtos envolvidos: %d\n", get_n_produtos(mn));
    printf("Clientes envolvidos: %d\n", get_n_clientes_total(mn));
    printf("Vendas efectivas: %d\n", get_n_vendas_total(mn));
    printf("Ultimo cliente: %s\n", mn->lastClient);
    if (mn->lastClient[0] != '\0')
        printf("Numero de vendas regitadas para o cliente %s: %d\n", mn->lastClient, get_client_n_vendas(mn, mn->lastClient));
    printf("Numero de vendas registadas na filial 1: %d\n", get_n_vendas_filial(mn, 1));
    printf("Numero de vendas registadas na filial 2: %d\n", get_n_vendas_filial(mn, 2));
    printf("Numero de vendas registadas na filial 3: %d\n", get_n_vendas_filial(mn, 3));
    show_number_sales(mn);
    printf("Faturacao total: %f\n", get_cashflow_total(mn));

    puts("\nFASE 2 SPECS");
    printf("Numero de clientes que não efeturam compras:%d\n", get_not_sold_client(mn));
    printf("Numero de produtos que nao foram vendidos em:%d\n", get_not_sold_product(mn));
}