#ifndef __MIN_PQ_BINARY_HEAP_BASE_H_
#define __MIN_PQ_BINARY_HEAP_BASE_H_

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

#include "Bool.h"

struct min_pq_binary_heap {
    void **A;
    size_t size;
    size_t max_size;
};

/**
 * @func: pq_new
 * @brief Allocated new memory space for the PQ
 * @param max_size -> The maximum size to store
 * @return struct min_pq_binary_heap* -> The newly created object
 */
struct min_pq_binary_heap *pq_new(size_t max_size);

/**
 * 
 * @brief Checks whether the structure is empty or not
 * @param self -> The PQ object
 * @return true -> if empty else false
 */
bool pq_is_empty(struct min_pq_binary_heap *self);

/**
 * @func: pq_get_min
 * @brief Get the minimum element (ON THE MIN_PQ ITS JUST `pq[0]`)
 * @param self -> The PQ object
 * @return void* -> The value of the minimum element
 */
void *pq_get_min(struct min_pq_binary_heap *self);

/**
 * @func: pq_delete_min
 * @brief Deletes the minimum element and fixes the heap
 * @param self -> The PQ object
 * @return void* -> The element deleted
 */
void *pq_delete_min(struct min_pq_binary_heap *self);

/**
 * @func: pq_fix_up
 * @brief Balance the heap upwards
 * @param self -> The PQ object
 * @param i -> The index of the element to fix
 * @param key -> The value of the element to fix
 */
void pq_fix_up(struct min_pq_binary_heap *self, size_t index, void *key);

/**
 * @func: pq_fix
 * @brief Balance the heap downwards
 * @param self -> The PQ object
 * @param i -> The index of the element to fix
 * @param key -> The value of the element to fix
 */
void pq_fix_down(struct min_pq_binary_heap *self, size_t index, void *key);

/**
 * @func: pq_insert
 * @brief Insert a new node on the priory queue
 * @param self -> The PQ object
 * @param key -> The value of the new element
 */
void pq_insert(struct min_pq_binary_heap *self, void *key);

/**
 * @func: pq_print
 * @brief Prints the current elements of the PQ
 * @param self -> The PQ object
 */
void pq_print(struct min_pq_binary_heap *self);

/**
 * @func: pq_reset
 * @brief Resets the priority queue by freeling the structure and reallocating space
 * @param self -> The PQ object
 */
void pq_reset(struct min_pq_binary_heap *self);

/**
 * @func: pq_free
 * @brief Frees the priority queue
 * @param self -> The PQ object
 */
void pq_free(struct min_pq_binary_heap *self);

#endif
