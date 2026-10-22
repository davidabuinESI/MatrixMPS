#ifndef OPMATRIX_H
#define OPMATRIX_H

#include "IOMATRIX.h"   /* N, codigos de error y log */

/* Todas las operaciones calculan en una matriz temporal y copian el resultado
 * en R solo si no ha habido ningun error: si falla, R queda como estaba. */

//Precondicion: A y B son matrices 5x5 con datos enteros.
//Postcondicion: R = A + B
//Devuelve: OK, ERR_NULO o ERR_OP_DESBORDAMIENTO.
int op_sumar(int A[N][N], int B[N][N], int R[N][N])
{
    int tmp[N][N];

    if (A == NULL || B == NULL || R == NULL) {
        return ERR_NULO;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long long t = (long long)A[i][j] + B[i][j];
            if (t > INT_MAX || t < INT_MIN) {
                return ERR_OP_DESBORDAMIENTO;
            }
            tmp[i][j] = (int)t;
        }
    }
    memcpy(R, tmp, sizeof tmp);
    return OK;
}

//Precondicion: A y B son matrices 5x5 con datos enteros.
//Postcondicion: R = A - B
//Devuelve: OK, ERR_NULO o ERR_OP_DESBORDAMIENTO.
int op_restar(int A[N][N], int B[N][N], int R[N][N])
{
    int tmp[N][N];

    if (A == NULL || B == NULL || R == NULL) {
        return ERR_NULO;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long long d = (long long)A[i][j] - B[i][j];
            if (d > INT_MAX || d < INT_MIN) {
                return ERR_OP_DESBORDAMIENTO;
            }
            tmp[i][j] = (int)d;
        }
    }
    memcpy(R, tmp, sizeof tmp);
    return OK;
}

//Precondicion: k es un entero y A una matriz 5x5 con datos enteros.
//Postcondicion: R = k * A (producto de una matriz por un escalar)
//Devuelve: OK, ERR_NULO o ERR_OP_DESBORDAMIENTO.
int op_escalar(int k, int A[N][N], int R[N][N])
{
    int tmp[N][N];

    if (A == NULL || R == NULL) {
        return ERR_NULO;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long long p = (long long)A[i][j] * k;
            if (p > INT_MAX || p < INT_MIN) {
                return ERR_OP_DESBORDAMIENTO;
            }
            tmp[i][j] = (int)p;
        }
    }
    memcpy(R, tmp, sizeof tmp);
    return OK;
}

//Precondicion: A y B son matrices 5x5 con datos enteros.
//Postcondicion: R = A x B (producto de matrices)
//Devuelve: OK, ERR_NULO o ERR_OP_DESBORDAMIENTO.
int op_multiplicar(int A[N][N], int B[N][N], int R[N][N])
{
    int tmp[N][N];

    if (A == NULL || B == NULL || R == NULL) {
        return ERR_NULO;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            long long suma = 0;

            for (int k = 0; k < N; k++) {
                long long p = (long long)A[i][k] * B[k][j];
                /* comprobar que la suma acumulada no se sale de long long */
                if ((p > 0 && suma > LLONG_MAX - p) || (p < 0 && suma < LLONG_MIN - p)) {
                    return ERR_OP_DESBORDAMIENTO;
                }
                suma += p;
            }
            if (suma > INT_MAX || suma < INT_MIN) {
                return ERR_OP_DESBORDAMIENTO;
            }
            tmp[i][j] = (int)suma;
        }
    }
    memcpy(R, tmp, sizeof tmp);
    return OK;
}

//Precondicion: A es una matriz 5x5 con datos enteros.
//Postcondicion: comprueba si A es simetrica (A[i][j] == A[j][i] para todo i, j).
//Devuelve: 0 si A es simetrica y 1 si NO lo es. (Ojo: no es un codigo de error.)
int es_simetrica(int A[N][N])
{
    for (int i = 0; i < N; i++)
    {
        // Solo comprobamos el "triangulo" inferior de la matriz
        for (int j = 0; j < i; j++)
        {
            if (A[i][j] != A[j][i])
            {
                return 1; // Al primer fallo, detenemos y descartamos
            }
        }
    }
    return 0; // Si terminan los bucles sin errores, es simetrica
}

//Precondicion: codigo devuelto por una funcion de OPMATRIX.h.
//Postcondicion: informa al usuario del error y lo registra en el log.
//Los codigos que no son de operaciones se pasan a io_gestionar_error.
void op_gestionar_error(int codigo)
{
    switch (codigo) {
        case OK:
            return;
        case ERR_OP_DESBORDAMIENTO:
            io_informar_error("Desbordamiento: el resultado no cabe en un entero.", codigo);
            break;
        case ERR_OP_SIN_DATOS:
            io_informar_error("Faltan datos: carga las matrices necesarias o realiza una operacion antes.", codigo);
            break;
        default:
            io_gestionar_error(codigo);
            break;
    }
}

#endif