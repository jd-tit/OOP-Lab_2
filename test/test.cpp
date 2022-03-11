//
// Created by jdt on 2022-03-10.
//

#include <gtest/gtest.h>
#include <cstdlib>
#include <cassert>
#include <climits>

extern "C" {
#include "domain.h"
#include "repo.h"
#include "validate.h"
#include "restrict_types.h"
#include "ctrl.h"
}

TEST(TestDomain, TestMakeTransaction){
    int value = 10000;
    signed char type = -1;
    unsigned char day_of_month = 30;
    Transaction t = make_transaction(value, type, day_of_month);

    EXPECT_EQ(value, t.value);
    EXPECT_EQ(type, t.type);
    EXPECT_EQ(day_of_month, t.day_of_month);
}

TEST(TestRepo, TestMakeRepo){
    Repository* repo = make_repository();
    EXPECT_EQ(repo->max_len, MAX_LEN);
    EXPECT_EQ(repo->crt_len, 0);
    destroy_repository(repo);
}

TEST(TestRepo, TestRepoAddTransaction){
    Repository* repo = make_repository();
    Transaction t = make_transaction(1000, 1, 30);

    EXPECT_EQ(repo_add_transaction(repo, t),  EXIT_SUCCESS);
    EXPECT_EQ(repo->transaction_log[0].day_of_month,  30);
    EXPECT_EQ(repo->transaction_log[0].value,  1000);
    EXPECT_EQ(repo->transaction_log[0].type,  1);

    for(size_t i = 1; i < MAX_LEN; ++i){
        EXPECT_EQ(repo_add_transaction(repo, t),  EXIT_SUCCESS);
    }
    EXPECT_EQ(repo_add_transaction(repo, t),  EXIT_FAILURE);
    free(repo);
}

TEST(TestValidators,TestIsValid){
    //day of month
    for(int i = 1; i <=31; ++i)
        EXPECT_TRUE(is_valid_day_of_month(i));
    EXPECT_FALSE(is_valid_day_of_month(0));
    EXPECT_FALSE(is_valid_day_of_month(32));
    EXPECT_FALSE(is_valid_day_of_month(-1));

    //type
    EXPECT_FALSE(is_valid_transaction_type(0));
    EXPECT_TRUE(is_valid_transaction_type(1));
    EXPECT_TRUE(is_valid_transaction_type(-1));

    //value
    EXPECT_FALSE(is_valid_transaction_value(-1));
    EXPECT_FALSE(is_valid_transaction_value(0));
    EXPECT_TRUE(is_valid_transaction_value(1));
    EXPECT_TRUE(is_valid_transaction_value(1000));
}

TEST(TestTypeRestrictors,TestRestrict){
    // --- type ---
    EXPECT_EQ(restrict_type(-1),  OUT);
    EXPECT_EQ(restrict_type(-1000),  OUT);
    EXPECT_EQ(restrict_type(1),  IN);
    EXPECT_EQ(restrict_type(1000),  IN);
    // for safety
    EXPECT_EQ(restrict_type(0),  0);

    // --- day of month ---
    // How do you test if something is of a certain type?

    for(int i = 1; i <=31; ++i)
        EXPECT_EQ(restrict_day_of_month(i),  (unsigned char)i);

    // --- value ---
    EXPECT_EQ(restrict_transaction_value(INT_MAX),  INT_MAX);
}

TEST(TestCTRL,TestMakeBankCtrl){
    BankCtrl* b_ctrl =  make_BankCtrl();
    EXPECT_NE(b_ctrl->repo, nullptr);
    EXPECT_EQ(b_ctrl->repo->max_len,  MAX_LEN);
    EXPECT_EQ(b_ctrl->repo->crt_len,  0);
    free(b_ctrl->repo);
    free(b_ctrl);
}

TEST(TestCTRL, TestCtrlAddTransaction){
    BankCtrl* b_ctrl = make_BankCtrl();

    EXPECT_EQ(ctrl_add_transaction(b_ctrl, 3000, 30, -1),  EXIT_SUCCESS);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, -1, 30, -1),  -1);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, -3000, 0, -1),  -1);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, 3000, 0, -1),  -2);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, 3000, 30, 0),  -3);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, 3000, 40, -1),  -2);

    free(b_ctrl->repo);
    free(b_ctrl);
}



