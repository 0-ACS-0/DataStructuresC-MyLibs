#include "stack.h"
#include <stdio.h>



int main(int argc, char ** argv){
    // Creación de la pila:
    stack_pt stack = stack_init(sizeof(uint8_t));
    printf("\nSe ha creado la pila correctamente en la dirección (%p)\n", (void *)stack);
    printf("\nLa lista está vacía: %d\n", stack_is_empty(stack));
    printf("Tamaño de la lista: %ld elementos.\n", stack_get_size(stack));
    printf("Tamaño de tipo de dato por nodo de la pila: %ld bytes.\n", stack_get_data_size(stack));

    // Inserción de datos en la pila:
    stack_push(stack, "a");
    stack_push(stack, "b");
    stack_push(stack, "c");

    printf("\nEstado de la pila tras la inserción de datos:\n");
    printf("La lista está vacía: %d\n", stack_is_empty(stack));
    printf("Tamaño de la lista: %ld elementos.\n", stack_get_size(stack));
    printf("Tamaño de tipo de dato por nodo de la pila: %ld bytes.\n", stack_get_data_size(stack));

    // Eliminación (o vistazo) de los datos de la pila:
    uint8_t data;
    stack_peek(stack, (void *)&data);
    printf("\nPeek del la cabecera del stack: %d\n", data);
    stack_pop(stack, (void *)&data);
    printf("Primer pop: %d\n", data);
    stack_pop(stack, (void *)&data);
    printf("Segundo pop: %d\n", data);

    printf("\nEstado de la pila tras la eliminación de datos:\n");
    printf("La lista está vacía: %d\n", stack_is_empty(stack));
    printf("Tamaño de la lista: %ld elementos.\n", stack_get_size(stack));
    printf("Tamaño de tipo de dato por nodo de la pila: %ld bytes.\n", stack_get_data_size(stack));

    // Destrucción de la pila:
    stack_deinit(&stack);
    printf("\nDirección de pila tras la eliminación: (%p)\n", (void *)stack);
    return 0;
}