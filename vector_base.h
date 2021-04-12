#ifndef __VECTOR_BASE_H_
#define __VECTOR_BASE_H_

#include <stdlib.h> /* malloc, calloc, realloc, free */

/* Initial capacity of a vector */
static const size_t vector_init_capacity = 32;

/**
 * @struct: vector
 * @desc: Defines a vector data structure
 * @param items -> A void pointer array that contains the heterogenous elements of the vector
 * @param alloced -> The total capacity of the vector
 * @param length -> The total number of values
 **/
typedef struct vector {
    /* TODO -> USE A TYPED UNION INSTEAD OF VOID POINTERS */
    void **items;
    size_t alloced;
    size_t length;
} vector;

/**
 * @func: vector_new
 * @desc: Initializes a vector data structure
 * @return: The newly created vector
 **/
vector *vector_new(void);

/**
 * @func: vector_add
 * @desc: Adds a new element in the vector
 * @param v -> The vector to use
 * @param item -> The item to add
 * @return The modified vector
 **/
vector *vector_add(vector *v, void *item);

/**
 * @func: vector_set
 * @desc: Set the value of a specific vector index to a new one
 * @param v-> The vector
 * @param index -> The index to set the value of
 * @param item -> The item to set the value as
 * @return The modified vector
 **/
vector *vector_set(vector *v, size_t index, void *item);

/**
 * @func: vector_get
 * @desc: Get the value of a specific vector index
 * @param v -> The vector to use
 * @param index -> The index to get the value of
 * @return The value
 **/
void *vector_get(vector *v, size_t index);

/**
 * @func: vector_delete
 * @desc: Delete a specific vector value by index
 * @param v -> The vector to use
 * @param index -> The index to delete
 * @return The modified vector
 **/
vector *vector_delete(vector *v, size_t index);

/**
 * @func: vector_length
 * @desc: Get the total number of values inserted in the vector
 * @param v -> The vector to use
 * @return: The number of items in the vector
 **/
size_t vector_length(vector *v);

/**
 * @func: vector_free
 * @brief Frees the memory of the vector
 * @param v -> The vector to free
 */
void vector_free(vector *v);

#endif
