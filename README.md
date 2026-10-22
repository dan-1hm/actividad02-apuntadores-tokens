# Actividad 2: Apuntadores aplicados al recorrido de tokens en C
**Matrícula:** 10240049
**Nombre:** Daniel Hernández Martínez
**Grupo:** 10SC151
**Objetivo:** Manipular un flujo de tokens mediante apuntadores, estructuras y cursores en memoria.

**Declaración:**
Los tokens fueron escritos manualmente; el programa no realiza análisis léxico ni sintáctico.

## Comandos de Ejecución y Pruebas
**Compilación Normal:**
gcc -std=c11 -Wall -Wextra -Wpedantic src/punteros_tokens.c -o punteros_tokens

**Ejecución Normal (Prueba 2 y 3):**
./punteros_tokens > evidencias/salida-final.txt
(Resultó en estado 0, verificando 12 tokens, 5 líneas corregidas, intervalo vacío 0).

**Prueba con Sanitizadores:**
gcc -std=c11 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g src/punteros_tokens.c -o punteros_tokens_san
./punteros_tokens_san > evidencias/sanitizadores.txt 2>&1
(Resultó en estado_sanitizadores=0, sin fugas de memoria ni comportamiento indefinido).

## Explicación breve de operadores
* **& (Dirección):** Obtiene la dirección de memoria de una variable.
* **\* (Desreferencia):** Accede al valor almacenado en la dirección que guarda el apuntador.
* **-> (Flecha):** Permite acceder a los campos de una `struct` cuando se utiliza un apuntador a dicha estructura.
* **const:** Protege los datos apuntados para que la función pueda leerlos pero no modificarlos.
* **NULL:** Indica que un apuntador está vacío o es inválido, previniendo segmentations faults.
* **Token \*\*:** Es un doble apuntador que permite modificar permanentemente la dirección hacia la que apunta el apuntador original (`Token *`).

## Preguntas de Razonamiento
**1. Checkpoints 1 y 2: ¿qué diferencia existe entre p_linea, *p_linea y &linea_actual, por qué p_linea = 2 sería incorrecto y por qué avanzar_linea puede modificar la variable original?**
`p_linea` guarda la dirección, `*p_linea` accede al valor en esa dirección y `&linea_actual` obtiene la dirección de la variable. `p_linea = 2` es incorrecto porque intenta asignar un número entero común como si fuera una dirección de memoria, lo cual es inválido. `avanzar_linea` modifica el original porque recibe su dirección física (referencia), alterando directamente el objeto en memoria.

**2. Checkpoint 2: ¿por qué avanzar_linea debe comprobar NULL antes de utilizar *linea?**
Porque si recibe `NULL`, significa que la "tarjeta" está en blanco y no apunta a una dirección válida en memoria. Intentar desreferenciarlo (`*linea`) provocaría una violación de segmento (Segmentation fault) y la caída del programa.

**3. Checkpoint 3: ¿qué función cumple \0, qué expresa const char* y por qué no debe modificarse un literal de cadena?**
`\0` es el terminador que marca el final lógico de una cadena de caracteres. `const char*` expresa que el apuntador solo observará los caracteres pero tiene prohibido sobrescribirlos. Modificar un literal de cadena está prohibido porque estos suelen guardarse en secciones de memoria de solo lectura del sistema.

**4. Checkpoint 4: ¿cuándo se utiliza punto, cuándo se utiliza -> y qué impide const Token * dentro de mostrar_token?**
El punto se usa para acceder a campos en variables de estructura directas (`muestra.linea`), mientras que `->` se usa cuando tenemos un apuntador a una estructura (`p_token->linea`). El uso de `const Token *` en `mostrar_token` impide estrictamente que la función sobrescriba accidentalmente la información del token que solo debería imprimir.

**5. Checkpoint 5: ¿cómo calcula la cantidad sizeof flujo / sizeof flujo[0] y por qué fin puede compararse, pero no desreferenciarse?**
Divide el total de bytes que ocupa el arreglo entero en la memoria entre los bytes que ocupa un solo elemento, obteniendo el total de registros. `fin` puede compararse porque sirve como una "señal de límite" matemática, pero no desreferenciarse porque apunta a un bloque vacío de memoria contiguo, donde ya no existe ninguna estructura válida.

**6. Checkpoint 6: ¿por qué contar_tipo puede mover una copia de inicio, mientras avanzar_cursor necesita const Token **? Explica &cursor, *cursor, (*cursor)++ y el uso de (void).**
`contar_tipo` solo necesita observar, así que mover una copia (`Token *`) localmente no afecta el exterior. `avanzar_cursor` necesita modificar permanentemente el cursor en `main`, por lo que exige su dirección con `Token **`. `&cursor` es esa dirección, `*cursor` desreferencia para alcanzar el apuntador original, y `(*cursor)++` lo desplaza. El `(void)` le dice explícitamente al compilador que descarte el retorno de la función, silenciando advertencias.

**7. Checkpoints 7 y 8: ¿qué debes comprobar antes de utilizar el resultado de buscar_primero y por qué corregir_lineas recibe Token* en lugar de const Token *?**
Se debe comprobar obligatoriamente si el resultado es `!= NULL` antes de acceder a sus campos con `->` para evitar caídas. `corregir_lineas` recibe `Token*` sin `const` precisamente porque su propósito nativo es mutar el campo `.linea` del objeto.

**8. Cierre: ¿cómo se relaciona el cursor con el consumo de tokens de un analizador sintáctico y por qué esta práctica no construye un analizador léxico ni sintáctico?**
El cursor simula el "dedo" del analizador sintáctico avanzando sobre el arreglo de tokens conformé va comprobando reglas. No construye las fases porque no fragmenta texto (el léxico ya se simuló metiendo los tokens a mano) y no valida gramática libre de contexto, limitándose solo al avance mecánico de la memoria.

## URL del repositorio
https://github.com/dan-1hm/actividad02-apuntadores-tokens.git
 
