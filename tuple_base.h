#ifndef __TUPLE_BASE_H_
#define __TUPLE_BASE_H_

/* Dependencies */
#include "read_handler_base.h"
#include "write_handler_base.h"
#include "string_base.h"
#include "vector_base.h"

/**
 * @func: tuple_get
 * @brief Craft the tuple for the line read
 * @param h -> The read handler to use
 * @return vector* -> A new vector containing the 2 elements of the tuple
 */
vector *tuple_get(struct read_handler *h);

/**
 * @func: tuple_less
 * @brief Checks for grammatical string inequality for less
 * @param tup1 -> The first tuple
 * @param tup2 -> The second tuple
 * @return true -> If tup1 < tup2 else false
 */
bool tuple_less(vector *tup1, vector *tup2);

/**
 * @func: tuple_greater
 * @brief Checks for grammatical string inequality for greater
 * @param tup1 -> The first tuple
 * @param tup2 -> The second tuple
 * @return true -> If tup1 > tup2 else false
 */
bool tuple_greater(vector *tup1, vector *tup2);

/**
 * @func: tuple_key_equals
 * @brief Checks for grammatical string equality
 * @param tup1 -> The first tuple
 * @param tup2 -> The second tuple
 * @return true -> If tup1 == tup2 else false
 */
bool tuple_key_equals(vector *tup1, vector *tup2);

/**
 * @func: tuple_value_equals
 * @brief Checks for integer equality
 * @param tup1 -> The first tuple
 * @param tup2 -> The second tuple
 * @return true -> If tup1 == tup2 else false
 */
bool tuple_value_equals(vector *tup1, vector *tup2);

/**
 * @func: tuple_eof
 * @brief Figures out if we are at EOF by checking for empty strings
        We assume we read coherent files.
 * @param tup 
 * @return true -> if the first element of the tuple is an empty string else false
 */
bool tuple_eof(vector *tup);

/**
 * @func: tuple_free
 * @brief Frees the memory used for crafting the tuple
 * @param tup -> The tuple to free
 */
void tuple_free(vector *tup);

#endif
