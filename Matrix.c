#include <stdio.h>

int main() {
	while(1) {
		int opt;

		printf("Choose a number from 1 to 5 in order to select operation you want to perform on matrices:\n");
		printf("[1] Adition\n");	
		printf("[2] Subtraction\n");	
		printf("[3] Multiplication (betwen matrices)\n");	
		printf("[4] Multiplication (betwen matrix and scalar)\n");
		printf("[5] Exit\n");
	
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
			case 4:
				// Multiplication scalar
				break;
			case 5:
				// exit
				return 0;
		}
	}
	
	return 0;
}
