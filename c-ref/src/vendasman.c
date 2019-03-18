/**
 * @file vendasman.c 
 * \brief Ficheiro contendo o código relativo ao módulo @c VENDASMAN.
 * 
 * Este módulo representa o principal gestor do SVG, sendo que contém e aplica
 * toda a informação.
 **/
#include "validation.h"
#include "vendasman.h"
#include "dbase.h"
#include "util.h"
#include <glib.h>
#include <stdio.h>

// ------------------------------------------------------------------------------

/* Metodos publicos */
MAN_b make_man(void);
void destroy_man(MAN_b);
void insert_client_man(MAN_b, char *);
void insert_product_man(MAN_b, char *);
int insert_sale_man(MAN_b, Sale);

int get_maior_linha(MAN_b);
int get_n_produtos(MAN_b);
int get_n_vendas_total(MAN_b);
int get_n_vendas_filial(MAN_b, int);
int get_n_vendas_month(MAN_b, int);
double get_n_faturacao_month(MAN_b, int);
int get_n_clientes_total(MAN_b);
double get_cashflow_total(MAN_b);
char *get_last_client(MAN_b);
int get_not_sold_client(MAN_b);
int get_not_sold_product(MAN_b);

int get_n_vendas_range(MAN_b, int, int);
double get_n_faturacao_range(MAN_b, int, int);

void set_maior_linha(MAN_b, int);

void show_boletim_vendas(MAN_b mn);

/* Metodos privados */

// ------------------------------------------------------------------------------

/**
 * \brief Estrutura de dados que encapsula a gestão principal.
 **/
typedef struct manb
{
    DBase clients,                     /**< Base de dados dos clientes */
        products;                      /**< Base de dados dos produtos */
    char lastClient[7];                /**< Ultimo cliente lido */
    int maiorLinha,                    /**< Maior linha lida */
        nVendasFiliais[N_FILIAIS];     /**< Numero de vendas por filial */
    double totalCashFlow;              /**< Lucro total da empresa */
    int nVendasMes[N_MONTHS + 1];      /**< Numero de vendas por cada mes, sendo o índice N_MONTHS para o total, aka, vendas anuais */
    double faturacaoMes[N_MONTHS + 1]; /**< faturação mensal, sendo o índice N_MONTHS para o total, aka, faturação anual */
} * MAN_b;

// ------------------------------------------------------------------------------

/**
 * \brief Cria em memória uma estrutura de gestão principal.
 **/
MAN_b make_man(void)
{
    int i;
    MAN_b b = g_malloc(sizeof(struct manb));
    b->clients = dbase_make(1);
    b->products = dbase_make(0);
    b->lastClient[0] = '\0';
    b->maiorLinha = -1;
    for (i = 0; i < N_FILIAIS; i++)
        b->nVendasFiliais[i] = 0;
    for (i = 0; i < N_MONTHS + 1; i++)
    {                             //
        b->nVendasMes[i] = 0;     //
        b->faturacaoMes[i] = 0.0; //
    }                             //
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
int insert_sale_man(MAN_b b, Sale s)
{
    double cf;
    int month;
    int r = validate_s(b->products, b->clients, s);

    if (r)
    {
        sale_insert_self(b->products, b->clients, s);

        sale_copy_client(s, b->lastClient);

        month = sale_get_month(s) - 1;

        cf = sale_get_rev(s);

        b->nVendasMes[month]++;

        b->nVendasMes[N_MONTHS]++;

        b->faturacaoMes[month] += cf;

        b->faturacaoMes[N_MONTHS] += cf;

        b->nVendasFiliais[sale_get_filial(s) - 1]++;

        b->totalCashFlow += cf;
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
    for (i = 0; i < N_FILIAIS; i++)
        r += b->nVendasFiliais[i];
    return r;
}

/**
 * \brief Calcula o numero de vendas por filial.
 **/
int get_n_vendas_filial(MAN_b b, int filial)
{
    int r = -1;
    if (is_between(filial, 1, N_FILIAIS))
        r = b->nVendasFiliais[filial - 1];
    return r;
}

/**
 * \brief Calcula o numero de vendas por mês.
 **/
int get_n_vendas_month(MAN_b b, int mes)
{
    int r = -1;
    if (is_between(mes, 1, N_MONTHS + 1))
        r = b->nVendasMes[mes - 1];
    return r;
}

/**
 * \brief Calcula a faturação de um certo mês.
 **/
double get_n_faturacao_month(MAN_b b, int mes)
{
    double r = -1;
    if (is_between(mes, 1, N_MONTHS + 1))
        r = b->faturacaoMes[mes - 1];
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

/**
 * \brief Calcula o número de vendas durante um certo período.
 **/
int get_n_vendas_range(MAN_b b, int mInicio, int mFinal)
{
    int r = -1;
    int month;

    if (is_between(mInicio, 1, N_MONTHS) && is_between(mFinal, 1, N_MONTHS) && mInicio <= mFinal)
    {
        r = 0;
        for (month = mInicio; month < mFinal + 1; month++)
            r += b->nVendasMes[month - 1];
    }
    return r;
}

/**
 * \brief Calcula a faturação durante um certo período.
 **/
double get_n_faturacao_range(MAN_b b, int mInicio, int mFinal)
{
    double r = -1;
    int month;

    if (is_between(mInicio, 1, N_MONTHS) && is_between(mFinal, 1, N_MONTHS) && mInicio <= mFinal)
    {
        r = 0.0;
        for (month = mInicio; month < mFinal + 1; month++)
            r += b->faturacaoMes[month - 1];
    }
    return r;
}

void show_boletim_vendas(MAN_b mn)
{
    size_t t = 0;
    printf("FIM DA LEITURA DO Vendas_1M.txt\n");
    printf("A maior linha tem tamanho %d\n", get_maior_linha(mn));
    printf("Produtos envolvidos: %d\n", get_n_produtos(mn));
    printf("Clientes envolvidos: %d\n", get_n_clientes_total(mn));
    printf("Vendas efectivas: %d\n", get_n_vendas_total(mn)); //get_n_vendas_month(mn, 13);
    printf("Ultimo cliente: %s\n", mn->lastClient);
    printf("Numero de vendas registadas na filial 1: %d\n", get_n_vendas_filial(mn, 1));
    printf("Numero de vendas registadas na filial 2: %d\n", get_n_vendas_filial(mn, 2));
    printf("Numero de vendas registadas na filial 3: %d\n", get_n_vendas_filial(mn, 3));

    printf("\nFaturacao total: %f\n\n", get_cashflow_total(mn)); //get_n_faturacao_month(mn, 13)
    printf("Expected: 44765588910.5209\n");
    printf("Offset: %f\n", 44765588910.5209 - get_cashflow_total(mn));

    puts("\nFASE 2 SPECS");

    printf("%ld clientes compraram em todas as filiais\n", t);

    printf("Vendas entre Janeiro e Março: %d\n", get_n_vendas_range(mn, 1, 12));
    printf("Faturação entre Janeiro e Dezembro: %f\n", get_n_faturacao_month(mn, 13));
    printf("Faturação entre Janeiro e Dezembro in range: %f\n", get_n_faturacao_range(mn, 1, 12));
    printf("Vendas entre Janeiro e dezembro: %d\n", get_n_vendas_month(mn, 13));
    printf("Vendas entre Janeiro e dezembro in range: %d\n", get_n_vendas_range(mn, 1, 12));
    printf("Offset: %f\n", 44765588910.5209 - get_n_faturacao_range(mn, 1, 12));
}