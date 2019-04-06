#include "CatProducts.h"
#include "CatClients.h"
#include "Verifier.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

CatClients build_catclients(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return NULL;

    char buffer[1024];
    CatClients cc = CatClients_make();
    Client tmp;

    while (fgets(buffer, 1024, fp))
    {
        tmp = verify_client(buffer);

        if (tmp)
        {
            CatClients_add_client(cc, tmp);
        }
    }

    fclose(fp);

    return cc;
}

CatProducts build_catproducts(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return NULL;

    char buffer[1024];
    CatProducts cp = CatProducts_make();
    Product tmp;

    while (fgets(buffer, 1024, fp))
    {
        tmp = verify_product(buffer);

        if (tmp)
        {
            CatProducts_add_product(cp, tmp);
        }
    }

    fclose(fp);

    return cp;
}

int main()
{
    CatProducts cp = build_catproducts("tests/Produtos.txt");

    CatProducts_destroy(cp);

    return 0;
}