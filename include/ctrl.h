//
// Created by jdt on 2022-03-06.
//

#ifndef LAB2_CTRL_H
#define LAB2_CTRL_H

#include "repo.h"

enum GetErrors {ORDER_CRITERION_ERROR = -1, SORT_ORDER_ERROR = -2};
enum OrderCriteria {DAY_OF_MONTH = 1, VALUE = 2};
enum SortOrders {DESC = -1, ASC = 1};

typedef struct BankCtrl{
    Repository* repo;
} BankCtrl;

BankCtrl* make_BankCtrl(void);
int ctrl_add_transaction(BankCtrl *ctrl, char *value_buff, char *day_of_month_buff, char *type_buff);
Transaction* ctrl_get_transactions(BankCtrl* b_ctrl, size_t* size);
int ctrl_get_sorted_transactions_copy(BankCtrl *b_ctrl, Transaction **result, char *order_by_buff,
                                      char *sort_order_buff);
void destroy_BankCtrl(BankCtrl* b_ctrl);
int ctrl_modify_transaction(BankCtrl* b_ctrl, char* id_buff, char* value_buff, char* day_of_month_buff, char* type_buff);
int ctrl_delete_transaction(BankCtrl* b_ctrl, char* id_buff);
int ctrl_get_transactions_matching_type(BankCtrl* b_ctrl, char *transaction_type_buff, Vector **result);
int ctrl_get_transactions_matching_value(BankCtrl* b_ctrl, char* value_buff, char*  selection_buff, Vector** result);

#endif //LAB2_CTRL_H
