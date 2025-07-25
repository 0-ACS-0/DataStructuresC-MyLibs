#ifndef ARRAY_HEADER
#define ARRAY_HEADER


/* --- Librerías -------------------------------------------------- */
/* ---------------------------------------------------------------- */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* ---------------------------------------------------------------- */


/* --- Constantes ------------------------------------------------- */
/* ---------------------------------------------------------------- */
#define MIN_ELEMENT_SIZE 1      // En bytes.
#define MAX_ELEMENT_SIZE 64     // En bytes.
#define ALLOC_BLOCK_SIZE 32     // En número de elementos (no bytes).
/* ---------------------------------------------------------------- */


/* --- Estructuras de datos---------------------------------------- */
/* ---------------------------------------------------------------- */
struct array{
    void * arr;             // Puntero al array.
    size_t element_size;    // Tamaño (bytes) del elemento del array.
    size_t capacity;        // Capacidad total del array (número de elementos).
    size_t size;            // Tamaño (número de elementos) del array actual.
};
/* ---------------------------------------------------------------- */


/* --- Tipos de datos --------------------------------------------- */
/* ---------------------------------------------------------------- */
typedef struct array array_t;
typedef array_t * array_pt;
/* ---------------------------------------------------------------- */


/* --- Prototipos de funciones ------------------------------------ */
/* ---------------------------------------------------------------- */
array_pt array_init(size_t element_size);
void array_deinit(array_pt array);
uint8_t array_set(array_pt array, const void * element, size_t index);
uint8_t array_get(const array_pt array, size_t index, void * element);
uint8_t array_del(array_pt array, size_t index);
size_t array_size(const array_pt array);
size_t array_element_size(const array_pt array);
size_t array_capacity(const array_pt array);
/* ---------------------------------------------------------------- */

#endif