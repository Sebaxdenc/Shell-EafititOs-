# Shell-EafititOs-
Shell educativa implementada en C que implementa comandos básicos y avanzados para operaciones del sistema.

**Integrantes y porcentajes**

|  Nombre                                 | Código | Rol     | Tareas Asignadas                                      | % Contribución |
|-----------------------------------------|--------|---------|-------------------------------------------------------|----------------|
| Juan Carlos Muñoz Trejos                | 1032176998   | Líder   | Diseño, implementación del core y del shell loop     | 50%            |
| Sebastian Medina Cabezas                | 1058198772   | Dev     | Implementación de comandos, parser y pruebas         | 50%            |

Total: 100%

**Diagrama de arquitectura (resumen)**

```
+----------------------+      +----------------------+      +--------------------+
| User (terminal)      | ---> | src/core/shellLoop.c | ---> | src/commands/*     |
+----------------------+      +----------------------+      +--------------------+
																 |         ^  ^  ^
																 |         |  |  |
																 v         |  |  |
                                                         src/core/parser.c |  |  |
																					 include/commands.h  |
																															 |
																												src/utils/*
```

- `shellLoop` : lee la línea, usa `parser` para tokenizar y despacha usando la tabla de comandos.
- `commands/*` : implementaciones de `cmd_listar`, `cmd_leer`, `cmd_crear`, `cmd_eliminar`, `cmd_calc`, `cmd_tiempo`, `cmd_limpiar`, `cmd_salir`, etc.
- `include/` : cabeceras públicas para declarar comandos y utilidades.

**Instrucciones de compilación**

Requisitos: `gcc` y `make` disponibles en el sistema.

Compilar usando el `Makefile` incluido:

```bash
make
```

Ejecutar la shell:

```bash
./shell.exe    # en Windows con MinGW/MSYS o en Unix
```

Comandos adicionales de `Make`:

```bash
make run       # compila y ejecuta
make clean     # elimina objetos y ejecutable
```

**Guía de uso completa**

Arranque: ejecutar `./shell.exe`. Aparecerá un prompt donde puedes escribir comandos.

Comandos disponibles (ejemplos):

- `listar`
	- Muestra los archivos del directorio actual.

- `leer <archivo>`
	- Muestra el contenido de `<archivo>` en la terminal.
	- Ejemplo: `leer README.md`

- `crear <archivo>`
	- Crea (o sobrescribe) un archivo vacío.
	- Ejemplo: `crear prueba.txt`

- `eliminar <archivo>`
	- Borra el archivo especificado.
	- Ejemplo: `eliminar prueba.txt`

- `tiempo`
	- Muestra fecha y hora del sistema.

- `calc <n1> <op> <n2>`
	- Realiza operaciones aritméticas básicas.
	- Operadores: `+ - * /` (también soporta `x` como multiplicación).
	- Ejemplo: `calc 5 + 3` → `Resultado: 8.00`

- `limpiar`
	- Limpia la pantalla de la terminal (usa secuencias ANSI).

- `ayuda`
	- Muestra la lista de comandos y uso básico.

- `salir`
	- Cierra la shell.

Notas:

- Para añadir nuevos comandos, implementar la función `void cmd_xxx(char **args)` en `src/commands/` y registrar su nombre y puntero en `src/core/shellLoop.c`.
- El `Makefile` compila todos los `.c` bajo `src/core`, `src/utils` y `src/commands`.



