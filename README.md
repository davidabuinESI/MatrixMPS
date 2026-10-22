# MATRIX

Programa en C que, desde la consola, realiza operaciones con dos matrices de orden 5x5 (A y B).

## Qué hace ahora mismo

- Lee dos matrices 5x5 de números enteros desde el fichero `entrada.txt`.
- Muestra un menú por consola que se repite hasta que eliges salir.
- Suma las matrices (A + B) y muestra el resultado.
- Resta las matrices (A - B) y muestra el resultado.
- Avisa si el resultado de una operación no cabe en un número entero (desbordamiento).

## Archivos del proyecto

| Archivo | Para qué sirve |
|---|---|
| `Matrix.c` | Programa principal: menú y operaciones |
| `IOMATRIX.h` | Carga de matrices desde fichero y visualización por pantalla |
| `OPMATRIX.h` | Declaración de las operaciones con matrices |
| `entrada.txt` | Datos de las matrices A y B |

## Cómo compilarlo

Necesitas tener instalado `gcc`. Desde la carpeta del proyecto:

```
gcc -std=c99 -o matrix Matrix.c
```

Compila solo `Matrix.c`.

## Cómo ejecutarlo

Ejecútalo desde la misma carpeta donde está `entrada.txt`:

```
.\matrix
```

## El fichero entrada.txt

Contiene las dos matrices, A primero y B después, con 5 filas de 5 números separados por espacios cada una. Se puede dejar una línea en blanco entre las dos.

```
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25

5 4 3 2 1
10 9 8 7 6
15 14 13 12 11
20 19 18 17 16
25 24 23 22 21
```

Si el fichero no existe o no tiene 25 números por matriz, el programa muestra un error y termina.

## Uso del menú

Al arrancar aparece este menú:

```
[1] Adition
[2] Subtraction
[3] Multiplication (betwen matrices)
[4] Exit
```

Escribe el número de la opción y pulsa Enter.

| Opción | Qué hace |
|---|---|
| 1 | Suma A + B y muestra el resultado |
| 2 | Resta A - B y muestra el resultado |
| 3 | Multiplicación de matrices: todavía no está disponible |
| 4 | Sale del programa |

Cualquier otro número muestra `Try again!` y vuelve al menú.

El resultado se muestra por pantalla, una fila por línea. Con el `entrada.txt` de ejemplo, la suma da:

```
[6][6][6][6][6]
[16][16][16][16][16]
[26][26][26][26][26]
[36][36][36][36][36]
[46][46][46][46][46]
```

## Errores

- Si el resultado de una suma o resta no cabe en un entero, se muestra `Error 10: desbordamiento` y no se muestra el resultado.
- Si `entrada.txt` no se puede abrir o está mal, el programa muestra el error y se cierra.

## Limitaciones actuales

- Solo trabaja con matrices de 5x5 de números enteros.
- Los datos solo se pueden leer de `entrada.txt`; no se pueden elegir otro fichero ni guardar el resultado.
- La multiplicación de matrices y la multiplicación por un número aún no están disponibles en el menú.
- Escribe solo números en el menú; si escribes letras, el programa puede quedarse repitiendo el menú.
- El menú está en inglés.
