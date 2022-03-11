#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "userInterface.h"
#include "repo.h"
#include "ctrl.h"
#include "test.h"

int main() {
    // runner function
    unsigned char cmd = 0;
    BankCtrl* b_ctrl = make_BankCtrl();
    if(b_ctrl == NULL) {
        free(b_ctrl);
        perror("Couldn't construct a `BankCtrl`; Probably ran out of memory.");
        return EXIT_FAILURE;
    }

    while(true){
        print_help_menu();
        printf("-->");
        scanf("%hhu", &cmd);

        switch (cmd) {
            case 0:
                free(b_ctrl->repo);
                free(b_ctrl);
                puts("\nGoodbye!");
                return EXIT_SUCCESS;
            case 1:
                runAllTests();
                break;
            case 2:
                ui_add_transaction(b_ctrl);
                break;
            default:
                break;
        }
    }
    return 0;
}
