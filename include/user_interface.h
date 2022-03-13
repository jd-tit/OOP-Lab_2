//
// Created by jdt on 2022-03-05.
//

#ifndef LAB2_USER_INTERFACE_H
#define LAB2_USER_INTERFACE_H

#include "ctrl.h"

void print_help_menu(void);
void ui_add_transaction(BankCtrl* ctrl);
void startUI();
void clear_input_buffer(void);
void safe_input(char* buff, int buff_size);
void ui_print_transaction(Transaction* t);
void ui_modify_transaction(BankCtrl* b_ctrl);
void ui_delete_transaction(BankCtrl* b_ctrl);
void ui_filter_transactions_by_type(BankCtrl* b_ctrl);
void ui_list_transactions(BankCtrl* b_ctrl);
void ui_filter_transactions_by_value(BankCtrl* b_ctrl);

#endif //LAB2_USER_INTERFACE_H
