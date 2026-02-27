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
    printf("  - crear <archivo>: Crea un archivo nuevo.\n");
    printf("  - eliminar <archivo>: Elimina un archivo.\n");
    printf("  - tiempo: Muestra la fecha y hora actual.\n");
    printf("  - calc <n1> <op> <n2>: Realiza cálculos simples.\n");
    printf("  - limpiar: Limpia la pantalla.\n");
    printf("  - ayuda: Muestra este mensaje.\n");
    printf("  - salir: Termina la sesión.\n");
    
    // Silenciar advertencia de compilador sobre variable no usada
    (void)args;
}

/**
 * @brief Comando LISTAR (ls)
 *
 * Abre el directorio actual (".") e itera sobre sus entradas para mostrar los nombres.
 *
 * @param args Argumentos del comando (ignorados en esta versión simple).
 */
void cmd_listar(char **args) {
    DIR *d;               // Puntero al flujo del directorio
    struct dirent *dir;   // Estructura que representa una entrada (archivo/carpeta)

    d = opendir(".");
    
    if (d) {
        printf("Archivos en el directorio actual:\n");
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("  %s\n", dir->d_name);
            }
        }
        closedir(d);
    } else {
        perror("Error al abrir directorio");
    }
    (void)args;
}

/**
 * @brief Comando LEER (cat)
 *
 * Abre un archivo en modo lectura, lee su contenido caracter por caracter
 * y lo imprime en la terminal.
 *
 * @param args args[1] debe contener la ruta o nombre del archivo a leer.
 */
void cmd_leer(char **args) {
    if (args[1] == NULL) {
        printf("Error: Debes especificar un archivo para leer.\nUso: leer <nombre_archivo>\n");
        return;
    }

    FILE *fp = fopen(args[1], "r");
    if (fp == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'. Verifique que exista.\n", args[1]);
        return;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    printf("\n");

    fclose(fp);
}
/**
 * @brief Comando CALC (Calculadora)
 *
 * Realiza operaciones aritméticas básicas entre dos números.
 * Sintaxis esperada: calc <num1> <operador> <num2>
 *
 * @param args Lista de argumentos donde:
 *             args[1]: Primer operando (cadena)
 *             args[2]: Operador (+, -, *, /)
 *             args[3]: Segundo operando (cadena)
 */
void cmd_calc(char **args) {
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        printf("Uso: calc <num1> <operador> <num2>\nEjemplo: calc 5 + 3\n");
        return;
    }

    float n1 = atof(args[1]);
    char op = args[2][0];
    float n2 = atof(args[3]);
    float res = 0;

    switch(op) {
        case '+':
            res = n1 + n2;
            break;
        case '-':
            res = n1 - n2;
            break;
        case '*':
        case 'x':
            res = n1 * n2;
            break;
        case '/':
            if (n2 == 0) {
                printf("Error: División por cero no permitida.\n");
                return;
            }
            res = n1 / n2;
            break;
        default:
            printf("Error: Operador '%c' no reconocido. Use +, -, * o /.\n", op);
            return;
    }

    printf("Resultado: %.2f\n", res);
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

