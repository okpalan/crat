#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "ray.h"
#include "sphere.h"
#include "material.h"

int main(int argc, char **argv) {

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file %s", argv[1]);
        return 1;
    }
    fp = jsonp_parse(fp);
    
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not parse file %s", argv[1]);
        return 1;
    }
    
    fclose(fp);
    return 0;

}