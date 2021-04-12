#include "linked_list_base.h"

linked_list *linked_list_new(void) {
    linked_list *list = (linked_list*)malloc(sizeof(linked_list));
    list->head = NULL;
    list->length = 0;
    return list;
}

void linked_list_add(linked_list *list, void *item) {
    struct llnode **probe = NULL;
    struct llnode *newnode = NULL;

    if(list == NULL || item == NULL) return;

    /* Use the address to take advantage of a pointer to pointer approach */
    probe = &(list->head);

    /* Create a new node */
    newnode = (struct llnode*)malloc(sizeof(struct llnode));
    newnode->item = (void*)malloc(sizeof(item));
    newnode->item = item;

    /* Traverse to the end of the linked list */
    while(*probe)
        probe = (struct llnode**)&(*probe)->next;

    newnode->next = (struct llnode*)*probe;
    *probe = newnode;
    list->length++;
}

/* TODO -> FIX MEMORY WHEN REMOVING */
void linked_list_remove(linked_list *list, void *item) {
    struct llnode **probe = NULL;

    if(list == NULL || item == NULL) return;

    probe = &(list->head);

    while((*probe) && (*probe)->item != list)
        probe = (struct llnode**)&(*probe)->next;

    *probe = (struct llnode*)((*probe)->next);
}

void linked_list_free(linked_list *list) {
    struct llnode **probe = NULL;
    struct llnode *next = NULL;

    if(list == NULL) return;

    probe = &(list->head);

    while(*probe) {
        next = (*probe)->next;
        free(*probe);
        *probe = next;
    }

    list->head = NULL;
    list->length = 0;
}
