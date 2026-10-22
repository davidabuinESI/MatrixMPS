typedef struct Matrix
{
    int m[5][5];
};#include <stdio.h>
//Precondición: 2 tipo Matrix A y B con valores enteros y rellenas.
//Postcondición: Devuelve la suma de las matrices A y B en la matriz R.
Matrix Addition(Matrix A,Matrix B)
{
    Matrix R;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R.m[i][j]=A.m[i][j]+B.m[i][j];
        }
    }
    return R;
}
//Precondición: 2 tipo Matrix A y B con valores enteros y rellenas.
//Postcondición: Devuelve la suma de las matrices A y B en la matriz R.
Matrix Substraction(Matrix A,Matrix B)
{
    int R[5][5];
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R.m[i][j]=A.m[i][j]-B.m[i][j];
        }
    }
    return R;
}