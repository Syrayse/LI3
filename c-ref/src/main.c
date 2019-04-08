/**
 * @file main.c
 * \brief Ficheiro contém o código que se pretende correr.
 */

#include "menu.h"

int main()
{
    Menu m = menu_make();

    menu_run(m);

    menu_destroy(m);

    return 0;
}
