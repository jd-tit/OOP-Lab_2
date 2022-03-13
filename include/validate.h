//
// Created by jdt on 2022-03-07.
//

#ifndef LAB2_VALIDATE_H
#define LAB2_VALIDATE_H

#include <stdbool.h>

bool is_valid_day_of_month(long day_of_month);
bool is_valid_transaction_value(long value);
bool is_valid_transaction_type(long type);
bool is_valid_order_type(long order_by);
bool is_valid_sort_order(long sort_order);
bool is_valid_order(long order);

#endif //LAB2_VALIDATE_H
