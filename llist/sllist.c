#include "sllist.h"


/* --- Prototipos de funciones internas --------------------------- */
/* ---------------------------------------------------------------- */
static sll_node_pt _sllist_node_init(sll_linkedlist_pt list, const void * data);
static void _sllist_node_deinit(sll_node_pt node);
/* ---------------------------------------------------------------- */



/* --- Implementación de las funciones ---------------------------- */
/* ---------------------------------------------------------------- */
/*
    @brief Función para crear e inicializar (a 0's) una single linked list.

    @param size_t data_size: Tamaño del tipo de dato básico de la lista.

    @retval sll_linkedlist_pt: Puntero a la single linked list creada.
*/
sll_linkedlist_pt sllist_init(size_t data_size){
    // Comprobación de los límites del tamaño del elemento básico de la lista:
    if((data_size < MIN_DATA_SIZE) || (data_size > MAX_DATA_SIZE)){
        return NULL;
    }

    // Reserva de memoria para la estructura básica de la single linked list:
    sll_linkedlist_pt list = (sll_linkedlist_pt)malloc(sizeof(sll_linkedlist_t));
    if (list == NULL){
        return NULL;
    } 

    // Inicio de los miembros de la estructura:
    list->data_size = data_size;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    
    return list;
}

/*
    @brief Función para destruir y liberar una single linked list.

    @param sll_linkedlist_pt list: Referencia a la single linked list.

    @retval None.
*/
void sllist_deinit(sll_linkedlist_pt list){
    // Comprobación de que la lista no sea nula:
    if (list == NULL){
        return;
    }

    // Liberación completa de memoria de la lista:
    sll_node_pt temp_node = list->head;
    sll_node_pt next_node;
    while (temp_node != NULL){
        next_node = temp_node->next;
        _sllist_node_deinit(temp_node);
        temp_node = next_node;
    }

    free(list);
}

/*
    @brief Función para insertar nodos nuevos a la lista en la cabecera.

    @param sll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t sllist_push_front(sll_linkedlist_pt list, const void * data){
    // Comprobación de lista y datos válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo y variables temporales:
    sll_node_pt temp_prev_head_node = list->head;
    sll_node_pt temp_new_head_node = _sllist_node_init(list, data);
    if(temp_new_head_node == NULL){
        return 2;
    }

    // Actualización de la posición de cabecera:
    list->head = temp_new_head_node;
    list->head->next = temp_prev_head_node;

    // Actualización de la posición de cola:
    if (list->tail == NULL){
        list->tail = list->head;
    }

    // Actualización del tamaño de la lista:
    list->size++;

    return 0;

}

/*
    @brief Función para insertar nuevos nodos a la lista en la cola.

    @param sll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t sllist_push_back(sll_linkedlist_pt list, const void * data){
    // Comprobación de lista o datos válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo:
    sll_node_pt temp_new_tail_node = _sllist_node_init(list, data);
    if (temp_new_tail_node == NULL){
        return 2;
    }

    // Actualización de la cola de la lista:
    if (list->tail == NULL){
        list->head = temp_new_tail_node;
        list->tail = temp_new_tail_node;
    } else {
        list->tail->next = temp_new_tail_node;
        list->tail = temp_new_tail_node;
    }

    // Actualización del tamaño de la lista:
    list->size++;

    return 0;
}

/*
    @brief Función para insertar un nodo en una posición arbitraria de la lista.

    @param sll_linkedlist_pt list: Referencia a la lista.
    @param void * data: Referencia a los datos del nuevo nodo.
    @param size_t index: Posición del nuevo nodo en la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nodo.
                -> 3: El índice excede el tamaño de la lista.
*/
uint8_t sllist_insert_at(sll_linkedlist_pt list, const void * data, size_t index){
    // Comprobación de lista, datos e índice válidos:
    if((list == NULL) || (data == NULL)){
        return 1;
    }

    if(index > list->size){
        return 3;
    }

    // Casos especiales (índice = 0 e índice = size)
    if (index == 0){
        return sllist_push_front(list, data);
    }

    if (index == list->size){
        return sllist_push_back(list, data);
    }

    // Creación del nuevo nodo:
    sll_node_pt temp_new_node = _sllist_node_init(list, data);
    if (temp_new_node == NULL){
        return 2;
    }

    // Asignación de referencias cruzadas para inserción del nodo:
    sll_node_pt temp_prev_node = list->head;
    for (size_t i = 0; i < index-1; i++){
        temp_prev_node = temp_prev_node->next;
    }

    temp_new_node->next = temp_prev_node->next;
    temp_prev_node->next = temp_new_node;

    // Actualización del tamaño de la lista:
    list->size++;

    return 0;
}

/*
    @brief Función para eliminar el elemento en la cabecera de la lista.

    @param sll_linkedlist_pt list: Referencia a la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: La lista está vacía.
*/
uint8_t sllist_pop_front(sll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return 1;
    }

    if (list->head == NULL){
        return 2;
    }

    // Actualización del nuevo nodo de cabecera:
    sll_node_pt temp_old_head = list->head;
    list->head = temp_old_head->next;

    // Caso de lista vacía:
    if (list->head == NULL){
        list->tail = NULL;
    } 

    // Destrucción del nodo:
    _sllist_node_deinit(temp_old_head);

    // Actualización del tamaño de la lista:
    list->size--;

    return 0;
}

/*
    @brief Función para eliminar un nodo en una posición dada.

    @param sll_linkedlist_pt list: Referencia a la lista.
    @param size_t index: Posición del nodo a eliminar.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: El índice es superior al tamaño de la lista.
*/
uint8_t sllist_remove_at(sll_linkedlist_pt list, size_t index){
    // Comprobación de lista e índice válidos:
    if (list == NULL){
        return 1;
    }

    if (index >= list->size){
        return 2;
    }

    // Caso especial (index == 0):
    if (index == 0){
        return sllist_pop_front(list);
    }

    // Eliminación del nodo en la posición index y actualización de enlaces:
    sll_node_pt temp_prev_node = list->head;
    sll_node_pt temp_to_delete_node;
    for (size_t i = 0; i < index-1; i++){
        temp_prev_node = temp_prev_node->next;
    }
    temp_to_delete_node = temp_prev_node->next;
    temp_prev_node->next = temp_to_delete_node->next;

    // Caso especial (cola):
    if (list->tail == temp_to_delete_node){
        list->tail = temp_prev_node;
    }

    // Destrucción del nodo:
    _sllist_node_deinit(temp_to_delete_node);

    // Actualización del tamaño de la lista:
    list->size--;

    return 0;
}

/*
    @brief Función que busca y retorna el nodo objetivo dado, con un criterio dado.

    @param sll_linkedlist_pt list: Referencia a la lista.
    @param const void * target: Referencia al dato objetivo que se busca.
    @param bool (*cmp_fn)(const void *, const void *): Referencia a la función que realiza la comparación entre objetivo y buscado.

    @retval void *: Referencia a los datos del nodo encontrado.

*/
void * sllist_find(sll_linkedlist_pt list, const void * target, bool (*cmp_fn)(const void *, const void *)){
    // Comprobación de lista, objetivo y función comparadora válidos:
    if ((list == NULL) || (target == NULL) || (cmp_fn == NULL)){
        return NULL;
    }

    // Recorrido de la lista hasta encontrar:
    sll_node_pt temp_current_node = list->head;
    while (temp_current_node != NULL){
        if(cmp_fn(target, temp_current_node->data)){
            return temp_current_node->data;
        }
        temp_current_node = temp_current_node->next;
    }

    return NULL;
}

/*
    @brief Función que aplica otra función dada a los datos de cada nodo de la lista.

    @param sll_linkedlist_pt list: Referencia a la lista.
    @param void (*fn)(void *): Referencia a la función a aplicar.

    @return uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista o la función no son válidas.
*/
uint8_t sllist_foreach(sll_linkedlist_pt list, void (*fn)(void *)){
    // Comprobación de lista y función comparadora válidos:
    if ((list == NULL) || (fn == NULL)){
        return 1;
    }

    // Recorrido de la lista y aplicación de la función a cada nodo:
    sll_node_pt temp_current_node = list->head;
    while (temp_current_node != NULL){
        fn(temp_current_node->data);
        temp_current_node = temp_current_node->next;
    }

    return 0;
}

/*
    @brief Función que retorna si la lista está o no vacía.

    @param sll_linkedlist_pt list: Referencia a la lista.

    @retval bool:
                -> true: La lista está vacía (o no es válida)
                -> false: La lista no está vacía.
*/
bool sllist_is_empty(sll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return true;
    }

    // Retorno de valor booleano dependiendo del contenido de la lista:
    return (list->head) ? false : true;
}

/*
    @brief Función que retorna el tamaño de la lista.

    @param sll_linkedlist_pt list: Referencia a la lista.

    @retval size_t: Tamaño de la lista.
*/
size_t sllist_get_size(sll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return 0;
    }

    // Retorno del tamaño de la lista:
    return list->size;
}

/* ---------------------------------------------------------------- */








/* --- Implementación de las funciones estáticas ------------------ */
/* ---------------------------------------------------------------- */
/*
    @brief Función interna para crear un nodo de la lista.
    @note: Crea un nodo en cuanto a memoria se refiere, en el contexto de una lista completa se gestionará el cambio de forma externa.
    @note: AL ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param sll_linkedlist_pt list: Referencia a la lista que alojará al nodo.
    @param const void * data: Referencia a los datos que copiar al nodo.

    @retval sll_node_pt: Referencia al nodo creado.
*/
static sll_node_pt _sllist_node_init(sll_linkedlist_pt list, const void * data){
    // Reserva de memoria para el nodo:
    sll_node_pt node = (sll_node_pt)malloc(sizeof(sll_node_t));
    if (node == NULL){
        return NULL;
    }

    node->data = calloc(1, list->data_size);
    if (node->data == NULL){
        free(node);
        return NULL;
    }

    // Copia de los datos al nodo e inicio de miembros de nodo:
    memcpy(node->data, data, list->data_size);
    node->next = NULL;

    return node;
}

/*
    @brief Función interna para eliminar un nodo.
    @note: Elimina un nodo en cuanto a memoria se refiere, en el contexto de una lista completa se gestionará el cambio de forma externa.
    @note: AL ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param sll_node_pt node: Referencia al nodo a destruir.

    @retval None.

*/
static void _sllist_node_deinit(sll_node_pt node){
    // Liberación completa de memoria del nodo:
    free(node->data);
    free(node);
}
/* ---------------------------------------------------------------- */