#ifndef __WRITE_HANDLER_BASE_H_
#define __WRITE_HANDLER_BASE_H_

#include <stdio.h>  /* FILE, fopen, fprintf, fclose, printf */
#include <stdlib.h> /* malloc, realloc, free */

#include "Bool.h"

/**
 * @struct write_handler
 * @brief File handler for making write operations more intuitive
 * @param fd -> The current file descriptor
 * @param filepath -> The name of the file to write to
 */
struct write_handler {
    FILE *fd;
    char *filepath;
};

/**
 * @func: write_handler_new
 * @brief Creates a new instance of a write handler
 * @return struct write_handler* -> The newly allocated handler
 */
struct write_handler *write_handler_new();

/**
 * @func: write_handler_open
 * @brief Open a file in write mode
 * @param filepath -> The path to open
 * @return a boolean signaling if the opening was successful
 */
bool write_handler_open(struct write_handler *self, char *filepath);

/**
 * @func: write_handler_write
 * @brief Write a string in the file
 * @param str -> The string to write
 * @return a boolean signaling if the opening was successful
 */
bool write_handler_write(struct write_handler *self, char *str);

/**
 * @func: write_handler_write_line
 * @brief Writes a line in the file
 * @param line -> The line to write
 * @return a boolean signaling if the opening was successful
 */
bool write_handler_write_line(struct write_handler *self, char *line);

/**
 * @func: write_handler_close
 * @brief Attempts to close the buffers to avoid memory overflows
 * @return a boolean signaling if the opening was successful
 */
bool write_handler_close(struct write_handler *self);

#endif
