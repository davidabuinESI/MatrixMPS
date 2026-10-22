#ifndef OPMATRIX_H
#define OPMATRIX_H
#include <stdio.h>

#define N 5 /* orden de las matrices */


typedef struct
{
    int m[N][N];
} Matrix;


//Precondición: 2 tipo Matrix A y B con valores enteros y rellenas.
//Postcondición: Devuelve la suma de las matrices A y B en la matriz R.
// R = A + B
Matrix op_sumar(const Matrix A, const Matrix B);


//Precondición: 2 tipo Matrix A y B con valores enteros y rellenas.
//Postcondición: Devuelve la suma de las matrices A y B en la matriz R.
// R = A - B
Matrix op_restar(const Matrix A, const Matrix B);
#endif