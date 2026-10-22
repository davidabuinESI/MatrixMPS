#include <stdio.h>
#include "OPMATRIX.h"
#include "IOMATRIX.h"
#include <limits.h>

void mainMenu(int *opt) {
	printf("Choose a number from 1 to 4 in order to select operation you want to perform on matrices:\n");
	printf("[1] Adition\n");	
	printf("[2] Subtraction\n");	
	printf("[3] Multiplication (betwen matrices)\n");	
	//printf("[4] Multiplication (betwen matrix and scalar)\n");
	printf("[4] Exit\n");

	printf("Choose a number: " );	
	scanf("%d", opt);
}

int main() {
	int A[N][N], B[N][N], R[N][N];
	int cod;
	if (!io_cargar_matrices(A, B)) {
		return 1;
	}
	while(1) {
		int opt;
	
		mainMenu(&opt);	

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


int op_restar(const int A[][5], const int B[][5],int R[][5])
{
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            long long d = (long long)A[i][j] - B[i][j];
            if (d > INT_MAX || d < INT_MIN) return 10; // Error: Overflow
            R[i][j] = (int)d;
        }
    }
    return 0;
}


int op_sumar(const int A[][5], const int B[][5],int R[][5])
{
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            long long t = (long long)A[i][j] + B[i][j];
            if (t > INT_MAX || t < INT_MIN) return 10; // Error: Overflow
            R[i][j] = (int)t;
        }
    }
    return 0;
}
int op_escalar(int k, const int A[][5], int R[][5])
{
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            
            R[i][j]=A[i][j]*k;
            if (k > 0 && A[i][j] > INT_MAX / j) return 10;
            if (k < 0 && k < INT_MIN / k) return 10;
            else
            if (k > 0 && A[i][j] < INT_MIN / k) return 10;
            if (k < 0 && ( A[i][j]!= 0 && k < INT_MAX / A[i][j])) return 10;
        }
        
    }
    return 0;
    
}
