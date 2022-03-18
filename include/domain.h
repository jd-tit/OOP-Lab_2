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
    unsigned id;
} Transaction;


/**
 * Create a transaction.
 * @param value - Transaction value
 * @param type - Transaction type, either IN or OUT
 * @param day_of_month  - a valid day of month (1 through 31)
 * @return The new transaction
 */
Transaction make_transaction(unsigned value, signed char type, unsigned char day_of_month);

/**
 * Make a copy of a transaction.
 * @param original - pointer to the original Transaction
 * @return An independent copy of `original`.
 */
Transaction copy_transaction(Transaction* original);

/**
 * Reset the ID counter to 0.
 */
void reset_id_counter(void);

#endif //LAB2_DOMAIN_H
