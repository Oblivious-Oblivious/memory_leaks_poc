#ifndef __LINKED_LIST_BASE_H_
#define __LINKED_LIST_BASE_H_

#include <stdlib.h> /* malloc, calloc, realloc, free */

/**
 * @struct: llnode
 * @desc: A linked list node with a typed object item
 * @param item -> The typed object contained in the linked list node
 * @param next -> The next node on the linked list
 **/
struct llnode {
    void *item;
    struct llnode *next;
};

/**
 * @struct: linked_list
 * @desc: A helper linked list helper struct containing the head node
 * @param length -> The number of elements in the linked list
 * @param head -> The head node of the list
 **/
typedef struct linked_list {
	size_t length;
    struct llnode *head;
} linked_list;

/**
 * @func: linked_list_new
 * @desc: Creates a new linked list instance and initiates the head node
 * @return The newly created typed linked list
 **/
linked_list *linked_list_new(void);

/**
 * @func: linked_list_add
 * @desc: Adds a new node in the linked list
 * @param list -> The list to append to
 * @param obj -> The node to append
 **/
void linked_list_add(linked_list *list, void *obj);

/**
 * @func: linked_list_remove
 * @desc: Finds and removes a node from the list
 * @param list -> The list to remove from
 * @param obj -> The node to remove
 **/
void linked_list_remove(linked_list *list, void *obj);

/**
 * @func: linked_list_free
 * @brief Frees the list structure
 * @param list -> The list to free
 */
void linked_list_free(linked_list *list);

#endif
