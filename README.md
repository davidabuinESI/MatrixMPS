# MATRIX

Programa en C que, desde la consola, realiza operaciones con matrices de orden 5x5. Cada operación usa dos matrices, A y B, y guarda el resultado en una tercera matriz, R.

## Qué puede hacer

- Cargar la matriz A y la matriz B por separado, cada una desde el fichero de texto que elijas.
- Mostrar por pantalla las matrices A, B y el último resultado R.
- Sumar (R = A + B), restar (R = A - B) y multiplicar matrices (R = A x B).
- Multiplicar la matriz A por un número (R = k * A).
- Guardar el resultado R en un fichero con el nombre que elijas.
- Comprobar si una matriz (A, B o R) es simétrica y mostrar el resultado en texto.
- Registrar todo lo que ocurre (cargas, operaciones, guardados y errores) en el fichero `matrix.log`.
- Avisar de cualquier error sin cerrarse: fichero que no existe, formato incorrecto, texto donde se espera un número, resultados que no caben en un entero, etc.

Antes de cada operación el programa muestra por pantalla las matrices con las que va a operar, y después el resultado.

## Archivos del proyecto

| Archivo | Para qué sirve |
|---|---|
| `Matrix.c` | Programa principal: mensaje de bienvenida y menú |
| `IOMATRIX.h` | Biblioteca de entrada/salida: carga y guardado de matrices, mostrar por pantalla, lectura del teclado, log y control de errores |
| `OPMATRIX.h` | Biblioteca de operaciones: suma, resta, producto por escalar, multiplicación, comprobación de simetría y control de errores |
| `matriz_A.txt`, `matriz_B.txt` | Matrices de ejemplo |
| `entrada.txt` | Fichero de ejemplo con dos matrices (al cargarlo se usa la primera) |

## Cómo compilarlo

Necesitas tener instalado `gcc`. Desde la carpeta del proyecto:

```
gcc -std=c99 -o matrix Matrix.c
```

Compila solo `Matrix.c`; las bibliotecas `.h` se incluyen solas.

## Cómo ejecutarlo

Desde la misma carpeta:

```
.\matrix
```

(en Linux o Mac: `./matrix`)

## Uso del menú

Escribe el número de la opción y pulsa Enter.

| Opción | Qué hace |
|---|---|
| 1 | Pide un fichero y carga la matriz A |
| 2 | Pide un fichero y carga la matriz B |
| 3 | Muestra A, B y el último resultado R |
| 4 | Suma: R = A + B |
| 5 | Resta: R = A - B |
| 6 | Multiplica matrices: R = A x B |
| 7 | Pide un número k y calcula R = k * A (solo necesita A) |
| 8 | Guarda R en un fichero con el nombre que indiques |
| 9 | Comprueba si una matriz (A, B o R, a elegir) es simétrica y lo indica con un texto |
| 10 | Sale del programa |

Las operaciones 4, 5 y 6 necesitan que A y B estén cargadas; la 7, solo A; la 8, que ya exista un resultado; y la 9, que esté cargada la matriz elegida (para R, que exista un resultado). Si falta algo, el programa lo avisa.

### Ejemplo de uso

1. Escribe `1` y el nombre `matriz_A.txt` para cargar A.
2. Escribe `2` y el nombre `matriz_B.txt` para cargar B.
3. Escribe `4` para sumarlas: se muestran A, B y el resultado R.
4. Escribe `8` y un nombre, por ejemplo `resultado.txt`, para guardar R.
5. Escribe `9` y elige `1` para comprobar si A es simétrica.
6. Escribe `10` para salir.

## Formato de los ficheros de matrices

Cinco filas con cinco números enteros separados por espacios. Se ignoran las líneas en blanco.

```
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
```

Si el fichero tiene más contenido a continuación (como `entrada.txt`, que tiene dos matrices), solo se lee la primera matriz. Los ficheros que guarda el programa tienen este mismo formato, así que se pueden volver a cargar como A o B.

## El fichero matrix.log

Se crea en la carpeta desde la que ejecutas el programa y se va ampliando en cada ejecución. Cada línea lleva la fecha y la hora:

```
[2026-10-22 13:11:28] INICIO: programa iniciado
[2026-10-22 13:11:28] CARGA: matriz A desde matriz_A.txt
[2026-10-22 13:11:28] OPERACION: suma R = A + B
[2026-10-22 13:11:28] ERROR: Desbordamiento: el resultado no cabe en un entero. (codigo 10)
[2026-10-22 13:11:28] FIN: programa finalizado
```

## Errores

Cada error se muestra como `ERROR <código>: <mensaje>` y se anota en el log. El programa no se cierra: vuelve al menú.

| Código | Cuándo ocurre |
|---|---|
| 1 | No se puede abrir el fichero (no existe o no hay permisos) |
| 2 | El fichero no contiene una matriz válida: faltan datos, sobran datos en una fila, hay letras o decimales, o un número es demasiado grande |
| 3 | Error al escribir en un fichero |
| 4 | No se puede escribir en el log |
| 5 | Nombre de fichero vacío o demasiado largo (máximo 255 caracteres) |
| 6 | Lo escrito en el teclado no es válido (por ejemplo, letras donde se espera un número) |
| 10 | Desbordamiento: el resultado de una operación no cabe en un entero |
| 11 | Error interno: se ha usado una matriz nula |
| 12 | Faltan datos: hay que cargar las matrices necesarias o hacer una operación antes |

Si una carga falla, la matriz que ya estuviera cargada se conserva. Si una operación falla, R conserva el último resultado válido.

## Limitaciones

- Solo trabaja con matrices de 5x5 de números enteros.
- Los números están limitados al rango de un entero de C (de -2147483648 a 2147483647).
- Al guardar, si el fichero ya existe se sobrescribe sin preguntar.