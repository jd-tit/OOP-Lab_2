//
// Created by jdt on 3/11/2022.
//

#ifndef LAB2_TESTS_UTIL_H
#define LAB2_TESTS_UTIL_H

#include "vector.h"
#include "domain.h"

/**
 * Fill a Vector with random Transactions
 * @param v - a pointer to a Vector
 * @param to - limit up to which to fill the Vector (inclusive)
 * @post `to` + 1 Transactions are added to the Vector
 */
void fill_randomly(Vector* v, size_t to);

/**
 * Create a random transaction.
 * @return A valid random Transaction
 */
Transaction make_random_transaction(void);

#endif //LAB2_TESTS_UTIL_H
