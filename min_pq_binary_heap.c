#include "min_pq_binary_heap.h"

struct min_pq_binary_heap *pq_new(size_t max_size) {
    size_t i;
    struct min_pq_binary_heap *self = (struct min_pq_binary_heap*)malloc(sizeof(struct min_pq_binary_heap));
    self->size = 0;
    self->pq = (size_t*)malloc(sizeof(size_t) * max_size + 1);
    self->index = (signed long*)malloc(sizeof(size_t) * max_size + 1);
    self->keys = (vector**)malloc(sizeof(vector*) * max_size + 1);

    for(i = 0; i <= max_size; self->index[i++] = -1);

    return self;
}

bool pq_is_empty(struct min_pq_binary_heap *self) {
    return self->size == 0;
}

bool pq_contains(struct min_pq_binary_heap *self, size_t i) {
    return self->index[i] != -1;
}

vector *pq_get_key(struct min_pq_binary_heap *self, size_t i) {
    return self->keys[i];
}

void pq_change(struct min_pq_binary_heap *self, size_t i, vector *key) {
    self->keys[i] = key;

    pq_fix_up(self, self->index[i]);
    pq_fix_down(self, self->index[i]);
}

void pq_swap_values(struct min_pq_binary_heap *self, size_t a, size_t b) {
    size_t temp = self->pq[a];
    self->pq[a] = self->pq[b];
    self->pq[b] = temp;

    self->index[self->pq[a]] = a;
    self->index[self->pq[b]] = b;
}

bool pq_greater(struct min_pq_binary_heap *self, size_t a, size_t b) {
    return tuple_greater(self->keys[self->pq[a]], self->keys[self->pq[b]]);
}

void pq_fix_up(struct min_pq_binary_heap *self, size_t i) {
    while(i > 1 && (pq_greater(self, i / 2, i))) {
        pq_swap_values(self, i, i / 2);
        i /= 2;
    }
}

void pq_fix_down(struct min_pq_binary_heap *self, size_t i) {
    while(2 * i <= self->size) {
        size_t new_root = 2 * i;

        if(new_root < self->size && (pq_greater(self, new_root, new_root + 1)))
            new_root++;
        if(!(pq_greater(self, i, new_root)))
            break;

        pq_swap_values(self, i, new_root);
        i = new_root;
    }
}

void pq_insert(struct min_pq_binary_heap *self, size_t i, vector *key) {
    self->size++;

    self->index[i] = self->size;
    self->pq[self->size] = i;
    self->keys[i] = key;

    pq_fix_up(self, self->size);
}

size_t pq_get_min(struct min_pq_binary_heap *self) {
    return self->pq[1];
}

size_t pq_delete_min(struct min_pq_binary_heap *self) {
    size_t min = pq_get_min(self);
    pq_swap_values(self, 1, self->size--);

    pq_fix_down(self, 1);

    self->index[min] = -1;
    self->pq[self->size + 1] = -1;

    return min;
}

void pq_print(struct min_pq_binary_heap *self) {
    size_t i;
    for(i = 1; i <= self->size; i++)
        printf("pq[%lu] = %lu, key = (%s,%s)\n",
            i,
            self->pq[i],
            string_get(vector_get(self->keys[self->pq[i]], 0)),
            string_get(vector_get(self->keys[self->pq[i]], 1)));
    for(i = 0; i < self->size; i++)
        printf("index[%lu] = %lu\n", i, self->index[i]);
}

void pq_reset(struct min_pq_binary_heap *self) {
    size_t size = self->size;

    pq_free(self);
    self = pq_new(self->size);
}

void pq_free(struct min_pq_binary_heap *self) {
    vector_free(*(self->keys));
    free(self);
}
