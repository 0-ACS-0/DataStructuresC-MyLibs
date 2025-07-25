#include "array.h"


/* --- Implementación de las funciones ---------------------------- */
/* ---------------------------------------------------------------- */
/*
    @brief Función para crear e inicializar (a 0's) un array dinámico.

    @param size_t element_size: Tamaño del elemento básico del array en bytes.

    @retval array_pt: Puntero al array creado.
*/
array_pt array_init(size_t element_size){
    // Comprobación de los límites del tamaño del elemento básico del array:
    if ((element_size < MIN_ELEMENT_SIZE) || (element_size > MAX_ELEMENT_SIZE)){
        return NULL;
    }

    // Reserva memoria para la estructura básica del array y el array:
    array_pt array = (array_pt)malloc(sizeof(array_t));
    if (array == NULL){
        return NULL;
    }

    array->arr = calloc(ALLOC_BLOCK_SIZE, element_size);
    if (array->arr == NULL){
        free(array);
        return NULL;
    }

    // Inicio de los miembros de la estructura:
    array->element_size = element_size;
    array->capacity = ALLOC_BLOCK_SIZE;
    array->size = 0;

    return array;
}

/*
    @brief Función para destruir y liberar un array dinámico.

    @param array_pt array: Referencia al elemento array a destruir.

    @retval None.
*/
void array_deinit(array_pt array){
    if (array != NULL){
        free(array->arr);
        array->arr = NULL;
        free(array);
    }
}

/*
    @brief Función para añadir un elemento al array, en la posición dada.

    @param array_pt array: Referencia al array.
    @param void * element: Referencia al elemento a almacenar.
    @param size_t index: Posición del array donde almacenar el element.

    @retval uint8_t:
            -> 0: No han ocurrido errores.
            -> 1: El array/elemento no es válido.
            -> 2: Error al ajustar el tamaño del array.
*/
uint8_t array_set(array_pt array,  const void * element, size_t index){
    // Comprobación de array y elemento válido:
    if ((array == NULL) || (element == NULL)){
        return 1;
    }

    // Comprobación del tamaño del array y reajuste si necesario:
    while(index >= array->capacity){

        void * temp_arr = realloc(array->arr, (array->capacity + ALLOC_BLOCK_SIZE) * array->element_size);
        if (temp_arr == NULL){
            return 2;
        }

        array->arr = temp_arr;
        array->capacity += ALLOC_BLOCK_SIZE;
    }

    // Copia del elemento en la posición del array indicada:
    void * target = (uint8_t *)array->arr + (index * array->element_size);
    memcpy(target, element, array->element_size);

    // Actualiza el tamaño del array (si ha variado):
    if (index >= array->size){
        array->size = index + 1;
    }
    return 0;
}

/*
    @brief Función para obtener un elemento de un array, del indice indicado, en la variable indicada.

    @param array_pt array: Referencia al array.
    @param size_t index: Índice del elemento a obtener.
    @param void * element: Referencia a la variable donde se copiará el elemento.

    @retval uint8_t:
            -> 0: No han ocurrido errores.
            -> 1: El array/elemento es nulo.
            -> 2: El índice no es válido.
*/
uint8_t array_get(const array_pt array, size_t index, void * element){
    // Comprobación de array y elemento:
    if ((array == NULL) || (element == NULL)){
        return 1;
    }

    // Comprobación del índice:
    if (index >= array->size){
        return 2;
    }

    // Copia del elemento a la referencia de la variable donde se copiará:
    void * target = (uint8_t *)array->arr + (index * array->element_size);
    memcpy(element, target, array->element_size);

    return 0;
}

/*
    @brief Función para eliminar un elemento del array, en la posición dada.

    @param array_pt array: Referencia al array.
    @param size_t index: Índice del elemento a eliminar.

    @retval uint8_t:
            -> 0: No han ocurrido errores.
            -> 1: Referencia nula al array dado.
            -> 2: Índice no válido.
*/
uint8_t array_del(array_pt array, size_t index){
    // Comprobación de array válido:
    if (array == NULL){
        return 1;
    }

    // Comprobación de índice válido:
    if (index >= array->size){
        return 2;
    }

    // Eliminación del elemento y desplazamiento de los bytes en memoria(si no es el último elemento):
    if (index < (array->size - 1)){
        void * from = (uint8_t *)array->arr + ((index+1) * array->element_size);
        void * to = (uint8_t *)array->arr + (index * array->element_size);
        size_t bytes = (array->size - index - 1) * array->element_size;
        memmove(to, from, bytes);
    }


    // Actualización del tamaño del array (en 1):
    array->size--;

    return 0;
}

/*
    @brief Función que retorna el tamaño del array.

    @param const array_pt array: Referencia al array.

    @retval size_t: Tamaño del array.
*/
size_t array_size(const array_pt array){
    // Comprobación de array válido:
    if (array == NULL){
        return 0;
    }

    return array->size;
}

/*
    @brief Función que retorna el tamaño (en bytes) de un elemento.

    @param const array_pt array: Referencia al array.

    @retval size_t: Tamaño del elemento.
*/
size_t array_element_size(const array_pt array){
    // Comprobación de array válido:
    if (array == NULL){
        return 0;
    }

    return array->element_size;
}

/*
    @brief Función que retorna la capacidad del array.

    @param const array_pt array: Referencia al array.

    @retval size_t: Capacidad del array.
*/
size_t array_capacity(const array_pt array){
    // Comprobación de array válido:
    if (array == NULL){
        return 0;
    }

    return array->capacity;
}
/* ---------------------------------------------------------------- */

