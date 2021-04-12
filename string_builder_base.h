#ifndef __STRING_BUILDER_BASE_H_
#define __STRING_BUILDER_BASE_H_

#include <stdlib.h> /* malloc, calloc, free */
#include <string.h> /* memcpy, strlen */
#include <stdarg.h> /* va_args, va_start, va_end */
#include "Bool.h"
#include "linked_list_base.h"
#include "vector_base.h"

typedef struct _string {
	linked_list *list;
	size_t length;
} string;

/**
 * @func: string_new
 * @desc: Create an str builder
 * @param initial_string -> The initial string to set
 * @return The str builder
 **/
string *string_new(char *initial_string);

/**
 * @func: string_add_str
 * @desc: Add a string to the builder
 * @param sb -> The string builder to use
 * @param str -> The string to add
 * @param len -> The length of the string to add.
 *              If 0, strlen will be called internally to determine length
 **/
void string_add(string *sb, const char *str);

/**
 * @func: string_addf
 * @brief Adds a formatted string into the builder
 * @param sb -> The str builder ot add to
 * @param f -> The format string to use
 * @param ... -> The rest of the arguments
 */
void string_addf(string *sb, const char *f, ...);

/**
 * @func: string_get
 * @desc: A pointer to the internal buffer with the builder's stirng data
 * @param sb -> The string builder to use
 * @return A pointer to the internal string data
 **/
char *string_get(string *sb);

/**
 * @func: string_shorten
 * @desc: Remove data from the end of the builder
 * @param sb -> The string builder to use
 * @param len -> The new length of the string, anything after this length is removed
 **/
void string_shorten(string *sb, size_t len);

/**
 * @func: string_delete
 * @desc: Clear the builder
 * @param sb -> The string builder to use
 **/
void string_delete(string *sb);

/**
 * @func: string_skip
 * @desc: Remove data from the beginning of the builder
 * @param sb -> The string builder to use
 * @param len -> The length to remove
 **/
void string_skip(string *sb, size_t len);

/**
 * @func: string_length
 * @desc: The length of the string contained in the builder
 * @param sb -> The string builder to use
 * @return The current length of the string
 **/
size_t string_length(string *sb);

/**
 * @func: string_equals
 * @desc: Checks if the char pointers of the two strings passed are the same
 * @param sb -> The first string
 * @param other -> The second string
 * @return A boolean signaling if the strings are equal
 **/
unsigned char string_equals(string *sb, string *other);

/**
 * @func: string_free
 * @brief Frees the memory of the string
 * @param sb -> The string to free
 */
void string_free(string *sb);

/**
 * @func: string_split
 * @desc: Splits a string to a spesific delimeter
 * @param str -> The string to split
 * @param delimeter -> The string delimeter
 * @return A vector with the string tokens
 **/
vector *string_split(string *str, string *delimeter);

#endif
