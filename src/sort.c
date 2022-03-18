//
// Created by jdt on 3/11/2022.
//

#include <stdio.h>

#include "sort.h"
#include "domain.h"

int pivot(Transaction* list, int l, int r, cmp_ptr cmp, int dir) {
    Transaction p = list[r];
    int lt = l-1;
    for(int i = l; i < r; ++i){
        if(cmp(&list[i], &p) * dir <= 0){
            ++lt;
            Transaction aux = list[lt];
            list[lt] = list[i];
            list[i] = aux;
        }
    }
    Transaction aux = list[r];
    list[r] = list[lt+1];
    list[lt+1] = aux;
    return lt + 1;
}

void quicksort(Transaction *list, int l, int r, cmp_ptr cmp, int dir){
    if(l < r){
        int p_index = pivot(list, l, r, cmp, dir);

        quicksort(list, l, p_index - 1, cmp, dir);
        quicksort(list, p_index + 1, r, cmp, dir);
    }
}

int cmp_transactions_day_of_month(Transaction *l, Transaction *r){
    Transaction* t1 = l;
    Transaction* t2 = r;
    if(t1->day_of_month < t2->day_of_month)
        return -1;
    if(t1->day_of_month == t2->day_of_month)
        return 0;
    return 1;
}

int cmp_transactions_value(Transaction* l, Transaction* r){
    if(l->value < r->value)
        return -1;
    if(l->value == r->value)
        return 0;
    return 1;
}


//int cmp_int(int l, int r){
//    if(l < r)
//        return -1;
//    if(l == r)
//        return 0;
//    return 1;
//}
