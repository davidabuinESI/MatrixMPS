#ifndef OPMATRIX_H
#define OPMATRIX_H
#include <stdio.h>
typedef struct Matrix
{
    int m[5][5];
};
//Precondición: 2 tipo Matrix A y B con valores enteros y rellenas.
//Postcondición: Devuelve la suma de las matrices A y B en la matriz R.
Matrix Addition(Matrix A,Matrix B);
//Precondición: 2 tipo Matrix A y B con valores enteros y rellenas.
//Postcondición: Devuelve la suma de las matrices A y B en la matriz R.
Matrix Substraction(Matrix A,Matrix B);
#endif