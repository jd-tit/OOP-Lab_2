//
// Created by jdt on 2022-03-05.
//

#ifndef LAB2_VECTOR_BASE_H
#define LAB2_VECTOR_BASE_H

#define INITIAL_MAX_SIZE 15
#define EXTEND_FACTOR 2

enum DataTypes{TRANSACTION, SIZE_T};

#include <stdio.h>

typedef struct Vector {
    size_t max_len, crt_len, element_size;
    void* contents;
} Vector;

Vector* make_vector(char type);
void destroy_vector(Vector* old_vector);
int push_back(Vector* vector, void* element);
void* at(Vector* vector, size_t position);
void* pop_back(Vector* vector);
int extend(Vector* vector);
Vector* copy_vector(Vector* v);

#endif //LAB2_VECTOR_BASE_H
