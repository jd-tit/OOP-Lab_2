//
// Created by jdt on 3/10/2022.
//
#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "domain.h"
#include "repo.h"
#include "validate.h"
#include "restrict_types.h"
#include "ctrl.h"

void TestMakeTransaction(void){
    int value = 10000;
    signed char type = -1;
    unsigned char day_of_month = 30;
    Transaction t = make_transaction(value, type, day_of_month);

    assert(value == t.value);
    assert (type == t.type);
    assert(day_of_month == t.day_of_month);
}

void TestMakeRepo(void){
    Repository* repo = make_repository();
    assert(repo->max_len == MAX_LEN);
    assert(repo->crt_len == 0);
    destroy_repository(repo);
}

void TestRepoAddTransaction(void){
    Repository* repo = make_repository();
    Transaction t = make_transaction(1000, 1, 30);

    assert(repo_add_transaction(repo, t) == EXIT_SUCCESS);
    assert(repo->crt_len == 1);
    assert(repo->transaction_log[0].day_of_month == 30);
    assert(repo->transaction_log[0].value == 1000);
    assert(repo->transaction_log[0].type == 1);

    for(size_t i = 1; i < MAX_LEN; ++i){
        assert(repo_add_transaction(repo, t) == EXIT_SUCCESS);
    }
    assert(repo_add_transaction(repo, t) == EXIT_FAILURE);
    free(repo);
}

void TestIsValid(void){
    //day of month
    for(int i = 1; i <=31; ++i)
        assert(is_valid_day_of_month(i));
    assert(!is_valid_day_of_month(0));
    assert(!is_valid_day_of_month(32));
    assert(!is_valid_day_of_month(-1));

    //type
    assert(!is_valid_transaction_type(0));
    assert(is_valid_transaction_type(1));
    assert(is_valid_transaction_type(-1));

    //value
    assert(!is_valid_transaction_value(-1));
    assert(!is_valid_transaction_value(0));
    assert(is_valid_transaction_value(1));
    assert(is_valid_transaction_value(1000));
}

void TestRestrict(void){
    // --- type ---
    assert(restrict_type(-1) == OUT);
    assert(restrict_type(-1000) == OUT);
    assert(restrict_type(1) == IN);
    assert(restrict_type(1000) == IN);
    // for safety
    assert(restrict_type(0) == 0);

    // --- day of month ---
    // How do you test if something is of a certain type?

    for(int i = 1; i <=31; ++i)
        assert(restrict_day_of_month(i) == (unsigned char)i);

    // --- value ---
    assert(restrict_transaction_value(INT_MAX) == INT_MAX);
}

void TestMakeBankCtrl(void){
    BankCtrl* b_ctrl =  make_BankCtrl();
    assert(b_ctrl->repo != NULL);
    assert(b_ctrl->repo->max_len == MAX_LEN);
    assert(b_ctrl->repo->crt_len == 0);
    free(b_ctrl->repo);
    free(b_ctrl);
}

void TestCtrlAddTransaction(void){
    BankCtrl* b_ctrl = make_BankCtrl();

    assert(ctrl_add_transaction(b_ctrl, 3000, 30, -1) == EXIT_SUCCESS);
    assert(ctrl_add_transaction(b_ctrl, -1, 30, -1) == -1);
    assert(ctrl_add_transaction(b_ctrl, -3000, 0, -1) == -1);
    assert(ctrl_add_transaction(b_ctrl, 3000, 0, -1) == -2);
    assert(ctrl_add_transaction(b_ctrl, 3000, 30, 0) == -3);
    assert(ctrl_add_transaction(b_ctrl, 3000, 40, -1) == -2);

    free(b_ctrl->repo);
    free(b_ctrl);
}

void runAllTests(void){
    TestMakeTransaction();
    TestMakeRepo();
    TestRepoAddTransaction();
    TestIsValid();
    TestRestrict();
    TestMakeBankCtrl();
    TestCtrlAddTransaction();
}

