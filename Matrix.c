#include <stdio.h>
#include "OPMATRIX.h"
#include "IOMATRIX.h"

int main() {
	while(1) {
		int opt;
        Matrix A,B,R;
        Rellena_matriz(A);
        Rellena_matriz(B);
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
				R=Addition(A,B);
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
		}
	}
	
	return 0;
}


Matrix op_restar( const Matrix A, const Matrix B)
{
    Matrix R;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            R.m[i][j]=A.m[i][j]-B.m[i][j];
        }
    }
    return R;
}


Matrix op_sumar(const Matrix A, const Matrix B)
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
void rellenarMatriz(Matrix M) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            M.m[i][j]=i+j;
        }
    }
}
void Show_matrix(Matrix M)
{
    for (int i;i<5;i++)
    {
        for(int j;j<5;i++)
        {
            printf("[%d]",M.m[i][j]);
        }
    }
}