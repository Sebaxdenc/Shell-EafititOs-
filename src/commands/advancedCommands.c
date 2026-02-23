/**
 * @file advancedCommands.c
 * @brief Implementación de comandos avanzados o de manipulación de archivos.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, malloc
#include "commands.h"

/**
 * @brief Comando CREAR
 * 
 * Crea un archivo de texto vacío en el directorio actual.
 * Si el archivo ya existe, lo sobrescribe (comportamiento de "w" en fopen).
 * 
 * Uso esperado:
 *   crear <nombre_archivo>
 * 
 * @param args Argumentos del comando.
 */
void cmd_crear(char **args) {
    if (args[1] == NULL) {
        printf("Error: Debe especificar el nombre del archivo.\n");
        return;
    }

    FILE *file = fopen(args[1], "w");

    if (file == NULL) {
        perror("Error al crear el archivo");
        return;
    }

    printf("Archivo creado exitosamente: %s\n", args[1]);
    fclose(file);
}

/**
 * @brief Comando ELIMINAR
 * 
 * Elimina un archivo del directorio actual.
 * Utiliza la llamada al sistema remove().
 * 
 * Uso esperado:
 *   eliminar <nombre_archivo>
 * 
 * @param args Argumentos del comando.
 */
void cmd_eliminar(char **args) {
    if (args[1] == NULL) {
        printf("Error: Debe especificar el nombre del archivo.\n");
        return;
    }

    if (remove(args[1]) == 0) {
        printf("Archivo eliminado exitosamente: %s\n", args[1]);
    } else {
        perror("Error al eliminar el archivo");
    }
}

