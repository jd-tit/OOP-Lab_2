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
#include "sort.h"
#include "vector.h"
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

    char valid_value[] = "3000";
    char invalid_value[] = "-1";

    char valid_day[] = "30";
    char invalid_day_1[] = "0";
    char invalid_day_2[] = "40";

    char valid_type[] = "-1";
    char invalid_type[] = "0";


    EXPECT_EQ(ctrl_add_transaction(b_ctrl, valid_value, valid_day, valid_type),  EXIT_SUCCESS);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, invalid_value, valid_day, valid_type), -1);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_1, valid_type), -2);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, valid_type), -2);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, valid_value, valid_day, invalid_type), -3);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, valid_type), -2);
    EXPECT_EQ(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, invalid_type), -2);

    free(b_ctrl->repo);
    free(b_ctrl);
}

TEST(TestSort, TestQuicksort){
    Transaction list[7];
    int start_value = 30;
    int day = 30;
    for(int i = 0; i < 7; ++i){
        list[i].value = start_value;
        list[i].day_of_month = day--;
        list[i].type = IN;
        start_value *= 2;
    }
    quicksort(list, 0, 6, cmp_transactions_value, ASC);

    for(int i = 0; i <= 5; ++i){
        EXPECT_LE(list[i].value, list[i+1].value);
    }

    quicksort(list, 0, 6, cmp_transactions_value, DESC);
    for(int i = 0; i <= 5; ++i){
        EXPECT_GE(list[i].value, list[i+1].value);
    }

    quicksort(list, 0, 6, cmp_transactions_day_of_month, ASC);

    for(int i = 0; i <= 5; ++i){
        EXPECT_LE(list[i].day_of_month, list[i+1].day_of_month);
    }

    quicksort(list, 0, 6, cmp_transactions_day_of_month, DESC);
    for(int i = 0; i <= 5; ++i){
        EXPECT_GE(list[i].day_of_month, list[i+1].day_of_month);
    }
}

TEST(TestVector, TestCreate){
    Vector* v = make_vector(DataTypes::TRANSACTION);
    EXPECT_EQ(v->max_len, INITIAL_MAX_SIZE);
    EXPECT_EQ(v->crt_len, 0);
    EXPECT_EQ(v->element_size, sizeof(Transaction));
}

TEST(TestVector, TestExtend){
    Vector* v = make_vector(DataTypes::TRANSACTION);
    extend(v);
    EXPECT_EQ(v->max_len, INITIAL_MAX_SIZE * EXTEND_FACTOR);
    EXPECT_EQ(v->element_size, sizeof(Transaction));
}

TEST(TestVector, TestPushBack){
    Vector* v = make_vector(DataTypes::TRANSACTION);
    Transaction t = make_transaction(3000, 1, 30);
    for(int i = 0; i <= v->max_len * 2; ++i){
        push_back(v, &t);
    }

    for(int i = 0; i <= v->max_len * 2; ++i){
        Transaction* transactions = (Transaction*)v->contents;
        EXPECT_EQ(transactions[i].day_of_month, 30);
        EXPECT_EQ(transactions[i].value, 3000);
        EXPECT_EQ(transactions[i].type, 1);
    }

    EXPECT_EQ(v->max_len, INITIAL_MAX_SIZE * EXTEND_FACTOR);
    EXPECT_EQ(v->element_size, sizeof(Transaction));
}
