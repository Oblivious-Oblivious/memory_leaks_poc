#include "string_builder_base.h"

string *string_new(char *initial_string) {
    string *sb = (string*)calloc(1, sizeof(*sb));
    sb->list = linked_list_new();
    sb->length = 0;
    string_add(sb, initial_string);

    return sb;
}

void string_add(string *sb, const char *str) {
    if(sb == NULL || str == NULL) return;

    linked_list_add(sb->list, (void*)str);
}

void string_addf(string *sb, const char *f, ...) {
    #define BIG_NUMBA 16384 /* TODO -> BOUNDS CHECKS */
    signed int result = 0;
    char buf[BIG_NUMBA];
    va_list args;

    if(sb == NULL || f == NULL) return;

    va_start(args, f);
        result = vsnprintf(buf, sizeof(buf), f, args);
    va_end(args);

    if(result < 0) return;

    string_add(sb, buf);
}

char *string_get(string *sb) {
    char *buf = NULL;
    char *c = NULL;
    void *head = NULL;
    struct llnode **probe = NULL;

    if(sb == NULL) return NULL;

    buf = (char*)malloc(sizeof(char) * (sb->length + 1));
    if(buf == NULL) return NULL;

    c = buf;
    probe = (&sb->list->head);

    /* Dereference once */
    while(*probe) {
        void *item = (*probe)->item;
        size_t item_len = strlen((char*)item);
        memcpy(c, (char*)item, sizeof(char) * item_len);
        c += item_len;

        /* Traverse tothe next node */
        probe = (struct llnode**)&(*probe)->next;
    }

    *c = '\0';

    return buf;
}

void string_delete(string *sb) {
    if(sb == NULL) return;
    if(sb->list == NULL) return;

    linked_list_free(sb->list);
    sb->length = 0;
}

bool string_equals(string *sb, string *other) {
    if(sb == NULL || other == NULL) return false;

    return strcmp(string_get(sb), string_get(other)) == 0;
}

void string_free(string *sb) {
    if(sb == NULL) return;

    string_delete(sb);
    free(sb);
}

vector *string_split(string *sb, string *delimeter) {
    size_t i;
    char *sb_p = NULL;
    char *token = NULL;
    char *delim_p = NULL;
    vector *str_tokens = vector_new();

    /* Iterate through the chars constructing a string and
		reseting the value once we find the delimeter */
    sb_p = string_get(sb);
    token = strtok(sb_p, (delim_p = string_get(delimeter)));

    while(token != NULL) {
        vector_add(str_tokens, string_new(token));
        token = strtok(NULL, delim_p);
    }

    free(token);
    return str_tokens;
}

