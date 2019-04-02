/**
 * @file Appender.c
 * \brief Define a classe `Appender` que deve ser anexada a produtos presentes numa instância da classe `Accounting`. 
 * 
 * Da forma como se encontra definida esta classe, é especificamente direcionada para a aplicação
 * em uma instância da classe `StrSet`. Sendo que fora desse contexto não possui muito valor lógico.
 * 
 * Tal como requerido pela classe `StrSet` esta função comtempla todos os metódos necessários para
 * criar, destruir e atualizar a informação que se pretende indexar a cada produto na contabilidade.
 */

#include "Appender.h"
#include "Verifier.h"
#include "gArray.h"
#include <glib.h>

/* ------------------------------------------------------------------------------ */

/* Metódos públicos */
void *Appender_make();
void Appender_destroy(void *app);
void Appender_update(void *app, void *user_data);
void Appender_iterate_overall(Appender app, void (*f_iter)(Transaction, void *), void *user_data);
void Appender_iterate_filial(Appender app, int filial, void (*f_iter)(Transaction, void *), void *user_data);

/* Metódos privados */
static void enclosed_iterator_filial(Appender app, int filial, void (*f_iter)(Transaction, void *), void *user_data);

/* ------------------------------------------------------------------------------ */

/**
 * \brief Definição da estrutura da classe `Appender`.
 * 
 * Esta classe, adaptada a responder a queries pedidas é repartida
 * em `N_FILIAIS` elementos do tipo `GrowingArray`, sendo que nesta concretização 
 * de array serão adicionados elementos do tipo `Transaction`. 
 * 
 * @see N_FILIAIS
 * @see GrowingArray
 * @see Transaction
 */
typedef struct appender
{
    GrowingArray regist[N_FILIAIS]; /**< Array de `GrowingArray`s que devem conter `Transaction`s. */
} * Appender;

/* ------------------------------------------------------------------------------ */

/**
 * \brief Criar uma instância da classe `Appender`.
 * 
 * Para além de criar em memória esta nova instância, também inicializa todos os valores por esta necessários.
 * 
 * @returns Uma nova instância.
 */
void *Appender_make()
{
    int i;
    Appender app = g_malloc(sizeof(struct appender));

    for (i = 0; i < N_FILIAIS; i++)
    {
        app->regist[i] = garray_make(sizeof(Transaction), trans_destroy);
    }

    return app;
}

/**
 * \brief Destrói uma instância da classe `Appender`.
 * 
 * Para além de destruir a instância em questão, também liberta
 * toda a memória associada a esta, bem como todas as instâncias da classe
 * `Transaction` que nela foram inseridas.
 * 
 * @param app Instância a destruir.
 */
void Appender_destroy(void *app)
{
    int i;

    if (app)
    {
        Appender a = (Appender)app;

        for (i = 0; i < N_FILIAIS; i++)
        {
            garray_destroy(a->regist[i]);
        }
    }
}
/**
 * \brief Atualização a informação da instância.
 * 
 * A atualização de uma instância desta classe funciona através da
 * passagem de uma instância da classe `Transaction` como argumento.
 * Esta instância é armazenada no destinatário mais adequado, segundo a filial.
 * 
 * @param app Instância a considerar.
 * @param user_data `Transaction` utilizada para atualizar a informação.
 */
void Appender_update(void *app, void *user_data)
{
    Transaction t = (Transaction)user_data;
    garray_add(((Appender)app)->regist[trans_get_filial(t) - 1], user_data);
}

/**
 * \brief Permite iterar uma dada função sobre todas as vendas associadas à instância.
 * 
 * Para que este método seja efetuada de forma regular os paramêtros passados
 * devem todos ser válidos, caso contrário não é feito nenhum tipo de iteração.
 * 
 * @param app Instância a considerar.
 * @param f_iter Função que iterar sobre as transações.
 * @param user_data Informação adicional, útil à função de iteração.
 */
void Appender_iterate_overall(Appender app, void (*f_iter)(Transaction, void *), void *user_data)
{
    if (!app || !f_iter || !user_data)
        return;

    int i;

    for (i = 1; i <= N_FILIAIS; i++)
    {
        enclosed_iterator_filial(app, i, f_iter, user_data);
    }
}

/**
 * \brief Permite iterar uma dada função sobre as vendas de uma certa filial associadas à instância.
 * 
 * Para que este método seja efetuada de forma regular os paramêtros passados
 * devem todos ser válidos, caso contrário não é feito nenhum tipo de iteração.
 * 
 * @param app Instância a considerar.
 * @param filial Filial na qual se pretende iterar.
 * @param f_iter Função que iterar sobre as transações.
 * @param user_data Informação adicional, útil à função de iteração.
 */
void Appender_iterate_filial(Appender app, int filial, void (*f_iter)(Transaction, void *), void *user_data)
{
    if (is_between(filial, 1, N_FILIAIS) && f_iter && user_data)
    {
        enclosed_iterator_filial(app, filial, f_iter, user_data);
    }
}

/**
 * \brief Permite iterar uma dada função sobre as vendas de uma certa filial associadas à instância.
 * 
 * Esta função difere do metódo `Appender_iterate_filial`, pois esta versão assume que todos
 * os argumentos passados no metódo são válidos.
 * 
 * @param app Instância a considerar.
 * @param filial Filial na qual se pretende iterar.
 * @param f_iter Função que iterar sobre as transações.
 * @param user_data Informação adicional, útil à função de iteração.
 */
static void enclosed_iterator_filial(Appender app, int filial, void (*f_iter)(Transaction, void *), void *user_data)
{
    int i, s;

    GrowingArray g = app->regist[filial - 1];

    s = garray_size(g);

    for (i = 0; i < s; i++)
    {
        (*f_iter)(garray_get_index(g, i), user_data);
    }
}