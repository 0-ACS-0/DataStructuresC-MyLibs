#include "array.h"
#include <stdio.h>

struct test_struct{
    uint8_t a;
    uint8_t b;
    uint16_t c;
};

int main(int argc, char ** argv){
    printf("\n--------------------------------------------------------\n");
    printf("---- PRUEBA DE FUNCIONAMIENTO DE LA LIBREARÍA ARRAY ----\n\n");

    // Elementos del array de prueba:
    struct test_struct test1 = (struct test_struct){.a = 2, .b = 4, .c = 512};
    struct test_struct test2 = (struct test_struct){.a = 1, .b = 3, .c = 421};

    // Inicialización de un array genérico:
    array_pt a = array_init(sizeof(struct test_struct));

    // Inserción de elementos en el array:
    array_set(a, &test1, 2);    // Inserción en la posición 2 del array (tercer elemento)
    array_set(a, &test2, 7);    // Inserción en la posición 7 del array (octavo elemento)    
    
    // Información del array:
    printf("Estado del array tras iniciar:\n");
    printf("\t-Capacidad del array: %ld Elementos\n", array_capacity(a));
    printf("\t-Longitud del array: %ld Elementos\n", array_size(a));
    printf("\t-Tamaño del elemento del array: %ld Bytes\n\n", array_element_size(a));

    // Copia de un elemento del array:
    struct test_struct test_rec;
    int pos = 2;
    array_get(a, pos, &test_rec);
    printf("Miembros del elemento recuperado en la posición %d:\n\r", pos);
    printf("a=%d ", test_rec.a);
    printf("b=%d ", test_rec.b);
    printf("c=%d\n ", test_rec.c);

    pos = 7;
    array_get(a, pos, &test_rec);
    printf("Miembros del elemento recuperado en la posición %d:\n\r", pos);
    printf("a=%d ", test_rec.a);
    printf("b=%d ", test_rec.b);
    printf("c=%d\n\n ", test_rec.c);

    // Eliminación de un elemento:
    pos=4;
    array_del(a, pos);
    printf("Estado del array tras eliminar el elemento en la posición %d:\n", pos);
    printf("\t-Capacidad del array: %ld Elementos\n", array_capacity(a));
    printf("\t-Longitud del array: %ld Elementos\n", array_size(a));
    printf("\t-Tamaño del elemento del array: %ld Bytes\n\n", array_element_size(a));

    // Desinicialización del array tras finalizar con su uso:
    array_deinit(a);

    printf("---- FIN DE PRUEBA DE FUNCIONAMIENTO DE LA LIBREARÍA ARRAY ----\n");
    printf("---------------------------------------------------------------\n\n");

    return 0;
}