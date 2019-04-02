/**
 * @file NavControl.c
 * \brief Módulo associado à classe `NavControl` que possibilita a interação dinâmica com um dicionário escolhido.
 *
 * Esta classe tem a capacidade de, associada com uma outra que lhe forneça dicionários, fazer um comunicação
 * mais user-friendly com o cliente do serviço SGV.
 */
#include "NavControl.h"
#include <glib.h>
#include <stdio.h>

/* ------------------------------------------------------------------------------ */

/* Metodos publicos */
NavControl NavControl_make();
void NavControl_destroy(NavControl nc);
void NavControl_change_dict(NavControl nc, void **dict, void *user_data, int size, f_print fp_elem, f_print fp_user);
int NavControl_next_page(NavControl nc);
int NavControl_previous_page(NavControl nc);
void NavControl_show(NavControl nc);

/* Metodos privados */
static void show_header(NavControl nc);
static void show_footer(NavControl nc);

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura que permite a visualização dinâmica de um dicionário.
 * 
 * Através desta estrutura é possivél atacar um sub-problema do sistema I/O a ser implementado.
 */
typedef struct nav_control
{
    int nPerPage,      /**< Numero de elementos por página a serem apresentados. */
        page,          /**< Indice da página corresponte do dicionário, começa em 1. */
        init,          /**< Indice do primeiro elemento do dicionário a ser apresentado na página corrente. */
        end,           /**< Indice do ultimo elemento do dicionário a ser apresentado na página corrente. */
        size;          /**< Número total de elementos no dicionário. */
    void **dictionary, /**< Dicionário corrente. */
        *user_data;    /**< Informação útil sobre o dicionário. */
    f_print fp_elem,   /**< Função de impressão a ser aplicada a cada elemento do dicionário. */
        fp_user;       /**< Função de impressão a ser aplicada à informação passada pelo usuário. */
} * NavControl;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Número de elementos predifinido por página.
 */
#define N_PER_PAGE 25

/**
 * \brief Separador utilizado no design de interface gráfico atual.
 */
#define SEPARATOR "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"

/**
 * \brief Máximo entre dois números.
 */
#define max(a, b) ((a) > (b) ? (a) : (b))
/* ------------------------------------------------------------------------------ */

/**
 * \brief Cria uma instância da classe `NavControl`.
 * 
 * @returns Uma nova instância da classe `NavControl`.
 */
NavControl NavControl_make()
{
    NavControl nc = g_malloc(sizeof(struct nav_control));

    nc->nPerPage = N_PER_PAGE;

    nc->page = nc->init = nc->end = nc->size = -1;

    nc->dictionary = nc->user_data = NULL;

    nc->fp_elem = nc->fp_user = NULL;

    return nc;
}

/**
 * \brief Destrói uma instância da classe `NavControl`.
 * 
 * @param nc Instância a ser destruída. 
 */
void NavControl_destroy(NavControl nc)
{
    if (nc)
    {
        g_free(nc);
    }
}

/**
 * \brief Altera o dicionário em vigor no `NavControl`.
 * 
 * Permite alterar o dicionário que se pretend verificar através do `NavControl`.
 * Se um dicionário já estiver em vigor este é discartado.
 * 
 * Para além disso, é passada um função de impressão que permite ao utilizador
 * deste metódo escolher como permite imprimir cada elemento.
 * 
 * @param nc Instância a ser considerada.
 * @param dict Novo dicionário a ser colocado.
 * @param user_data Informação pertinente ao conteúdo do dicionário.
 * @param size Tamanho do novo dicionário.
 * @param fp_elem Função de impessão do novo dicionário, a ser aplicada a cada elemento deste. 
 * @param fp_user Função de impressão de informação pertinente ao conteúdo do dicionário.
 */
void NavControl_change_dict(NavControl nc, void **dict, void *user_data, int size, f_print fp_elem, f_print fp_user)
{
    if (!nc || size <= 0)
        return;

    nc->dictionary = dict;

    nc->user_data = user_data;

    nc->size = size;

    nc->page = 1;

    nc->fp_elem = fp_elem;

    nc->fp_user = fp_user;

    nc->init = 0;

    nc->end = max(size, nc->nPerPage);
}

/**
 * \brief Permite passar para a próxima página de elementos que se pretende visualizar.
 * 
 * Dependendo da váriavel de instância de `NavControl`, `nPerPage`, são alterados os parametros
 * `init` e `end` de forma a tentar simular o que seria o passar de uma página.
 * 
 * @returns 1 se foi possivél avançar para a próxima página, 0 caso contrário.
 */
int NavControl_next_page(NavControl nc)
{
    int r = 0;

    if (nc && nc->dictionary && nc->end < nc->size)
    {
        r = 1;

        nc->page++;

        nc->init = nc->end;

        nc->end += nc->nPerPage;

        if (nc->end > nc->size)
        {
            nc->end -= (nc->end - nc->size);
        }
    }

    return r;
}

/**
 * \brief Permite retroceder para a página anterior de elementos que se pretende visualizar.
 * 
 * Dependendo da váriavel de instância de `NavControl`, `nPerPage`, são alterados os parametros
 * `init` e `end` de forma a tentar simular o que seria retroceder uma página.
 * 
 * @returns 1 se foi possivél retroceder para a página anterior, 0 caso contrário.
 */
int NavControl_previous_page(NavControl nc)
{
    int r = 0;

    if (nc && nc->dictionary && nc->init > 0)
    {
        r = 1;

        nc->page--;

        nc->end = nc->init;

        nc->init -= nc->nPerPage;

        if (nc->init < 0)
        {
            nc->init = 0;
        }
    }

    return r;
}

/**
 * \brief Imprime no ecra o correspondente a uma página.
 * 
 * A formatação desta página possui, um _header_ com informação útil à
 * página corrente, os elementos da página, segundo a aplicação da função
 * `f_print` e para além disso um rodapé também com informação útil.
 * 
 * @param nc Instância a considerar.
 */
void NavControl_show(NavControl nc)
{
    if (!nc || !nc->fp_elem)
        return;

    int i;

    show_header(nc);

    for (i = nc->init; i < nc->end; i++)
    {
        (*nc->fp_elem)(nc->dictionary[i]);
    }

    show_footer(nc);
}

/**
 * \brief Imprime um _header_ adequado para a apresentação da página da instância.
 * 
 * @param nc Instância a considerar.
 */
static void show_header(NavControl nc)
{
    if (nc->user_data && nc->fp_user)
    {
        printf("Showing info about:\n");
        (*nc->fp_user)(nc->user_data);
    }

    printf(SEPARATOR);
}

/**
 * \brief imprime um rodapé adequado para a representação da página da instância.
 * 
 * @param nc Instância a considerar.
 */
static void show_footer(NavControl nc)
{
    printf(SEPARATOR);

    printf("Showing results from %d to %d.\t\t\t\tCurrent page:%d\n", nc->init, nc->end - 1, nc->page);

    printf(SEPARATOR);
}