#ifndef DLLIST_HEADER
#define DLLIST_HEADER


/* --- Librerías -------------------------------------------------- */
/* ---------------------------------------------------------------- */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
/* ---------------------------------------------------------------- */


/* --- Constantes ------------------------------------------------- */
/* ---------------------------------------------------------------- */
#define MIN_DATA_SIZE 1      // En bytes.
#define MAX_DATA_SIZE 128    // En bytes.
/* ---------------------------------------------------------------- */

/* --- Estructuras de datos---------------------------------------- */
/* ---------------------------------------------------------------- */
struct dll_node{
    void * data;
    struct dll_node * next;
    struct dll_node * prev;
};

struct dll_linkedlist{
    struct dll_node * head;
    struct dll_node * tail;
    size_t data_size;
    size_t size;
};
/* ---------------------------------------------------------------- */


/* --- Tipos de datos --------------------------------------------- */
/* ---------------------------------------------------------------- */
typedef struct dll_node dll_node_t;
typedef dll_node_t * dll_node_pt;

typedef struct dll_linkedlist dll_linkedlist_t;
typedef dll_linkedlist_t * dll_linkedlist_pt;
/* ---------------------------------------------------------------- */


/* --- Prototipos de funciones ------------------------------------ */
/* ---------------------------------------------------------------- */
// Creación y destrucción de la lista:
dll_linkedlist_pt dllist_init(size_t data_size);
void dllist_deinit(dll_linkedlist_pt * list);
void dllist_clear(dll_linkedlist_pt list);

// Inserción de elementos:
uint8_t dllist_push_front(dll_linkedlist_pt list, const void * data);
uint8_t dllist_push_back(dll_linkedlist_pt list, const void * data);
uint8_t dllist_insert_at(dll_linkedlist_pt list, const void * data, size_t index);

// Eliminación de elementos:
uint8_t dllist_pop_front(dll_linkedlist_pt list);
uint8_t dllist_pop_back(dll_linkedlist_pt list);
uint8_t dllist_remove_at(dll_linkedlist_pt list, size_t index);

// Búsqueda e iteración:
void * dllist_find(dll_linkedlist_pt list, const void * target, bool (*cmp_fn)(const void *, const void * ));
uint8_t dllist_foreach(dll_linkedlist_pt list, void (*fn)(void *));

// Utilidades generales:
bool dllist_is_empty(dll_linkedlist_pt list);
size_t dllist_get_size(dll_linkedlist_pt list);
size_t dllist_get_data_size(dll_linkedlist_pt list);
/* ---------------------------------------------------------------- */

#endif