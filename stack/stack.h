#ifndef STACK_HEADER
#define STACK_HEADER


/* --- Librerías -------------------------------------------------- */
/* ---------------------------------------------------------------- */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/* ---------------------------------------------------------------- */


/* --- Constantes ------------------------------------------------- */
/* ---------------------------------------------------------------- */
#define MIN_DATA_SIZE 1     // En bytes.
#define MAX_DATA_SIZE 128   // En bytes.
/* ---------------------------------------------------------------- */


/* --- Estructuras de datos --------------------------------------- */
/* ---------------------------------------------------------------- */
struct stack_node{
    void * data;
    struct stack_node * next;
};

struct stack{
    struct stack_node * top;
    size_t data_size;
    size_t size;
};
/* ---------------------------------------------------------------- */


/* --- Tipos de datos --------------------------------------------- */
/* ---------------------------------------------------------------- */
typedef struct stack_node stack_node_t;
typedef stack_node_t * stack_node_pt;

typedef struct stack stack_t;
typedef stack_t * stack_pt;
/* ---------------------------------------------------------------- */


/* --- Prototipos de funciones ------------------------------------ */
/* ---------------------------------------------------------------- */
// Creación y destrucción del stack:
stack_pt stack_init(size_t data_size);
void stack_deinit(stack_pt * stack);

// Inserción de datos:
uint8_t stack_push(stack_pt stack, void * data);

// Salida de datos:
uint8_t stack_pop(stack_pt stack, void * out_data);
uint8_t stack_peek(stack_pt stack, void * out_data);

// Utilidades:
bool stack_is_empty(stack_pt stack);
size_t stack_get_size(stack_pt stack);
size_t stack_get_data_size(stack_pt stack);
/* ---------------------------------------------------------------- */

#endif