#include "tuple_base.h"

vector *tuple_get(struct read_handler *h) {
    char *line = read_handler_read_line(h);

    /* TODO -> LINE MIGHT CAUSE A SEGFAULT */
    return string_split(string_new(line), string_new("\t"));
}

bool tuple_less(vector *tup1, vector *tup2) {
    char *str1 = string_get(vector_get(tup1, 0));
    char *str2 = string_get(vector_get(tup2, 0));

    if(str1 == NULL || str2 == NULL)
        return false;

    if(!strcmp(str1, ""))
        return false; /* Tup1 is greater since its at EOF */
    if(!strcmp(str2, ""))
        return true;  /* Tup2 is less since its at EOF */
    return strcmp(str1, str2) < 0;
}

bool tuple_greater(vector *tup1, vector *tup2) {
    char *str1 = string_get(vector_get(tup1, 0));
    char *str2 = string_get(vector_get(tup2, 0));

    if(str1 == NULL || str2 == NULL)
        return false;

    if(!strcmp(str1, ""))
        return true;  /* Tup1 is greater since its at EOF */
    if(!strcmp(str2, ""))
        return false; /* Tup2 is less since its at EOF */
    return strcmp(str1, str2) > 0;
}

bool tuple_key_equals(vector *tup1, vector *tup2) {
    char *str1 = string_get(vector_get(tup1, 0));
    char *str2 = string_get(vector_get(tup2, 0));
    
    if(str1 == NULL || str2 == NULL)
        return false;

    return strcmp(str1, str2) == 0;
}

bool tuple_value_equals(vector *tup1, vector *tup2) {
    char *num1 = string_get(vector_get(tup1, 1));
    char *num2 = string_get(vector_get(tup2, 1));
    
    if(num1 == NULL || num2 == NULL)
        return false;

    return strcmp(num1, num2) == 0;
}

bool tuple_eof(vector *tup) {
    /* TODO -> WORKS IF WE ASSUME WE READ COHERENT FILES, CHECK FOR ACTUAL NULLITY */
    char *str = string_get(vector_get(tup, 0));

    if(tup == NULL)
        return true;
    if(vector_get(tup, 0) == NULL)
        return true;

    if(str == NULL)
        return true;

    return strcmp(str, "") == 0;
}

void tuple_free(vector *tup) {
    string_free(vector_get(tup, 0));
    string_free(vector_get(tup, 1));
    vector_free(tup);
}
