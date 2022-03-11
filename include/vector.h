//
// Created by jdt on 2022-03-05.
//

//#ifndef LAB2_VECTOR_BASE_H
//#define LAB2_VECTOR_BASE_H

#include <stdlib.h>
#include <memory.h>

typedef struct Vector {
    size_t max_len, crt_len, element_size;
    void* contents;
} Vector;

/*  Some vector related functions require a `type`, which is one of the following:
 *  z - size_t
 *  b - bank record
 * */

Vector* make_vector(char type){
    const size_t INITIAL_MAX_SIZE = 15;
    size_t element_size = 0;
    switch(type) {
        case 'z':
            element_size = sizeof(size_t);
        default:
            element_size = sizeof(int);
    }

    Vector* new_vector = (Vector*) malloc(sizeof(Vector));
    new_vector->max_len = INITIAL_MAX_SIZE;
    new_vector->crt_len = 0;
    new_vector->element_size = element_size;
    new_vector->contents = malloc(sizeof(element_t) * INITIAL_MAX_SIZE);
    return new_vector;

}

void destroy_vector(Vector* old_vector){
    free(old_vector->contents);
    free(old_vector);
}

void push_back(Vector* vector, void* element){
    size_t element_size = vector->element_size;
    char* destination = vector->contents + vector->crt_len * vector->element_size;
    memcpy(destination, element, element_size);
    vector->crt_len += 1;
}

void* at(Vector* vector, size_t position){
    char* result = (char*)vector->contents + position * vector->element_size;
    return result;
}

void* pop_back(Vector* vector){
    void* result = malloc(vector->element_size);
    *result = at(vector, vector->crt_len - 1);
}



//#endif //LAB2_VECTOR_BASE_H
