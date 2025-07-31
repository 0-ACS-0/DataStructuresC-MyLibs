#include "csllist.h"


/* --- Prototipos de funciones internas --------------------------- */
/* ---------------------------------------------------------------- */
static csll_node_pt _csllist_node_init(csll_linkedlist_pt list, const void * data);
static void _csllist_node_deinit(csll_node_pt node);
/* ---------------------------------------------------------------- */



/* --- Implementación de las funciones ---------------------------- */
/* ---------------------------------------------------------------- */
/*
    @brief Función para crear e inicializar (a 0's) una circular single linked list.

    @param size_t data_size: Tamaño del tipo de datos básico de la lista.

    @retval csll_linkedlist_pt: Puntero a la circular single linked list creada.
*/
csll_linkedlist_pt csllist_init(size_t data_size){
    // Comprobación de los límites del tamaño del elemento básico de la lista:
    if ((data_size < MIN_DATA_SIZE) || (data_size > MAX_DATA_SIZE)){
        return NULL;
    }

    // Reserva de memoria para la estructura básica de la circular single linked list:
    csll_linkedlist_pt list = (csll_linkedlist_pt)malloc(sizeof(csll_linkedlist_t));
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
    @brief Función para destruir y liberar una circular single linked list.

    @param csll_linkedlist_pt list: Referencia a la circular single linked list.

    @retval None.
*/
void csllist_deinit(csll_linkedlist_pt * list){
    // Comprobación de que la lista no sea nula:
    if ((list == NULL) || (*list == NULL)){
        return;
    }

    // Liberación completa de memoria de la lista:
    csll_node_pt temp_node = (*list)->head;
    csll_node_pt next_node;

    if (temp_node != NULL){
        do {
            next_node = temp_node->next;
            _csllist_node_deinit(temp_node);
            temp_node = next_node;
        } while (temp_node != (*list)->head);
    }


    free(*list);

    // Se establece como lista inválida:
    *list = NULL;
}



/*
    @brief Función para liberar la memoria de los nodos sin liberar la estructura principal.

    @param csll_linkedlist_pt list: Referencia a la lista.

    @retval None.
*/
void csllist_clear(csll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return;
    }

    // Liberación de los nodos de la lista:
    csll_node_pt temp_node = list->head;
    csll_node_pt next_node;

    if (temp_node != NULL){
        do{
            next_node = temp_node->next;
            _csllist_node_deinit(temp_node);
            temp_node = next_node;
        } while (temp_node != list->head);
    }

    // Reinicio de los miembros de la estructura:
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

/*
    @brief Función para insertar nodos nuevos a la lista en la cabecera.

    @param csll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t csllist_push_front(csll_linkedlist_pt list, const void * data){
    // Comprobación de lista y datos válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo y variables temporales:
    csll_node_pt temp_prev_head_node = list->head;
    csll_node_pt temp_new_head_node = _csllist_node_init(list, data);
    if (temp_new_head_node == NULL){
        return 2;
    }

    // Actualización de la posición de cabecera:
    list->head = temp_new_head_node;
    list->head->next = temp_prev_head_node;

    // Actualización de la cola:
    if (list->tail == NULL){
        list->tail = list->head;
    }

    // Actualización del bucle de lista:
    list->tail->next = list->head;

    // Actualización del tamaño de la lista:
    list->size++;

    return 0;
}

/*
    @brief Función para insertar nuevos nodos a la lista en la cola.

    @param csll_linkedlist_pt list: Referencia a la lista.
    @param const void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t csllist_push_back(csll_linkedlist_pt list, const void * data){
    // Comprobación de lista o datos válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo:
    csll_node_pt temp_new_tail_node = _csllist_node_init(list, data);
    if (temp_new_tail_node == NULL){
        return 2;
    }

    // Actualización dd la cola de la lista:
    if (list->tail == NULL){
        list->head = temp_new_tail_node;
        list->tail = temp_new_tail_node;
        list->tail->next = list->head;
    } else {
        list->tail->next = temp_new_tail_node;
        list->tail = temp_new_tail_node;
        list->tail->next = list->head;
    }

    // Actualización del tamaño de la lista:
    list->size++;

    return 0;
}

/*
    @brief Función para insertar un nodo en una posición arbitraria de la lista.

    @param csll_linkedlist_pt list: Referencia a la lista.
    @param void * data: Referencia a los datos del nuevo nodo.
    @param size_t index: Posición del nuevo nodo en la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Lista o datos no válidos.
                -> 2: Error en la creación del nodo.
                -> 3: El índice excede el tamaño de la lista.
*/
uint8_t csllist_insert_at(csll_linkedlist_pt list, const void * data, size_t index){
    // Comprobación de lista, datos e índice válidos:
    if ((list == NULL) || (data == NULL)){
        return 1;
    }

    if (index > list->size){
        return 3;
    }

    // Casos especiales (índice = 0 e índice = size)
    if (index == 0){
        return csllist_push_front(list, data);
    }

    if (index == list->size){
        return csllist_push_back(list, data);
    }

    // Creación del nuevo nodo:
    csll_node_pt temp_new_node = _csllist_node_init(list, data);
    if (temp_new_node == NULL){
        return 2;
    }

    // Asignación de referencias cruzadas para inserción del nodo:
    csll_node_pt temp_prev_node = list->head;
    for (size_t i = 0; i < index-1; i++){
        temp_prev_node = temp_prev_node->next;
    }

    temp_new_node->next = temp_prev_node->next;
    temp_prev_node->next = temp_new_node;

    // Actualización del tamaño de lista:
    list->size++;

    return 0;
}

/*
    @brief Función para eliminar el elemento en la cabecera de la lista.

    @param csll_linkedlist_pt list: Referencia a la lista.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: La lista está vacía.
*/
uint8_t csllist_pop_front(csll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return 1;
    }

    if (list->head == NULL){
        return 2;
    }

    // Actualización del nuevo nodo de cabecera:
    csll_node_pt temp_old_head = list->head;
    list->head = temp_old_head->next;

    // Caso de lista vacía:
    if (list->head == NULL){
        list->tail = NULL;
    }

    // Destrucción del nodo:
    _csllist_node_deinit(temp_old_head);

    // Actualización de referencias:
    if (list->tail != NULL){
        list->tail->next = list->head;
    }

    // Actualización del tamaño de lista:
    list->size--;

    return 0;
}

/*
    @brief Función para eliminar un nodo en una posición dada.

    @param csll_linkedlist_pt list: Referencia a la lista.
    @param size_t index: Posición del nodo a eliminar.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista no es válida.
                -> 2: El índice es superior al tamaño de la lista.
*/
uint8_t csllist_remove_at(csll_linkedlist_pt list, size_t index){
    // Comprobación de lista e índice válidos:
    if (list == NULL){
        return 1;
    }

    if (index >= list->size){
        return 2;
    }

    // Caso especial (index == 0):
    if (index == 0){
        return csllist_pop_front(list);
    }

    // Eliminación del nodo en la posición index y actualización de enlaces:
    csll_node_pt temp_prev_node = list->head;
    csll_node_pt temp_to_delete_node;
    for (size_t i = 0; i < index-1; i++){
        temp_prev_node = temp_prev_node->next;
    }
    temp_to_delete_node = temp_prev_node->next;
    temp_prev_node->next = temp_to_delete_node->next;

    // Caso especial (cola):
    if (list->tail == temp_to_delete_node){
        list->tail = temp_prev_node;
        list->tail->next = list->head;
    }

    // Destrucción del nodo:
    _csllist_node_deinit(temp_to_delete_node);

    // Actualización del tamaño de la lista:
    list->size--;

    return 0;
}

/*
    @brief Función que busca y retorna el nodo objetivo dado, con un criterio dado.

    @param csll_linkedlist_pt list: Referencia a la lista.
    @param const void * target: Referencia al dato objetivo que se busca.
    @param bool (*cmp_fn)(const void *, const void *): Referencia a la función que realiza la comparación entre objetivo y buscado.

    @retval void *: Referencia a los datos del nodo encontrado.
*/
void * csllist_find(csll_linkedlist_pt list, const void * target, bool (*cmp_fn)(const void *, const void *)){
    // Comprobación de lista, objetivo y función comparadora válidos:
    if ((list == NULL) || (target == NULL) || (cmp_fn == NULL)){
        return NULL;
    }

    // Recorrido de la lista hasta encontrar:
    csll_node_pt temp_current_node = list->head;
    if (list->head != NULL){
        do{
            if (cmp_fn(target, temp_current_node->data)){
                return temp_current_node->data;
            }
            temp_current_node = temp_current_node->next;
        }while(temp_current_node != list->head);
    } 

    return NULL;
}   

/*
    @brief Función que aplica otra función dada a los datos de cada nodo de la lista.

    @param csll_linkedlist_pt list: Referencia a la lista.
    @param void (*fn)(void *): Referencia a la función a aplicar.

    @return uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: La lista o la función no son válidas.
*/
uint8_t csllist_foreach(csll_linkedlist_pt list, void (*fn)(void *)){
    // Comprobación de lista y función válidos:
    if ((list == NULL) || (fn == NULL)){
        return 1;
    }

    // Recorrido de la lista y aplicación de la función a cada nodo:
    csll_node_pt temp_current_node = list->head;
    if (list->head != NULL){
        do{
            fn(temp_current_node->data);
            temp_current_node = temp_current_node->next;
        }while(temp_current_node != list->head);
    }

    return 0;
}

/*
    @brief Función que retorna si la lista está o no vacía.

    @param csll_linkedlist_pt list: Referencia a la lista.

    @retval bool:
                -> true: La lista está vacía (o no es válida).
                -> false: La lista no está vacía.
*/
bool csllist_is_empty(csll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return true;
    }

    // Retorno de valor booleano dependiendo del contenido de la lista:
    return (list->head) ? false : true;
}

/*
    @brief Función que retorna el tamaño de la lista.

    @param csll_linkedlist_pt list: Referencia a la lista.

    @retval size_t: Tamaño de la lista.
*/
size_t csllist_get_size(csll_linkedlist_pt list){
    // Comprobación de lista válida:
    if (list == NULL){
        return 0;
    }

    // Retorno del tamaño de la lista:
    return list->size;
}

/*
    @brief Función que retorna el tamaño en bytes de los datos en un nodo.

    @param sll_linkedlist_pt list: Referencia a la lista.

    @retval size_t: Tamaño en bytes de los datos de un nodo de la lista.
*/
size_t csllist_get_data_size(csll_linkedlist_pt list){
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

    @param csll_linkedlist_pt list: Referencia a la lista que alojará al nodo.
    @param const void * data: Referencia a los datos que copiar al nodo.

    @retval csll_node_pt: Referencia al nodo creado.
*/
static csll_node_pt _csllist_node_init(csll_linkedlist_pt list, const void * data){
    // Reserva de memoria para el nodo:
    csll_node_pt node = (csll_node_pt)malloc(sizeof(csll_node_t));
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
    @note: Al ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param csll_node_pt node: Referencia al nodo a destruir.

    @retval None.
*/
static void _csllist_node_deinit(csll_node_pt node){
    // Liberación completa de memoria del nodo:
    free(node->data);
    free(node);
}
/* ---------------------------------------------------------------- */