#include "dllist.h"


/* --- Prototipos de funciones internas --------------------------- */
/* ---------------------------------------------------------------- */
static dll_node_pt _dllist_node_init(dll_linkedlist_pt list, const void * data);
static void _dllist_node_deinit(dll_node_pt node);
/* ---------------------------------------------------------------- */




/* --- Implementación de las funciones ---------------------------- */
/* ---------------------------------------------------------------- */
/*
    @brief Función para crear e inicializar (a 0's) una double linked list.

    @param size_t data_size: Tamaño del tipo de dato básico de la lista.

    @retval dll_linkedlist_pt: Puntero a la double linked list creada.
*/
dll_linkedlist_pt dllist_init(size_t data_size){
    // Comprobación de los límites del tamaño del elemento básico de la lista:
    if((data_size < MIN_DATA_SIZE) || (data_size > MAX_DATA_SIZE)){
        return NULL;
    }

    // Reserva de memoria para la estructura básica de la double linked list:
    dll_linkedlist_pt list = (dll_linkedlist_pt)malloc(sizeof(dll_linkedlist_t));
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
    @brief Función para destruir y liberar una double linked list.

    @param dll_linkedlist_pt list: Referencia a la double linked list.

    @retval None.
*/
void dllist_deinit(dll_linkedlist_pt list){
    // Comprobación de que la lista no sea nula:
    if (list == NULL){
        return;
    }

    // Liberación completa de memoria de la lista:
    dll_node_pt temp_node = list->head;
    dll_node_pt next_node;
    while (temp_node != NULL){
        next_node = temp_node->next;
        _dllist_node_deinit(temp_node);
        temp_node = next_node;
    }

    free(list);
}

/*
    @brief Función para insertar nodos nuevos a la lista en la cabecera.

    @param dll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t dllist_push_front(dll_linkedlist_pt list, const void * data){
    // Comprobación de lista y datos válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo y variables temporales:
    dll_node_pt temp_prev_head_node = list->head;
    dll_node_pt temp_new_head_node = _dllist_node_init(list, data);
    if (temp_new_head_node == NULL){
        return 2;
    }

    // Actualización de la posición de cabecera:
    list->head = temp_new_head_node;
    list->head->next = temp_prev_head_node;

    if(list->head->next != NULL){
        list->head->next->prev = temp_new_head_node;
    }

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

    @param dll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t dllist_push_back(dll_linkedlist_pt list, const void * data){
    // Comprobación de lista o datos válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo:
    dll_node_pt temp_new_tail_node = _dllist_node_init(list, data);
    if (temp_new_tail_node == NULL){
        return 2;
    }

    // Actualización de la cola de la lista:
    if (list->tail == NULL){
        list->head = temp_new_tail_node;
        list->tail = temp_new_tail_node;
    } else {
        temp_new_tail_node->prev = list->tail;
        list->tail->next = temp_new_tail_node;
        list->tail = temp_new_tail_node;
    }

    // Actualización del tamaño de la lista:
    list->size++;

    return 0;
}

/*
    @brief Función para insertar un nodo en una posición arbitraria de la lista.

    @param dll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.
    @param size_t index: Posición del nuevo nodo de la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nodo.
                -> 3: El índice excede el tamaño de la lista.
*/
uint8_t dllist_insert_at(dll_linkedlist_pt list, const void * data, size_t index){
    // Comprobación de lista, datos e índice válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    if (index > list->size){
        return 3;
    }

    // Casos especiales (índice = 0 e índice = size)
    if (index == 0){
        return dllist_push_front(list, data);
    }

    if (index == list->size){
        return dllist_push_back(list, data);
    }

    // Creación del nuevo nodo:
    dll_node_pt temp_new_node = _dllist_node_init(list, data);
    if (temp_new_node == NULL){
        return 2;
    }

    // Asignación de referencias cruzadas para inserción del nodo:
    dll_node_pt temp_prev_node = list->head;
    for (size_t i = 0; i < index-1; i++){
        temp_prev_node = temp_prev_node->next;
    }

    temp_new_node->next = temp_prev_node->next;
    temp_new_node->prev = temp_prev_node;
    temp_new_node->next->prev = temp_new_node;

    temp_prev_node->next = temp_new_node;

    // Actualización del tamaño de la lista:
    list->size++;
    
    return 0;
}

/*
    @brief Función para eliminar el elemento en la cabecera de la lista.

    @param dll_linkedlist_pt list: Referencia a la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: La lista está vacía.
*/
uint8_t dllist_pop_front(dll_linkedlist_pt list){
    // Comprobación de lista y cabecera válida:
    if (list == NULL){
        return 1;
    }

    if (list->head == NULL){
        return 2;
    }

    // Actualización del nuevo nodo de cabecera:
    dll_node_pt temp_old_head = list->head;
    list->head = temp_old_head->next;

    // Caso de lista vacía/no vacía:
    if (list->head == NULL){
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }

    // Destrucción del nodo:
    _dllist_node_deinit(temp_old_head);

    // Actualización del tamaño de la lista:
    list->size--;

    return 0;
}

/*
    @brief Función para eliminar el elemento en la cola de la lista.

    @param dll_linkedlist_pt list: Referencia a la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: La lista está vacía.
*/
uint8_t dllist_pop_back(dll_linkedlist_pt list){
    // Comprobación de lista y cola válida:
    if (list == NULL){
        return 1;
    }

    if (list->tail == NULL){
        return 2;
    }

    // Actualización del nuevo nodo de cola:
    dll_node_pt temp_old_tail = list->tail;
    list->tail = temp_old_tail->prev;


    // Caso de lista vacía/no vacía:
    if (list->tail == NULL){
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }

    // Destrucción del nodo:
    _dllist_node_deinit(temp_old_tail);

    // Actualización del tamaño de la lista:
    list->size--;

    return 0;
}

/*
    @brief Función para eliminar un nodo en una posición dada.

    @param dll_linkedlist_pt list: Referencia a la lista.
    @param size_t index: Posición del nodo a eliminar.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: El índice es superior al tamaño de la lista.
*/
uint8_t dllist_remove_at(dll_linkedlist_pt list, size_t index){
    // Comprobación de la lista e índice válidos:
    if (list == NULL){
        return 1;
    }

    if (index >= list->size){
        return 2;
    }

    // Casos especiales (index == 0 / index == list->size-1):
    if (index == 0){
        return dllist_pop_front(list);
    }

    if (index == list->size-1){
        return dllist_pop_back(list);
    }

    // Eliminación del nodo en la posición index y actualización de enlaces:
    dll_node_pt temp_current_node;

    if (index <= list->size / 2){
        temp_current_node = list->head;
        for (size_t i = 0; i < index; i++){
            temp_current_node = temp_current_node->next;
        }
    } else {
        temp_current_node = list->tail;
        for (size_t i = list->size-1; i > index; i--){
            temp_current_node = temp_current_node->prev;
        }
    }

    temp_current_node->prev->next = temp_current_node->next;
    temp_current_node->next->prev = temp_current_node->prev;


    // Destrucción del nodo:
    _dllist_node_deinit(temp_current_node);

    // Actualización del tamaño de la lista:
    list->size--;

    return 0;
}

/*
    @brief Función que busca y retorna el nodo objetivo dado, con un criterio dado.

    @param dll_linkedlist_pt list: Referencia a la lista.
    @param const void * target: Referencia al dato objetivo que se busca.
    @param bool (*cmp_fn)(const void *, const void *): Referencia a la función que realiza la comparación entre objetivo y buscado.

    @retval void *: Referencia a los datos del nodo encontrado.
*/
void * dllist_find(dll_linkedlist_pt list, const void * target, bool (*cmp_fn)(const void *, const void * )){
    // Comprobación de lista, objetivo y función comparadora válidos:
    if ((list == NULL) || (target == NULL) || (cmp_fn == NULL)){
        return NULL;
    }

    // Recorrido de la lista hasta encontrar el nodo:
    dll_node_pt temp_current_node = list->head;
    while (temp_current_node != NULL){
        if (cmp_fn(target, temp_current_node->data)){
            return temp_current_node->data;
        }
        temp_current_node = temp_current_node->next;
    }

    return NULL;
}

/*
    @brief Función que aplica otra función dada a los datos de cada nodo de la lista.

    @param dll_linkedlist_pt list: Referencia a la lista.
    @param void (*fn)(void *): Referencia a la función a aplicar.

    @return uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista o la función no son válidas.
*/
uint8_t dllist_foreach(dll_linkedlist_pt list, void (*fn)(void *)){
    // Comprobación de la lista y función válidos:
    if ((list == NULL) || (fn == NULL)){
        return 1;
    } 

    // Recorrido de la lista y aplicación de la función a cada nodo:
    dll_node_pt temp_current_node = list->head;
    while (temp_current_node != NULL){
        fn(temp_current_node->data);
        temp_current_node = temp_current_node->next;
    }

    return 0;
}

/*
    @brief Función que retorna si la lista está o no vacía.

    @param dll_linkedlist_pt list: Referencia a la lista.

    @retval bool:
                -> true: La lista está vacía (o no es válida).
                -> false: La lista no está vacía.
*/
bool dllist_is_empty(dll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return true;
    }

    // Retorno de valor booleano dependiendo del contenido de la lista:
    return (list->head) ? false : true;
}

/*
    @brief Función que retorna el tamaño de la lista.

    @param dll_linkedlist_pt list: Referencia a la lista.

    @retval size_t: Tamaño de la lista.
*/
size_t dllist_get_size(dll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return 0;
    }

    // Retorno del tamaño de la lista:
    return list->size;
}

/*
    @brief Función que retorna el tamaño en bytes de los datos en un nodo.

    @param dll_linkedlist_pt list: Referencia a la lista.

    @retval size_t: Tamaño en bytes de los datos de un nodo de la lista.
*/
size_t dllist_get_data_size(dll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return 0;
    }

    // Retorno del tamaño (en bytes) de los datos de un nodo de la lista.
    return list->data_size;
}
/* ---------------------------------------------------------------- */








/* --- Implementación de las funciones estáticas ------------------ */
/* ---------------------------------------------------------------- */
/*
    @brief Función interna para crear un nodo de la lista.
    @note: Crea un nodo en cuanto a memoria se refiere, en el contexto de una lista completa se gestionará el cambio de forma externa.
    @note: Al ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param dll_linkedlist_pt list: Referencia a la lista que alojará al nodo.
    @param const void * data: Referencia a los datos que copiar al nodo.

    @retval dll_node_pt: Referencia al nodo creado.
*/
static dll_node_pt _dllist_node_init(dll_linkedlist_pt list, const void * data){
    // Reserva de memoria para el nodo:
    dll_node_pt node = (dll_node_pt)malloc(sizeof(dll_node_t));
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
    node->prev = NULL;

    return node;
}

/*
    @brief Función interna para eliminar un nodo.
    @note: Elimina un nodo en cuanto a memoria se refiere, en el contexto de una lista completa se gestionará el cambio de forma externa.
    @note: Al ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param dll_node_pt node: Referencia al nodo a eliminar.

    @retval None.
*/
static void _dllist_node_deinit(dll_node_pt node){
    // Liberación completa de memoria del nodo:
    free(node->data);
    free(node);
}

/* ---------------------------------------------------------------- */