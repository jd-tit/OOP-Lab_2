//
// Created by jdt on 3/11/2022.
//

#include <stdlib.h>
#include <memory.h>

#include "vector.h"
#include "domain.h"

#define EXTEND_FACTOR 2

Vector* make_vector(char type){
    size_t element_size = 0;
    element_size = sizeof(Transaction); // Only Transaction vectors were necessary after all
//    switch(type) {
//        case TRANSACTION:
//            element_size = sizeof(Transaction);
//            break;
//        case SIZE_T:
//            element_size = sizeof(size_t);
//            break;
//        default:
//            element_size = sizeof(int);
//            break;
//    }

    Vector* new_vector = (Vector*) malloc(sizeof(Vector));
    new_vector->max_len = INITIAL_MAX_SIZE;
    new_vector->crt_len = 0;
    new_vector->element_size = element_size;
    new_vector->contents = malloc(element_size * INITIAL_MAX_SIZE);
    return new_vector;
}

void destroy_vector(Vector* old_vector){
    free(old_vector->contents);
    old_vector->contents = NULL;
    free(old_vector);
    old_vector = NULL;
}

int push_back(Vector* vector, void* element){
    /** Copy element into vector
     * @pre: vector is configured with an element_size equal to that of element
     * @post: element is added to the vector, or EXIT_FAILURE is returned.
     */
    if(vector->crt_len + 1 >= vector->max_len){
        if(extend(vector) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }

    size_t element_size = vector->element_size;
    //casting to char* to do pointer arithmetic
    char* destination = (char*)vector->contents + vector->crt_len * vector->element_size;
    memcpy(destination, element, element_size);
    vector->crt_len += 1;
    return EXIT_SUCCESS;
}

//void* at(Vector* vector, size_t position){
//    char* result = (char*)vector->contents + position * vector->element_size;
//    return result;
//}

//void* pop(Vector* vector, ){
//    void* result = malloc(vector->element_size);
//    *result = at(vector, vector->crt_len - 1);
//}

int extend(Vector* vector){
    size_t new_len = vector->max_len * EXTEND_FACTOR;
    void* new_contents = realloc(vector->contents, new_len * vector->element_size);
    if(new_contents == NULL)
        return EXIT_FAILURE;
    vector->max_len = new_len;
    vector->contents = new_contents;
    return EXIT_SUCCESS;
}

Vector* copy_vector(Vector* v){
    char* contents = malloc(v->element_size * v->max_len);
    memcpy(contents, v->contents, v->crt_len * v->element_size);
    Vector* result = malloc(sizeof(Vector));
    result->contents = contents;
    result->crt_len = v->crt_len;
    result->max_len = v->max_len;
    result->element_size = v->element_size;
    return result;
}

