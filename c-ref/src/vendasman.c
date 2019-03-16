/**
 * @file vendasman.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c VENDASMAN.
 * 
 * Este módulo representa o principal gestor do SVG, sendo que contém e aplica
 * toda a informação.
 **/
#include "validation.h"
#include "vendasman.h"
#include "mainstruct.h"
#include "util.h"
#include <glib.h>
#include <gmodule.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
MAN_b make_man(void);
void destroy_man(MAN_b);
void insert_client_man(MAN_b, char *);
void insert_product_man(MAN_b, char *);
int insert_sale_man(MAN_b, SALE);

int get_maior_linha(MAN_b);
int get_n_produtos(MAN_b);
int get_n_vendas_total(MAN_b);
int get_n_vendas_filial(MAN_b, int);
int get_n_clientes_total(MAN_b);
double get_cashflow_total(MAN_b);
char *get_last_client(MAN_b);
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
    DBase clients,         /**< Base de dados dos clientes */
        products;          /**< Base de dados dos produtos */
    char lastClient[7];    /**< Ultimo cliente lido */
    int maiorLinha,        /**< Maior linha lida */
        nVendasFiliais[3]; /**< Numero de vendas por filial */
    double totalCashFlow;  /**< Lucro total da empresa */
} * MAN_b;

// ------------------------------------------------------------------------------

/**
 * \brief Cria em memória uma estrutura de gestão principal.
 **/
MAN_b make_man(void)
{
    int i;
    MAN_b b = g_malloc(sizeof(struct manb));
    b->clients = dbase_make();
    b->products = dbase_make();
    b->lastClient[0] = '\0';
    b->maiorLinha = -1;
    for (i = 0; i < 3; i++)
        b->nVendasFiliais[i] = 0;
    b->totalCashFlow = 0.0;
    return b;
}

/**
 * \brief Liberta de memoria uma estrutura de gestão principal.
 **/
void destroy_man(MAN_b b)
{
    if (b)
    {
        dbase_destroy(b->clients);
        dbase_destroy(b->products);
        g_free(b);
    }
}

/**
 * \brief Insere uma dado cliente na respetiva base de dados.
 **/
void insert_client_man(MAN_b b, char *s)
{
    dbase_add(b->clients, s, NULL);
}

/**
 * \brief Insere uma dado produto na respetiva base de dados.
 **/
void insert_product_man(MAN_b b, char *s)
{
    dbase_add(b->products, s, NULL);
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

        b->totalCashFlow = b->totalCashFlow + get_rev_s(s);
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
    return dbase_size(b->products);
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
    return dbase_size(b->clients);
}

/**
 * \brief Calcula o numero total obtido.
 **/
double get_cashflow_total(MAN_b b)
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
 * \brief Atribui a maior linha à gestão principal.
 **/
void set_maior_linha(MAN_b m, int l)
{
    m->maiorLinha = l;
}

void show_boletim_vendas(MAN_b mn)
{
    char **tmp;
    size_t t = 0;
    printf("FIM DA LEITURA DO Vendas_1M.txt\n");
    printf("A maior linha tem tamanho %d\n", get_maior_linha(mn));
    printf("Produtos envolvidos: %d\n", get_n_produtos(mn));
    printf("Clientes envolvidos: %d\n", get_n_clientes_total(mn));
    printf("Vendas efectivas: %d\n", get_n_vendas_total(mn));
    printf("Ultimo cliente: %s\n", mn->lastClient);
    printf("Numero de vendas registadas na filial 1: %d\n", get_n_vendas_filial(mn, 1));
    printf("Numero de vendas registadas na filial 2: %d\n", get_n_vendas_filial(mn, 2));
    printf("Numero de vendas registadas na filial 3: %d\n", get_n_vendas_filial(mn, 3));

    printf("Faturacao total: %f\n", get_cashflow_total(mn));
    printf("Expected: 44765588910.5209\n");
    printf("Offset: %f\n", 44765588910.5209 - get_cashflow_total(mn));

    puts("\nFASE 2 SPECS");

    tmp = dbase_get_not_sold(mn->products, &t, 0);
    printf("|%ld|\n", t);
    g_free(tmp);

    tmp = dbase_get_not_sold(mn->products, &t, 1);
    printf("|%ld|\n", t);
    g_free(tmp);

    tmp = dbase_get_not_sold(mn->products, &t, 2);
    printf("|%ld|\n", t);
    g_free(tmp);

    tmp = dbase_get_not_sold(mn->products, &t, 3);
    printf("|%ld|\n", t);
    g_free(tmp);

    tmp = dbase_get_overall(mn->clients, &t, 0);
    g_free(tmp);

    printf("%ld clientes compraram em todas as filiais\n", t);
}