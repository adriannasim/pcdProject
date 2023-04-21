#include "header.h"

void main() {
    int login;

    do {
        printf("WELCOME TO TWAY MLM SYSTEM.\n");
        printf("Please choose MEMBER or STAFF login: \n");
        printf("1. Member\n");
        printf("2. Staff\n");
        printf("3. Exit\n");
        printf("> ");
        scanf("%d", &login);
        if (login == 1) { 
            memberLogin();
        }
        else if (login == 2) {
            //staffLogin();
        }
        else if (login == 3) {
            printf("System Shut Down.\n");
            exit(-1);
        }
        else {
            printf("Invalid choice. Please enter again.\n");
        }
    } while(1);
}