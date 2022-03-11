//
// Created by jdt on 2022-03-06.
//

#include "domain.h"

Transaction make_transaction(unsigned value, signed char type, unsigned char day_of_month){
    // Create a transaction object
    // pre: none extra
    // post: return a Transaction object configured with the given arguments
    Transaction transaction;
    transaction.day_of_month = day_of_month;
    transaction.type = type;
    transaction.value = value;

    return transaction;
}