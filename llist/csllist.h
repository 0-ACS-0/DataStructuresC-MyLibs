#ifndef CSLLIST_HEADER
#define CSLLIST_HEADER

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
struct csll_node{
    void * data;                // Referencia a los datos.
    struct csll_node * next;     // Referencia al siguiente nodo.
};

struct csll_linkedlist{
    struct csll_node * head;     // Referencia al primer nodo.
    struct csll_node * tail;     // Referencia al último nodo.
    size_t data_size;           // Tamaño (en bytes) de los datos de cada nodo.
    size_t size;                // Tamaño (en nº de nodos) de la lista.
};
/* ---------------------------------------------------------------- */


/* --- Tipos de datos --------------------------------------------- */
/* ---------------------------------------------------------------- */
typedef struct csll_node csll_node_t;
typedef csll_node_t * csll_node_pt;

typedef struct csll_linkedlist csll_linkedlist_t;
typedef csll_linkedlist_t * csll_linkedlist_pt;
/* ---------------------------------------------------------------- */


/* --- Prototipos de funciones ------------------------------------ */
/* ---------------------------------------------------------------- */
// Creación y destrucción de la lista:
csll_linkedlist_pt csllist_init(size_t data_size);
void csllist_deinit(csll_linkedlist_pt * list);
void csllist_clear(csll_linkedlist_pt list);

// Inserción de elementos:
uint8_t csllist_push_front(csll_linkedlist_pt list, const void * data);
uint8_t csllist_push_back(csll_linkedlist_pt list, const void * data);
uint8_t csllist_insert_at(csll_linkedlist_pt list, const void * data, size_t index);

// Eliminación de elementos:
uint8_t csllist_pop_front(csll_linkedlist_pt list);
uint8_t csllist_remove_at(csll_linkedlist_pt list, size_t index);

// Búsqueda e iteración:
void * csllist_find(csll_linkedlist_pt list, const void * target, bool (*cmp_fn)(const void *, const void *));
uint8_t csllist_foreach(csll_linkedlist_pt list, void (*fn)(void *));

// Utilidades generales:
bool csllist_is_empty(csll_linkedlist_pt list);
size_t csllist_get_size(csll_linkedlist_pt list);
size_t csllist_get_data_size(csll_linkedlist_pt list);
/* ---------------------------------------------------------------- */


#endif