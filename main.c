#include "OPTIONS.h"
#include "tuple_base.h"
#include "min_pq_binary_heap.h"

/* Readers */
static struct read_handler *r_reader = NULL;
static struct write_handler *r_writer = NULL;

/**
 * @func: add_evaluation
 * @brief Adds a evaluation in the output file
 * @param rel -> The relation to add
 */
static void add_evaluation(vector *rel, size_t agg) {
    char buf[32];

    snprintf(buf, sizeof(buf), "%lu", agg);
    write_handler_write(r_writer, string_get(vector_get(rel, 0)));
    write_handler_write(r_writer, "\t");
    write_handler_write(r_writer, buf);
    write_handler_write(r_writer, "\n");

    tuple_free(rel);
}

/**
 * @func: read_tuples_into_memory
 * @brief Reads all tuples into memory for the external sort
 * @return vector* -> The vector of tuples
 */
static vector *read_tuples_into_memory(void) {
    vector *data = vector_new();

    vector *r = tuple_get(r_reader);
    while(!tuple_eof(r)) {
        vector_add(data, r);
        r = tuple_get(r_reader);
    }
    read_handler_close(r_reader);

    return data;
}

/**
 * @func: write_buffer_size_elements_to_vector
 * @brief Partition the array into a smaller vector of BUFFER_SIZE elements
 * @param data -> The vector of tuples to partition
 * @param runs -> The vector containing the partitions
 * @return true -> If there are more elements to partition else false
 */
static bool write_buffer_size_elements_to_vector(vector *data, vector **runs, size_t curr) {
    size_t i;
    vector *part = vector_new();
    for(i = curr * BUFFER_SIZE; (i < (curr + 1)*BUFFER_SIZE); i++) {
        if(i >= vector_length(data)) {
            if(vector_length(part) != 0)
                vector_add(*runs, part);
            return false;
        }

        vector_add(part, vector_get(data, i));
    }

    vector_add(*runs, part);
    return true;
}

static void sort_using_priority_queue(vector **curr_partition) {
    struct min_pq_binary_heap *self;
    size_t i;

    /* TODO -> HANDLE MEMORY REMOVAL FOR DUPLICATES */
    vector *sorted = vector_new();
    size_t curr_len = vector_length(*curr_partition);

    self = pq_new(BUFFER_SIZE);

    for(i = 0; i < curr_len; i++)
        pq_insert(self, i, vector_get(*curr_partition, i));

    while(!pq_is_empty(self)) {
        vector *key = pq_get_key(self, pq_get_min(self));
        vector_add(sorted, key);

        pq_delete_min(self);
    }

    pq_free(self);

    /* Save to the old pointer */
    *curr_partition = sorted;
}

/**
 * @func: create_initial_runs
 * @brief Create the initial runs and store on an in-memory vector
 * @param data -> The vector of tuples
 * @return vector* -> The partitioned vector of vectors of tuples
 */
static vector *create_initial_runs(vector *data) {
    size_t curr_index = 0;
    vector *curr_partition = NULL;
    vector *runs = vector_new();

    /* Partition into a smaller vector of BUFFER_SIZE elements */
    while(write_buffer_size_elements_to_vector(data, &runs, curr_index)) {
        /* Sort the vector */
        curr_partition = vector_get(runs, curr_index);

        /** quicksort(&curr_partition, 0, vector_length(curr_partition)); **/
        sort_using_priority_queue(&curr_partition);
        vector_set(runs, curr_index, curr_partition); /* Set to the sorted partition */

        curr_index++;
    }

    /* Sort the remaining elements after quitting the while loop */
    curr_partition = vector_get(runs, curr_index);

    /** quicksort(&curr_partition, 0, vector_length(curr_partition)); **/
    sort_using_priority_queue(&curr_partition);
    vector_set(runs, curr_index, curr_partition); /* Set to the sorted partition */

    return runs;
}

/**
 * @func: flush_memory_to_output
 * @brief Writes the contents of the PQ into the output file
 * @param memory -> The PQ object
 */
static void flush_memory_to_output(struct min_pq_binary_heap *memory) {
    size_t agg = 0;
    vector *curr = NULL;

    /* Create a dummy tuple */
    vector *prev = vector_new();
    vector_add(prev, string_new(""));
    vector_add(prev, string_new("0"));

    while(true) {
        /* Peek the top of the heap */
        curr = pq_get_key(memory, pq_get_min(memory));
        /* Remove the node */
        pq_delete_min(memory);

        /* If we reach the last node, we insert in any case
            but care for correct aggregation */
        if(pq_is_empty(memory)) {
            if(tuple_key_equals(prev, curr)) {
                agg += (atoi(string_get(vector_get(prev, 1))) + atoi(string_get(vector_get(curr, 1))));
                add_evaluation(curr, agg);
            }
            else {
                if(agg == 0)
                    agg += atoi(string_get(vector_get(curr, 1)));
                add_evaluation(curr, agg);
            }
            break;
        }

        if(tuple_key_equals(prev, curr))
            /* On equal adjacent nodes aggregate the values and move on */
            agg += (atoi(string_get(vector_get(prev, 1))) + atoi(string_get(vector_get(curr, 1))));
        else if(!string_equals(vector_get(prev, 0), string_new(""))) {
            /* No duplicate exists */
            if(agg == 0)
                agg += atoi(string_get(vector_get(prev, 1)));

            add_evaluation(prev, agg);

            /* Reset the accumulator */
            agg = 0;
        }
        /* Keep track of the adjacent */
        prev = curr;
    }

    /* TODO CANT RESET THE MEMORY */
    /*pq_reset(memory);*/
}

/**
 * @func: sort_and_merge_final_endpoints
 * @brief Reads from the output file and merges on parts
 */
static void sort_and_merge_final_endpoints(void) {
    size_t i = 0;
    vector *tup;
    struct min_pq_binary_heap *memory = pq_new(BUFFER_SIZE);
    r_reader = read_handler_new();
    read_handler_open(r_reader, "__intermediate.tsv");
    write_handler_open(r_writer, "Rgroupby.tsv");

    tup = tuple_get(r_reader);
    while(true) {
        for(i = 0; i < BUFFER_SIZE+1; i++) {
            if(tuple_eof(tup)) goto panic_exit;
            pq_insert(memory, i, tup);
            tup = tuple_get(r_reader);
        }
        flush_memory_to_output(memory);
    }

    if(1 == 0) {
    panic_exit: flush_memory_to_output(memory);
    }
}

/**
 * @func: merge_runs
 * @brief Merges the runs according to the sort merge algorithm
 * @param runs -> The vector of sorted vectors of tuples
 * @param data -> The total number of elements
 */
static void merge_runs(vector *runs, size_t data_size) {
    size_t data_index;
    size_t part_index = 0;
    size_t runs_len;
    struct min_pq_binary_heap *memory = pq_new(BUFFER_SIZE);

    runs_len = vector_length(runs);
    for(data_index = 0; data_index < data_size; data_index++) {
        /* Cycle around the partitions until memory is full */
        vector *block = vector_get(runs, data_index % runs_len);

        /* Insert the value in the range of each partition's size */
        if(data_index % runs_len == 0 && data_index != 0)
            part_index++;

        /* Care if some block has less values in and counter it with the MOD */
        pq_insert(memory, data_index, vector_get(block, (part_index % BUFFER_SIZE)));

        /* At this point the memory is full */
        if((data_index+1) % BUFFER_SIZE == 0 && (data_index+1) != 0)
            flush_memory_to_output(memory);
    }
    write_handler_close(r_writer);

    /* Sort and merge final endpoints */
    sort_and_merge_final_endpoints();
}

/**
 * @func: aggregate
 * @brief Implements an aggregation grouping of elements based on the integral value
 */
static void aggregate(void) {
    vector *runs = NULL;
    vector *data = read_tuples_into_memory();

    runs = create_initial_runs(data);
    merge_runs(runs, vector_length(data));
}

void call_aggregate(char *R) {
    r_reader = read_handler_new();
    r_writer = write_handler_new();
    read_handler_open(r_reader, R);
    write_handler_open(r_writer, "__intermediate.tsv");

    /* Execute aggregation */
    aggregate();
    system("rm -f __intermediate.tsv");
}

int main(void) {
    call_aggregate(R_TSV);
    return 0;
}
