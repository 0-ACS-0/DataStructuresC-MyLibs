#ifndef SLLIST_HEADER
#define SLLIST_HEADER


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
struct sll_node{
    void * data;                // Referencia a los datos.
    struct sll_node * next;     // Referencia al siguiente nodo.
};

struct sll_linkedlist{
    struct sll_node * head;     // Referencia al primer nodo.
    struct sll_node * tail;     // Referencia al último nodo.
    size_t data_size;           // Tamaño (en bytes) de los datos de cada nodo.
    size_t size;                // Tamaño (en nº de nodos) de la lista.
};
/* ---------------------------------------------------------------- */


/* --- Tipos de datos --------------------------------------------- */
/* ---------------------------------------------------------------- */
typedef struct sll_node sll_node_t;
typedef sll_node_t * sll_node_pt;

typedef struct sll_linkedlist sll_linkedlist_t;
typedef sll_linkedlist_t * sll_linkedlist_pt;
/* ---------------------------------------------------------------- */


/* --- Prototipos de funciones ------------------------------------ */
/* ---------------------------------------------------------------- */
// Creación y destrucción de la lista:
sll_linkedlist_pt sllist_init(size_t data_size);
void sllist_deinit(sll_linkedlist_pt list);

// Inserción de elementos:
uint8_t sllist_push_front(sll_linkedlist_pt list, const void * data);
uint8_t sllist_push_back(sll_linkedlist_pt list, const void * data);
uint8_t sllist_insert_at(sll_linkedlist_pt list, const void * data, size_t index);

// Eliminación de elementos:
uint8_t sllist_pop_front(sll_linkedlist_pt list);
uint8_t sllist_remove_at(sll_linkedlist_pt list, size_t index);

// Búsqueda y recorrido:
void * sllist_find(sll_linkedlist_pt list, const void * target, bool (*cmp_fn)(const void *, const void *));
uint8_t sllist_foreach(sll_linkedlist_pt list, void (*fn)(void *));

// Utilidades generales:
bool sllist_is_empty(sll_linkedlist_pt list);
size_t sllist_get_size(sll_linkedlist_pt list);
/* ---------------------------------------------------------------- */

#endif