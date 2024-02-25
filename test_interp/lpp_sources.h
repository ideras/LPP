const char *hola_mundo_src =
R"(inicio
    Escriba "Hola Mundo"
fin
)";

const char *int_test_src =
R"(Entero x

Inicio
    x <- 10
    Escriba x
Fin)";

const char *real_test_src =
R"(Real x

Inicio
    x <- 3.14159
    Escriba x
Fin)";

const char *char_test_src =
R"(Caracter x

Inicio
    x <- 'A'
    Escriba x
Fin)";

const char *bool_test_src =
R"(Booleano x

Inicio
    x <- Verdadero
    Escriba x
    x <- Falso
    Escriba x
Fin)";

const char *int_int_add_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 27
    z <- x + _y
    Escriba z
Fin
)";

const char *int_int_sub_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 27
    z <- x - _y
    Escriba z
Fin
)";

const char *int_int_mult_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 27
    z <- x * _y
    Escriba z
Fin
)";

const char *int_int_div_src =
R"(Entero x, _y
Real z

Inicio
    x <- 65
    _y <- 27
    z <- x / _y
    Escriba z
Fin
)";

const char *int_int_i_div_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 27
    z <- x div _y
    Escriba z
Fin
)";

const char *int_int_mod_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 27
    z <- x mod _y
    Escriba z
Fin
)";

const char *int_int_pow_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 3
    z <- x ^ _y
    Escriba z
Fin
)";

const char *real_real_add_src =
R"(Real a, b, c

Inicio
    a <- 3.14159
    b <- 65.8
    c <- a + b
    Escriba c
Fin)";

const char *real_real_sub_src =
R"(Real a, b, c

Inicio
    a <- 3.14159
    b <- 65.8
    c <- a - b
    Escriba c
Fin)";

const char *real_real_mult_src =
R"(Real a, b, c

Inicio
    a <- 3.14159
    b <- 65.8
    c <- a * b
    Escriba c
Fin)";

const char *real_real_div_src =
R"(Real a, b, c

Inicio
    a <- 65.8
    b <- 3.14159
    c <- a / b
    Escriba c
Fin)";

const char *real_real_i_div_src =
R"(Real a, b
Entero c

Inicio
    a <- 65.8
    b <- 3.14159
    c <- a div b
    Escriba c
Fin)";

const char *real_real_mod_src =
R"(Real a, b
Entero c

Inicio
    a <- 65.8
    b <- 3.14159
    c <- a mod b
    Escriba c
Fin)";

const char *real_real_pow_src =
R"(Real a, b, c

Inicio
    a <- 65.8
    b <- 3.14159
    c <- a ^ b
    Escriba c
Fin)";

const char *add_int_real_src =
R"(
Entero a
Real b, c

Inicio
    a <- 65
    b <- 3.14159
    c <- a + b
    Escriba c
Fin

)";

const char *add_real_int_src =
R"(Real a, c
Entero b

Inicio
    a <- 3.14159
    b <- 65
    c <- a + b
    Escriba c
Fin
)";

const char *bool_ops_src =
R"(Real a, c
Entero b

Inicio
    Escriba Falso o Falso
    Escriba Falso o Verdadero
    Escriba Verdadero o Falso
    Escriba Verdadero o Verdadero
    Escriba Falso y Falso
    Escriba Falso y Verdadero
    Escriba Verdadero y Falso
    Escriba Verdadero y Verdadero
    Escriba No Falso
    Escriba No Verdadero
Fin
)";

const char *unary_ops_src =
R"(Entero x, _y, z

Inicio
    x <- 65
    _y <- 27
    z <- -(x + _y)
    Escriba z
    z <- +(x + _y)
    Escriba z
Fin)";

const char *test_string1_src =
R"(Cadena x

Inicio
    x <- "Hola Mundo Hello World"
    Escriba x
Fin)";

const char *test_string2_src =
R"(Cadena str1
Cadena str2
Cadena str3

Inicio
    str1 <- "OTkxMAo4MDYxCjU2ODUKNzc1NQo2NDIwCjc0NjIKOTk4CjU0MTIKODA5MAo4Nzk1CjIxMwo3MTQz"
    str2 <- "CjMyMzYKMzA5OQozNTQ0CjY3NjMKNjE5MQo5NDg4CjEyODMKNDEwOAoxMTExCjM2Nwo3MDg5CjEz"
    str3 <- str1 + str2 + "MQo4OTEwCjM0NTIKNzQzOQoxMTE3Cjg4NzcKNzE1Mgo5NjY4CjkxNzMKMjc1OQo5NjAyCjEwMjMK" + "MjE2CjQ3MTYKOTE2OAo2NDAzCjE3ODUKNzE1MAo3NDA4CjE5NTMKOTIwMwozNDc4CjMxMzUKODA5"
    Escriba str3
Fin)";

const char *test_string3_src =
R"(Cadena[3] str

Inicio
    str[1] <- 'A'
    str[2] <- 'B'
    str[3] <- 'C'
    Escriba str
Fin
)";

const char *test_string4_src =
R"(Cadena[10] str

Inicio
    str <- "0123456789ABC"
    Escriba str
Fin
)";

const char *concat_string_src =
R"(Cadena a, b, c

Inicio
    a <- "nuy9hqgrervpLrZaCuBk"
    b <- " qopQyzLzEAtGTMABjrzy"
    c <- a + b

    Escriba c
Fin
)";

const char *concat_string_char_src =
R"(Cadena a, c
Caracter b

Inicio
    a <- "nuy9hqgrervpLrZaCuBk"
    b <- ' '
    c <- a + b + 'C'

    Escriba c
Fin

)";

const char *test_array1_d_int_src =
R"(Arreglo [5] De Entero x

Inicio
    x[1] <- 354
    x[2] <- 642
    x[3] <- 197
    x[4] <- 253
    x[5] <- 938

    Escriba x[1]
    Escriba x[2]
    Escriba x[3]
    Escriba x[4]
    Escriba x[5]
Fin)";

const char *test_array1_d_string_src =
R"(Arreglo [5] De Cadena x

Inicio
    x[1] <- "oFEwk5i7W6ZS2S4W5vdr"
    x[2] <- "BO7GQv7aVzjRZ8m1lvCP"
    x[3] <- "HIZyS2Rs1DnzCvtU4Tk6"
    x[4] <- "OGupKjPrakyYQ2oMhGSe"
    x[5] <- "KKBOVT65jkTt32dFg5sv"

    Escriba x[1]
    Escriba x[2]
    Escriba x[3]
    Escriba x[4]
    Escriba x[5]
Fin)";

const char *test_array2_d_int_src =
R"(Arreglo [2,3] De Entero x

Inicio
    x[1,1] <- 354
    x[1,2] <- 642
    x[1,3] <- 197
    x[2,1] <- 253
    x[2,2] <- 938
    x[2,3] <- 459

    Escriba x[1,1]
    Escriba x[1,2]
    Escriba x[1,3]
    Escriba x[2,1]
    Escriba x[2,2]
    Escriba x[2,3]
Fin
)";

const char *test_array2_d_string_src =
R"(Arreglo [2, 3] De Cadena x

Inicio
    x[1, 1] <- "hlceg4Jy5eUs92sqZp104W38JUjTMB2UKlFkMc3q"
    x[1, 2] <- "dQtoVAKNprqd9WN8v8aBZLl5u0LaEZUbtPUQYeSz"
    x[1, 3] <- "3Q3CgY8lUENkCr8uE4csnsTfPn8bF8pSPI8aPnfR"
    x[2, 1] <- "OH8u0bxWtGssr3KkqgGhREfINB534oRm1x0moRMt"
    x[2, 2] <- "nNlzsCbClwFKD78VzLuZjNsQWiF15w585mgIOp8u"
    x[2, 3] <- "B6Dw8Oq4rnhNJB87qvIiGJAg1I4TCWnVbOEwkg5D"
    
    Escriba x[1, 1]
    Escriba x[1, 2]
    Escriba x[1, 3]
    Escriba x[2, 1]
    Escriba x[2, 2]
    Escriba x[2, 3]
Fin)";

const char *test_array3_d_int_src =
R"(Arreglo [2,3,4] De Entero x

Inicio
    x[1,1,1] <- 354
    x[1,1,2] <- 642
    x[1,1,3] <- 197
    x[1,1,4] <- 253
    x[1,2,1] <- 938
    x[1,2,2] <- 459
    x[1,2,3] <- 938
    x[1,2,4] <- 459
    x[1,3,1] <- 288
    x[1,3,2] <- 458
    x[1,3,3] <- 902
    x[1,3,4] <- 664
    x[2,1,1] <- 718
    x[2,1,2] <- 464
    x[2,1,3] <- 342
    x[2,1,4] <- 343
    x[2,2,1] <- 380
    x[2,2,2] <- 510
    x[2,2,3] <- 458
    x[2,2,4] <- 283
    x[2,3,1] <- 304
    x[2,3,2] <- 945
    x[2,3,3] <- 547
    x[2,3,4] <- 549

    Escriba x[1,1,1]
    Escriba x[1,1,2]
    Escriba x[1,1,3]
    Escriba x[1,1,4]
    Escriba x[1,2,1]
    Escriba x[1,2,2]
    Escriba x[1,2,3]
    Escriba x[1,2,4]
    Escriba x[1,3,1]
    Escriba x[1,3,2]
    Escriba x[1,3,3]
    Escriba x[1,3,4]
    Escriba x[2,1,1]
    Escriba x[2,1,2]
    Escriba x[2,1,3]
    Escriba x[2,1,4]
    Escriba x[2,2,1]
    Escriba x[2,2,2]
    Escriba x[2,2,3]
    Escriba x[2,2,4]
    Escriba x[2,3,1]
    Escriba x[2,3,2]
    Escriba x[2,3,3]
    Escriba x[2,3,4]
Fin

)";

const char *test_array3_d_string_src =
R"(Arreglo [2, 3, 4] De Cadena x

Inicio
    x[1, 1, 1] <- "axZht2g3NNynSV1QWQh4"
    x[1, 1, 2] <- "A4jL14TDfI2jWtBzmk8l"
    x[1, 1, 3] <- "78PmsmDBcJPzTy92OGso"
    x[1, 1, 4] <- "AhvnxDJkqiMUNaVQBRTh"
    x[1, 2, 1] <- "SUt6jIDupBZYU5vqgX01"
    x[1, 2, 2] <- "zgnDwyufCwX13r6SMaA0"
    x[1, 2, 3] <- "BwGhvPCFKOXGn5zDHVdy"
    x[1, 2, 4] <- "ZqIGxNOIJb1M3P8kIQy7"
    x[1, 3, 1] <- "0YVNqzaAOAGowoJl35CA"
    x[1, 3, 2] <- "eS0L7PrlaDVGKgcAiFsz"
    x[1, 3, 3] <- "BR5XOGvl30PtuJHpG23V"
    x[1, 3, 4] <- "Soz925yMUjIBM1EEvqqE"
    x[2, 1, 1] <- "d1P278fvu3YnGGJnvE9J"
    x[2, 1, 2] <- "l5ct1lPxVdWE3e9PQNEu"
    x[2, 1, 3] <- "OXgGk1jiDFXDWw24Lk08"
    x[2, 1, 4] <- "n6fhP8hfi1UWG1gBLUFg"
    x[2, 2, 1] <- "9iVphhWE7ieDqDil6eH6"
    x[2, 2, 2] <- "OzqLD78H8o7wIrXioyax"
    x[2, 2, 3] <- "5QfIQsj9gh0688qhTsxa"
    x[2, 2, 4] <- "DAsimu9c3SYTZtLP7xJM"
    x[2, 3, 1] <- "VcH4SpUcWxFrLgCJiYuJ"
    x[2, 3, 2] <- "qyLD9RJCd4QJo3ZYNTYI"
    x[2, 3, 3] <- "HSXKQEPTvCf684t3Uip0"
    x[2, 3, 4] <- "6EF5eZp0xiCE0yFWKNSY"

    Escriba x[1, 1, 1]
    Escriba x[1, 1, 2]
    Escriba x[1, 1, 3]
    Escriba x[1, 1, 4]
    Escriba x[1, 2, 1]
    Escriba x[1, 2, 2]
    Escriba x[1, 2, 3]
    Escriba x[1, 2, 4]
    Escriba x[1, 3, 1]
    Escriba x[1, 3, 2]
    Escriba x[1, 3, 3]
    Escriba x[1, 3, 4]
    Escriba x[2, 1, 1]
    Escriba x[2, 1, 2]
    Escriba x[2, 1, 3]
    Escriba x[2, 1, 4]
    Escriba x[2, 2, 1]
    Escriba x[2, 2, 2]
    Escriba x[2, 2, 3]
    Escriba x[2, 2, 4]
    Escriba x[2, 3, 1]
    Escriba x[2, 3, 2]
    Escriba x[2, 3, 3]
    Escriba x[2, 3, 4]
Fin)";

const char *test_array_of_array_int_src =
R"(Arreglo [2] De Arreglo [3] De Entero x

Inicio
    x[1][1] <- 354
    x[1][2] <- 642
    x[1][3] <- 197
    x[2][1] <- 253
    x[2][2] <- 938
    x[2][3] <- 459

    Escriba x[1][1]
    Escriba x[1][2]
    Escriba x[1][3]
    Escriba x[2][1]
    Escriba x[2][2]
    Escriba x[2][3]
Fin

)";

const char *test_array_of_array_of_array_int_src =
R"(Arreglo [2] De Arreglo [3] De Arreglo [4] De Entero x

Inicio
    x[1][1][1] <- 354
    x[1][1][2] <- 642
    x[1][1][3] <- 197
    x[1][1][4] <- 253
    x[1][2][1] <- 938
    x[1][2][2] <- 459
    x[1][2][3] <- 938
    x[1][2][4] <- 459
    x[1][3][1] <- 288
    x[1][3][2] <- 458
    x[1][3][3] <- 902
    x[1][3][4] <- 664
    x[2][1][1] <- 718
    x[2][1][2] <- 464
    x[2][1][3] <- 342
    x[2][1][4] <- 343
    x[2][2][1] <- 380
    x[2][2][2] <- 510
    x[2][2][3] <- 458
    x[2][2][4] <- 283
    x[2][3][1] <- 304
    x[2][3][2] <- 945
    x[2][3][3] <- 547
    x[2][3][4] <- 549

    Escriba x[1][1][1]
    Escriba x[1][1][2]
    Escriba x[1][1][3]
    Escriba x[1][1][4]
    Escriba x[1][2][1]
    Escriba x[1][2][2]
    Escriba x[1][2][3]
    Escriba x[1][2][4]
    Escriba x[1][3][1]
    Escriba x[1][3][2]
    Escriba x[1][3][3]
    Escriba x[1][3][4]
    Escriba x[2][1][1]
    Escriba x[2][1][2]
    Escriba x[2][1][3]
    Escriba x[2][1][4]
    Escriba x[2][2][1]
    Escriba x[2][2][2]
    Escriba x[2][2][3]
    Escriba x[2][2][4]
    Escriba x[2][3][1]
    Escriba x[2][3][2]
    Escriba x[2][3][3]
    Escriba x[2][3][4]
Fin


)";

const char *test_rel_int_src =
R"(Entero a, b

Inicio
    a <- 913764
    b <- 5692376

    Escriba a < b
    Escriba a <= b
    Escriba a > b
    Escriba a >= b
    Escriba a = b
    Escriba a <> b

    a <- 5692376
    b <- 913764

    Escriba a < b
    Escriba a <= b
    Escriba a > b
    Escriba a >= b
    Escriba a = b
    Escriba a <> b

    a <- 5692376
    b <- 5692376

    Escriba a < b
    Escriba a <= b
    Escriba a > b
    Escriba a >= b
    Escriba a = b
    Escriba a <> b

Fin
    )";

const char *test_rel_real_src =
R"(Entero a, b

Inicio
    a <- 91.3764
    b <- 569.2376

    Escriba a < b
    Escriba a <= b
    Escriba a > b
    Escriba a >= b
    Escriba a = b
    Escriba a <> b

    a <- 569.2376
    b <- 91.3764

    Escriba a < b
    Escriba a <= b
    Escriba a > b
    Escriba a >= b
    Escriba a = b
    Escriba a <> b

    a <- 569.2376
    b <- 569.2376

    Escriba a < b
    Escriba a <= b
    Escriba a > b
    Escriba a >= b
    Escriba a = b
    Escriba a <> b

Fin
    )";

const char *test_mientras_src =
R"(Entero i

Inicio
    i <- 1
    Mientras i <= 100 Haga
        Escriba i
        i <- i + 1
    Fin Mientras
Fin)";

const char *test_repita_src =
R"(Entero a

Inicio
    a <- 1
    Repita
        Escriba a
        a <- a + 1
    Hasta a > 100
Fin)";

const char *test_para_src =
R"(Entero i

Inicio
    Para i <- 1 Hasta 100 Haga
        Escriba i
    Fin Para
Fin)";

const char *test_si_src =
R"(Entero a, b

Inicio
    a <- 10
    Si a < 10 Entonces
        Escriba 0
    Sino Si a > 10 Entonces
        Escriba 100
    Sino Si a = 10 Entonces
        Escriba 10
    Fin Si

    a <- 5
    Si a < 10 Entonces
        Escriba 'A'
    Sino Si a > 10 Entonces
        Escriba 100
    Sino Si a = 10 Entonces
        Escriba 10
    Fin Si

    a <- 73
    Si a < 10 Entonces
        Escriba 0
    Sino Si a > 10 Entonces
        Escriba 100
    Sino Si a = 10 Entonces
        Escriba 10
    Fin Si
Fin
)";

const char *test_si_anidado_src =
R"(Entero a, b

Inicio
    a <- 5
    b <- 9
    Si a < 10 Entonces
        Si b < 10 Entonces
            Escriba 'A'
        Sino
            Escriba 'B'
        Fin Si
    Sino Si a > 10 Entonces
        Si b < 10 Entonces
            Escriba 'C'
        Sino
            Escriba 'D'
        Fin Si
    Sino Si a = 10 Entonces
        Si b < 10 Entonces
            Escriba 'E'
        Sino
            Escriba 'F'
        Fin Si
    Fin Si

    a <- 45
    b <- 9
    Si a < 10 Entonces
        Si b < 10 Entonces
            Escriba 'A'
        Sino
            Escriba 'B'
        Fin Si
    Sino Si a > 10 Entonces
        Si b < 10 Entonces
            Escriba 'C'
        Sino
            Escriba 'D'
        Fin Si
    Sino Si a = 10 Entonces
        Si b < 10 Entonces
            Escriba 'E'
        Sino
            Escriba 'F'
        Fin Si
    Fin Si

    a <- 10
    b <- 9
    Si a < 10 Entonces
        Si b < 10 Entonces
            Escriba 'A'
        Sino
            Escriba 'B'
        Fin Si
    Sino Si a > 10 Entonces
        Si b < 10 Entonces
            Escriba 'C'
        Sino
            Escriba 'D'
        Fin Si
    Sino Si a = 10 Entonces
        Si b < 10 Entonces
            Escriba 'E'
        Sino
            Escriba 'F'
        Fin Si
    Fin Si

    a <- 5
    b <- 11
    Si a < 10 Entonces
        Si b < 10 Entonces
            Escriba 'A'
        Sino
            Escriba 'B'
        Fin Si
    Sino Si a > 10 Entonces
        Si b < 10 Entonces
            Escriba 'C'
        Sino
            Escriba 'D'
        Fin Si
    Sino Si a = 10 Entonces
        Si b < 10 Entonces
            Escriba 'E'
        Sino
            Escriba 'F'
        Fin Si
    Fin Si

    a <- 45
    b <- 12
    Si a < 10 Entonces
        Si b < 10 Entonces
            Escriba 'A'
        Sino
            Escriba 'B'
        Fin Si
    Sino Si a > 10 Entonces
        Si b < 10 Entonces
            Escriba 'C'
        Sino
            Escriba 'D'
        Fin Si
    Sino Si a = 10 Entonces
        Si b < 10 Entonces
            Escriba 'E'
        Sino
            Escriba 'F'
        Fin Si
    Fin Si

    a <- 10
    b <- 13
    Si a < 10 Entonces
        Si b < 10 Entonces
            Escriba 'A'
        Sino
            Escriba 'B'
        Fin Si
    Sino Si a > 10 Entonces
        Si b < 10 Entonces
            Escriba 'C'
        Sino
            Escriba 'D'
        Fin Si
    Sino Si a = 10 Entonces
        Si b < 10 Entonces
            Escriba 'E'
        Sino
            Escriba 'F'
        Fin Si
    Fin Si
Fin)";

const char *test_caso1_src =
R"(Entero a

Inicio
    a <- 10
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 11
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 12
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 13
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 14
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 15
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 16
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 17
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 18
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 19
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 20
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 76
    caso a
        10: Escriba 'A'
        11: Escriba 'B'
        12: Escriba 'C'
        13: Escriba 'D'
        14: Escriba 'E'
        15: Escriba 'F'
        16: Escriba 'G'
        17: Escriba 'H'
        18: Escriba 'I'
        19: Escriba 'J'
        20: Escriba 'K'
        Sino:
            Escriba 'Z'
    fin caso
Fin)";

const char *test_caso2_src =
R"(Entero a

Inicio
    a <- 10
    caso a
        10 -> 19: Escriba 'A'
        20 -> 29: Escriba 'B'
        30 -> 39: Escriba 'C'
        40 -> 49: Escriba 'D'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 23
    caso a
        10 -> 19: Escriba 'A'
        20 -> 29: Escriba 'B'
        30 -> 39: Escriba 'C'
        40 -> 49: Escriba 'D'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 35
    caso a
        10 -> 19: Escriba 'A'
        20 -> 29: Escriba 'B'
        30 -> 39: Escriba 'C'
        40 -> 49: Escriba 'D'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 47
    caso a
        10 -> 19: Escriba 'A'
        20 -> 29: Escriba 'B'
        30 -> 39: Escriba 'C'
        40 -> 49: Escriba 'D'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 86
    caso a
        10 -> 19: Escriba 'A'
        20 -> 29: Escriba 'B'
        30 -> 39: Escriba 'C'
        40 -> 49: Escriba 'D'
        Sino:
            Escriba 'Z'
    fin caso
Fin)";

const char *test_caso3_src =
R"(Entero a

Inicio
    a <- 11
    caso a
        10,11,12,13,14,15: Escriba 'A'
        20,21,22,23,24,25: Escriba 'B'
        30,31,32,33,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 23
    caso a
        10,11,12,13,14,15: Escriba 'A'
        20,21,22,23,24,25: Escriba 'B'
        30,31,32,33,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 34
    caso a
        10,11,12,13,14,15: Escriba 'A'
        20,21,22,23,24,25: Escriba 'B'
        30,31,32,33,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 47
    caso a
        10,11,12,13,14,15: Escriba 'A'
        20,21,22,23,24,25: Escriba 'B'
        30,31,32,33,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso
Fin)";

const char *test_caso4_src =
R"(Entero a

Inicio
    a <- 13
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 17
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 23
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 27
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 34
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 38
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 40
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso

    a <- 77
    caso a
        10,11,12,16->19,13,14,15: Escriba 'A'
        20,21,22,26->29,23,24,25: Escriba 'B'
        30,31,32,33,36->39,34,35: Escriba 'C'
        Sino:
            Escriba 'Z'
    fin caso
Fin)";

const char *test_caso5_src =
R"(Caracter a

Inicio
    a <- 'A'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso

    a <- 'B'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso

    a <- 'C'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso

    a <- 'D'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso

    a <- 'E'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso

    a <- 'F'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso

    a <- 'G'
    caso a
        'A': Escriba 10
        'B': Escriba 11
        'C': Escriba 12
        'D': Escriba 13
        'E': Escriba 14
        'F': Escriba 15
        Sino:
            Escriba 99
    fin caso
Fin)";

const char *test_caso6_src =
R"(Caracter a

Inicio
    a <- 'B'
    caso a
        'A' -> 'C': Escriba 10
        'D' -> 'F': Escriba 20
        'G' -> 'I': Escriba 30
        Sino:
            Escriba 40
    fin caso

    a <- 'E'
    caso a
        'A' -> 'C': Escriba 10
        'D' -> 'F': Escriba 20
        'G' -> 'I': Escriba 30
        Sino:
            Escriba 40
    fin caso

    a <- 'H'
    caso a
        'A' -> 'C': Escriba 10
        'D' -> 'F': Escriba 20
        'G' -> 'I': Escriba 30
        Sino:
            Escriba 40
    fin caso

    a <- 'J'
    caso a
        'A' -> 'C': Escriba 10
        'D' -> 'F': Escriba 20
        'G' -> 'I': Escriba 30
        Sino:
            Escriba 40
    fin caso
Fin)";

const char *test_caso7_src =
R"(Caracter a

Inicio
    a <- 'B'
    caso a
        'A','B','C': Escriba 10
        'D','E','F': Escriba 20
        'G','H','I': Escriba 30
        Sino:
            Escriba 40
    fin caso

    a <- 'E'
    caso a
        'A','B','C': Escriba 10
        'D','E','F': Escriba 20
        'G','H','I': Escriba 30
        Sino:
            Escriba 40
    fin caso

    a <- 'H'
    caso a
        'A','B','C': Escriba 10
        'D','E','F': Escriba 20
        'G','H','I': Escriba 30
        Sino:
            Escriba 40
    fin caso

    a <- 'J'
    caso a
        'A','B','C': Escriba 10
        'D','E','F': Escriba 20
        'G','H','I': Escriba 30
        Sino:
            Escriba 40
    fin caso
Fin)";

const char *test_caso8_src =
R"(Caracter a

Inicio
    a <- 'E'
    caso a
        'A','B','C','D' -> 'F': Escriba 10
        'G','H','I','J' -> 'L': Escriba 20
        Sino:
            Escriba 40
    fin caso

    a <- 'B'
    caso a
        'A','B','C','D' -> 'F': Escriba 10
        'G','H','I','J' -> 'L': Escriba 20
        Sino:
            Escriba 40
    fin caso

    a <- 'K'
    caso a
        'A','B','C','D' -> 'F': Escriba 10
        'G','H','I','J' -> 'L': Escriba 20
        Sino:
            Escriba 40
    fin caso

    a <- 'K'
    caso a
        'A','B','C','D' -> 'F': Escriba 10
        'G','H','I','J' -> 'L': Escriba 20
        Sino:
            Escriba 40
    fin caso

    a <- 'M'
    caso a
        'A','B','C','D' -> 'F': Escriba 10
        'G','H','I','J' -> 'L': Escriba 20
        Sino:
            Escriba 40
    fin caso

    a <- 'N'
    caso a
        'A','B','C','D' -> 'F': Escriba 10
        'G','H','I','J' -> 'L': Escriba 20
        Sino:
            Escriba 40
    fin caso
Fin)";

const char *test_lea_src =
R"(Entero i1
Real r1
Caracter c1
Booleano b1
Cadena str

Inicio
    Lea i1
    Escriba i1
    Lea r1
    Escriba r1
    Lea c1
    Escriba c1
    Lea b1
    Escriba b1
    Lea str
    Escriba str
Fin)";

const char *test_aleatorio_src =
R"(Inicio
    Escriba Aleatorio()
    Escriba Aleatorio()
    Escriba Aleatorio()
    Escriba Aleatorio()
    Escriba Aleatorio()
    Escriba Aleatorio()
    Escriba Aleatorio()
    Escriba Aleatorio()
Fin)";

const char *test_caracter_ascii_src =
R"(Inicio
    Escriba Caracter_Ascii(65)
    Escriba Caracter_Ascii(66)
    Escriba Caracter_Ascii(67)
    Escriba Caracter_Ascii(68)
    Escriba Caracter_Ascii(69)
    Escriba Caracter_Ascii(70)
    Escriba Caracter_Ascii(71)
    Escriba Caracter_Ascii(72)
    Escriba Caracter_Ascii(73)
    Escriba Caracter_Ascii(74)
    Escriba Caracter_Ascii(75)
Fin)";

const char *test_valor_ascii_src =
R"(Inicio
    Escriba Valor_Ascii('A')
    Escriba Valor_Ascii('B')
    Escriba Valor_Ascii('C')
    Escriba Valor_Ascii('D')
    Escriba Valor_Ascii('E')
    Escriba Valor_Ascii('F')
    Escriba Valor_Ascii('G')
    Escriba Valor_Ascii('H')
    Escriba Valor_Ascii('I')
    Escriba Valor_Ascii('J')
    Escriba Valor_Ascii('K')
Fin)";

const char *test_entero_a_cadena_src =
R"(Entero a, b, c

Inicio
    a <- 30017
    b <- 10135
    c <- 31509
    Escriba Entero_A_Cadena(26903)
    Escriba Entero_A_Cadena(13667)
    Escriba Entero_A_Cadena(a)
    Escriba Entero_A_Cadena(b)
    Escriba Entero_A_Cadena(c)
Fin)";

const char *test_longitud_cadena_src =
R"(Cadena x

Inicio
    x <- "MjgKNzQxMwo3MjIzCjc2ODAKNzk3CjgxOTAKMTc0NQo0NTA3Cjg0MzAKMTM5Mwo5Njg5CjQ1NTQK"
    x <- x + "ODc4CjM2MTAKMzc4MAozOTEKOTA0CjI1NDIKNjYxMQo1Mjg4Cjk3NTkKNTgKMTUxNAo0OTQyCjYz"

    Escriba longitud(x)
Fin)";

const char *test_real_a_cadena_src =
R"(Real a, b, c

Inicio
    a <- 1.81095
    b <- 1.51261
    c <- 1.78628
    Escriba Real_A_Cadena(a, 5)
    Escriba Real_A_Cadena(b, 5)
    Escriba Real_A_Cadena(c, 5)
    Escriba Real_A_Cadena(1.77054, 5)
    Escriba Real_A_Cadena(1.66394, 5)
Fin)";

const char *test_simple_record_src =
R"(Registro Test
    Entero a
    Entero b
    Entero c
Fin Registro

Test r

Inicio
    r.a <- 4876
    r.b <- 9238
    r.c <- 6582

    Escriba r.a
    Escriba r.b
    Escriba r.c
Fin
)";

const char *test_mixed_record_src =
R"(Registro RTest
    Entero a
    Real b
    Caracter c
    Booleano d
Fin Registro

RTest r

Inicio
    r.a <- 4876
    r.b <- 3.14159
    r.c <- 'A'
    r.d <- Verdadero

    Escriba r.a
    Escriba r.b
    Escriba r.c
    Escriba r.d
Fin

)";

const char *test_mixed_record_string_src =
R"(Registro RTest
    Entero a
    Real b
    Caracter c
    Booleano d
    Cadena str
Fin Registro

RTest r

Inicio
    r.a <- 4876
    r.b <- 3.14159
    r.c <- 'A'
    r.d <- Verdadero
    r.str <- "FUaFy3WWO7EINvEWr0sZ14jyeHzDCOz36HWJKhFQK9t5tlTGU16apizYth8X6j0gbFWHJgXYCp8E7C7D"

    Escriba r.a
    Escriba r.b
    Escriba r.c
    Escriba r.d
    Escriba r.str
Fin


)";

const char *test_record_of_array1_d_int_src =
R"(Registro RTest
    Arreglo [5] De Entero a
    Entero b
    Real c
Fin Registro

RTest r

Inicio
    r.a[1] <- 354
    r.a[2] <- 642
    r.a[3] <- 197
    r.a[4] <- 253
    r.a[5] <- 938
    r.b <- 8527
    r.c <- 3.14159

    Escriba r.a[1]
    Escriba r.a[2]
    Escriba r.a[3]
    Escriba r.a[4]
    Escriba r.a[5]
    Escriba r.b
    Escriba r.c
Fin
)";

const char *test_record_of_array2_d_int_src =
R"(Registro RTest
    Entero b
    Real c
    Arreglo [2,3] De Entero a
Fin Registro

RTest r

Inicio
    r.a[1,1] <- 354
    r.a[1,2] <- 642
    r.a[1,3] <- 197
    r.a[2,1] <- 253
    r.a[2,2] <- 938
    r.a[2,3] <- 459
    r.b <- 8527
    r.c <- 3.14159

    Escriba r.a[1,1]
    Escriba r.a[1,2]
    Escriba r.a[1,3]
    Escriba r.a[2,1]
    Escriba r.a[2,2]
    Escriba r.a[2,3]
    Escriba r.b
    Escriba r.c
Fin
)";

const char *test_record_of_record1_src =
R"(Registro RSub
    Entero a
    Entero b
    Entero c
Fin Registro

Registro RTest
    RSub sr
    Entero b
    Real c
Fin Registro

RTest r

Inicio
    r.sr.a <- 4876
    r.sr.b <- 9238
    r.sr.c <- 6582
    r.b <- 3975
    r.c <- 3.14159

    Escriba r.sr.a
    Escriba r.sr.b
    Escriba r.sr.c
    Escriba r.b
    Escriba r.c
Fin

)";

const char *test_record_of_array_of_array_int_src =
R"(Registro RTest
    Entero b
    Real c
    Arreglo [2] De Arreglo [3] De Entero a
Fin Registro

RTest r

Inicio
    r.a[1][1] <- 354
    r.a[1][2] <- 642
    r.a[1][3] <- 197
    r.a[2][1] <- 253
    r.a[2][2] <- 938
    r.a[2][3] <- 459
    r.b <- 8527
    r.c <- 3.14159

    Escriba r.a[1][1]
    Escriba r.a[1][2]
    Escriba r.a[1][3]
    Escriba r.a[2][1]
    Escriba r.a[2][2]
    Escriba r.a[2][3]
    Escriba r.b
    Escriba r.c
Fin
)";

const char *test_mixed_subtype_reg_array_src =
R"(tipo TArr2D es arreglo[2, 3] de entero
tipo TArr1D es arreglo[5] de entero
tipo TArrOfArr es arreglo[2] de arreglo[3] de entero

registro TRec1
	entero a, b
fin registro

registro TRec
	entero a, b
	TArr2D arr_2d
	TArr1D arr_1d
	TArrOfArr arr_arr
	TRec1 reg2
fin registro

TRec x
TRec yy

inicio
	x.arr_2d[1,1] <- 764
	x.arr_2d[1,2] <- 829
	x.arr_2d[1,3] <- 874
	x.arr_2d[2,1] <- 619
	x.arr_2d[2,2] <- 851
	x.arr_2d[2,3] <- 618
	x.arr_1d[1] <- 301
	x.arr_1d[2] <- 314
	x.arr_1d[3] <- 185
	x.arr_1d[4] <- 820
	x.arr_1d[5] <- 133
	x.arr_arr[1][1] <- 764
	x.arr_arr[1][2] <- 829
	x.arr_arr[1][3] <- 874
	x.arr_arr[2][1] <- 619
	x.arr_arr[2][2] <- 851
	x.arr_arr[2][3] <- 618
	x.a <- 559
	x.b <- 979
	x.reg2.a <- 578
	x.reg2.b <- 368
	Escriba x.arr_2d[1,1]
	Escriba x.arr_2d[1,2]
	Escriba x.arr_2d[1,3]
	Escriba x.arr_2d[2,1]
	Escriba x.arr_2d[2,2]
	Escriba x.arr_2d[2,3]
	Escriba x.arr_1d[1]
	Escriba x.arr_1d[2]
	Escriba x.arr_1d[3]
	Escriba x.arr_1d[4]
	Escriba x.arr_1d[5]
	Escriba x.arr_arr[1][1]
	Escriba x.arr_arr[1][2]
	Escriba x.arr_arr[1][3]
	Escriba x.arr_arr[2][1]
	Escriba x.arr_arr[2][2]
	Escriba x.arr_arr[2][3]
	Escriba x.a
	Escriba x.b
	Escriba x.reg2.a
	Escriba x.reg2.b
fin
)";

const char *test_subprg1_src =
R"(Funcion Suma(Entero a, Entero b): Entero
Inicio
    Retorne a + b
Fin

Inicio
    Escriba Suma(379, 837)
Fin


)";

const char *test_subprg2_src =
R"(Procedimiento Suma(Entero a, Entero b)
Inicio
    Escriba a + b
Fin

Inicio
    Llamar Suma(379, 837)
Fin


)";

const char *test_subprg3_src =
R"(Procedimiento Imprime(Cadena a, Cadena b)
Inicio
    Escriba a + ":" + b
Fin

Inicio
    Llamar Imprime("Hola Mundo", "Hello World")
Fin


)";

const char *test_subprg4_src =
R"(Funcion Concatena(Cadena a, Cadena b): Cadena
Inicio
    Retorne a + ":" + b
Fin

Inicio
    Escriba Concatena("Hola Mundo", "Hello World")
Fin


)";

const char *test_subprg5_src =
R"(Entero c

Procedimiento Suma(Entero a, Entero b, var Entero c)
Inicio
    c <- a + b
Fin

Inicio
    Llamar Suma(379, 837, c)
    Escriba c
Fin


)";

const char *test_subprg6_src =
R"(Cadena c

Procedimiento Concatena(Cadena a, Cadena b, var Cadena c)
Inicio
    c <- a + ":" + b
Fin

Inicio
    Llamar Concatena("Hola Mundo", "Hello World", c)
    Escriba c
Fin


)";

const char *test_subprg7_src =
R"(Cadena c

Procedimiento Concatena(Cadena a, Cadena b, Cadena c)
Inicio
    c <- a + ":" + b
Fin

Inicio
    c <- "brqSpDifrAptydtohFxRkHcorGSSVvnvyeCTtuKZqQHIYtBIjSzsJJGFavfn"
    Llamar Concatena("Hola Mundo", "Hello World", c)
    Escriba c
Fin


)";

const char *test_subprg8_src =
R"(Arreglo [5] de Entero x

Procedimiento ModificaArreglo(var Arreglo [5] de Entero a)
Inicio
    a[1] <- 354
    a[2] <- 642
    a[3] <- 197
    a[4] <- 253
    a[5] <- 938
Fin

Inicio
    LLamar ModificaArreglo(x)
    Escriba x[1]
    Escriba x[2]
    Escriba x[3]
    Escriba x[4]
    Escriba x[5]
Fin


)";

const char *test_subprg9_src =
R"(Arreglo [5] de Entero x

Procedimiento NoModificaArreglo(Arreglo [5] de Entero a)
Inicio
    a[1] <- 354
    a[3] <- 197
    a[5] <- 938
    Escriba a[1]
    Escriba a[2]
    Escriba a[3]
    Escriba a[4]
    Escriba a[5]
Fin

Inicio
    x[1] <- 1159
    x[2] <- 1117
    x[3] <- 1624
    x[4] <- 1035
    x[5] <- 1303
    LLamar NoModificaArreglo(x)
    Escriba x[1]
    Escriba x[2]
    Escriba x[3]
    Escriba x[4]
    Escriba x[5]
Fin


)";

const char *test_subprg10_src =
R"(Arreglo [2] de Arreglo[3] De Entero x

Procedimiento NoModificaArreglo(Arreglo [2] de Arreglo[3] De Entero a)
Inicio
    a[1][1] <- 2222
    a[2][1] <- 3333
    Escriba a[1][1]
    Escriba a[1][2]
    Escriba a[1][3]
    Escriba a[2][1]
    Escriba a[2][2]
    Escriba a[2][3]
Fin

Inicio
    x[1][1] <- 1159
    x[1][2] <- 1117
    x[1][3] <- 1624
    x[2][1] <- 1035
    x[2][2] <- 1303
    x[2][3] <- 6923
    LLamar NoModificaArreglo(x)
    Escriba x[1][1]
    Escriba x[1][2]
    Escriba x[1][3]
    Escriba x[2][1]
    Escriba x[2][2]
    Escriba x[2][3]
Fin


)";

const char *test_subprg11_src =
R"(Arreglo [5] de Entero x

Procedimiento ModificaArreglo(var Arreglo [5] de Entero a)
Inicio
    a[1] <- 354
    a[3] <- 197
    a[5] <- 938
    Escriba a[1]
    Escriba a[2]
    Escriba a[3]
    Escriba a[4]
    Escriba a[5]
Fin

Inicio
    x[1] <- 1159
    x[2] <- 1117
    x[3] <- 1624
    x[4] <- 1035
    x[5] <- 1303
    LLamar ModificaArreglo(x)
    Escriba x[1]
    Escriba x[2]
    Escriba x[3]
    Escriba x[4]
    Escriba x[5]
Fin


)";

const char *test_subprg12_src =
R"(Arreglo [2] de Arreglo[3] De Entero x

Procedimiento ModificaArreglo(var Arreglo [2] de Arreglo[3] De Entero a)
Inicio
    a[1][1] <- 2222
    a[2][1] <- 3333
    Escriba a[1][1]
    Escriba a[1][2]
    Escriba a[1][3]
    Escriba a[2][1]
    Escriba a[2][2]
    Escriba a[2][3]
Fin

Inicio
    x[1][1] <- 1159
    x[1][2] <- 1117
    x[1][3] <- 1624
    x[2][1] <- 1035
    x[2][2] <- 1303
    x[2][3] <- 6923
    LLamar ModificaArreglo(x)
    Escriba x[1][1]
    Escriba x[1][2]
    Escriba x[1][3]
    Escriba x[2][1]
    Escriba x[2][2]
    Escriba x[2][3]
Fin


)";

const char *test_subprg13_src =
R"(Registro RTest
    Entero a
    Entero b
    Entero c
Fin Registro

RTest r

Procedimiento ModificaRegistro(var RTest reg)
Inicio
    reg.a <- 4876
    reg.b <- 9238
    reg.c <- 6582
Final

Inicio
    Llamar ModificaRegistro(r)

    Escriba r.a
    Escriba r.b
    Escriba r.c
Fin
)";

const char *test_subprg14_src =
R"(Registro RSub
    Entero a
    Entero b
    Entero c
Fin Registro

Registro RTest
    RSub sr
    Entero b
    Real c
Fin Registro

RTest r

Procedimiento ModificaRegistro(var RTest reg)
Inicio
    reg.sr.a <- 4876
    reg.sr.b <- 9238
    reg.sr.c <- 6582
    reg.b <- 3975
    reg.c <- 3.14159
Fin

Inicio
    Llamar ModificaRegistro(r)
    Escriba r.sr.a
    Escriba r.sr.b
    Escriba r.sr.c
    Escriba r.b
    Escriba r.c
Fin

)";

const char *test_subprg15_src =
R"(Registro RTest
    Entero a
    Real b
    Caracter c
    Booleano d
    Cadena str
Fin Registro

RTest r

Procedimiento ModificaRegistro(var RTest reg)
Inicio
    reg.a <- 4876
    reg.b <- 3.14159
    reg.c <- 'A'
    reg.d <- Verdadero
    reg.str <- "FUaFy3WWO7EINvEWr0sZ14jyeHzDCOz36HWJKhFQK9t5tlTGU16apizYth8X6j0gbFWHJgXYCp8E7C7D"
Fin

Inicio
    Llamar ModificaRegistro(r)
    Escriba r.a
    Escriba r.b
    Escriba r.c
    Escriba r.d
    Escriba r.str
Fin

)";

const char *test_subprg16_src =
R"(Registro RTest
    Entero b
    Real c
    Arreglo [2] De Arreglo [3] De Entero a
Fin Registro

RTest r

Procedimiento ModificaRegistro(var RTest reg)
Inicio
    reg.a[1][3] <- 197
    reg.a[2][1] <- 253
    reg.a[2][2] <- 938
    reg.a[2][3] <- 459
    reg.b <- 8527
    reg.c <- 3.14159

    Escriba reg.a[1][1]
    Escriba reg.a[1][2]
    Escriba reg.a[1][3]
    Escriba reg.a[2][1]
    Escriba reg.a[2][2]
    Escriba reg.a[2][3]
    Escriba reg.b
    Escriba reg.c
Fin

Inicio
    r.a[1][1] <- 354
    r.a[1][2] <- 642
    Llamar ModificaRegistro(r)
    Escriba r.a[1][1]
    Escriba r.a[1][2]
    Escriba r.a[1][3]
    Escriba r.a[2][1]
    Escriba r.a[2][2]
    Escriba r.a[2][3]
    Escriba r.b
    Escriba r.c
Fin

)";

const char *test_subprg17_src =
R"(Entero a, b

Procedimiento Suma
Inicio
    Escriba a + b
Fin

Inicio
    a <- 567
    b <- 765
    Llamar Suma
    a <- 374
    b <- 473
    Llamar Suma
Fin

)";

const char *test_subprg18_src =
R"(Entero a, b

Funcion Suma: Entero
Inicio
    Retorne a + b
Fin

Inicio
    a <- 567
    b <- 765
    Escriba Suma()
    a <- 374
    b <- 473
    Escriba Suma()
Fin

)";

const char *gcd_src =
R"(Entero a, b, c

// Funcion que calcula el maximo comun divisor
Funcion gcd(Entero a, Entero b): Entero
Inicio
    Si b = 0 Entonces
        Retorne a
    Sino
        Retorne gcd(b, a mod b)
    Fin Si
Fin

Inicio
    a <- 134
    b <- 567
    c <- gcd(a, b)
    Escriba c
    a <- 132
    b <- 567
    c <- gcd(a, b)
    Escriba c
    a <- 51492
    b <- 20636
    c <- gcd(a, b)
    Escriba c
    a <- 53316
    b <- 33876
    c <- gcd(a, b)
    Escriba c
    a <- 5416
    b <- 9236
    c <- gcd(a, b)
    Escriba c
    a <- 5416
    b <- 9232
    c <- gcd(a, b)
    Escriba c
    a <- 5406
    b <- 9231
    c <- gcd(a, b)
    Escriba c
    a <- 5395
    b <- 9230
    c <- gcd(a, b)
    Escriba c
Fin)";

const char *fibonacci_src =
R"(Entero f

funcion fibonacci( entero n ):entero
Real i, j, k
inicio
	si (n=0) o (n=1) entonces
		retorne 1
	sino
		retorne fibonacci(n-1) + fibonacci(n-2)
	fin si
fin

inicio
    f <- fibonacci(0)
    Escriba f
    f <- fibonacci(1)
    Escriba f
    f <- fibonacci(2)
    Escriba f
    f <- fibonacci(3)
    Escriba f
    f <- fibonacci(4)
    Escriba f
    f <- fibonacci(5)
    Escriba f
    f <- fibonacci(6)
    Escriba f
    f <- fibonacci(7)
    Escriba f
    f <- fibonacci(8)
    Escriba f
    f <- fibonacci(9)
    Escriba f
    f <- fibonacci(10)
    Escriba f
    f <- fibonacci(11)
    Escriba f
    f <- fibonacci(12)
    Escriba f
    f <- fibonacci(13)
    Escriba f
fin
)";

const char *test_subprg_with_error_src =
R"(funcion Suma(Entero a, Entero b): Entero
Inicio
    Retorne a + b
Fin

funcion Suma(Entero a): Entero
Inicio
    Retorne a + 10
Fin

Inicio
    Escriba Suma(379, 837)
Fin)";

const char *hola_mundo_eout = "Hola Mundo";
const char *int_test_eout = "10";
const char *real_test_eout = "3.14159";
const char *char_test_eout = "A";
const char *bool_test_eout = "VerdaderoFalso";
const char *int_int_add_eout = "92";
const char *int_int_sub_eout = "38";
const char *int_int_mult_eout = "1755";
const char *int_int_div_eout = "2.407407";
const char *int_int_i_div_eout = "2";
const char *int_int_mod_eout = "11";
const char *int_int_pow_eout = "274625";
const char *real_real_add_eout = "68.94159";
const char *real_real_sub_eout = "-62.65841";
const char *real_real_mult_eout = "206.716622";
const char *real_real_div_eout = "20.944808";
const char *real_real_i_div_eout = "21";
const char *real_real_mod_eout = "2";
const char *real_real_pow_eout = "515371.365534";
const char *add_int_real_eout = "68.14159";
const char *add_real_int_eout = "68.14159";
const char *bool_ops_eout = "FalsoVerdaderoVerdaderoVerdaderoFalsoFalsoFalsoVerdaderoVerdaderoFalso";
const char *unary_ops_eout = "-9292";
const char *test_string1_eout = "Hola Mundo Hello World";

const char *test_string2_eout = "OTkxMAo4MDYxCjU2ODUKNzc1NQo2NDIwCjc0NjIKOTk4CjU0MTIKODA5MAo4Nzk1Cj"
                                "IxMwo3MTQzCjMyMzYKMzA5OQozNTQ0CjY3NjMKNjE5MQo5NDg4CjEyODMKNDEwOAoxM"
                                "TExCjM2Nwo3MDg5CjEzMQo4OTEwCjM0NTIKNzQzOQoxMTE3Cjg4NzcKNzE1Mgo5NjY4C"
                                "jkxNzMKMjc1OQo5NjAyCjEwMjMKMjE2CjQ3MTYKOTE2OAo2NDAzCjE3ODUKNzE1MAo3ND"
                                "A4CjE5NTMKOTIwMwozNDc4CjMxMzUKODA5";

const char *test_string3_eout = "ABC";
const char *test_string4_eout = "0123456789ABC";
const char *concat_string_eout = "nuy9hqgrervpLrZaCuBk qopQyzLzEAtGTMABjrzy";
const char *concat_string_char_eout = "nuy9hqgrervpLrZaCuBk C";
const char *test_array1_d_int_eout = "354642197253938";

const char *test_array1_d_string_eout = "oFEwk5i7W6ZS2S4W5vdrBO7GQv7aVzjRZ8m1lvCPHIZyS2Rs1DnzCvtU4T"
                                        "k6OGupKjPrakyYQ2oMhGSeKKBOVT65jkTt32dFg5sv";

const char *test_array2_d_int_eout = "354642197253938459";

const char *test_array2_d_string_eout = "hlceg4Jy5eUs92sqZp104W38JUjTMB2UKlFkMc3qdQtoVAKNprqd9WN8v8"
                                        "aBZLl5u0LaEZUbtPUQYeSz3Q3CgY8lUENkCr8uE4csnsTfPn8bF8pSPI8aP"
                                        "nfROH8u0bxWtGssr3KkqgGhREfINB534oRm1x0moRMtnNlzsCbClwFKD78V"
                                        "zLuZjNsQWiF15w585mgIOp8uB6Dw8Oq4rnhNJB87qvIiGJAg1I4TCWnVbOEwkg5D";

const char *test_array3_d_int_eout = "354642197253938459938459288458902664718464342343380510458283304945547549";

const char *test_array3_d_string_eout = "axZht2g3NNynSV1QWQh4A4jL14TDfI2jWtBzmk8l78PmsmDBcJPzTy92OG"
                                        "soAhvnxDJkqiMUNaVQBRThSUt6jIDupBZYU5vqgX01zgnDwyufCwX13r6S"
                                        "MaA0BwGhvPCFKOXGn5zDHVdyZqIGxNOIJb1M3P8kIQy70YVNqzaAOAGowo"
                                        "Jl35CAeS0L7PrlaDVGKgcAiFszBR5XOGvl30PtuJHpG23VSoz925yMUjIB"
                                        "M1EEvqqEd1P278fvu3YnGGJnvE9Jl5ct1lPxVdWE3e9PQNEuOXgGk1jiDF"
                                        "XDWw24Lk08n6fhP8hfi1UWG1gBLUFg9iVphhWE7ieDqDil6eH6OzqLD78H"
                                        "8o7wIrXioyax5QfIQsj9gh0688qhTsxaDAsimu9c3SYTZtLP7xJMVcH4Sp"
                                        "UcWxFrLgCJiYuJqyLD9RJCd4QJo3ZYNTYIHSXKQEPTvCf684t3Uip06EF5"
                                        "eZp0xiCE0yFWKNSY";

const char *test_array_of_array_int_eout = "354642197253938459";

const char *test_array_of_array_of_array_int_eout = "3546421972539384599384592884589026647184643423"
                                                    "43380510458283304945547549";

const char *test_rel_int_eout = "VerdaderoVerdaderoFalsoFalsoFalsoVerdaderoFalsoFalsoVerdaderoVerdadero"
                                "FalsoVerdaderoFalsoVerdaderoFalsoVerdaderoVerdaderoFalso";

const char *test_rel_real_eout = "VerdaderoVerdaderoFalsoFalsoFalsoVerdaderoFalsoFalsoVerdaderoVerdadero"
                                 "FalsoVerdaderoFalsoVerdaderoFalsoVerdaderoVerdaderoFalso";

const char *test_mientras_eout = "12345678910111213141516171819202122232425262728293031323334353637"
                                 "38394041424344454647484950515253545556575859606162636465666768697"
                                 "07172737475767778798081828384858687888990919293949596979899100";

const char *test_repita_eout = "1234567891011121314151617181920212223242526272829303132333435363738"
                               "3940414243444546474849505152535455565758596061626364656667686970717"
                               "2737475767778798081828384858687888990919293949596979899100";

const char *test_para_eout = "123456789101112131415161718192021222324252627282930313233343536373839"
                             "404142434445464748495051525354555657585960616263646566676869707172737"
                             "475767778798081828384858687888990919293949596979899100";

const char *test_si_eout = "10A100";
const char *test_si_anidado_eout = "ACEBDF";
const char *test_caso1_eout = "ABCDEFGHIJKZ";
const char *test_caso2_eout = "ABCDZ";
const char *test_caso3_eout = "ABCZ";
const char *test_caso4_eout = "AABBCCZZ";
const char *test_caso5_eout = "10111213141599";
const char *test_caso6_eout = "10203040";
const char *test_caso7_eout = "10203040";
const char *test_caso8_eout = "101020204040";

const char *test_lea_eout = 
R"(
134
3.14159
C
Verdadero
Esta es un cadena)";

const char *test_aleatorio_eout = "0.0273130.2469460.8321050.3461540.9664710.9425040.7507910.13351";
const char *test_caracter_ascii_eout = "ABCDEFGHIJK";
const char *test_valor_ascii_eout = "6566676869707172737475";
const char *test_entero_a_cadena_eout = "2690313667300171013531509";
const char *test_longitud_cadena_eout = "152";
const char *test_real_a_cadena_eout = "1.810951.512611.786281.770541.66394";
const char *test_simple_record_eout = "487692386582";
const char *test_mixed_record_eout = "48763.14159AVerdadero";

const char *test_mixed_record_string_eout = "48763.14159AVerdaderoFUaFy3WWO7E"
                                            "INvEWr0sZ14jyeHzDCOz36HWJKhFQK9t5"
                                            "tlTGU16apizYth8X6j0gbFWHJgXYCp8E7C7D";

const char *test_record_of_array1_d_int_eout = "35464219725393885273.14159";
const char *test_record_of_array2_d_int_eout = "35464219725393845985273.14159";
const char *test_record_of_record1_eout = "48769238658239753.14159";
const char *test_record_of_array_of_array_int_eout = "35464219725393845985273.14159";
const char *test_mixed_subtype_reg_array_eout = "764829874619851618301314185820133764829874619851618559979578368";
const char *test_subprg1_eout = "1216";
const char *test_subprg2_eout = "1216";
const char *test_subprg3_eout = "Hola Mundo:Hello World";
const char *test_subprg4_eout = "Hola Mundo:Hello World";
const char *test_subprg5_eout = "1216";
const char *test_subprg6_eout = "Hola Mundo:Hello World";
const char *test_subprg7_eout = "brqSpDifrAptydtohFxRkHcorGSSVvnvyeCTtuKZqQHIYtBIjSzsJJGFavfn";
const char *test_subprg8_eout = "354642197253938";
const char *test_subprg9_eout = "3541117197103593811591117162410351303";
const char *test_subprg10_eout = "222211171624333313036923115911171624103513036923";
const char *test_subprg11_eout = "3541117197103593835411171971035938";
const char *test_subprg12_eout = "222211171624333313036923222211171624333313036923";
const char *test_subprg13_eout = "487692386582";
const char *test_subprg14_eout = "48769238658239753.14159";

const char *test_subprg15_eout = "48763.14159AVerdaderoFUaFy3WWO7EINvEWr0sZ14jyeHzD"
                                 "COz36HWJKhFQK9t5tlTGU16apizYth8X6j0gbFWHJgXYCp8E7C7D";

const char *test_subprg16_eout = "35464219725393845985273.1415935464219725393845985273.14159";
const char *test_subprg17_eout = "1332847";
const char *test_subprg18_eout = "1332847";
const char *gcd_eout = "132836485165";
const char *fibonacci_eout = "1123581321345589144233377";
const char *test_subprg_with_error_eout = "Linea 6: El procedimiento 'Suma' ya fue declarado";