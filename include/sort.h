//
// Created by jdt on 3/11/2022.
//

#ifndef LAB2_TESTS_SORT_H
#define LAB2_TESTS_SORT_H

#include "domain.h"

typedef int (*cmp_ptr)(Transaction*, Transaction*);

int pivot(Transaction* list, int l, int r, cmp_ptr cmp, int dir);
void quicksort(Transaction *list, int l, int r, cmp_ptr cmp, int dir);
int cmp_int(void* l, void* r);
int cmp_transactions_day_of_month(Transaction *l, Transaction *r);
int cmp_transactions_value(Transaction* l, Transaction* r);

#endif //LAB2_TESTS_SORT_H
