#include "header.h"

void memberLogin() {
    Login input, compare;
    FILE * flogin = fopen("memberLogin.txt", "r");
    if (flogin == NULL) {
        printf("Error in opening file.\n");
        return;
    }

    printf("WELCOME TO TWAY MLM MEMBER LOGIN PAGE.\n");
    do {
        printf("Enter username: \n");
        printf("> ");
        scanf("&[^\n]", input.username);
        while(fscanf(flogin, "%[^||]%[^||]\n", &compare.username, &compare.password)!=EOF) {
            if (compare.username == input.username) {
                printf("WELCOME USER: %s\n", compare.username);
                do {
                    printf("Enter password: (Enter EXIT to go back)\n");
                    printf("> ");
                    scanf("&[^\n]", input.password);
                    if (compare.password == input.password) {
                        memberModule();
                    } else if (strcmp("EXIT", input.password) == 0 || strcmp("exit", input.password) == 0) {
                        break;
                    } else {
                        printf("WRONG PASSWORD. PLEASE TRY AGAIN\n");
                    }
                } while (1);
            }
        }
    } while (1);
}