#include "jsonp.h"
#include <stdbool.h>
#include <stdio.h>

json_value *json_parse(const char *json) {
    json_value *value = malloc(sizeof(json_value));
    if (value == NULL) {
        return NULL;
    }
    value->type = JSON_NULL;
    value->data.string = NULL;
    return value;
}

void json_free(json_value *value) {
    if (value == NULL) {
        return;
    }
    if (value->type == JSON_STRING) {
        free(value->data.string);
    }
    free(value);
}

json_value *json_parse_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *json = malloc(size + 1);
    if (json == NULL) {
        fclose(file);
        return NULL;
    }

    fread(json, 1, size, file);
    fclose(file);
    json[size] = '\0';
    json_value *value = json_parse(json);
    free(json);
    return value;

}

json_value *json_stringify(const json_value *value){
    if (value == NULL) {
        return NULL;
    }
    json_value *new_value = malloc(sizeof(json_value));
    if (new_value == NULL) {
        return NULL;
    }
    new_value->type = value->type;
    if (value->type == JSON_STRING) {
        new_value->data.string = strdup(value->data.string);
        if (new_value->data.string == NULL) {
            free(new_value);
            return NULL;
        }
    }
    return new_value;
}
void json_print(const json_value *value) {
    if (value == NULL) {
        return;
    }
    switch (value->type) {
        case JSON_STRING:
            printf("\"%s\"", value->data.string);
            break;
        case JSON_NUMBER:
            printf("%f", value->data.number);
            break;
        case JSON_OBJECT:
            printf("{");
            json_object *object = value->data.object;
            while (object != NULL) {
                printf("\"%s\":", object->key);
                json_print(&object->value);
                object = object->next;
                if (object != NULL) {
                    printf(",");
                }
            }
            printf("}");
            break;
        case JSON_ARRAY:
            printf("[");
            json_array *array = value->data.array;
            while (array != NULL) {
                json_print(&array->value);
                array = array->next;
                if (array != NULL) {
                    printf(",");
                }
            }
            printf("]");
            break;
        case JSON_TRUE:
            printf("true");
            break;
        case JSON_FALSE:
            printf("false");
            break;
        case JSON_NULL:
            printf("null");
            break;
    }
}

int main(int argc, char *argv[]) {
    json_value *value = json_parse_file(argv[1]);
    json_print(value);
    
}