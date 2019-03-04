#include "sale.h"
#include <glib.h>

// ------------------------------------------------------------------------------

APPENDER make_appender();
void update_appender(void *);
int get_app_vendas(APPENDER);
void destroy_appender(APPENDER);

// ------------------------------------------------------------------------------

typedef struct appendix
{
    int vendas, unitsSold; // Compras
    float totalRevenue;
} * APPENDER;

// ------------------------------------------------------------------------------

APPENDER make_appender()
{
    APPENDER a = g_malloc(sizeof(struct appendix));

    a->vendas = a->unitsSold = 0;
    a->totalRevenue = 0;

    return a;
}

void update_appender(APPENDER a, void *e)
{
    if (!e)
        return;
    SALE s = (SALE)e;
    a->vendas++;
    a->unitsSold += get_units_s(s);
    a->totalRevenue += (get_units_s(s) * get_price_s(s));
}

int get_app_vendas(APPENDER a)
{
    return a->vendas;
}

void destroy_appender(APPENDER a)
{
    if (a)
        g_free(a);
}