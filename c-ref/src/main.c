/**
 * @file main.c
 * \brief Ficheiro contém o código que se pretende correr.
 */

#include "menuXPTO.h"

int main()
{
    MenuXPTO mx = menu_make();

    menu_run(mx);

    menu_destroy(mx);

    return 0;
}
