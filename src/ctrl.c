//
// Created by jdt on 2022-03-06.
//

#include <malloc.h>
#include <stdlib.h>
#include "repo.h"
#include "ctrl.h"
#include "domain.h"
#include "validate.h"
#include "restrict_types.h"

BankCtrl* make_BankCtrl(void){
    /*  Create a BankController object
     * pre: void
     * post: return a pointer to a BankController object, initialised with a repository,
     *          or NULL if allocation failed
     * */

    BankCtrl* ctrl = malloc(sizeof(BankCtrl));
    ctrl->repo = make_repository();
    if(ctrl->repo == NULL){
        free(ctrl);
        return (BankCtrl*)NULL;
    }
    return ctrl;
}

int ctrl_add_transaction(BankCtrl *ctrl, int value, int day_of_month, int type) {
    /* Controller function for adding transactions to the database.
     * pre: void
     * post: A transaction with the given data is added to the database.
     * */
    if(!is_valid_transaction_value(value))
        return -1;
    unsigned r_value = restrict_transaction_value(value);

    if(!is_valid_day_of_month(day_of_month))
        return -2;
    unsigned char r_day_of_month = restrict_day_of_month(day_of_month);

    if(!is_valid_transaction_type(type))
        return -3;
    signed char r_type = restrict_type(type);

    Transaction transaction = make_transaction(r_value, r_type, r_day_of_month);
    if(repo_add_transaction(ctrl->repo, transaction) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}