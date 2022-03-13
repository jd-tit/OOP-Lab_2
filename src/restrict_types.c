//
// Created by jdt on 2022-03-09.
//

#include "../include/restrict_types.h"

signed char restrict_type(long type){
    /* Restrict a transaction type to the types in the enum
     * pre: `type` is a validated type (any non-zero integer works)
     * post:    - return:a (signed char) with a value from the enum Domain.Types: either IN or OUT
     * */
    if(type < 0)
        return OUT;
    if(type > 0)
        return IN;
    return 0;
}

unsigned char restrict_day_of_month(long dom){
    /* Restrict a day_of_month to an unsigned char.
     * pre:     `dom` is a validated day_of_month ( has a value between 1 and 31, inclusive)
     * post:    `dom` is cast and returned as an (unsigned char)
     * */
    return (unsigned char) dom;
}

unsigned restrict_transaction_value(long value){
    /* Restrict a transaction value to an unsigned integer.
     * pre:     `value` is a validated transaction value ( has a value strictly greater than 0)
     * post:    `value` is cast and returned as an (unsigned int)
     * */
    return (unsigned) value;
}
