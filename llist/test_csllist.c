#include "csllist.h"
#include <stdio.h>

// Prototipos de funciones:
bool is_double(const void * target, const void * data);
void print_u16_data(void * data);

// Función main:
int main(int argc, char ** argv){

    // Creación de una lista:
    csll_linkedlist_pt list = csllist_init(sizeof(uint16_t));

    // Inserción de datos al frente, cola y en un lugar en específico:
    uint16_t test_data[4] = {64, 128, 255, 512};
    csllist_push_front(list, &test_data[0]);
    csllist_push_back(list, &test_data[1]);
    csllist_insert_at(list, &test_data[2], 1);
    csllist_insert_at(list, &test_data[3], 2);

    // Prueba de funciones de búsqueda:
    uint16_t * num = (uint16_t*)csllist_find(list, &test_data[0], is_double);
    printf("Número encontrado: %d\n\n", *num);
    printf("Lista: [ ");
    csllist_foreach(list, print_u16_data);
    printf("] en la dirección (%p)\n", (void *)list);

    // Eliminación de nodo:
    csllist_pop_front(list);
    csllist_remove_at(list, 2);
    printf("Lista tras eliminar elementos: [ ");
    csllist_foreach(list, print_u16_data);
    printf("] en la dirección (%p)\n", (void *)list);

    // Datos de la lista previa a su limpieza:
    printf("\nLa lista está vacía: %d\n", csllist_is_empty(list));
    printf("Tamaño de lista: %ld\n", csllist_get_size(list));
    printf("Tamaño de dato de cada nodo de la lista: %ld\n", csllist_get_data_size(list));

    // Limpieza de la lista:
    csllist_clear(list);

    // Datos de la lista tras limpieza:
    printf("\nLista tras eliminar todos los nodos, en la dirección (%p)\n", (void *)list);
    printf("La lista está vacía: %d\n", csllist_is_empty(list));
    printf("Tamaño de lista: %ld\n", csllist_get_size(list));
    printf("Tamaño de dato de cada nodo de la lista: %ld\n", csllist_get_data_size(list));
    
    // Destrucción de una lista:
    csllist_deinit(&list);

    // Datos de la lista tras destrucción:
    printf("\n Lista tras ser eliminada: (%p)\n", (void *)list);

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