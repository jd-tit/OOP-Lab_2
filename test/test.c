//
// Created by jdt on 2022-03-10.
//

#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "domain.h"
#include "repo.h"
#include "validate.h"
#include "restrict_types.h"
#include "ctrl.h"
#include "sort.h"
#include "vector.h"


void TestMakeTransaction(){
    int value = 10000;
    signed char type = -1;
    unsigned char day_of_month = 30;
    Transaction t = make_transaction(value, type, day_of_month);
    
    assert(value == t.value);
    assert(type == t.type);
    assert(day_of_month == t.day_of_month);
}

void TestMakeRepo(){
    Repository* repo = make_repository();
    assert(repo->transactions->crt_len == 0);
    destroy_repository(repo);
}

void TestRepoAddTransaction(){
    Repository* repo = make_repository();
    Transaction t = make_transaction(1000, 1, 30);
    Transaction* trans = repo->transactions->contents;
    assert(repo_add_transaction(repo, t) ==  EXIT_SUCCESS);
    assert(trans[0].day_of_month ==  30);
    assert(trans[0].value ==  1000);
    assert(trans[0].type ==  1);

    for(size_t i = 1; i < MAX_LEN; ++i){
        assert(repo_add_transaction(repo, t) ==  EXIT_SUCCESS);
    }
    destroy_repository(repo);
}

void TestIsValid(){
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

    //
}

void TestRestrict(){
    // --- type ---
    assert(restrict_type(-1) ==  OUT);
    assert(restrict_type(-1000) ==  OUT);
    assert(restrict_type(1) ==  IN);
    assert(restrict_type(1000) ==  IN);
    // for safety
    assert(restrict_type(0) ==  0);

    // --- day of month ---
    // How do you test if something is of a certain type?

    for(int i = 1; i <=31; ++i)
    assert(restrict_day_of_month(i) ==  (unsigned char)i);

    // --- value ---
    assert(restrict_transaction_value(INT_MAX) ==  INT_MAX);
}

void TestMakeBankCtrl(){
    BankCtrl* b_ctrl =  make_BankCtrl();
    assert(b_ctrl->repo != NULL);
    assert(b_ctrl->repo->transactions->crt_len ==  0);
    destroy_BankCtrl(b_ctrl);
}

void TestCtrlAddTransaction(){
    BankCtrl* b_ctrl = make_BankCtrl();

    char valid_value[] = "3000";
    char invalid_value[] = "-1";

    char valid_day[] = "30";
    char invalid_day_1[] = "0";
    char invalid_day_2[] = "40";

    char valid_type[] = "-1";
    char invalid_type[] = "0";


    assert(ctrl_add_transaction(b_ctrl, valid_value, valid_day, valid_type) ==  EXIT_SUCCESS);
    assert(ctrl_add_transaction(b_ctrl, invalid_value, valid_day, valid_type) == -1);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_1, valid_type) == -2);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, valid_type) == -2);
    assert(ctrl_add_transaction(b_ctrl, valid_value, valid_day, invalid_type) == -3);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, valid_type) == -2);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, invalid_type) == -2);

    destroy_BankCtrl(b_ctrl);
}

void TestQuicksort(){
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
        assert(list[i].value <= list[i+1].value);
    }

    quicksort(list, 0, 6, cmp_transactions_value, DESC);
    for(int i = 0; i <= 5; ++i){
        assert(list[i].value >=list[i+1].value);
    }

    quicksort(list, 0, 6, cmp_transactions_day_of_month, ASC);

    for(int i = 0; i <= 5; ++i){
        assert(list[i].day_of_month <= list[i+1].day_of_month);
    }

    quicksort(list, 0, 6, cmp_transactions_day_of_month, DESC);
    for(int i = 0; i <= 5; ++i){
        assert(list[i].day_of_month >= list[i+1].day_of_month);
    }
}

void TestCreateVector(){
    Vector* v = make_vector(TRANSACTION);
    assert(v->max_len == INITIAL_MAX_SIZE);
    assert(v->crt_len == 0);
    assert(v->element_size == sizeof(Transaction));
    destroy_vector(v);
}

void TestExtendVector(){
    Vector* v = make_vector(TRANSACTION);
    extend(v);
    assert(v->max_len == INITIAL_MAX_SIZE * EXTEND_FACTOR);
    assert(v->element_size == sizeof(Transaction));
    destroy_vector(v);
}

void TestPushBackVector(){
    Vector* v = make_vector(TRANSACTION);
    Transaction t = make_transaction(3000, 1, 30);
    size_t stop = v->max_len * 2;
    for(int i = 0; i <= stop; ++i){
        push_back(v, &t);
    }

    for(int i = 0; i <= stop; ++i){
        Transaction* transactions = (Transaction*)v->contents;
        assert(transactions[i].day_of_month == 30);
        assert(transactions[i].value == 3000);
        assert(transactions[i].type == 1);
    }

    assert(v->max_len == INITIAL_MAX_SIZE * EXTEND_FACTOR * EXTEND_FACTOR);
    assert(v->element_size == sizeof(Transaction));
    destroy_vector(v);
}

void TestCopyVector(void){
    Vector* original = make_vector(TRANSACTION);
    Transaction t = make_transaction(3000, 1, 30);
    size_t stop = original->max_len * 2;
    for(int i = 0; i <= stop; ++i){
        push_back(original, &t);
    }

    Vector* new = copy_vector(original);
    assert(new != NULL);

    for(int i = 0; i <= stop; ++i){
        Transaction* transactions = (Transaction*)new->contents;
        assert(transactions[i].day_of_month == 30);
        assert(transactions[i].value == 3000);
        assert(transactions[i].type == 1);
    }

    assert(new->max_len == original->max_len);
    assert(new->element_size == original->element_size);
    assert(new->crt_len == original->crt_len);
    destroy_vector(original);
    destroy_vector(new);
}

void log_test(char* name, int test_count){
    static int crt_pos = 1;
    double percent = crt_pos++ * (100.0 / test_count);

    printf("| %s %.2lf%%\n", name, percent);
}

void runAllTests(void){
    int test_count = 12;
    TestMakeBankCtrl();
    log_test("TestMakeBankCtrl", test_count);
    TestCtrlAddTransaction();
    log_test("TestCtrlAddTransaction", test_count);

    TestCreateVector();
    log_test("TestCreateVector", test_count);
    TestExtendVector();
    log_test("TestExtendVector", test_count);
    TestPushBackVector();
    log_test("TestPushBackVector", test_count);
    TestCopyVector();
    log_test("TestPushBackVector", test_count);

    TestQuicksort();
    log_test("TestQuicksort", test_count);
    TestIsValid();
    log_test("TestIsValid", test_count);
    TestMakeTransaction();
    log_test("TestMakeTransaction", test_count);
    TestMakeRepo();
    log_test("TestMakeRepo", test_count);
    TestRestrict();
    log_test("TestRestrict", test_count);
    TestRepoAddTransaction();
    log_test("TestRepoAddTransaction", test_count);
    puts("All tests ran successfully!\n\n");
}