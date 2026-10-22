#include <stdio.h>
#include "OPMATRIX.h"
#include "IOMATRIX.h"
#include <limits.h>
int main() {
	int A[N][N], B[N][N], R[N][N];
	int cod;
	if (!io_cargar_matrices(A, B)) {
		return 1;
	}
	while(1) {
		int opt;
		printf("Choose a number from 1 to 5 in order to select operation you want to perform on matrices:\n");
		printf("[1] Adition\n");	
		printf("[2] Subtraction\n");	
		printf("[3] Multiplication scalar\n");	
		//printf("[4] Multiplication (betwen matrix and scalar)\n");
		printf("[4] Multiplication Matrix\n");
		printf("[5] Exit\n");
	
		printf("Choose a number: " );	
		scanf("%d", &opt);

		switch(opt) {
			case 1:
				cod = op_sumar(A,B,R);
				if (cod == 0) Show_matrix(R); else printf("Error %d: desbordamiento\n", cod);
				break;
			case 2:
				cod = op_restar(A,B,R);
				if (cod == 0) Show_matrix(R); else printf("Error %d: desbordamiento\n", cod);
				break;
			case 3:
				// Multiplication matrix
				break;
			/*case 4:
				// Multiplication scalar
				break;*/
			case 4:
				// exit
				return 0;
			default:
				printf("\nTry again!\n\n");
				break;
		}
	}
	
	return 0;
}


int op_restar(const int A[][N], const int B[][N],int R[][N])
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            long long d = (long long)A[i][j] - B[i][j];
            if (d > INT_MAX || d < INT_MIN) return 10; // Error: Overflow
            R[i][j] = (int)d;
        }
    }
    return 0;
}


int op_sumar(const int A[][N], const int B[][N],int R[][N])
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            long long t = (long long)A[i][j] + B[i][j];
            if (t > INT_MAX || t < INT_MIN) return 10; // Error: Overflow
            R[i][j] = (int)t;
        }
    }
    return 0;
}
int op_escalar(int k, const int A[][N], int R[][N])
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            int a = A[i][j];
            
            // 1. Comprobar desbordamientos ANTES de multiplicar
            if (a > 0 && k > 0 && a > INT_MAX / k) return 10; // Overflow positivo
            if (a > 0 && k < 0 && k < INT_MIN / a) return 10; // Underflow negativo
            if (a < 0 && k > 0 && a < INT_MIN / k) return 10; // Underflow negativo
            if (a < 0 && k < 0 && a < INT_MAX / k) return 10; // Overflow positivo (menos por menos)

            // 2. Operar de forma segura
            R[i][j] = a * k;
        }
    }
    return 0;
}
int op_multiplicar (const int A[][N], const int B[][N],int R[][N])
{
	for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            R[i][j] = 0;
            
            for (int k = 0; k < N; k++)
            {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
int es_simetrica (const int A[N][N])
{
    for (int i = 0; i < N; i++)
    {
        // Solo comprobamos el "triángulo" inferior de la matriz
        for (int j = 0; j < i; j++)
        {
            if (A[i][j] != A[j][i])
            {
                return 1; // Al primer fallo, detenemos y descartamos
            }
        }
    }
    return 0; // Si terminan los bucles sin errores, es simétrica
}