#include "stack.h"
#include <string.h>



/* --- Prototipos de funciones internas --------------------------- */
/* ---------------------------------------------------------------- */
static stack_node_pt _stack_node_init(stack_pt stack, void * data);
static void _stack_node_deinit(stack_node_pt node);
/* ---------------------------------------------------------------- */


/* --- Implementación de las funciones ---------------------------- */
/* ---------------------------------------------------------------- */
/*
    @brief Función para crear e inicializar (a 0's) una pila.

    @param size_t data_size: Tamaño del tipo de datos básico de la pila.

    @retval stack_pt: Referencia a la pila creada.
*/
stack_pt stack_init(size_t data_size){
    // Comprobación de lis límites del tamaño del elemento básico de la lista:
    if ((data_size < MIN_DATA_SIZE) || (data_size > MAX_DATA_SIZE)){
        return NULL;
    }

    // Reserva de memoria para la estructura básica de la pila:
    stack_pt stack = (stack_pt)malloc(sizeof(stack_t));
    if (stack == NULL){
        return NULL;
    }

    // Inicio de los miembros de la estructura:
    stack->data_size = data_size;
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

/*
    @brief Función para destruir y liberar una pila.

    @param stack_pt * stack: Referencia a la referencia de la pila.

    @retval None.
*/
void stack_deinit(stack_pt * stack){
    // Comprobación de que la lista no sea nula:
    if ((stack == NULL) || (*stack == NULL)){
        return;
    }

    // Liberación comopleta de memoria de la pila:
    stack_node_pt temp_node = (*stack)->top;
    stack_node_pt next_node;
    while (temp_node != NULL){
        next_node = temp_node->next;
        _stack_node_deinit(temp_node);
        temp_node = next_node;
    }

    // Se libera la estructura de la pila y se establece como pila inválida:
    free(*stack);
    *stack = NULL;
}

/*
    @brief Función para introducir un nuevo nodo en la pila.

    @param stack_pt stack: Referencia al stack.
    @param void * data: Referencia a los datos del nuevo nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Stack o datos no válidos.
                -> 2: Error en la creación del nuevo nodo.
*/
uint8_t stack_push(stack_pt stack, void * data){
    // Comprobación de stack y datos válidos:
    if ((stack == NULL) || (data == NULL)){
        return 1;
    }

    // Creación del nuevo nodo de la pila:
    stack_node_pt temp_prev_top_node = stack->top;
    stack_node_pt temp_new_top_node = _stack_node_init(stack, data);
    if (temp_new_top_node == NULL){
        return 2;
    }

    // Actualización de la cabecera de la pila, referencias y miembros:
    stack->top = temp_new_top_node;
    stack->top->next = temp_prev_top_node;
    stack->size++;

    return 0;
}

/*
    @brief Función para recuperar el dato superior de la pila y eliminar el nodo.

    @param stack_pt stack: Referencia a la pila.
    @param void * out_data: Referencia a variable externa donde se copiarán los datos del nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Pila o puntero a variable externa inválidos para la operación.
*/
uint8_t stack_pop(stack_pt stack, void * out_data){
    // Comprobación de lista o puntero a variable externa inválidos:
    if ((stack == NULL) || (out_data == NULL) || (stack->top == NULL)){
        return 1;
    }

    // Copia del dato superior de la pila a la variable externa:
    memcpy(out_data, stack->top->data, stack->data_size);

    // Eliminación del nodo superior:
    stack_node_pt temp_top_node = stack->top;
    stack->top = stack->top->next;
    _stack_node_deinit(temp_top_node);

    // Actualización de tamaño de la pila:
    stack->size--;

    return 0;
}

/*
    @brief Fucnión para recuperar el dato superior de la pila sin eliminar el nodo.

    @param stack_pt stack: Referencia a la pila.
    @param void * out_data: Referencia a variable externa donde se copiarán los datos del nodo.

    @retval uint8_t:
                -> 0: No han ocurrido errores.
                -> 1: Pila o puntero a variable externa inválidos para la operación.
*/
uint8_t stack_peek(stack_pt stack, void * out_data){
    // Comprobación de lista o puntero a variable externa inválidos:
    if ((stack == NULL) || (out_data == NULL) || (stack->top == NULL)){
        return 1;
    }

    // Copia del dato superior de la pila a la variable externa:
    memcpy(out_data, stack->top->data, stack->data_size);

    return 0;
}

/*
    @brief Función que retorna si la lista está o no vacía.

    @param stack_pt stack: Referencia a la pila.

    @retval bool: 
                -> true: La pila está vacía (o no es válida).
                -> false: La lista no está vacía.
*/
bool stack_is_empty(stack_pt stack){
    // Comprobación de stack válida:
    if (stack == NULL){
        return true;
    }

    // Retorno de valor booleano dependiendo del contenido de la pila:
    return (stack->top) ? false : true;
}

/*
    @brief Función que retorna del tamaño de la pila.

    @param stack_pt stack: Referencia de la pila.

    @retval size_t: Tamaño de la pila.
*/
size_t stack_get_size(stack_pt stack){
    // Comprobación de stack válido:
    if (stack == NULL){
        return 0;
    }

    // Retorno del tamaño de la lista:
    return stack->size;
}

/*
    @brief Función que retorna el tamaño en bytes de los datos de un nodo de la pila.

    @param stack_pt stack: Referencia a la pila.

    @retval size_t Tamaño en bytes de los datos de un nodo de la pila.
*/
size_t stack_get_data_size(stack_pt stack){
    // Comprobación de lista válida:
    if (stack == NULL){
        return 0;
    }

    // Retorno del tamaño (en bytes) de los datos por nodo de la pila.
    return stack->data_size;
}
/* ---------------------------------------------------------------- */


/* --- Implementación de las funciones estáticas ------------------ */
/* ---------------------------------------------------------------- */
/*
    @brief Función interna para crear un nodo de la pila.
    @note: Crea un nodo en cuanto a memoria se refiere, en el contexto de una pila completa se gestionará el cambio de forma externa.
    @note: Al ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param stack_pt list: Referencia a la pila donde se alojará el nodo.
    @param const void * data: Referencia a los datos que copiar al nodo.

    @retval stack_node_pt: Referencia al nodo creado.
*/
static stack_node_pt _stack_node_init(stack_pt stack, void * data){
    // Reserva de memoria para el nodo:
    stack_node_pt node = (stack_node_pt)malloc(sizeof(stack_node_t));
    if (node == NULL){
        return NULL;
    }

    // Reserva de memoria para los datos del nodo:
    node->data = calloc(1, stack->data_size);
    if (node->data == NULL){
        free(node);
        return NULL;
    }

    // Copia de los datos al nodo e inicio de miembros de nodo:
    memcpy(node->data, data, stack->data_size);
    node->next = NULL;

    return node;
}

/*
    @brief Función interna para eliminar un nodo de la pila.
    @note: Elimina un nodo en cuanto a memoria se refiere, en el contexto de una pila completa se gestionará el cambio de forma externa.
    @note: Al ser una función de uso interno, se obvian comprobaciones como punteros nulos. (Se suponen presentes en funciones públicas)

    @param stack_node_pt node: Referencia al nodo a destruir.

    @retval None.
*/
static void _stack_node_deinit(stack_node_pt node){
    // Liberación completa de memoria del nodo:
    free(node->data);
    free(node);
}
/* ---------------------------------------------------------------- */