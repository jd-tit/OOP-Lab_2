//
// Created by jdt on 3/11/2022.
//

#ifndef LAB2_TESTS_SORT_H
#define LAB2_TESTS_SORT_H

#include "domain.h"

typedef int (*cmp_ptr)(Transaction*, Transaction*);


/**
 * Internal pivot function to be used by Quicksort.
 * Select a pivot and place it in its final place in the sorted array.
 * @param list - the array to work on
 * @param l - the start index (inclusive)
 * @param r - the stop index (inclusive)
 * @param cmp - a compare function
 * @param dir - which way to sort: 1 for ascending, -1 for descending order.
 * @return The index at which the pivot was placed.
 */
int pivot(Transaction* list, int l, int r, cmp_ptr cmp, int dir);

/**
 * Sort an array using the Quicksort algorithm
 * @param l - the start index (inclusive)
 * @param r - the stop index (inclusive)
 * @param cmp - a compare function
 * @param dir - which way to sort: 1 for ascending, -1 for descending order.
 */
void quicksort(Transaction *list, int l, int r, cmp_ptr cmp, int dir);

/**
 * Compare two Transactions' days of month
 * @param l - the first Transaction
 * @param r - the second Transaction
 * @return 1 if l > r, 0 if l == r, or -1 if l < r.
 */
int cmp_transactions_day_of_month(Transaction *l, Transaction *r);



/**
 * Compare two Transactions' values
 * @param l - the first Transaction
 * @param r - the second Transaction
 * @return 1 if l > r, 0 if l == r, or -1 if l < r.
 */
int cmp_transactions_value(Transaction* l, Transaction* r);

#endif //LAB2_TESTS_SORT_H
