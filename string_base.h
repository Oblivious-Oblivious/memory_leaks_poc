#ifndef __STRING_BASE_H_
#define __STRING_BASE_H_

#include <stdio.h>  /* printf, snprintf */
#include <stdlib.h> /* malloc, calloc, realloc, free */
#include <string.h> /* strlen, strcmp, memmove */
#include <stdarg.h> /* va_start, va_end, va_arg */

#include "Bool.h"
#include "vector_base.h"

/** The initial minimum size of a string **/
static const size_t string_init_capacity = 32;

/**
 * @struct: string
 * @desc: A mutable string of characters used to dynamically build a string.
 * @param str -> The str char* we construct our string into
 * @param alloced -> The total sized allocated for the string
 * @param length -> The total length of the string
 **/
typedef struct string {
    char *str;
    size_t alloced;
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
 * @func: string_addf
 * @brief Adds a formatted string into the builder
 * @param sb -> The str builder ot add to
 * @param f -> The format string to use
 * @param ... -> The rest of the arguments
 */
void string_addf(string *sb, const char *f, ...);

/**
 * @func: string_add_str
 * @desc: Add a string to the builder
 * @param sb -> The string builder to use
 * @param str -> The string to add
 * @param len -> The length of the string to add.
 *              If 0, strlen will be called internally to determine length
 **/
void string_add_str(string *sb, const char *str);

/**
 * @func: string_add_char
 * @desc: Add a character to the builder
 * @param sb -> The string builder to use
 * @param c -> The character to add 
 **/
void string_add_char(string *sb, char c);

/**
 * @func: string_add_int
 * @desc: Add an integer to the builder
 * @param sb -> The string builder to use
 * @param val -> The integer to add
 **/
void string_add_int(string *sb, int val);

/**
 * @func: string_add_double_precision
 * @desc: Add a double to the builder
 * @param sb -> The string builder to use
 * @param val -> The double to add
 **/
void string_add_double_precision(string *sb, double val);

/**
 * @func: string_get
 * @desc: A pointer to the internal buffer with the builder's stirng data
 * @param sb -> The string builder to use
 * @return A pointer to the internal string data
 **/
char *string_get(string *sb);

/**
 * @func: string_get_char_at_index
 * @desc: Accessor to the string characters by index
 * @param sb -> The string builder to use
 * @param index -> The index of the character we want to receive
 * @return The character we searched for
 **/
char string_get_char_at_index(string *sb, size_t index);

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
 * @func: string_identifier
 * @desc: Turns a string into a valid identifier by
 *  converting illegal characters to hex codes
 * @param sb -> The string builder to convert
 * @return A valid char pointer identifier
 **/
char *string_identifier(string *sb);

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
