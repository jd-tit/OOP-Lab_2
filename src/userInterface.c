//
// Created by jdt on 2022-03-06.
//

#include <stdio.h>
#include <stdlib.h>

#include "../include/userInterface.h"

void print_help_menu(void){
    /**
     * Print the help menu for the program
     * @pre: None
     * @post: The menu is printed
     */
    puts("0. Exit the program");
    puts("1. Run all tests");
    puts("2. Add a transaction");
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

    printf("\nTransaction value: ");
    fgets(value_buff, 30, stdin);

    printf("Transaction day of month: ");
    fgets(day_of_month_buff, 4, stdin);

    printf("Transaction type (1 = income, -1 = expense): ");
    fgets(type_buff, 3, stdin);

    int exit_code = ctrl_add_transaction(ctrl, value, day_of_month, type);
        switch (exit_code) {
            case EXIT_FAILURE: //malloc failed
                puts("Failed to create transaction; ran out of memory.");
                break;
            case -1: //value not valid
                printf("Value '%i' is not valid\n", value);
                break;
            case -2: //day_of_month not valid
                printf("Day of month '%i' is not valid\n", day_of_month);
                break;
            case -3: //transaction type not valid
                printf("Transaction type '%i' is not valid\n", type);
                break;
            case EXIT_SUCCESS:
                puts("Transaction added successfully!");
                break;
            default:
                printf("UNEXPECTED RETURN TYPE `%i` FROM ctrl_add_transaction!\n\n", exit_code);
        }
}

