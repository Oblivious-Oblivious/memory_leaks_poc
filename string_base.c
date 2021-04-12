#include "string_base.h"

#define GOLDEN_MEAN 1.618

/**
 * @func: string_ensure_space
 * @desc: Ensure there is enough space for data being added plus a NULL terminator
 * @param sb -> The string builder to use
 * @param add_len -> he length that needs to be added *not* including a NULL terminator
 **/
static void string_ensure_space(string *sb, size_t capacity) {
    char *new_str = NULL;
    if(sb == NULL || capacity == 0) return;

    /* Attempt to reallocate new memory in the items list */
    new_str = (char*)realloc(sb->str, sizeof(char*) * capacity);

    if(new_str) {
        /* Reset the items in the new memory space */
        sb->str = new_str;
        sb->alloced = capacity;
    }
}

string *string_new(char *initial_string) {
    string *sb = (string*)calloc(1, sizeof(*sb));
    sb->str = (char*)malloc(string_init_capacity);

    /* NULL terminate the string */
    *sb->str = '\0';

    sb->alloced = string_init_capacity;
    sb->length = 0;

    string_add_str(sb, initial_string);
    return sb;
}

void string_addf(string *sb, const char *f, ...) {
    #define BIG_NUMBA 16384 /* TODO -> BOUNDS CHECKS */
    signed int result = 0;
    char buf[BIG_NUMBA];
    va_list args;

    va_start(args, f);
        result = vsnprintf(buf, sizeof(buf), f, args);
    va_end(args);

    if(result < 0) return;

    string_add_str(sb, buf);
}

void string_add_str(string *sb, const char *str) {
    size_t len;
    
    if(sb == NULL || str == NULL || *str == '\0') return;

    len = strlen(str);
    
    if(sb->alloced == sb->length)
        string_ensure_space(sb, sb->alloced * GOLDEN_MEAN);

    /* Copy the value into memory */
    memmove(sb->str+sb->length, str, len);

    /* Reset length and NULL terminate */
    sb->length += len;
    sb->str[sb->length] = '\0';
}

void string_add_char(string *sb, char c) {
    if(sb == NULL) return;

    if(sb->alloced == sb->length)
        string_ensure_space(sb, sb->alloced * GOLDEN_MEAN);

    sb->str[sb->length] = c;
    sb->length++;
    sb->str[sb->length] = '\0';
}

void string_add_int(string *sb, int val) {
    char str[32];

    if(sb == NULL) return;

    snprintf(str, sizeof(str), "%d", val);
    string_add_str(sb, str);
}

void string_add_double_precision(string *sb, double val) {
    char str[64];

    if(sb == NULL) return;

    /* Use %g for minimum precision on printing floats */
    snprintf(str, sizeof(str), "%g", val);
    string_add_str(sb, str);
}

char *string_get(string *sb) {
    if(sb == NULL) return NULL;
    return sb->str;
}

char string_get_char_at_index(string *sb, size_t index) {
    if(sb == NULL) return '\0';
    return sb->str[index];
}

void string_shorten(string *sb, size_t len) {
    if(sb == NULL || len >= sb->length) return;

    /* Reset the length and NULL terminate, ingoring
        all values right to the NULL from memory */
    sb->length = len;
    sb->str[sb->length] = '\0';
}

void string_delete(string *sb) {
    if(sb == NULL) return;

    /* Call shorten with 0, clearing out the string */
    string_free(sb);
    string_shorten(sb, 0);
}

void string_skip(string *sb, size_t len) {
    if(sb == NULL || len == 0) return;

    if(len >= sb->length) {
        /* If we choose to drop more bytes than the
            string has simply clear the string */
        string_delete(sb);
        return;
    }

    sb->length -= len;

    /* +1 to move the NULL. */
    memmove(sb->str, sb->str + len, sb->length + 1);
}

size_t string_length(string *sb) {
    if(sb == NULL) return 0;
    return sb->length;
}

unsigned char string_equals(string *sb, string *other) {
    return strcmp(string_get(sb), string_get(other)) == 0;
}

char *string_identifier(string *sb) {
    unsigned char add_underscore = 0;
    char buf[32];
    size_t i;
    string *output = NULL;
    string *ret_value = NULL;

    if(sb == NULL) return NULL;

    output = string_new("");

    for(i = 0; i < string_length(sb); i++) {
        char c = string_get(sb)[i];

        if((c > 47 && c < 58)
        || (c > 64 && c < 91)
        || (c > 96 && c != 95 && c < 123))
            string_add_char(output, c);
        else if(c == 32)
            string_add_char(output, '_');
        else {
            if(i == 0) add_underscore = 1;
            snprintf(buf, 2, "%02x", c & 0xff);
            string_add_str(output, buf);
        }
    }

    if(add_underscore)
        ret_value = string_new("_");
    else
        ret_value = string_new("");
    string_add_str(ret_value, string_get(output));

    return string_get(ret_value);
}

void string_free(string *sb) {
    free(sb->str);
    free(sb);
}

vector *string_split(string *str, string *delimeter) {
	size_t i;
	vector *str_tokens = vector_new();
	string *token_str = string_new("");

	/* Iterate through the chars constructing a string and
		reseting the value once we find the delimeter */
	for(i = 0; (i <= string_length(str)
	&& string_get_char_at_index(str, i) != '\0'); i++) {
		if(string_get_char_at_index(str, i) == string_get(delimeter)[0]) {
			/* We found a character matching the delimeter */
			vector_add(str_tokens, token_str);

			/* Reset the temp string */
			token_str = string_new("");
			continue;
		}

		string_add_char(token_str, string_get_char_at_index(str, i));
	}

	/* We add the last collected characters */
	vector_add(str_tokens, token_str);
	return str_tokens;
}
