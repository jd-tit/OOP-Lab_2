//
// Created by jdt on 2022-03-07.
//

#include "../include/validate.h"
#include "stdbool.h"

bool is_valid_day_of_month(int day_of_month){
    /**
     * Check if `day_of_month` is a valid day of the month.
     * @pre: None
     * @post: Result of check is returned
     */
    if(day_of_month > 31 || day_of_month < 1)
        return false;
    return true;
}

bool is_valid_transaction_value(int value){
    /**
     * Check if `value` is a valid transaction value.
     * @pre: None
     * @post: Result of check is returned
     */
    if(value <= 0)
        return false;
    return true;
}

bool is_valid_transaction_type(int type){
    /**
     * Check if `type` is a valid transaction value.
     * @pre: None
     * @post: Result of check is returned
     */
    if(type == 0)
        return false;
    return true;
}
