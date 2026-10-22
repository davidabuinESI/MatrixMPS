#ifndef IOMATRIX_H
#define IOMATRIX_H
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "OPMATRIX.h"

//Precondición: Recibe una matriz 5x5 vacía y un fichero de texto
//Postcondición: Rellena la matriz con la matriz correspondiente del fichero de texto
int io_cargar_matriz(FILE *f, int M[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (fscanf(f, "%d", &M[i][j]) != 1) {
                return 0;
            }
        }
    }

    return 1;
}
//Precondición: recibe 2 matrices vacías
//Postcondición: Rellena las dos matrices con las matrices del fichero entrada.txt
int io_cargar_matrices(int A[5][5], int B[5][5]) {
    printf("Introduce el nombre del fichero de entrada terminado en .txt: ");
    char nombre[100];
    if (fgets(nombre, sizeof(nombre), stdin) == NULL) {
        return 0;
    }
    nombre[strcspn(nombre, "\n")] = '\0';
    FILE *f = fopen(nombre, "r");

    if (f == NULL) {
        perror("Error al abrir el fichero");
        return 0;
    }

    int correcto = io_cargar_matriz(f, A) && io_cargar_matriz(f, B);

    fclose(f);

    if (!correcto) {
        fprintf(stderr, "Error al leer las matrices.\n");
        return 0;
    }

    return 1;
}

int io_registrar_log(const char *evento, const char *LOG_RUTA)
{
    FILE *f;
    time_t t;

    if (evento == NULL) {
        return 4;
    }

    f = fopen(LOG_RUTA, "a");
    if (f == NULL) {
        return 4;
    }

    t = time(NULL);
    fprintf(f, "[%s] %s\n", ctime(&t), evento);   /* ctime ya trae fecha, hora y \n */
    fclose(f);
    return 0;
}



void io_gestionar_error(int codigo)
{
    const char *texto;

    switch (codigo) {
        case 1:  texto = "No se puede abrir el fichero.";   break;
        case 2:  texto = "Formato incorrecto.";             break;
        case 3:  texto = "Error de escritura.";             break;
        case 4:  texto = "No se puede escribir en el log."; break;
        case 5:  texto = "Nombre de fichero no valido.";    break;
        case 11: texto = "Puntero nulo.";                   break;
        default: texto = "Error desconocido.";              break;
    }

    printf("ERROR %d: %s\n", codigo, texto);
}

void Show_matrix(const int M[5][5])
{
    for (int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("[%d]", M[i][j]);
        }
	printf("\n");
    }
}


//Precondición: Recibe una matriz 5x5 llena
//Postcondición: Abre el archivo salida.txt y lo rellena con esa matriz
int guardarMatriz(int M[5][5]) {
    printf("Introduce el nombre del fichero de salida terminado en .txt: ");
    char nombre[100];
    if (fgets(nombre, sizeof(nombre), stdin) == NULL) {
        return 0;
    }
    nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el salto de línea al final
    FILE *f = fopen(nombre, "w");

    if (f == NULL) {
        perror("Error al abrir salida.txt");
        return 0;
    }

    fprintf(f, "Matriz resultado:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fprintf(f, "%d ", M[i][j]);
        }
        fprintf(f, "\n");
    }

    if (fclose(f) != 0) {
        perror("Error al cerrar salida.txt");
        return 0;
    }

    return 1;
}
#endif