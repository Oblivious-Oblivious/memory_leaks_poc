#include "vector_base.h"

#define GOLDEN_MEAN 1.618

/**
 * @func: vector_ensure_space
 * @desc: Ensure there is enough space for our values in the vector
 * @param v -> The vector to use
 * @param capacity -> The new capacity to set
 **/
static void vector_ensure_space(vector *v, size_t capacity) {
    void **items = NULL;
    
    if(v == NULL || capacity == 0) return;

    /* Attempt to reallocate new memory in the items list */
    items = realloc(v->items, sizeof(void*) * capacity);

    if(items) {
        /* Reset the items in the new memory space */
        v->items = items;
        v->alloced = capacity;
    }
}

vector *vector_new(void) {
    vector *v = (vector*)malloc(sizeof(vector));
    v->alloced = vector_init_capacity;
    v->length = 0;
    v->items = (void**)malloc(sizeof(void*) * v->alloced);
    return v;
}

vector *vector_add(vector *v, void *item) {
    /* TODO We allow NULL elements (NOT TESTED) */
    if(v == NULL) return v;
    if(v->alloced == v->length)
        vector_ensure_space(v, v->alloced * GOLDEN_MEAN);
    v->items[v->length++] = item;

    return v;
}

vector *vector_set(vector *v, size_t index, void *item) {
    if(v == NULL) return v;
    if(index < v->length)
        v->items[index] = item;
    
    return v;
}

void *vector_get(vector *v, size_t index) {
    if(v == NULL) return NULL;
    if(index < v->length)
        return v->items[index];
    
    /* TODO -> FIX NULLITY */
    return NULL;
}

vector *vector_delete(vector *v, size_t index) {
    size_t i;
    size_t vlen;
    
    if(v == NULL) return v;
    if(index >= v->length) return v;
    
    v->items[index] = NULL;

    /* Reset the rest of the elements forwards */
    vlen = vector_length(v);
    for(i = index; i < vlen - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->length--;

    if(v->length > 0 && v->length == v->alloced / 4)
        vector_ensure_space(v, v->alloced / GOLDEN_MEAN);
    
    return v;
}

size_t vector_length(vector *v) {
    if(v == NULL) return 0;
    return v->length;
}

void vector_free(vector *v) {
    /* TODO -> IMPLEMENT A CUSTOM FREE METHOD FOR ARRAY ELEMENTS */
    if(v != NULL && v->items != NULL)
        free(v->items);
    if(v != NULL)
        free(v);
}
