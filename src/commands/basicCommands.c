/**
 * @file basic_commands.c
 * @brief Implementación de comandos básicos del sistema.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, malloc
#include <time.h>   // time, localtime, strfti
#include <string.h>   // strcmp, atof
#include <dirent.h>   // opendir, readdir, closedir
#include "commands.h"

/**
 * @brief Comando AYUDA
 * 
 * Muestra al usuario la lista de acciones que puede realizar.
 * Es fundamental para la usabilidad de la shell.
 * 
 * @param args Argumentos del comando (no se usan aquí, por eso (void)args).
 */
void cmd_ayuda(char **args) {
    printf("--- Ayuda de Shell Educativa ---\n");
    printf("Comandos disponibles:\n");
    printf("  - listar: Muestra archivos del directorio.\n");
    printf("  - leer <archivo>: Muestra el contenido de un archivo.\n");
    printf("  - tiempo: Muestra la fecha y hora actual.\n");
    printf("  - calc <n1> <op> <n2>: Realiza cálculos simples.\n");
    printf("  - ayuda: Muestra este mensaje.\n");
    printf("  - salir: Termina la sesión.\n");
    printf("  - crear: Crea un archivo nuevo.\n");
    printf("  - eliminar: Elimina un archivo creado.\n");
    
    // Silenciar advertencia de compilador sobre variable no usada
    (void)args;
}

/**
 * @brief Comando SALIR
 * 
 * Finaliza la ejecución del programa de forma controlada.
 * Utiliza la llamada al sistema exit().
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_salir(char **args) {
    printf("Saliendo de la shell...\n");
    // exit(0) devuelve el código 0 al sistema operativo padre,
    // indicando que el proceso terminó sin errores.
    exit(0);
    (void)args;
}

/**
 * @brief Comando TIEMPO (date)
 * 
 * Obtiene y formatea la fecha y hora del sistema.
 * Demuestra el uso de la librería estándar <time.h>.
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_tiempo(char **args) {
    // 1. Obtener tiempo "crudo" (segundos desde 1970 - Epoch Unix)
    time_t t = time(NULL);
    
    // 2. Convertir a una estructura estructurada local (struct tm)
    // localtime devuelve un puntero, así que desreferenciamos con *
    struct tm tm = *localtime(&t);
    
    // 3. Imprimir con formato
    // tm_year cuenta desde 1900, por eso sumamos 1900.
    // tm_mon es 0-11, por eso sumamos 1.
    printf("Fecha y Hora del Sistema: %02d-%02d-%04d %02d:%02d:%02d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
           tm.tm_hour, tm.tm_min, tm.tm_sec);
           
    (void)args;
}

/**
 * @brief Comando LISTAR
 * 
 * Lista los archivos y directorios del directorio actual.
 * Utiliza la librería <dirent.h> para interactuar con el sistema
 * de archivos del sistema operativo.
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_listar(char **args){
    DIR *dir;
    struct dirent *entry;

    // 1. Abrir el directorio actual (".")
    dir = opendir(".");

    if (dir == NULL) {
        perror("Error al abrir el directorio");
        return;
    }

    printf("Contenido del directorio actual:\n");

    // 2. Leer cada entrada del directorio
    while ((entry = readdir(dir)) != NULL) {
        printf(" - %s\n", entry->d_name);
    }

    // 3. Cerrar el directorio
    closedir(dir);

    (void)args;
}

/**
 * @brief Comando LEER
 * 
 * Abre un archivo en modo lectura y muestra su contenido
 * línea por línea en la consola.
 * 
 * Uso esperado:
 *   leer nombre_archivo.txt
 * 
 * @param args Argumentos del comando.
 */
void cmd_leer(char **args){
    if (args[1] == NULL) {
        printf("Error: Debe especificar el nombre del archivo.\n");
        return;
    }

    FILE *file = fopen(args[1], "r");

    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char buffer[256];

    printf("Contenido de %s:\n", args[1]);

    // Leer línea por línea
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}



/**
 * @brief Comando CALC
 * 
 * Realiza operaciones matemáticas simples entre dos números.
 * Soporta operadores: +, -, *, /
 * 
 * Uso esperado:
 *   calc 5 + 3
 * 
 * @param args Argumentos del comando.
 */
void cmd_calc(char **args){
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        printf("Uso correcto: calc <n1> <op> <n2>\n");
        return;
    }

    double n1 = atof(args[1]);
    double n2 = atof(args[3]);
    char op = args[2][0];

    double resultado;

    switch (op) {
        case '+':
            resultado = n1 + n2;
            break;
        case '-':
            resultado = n1 - n2;
            break;
        case '*':
            resultado = n1 * n2;
            break;
        case '/':
            if (n2 == 0) {
                printf("Error: División por cero.\n");
                return;
            }
            resultado = n1 / n2;
            break;
        default:
            printf("Operador no válido. Use +, -, * o /.\n");
            return;
    }

    printf("Resultado: %.2f\n", resultado);
}
