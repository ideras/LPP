# Manual de Usuario de LPP
## Lenguaje de Programación para Principiantes

---

## Tabla de Contenidos
1. [Introducción](#introducción)
2. [Estructura de un Programa](#estructura-de-un-programa)
3. [Tipos de Datos](#tipos-de-datos)
4. [Variables](#variables)
5. [Operadores](#operadores)
6. [Estructuras de Control](#estructuras-de-control)
7. [Arreglos](#arreglos)
8. [Cadenas](#cadenas)
9. [Registros](#registros)
10. [Procedimientos y Funciones](#procedimientos-y-funciones)
11. [Funciones Integradas](#funciones-integradas)
12. [Entrada y Salida](#entrada-y-salida)
13. [Comentarios](#comentarios)
14. [Ejemplos Completos](#ejemplos-completos)

---

## Introducción

LPP (Lenguaje de Programación para Principiantes) es un lenguaje interpretado diseñado específicamente para enseñar programación utilizando sintaxis en español. Es ideal para estudiantes que están aprendiendo conceptos básicos de programación.

### Características Principales
- Sintaxis completamente en español
- Tipado fuerte y estático
- Soporte para estructuras de datos complejas
- Fácil de aprender y usar

---

## Estructura de un Programa

Todo programa en LPP tiene la siguiente estructura básica:

```lpp
// Declaración de variables globales (opcional)
Entero x, y

Inicio
    // Instrucciones del programa
    x <- 10
    y <- 20
    Escriba x + y
Fin
```

### Componentes:
1. **Declaraciones globales**: Variables, tipos, registros, funciones y procedimientos
2. **Bloque principal**: Delimitado por `Inicio` y `Fin`
3. **Instrucciones**: Asignaciones, llamadas a funciones, estructuras de control

---

## Tipos de Datos

LPP soporta los siguientes tipos de datos primitivos:

### 1. Entero
Números enteros de 32 bits (con signo).

```lpp
Entero edad, cantidad
Inicio
    edad <- 25
    cantidad <- -100
Fin
```

### 2. Real
Números de punto flotante de doble precisión.

```lpp
Real precio, pi
Inicio
    precio <- 19.99
    pi <- 3.14159
Fin
```

### 3. Caracter
Un solo carácter.

```lpp
Caracter letra, inicial
Inicio
    letra <- 'A'
    inicial <- 'J'
Fin
```

### 4. Booleano
Valores lógicos: `Verdadero` o `Falso`.

```lpp
Booleano activo, terminado
Inicio
    activo <- Verdadero
    terminado <- Falso
Fin
```

### 5. Cadena
Cadenas de texto de longitud variable o fija.

```lpp
Cadena nombre          // Longitud variable
Cadena[20] codigo      // Longitud fija de 20 caracteres

Inicio
    nombre <- "Juan Pérez"
    codigo <- "ABC123"
Fin
```

---

## Variables

### Declaración de Variables

Las variables se declaran especificando el tipo seguido del nombre:

```lpp
Entero x
Real temperatura
Caracter opcion
Booleano activo
Cadena mensaje
```

Múltiples variables del mismo tipo pueden declararse en una línea:

```lpp
Entero a, b, c
Real x, y, z
```

### Asignación

Se utiliza el operador `<-` para asignar valores:

```lpp
x <- 10
nombre <- "María"
activo <- Verdadero
```

---

## Operadores

### Operadores Aritméticos

| Operador | Descripción | Ejemplo |
|----------|-------------|---------|
| `+` | Suma | `a + b` |
| `-` | Resta | `a - b` |
| `*` | Multiplicación | `a * b` |
| `/` | División real | `a / b` |
| `div` | División entera | `a div b` |
| `mod` | Módulo (resto) | `a mod b` |
| `^` | Potencia | `a ^ b` |

```lpp
Entero a, b, c, d
Real x

Inicio
    a <- 10
    b <- 3

    c <- a + b      // 13
    c <- a - b      // 7
    c <- a * b      // 30
    x <- a / b      // 3.333...
    c <- a div b    // 3
    c <- a mod b    // 1
    c <- 2 ^ 8      // 256
Fin
```

### Operadores Relacionales

| Operador | Descripción | Ejemplo |
|----------|-------------|---------|
| `<` | Menor que | `a < b` |
| `<=` | Menor o igual que | `a <= b` |
| `>` | Mayor que | `a > b` |
| `>=` | Mayor o igual que | `a >= b` |
| `=` | Igual a | `a = b` |
| `<>` | Diferente de | `a <> b` |

```lpp
Booleano resultado
Entero x, y

Inicio
    x <- 10
    y <- 20

    resultado <- x < y      // Verdadero
    resultado <- x > y      // Falso
    resultado <- x = y      // Falso
    resultado <- x <> y     // Verdadero
Fin
```

### Operadores Lógicos

| Operador | Descripción | Ejemplo |
|----------|-------------|---------|
| `y` | AND lógico | `a y b` |
| `o` | OR lógico | `a o b` |
| `No` | NOT lógico | `No a` |

```lpp
Booleano a, b, resultado

Inicio
    a <- Verdadero
    b <- Falso

    resultado <- a y b      // Falso
    resultado <- a o b      // Verdadero
    resultado <- No a       // Falso
Fin
```

---

## Estructuras de Control

### 1. Condicional Si-Entonces-Sino

```lpp
Si <condición> Entonces
    // instrucciones
Sino
    // instrucciones alternativas
Fin Si
```

**Ejemplo:**

```lpp
Entero edad

Inicio
    edad <- 18

    Si edad >= 18 Entonces
        Escriba "Eres mayor de edad"
    Sino
        Escriba "Eres menor de edad"
    Fin Si
Fin
```

**Si anidado:**

```lpp
Entero nota

Inicio
    nota <- 85

    Si nota >= 90 Entonces
        Escriba "Excelente"
    Sino Si nota >= 80 Entonces
        Escriba "Muy bien"
    Sino Si nota >= 70 Entonces
        Escriba "Bien"
    Sino
        Escriba "Necesitas mejorar"
    Fin Si
Fin
```

### 2. Ciclo Mientras

```lpp
Mientras <condición> Haga
    // instrucciones
Fin Mientras
```

**Ejemplo:**

```lpp
Entero contador

Inicio
    contador <- 1

    Mientras contador <= 10 Haga
        Escriba contador
        contador <- contador + 1
    Fin Mientras
Fin
```

### 3. Ciclo Para

```lpp
Para <variable> <- <inicio> Hasta <fin> Haga
    // instrucciones
Fin Para
```

**Ejemplo:**

```lpp
Entero i

Inicio
    Para i <- 1 Hasta 10 Haga
        Escriba i
    Fin Para
Fin
```

### 4. Ciclo Repita-Hasta

```lpp
Repita
    // instrucciones
Hasta <condición>
```

**Ejemplo:**

```lpp
Entero numero

Inicio
    numero <- 1

    Repita
        Escriba numero
        numero <- numero + 1
    Hasta numero > 10
Fin
```

### 5. Estructura Caso

La estructura `Caso` permite evaluar múltiples opciones:

```lpp
Caso <expresión>
    valor1: instrucción1
    valor2: instrucción2
    valor3: instrucción3
    Sino:
        instrucción_predeterminada
Fin Caso
```

**Ejemplo con valores individuales:**

```lpp
Entero opcion

Inicio
    opcion <- 2

    Caso opcion
        1: Escriba "Opción uno"
        2: Escriba "Opción dos"
        3: Escriba "Opción tres"
        Sino:
            Escriba "Opción no válida"
    Fin Caso
Fin
```

**Ejemplo con rangos:**

```lpp
Entero edad

Inicio
    edad <- 25

    Caso edad
        0 -> 12: Escriba "Niño"
        13 -> 17: Escriba "Adolescente"
        18 -> 64: Escriba "Adulto"
        65 -> 120: Escriba "Adulto mayor"
        Sino:
            Escriba "Edad no válida"
    Fin Caso
Fin
```

**Ejemplo con múltiples valores:**

```lpp
Caracter vocal

Inicio
    vocal <- 'e'

    Caso vocal
        'a','e','i','o','u': Escriba "Es vocal minúscula"
        'A','E','I','O','U': Escriba "Es vocal mayúscula"
        Sino:
            Escriba "No es vocal"
    Fin Caso
Fin
```

**Ejemplo combinando valores y rangos:**

```lpp
Entero dia

Inicio
    dia <- 15

    Caso dia
        1,15,31: Escriba "Día de pago"
        5 -> 10: Escriba "Días de reuniones"
        20,21,22: Escriba "Días especiales"
        Sino:
            Escriba "Día normal"
    Fin Caso
Fin
```

---

## Arreglos

Los arreglos permiten almacenar múltiples valores del mismo tipo.

### Arreglos Unidimensionales

```lpp
Arreglo [<tamaño>] De <tipo> <nombre>
```

**Ejemplo:**

```lpp
Arreglo [5] De Entero numeros
Entero i

Inicio
    numeros[1] <- 10
    numeros[2] <- 20
    numeros[3] <- 30
    numeros[4] <- 40
    numeros[5] <- 50

    Para i <- 1 Hasta 5 Haga
        Escriba numeros[i]
    Fin Para
Fin
```

**Nota:** Los índices en LPP comienzan en 1, no en 0.

### Arreglos Multidimensionales

```lpp
Arreglo [<filas>, <columnas>] De <tipo> <nombre>
```

**Ejemplo de arreglo bidimensional:**

```lpp
Arreglo [3, 3] De Entero matriz
Entero i, j

Inicio
    // Llenar la matriz
    matriz[1,1] <- 1
    matriz[1,2] <- 2
    matriz[1,3] <- 3
    matriz[2,1] <- 4
    matriz[2,2] <- 5
    matriz[2,3] <- 6
    matriz[3,1] <- 7
    matriz[3,2] <- 8
    matriz[3,3] <- 9

    // Imprimir la matriz
    Para i <- 1 Hasta 3 Haga
        Para j <- 1 Hasta 3 Haga
            Escriba matriz[i,j]
        Fin Para
    Fin Para
Fin
```

### Arreglos de Arreglos

También puedes declarar arreglos de arreglos:

```lpp
Arreglo [2] De Arreglo [3] De Entero tabla

Inicio
    tabla[1][1] <- 10
    tabla[1][2] <- 20
    tabla[1][3] <- 30
    tabla[2][1] <- 40
    tabla[2][2] <- 50
    tabla[2][3] <- 60
Fin
```

---

## Cadenas

Las cadenas en LPP pueden tener longitud variable o fija.

### Cadenas de Longitud Variable

```lpp
Cadena mensaje

Inicio
    mensaje <- "Hola Mundo"
    Escriba mensaje
Fin
```

### Cadenas de Longitud Fija

```lpp
Cadena[10] codigo

Inicio
    codigo <- "ABC123"
    Escriba codigo
Fin
```

### Operaciones con Cadenas

#### Concatenación

```lpp
Cadena nombre, apellido, nombreCompleto

Inicio
    nombre <- "Juan"
    apellido <- "Pérez"
    nombreCompleto <- nombre + " " + apellido
    Escriba nombreCompleto  // "Juan Pérez"
Fin
```

#### Acceso a Caracteres

```lpp
Cadena[5] palabra

Inicio
    palabra[1] <- 'H'
    palabra[2] <- 'o'
    palabra[3] <- 'l'
    palabra[4] <- 'a'
    palabra[5] <- '!'
    Escriba palabra  // "Hola!"
Fin
```

---

## Registros

Los registros (estructuras) permiten agrupar diferentes tipos de datos relacionados.

### Declaración de Registros

```lpp
Registro <NombreRegistro>
    <tipo> <campo1>
    <tipo> <campo2>
    ...
Fin Registro
```

**Ejemplo:**

```lpp
Registro Persona
    Cadena nombre
    Entero edad
    Real altura
Fin Registro

Persona estudiante

Inicio
    estudiante.nombre <- "María"
    estudiante.edad <- 20
    estudiante.altura <- 1.65

    Escriba estudiante.nombre
    Escriba estudiante.edad
    Escriba estudiante.altura
Fin
```

### Registros Anidados

```lpp
Registro Direccion
    Cadena calle
    Cadena ciudad
    Entero codigoPostal
Fin Registro

Registro Empleado
    Cadena nombre
    Direccion domicilio
    Real salario
Fin Registro

Empleado trabajador

Inicio
    trabajador.nombre <- "Carlos"
    trabajador.domicilio.calle <- "Calle Principal 123"
    trabajador.domicilio.ciudad <- "Tegucigalpa"
    trabajador.domicilio.codigoPostal <- 11101
    trabajador.salario <- 25000.50

    Escriba trabajador.nombre
    Escriba trabajador.domicilio.ciudad
Fin
```

### Registros con Arreglos

```lpp
Registro Estudiante
    Cadena nombre
    Arreglo [5] De Real notas
Fin Registro

Estudiante alumno
Entero i

Inicio
    alumno.nombre <- "Ana"
    alumno.notas[1] <- 85.5
    alumno.notas[2] <- 90.0
    alumno.notas[3] <- 88.5
    alumno.notas[4] <- 92.0
    alumno.notas[5] <- 87.5

    Escriba alumno.nombre
    Para i <- 1 Hasta 5 Haga
        Escriba alumno.notas[i]
    Fin Para
Fin
```

---

## Procedimientos y Funciones

LPP permite definir subprogramas mediante procedimientos y funciones.

### Procedimientos

Los procedimientos ejecutan acciones pero no devuelven valores.

```lpp
Procedimiento <nombre>(<parámetros>)
    // instrucciones
Fin
```

**Ejemplo:**

```lpp
Procedimiento Saludar(Cadena nombre)
Inicio
    Escriba "Hola, " + nombre
Fin

Inicio
    Llamar Saludar("María")
Fin
```

### Funciones

Las funciones ejecutan acciones y devuelven un valor.

```lpp
Funcion <nombre>(<parámetros>): <tipo_retorno>
Inicio
    // instrucciones
    Retorne <valor>
Fin
```

**Ejemplo:**

```lpp
Funcion Suma(Entero a, Entero b): Entero
Inicio
    Retorne a + b
Fin

Entero resultado

Inicio
    resultado <- Suma(10, 20)
    Escriba resultado  // 30
Fin
```

### Parámetros por Valor y por Referencia

#### Por Valor (predeterminado)
El parámetro recibe una copia del valor:

```lpp
Procedimiento Incrementar(Entero x)
Inicio
    x <- x + 1
    Escriba x  // Se incrementa dentro del procedimiento
Fin

Entero numero

Inicio
    numero <- 5
    Llamar Incrementar(numero)  // Imprime 6
    Escriba numero  // Imprime 5 (no cambió)
Fin
```

#### Por Referencia (var)
El parámetro es una referencia a la variable original:

```lpp
Procedimiento Incrementar(var Entero x)
Inicio
    x <- x + 1
Fin

Entero numero

Inicio
    numero <- 5
    Llamar Incrementar(numero)
    Escriba numero  // Imprime 6 (sí cambió)
Fin
```

### Procedimientos y Funciones sin Parámetros

```lpp
Entero contador

Procedimiento IncrementarContador
Inicio
    contador <- contador + 1
Fin

Funcion ObtenerContador: Entero
Inicio
    Retorne contador
Fin

Inicio
    contador <- 0
    Llamar IncrementarContador
    Escriba ObtenerContador()  // 1
Fin
```

### Funciones Recursivas

LPP soporta recursión:

```lpp
Funcion Factorial(Entero n): Entero
Inicio
    Si n <= 1 Entonces
        Retorne 1
    Sino
        Retorne n * Factorial(n - 1)
    Fin Si
Fin

Inicio
    Escriba Factorial(5)  // 120
Fin
```

---

## Funciones Integradas

LPP proporciona varias funciones integradas útiles:

### Funciones de Conversión

#### Aleatorio()
Genera un número aleatorio entre 0 y 1.

```lpp
Real num
Inicio
    num <- Aleatorio()
    Escriba num
Fin
```

#### Caracter_Ascii(entero)
Convierte un código ASCII en un carácter.

```lpp
Caracter letra
Inicio
    letra <- Caracter_Ascii(65)  // 'A'
    Escriba letra
Fin
```

#### Valor_Ascii(caracter)
Obtiene el código ASCII de un carácter.

```lpp
Entero codigo
Inicio
    codigo <- Valor_Ascii('A')  // 65
    Escriba codigo
Fin
```

#### Entero_A_Cadena(entero)
Convierte un entero a cadena.

```lpp
Cadena texto
Entero numero
Inicio
    numero <- 123
    texto <- Entero_A_Cadena(numero)
    Escriba texto  // "123"
Fin
```

#### Real_A_Cadena(real, decimales)
Convierte un número real a cadena con el número especificado de decimales.

```lpp
Cadena texto
Real pi
Inicio
    pi <- 3.14159
    texto <- Real_A_Cadena(pi, 2)
    Escriba texto  // "3.14"
Fin
```

### Funciones de Cadenas

#### longitud(cadena)
Retorna la longitud de una cadena.

```lpp
Cadena mensaje
Entero tam
Inicio
    mensaje <- "Hola Mundo"
    tam <- longitud(mensaje)
    Escriba tam  // 10
Fin
```

---

## Entrada y Salida

### Escriba - Salida de Datos

Imprime valores en la pantalla:

```lpp
Escriba <expresión>
```

**Ejemplos:**

```lpp
Inicio
    Escriba "Hola Mundo"
    Escriba 123
    Escriba 3.14159
    Escriba 'A'
    Escriba Verdadero
Fin
```

### Lea - Entrada de Datos

Lee valores desde el teclado:

```lpp
Lea <variable>
```

**Ejemplo:**

```lpp
Entero edad
Cadena nombre
Real altura

Inicio
    Escriba "Ingrese su nombre:"
    Lea nombre

    Escriba "Ingrese su edad:"
    Lea edad

    Escriba "Ingrese su altura:"
    Lea altura

    Escriba "Hola " + nombre
    Escriba "Edad: "
    Escriba edad
    Escriba "Altura: "
    Escriba altura
Fin
```

---

## Comentarios

Los comentarios en LPP se escriben utilizando `//`:

```lpp
// Este es un comentario de una línea

Entero x  // También puedes poner comentarios al final de una línea

Inicio
    // Los comentarios son ignorados por el intérprete
    x <- 10
Fin
```

---

## Ejemplos Completos

### Ejemplo 1: Calculadora Simple

```lpp
Entero opcion, num1, num2
Real resultado

Inicio
    Escriba "Calculadora Simple"
    Escriba "1. Sumar"
    Escriba "2. Restar"
    Escriba "3. Multiplicar"
    Escriba "4. Dividir"
    Escriba "Seleccione una opción:"
    Lea opcion

    Escriba "Ingrese el primer número:"
    Lea num1
    Escriba "Ingrese el segundo número:"
    Lea num2

    Caso opcion
        1: resultado <- num1 + num2
        2: resultado <- num1 - num2
        3: resultado <- num1 * num2
        4: resultado <- num1 / num2
        Sino:
            Escriba "Opción no válida"
    Fin Caso

    Escriba "Resultado: "
    Escriba resultado
Fin
```

### Ejemplo 2: Búsqueda en Arreglo

```lpp
Arreglo [5] De Entero numeros
Entero i, buscar
Booleano encontrado

Procedimiento BuscarNumero(Entero num, var Booleano result)
Entero j
Inicio
    result <- Falso
    Para j <- 1 Hasta 5 Haga
        Si numeros[j] = num Entonces
            result <- Verdadero
        Fin Si
    Fin Para
Fin

Inicio
    // Llenar el arreglo
    numeros[1] <- 10
    numeros[2] <- 25
    numeros[3] <- 30
    numeros[4] <- 45
    numeros[5] <- 50

    Escriba "Ingrese un número a buscar:"
    Lea buscar

    Llamar BuscarNumero(buscar, encontrado)

    Si encontrado Entonces
        Escriba "El número fue encontrado"
    Sino
        Escriba "El número no está en el arreglo"
    Fin Si
Fin
```

### Ejemplo 3: Sistema de Estudiantes

```lpp
Registro Estudiante
    Cadena nombre
    Cadena carrera
    Arreglo [3] De Real notas
    Real promedio
Fin Registro

Funcion CalcularPromedio(Arreglo [3] De Real calificaciones): Real
Real suma
Entero i
Inicio
    suma <- 0.0
    Para i <- 1 Hasta 3 Haga
        suma <- suma + calificaciones[i]
    Fin Para
    Retorne suma / 3
Fin

Estudiante alumno
Entero i

Inicio
    Escriba "Sistema de Registro de Estudiantes"

    Escriba "Ingrese el nombre del estudiante:"
    Lea alumno.nombre

    Escriba "Ingrese la carrera:"
    Lea alumno.carrera

    Para i <- 1 Hasta 3 Haga
        Escriba "Ingrese la nota " + Entero_A_Cadena(i) + ":"
        Lea alumno.notas[i]
    Fin Para

    alumno.promedio <- CalcularPromedio(alumno.notas)

    Escriba "===== Información del Estudiante ====="
    Escriba "Nombre: " + alumno.nombre
    Escriba "Carrera: " + alumno.carrera
    Escriba "Notas:"
    Para i <- 1 Hasta 3 Haga
        Escriba "  Nota " + Entero_A_Cadena(i) + ": " + Real_A_Cadena(alumno.notas[i], 2)
    Fin Para
    Escriba "Promedio: " + Real_A_Cadena(alumno.promedio, 2)

    Si alumno.promedio >= 70 Entonces
        Escriba "Estado: APROBADO"
    Sino
        Escriba "Estado: REPROBADO"
    Fin Si
Fin
```

### Ejemplo 4: Números Primos

```lpp
Funcion EsPrimo(Entero n): Booleano
Entero i
Booleano primo
Inicio
    Si n <= 1 Entonces
        Retorne Falso
    Fin Si

    primo <- Verdadero
    i <- 2

    Mientras (i * i <= n) y primo Haga
        Si (n mod i) = 0 Entonces
            primo <- Falso
        Fin Si
        i <- i + 1
    Fin Mientras

    Retorne primo
Fin

Entero limite, num

Inicio
    Escriba "Números primos del 1 al 100:"

    Para num <- 2 Hasta 100 Haga
        Si EsPrimo(num) Entonces
            Escriba num
        Fin Si
    Fin Para
Fin
```

### Ejemplo 5: Ordenamiento de Arreglo (Burbuja)

```lpp
Arreglo [10] De Entero numeros

Procedimiento OrdenarBurbuja(var Arreglo [10] De Entero arr)
Entero i, j, temp
Inicio
    Para i <- 1 Hasta 9 Haga
        Para j <- 1 Hasta (10 - i) Haga
            Si arr[j] > arr[j + 1] Entonces
                // Intercambiar
                temp <- arr[j]
                arr[j] <- arr[j + 1]
                arr[j + 1] <- temp
            Fin Si
        Fin Para
    Fin Para
Fin

Entero k

Inicio
    // Llenar el arreglo con valores aleatorios
    Escriba "Arreglo original:"
    Para k <- 1 Hasta 10 Haga
        numeros[k] <- Entero(Aleatorio() * 100)
        Escriba numeros[k]
    Fin Para

    // Ordenar
    Llamar OrdenarBurbuja(numeros)

    // Mostrar arreglo ordenado
    Escriba "Arreglo ordenado:"
    Para k <- 1 Hasta 10 Haga
        Escriba numeros[k]
    Fin Para
Fin
```

---

## Alias de Tipos

LPP permite crear alias para tipos de datos, lo que mejora la legibilidad del código:

```lpp
Tipo Vector es Arreglo [3] De Real
Tipo Matriz es Arreglo [3, 3] De Entero

Vector posicion
Matriz tabla

Inicio
    posicion[1] <- 1.5
    posicion[2] <- 2.5
    posicion[3] <- 3.5

    tabla[1,1] <- 1
    tabla[1,2] <- 2
    tabla[1,3] <- 3
Fin
```

---

## Buenas Prácticas

1. **Nombres descriptivos**: Usa nombres significativos para variables, funciones y procedimientos.
   ```lpp
   // Bien
   Entero edadEstudiante

   // Evitar
   Entero e
   ```

2. **Comentarios**: Documenta tu código con comentarios útiles.
   ```lpp
   // Calcula el promedio de tres números
   Funcion Promedio(Real a, Real b, Real c): Real
   Inicio
       Retorne (a + b + c) / 3
   Fin
   ```

3. **Indentación**: Mantén una indentación consistente para mejorar la legibilidad.

4. **Divide y vencerás**: Usa procedimientos y funciones para dividir problemas complejos en partes más pequeñas.

5. **Validación de entrada**: Siempre valida los datos ingresados por el usuario.
   ```lpp
   Entero edad
   Inicio
       Lea edad
       Si (edad < 0) o (edad > 120) Entonces
           Escriba "Edad no válida"
       Fin Si
   Fin
   ```

---

## Errores Comunes

### 1. Olvidar el operador de asignación correcto
```lpp
// Incorrecto
x = 10

// Correcto
x <- 10
```

### 2. Índices de arreglos
```lpp
// Recuerda: los índices empiezan en 1, no en 0
Arreglo [5] De Entero nums

Inicio
    nums[1] <- 10  // Correcto
    nums[0] <- 10  // Error: índice fuera de rango
Fin
```

### 3. Olvidar Fin en estructuras
```lpp
// Incorrecto
Si x > 0 Entonces
    Escriba "Positivo"

// Correcto
Si x > 0 Entonces
    Escriba "Positivo"
Fin Si
```

### 4. No usar Llamar para procedimientos
```lpp
Procedimiento Saludar
Inicio
    Escriba "Hola"
Fin

Inicio
    // Incorrecto
    Saludar

    // Correcto
    Llamar Saludar
Fin
```

---

## Diferencias con Otros Lenguajes

| Característica | LPP | Otros lenguajes |
|----------------|-----|-----------------|
| Asignación | `<-` | `=` |
| División entera | `div` | `/` o `//` |
| Módulo | `mod` | `%` |
| AND lógico | `y` | `&&` o `and` |
| OR lógico | `o` | `||` o `or` |
| NOT lógico | `No` | `!` o `not` |
| Diferente de | `<>` | `!=` |
| Índice inicial | 1 | 0 |
| Llamar procedimiento | `Llamar Proc` | `Proc()` |

---

## Conclusión

Este manual cubre las características principales de LPP. El lenguaje está diseñado para ser intuitivo y fácil de aprender, especialmente para hispanohablantes que están comenzando en la programación.

Para más información y ejemplos, consulta:
- Los archivos de prueba en el directorio `test_interp/`
- El código fuente del intérprete en el directorio `interp/`
- El repositorio oficial: https://github.com/ideras/LPP

---

**Versión del Manual**: 1.0
**Fecha**: 2024
**Autor**: Documentación basada en LPP por Ivan de Jesus Deras
