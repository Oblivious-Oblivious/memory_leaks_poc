#ifndef __READ_HANDLER_BASE_H_
#define __READ_HANDLER_BASE_H_

#include <stdio.h>  /* FILE, fopen, fclose, printf */
#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* strcat, strlen, strcpy */

#include "Bool.h"

/**
 * @struct read_handler
 * @brief File handler for making file read operations more intuitive
 * @param fd -> The current file descriptor
 * @param filepath -> The name of the file to read from
 */
struct read_handler {
    FILE *fd;
    char *filepath;
};

/**
 * @func: read_handler
 * @brief Creates a new instance of a read_handler struct
 * @return struct read_handler* -> The newly allocated read_handler
 */
struct read_handler *read_handler_new(void);

/**
 * @func: read_handler_open
 * @brief Open a file in read mode
 * @param filepath -> The path to open
 * @return a boolean signaling if the opening was successful
 */
bool read_handler_open(struct read_handler *self, char *filepath);

/**
 * @func: read_handler_read_line
 * @brief Read a new line from the file descriptor
 * @return The line read
 */
char *read_handler_read_line(struct read_handler *self);

/**
 * @func: read_handler_close
 * @brief Attempts to close the buffers to avoid memory overflows
 */
bool read_handler_close(struct read_handler *self);

#endif
