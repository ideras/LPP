# LPP (Lenguaje de Programacion para Principiantes)
LPP es un lenguaje de programación interpretado diseñado para trabajar con la sintaxis y las convenciones del idioma español. Proporciona un entorno de desarrollo integrado (IDE) y un intérprete para escribir y ejecutar programas en el lenguaje.
Originalmente LPP fue creado como un requisito de graduación de Ingenieria en Sistemas computacionales por mi persona (Ivan de Jesus Deras).  La versión original fue creada en el año 2002.  Esta versión es una reescritura de la mayoria de las partes de LPP con el proposito de hacerlo amigable al Open Source y motivar las contribuciones al proyecto.
Personalmente no habia liberado este código porque con el pasar del tiempo LPP dejo de ser utilizado en mi pais (Honduras) y pensé que el proyecto habia muerto, hasta que a inicios del 2024 alguien de Colombia llamado Kevin Bermudez me contactó y me dejó saber que LPP todavia se utiliza en Colombia.

## Características Principales

- **Lenguaje Interpretado**: Escrito en C++17, el intérprete permite ejecutar programas escritos en el lenguaje.
- **Soporte de Tipos de Datos**: Admite variables de tipos primitivos como enteros de 32 bits, reales de doble precisión, caracteres y booleanos.
- **Manejo de Arreglos y Cadenas**: Permite el uso de arreglos de tamaño definido y cadenas de tamaño fijo e indefinido.
- **Alias de Tipos de Datos**: Facilita la definición de alias para los tipos de datos, lo que mejora la legibilidad del código.
- **Estructuras de Datos**: Acepta la definición de estructuras, también conocidas como registros en otros lenguajes.

## Requisitos Previos

Para compilar y ejecutar el proyecto, se necesitan los siguientes requisitos:

- CMake
- re2c
- Compilador de C++ con soporte para C++17
- QT version 6.2

## Estructura

- El folder **interp** contiene el código fuente del interprete.
- El folder **test_interp** contiene un seria de pruebas unitarias para el interprete.
- El folder **ide** contiene el codigo del IDE del LPP.

## Instalación

1. Clona el repositorio desde GitHub:

```bash
git clone https://github.com/ideras/LPP.git
```

2. Navega al directorio del proyecto:

```bash
cd LPP
```

3. Configura y compila el interprete utilizando CMake:

```bash
mkdir build-interp && cd build-interp
cmake ../interp
cmake --build .
```

3. Configura y compila el IDE utilizando CMake:

```bash
mkdir build-ide && cd build-ide
cmake ../ide
cmake --build .
```

## Uso

Una vez compilado, puedes utilizar el intérprete y el IDE para escribir y ejecutar programas en el lenguaje. Antes de ejecutar el IDE
debes copiar el ejecutable del interprete en el mismo directorio del IDE.  Luego simplemente inicias el IDE con el siguiente comando:

```bash
./lpp_ide
```

En caso que desees ejecutar un programa de LPP directamente desde la terminal lo puedes hacer de la siguiente manera:

```bash
./lpp_interp --action run holamundo.lpp
```
En este caso holamundo.lpp es el nombre del programa de lpp que queremos ejecutar.

## Contribuciones

Las contribuciones son bienvenidas y alentadas. Si deseas contribuir al proyecto, sigue estos pasos:

1. Haz un fork del proyecto.
2. Crea una nueva branch (`git checkout -b feature/nueva-caracteristica`).
3. Realiza tus cambios y haz commit de ellos (`git commit -am 'Agrega nueva característica'`).
4. Haz push a la branch (`git push origin feature/nueva-caracteristica`).
5. Abre un pull request

## Licencia

Este proyecto está licenciado bajo la Licencia BSD de 2 cláusulas. Para obtener más información, consulta el archivo [LICENSE](LICENSE).

