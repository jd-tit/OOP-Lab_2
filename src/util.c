//
// Created by jdt on 3/11/2022.
//

#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "domain.h"
#include "vector.h"

Transaction make_random_transaction(void){
    unsigned int value = (rand() % 100 + 1) * 1000;
    signed char type = 0;
    while(type == 0)
        type = (rand() % 3) -1;

    unsigned char day_of_month = rand() % 31 + 1;
    Transaction t = make_transaction(value, type, day_of_month);
    return t;
}

void fill_randomly(Vector* v, size_t to){
    for(size_t i = 0; i <= to; ++i) {
        Transaction t = make_random_transaction();
        push_back(v, &t);
    }
}
