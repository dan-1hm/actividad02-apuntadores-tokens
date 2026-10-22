/* Matricula: 10240049
Nombre: Daniel Hernández Martínez
Actividad 2 Apuntadores y tokens */

#include <stddef.h>
#include <stdio.h>

typedef enum {
    INT, ID, ASIGNA, LIT_INT,
    PUNTOCOMA, PRINT, PARIZQ, PARDER,
    DESCONOCIDO
} TipoToken;

typedef struct {
    TipoToken tipo;
    const char *lexema;
    int linea;
} Token;

int avanzar_linea(int *linea) {
    if (linea == NULL) {
        return 0;
    }
    (*linea)++;
    return 1;
}

size_t longitud_lexema(const char *texto) {
    const char *cursor;
    size_t longitud = 0;
    if (texto == NULL) return 0;
    cursor = texto;
    while (*cursor != '\0') {
        cursor++;
        longitud++;
    }
    return longitud;
}

const char *nombre_tipo(TipoToken tipo) {
    switch (tipo) {
        case INT: return "INT";
        case ID: return "ID";
        case ASIGNA: return "ASIGNA";
        case LIT_INT: return "LIT_INT";
        case PUNTOCOMA: return "PUNTOCOMA";
        case PRINT: return "PRINT";
        case PARIZQ: return "PARIZQ";
        case PARDER: return "PARDER";
        case DESCONOCIDO: return "DESCONOCIDO";
    }
    return "DESCONOCIDO";
}

void mostrar_token(const Token *token) {
    const char *lexema;
    if (token == NULL) {
        puts("[token nulo]");
        return;
    }
    lexema = token->lexema != NULL ? token->lexema : "(NULL)";
    printf("[%d] %-11s lexema=%-8s longitud=%zu\n",
           token->linea, nombre_tipo(token->tipo),
           lexema, longitud_lexema(token->lexema));
}

int avanzar_cursor(const Token **cursor, const Token *fin) {
    if (cursor == NULL || *cursor == NULL || fin == NULL) {
        return 0;
    }
    if (*cursor >= fin) return 0;
    (*cursor)++;
    return 1;
}

size_t contar_tipo(const Token *inicio, const Token *fin, TipoToken buscado) {
    size_t total = 0;
    if (inicio == NULL || fin == NULL) return 0;
    while (inicio < fin) {
        if (inicio->tipo == buscado) total++;
        inicio++;
    }
    return total;
}

size_t corregir_lineas(Token *inicio, Token *fin, int nueva_linea) {
    size_t cambios = 0;
    if (inicio == NULL || fin == NULL || nueva_linea < 1) return 0;
    while (inicio < fin) {
        inicio->linea = nueva_linea;
        inicio++;
        cambios++;
    }
    return cambios;
}

const Token *buscar_primero(const Token *inicio, const Token *fin, TipoToken buscado) {
    if (inicio == NULL || fin == NULL) return NULL;
    while (inicio < fin) {
        if (inicio->tipo == buscado) return inicio;
        inicio++;
    }
    return NULL;
}

int main(void) {
    /* Checkpoints 1, 2 y 3 */
    int linea_actual = 1;
    int *p_linea = &linea_actual;
    const char *lexema = "total";
    
    printf("directo=%d | por_puntero=%d | misma_direccion=%s\n",
           linea_actual, *p_linea,
           p_linea == &linea_actual ? "si" : "no");
           
    printf("avance_valido=%d\n", avanzar_linea(p_linea));
    printf("avance_nulo=%d\n", avanzar_linea(NULL));
    printf("despues=%d\n", linea_actual);
    
    printf("lexema=%s | longitud=%zu\n", lexema, longitud_lexema(lexema));
    printf("vacio=%zu | nulo=%zu\n", longitud_lexema(""), longitud_lexema(NULL));

    /* Checkpoints 5, 6, 7 y 8 */
    Token flujo[] = {
        {INT, "int", 1},
        {ID, "total", 1},
        {PUNTOCOMA, ";", 1},
        {ID, "total", 1},
        {ASIGNA, "=", 1},
        {LIT_INT, "42", 1},
        {PUNTOCOMA, ";", 1},
        {PRINT, "print", 1},
        {PARIZQ, "(", 1},
        {ID, "total", 1},
        {PARDER, ")", 1},
        {PUNTOCOMA, ";", 1}
    };
    
    size_t cantidad = sizeof flujo / sizeof flujo[0];
    Token *fin = flujo + cantidad;
    const Token *cursor = flujo;
    const Token *primero;
    
    printf("lineas_corregidas=%zu\n", corregir_lineas(flujo + 7, fin, 2));
    
    puts("-- flujo de tokens --");
    while (cursor < fin) {
        mostrar_token(cursor);
        (void)avanzar_cursor(&cursor, fin);
    }
    
    printf("cantidad=%zu\n", cantidad);
    printf("identificadores=%zu\n", contar_tipo(flujo, fin, ID));
    printf("puntos_y_coma=%zu\n", contar_tipo(flujo, fin, PUNTOCOMA));
    printf("avance_en_fin=%d\n", avanzar_cursor(&cursor, fin));
    
    primero = buscar_primero(flujo, fin, PRINT);
    if (primero != NULL) {
        printf("primero_print=%s linea=%d\n", primero->lexema, primero->linea);
    }
    
    primero = buscar_primero(flujo, fin, DESCONOCIDO);
    printf("desconocido=%s\n", primero == NULL ? "no encontrado" : "REVISAR");

    /* Prueba 3: Caso Frontera */
    printf("intervalo_vacio=%zu\n", corregir_lineas(fin, fin, 3));
    
    return 0;
}
