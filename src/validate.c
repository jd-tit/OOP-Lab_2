//
// Created by jdt on 2022-03-07.
//

#include "validate.h"
#include "stdbool.h"
#include "ctrl.h"

bool is_valid_day_of_month(long day_of_month){
    /**
     * Check if `day_of_month` is a valid day of the month.
     * @pre: None
     * @post: Result of check is returned
     */
    if(day_of_month > 31 || day_of_month < 1)
        return false;
    return true;
}

bool is_valid_transaction_value(long value){
    /**
     * Check if `value` is a valid transaction value.
     * @pre: None
     * @post: Result of check is returned
     */
    if(value <= 0)
        return false;
    return true;
}

bool is_valid_transaction_type(long type){
    /**
     * Check if `type` is a valid transaction value.
     * @pre: None
     * @post: Result of check is returned
     */
    if(type == 0)
        return false;
    return true;
}

bool is_valid_order_type(long order_by){
    if(order_by != VALUE && order_by != DAY_OF_MONTH)
        return false;
    return true;
}

bool is_valid_order(long order){
    if(order != 1 && order != 2)
        return false;
    return true;
}

bool is_valid_sort_order(long sort_order){
    if(sort_order != DESC && sort_order != ASC)
        return false;
    return true;
}
