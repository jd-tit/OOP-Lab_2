//
// Created by jdt on 2022-03-06.
//

#ifndef LAB2_DOMAIN_H
#define LAB2_DOMAIN_H

enum Types {IN = 1, OUT = -1};

typedef struct Transaction{
    unsigned char day_of_month;
    unsigned value;
    signed char type;
} Transaction;

Transaction make_transaction(unsigned value, signed char type, unsigned char day_of_month);

#endif //LAB2_DOMAIN_H
