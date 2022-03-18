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
#include "util.h"
#include "convert.h"


void TestMakeTransaction(){
    reset_id_counter();
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
    reset_id_counter();
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

    //order by types
    assert(is_valid_order_type(VALUE));
    assert(is_valid_order_type(DAY_OF_MONTH));
    assert(!is_valid_order_type(0));

    //display orders
    assert(is_Above_or_Below(ABOVE));
    assert(is_Above_or_Below(BELOW));
    assert(!is_Above_or_Below(0));

    //sort orders
    assert(is_valid_sort_order(ASC));
    assert(is_valid_sort_order(DESC));
    assert(!is_valid_sort_order(0));
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
    reset_id_counter();
    BankCtrl* b_ctrl = make_BankCtrl();

    char valid_value[] = "3000";
    char invalid_value[] = "-1";

    char valid_day[] = "30";
    char invalid_day_1[] = "0";
    char invalid_day_2[] = "40";

    char valid_type[] = "-1";
    char invalid_type[] = "0";


    assert(ctrl_add_transaction(b_ctrl, valid_value, valid_day, valid_type) ==  EXIT_SUCCESS);
    assert(ctrl_add_transaction(b_ctrl, invalid_value, valid_day, valid_type) == VALUE_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_1, valid_type) == DAY_OF_MONTH_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, valid_type) == DAY_OF_MONTH_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, valid_day, invalid_type) == TRANSACTION_TYPE_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, valid_type) == DAY_OF_MONTH_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, invalid_day_2, invalid_type) == DAY_OF_MONTH_ERROR);


    assert(ctrl_add_transaction(b_ctrl, "bad", "bad", "bad") ==  VALUE_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, "bad", "bad") ==  DAY_OF_MONTH_ERROR);
    assert(ctrl_add_transaction(b_ctrl, valid_value, valid_day, "bad") ==  TRANSACTION_TYPE_ERROR);

    destroy_BankCtrl(b_ctrl);
}


void TestCtrlGetTransactions(void){
    reset_id_counter();
    BankCtrl* b = make_BankCtrl();
    fill_randomly(b->repo->transactions, 100);
    Transaction* contents = b->repo->transactions->contents;
    size_t s;
    Transaction* res = ctrl_get_transactions(b, &s);

    for(int i = 0; i <= 100; ++i){
        assert(res[i].value == contents[i].value);
        assert(res[i].id == contents[i].id);
        assert(res[i].day_of_month == contents[i].day_of_month);
        assert(res[i].type == contents[i].type);
    }
    destroy_BankCtrl(b);
}

void TestCtrlGetSortedTransactionsCopy(void){
    BankCtrl* b = make_BankCtrl();
    fill_randomly(b->repo->transactions, 100);
    Transaction* contents = b->repo->transactions->contents;
    size_t s;
    Transaction* res;
    assert(ctrl_get_sorted_transactions_copy(b, &res, "1", "1") == EXIT_SUCCESS);
    for(int i = 0; i < 100; ++i){
        assert(res[i].day_of_month <= res[i+1].day_of_month);
    }
    free(res);

    assert(ctrl_get_sorted_transactions_copy(b, &res, "1", "-1") == EXIT_SUCCESS);
    for(int i = 0; i < 100; ++i){
        assert(res[i].day_of_month >= res[i+1].day_of_month);
    }
    free(res);

    assert (ctrl_get_sorted_transactions_copy(b, &res, "2", "1") == EXIT_SUCCESS);
    for(int i = 0; i < 100; ++i){
        assert(res[i].value <= res[i+1].value);
    }
    free(res);

    assert(ctrl_get_sorted_transactions_copy(b, &res, "2", "-1") == EXIT_SUCCESS);
    for(int i = 0; i < 100; ++i){
        assert(res[i].value >= res[i+1].value);
    }
    free(res);

    assert(ctrl_get_sorted_transactions_copy(b, &res, "3", "3") == ORDER_CRITERION_ERROR);
    assert(ctrl_get_sorted_transactions_copy(b, &res, "bad", "3") == ORDER_CRITERION_ERROR);
    assert(ctrl_get_sorted_transactions_copy(b, &res, "1", "3") == SORT_ORDER_ERROR);
    assert(ctrl_get_sorted_transactions_copy(b, &res, "1", "abc") == SORT_ORDER_ERROR);

    destroy_BankCtrl(b);
}

void TestCtrlModifyTransaction(void){
    reset_id_counter();
    BankCtrl* b = make_BankCtrl();
    fill_randomly(b->repo->transactions, 5);
    Transaction* contents = b->repo->transactions->contents;
    assert(ctrl_modify_transaction(b, "0" , "3000", "30", "1") == EXIT_SUCCESS);
    assert(contents[0].value == 3000);
    assert(contents[0].day_of_month == 30);
    assert(contents[0].type == 1);

    assert(ctrl_modify_transaction(b, "asd" , "3000", "30", "1") == TRANSACTION_ID_ERROR);
    assert(ctrl_modify_transaction(b, "0" , "asd", "30", "1") == VALUE_ERROR);
    assert(ctrl_modify_transaction(b, "0" , "3000", "asd", "1") == DAY_OF_MONTH_ERROR);
    assert(ctrl_modify_transaction(b, "0" , "3000", "30", "asd") == TRANSACTION_TYPE_ERROR);

    assert(ctrl_modify_transaction(b, "0" , "-3000", "30", "1") == VALUE_ERROR);
    assert(ctrl_modify_transaction(b, "0" , "3000", "0", "1") == DAY_OF_MONTH_ERROR);
    assert(ctrl_modify_transaction(b, "0" , "3000", "30", "0") == TRANSACTION_TYPE_ERROR);
    destroy_BankCtrl(b);
}

void TestCtrlDeleteTransaction(void){
    reset_id_counter();
    BankCtrl* b = make_BankCtrl();
    fill_randomly(b->repo->transactions, 5);
    size_t original_len = b->repo->transactions->crt_len;
    assert(ctrl_delete_transaction(b, "0") == EXIT_SUCCESS);
    assert(ctrl_delete_transaction(b, "0") == EXIT_FAILURE);
    assert(ctrl_delete_transaction(b, "bad") == TRANSACTION_ID_ERROR);

    assert(repo_find_by_id(b->repo, 0) == NULL);
    assert(b->repo->transactions->crt_len == original_len - 1);
    destroy_BankCtrl(b);
}

void TestCtrlGetTransactionMatchingType(void){
    reset_id_counter();
    BankCtrl* b = make_BankCtrl();
    fill_randomly(b->repo->transactions, 100);
    Vector* v;
    assert(ctrl_get_transactions_matching_type(b, "1", &v) == EXIT_SUCCESS);

    for(int i = 0; i < v->crt_len; ++i){
        Transaction* t = v->contents;
        assert(t[i].type == 1);
    }
    destroy_vector(v);

    assert(ctrl_get_transactions_matching_type(b, "-1", &v) == EXIT_SUCCESS);

    for(int i = 0; i < v->crt_len; ++i){
        Transaction* t = v->contents;
        assert(t[i].type == -1);
    }
    destroy_vector(v);

    assert(ctrl_get_transactions_matching_type(b, "0", &v) == TRANSACTION_TYPE_ERROR);
    assert(ctrl_get_transactions_matching_type(b, "bad", &v) == TRANSACTION_TYPE_ERROR);
    destroy_BankCtrl(b);
}

void TestCtrlGetTransactionMatchingValue(void){
    reset_id_counter();
    BankCtrl* b = make_BankCtrl();
    fill_randomly(b->repo->transactions, 100);
    Vector* v;
    assert(ctrl_get_transactions_matching_value(b, "100", "1", &v) == EXIT_SUCCESS);
    for(int i = 0; i < v->crt_len; ++i){
        Transaction* t = v->contents;
        assert(t[i].value >= 100);
    }
    destroy_vector(v);

    assert(ctrl_get_transactions_matching_value(b, "100000", "2", &v) == EXIT_SUCCESS);
    for(int i = 0; i < v->crt_len; ++i){
        Transaction* t = v->contents;
        assert(t[i].value <= 100000);
    }
    destroy_vector(v);

    assert(ctrl_get_transactions_matching_value(b, "-100", "2", &v) == VALUE_ERROR);
    assert(ctrl_get_transactions_matching_value(b, "bad", "2", &v) == VALUE_ERROR);
    assert(ctrl_get_transactions_matching_value(b, "100000", "0", &v) == NOT_ABOVE_OR_BELOW_ERROR);
    assert(ctrl_get_transactions_matching_value(b, "1000", "bad", &v) == NOT_ABOVE_OR_BELOW_ERROR);
    //destroy_BankCtrl(b);
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

    // test with a list where all elements are equal
    for(int i = 0; i < 7; ++i){
        list[i].value = start_value;
        list[i].day_of_month = day;
        list[i].type = IN;
    }

    quicksort(list, 0, 6, cmp_transactions_day_of_month, ASC);
    for(int i = 0; i <= 5; ++i){
        assert(list[i].day_of_month <= list[i+1].day_of_month);
    }
    quicksort(list, 0, 6, cmp_transactions_day_of_month, DESC);
    for(int i = 0; i <= 5; ++i){
        assert(list[i].day_of_month >= list[i+1].day_of_month);
    }
    quicksort(list, 0, 6, cmp_transactions_value, ASC);
    for(int i = 0; i <= 5; ++i){
        assert(list[i].value <= list[i+1].value);
    }
    quicksort(list, 0, 6, cmp_transactions_value, DESC);
    for(int i = 0; i <= 5; ++i){
        assert(list[i].value >= list[i+1].value);
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

void TestMakeRandomTransaction(void){
    for(int i = 0; i < 1000; ++i){
        Transaction t = make_random_transaction();
        assert(is_valid_transaction_value(t.value));
        assert(is_valid_day_of_month(t.day_of_month));
        assert(is_valid_transaction_type(t.value));
        assert(t.id >= 0);
    }
}

void TestFillRandomly(void){
    Vector* v = make_vector(TRANSACTION);
    const int limit = 200;
    fill_randomly(v, limit);
    Transaction* transactions = (Transaction* )v->contents;
    for(int i = 0; i < limit; ++i){
        Transaction t = transactions[i];
        assert(is_valid_transaction_value(t.value));
        assert(is_valid_day_of_month(t.day_of_month));
        assert(is_valid_transaction_type(t.value));
        assert(t.id >= 0);
    }
    destroy_vector(v);
}

void TestStrToSLong(void){
    char* bad_buff = "DEADBEEF";
    char* good_buff = "123456789";
    long result;
    assert(!str_to_s_long(bad_buff, &result));
    assert(str_to_s_long(good_buff, &result));
}

void TestCopyTransaction(void){
    Transaction t = make_transaction(3000, IN, 30);
    Transaction copy = copy_transaction(&t);

    assert(t.value == copy.value);
    assert(t.day_of_month == copy.day_of_month);
    assert(t.type == copy.type);
    assert(t.id == copy.id);
}

void TestRepoFindByID(void){
    reset_id_counter();
    Repository* r = make_repository();
    fill_randomly(r->transactions, 100);
    Transaction* t_list = r->transactions->contents;
    for(int i = 0; i <= 100; ++i){
        Transaction* tp = repo_find_by_id(r, i);
        assert(tp->value == t_list[i].value);
        assert(tp->day_of_month == t_list[i].day_of_month);
        assert(tp->type == t_list[i].type);
        assert(tp->id == t_list[i].id);
    }

    assert(repo_find_by_id(r, -100) == NULL);
    assert(repo_find_by_id(r, 101) == NULL);
    destroy_repository(r);
}

void log_test(char* name, int test_count){
    static int crt_pos = 1;
    double percent = crt_pos++ * (100.0 / test_count);

    printf("| %s %.2lf%%\n", name, percent);
}

void runAllTests(void){
    int test_count = 23;
    TestMakeBankCtrl();
    log_test("TestMakeBankCtrl", test_count);
    TestCtrlAddTransaction();
    log_test("TestCtrlAddTransaction", test_count);
    TestCopyTransaction();
    log_test("TestCopyTransaction", test_count);

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

    TestMakeRandomTransaction();
    log_test("TestMakeRandomTransaction", test_count);
    TestFillRandomly();
    log_test("TestFillRandomly", test_count);

    TestStrToSLong();
    log_test("TestStrToSLong", test_count);

    TestRepoFindByID();
    log_test("TestRepoFindByID", test_count);
    TestCtrlGetTransactions();
    log_test("TestCtrlGetTransactions", test_count);

    TestCtrlGetSortedTransactionsCopy();
    log_test("TestCtrlGetSortedTransactionsCopy", test_count);

    TestCtrlModifyTransaction();
    log_test("TestCtrlModifyTransaction", test_count);

    TestCtrlDeleteTransaction();
    log_test("TestCtrlDeleteTransaction", test_count);

    TestCtrlGetTransactionMatchingType();
    log_test("TestCtrlGetTransactionMatchingType", test_count);

    TestCtrlGetTransactionMatchingValue();
    log_test("TestCtrlGetTransactionMatchingValue", test_count);

    puts("All tests ran successfully!\n\n");
}