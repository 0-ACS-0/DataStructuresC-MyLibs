#include "dllist.h"
#include <stdio.h>

// Prototipos de funciones:
bool is_double(const void * target, const void * data);
void print_u16_data(void * data);

// Función main:
int main(int argc, char ** argv){

    // Creación de una lista:
    dll_linkedlist_pt list = dllist_init(sizeof(uint16_t));

    // Inserción de datos al frente, cola y en un lugar en específico:
    uint16_t test_data[4] = {64, 128, 255, 512};
    dllist_push_front(list, &test_data[0]);
    dllist_push_back(list, &test_data[1]);
    dllist_insert_at(list, &test_data[2], 1);
    dllist_insert_at(list, &test_data[3], 2);

    // Prueba de funciones de búsqueda:
    uint16_t * num = (uint16_t*)dllist_find(list, &test_data[0], is_double);
    printf("Número encontrado: %d\n\n", *num);
    printf("Lista: [ ");
    dllist_foreach(list, print_u16_data);
    printf("]\n");

    // Eliminación de nodo:
    dllist_pop_front(list);
    dllist_remove_at(list, 2);
    printf("Lista tras eliminar elementos: [ ");
    dllist_foreach(list, print_u16_data);
    printf("]\n");

    // Datos de la lista:
    printf("\nLa lista está vacía: %d\n", dllist_is_empty(list));
    printf("Tamaño de lista: %ld\n", dllist_get_size(list));
    printf("Tamaño de dato de cada nodo de la lista: %ld\n", dllist_get_data_size(list));

    // Destrucción de una lista:
    dllist_deinit(list);

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