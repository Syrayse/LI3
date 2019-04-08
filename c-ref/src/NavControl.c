/**
 * @file NavControl.c
 * \brief Módulo associado à classe `NavControl` que possibilita a interação dinâmica com um dicionário escolhido.
 *
 * Esta classe tem a capacidade de, associada com uma outra que lhe forneça dicionários, fazer uma comunicação
 * mais user-friendly com o cliente do serviço SGV.
 */
#include "NavControl.h"
#include "TAD_List.h"
#include "stdio.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/**
 * \brief Estrutura que permite a visualização dinâmica de um dicionário.
 * 
 * Através desta estrutura é possível atacar um sub-problema do sistema I/O a ser implementado.
 */
typedef struct nav_control
{
    int nPerPage,        /**< Número de elementos por página a serem apresentados. */
        page,            /**< Índice da página corresponte do dicionário, começa em 1. */
        init,            /**< Índice do primeiro elemento do dicionário a ser apresentado na página corrente. */
        end,             /**< Índice do último elemento do dicionário a ser apresentado na página corrente. */
        size;            /**< Número total de elementos no dicionário. */
    TAD_List dictionary; /**< Dicionário corrente. */
    gpointer user_data;  /**< Informação útil sobre o dicionário. */
    f_print fp_elem,     /**< Função de impressão a ser aplicada a cada elemento do dicionário. */
        fp_user;         /**< Função de impressão a ser aplicada à informação passada pelo usuário. */
} * NavControl;

/* ------------------------------------------------------------------------------ */

/* Métodos públicos */
NavControl NavControl_make();
void NavControl_destroy(NavControl nc);
void NavControl_change_dict(NavControl nc, TAD_List tl, gpointer user_data, f_print fp_elem, f_print fp_user);
int NavControl_next_page(NavControl nc);
int NavControl_previous_page(NavControl nc);
void NavControl_show(NavControl nc);
int NavControl_get_init(NavControl nc);
int NavControl_get_end(NavControl nc);
int NavControl_get_page(NavControl nc);

/* Métodos privados */

/* ------------------------------------------------------------------------------ */

/**
 * \brief Número de elementos predifinido por página.
 */
#define N_PER_PAGE 25

/**
 * \brief Máximo entre dois números.
 */
#define max(a, b) ((a) > (b) ? (a) : (b))

/* ------------------------------------------------------------------------------ */

NavControl NavControl_make()
{
    NavControl nc = g_malloc(sizeof(struct nav_control));

    nc->nPerPage = N_PER_PAGE;

    nc->page = nc->init = nc->end = nc->size = -1;

    nc->dictionary = nc->user_data = NULL;

    nc->fp_elem = nc->fp_user = NULL;

    return nc;
}

void NavControl_destroy(NavControl nc)
{
    if (nc)
    {
        g_free(nc);
    }
}

void NavControl_change_dict(NavControl nc, TAD_List dict, gpointer user_data, f_print fp_elem, f_print fp_user)
{
    nc->dictionary = dict;

    nc->user_data = user_data;

    nc->size = list_size(dict);

    nc->page = 1;

    nc->fp_elem = fp_elem;

    nc->fp_user = fp_user;

    nc->init = 0;

    nc->end = max(nc->size, nc->nPerPage);
}

int NavControl_next_page(NavControl nc)
{
    int r = 0;

    if (nc && nc->dictionary)
    {
        r = 1;

        if (nc->end > nc->size)
        {
            nc->page = 1;

            nc->init = 0;

            nc->end = nc->nPerPage;
        }

        else
        {
            nc->page++;

            nc->init = nc->end;

            nc->end += nc->nPerPage;
        }
    }

    return r;
}

int NavControl_previous_page(NavControl nc)
{
    int r = 0;

    if (nc && nc->dictionary)
    {
        r = 1;

        if (nc->init < nc->nPerPage)
        {
            nc->page = (nc->size / nc->nPerPage + 1);

            nc->end = nc->page * nc->nPerPage;

            nc->init = nc->end - nc->nPerPage;
        }

        else
        {
            nc->page--;

            nc->end = nc->init;

            nc->init -= nc->nPerPage;
        }
    }

    return r;
}

void NavControl_show(NavControl nc)
{
    if (!nc->fp_elem)
        return;

    int i;

    for (i = nc->init; i < nc->end; i++)
    {
        printf("%d: ", i);
        (*nc->fp_elem)(list_get_index(nc->dictionary, i));
    }
}

int NavControl_get_init(NavControl nc)
{
    return nc->init;
}

int NavControl_get_end(NavControl nc)
{
    return nc->end - 1;
}

int NavControl_get_page(NavControl nc)
{
    return nc->page;
}