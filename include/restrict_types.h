//
// Created by jdt on 2022-03-09.
//

#ifndef LAB2_RESTRICT_TYPES_H
#define LAB2_RESTRICT_TYPES_H
#include "domain.h"

/**
 * Restrict a type to the proper values for a type, either 1 or -1
 * @param type The value to restrict
 * @post If the value of `type` is invalid (ie. 0), return 0.
 * @return The restricted value.
 */
signed char restrict_type(long type);

/**
 * Cast a valid day of month to unsigned char
 * @param dom - the value to be cast
 * @return The cast value.
 */
unsigned char restrict_day_of_month(long dom);


/**
 * Cast a valid Transaction value to unsigned int.
 * @param value - the value to be cast
 * @return - the cast value
 */
unsigned restrict_transaction_value(long value);

#endif //LAB2_RESTRICT_TYPES_H
