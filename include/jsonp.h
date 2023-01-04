#ifndef JSONP_H
#define JSONP_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

enum json_type {
    JSON_STRING,
    JSON_NUMBER,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL
};

struct json_value {
    enum json_type type;
    union {
        char *string;
        double number;
        struct json_object *object;
        struct json_array *array;
    } data;
};

typedef struct json_object {
    char *key;
    struct json_value value;
    struct json_object *next;
};

typedef struct json_array {
    struct json_value value;
    struct json_array *next;
};



#endif // JSONP_H
