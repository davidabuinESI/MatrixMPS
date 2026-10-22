#ifndef IOMATRIX_H
#define IOMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

#define N           5            /* orden de las matrices */
#define MAX_RUTA    256          /* longitud maxima de un nombre de fichero */
#define FICHERO_LOG "matrix.log" /* fichero donde se registran las operaciones */

/* Codigos de error. 0 = todo correcto.
 * 1-6 los generan las funciones de IOMATRIX.h; 10-12, las de OPMATRIX.h. */
typedef enum {
    OK                    = 0,
    ERR_IO_ABRIR          = 1,   /* no se puede abrir el fichero */
    ERR_IO_FORMATO        = 2,   /* el fichero no contiene una matriz 5x5 valida */
    ERR_IO_ESCRITURA      = 3,   /* error al escribir en el fichero */
    ERR_IO_LOG            = 4,   /* no se puede escribir en el log */
    ERR_IO_RUTA           = 5,   /* nombre de fichero vacio o demasiado largo */
    ERR_IO_ENTRADA        = 6,   /* dato de teclado no valido o fin de la entrada */
    ERR_OP_DESBORDAMIENTO = 10,  /* el resultado no cabe en un int */
    ERR_NULO              = 11,  /* puntero nulo en lugar de una matriz */
    ERR_OP_SIN_DATOS      = 12   /* faltan matrices por cargar o no hay resultado */
} CodigoError;

/* ------------------------------------------------------------------ */
/* LOG                                                                 */
/* ------------------------------------------------------------------ */

//Precondicion: evento es un texto terminado en '\0'.
//Postcondicion: anade al final de matrix.log la linea "[AAAA-MM-DD HH:MM:SS] evento".
//Devuelve: OK, ERR_NULO (evento NULL) o ERR_IO_LOG (no se puede escribir).
int io_registrar_log(const char *evento)
{
    FILE *f;
    time_t ahora;
    struct tm *local;
    char marca[32];

    if (evento == NULL) {
        return ERR_NULO;
    }

    f = fopen(FICHERO_LOG, "a");
    if (f == NULL) {
        return ERR_IO_LOG;
    }

    ahora = time(NULL);
    local = localtime(&ahora);
    if (local == NULL || strftime(marca, sizeof marca, "%Y-%m-%d %H:%M:%S", local) == 0) {
        strcpy(marca, "sin fecha");
    }

    if (fprintf(f, "[%s] %s\n", marca, evento) < 0) {
        fclose(f);
        return ERR_IO_LOG;
    }
    if (fclose(f) != 0) {
        return ERR_IO_LOG;
    }
    return OK;
}

/* ------------------------------------------------------------------ */
/* CONTROL DE ERRORES                                                  */
/* ------------------------------------------------------------------ */

//Postcondicion: muestra "ERROR <codigo>: <mensaje>" y lo registra en el log.
//Lo usan io_gestionar_error y op_gestionar_error.
void io_informar_error(const char *mensaje, int codigo)
{
    char evento[160];

    printf("ERROR %d: %s\n", codigo, mensaje);
    snprintf(evento, sizeof evento, "ERROR: %s (codigo %d)", mensaje, codigo);
    if (io_registrar_log(evento) != OK) {
        fprintf(stderr, "Aviso: no se ha podido escribir en el log.\n");
    }
}

//Precondicion: codigo devuelto por una funcion de IOMATRIX.h.
//Postcondicion: informa al usuario del error y lo registra en el log.
//Con OK no hace nada.
void io_gestionar_error(int codigo)
{
    switch (codigo) {
        case OK:
            return;
        case ERR_IO_ABRIR:
            io_informar_error("No se puede abrir el fichero.", codigo);
            break;
        case ERR_IO_FORMATO:
            io_informar_error("Formato incorrecto: se esperan 5 filas con 5 enteros cada una.", codigo);
            break;
        case ERR_IO_ESCRITURA:
            io_informar_error("Error de escritura.", codigo);
            break;
        case ERR_IO_LOG:
            /* Un fallo del propio log no se puede registrar en el log. */
            fprintf(stderr, "ERROR %d: No se puede escribir en el log.\n", codigo);
            break;
        case ERR_IO_RUTA:
            io_informar_error("Nombre de fichero no valido (vacio o demasiado largo).", codigo);
            break;
        case ERR_IO_ENTRADA:
            io_informar_error("Entrada no valida.", codigo);
            break;
        case ERR_NULO:
            io_informar_error("Puntero nulo.", codigo);
            break;
        default:
            io_informar_error("Error desconocido.", codigo);
            break;
    }
}

/* ------------------------------------------------------------------ */
/* LECTURA DE TECLADO                                                  */
/* ------------------------------------------------------------------ */

/* Lee una linea de teclado (sin el salto de linea). Si la linea no cabe en
 * buf, descarta el resto y pone *truncada a 1.
 * Devuelve OK o ERR_IO_ENTRADA si se ha terminado la entrada. */
static int io_leer_linea(const char *aviso, char *buf, size_t tam, int *truncada)
{
    size_t n;
    int c;

    *truncada = 0;
    printf("%s", aviso);
    fflush(stdout);

    if (fgets(buf, (int)tam, stdin) == NULL) {
        return ERR_IO_ENTRADA;
    }

    n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n') {
        buf[--n] = '\0';
    } else if (n == tam - 1) {
        /* buffer lleno sin salto de linea: ver si la linea acaba justo ahi o continua */
        c = getchar();
        if (c != '\n' && c != EOF) {
            *truncada = 1;
            while ((c = getchar()) != '\n' && c != EOF) {
                /* descartar el resto de la linea */
            }
        }
    }
    if (n > 0 && buf[n - 1] == '\r') {
        buf[--n] = '\0';
    }
    return OK;
}

//Postcondicion: lee un numero entero de teclado y lo guarda en *valor.
//Devuelve: OK, ERR_NULO o ERR_IO_ENTRADA (no es un entero valido o fin de la entrada).
int io_leer_entero(const char *aviso, int *valor)
{
    char buf[64];
    char *fin;
    long v;
    int truncada;
    int cod;

    if (aviso == NULL || valor == NULL) {
        return ERR_NULO;
    }
    cod = io_leer_linea(aviso, buf, sizeof buf, &truncada);
    if (cod != OK) {
        return cod;
    }
    if (truncada) {
        return ERR_IO_ENTRADA;
    }

    errno = 0;
    v = strtol(buf, &fin, 10);
    if (fin == buf || errno == ERANGE || v > INT_MAX || v < INT_MIN) {
        return ERR_IO_ENTRADA;
    }
    while (*fin == ' ' || *fin == '\t') {
        fin++;
    }
    if (*fin != '\0') {
        return ERR_IO_ENTRADA;
    }
    *valor = (int)v;
    return OK;
}

//Postcondicion: lee de teclado un nombre de fichero y lo guarda en ruta (tam bytes).
//Devuelve: OK, ERR_NULO, ERR_IO_RUTA (vacio o demasiado largo) o ERR_IO_ENTRADA (fin de la entrada).
int io_leer_ruta(const char *aviso, char *ruta, size_t tam)
{
    int truncada;
    int cod;

    if (aviso == NULL || ruta == NULL || tam < 2) {
        return ERR_NULO;
    }
    cod = io_leer_linea(aviso, ruta, tam, &truncada);
    if (cod != OK) {
        return cod;
    }
    if (truncada || ruta[0] == '\0') {
        return ERR_IO_RUTA;
    }
    return OK;
}

/* ------------------------------------------------------------------ */
/* FICHEROS Y PANTALLA                                                 */
/* ------------------------------------------------------------------ */

//Precondicion: ruta es el nombre de un fichero de texto con una matriz 5x5:
//  5 filas de 5 enteros separados por espacios (se ignoran las lineas en blanco).
//  Si el fichero tiene mas contenido a continuacion, solo se lee la primera matriz.
//Postcondicion: M se rellena solo si la lectura completa es correcta.
//Devuelve: OK, ERR_NULO, ERR_IO_RUTA, ERR_IO_ABRIR o ERR_IO_FORMATO.
int io_cargar_matriz(const char *ruta, int M[N][N])
{
    FILE *f;
    int tmp[N][N];
    char linea[1024];
    int fila = 0;

    if (ruta == NULL || M == NULL) {
        return ERR_NULO;
    }
    if (ruta[0] == '\0' || strlen(ruta) >= MAX_RUTA) {
        return ERR_IO_RUTA;
    }

    f = fopen(ruta, "r");
    if (f == NULL) {
        return ERR_IO_ABRIR;
    }

    while (fila < N && fgets(linea, sizeof linea, f) != NULL) {
        char *p = linea;
        char *fin;
        size_t n = strlen(linea);

        if (n == sizeof linea - 1 && linea[n - 1] != '\n' && !feof(f)) {
            fclose(f);
            return ERR_IO_FORMATO;          /* linea absurdamente larga */
        }
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
            p++;
        }
        if (*p == '\0') {
            continue;                       /* linea en blanco */
        }

        for (int j = 0; j < N; j++) {
            long v;

            errno = 0;
            v = strtol(p, &fin, 10);
            if (fin == p || errno == ERANGE || v > INT_MAX || v < INT_MIN) {
                fclose(f);
                return ERR_IO_FORMATO;      /* faltan datos o no es un entero */
            }
            tmp[fila][j] = (int)v;
            p = fin;
        }
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
            p++;
        }
        if (*p != '\0') {
            fclose(f);
            return ERR_IO_FORMATO;          /* sobran datos en la fila */
        }
        fila++;
    }
    fclose(f);

    if (fila < N) {
        return ERR_IO_FORMATO;              /* faltan filas */
    }
    memcpy(M, tmp, sizeof tmp);
    return OK;
}

//Precondicion: M es una matriz 5x5 con datos.
//Postcondicion: escribe M en el fichero ruta (5 filas de 5 enteros), de forma
//  que despues se pueda volver a cargar con io_cargar_matriz.
//Devuelve: OK, ERR_NULO, ERR_IO_RUTA, ERR_IO_ABRIR o ERR_IO_ESCRITURA.
int io_guardar_matriz(const char *ruta, int M[N][N])
{
    FILE *f;

    if (ruta == NULL || M == NULL) {
        return ERR_NULO;
    }
    if (ruta[0] == '\0' || strlen(ruta) >= MAX_RUTA) {
        return ERR_IO_RUTA;
    }

    f = fopen(ruta, "w");
    if (f == NULL) {
        return ERR_IO_ABRIR;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fprintf(f, "%d%c", M[i][j], (j == N - 1) ? '\n' : ' ') < 0) {
                fclose(f);
                return ERR_IO_ESCRITURA;
            }
        }
    }
    if (fclose(f) != 0) {
        return ERR_IO_ESCRITURA;
    }
    return OK;
}

//Precondicion: M es una matriz 5x5 con datos.
//Postcondicion: muestra M por pantalla, una fila por linea.
void Show_matrix(int M[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("[%d]", M[i][j]);
        }
        printf("\n");
    }
}

#endif