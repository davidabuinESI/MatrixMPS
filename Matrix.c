#include <stdio.h>
#include <OPMATRIX.h>
#include <IOMATRIX.h>

int main() {
	while(1) {
		int opt;

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
		}
	}
	
	return 0;
}
Matrix Substraction(Matrix A,Matrix B)
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
