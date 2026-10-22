#ifndef IOMATRIX_H
#define IOMATRIX_H
#include <stdio.h>
#include "OPMATRIX.h"

//Precondición: Recibe una matriz vacía y un fichero de texto
//Postcondición: Rellena la matriz con la matriz correspondiente del fichero de texto
int io_cargar_matriz(FILE *f, int M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(f, "%d", &M[i][j]) != 1) {
                return 0;
            }
        }
    }

    return 1;
}
//Precondición: recibe 2 matrices vacías
//Postcondición: Rellena las dos matrices con las matrices del fichero entrada.txt
int io_cargar_matrices(int A[N][N], int B[N][N]) {
    FILE *f = fopen("entrada.txt", "r");

    if (f == NULL) {
        perror("Error al abrir el fichero");
        return 0;
    }

    int correcto = cargarMatriz(f, A) && cargarMatriz(f, B);

    fclose(f);

    if (!correcto) {
        fprintf(stderr, "Error al leer las matrices.\n");
        return 0;
    }

    return 1;
}
//Precondición: Recibe una matriz 5x5 llena
//Psotcondición: Abre el archivo salida.txt y lo rellena con esa matriz
/*int guardarMatriz(int M[N][N]) {
    FILE *f = fopen("salida.txt", "w");

    if (f == NULL) {
        perror("Error al abrir salida.txt");
        return 0;
    }

    fprintf(f, "Matriz resultado:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%d ", M[i][j]);
        }
        fprintf(f, "\n");
    }

    if (fclose(f) != 0) {
        perror("Error al cerrar salida.txt");
        return 0;
    }

    return 1;
}/*/
#endif