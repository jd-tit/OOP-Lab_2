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
#include "convert.h"
#include "sort.h"

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

int ctrl_add_transaction(BankCtrl *ctrl, char *value_buff, char *day_of_month_buff, char *type_buff) {
    /* Controller function for adding transactions to the database.
     * pre: void
     * post: A transaction with the given data is added to the database.
     * */
    // Transform input buffers into usable (long int) values
    long value, day_of_month, type;

    if(!str_to_s_long(value_buff, &value))
        return -1;

    if(!str_to_s_long(day_of_month_buff, &day_of_month))
        return -2;

    if(!str_to_s_long(type_buff, &type))
        return -3;

    // Check for validity & restrict to proper intervals
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

Transaction* ctrl_get_transactions(BankCtrl* b_ctrl, size_t* size){
    /**
     * Return all transactions found in database.
     */
    *size = b_ctrl->repo->transactions->crt_len;
    return b_ctrl->repo->transactions->contents;
}

int ctrl_get_sorted_transactions_copy(BankCtrl *b_ctrl, Transaction** result, char *order_by_buff,
                                      char *sort_order_buff) {
    long order_by, sort_order;
    if(!str_to_s_long(order_by_buff, &order_by))
        return ORDER_CRITERION_ERROR;
    if(!str_to_s_long(sort_order_buff, &sort_order))
        return SORT_ORDER_ERROR;

    if(!is_valid_order_type(order_by))
        return ORDER_CRITERION_ERROR;
    if(!is_valid_sort_order(sort_order))
        return SORT_ORDER_ERROR;

    cmp_ptr cmp;
    if(order_by == DAY_OF_MONTH){
        cmp = cmp_transactions_day_of_month;
    }  else {
        cmp = cmp_transactions_value;
    }

    Vector* contents_copy = copy_vector(b_ctrl->repo->transactions);
    int length = contents_copy->crt_len;
    quicksort((Transaction*)contents_copy->contents, 0,length -1, cmp, sort_order);
    *result = (Transaction*)contents_copy->contents;

    free(contents_copy);
    return EXIT_SUCCESS;
}

void destroy_BankCtrl(BankCtrl* b_ctrl){
    destroy_repository(b_ctrl->repo);
    free(b_ctrl);
}

int ctrl_modify_transaction(BankCtrl* b_ctrl, char* id_buff, char* value_buff, char* day_of_month_buff, char* type_buff){
    /* Controller function for modifying transactions in the database.
     * pre: void
     * post: The transaction with the given ID is modified using the given data, if it exists.
     *      otherwise, return an error code
     * */
    // Transform input buffers into usable (long int) values
    long value, day_of_month, type, id;

    if(!str_to_s_long(value_buff, &value))
        return -1;

    if(!str_to_s_long(day_of_month_buff, &day_of_month))
        return -2;

    if(!str_to_s_long(type_buff, &type))
        return -3;

    if(!str_to_s_long(id_buff, &id))
        return -4;

    // Check for validity & restrict to proper intervals
    if(!is_valid_transaction_value(value))
        return -1;
    unsigned r_value = restrict_transaction_value(value);

    if(!is_valid_day_of_month(day_of_month))
        return -2;
    unsigned char r_day_of_month = restrict_day_of_month(day_of_month);

    if(!is_valid_transaction_type(type))
        return -3;
    signed char r_type = restrict_type(type);

    Transaction* t = repo_find_by_id(b_ctrl->repo, id);
    if(t == NULL)
        return EXIT_FAILURE;

    t->day_of_month = r_day_of_month;
    t->value = r_value;
    t->type = r_type;
    return EXIT_SUCCESS;
}

int ctrl_delete_transaction(BankCtrl* b_ctrl, char* id_buff){
    long id;
    if(!str_to_s_long(id_buff, &id))
        return -1;
    Transaction* t = repo_find_by_id(b_ctrl->repo, id);
    if(t == NULL)
        return EXIT_FAILURE;
    Transaction* contents = b_ctrl->repo->transactions->contents;
    size_t last = b_ctrl->repo->transactions->crt_len - 1;
    *t = contents[last];
    b_ctrl->repo->transactions->crt_len -= 1;

    return EXIT_SUCCESS;
}

int ctrl_get_transactions_matching_type(BankCtrl* b_ctrl, char *transaction_type_buff, Vector **result){
    long transaction_type;
    if(!str_to_s_long(transaction_type_buff, &transaction_type)){
        return -1;
    }

    if(!is_valid_transaction_type(transaction_type))
        return -1;

    signed char type = restrict_type(transaction_type);

    size_t len = 0;
    Transaction* transactions = ctrl_get_transactions(b_ctrl, &len);
    *result = make_vector(TRANSACTION);
    for(size_t i = 0; i < len; ++i){
        if(transactions[i].type == type){
            push_back(*result, &transactions[i]);
        }
    }
    return EXIT_SUCCESS;
}

int ctrl_get_transactions_matching_value(BankCtrl* b_ctrl, char* value_buff, char*  selection_buff, Vector** result){
    long value, selection;
    if(!str_to_s_long(value_buff, &value))
        return -1;

    if(!is_valid_transaction_value(value))
        return -1;

    if(!str_to_s_long(selection_buff, &selection))
        return -2;

    if(!is_valid_order(selection))
        return -2;

    unsigned int value_r = restrict_transaction_value(value);

    bool invert = (selection == 2);

    size_t len = 0;
    Transaction* transactions = ctrl_get_transactions(b_ctrl, &len);
    *result = make_vector(TRANSACTION);
    for(size_t i = 0; i < len; ++i){
        if(!invert && transactions[i].value >= value_r || invert && transactions[i].value <= value_r){
            push_back(*result, &transactions[i]);
        }
    }
    return EXIT_SUCCESS;
}
