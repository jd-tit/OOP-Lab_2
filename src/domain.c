//
// Created by jdt on 2022-03-06.
//

#include "domain.h"

Transaction make_transaction(unsigned value, signed char type, unsigned char day_of_month){
    // Create a transaction object
    // pre: none extra
    // post: return a Transaction object configured with the given arguments
    static unsigned id = 0;
    Transaction transaction;
    transaction.day_of_month = day_of_month;
    transaction.type = type;
    transaction.value = value;
    transaction.id = id++;

    return transaction;
}

Transaction copy_transaction(Transaction* original){
    unsigned int id = original->id;
    signed char type = original->type;
    unsigned char day_of_month = original->day_of_month;
    unsigned int value = original->value;
    Transaction t = make_transaction(value, type, day_of_month);
    t.id = id;
    return t;
}
