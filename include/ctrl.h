//
// Created by jdt on 2022-03-06.
//

#ifndef LAB2_CTRL_H
#define LAB2_CTRL_H

#include "repo.h"

enum Errors {ORDER_CRITERION_ERROR = 10, SORT_ORDER_ERROR, NOT_ABOVE_OR_BELOW_ERROR, VALUE_ERROR, DAY_OF_MONTH_ERROR,
                TRANSACTION_TYPE_ERROR, TRANSACTION_ID_ERROR};
enum OrderCriteria {DAY_OF_MONTH = 1, VALUE = 2};
enum SortOrders {DESC = -1, ASC = 1};

typedef struct BankCtrl{
    Repository* repo;
} BankCtrl;


/**
 * Create a Controller object for bank transactions.
 * @return A pointer to a BankController object, initialised with a repository, or NULL if allocation failed.
 */
BankCtrl* make_BankCtrl(void);


/**
 * Add a transaction with a given Bank Controller object.
 * @param ctrl - a pointer to the Bank Controller
 * @param value_buff - a char buffer containing the value of the Transaction
 * @param day_of_month_buff - a char buffer containing the day of month of the Transaction
 * @param type_buff - a char buffer containing the Transaction type
 * @return EXIT_SUCCESS, or one of the following errors: [VALUE_ERROR, DAY_OF_MONTH_ERROR, TRANSACTION_TYPE_ERROR]
 */
int ctrl_add_transaction(BankCtrl *ctrl, char *value_buff, char *day_of_month_buff, char *type_buff);

/**
 * Get all the Transactions from a given Bank Controller object.
 * @param b_ctrl - the bank controller
 * @param size - length of the returned array
 * @return A pointer to the Transaction-type contents of the Bank Controller
 */
Transaction* ctrl_get_transactions(BankCtrl* b_ctrl, size_t* size);

/**
 * Get a sorted copy of the Transaction-type contents of a given Bank Controller object.
 * @param b_ctrl - the Bank Controller
 * @param result - this will point to the resulting copy of the Transactions
 * @param order_by_buff - a char buffer containing the criterion to order by, in numerical form (any of the types from
 *                          the enum OrderCriteria are valid)
 * @param sort_order_buff - a char buffer containing the order to sort in, either of the values of `ASC` or `DESC`
 *                          (found in the enum SortOrders)
 * @return The exit code, either EXIT_SUCCESS or one of the errors: ORDER_CRITERION_ERROR, SORT_ORDER_ERROR.
 */
int ctrl_get_sorted_transactions_copy(BankCtrl *b_ctrl, Transaction **result, char *order_by_buff,
                                      char *sort_order_buff);




/**
 * Deallocate a BankController and its contents using their proper destructor functions.
 * @param b_ctrl - the Bank Controller to destroy.
 */
void destroy_BankCtrl(BankCtrl* b_ctrl);


/**
 * Modify a transaction.
 * @param b_ctrl - the Bank Controller containing the Transaction to be modified
 * @param id_buff - a char buffer containing the ID of the Transaction to be modified
 * @param value_buff - a char buffer containing the new Transaction value
 * @param day_of_month_buff - a char buffer containing the new Transaction day of month
 * @param type_buff - a char buffer containing the new Transaction type
 * @return The exit code, either EXIT_SUCCESS or one of the errors: VALUE_ERROR, DAY_OF_MONTH_ERROR,
 *                          TRANSACTION_TYPE_ERROR, TRANSACTION_ID_ERROR.
 */
int ctrl_modify_transaction(BankCtrl* b_ctrl, char* id_buff, char* value_buff, char* day_of_month_buff, char* type_buff);


/**
 * Delete a transaction from a given Bank Controller.
 * @param b_ctrl - the Bank Controller object
 * @param id_buff - a char buffer containing the ID of the Transaction to be deleted
 * @return The exit code, either EXIT_SUCCESS, TRANSACTION_ID_ERROR or EXIT_FAILURE. The latter only if the Transaction
 *                  couldn't be found.
 */
int ctrl_delete_transaction(BankCtrl* b_ctrl, char* id_buff);


/**
 * Get the Transactions matching a given type
 * @param b_ctrl - the Bank Controller to search in
 * @param transaction_type_buff - a char buffer containing the Transaction type to filter by
 * @param result - this will point to a Vector containing the matching transactions
 * @return The exit code, either EXIT_SUCCESS or TRANSACTION_TYPE_ERROR.
 */
int ctrl_get_transactions_matching_type(BankCtrl* b_ctrl, char *transaction_type_buff, Vector **result);


/**
 *
 * @param b_ctrl
 * @param value_buff
 * @param selection_buff
 * @param result
 * @return
 */
int ctrl_get_transactions_matching_value(BankCtrl* b_ctrl, char* value_buff, char*  selection_buff, Vector** result);

#endif //LAB2_CTRL_H