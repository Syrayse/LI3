#ifndef UTIL_H
#define UTIL_H

/**
 * \brief Indexador dos códigos promocionais.
 **/
#define indP(a) ((a) == ('N') ? 0 : 1)

/**
 * \brief Número de meses em um ano.
 **/
#define N_MONTHS 12

/**
 * \brief Número de filiais no sistema.
 **/
#define N_FILIAIS 3

/**
 * \brief Número de códigos promocionais no sistema.
 **/
#define N_PROMOS 2

/**
 * \brief Verifica se x se encontra entre dois limites.
 **/
#define is_between(x, min, max) ((x >= min) && (x <= max))

/**
 * \brief Mínimo entre dois números.
 **/
#define min(a, b) ((a) < (b) ? (a) : (b))

/**
 * \brief Maximo entre dois números.
 **/
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef void (*freefunc)(void *);

typedef int (*fcompare)(const void *, const void *);

typedef int (*Predicate)(const void *);

int mystrcmp(const void *, const void *);

int conv_str(const void *);

#endif