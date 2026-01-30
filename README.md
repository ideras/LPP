# LPP (Lenguaje de Programación para Principiantes)

LPP es un lenguaje de programación **interpretado**, diseñado específicamente para trabajar con **sintaxis y convenciones en español**, con el objetivo de facilitar el aprendizaje de la programación a estudiantes principiantes. El proyecto incluye tanto un **intérprete** como un **Entorno de Desarrollo Integrado (IDE)**.

LPP fue creado originalmente en **2002** como proyecto de graduación de Ingeniería en Sistemas Computacionales por **Iván de Jesús Deras**. La versión actual es una **reescritura profunda** de la mayor parte del sistema original, orientada a:

* Modernizar el código base
* Facilitar su mantenimiento
* Adaptarlo a un modelo **Open Source**
* Fomentar contribuciones de la comunidad

Durante muchos años el proyecto permaneció inactivo, bajo la suposición de que LPP había dejado de utilizarse en Honduras. Sin embargo, a inicios de **2024**, el contacto de un usuario en Colombia confirmó que LPP **sigue siendo utilizado con fines educativos**, lo que motivó la liberación y reactivación del proyecto.

---

## Características principales

* **Lenguaje interpretado** escrito en **C++17**
* **Sintaxis en español**, pensada para principiantes
* **Tipos de datos primitivos**:

  * Enteros de 32 bits
  * Reales de doble precisión
  * Caracteres
  * Booleanos
* **Arreglos** de tamaño definido
* **Cadenas** de tamaño fijo e indefinido
* **Alias de tipos de datos**, para mejorar la legibilidad del código
* **Estructuras de datos** (registros)
* IDE dedicado para edición y ejecución de programas

---

## Requisitos

Para compilar y ejecutar el proyecto se requiere:

* Compilador con soporte para **C++17**
* **CMake**
* **re2c**
* **Qt 6.2** (para el IDE)

---

## Estructura del proyecto

```
LPP/
├── interp/        # Código fuente del intérprete
├── test_interp/  # Pruebas unitarias del intérprete
└── ide/           # Código fuente del IDE
```

---

## Instalación y compilación

### Clonar el repositorio

```bash
git clone https://github.com/ideras/LPP.git
cd LPP
```

### Compilar el intérprete

```bash
mkdir build-interp
cd build-interp
cmake ../interp
cmake --build .
```

### Compilar el IDE

```bash
mkdir build-ide
cd build-ide
cmake ../ide
cmake --build .
```

---

## Configuración del IDE

El IDE utiliza un archivo de configuración llamado **`lpp.ini`**, ubicado en el mismo directorio que el ejecutable `lpp_ide`.

Si el archivo no existe, el IDE lo creará automáticamente con valores predeterminados la primera vez que se ejecute.

### Parámetros disponibles

* **Terminal**: Ruta al emulador de terminal

  * Ejemplo: `/usr/bin/konsole`, `/usr/bin/xterm`
* **TerminalArgs**: Argumentos utilizados para ejecutar el intérprete

  * Ejemplo: `-e`
* **LppInterp**: Ruta al ejecutable del intérprete `lpp_interp`

### Ejemplo de `lpp.ini`

```ini
[General]
Terminal=/usr/bin/konsole
TerminalArgs=-e
LppInterp=/ruta/a/lpp_interp
```

---

## Uso

### Ejecutar el IDE

Antes de iniciar el IDE, asegúrate de que el ejecutable del intérprete (`lpp_interp`) se encuentre en el mismo directorio que `lpp_ide`.

Luego, ejecuta:

```bash
./lpp_ide
```

### Ejecutar un programa desde la terminal

También puedes ejecutar programas directamente desde la línea de comandos:

```bash
./lpp_interp --action run holamundo.lpp
```

Donde `holamundo.lpp` es el archivo fuente del programa escrito en LPP.

---

## Contribuciones

Las contribuciones son **bienvenidas y altamente valoradas**.

Para contribuir:

1. Realiza un **fork** del repositorio
2. Crea una nueva rama:

   ```bash
   git checkout -b feature/nueva-caracteristica
   ```
3. Realiza tus cambios y confirma los commits:

   ```bash
   git commit -am "Agrega nueva característica"
   ```
4. Envía la rama a tu fork:

   ```bash
   git push origin feature/nueva-caracteristica
   ```
5. Abre un **Pull Request**

---

## Licencia

Este proyecto se distribuye bajo la **Licencia BSD de 2 cláusulas**.

Consulta el archivo [LICENSE](LICENSE) para más detalles.
