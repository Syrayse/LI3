#include "vendasman.h"
#include "mainstruct.h"
#include <glib.c>

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

/* Metodos privados */

// ------------------------------------------------------------------------------

#define min(a, b) ((a) < (b) ? (a) : (b))

#define max(a, b) ((a) > (b) ? (a) : (b))

#define is_between(a, min, max) (((a) >= (min)) && ((a) <= (max)))

// ------------------------------------------------------------------------------

typedef struct manb
{
    MainStructB clients, products;
    SALE lastSale;
    int maiorLinha,
        nVendasFiliais[3],
        nClientesAlph['Z' - 'A' + 1];
    float totalCashFlow;
} * MAN_b;

MAN_b make_man(void)
{
    int i;
    MAN_b b = g_malloc(sizeof(struct manb));
    b->clients = make_msb();
    b->products = make_msb();
    b->lastSale = NULL;
    b->maiorLinha = -1;
    for (i = 0; i < 3; i++)
        b->nVendasFiliais[i] = 0;
    for (i = 0; i < 'Z' - 'A' + 1; i++)
        b->nClientesAlph[i] = 0;
    b->totalCashFlow = 0;
    return b;
}

void destroy_man(MAN_b b)
{
    if (b)
    {
        destroy_msb(b->clients);
        destroy_msb(b->products);
        g_free(b);
    }
}

int insert_client_man(MAN_b b, char *s)
{
    return insert_msb(b->clients, s, NULL);
}

int insert_product_man(MAN_b b, char *s)
{
    return insert_msb(b->products, s, NULL);
}

// Asumme que a sale é válida, retorna 1 se a venda for valida, 0 caso contrario.
int insert_sale_man(MAN_b b, SALE s)
{
    int r = validate_s(b->products, b->clients, s);

    if (r)
    {
        insert_self_s(b->products, b->clients, s);

        b->lastSale = s;

        b->nVendasFiliais[get_filial_s(s)]++;

        b->totalCashFlow += (get_units_s(s) * get_price_s(s));
    }

    return r;
}

int get_maior_linha(MAN_b b)
{
    return b->maiorLinha;
}

int get_n_produtos(MAN_b b)
{
    return get_size_msb(b->products);
}

int get_n_vendas_total(MAN_b b)
{
    int i, r = 0;
    for (i = 0; i < 3; i++)
        r += b->nVendasFiliais[i];
    return r;
}

int get_n_vendas_filial(MAN_b b, int filial)
{
    int r = -1;
    if (is_between(filial, 1, 3))
        r = b->nVendasFiliais[filial - 1];
    return r;
}

int get_n_clientes_total(MAN_b b)
{
    return get_size_msb(b->clients);
}

int get_n_clientes_alph(MAN_b b, char inicial)
{
    int r = -1;
    if (is_between(inicial, 'A', 'Z'))
        r = b->nClientesAlph[inicial - 'A'];
    return r;
}

float get_cashflow_total(MAN_b b)
{
    return b->totalCashFlow;
}

char *get_last_client(MAN_b b)
{
    char *r = NULL;
    if (b->lastSale)
        r = get_client_s(b->lastSale);
    return r;
}

int get_client_n_vendas(MAN_b b, char *client)
{
    return get_client_v(b, client);
}
