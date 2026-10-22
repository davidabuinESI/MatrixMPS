#include <stdio.h>
#include "OPMATRIX.h"
#include "IOMATRIX.h"

/* Registra un evento en el log. Si falla, avisa pero el programa sigue. */
static void registrar(const char *evento)
{
    int cod = io_registrar_log(evento);

    if (cod != OK) {
        io_gestionar_error(cod);
    }
}

static void mostrar_bienvenida(void)
{
    printf("==============================================\n");
    printf("   MATRIX - Operaciones con matrices de 5x5\n");
    printf("==============================================\n");
}

/* Muestra el menu y lee la opcion elegida. Devuelve OK o un codigo de error. */
int mainMenu(int *opt)
{
    printf("\n--------------- MENU ---------------\n");
    printf("[1] Cargar la matriz A desde un fichero\n");
    printf("[2] Cargar la matriz B desde un fichero\n");
    printf("[3] Mostrar las matrices A, B y R\n");
    printf("[4] Sumar            R = A + B\n");
    printf("[5] Restar           R = A - B\n");
    printf("[6] Multiplicar      R = A x B\n");
    printf("[7] Producto por escalar   R = k * A\n");
    printf("[8] Guardar la matriz R en un fichero\n");
    printf("[9] Comprobar si una matriz es simetrica\n");
    printf("[10] Salir\n");

    return io_leer_entero("Elige una opcion: ", opt);
}

/* Pide al usuario un fichero y carga en M la matriz que contiene.
 * nombre es "A" o "B". Devuelve OK o un codigo de error. */
static int cargar_matriz_usuario(const char *nombre, int M[N][N])
{
    char ruta[MAX_RUTA];
    char aviso[64];
    char evento[MAX_RUTA + 64];
    int cod;

    snprintf(aviso, sizeof aviso, "Fichero de la matriz %s (.txt): ", nombre);
    cod = io_leer_ruta(aviso, ruta, sizeof ruta);
    if (cod == OK) {
        cod = io_cargar_matriz(ruta, M);
    }
    if (cod != OK) {
        return cod;
    }

    printf("\nMatriz %s cargada desde %s:\n", nombre, ruta);
    Show_matrix(M);
    snprintf(evento, sizeof evento, "CARGA: matriz %s desde %s", nombre, ruta);
    registrar(evento);
    return OK;
}

/* Comprueba que A y B estan cargadas y las muestra antes de operar. */
static int mostrar_operandos(int a_cargada, int b_cargada, int A[N][N], int B[N][N])
{
    if (!a_cargada || !b_cargada) {
        return ERR_OP_SIN_DATOS;
    }
    printf("\nMatriz A:\n");
    Show_matrix(A);
    printf("\nMatriz B:\n");
    Show_matrix(B);
    return OK;
}

int main(void)
{
    int A[N][N] = {{0}}, B[N][N] = {{0}}, R[N][N] = {{0}};
    int a_cargada = 0, b_cargada = 0, r_disponible = 0;
    int opt, cod;

    mostrar_bienvenida();
    registrar("INICIO: programa iniciado");

    while (1) {
        cod = mainMenu(&opt);
        if (cod != OK) {
            if (feof(stdin)) {
                printf("\nFin de la entrada. Saliendo.\n");
                break;
            }
            io_gestionar_error(cod);
            continue;
        }

        switch (opt) {
            case 1:
                cod = cargar_matriz_usuario("A", A);
                if (cod == OK) {
                    a_cargada = 1;
                } else {
                    io_gestionar_error(cod);
                }
                break;

            case 2:
                cod = cargar_matriz_usuario("B", B);
                if (cod == OK) {
                    b_cargada = 1;
                } else {
                    io_gestionar_error(cod);
                }
                break;

            case 3:
                printf("\nMatriz A:\n");
                if (a_cargada) Show_matrix(A); else printf("(sin cargar)\n");
                printf("\nMatriz B:\n");
                if (b_cargada) Show_matrix(B); else printf("(sin cargar)\n");
                printf("\nMatriz R (ultimo resultado):\n");
                if (r_disponible) Show_matrix(R); else printf("(sin resultado)\n");
                break;

            case 4:
                cod = mostrar_operandos(a_cargada, b_cargada, A, B);
                if (cod == OK) cod = op_sumar(A, B, R);
                if (cod != OK) {
                    op_gestionar_error(cod);
                    break;
                }
                r_disponible = 1;
                printf("\nResultado R = A + B:\n");
                Show_matrix(R);
                registrar("OPERACION: suma R = A + B");
                break;

            case 5:
                cod = mostrar_operandos(a_cargada, b_cargada, A, B);
                if (cod == OK) cod = op_restar(A, B, R);
                if (cod != OK) {
                    op_gestionar_error(cod);
                    break;
                }
                r_disponible = 1;
                printf("\nResultado R = A - B:\n");
                Show_matrix(R);
                registrar("OPERACION: resta R = A - B");
                break;

            case 6:
                cod = mostrar_operandos(a_cargada, b_cargada, A, B);
                if (cod == OK) cod = op_multiplicar(A, B, R);
                if (cod != OK) {
                    op_gestionar_error(cod);
                    break;
                }
                r_disponible = 1;
                printf("\nResultado R = A x B:\n");
                Show_matrix(R);
                registrar("OPERACION: multiplicacion de matrices R = A x B");
                break;

            case 7: {
                int k;
                char evento[64];

                if (!a_cargada) {
                    op_gestionar_error(ERR_OP_SIN_DATOS);
                    break;
                }
                printf("\nMatriz A:\n");
                Show_matrix(A);
                cod = io_leer_entero("Escalar k: ", &k);
                if (cod != OK) {
                    io_gestionar_error(cod);
                    break;
                }
                cod = op_escalar(k, A, R);
                if (cod != OK) {
                    op_gestionar_error(cod);
                    break;
                }
                r_disponible = 1;
                printf("\nResultado R = %d * A:\n", k);
                Show_matrix(R);
                snprintf(evento, sizeof evento, "OPERACION: producto por escalar R = %d * A", k);
                registrar(evento);
                break;
            }

            case 8: {
                char ruta[MAX_RUTA];
                char evento[MAX_RUTA + 64];

                if (!r_disponible) {
                    op_gestionar_error(ERR_OP_SIN_DATOS);
                    break;
                }
                cod = io_leer_ruta("Nombre del fichero de salida (.txt): ", ruta, sizeof ruta);
                if (cod == OK) {
                    cod = io_guardar_matriz(ruta, R);
                }
                if (cod != OK) {
                    io_gestionar_error(cod);
                    break;
                }
                printf("Matriz R guardada en %s\n", ruta);
                snprintf(evento, sizeof evento, "GUARDADO: matriz R en %s", ruta);
                registrar(evento);
                break;
            }

            case 9: {
                int cual, ok = 0, es_sim;
                int (*M)[N] = NULL;
                const char *nombre = "";
                char evento[96];

                printf("\nMatriz a comprobar: [1] A   [2] B   [3] R\n");
                cod = io_leer_entero("Elige la matriz: ", &cual);
                if (cod != OK) {
                    io_gestionar_error(cod);
                    break;
                }
                if (cual == 1)      { M = A; nombre = "A"; ok = a_cargada; }
                else if (cual == 2) { M = B; nombre = "B"; ok = b_cargada; }
                else if (cual == 3) { M = R; nombre = "R"; ok = r_disponible; }
                else {
                    io_gestionar_error(ERR_IO_ENTRADA);
                    break;
                }
                if (!ok) {
                    op_gestionar_error(ERR_OP_SIN_DATOS);
                    break;
                }
                printf("\nMatriz %s:\n", nombre);
                Show_matrix(M);
                es_sim = (es_simetrica(M) == 0);
                printf("\nLa matriz %s %s simetrica.\n", nombre, es_sim ? "SI es" : "NO es");
                snprintf(evento, sizeof evento, "OPERACION: simetria de la matriz %s -> %s",
                         nombre, es_sim ? "simetrica" : "no simetrica");
                registrar(evento);
                break;
            }

            case 10:
                printf("\nHasta pronto.\n");
                registrar("FIN: programa finalizado");
                return 0;

            default:
                printf("\nOpcion no valida. Elige un numero del 1 al 10.\n");
                break;
        }
    }

    registrar("FIN: programa finalizado");
    return 0;
}