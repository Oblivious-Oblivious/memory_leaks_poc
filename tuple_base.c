#include "tuple_base.h"

static bool get_result(char *str1, char *str2, bool result) {
    free(str1);
    free(str2);
    return result;
}

vector *tuple_get(struct read_handler *h) {
    char *line = read_handler_read_line(h);

    /* TODO -> LINE MIGHT CAUSE A SEGFAULT */
    return string_split(string_new(line), string_new("\t"));
}

bool tuple_less(vector *tup1, vector *tup2) {
    char *str1 = string_get(vector_get(tup1, 0));
    char *str2 = string_get(vector_get(tup2, 0));

    if(str1 == NULL || str2 == NULL)
        return get_result(str1, str2, false);

    if(!strcmp(str1, ""))
        return get_result(str1, str2, false); /* Tup1 is greater since its at EOF */
    if(!strcmp(str2, ""))
        return get_result(str1, str2, true);  /* Tup2 is less since its at EOF */
    return get_result(str1, str2, strcmp(str1, str2) < 0);
}

bool tuple_greater(vector *tup1, vector *tup2) {
    char *str1 = string_get(vector_get(tup1, 0));
    char *str2 = string_get(vector_get(tup2, 0));

    if(str1 == NULL || str2 == NULL)
        return get_result(str1, str2, false);

    if(!strcmp(str1, ""))
        return get_result(str1, str2, true);  /* Tup1 is greater since its at EOF */
    if(!strcmp(str2, ""))
        return get_result(str1, str2, false); /* Tup2 is less since its at EOF */
    return get_result(str1, str2, strcmp(str1, str2) > 0);
}

bool tuple_key_equals(vector *tup1, vector *tup2) {
    char *str1 = string_get(vector_get(tup1, 0));
    char *str2 = string_get(vector_get(tup2, 0));
    
    if(str1 == NULL || str2 == NULL)
        return get_result(str1, str2, false);

    return get_result(str1, str2, strcmp(str1, str2) == 0);
}

bool tuple_value_equals(vector *tup1, vector *tup2) {
    char *num1 = string_get(vector_get(tup1, 1));
    char *num2 = string_get(vector_get(tup2, 1));
    
    if(num1 == NULL || num2 == NULL)
        return get_result(num1, num2, false);

    return get_result(num1, num2, strcmp(num1, num2) == 0);
}

bool tuple_eof(vector *tup) {
    /* TODO -> WORKS IF WE ASSUME WE READ COHERENT FILES, CHECK FOR ACTUAL NULLITY */
    bool result;
    char *str = string_get(vector_get(tup, 0));

    if(tup == NULL) {
        free(str);
        return true;
    }
    if(vector_get(tup, 0) == NULL) {
        free(str);
        return true;
    }

    if(str == NULL) {
        free(str);
        return true;
    }

    result = strcmp(str, "") == 0;

    free(str);
    return result;
}

void tuple_free(vector *tup) {
    string_free(vector_get(tup, 0));
    string_free(vector_get(tup, 1));
    vector_free(tup);
}
