//
// Created by jdt on 2022-03-06.
//

#include "domain.h"

static unsigned id = 0;

Transaction make_transaction(unsigned value, signed char type, unsigned char day_of_month){
    Transaction transaction;
    transaction.day_of_month = day_of_month;
    transaction.type = type;
    transaction.value = value;
    transaction.id = id++;

    return transaction;
}

Transaction copy_transaction(Transaction* original){
    unsigned int id_local = original->id;
    signed char type = original->type;
    unsigned char day_of_month = original->day_of_month;
    unsigned int value = original->value;
    Transaction t = make_transaction(value, type, day_of_month);
    --id;
    t.id = id_local;
    return t;
}

void reset_id_counter(void){
    id = 0;
}
