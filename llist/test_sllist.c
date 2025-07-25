#include "sllist.h"
#include <stdio.h>

// Prototipos de funciones:
bool is_double(const void * target, const void * data);
void print_u16_data(void * data);

// Función main:
int main(int argc, char ** argv){

    // Creación de una lista:
    sll_linkedlist_pt list = sllist_init(sizeof(uint16_t));

    // Inserción de datos al frente, cola y en un lugar en específico:
    uint16_t test_data[4] = {64, 128, 255, 512};
    sllist_push_front(list, &test_data[0]);
    sllist_push_back(list, &test_data[1]);
    sllist_insert_at(list, &test_data[2], 1);
    sllist_insert_at(list, &test_data[3], 2);

    // Prueba de funciones de búsqueda:
    uint16_t * num = (uint16_t*)sllist_find(list, &test_data[0], is_double);
    printf("Número encontrado: %d\n\n", *num);
    printf("Lista: [ ");
    sllist_foreach(list, print_u16_data);
    printf("]\n");

    // Eliminación de nodo:
    sllist_pop_front(list);
    sllist_remove_at(list, 2);
    printf("Lista tras eliminar elementos: [ ");
    sllist_foreach(list, print_u16_data);
    printf("]\n");

    // Datos de la lista:
    printf("\nLa lista está vacía: %d\n", sllist_is_empty(list));
    printf("Tamaño de lista: %ld\n", sllist_get_size(list));

    // Destrucción de una lista:
    sllist_deinit(list);

    return 0;
}

/*
    @brief Retorna verdadero si el dato objetivo es la mitad de data.

    @param void * target: Dato objetivo.
    @param void * data: Dato comparativo.

    @retval bool:
                -> false: Si target != data/2
                -> true: Si target == data/2
*/
bool is_double(const void * target, const void * data){
    return (*(uint16_t *)target == *(uint16_t *)data);
}

/*
    @brief Función para imprimir un dato genérico como uint16_t.

    @param void * data: Referencia a los datos.

    @retval None.
*/
void print_u16_data(void * data){
    printf("%d ", *(uint16_t *)data);
}