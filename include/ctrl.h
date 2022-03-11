//
// Created by jdt on 2022-03-06.
//

#ifndef LAB2_CTRL_H
#define LAB2_CTRL_H

#include "repo.h"

typedef struct BankCtrl{
    Repository* repo;
} BankCtrl;

BankCtrl* make_BankCtrl(void);
int ctrl_add_transaction(BankCtrl *ctrl, int value, int day_of_month, int type);


#endif //LAB2_CTRL_H
