#include <stdio.h>
#include "OPMATRIX.h"
#include "IOMATRIX.h"

void mainMenu(int *opt) {
	printf("Choose a number from 1 to 4 in order to select operation you want to perform on matrices:\n");
	printf("[1] Addition\n");	
	printf("[2] Subtraction\n");	
	printf("[3] Multiplication (between matrices)\n");	
	//printf("[4] Multiplication (between matrix and scalar)\n");
	printf("[4] Exit\n");
	
	printf("Choose a number: " );	
	scanf("%d", opt);
}

int main() {
	while(1) {
		int opt;
			
		mainMenu(&opt);
		
		switch(opt) {
			case 1:
				// Adition
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
