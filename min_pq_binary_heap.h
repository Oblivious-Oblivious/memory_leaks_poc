#include "tuple_base.h"
#include <assert.h>

/**
 * @struct min_pq_binary_heap
 * @brief A trivial implementation of a min priority queue using a binary heap
 * @param size -> The current size of the pq
 * @param pq -> The array where elements are stored
 * @param index -> The array of indices for the pq
 * @param keys -> The array of keys for the pq
 */
struct min_pq_binary_heap {
    size_t size;
    size_t *pq;
    signed long *index;
    vector **keys;
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
 * @func: pq_contains
 * @brief Checks for the existence of an element in the PQ
 * @param self -> The PQ object
 * @param i -> The index of the element to check
 * @return true -> if exists else false
 */
bool pq_contains(struct min_pq_binary_heap *self, size_t i);

/**
 * @func: pq_get_key
 * @brief Gets the the key of a specified index
 * @param self -> The PQ object
 * @param i -> The index of the element
 * @return vector* -> The value
 */
vector *pq_get_key(struct min_pq_binary_heap *self, size_t i);

/**
 * @func: pq_change
 * @brief Changes the value on an index
 * @param self -> The PQ object
 * @param i -> The index of the element
 * @param key -> The new value
 */
void pq_change(struct min_pq_binary_heap *self, size_t i, vector *key);

/**
 * @func: pq_swap_values
 * @brief Swaps the values on 2 specified indices
 * @param self -> The PQ object
 * @param a -> The first index
 * @param b -> The first index
 */
void pq_swap_values(struct min_pq_binary_heap *self, size_t a, size_t b);

/**
 * @func: pq_greater
 * @brief Checks if the value on an index is greater than the other
 * @param self -> The PQ object
 * @param a -> The first index
 * @param b -> The second index
 * @return true -> if the value is greater else false
 */
bool pq_greater(struct min_pq_binary_heap *self, size_t a, size_t b);

/**
 * @func: pq_fix_up
 * @brief Balance the heap upwards
 * @param self -> The PQ object
 * @param i -> The index of the element to fix
 */
void pq_fix_up(struct min_pq_binary_heap *self, size_t i);

/**
 * @func: pq_fix
 * @brief Balance the heap downwards
 * @param self -> The PQ object
 * @param i -> The index of the element to fi
 */
void pq_fix_down(struct min_pq_binary_heap *self, size_t i);

/**
 * @func: pq_insert
 * @brief Insert a new node on the priory queue
 * @param self -> The PQ object
 * @param i -> The index of the new element
 * @param key -> The value of the new element
 */
void pq_insert(struct min_pq_binary_heap *self, size_t i, vector *key);

/**
 * @func: pq_get_min
 * @brief Get the minimum element (ON THE MIN_PQ ITS JUST `pq[0]`)
 * @param self -> The PQ object
 * @return size_t -> The value of the minimum element
 */
size_t pq_get_min(struct min_pq_binary_heap *self);

/**
 * @func: pq_delete_min
 * @brief Deletes the minimum element and fixes the heap
 * @param self -> The PQ object
 * @return size_t -> The element deleted
 */
size_t pq_delete_min(struct min_pq_binary_heap *self);

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
