//
// Created by jdt on 2022-03-06.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "user_interface.h"
#include "ctrl.h"
#include "convert.h"
#include "test.h"
#include "util.h"

#define CMD_BUFF_SIZE 3

void startUI() {
    /** Decide which command to run based on user input.
     * @pre: None
     * @post: If the command string given matches a known command number, execute that command
     * */
    char cmd_buff[CMD_BUFF_SIZE];
    char* cmd_read_to;
    unsigned long cmd;

    // For console output, use No Buffering, with a max buffer size of 0 characters:
    setvbuf(stdout, NULL, _IONBF, 0);


    BankCtrl* b_ctrl = make_BankCtrl();
    if(b_ctrl == NULL) {
        free(b_ctrl);
        perror("Couldn't construct a `BankCtrl`; Probably ran out of memory.");
        exit(EXIT_FAILURE);
    }

    while(true){
        print_help_menu();
        printf("-->");
        safe_input(cmd_buff, CMD_BUFF_SIZE);

        cmd = strtoul(cmd_buff, &cmd_read_to, 10);

        if(cmd_read_to == cmd_buff){
            puts("Invalid command.");
            continue;
        }

        switch (cmd) {
            case 0:
                destroy_BankCtrl(b_ctrl);
                puts("\nGoodbye!");
                exit(EXIT_SUCCESS);
            case 1:
                ui_list_transactions(b_ctrl);
                break;
            case 2:
                ui_add_transaction(b_ctrl);
                break;
            case 3:
                fill_randomly(b_ctrl->repo->transactions, 100);
                break;
            case 4:
                ui_modify_transaction(b_ctrl);
                break;
            case 5:
                ui_delete_transaction(b_ctrl);
                break;
            case 6:
                ui_filter_transactions_by_type(b_ctrl);
                break;
            case 7:
                ui_filter_transactions_by_value(b_ctrl);
                break;
            case 10:
                runAllTests();
                break;
            default:
                puts("Invalid command.");
                break;
        }
    }
}

void ui_list_transactions(BankCtrl* b_ctrl) {
    /**
     * List all stored transactions
     * @pre: none
     * @post: All the transactions are printed, or a message is shown if there are no transactions
     */
    size_t size;
    char order_by_buff[3];
    char sort_order_buff[3];

    size = b_ctrl->repo->transactions->crt_len;
    if(size == 0){
        puts("There are currently no transactions in the database.");
        return;
    }

    puts("Order by (day of month = 1, value = 2):");
    safe_input(order_by_buff, 3);

    puts("Sort order (Ascending = 1, Descending = -1):");
    safe_input(sort_order_buff, 3);

    Transaction* result = NULL;

    int exit_val = ctrl_get_sorted_transactions_copy(b_ctrl, &result, order_by_buff, sort_order_buff);
    switch (exit_val) {
        case ORDER_CRITERION_ERROR:
            printf("Order criterion %s is not valid.\n", order_by_buff);
            return;
        case SORT_ORDER_ERROR:
            printf("Sort order '%s' is not valid.\n", sort_order_buff);
            return;
        case EXIT_SUCCESS:
        default:
            break;
    }

    puts("The transactions are: ");
    for(size_t i = 0; i < size; ++i){
        Transaction t = result[i];
        ui_print_transaction(&t);
    }
    printf("\n");
    free(result);
}

void ui_print_transaction(Transaction* t){
    char type_expense[] = "Expense";
    char type_income[] = "Income";
    char* type;
    if(t->type == IN){
        type = type_income;
    } else {
        type = type_expense;
    }

    printf("ID: %4u; Day: %3hhu; Value: %10u; Type: %s\n", t->id, t->day_of_month, t->value, type);
}

void safe_input(char* buff, int buff_size){
    /**
     * Read  at most `buff_size` - 1 characters from stdin into buff,
     * or stop early if a newline character is hit, and get rid of extra characters if needed.
     * @pre: buff can contain at least `buff_size` characters, including the '\0' at the end of the string.
     * @post:   - Input is read into `buff` from stdin, with no overflow.
     *          - Characters after `buff_size` -1 are read and ignored.
     */
    fgets(buff, buff_size, stdin);
    bool line_fit = false;
    for(size_t i = 0; i < buff_size; ++i){
        if(buff[i] == '\n'){
            line_fit = true;
            break;
        }
    }
    if(!line_fit){
        clear_input_buffer();
    }
}

void print_help_menu(void){
    /**
     * Print the help menu for the program
     * @pre: None
     * @post: The menu is printed
     */
    puts("0. Exit the program");
    puts("1. List all transactions");
    puts("2. Add a transaction");
    puts("3. Add 100 random transactions");
    puts("4. Modify a transaction");
    puts("5. Delete a transaction");
    puts("6. Show transactions of a certain type");
    puts("7. Show transactions above/below a certain value");
    puts("10. Run all tests");
}

void clear_input_buffer(void){
    /**
     * Clear the stdin input buffer.
     * @pre: none
     * @post: Characters from stdin are read until a newline is hit.
     */
    int ch;
    while( (ch = getc(stdin)) != EOF && ch != '\n')
        ;
}

void ui_add_transaction(BankCtrl* ctrl){
    /**
     * Start dialogue for adding a transaction and pass details to transaction controller.
     * @pre: `ctrl` points to a valid BankCtrl object
     * @post: Input was gathered from the user and passed to controller function
     */
    char value_buff[30];
    char day_of_month_buff[4];
    char type_buff[3];

    printf("\nTransaction value:\n");
    safe_input(value_buff, 30);

    printf("Transaction day of month:\n");
    safe_input(day_of_month_buff, 4);

    printf("Transaction type (1 = income, -1 = expense):\n");
    safe_input(type_buff, 3);

    int exit_code = ctrl_add_transaction(ctrl, value_buff, day_of_month_buff, type_buff);
        switch (exit_code) {
            case EXIT_FAILURE: //malloc failed
                puts("Failed to create transaction; ran out of memory.");
                break;
            case -1: //value not valid
                printf("Value '%s' is not valid\n", value_buff);
                break;
            case -2: //day_of_month not valid
                printf("Day of month '%s' is not valid\n", day_of_month_buff);
                break;
            case -3: //transaction type not valid
                printf("Transaction type '%s' is not valid\n", type_buff);
                break;
            case EXIT_SUCCESS:
                puts("Transaction added successfully!");
                break;
            default:
                printf("UNEXPECTED RETURN TYPE `%i` FROM ctrl_add_transaction!\n\n", exit_code);
        }
}

void ui_modify_transaction(BankCtrl* b_ctrl){
    char value_buff[30];
    char id_buff[5];
    char day_of_month_buff[4];
    char type_buff[3];

    printf("\nID of transaction to modify:\n");
    safe_input(id_buff, 5);

    printf("\nNew transaction value:\n");
    safe_input(value_buff, 30);

    printf("New transaction day of month:\n");
    safe_input(day_of_month_buff, 4);

    printf("New transaction type (1 = income, -1 = expense):\n");
    safe_input(type_buff, 3);

    int exit_code = ctrl_modify_transaction(b_ctrl, id_buff, value_buff, day_of_month_buff, type_buff);
    switch (exit_code) {
        case EXIT_FAILURE: //malloc failed
            puts("Transaction not found. Maybe you've used the wrong id?");
            break;
        case -1: //value not valid
            printf("Value '%s' is not valid\n", value_buff);
            break;
        case -2: //day_of_month not valid
            printf("Day of month '%s' is not valid\n", day_of_month_buff);
            break;
        case -3: //transaction type not valid
            printf("Transaction type '%s' is not valid\n", type_buff);
            break;
        case -4:
            printf("Transaction ID '%s' is not valid\n", id_buff);
            break;
        case EXIT_SUCCESS:
            puts("Transaction modified successfully!");
            break;
        default:
            printf("UNEXPECTED RETURN TYPE `%i` FROM ctrl_add_transaction!\n\n", exit_code);
    }
}

void ui_delete_transaction(BankCtrl* b_ctrl){
    char id_buff[5];

    printf("\nID of transaction to delete:\n");
    safe_input(id_buff, 5);

    int exit_code = ctrl_delete_transaction(b_ctrl, id_buff);
    switch (exit_code) {
        case EXIT_FAILURE: //malloc failed
            puts("Transaction not found. Maybe you've used the wrong id?");
            break;
        case -1:
            printf("Transaction ID '%s' is not valid.\n", id_buff);
            break;
        case EXIT_SUCCESS:
            puts("Transaction deleted successfully!\n");
            break;
        default:
            printf("UNEXPECTED RETURN TYPE `%i` FROM ctrl_add_transaction!\n\n", exit_code);
    }
}

void ui_filter_transactions_by_type(BankCtrl* b_ctrl){
    char type_buff[3];
    printf("Transaction type to search for (1 = income, -1 = expense):\n");
    safe_input(type_buff, 3);

    Vector* matching_trans;
    int exit_value = ctrl_get_transactions_matching_type(b_ctrl, type_buff, &matching_trans);

    if(exit_value == -1){
        printf("Transaction type '%s' is not valid.", type_buff);
        return;
    }

    size_t size = matching_trans->crt_len;
    if(size == 0){
        puts("There are no transactions matching this criterion.\n");
        return;
    }

    Transaction* transactions = matching_trans->contents;
    for(size_t i = 0; i < size; ++i){
        Transaction t = transactions[i];
        ui_print_transaction(&t);
    }

    destroy_vector(matching_trans);
}

void ui_filter_transactions_by_value(BankCtrl* b_ctrl){
    char value_buff[30];
    char selection_buff[3];
    puts("Transaction value to filter by: ");
    safe_input(value_buff, 30);

    puts("Show transactions above or below the given value? (1 = above, 2 = below):");
    safe_input(selection_buff, 3);

    Vector* matching_trans;
    int exit_value = ctrl_get_transactions_matching_value(b_ctrl, value_buff, selection_buff, &matching_trans);

    if(exit_value == -1){
        printf("Transaction value '%s' is not valid.\n", value_buff);
        return;
    } else if (exit_value == -2){
        printf("'%s' is not '1' or '2'.", selection_buff);
        return;
    }

    size_t size = matching_trans->crt_len;
    if(size == 0){
        puts("There are no transactions matching this criterion.\n");
        return;
    }

    Transaction* transactions = matching_trans->contents;
    for(size_t i = 0; i < size; ++i){
        Transaction t = transactions[i];
        ui_print_transaction(&t);
    }

    destroy_vector(matching_trans);
}
