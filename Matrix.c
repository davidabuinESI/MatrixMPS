#include <stdio.h>
#include "OPMATRIX.h"
#include "IOMATRIX.h"
#include <limits.h>
void rellenarMatriz(Matrix M);
void Show_matrix(Matrix M);
int main() {
	while(1) {
		int opt;
        Matrix A,B,R;
        rellenarMatriz(A);
        rellenarMatriz(B);
		printf("Choose a number from 1 to 5 in order to select operation you want to perform on matrices:\n");
		printf("[1] Adition\n");	
		printf("[2] Subtraction\n");	
		printf("[3] Multiplication (betwen matrices)\n");	
		//printf("[4] Multiplication (betwen matrix and scalar)\n");
		printf("[4] Exit\n");
	
		printf("Choose a number: " );	
		scanf("%d", &opt);

		switch(opt) {
			case 1:
				R=op_sumar(A,B);
                Show_matrix(R);
				break;
			case 2:
				// Subtraction
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
    Matrix R;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R[i][j]=A[i][j]-B[i][j];
            if ((B[i][j]> 0) && (A[i][j] > INT_MAX - B[i][j])) 
            {
                return 10; // Error: Overflow hacia positivo
            }
        }
    }
    return 0;
}


int op_sumar(const int A[][5], const int B[][5],int R[][5])
{
    Matrix R;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R[i][j]=A[i][j]+B[i][j];
            if ((B[i][j]> 0) && (A[i][j] > INT_MAX - B[i][j])) 
            {
                return 10; // Error: Overflow hacia positivo
            }
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
void rellenarMatriz(Matrix M) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            M.m[i][j]=i+j;
        }
    }
}
void Show_matrix(Matrix M)
{
    for (int i=0;i<5;i++)
    {
        for(int j=0;j<5;i++)
        {
            printf("[%d]",&M.m[i][j]);
        }
    }
}