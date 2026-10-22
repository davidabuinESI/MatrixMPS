#ifndef IOMATRIX_H
#define IOMATRIX_H
#include <stdio.h>
#include <time.h>
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

void Show_matrix(const int M[N][N])
{
    for (int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("[%d]", M[i][j]);
        }
	printf("\n");
    }
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