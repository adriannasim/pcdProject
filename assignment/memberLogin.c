#include "header.h"

void memberLogin() {
    Login input, compare;
    FILE * flogin;

    printf("\n WELCOME TO TWAY MLM MEMBER LOGIN PAGE.\n");
    while (1) {    
        flogin = fopen(" memberLogin.txt", "r");
        if (flogin == NULL) {
            printf("Error in opening file.\n");
            return;
        }
        printf(" Enter username: (Enter EXIT to go back to menu)\n");
        printf(" > ");
        scanf("%[^\n]", &input.username);
        rewind(stdin);
        if (strcmp("EXIT", input.username) == 0 || strcmp("exit", input.username) == 0) {
            return;
        }
        printf(" Enter password: \n");
        printf(" > ");
        scanf("%[^\n]", &input.password);
        rewind(stdin);
        while (fscanf(flogin, "%[^|]|%[^\n]\n", &compare.username, &compare.password) != EOF) {
            if (strcmp(input.username, compare.username) == 0 && strcmp(input.password, compare.password) == 0) {
                printf("\n WELCOME USER: %s\n", compare.username);
                memberModule(compare.username);
                return;
            }
        }
        printf(" WRONG USERNAME OR PASSWORD. PLEASE TRY AGAIN\n");
    }
    fclose(flogin);
}