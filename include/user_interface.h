//
// Created by jdt on 2022-03-05.
//

#ifndef LAB2_USER_INTERFACE_H
#define LAB2_USER_INTERFACE_H

#include "ctrl.h"

/**
 * Print the help menu.
 */
void print_help_menu(void);

/**
 * Start UI dialogue to add a Transaction, then pass collected info to given Controller object
 * @param ctrl - the Controller to pass information to
 */
void ui_add_transaction(BankCtrl* ctrl);

/**
 * Start the REPL.
 */
void startUI();

/**
 * Read all characters left in the input buffer after a read, until either an EOF or a newline character is hit.
 */
void clear_input_buffer(void);

/**
 * Get input from the console, safely.
 * @param buff - the buffer to put the result in.
 * @param buff_size - the max number of characters that can be put in the buffer.
 * @post At most `buff_size` - characters of input will be put in the buffer (the last is reserved for the string
 *                  terminator)
 */
void safe_input(char* buff, int buff_size);

/**
 * Print a given transaction to the console.
 * @param t - the transaction to be printed.
 */
void ui_print_transaction(Transaction* t);


/**
 * Start UI dialogue to modify a transaction, then pass collected info to given Controller object.
 * @param b_ctrl - the controller to pass information to
 */
void ui_modify_transaction(BankCtrl* b_ctrl);


/**
  * Start UI dialogue to delete a transaction, then pass collected info to given Controller object.
 * @param b_ctrl - the controller to pass information to
 */
void ui_delete_transaction(BankCtrl* b_ctrl);


/**
 * Show transaction matching a type given by the user.
 * @param b_ctrl - the controller to pass information to
 */
void ui_filter_transactions_by_type(BankCtrl* b_ctrl);

/**
 * List all transactions tracked by a given controller object.
 * @param b_ctrl - the bank controller
 */
void ui_list_transactions(BankCtrl* b_ctrl);


/**
 * Show transaction above or below a given value.
 * @param b_ctrl
 */
void ui_filter_transactions_by_value(BankCtrl* b_ctrl);

#endif //LAB2_USER_INTERFACE_H
