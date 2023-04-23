#include "header.h"

void memberLogin() {
    Login input, compare;
    mDetails reg;
    FILE * flogin, *fdetails;
    int choice;

    printf("\n WELCOME TO TWAY MLM MEMBER LOGIN PAGE.\n");
    while (1) {
        printf(" Login or Register: \n");
        printf(" 1. Login\n");
        printf(" 2. Register\n");
        printf(" 3. Exit\n");
        printf(" > ");
        scanf("%d", &choice);
        rewind(stdin);
        if (choice == 1) {
            //login
            while (1) {
                flogin = fopen("memberLogin.txt", "r");
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
        else if (choice == 2) {
            //register
            while (1) {
                flogin = fopen("memberLogin.txt", "a");
                fdetails = fopen("memberDetails.txt", "a");
                if (flogin == NULL || fdetails == NULL) {
                    printf("Error in opening file.\n");
                    return;
                }

                while (1) {
                    printf(" Enter USERNAME: (Enter EXIT to go back to menu)\n");
                    printf(" > ");
                    scanf("%[^\n]", &reg.lDetails.username);
                    rewind(stdin);
                    if (strcmp("EXIT", reg.lDetails.username) == 0 || strcmp("exit", reg.lDetails.username) == 0) {
                        return;
                    }
                    else if (strlen(reg.lDetails.username) > 20) {
                        printf(" Enter only 12 characters.\n");
                    }
                    else {
                        break;
                    }
                }

                while (1) {
                    printf(" Enter PASSWORD: \n");
                    printf(" > ");
                    scanf("%[^\n]", &reg.lDetails.password);
                    rewind(stdin);
                    if (strlen(reg.lDetails.password) > 20) {
                        printf(" Enter only 20 characters.\n");
                    }
                    else {
                        break;
                    }
                }

                while (1) {
                    printf(" Enter NAME: \n");
                    printf(" > ");
                    scanf("%[^\n]", &reg.name);
                    rewind(stdin);
                    if (strlen(reg.name) > 20) {
                        printf(" Enter only 20 characters.\n");
                    }
                    else {
                        break;
                    }
                }

                while (1) {
                    printf(" Enter GENDER (M - Male, F - Female): \n");
                    printf(" > ");
                    scanf("%c", &reg.gender);
                    rewind(stdin);
                    if (reg.gender != 'M' && reg.gender != 'F') {
                        printf(" Wrong input. Please try again.");
                    }
                    else {
                        break;
                    }
                }

                while (1) {
                    printf(" Enter IC: \n");
                    printf(" > ");
                    scanf("%[^\n]", &reg.ic);
                    rewind(stdin);
                    if (strlen(reg.ic) > 12) {
                        printf(" Enter only 12 characters.\n");
                    }
                    else {
                        break;
                    }
                }

                while (1) {
                    printf(" Enter PHONE NO. : \n");
                    printf(" > ");
                    scanf("%[^\n]", &reg.phoneNo);
                    rewind(stdin);
                    if (strlen(reg.phoneNo) > 11) {
                        printf(" Enter only 11 characters.\n");
                    }
                    else {
                        break;
                    }
                }
                break;
            }
            fprintf(fdetails, "%s|%s|%c|%s|%s\n", reg.lDetails.username, reg.name, reg.gender, reg.ic, reg.phoneNo);
            fprintf(flogin, "%s|%s\n", reg.lDetails.username, reg.lDetails.password);
            fclose(flogin);
            fclose(fdetails);
        }
        else if (choice == 3) {
            return;
        }
        else {
            printf(" INVALID INPUT. PLEASE TRY AGAIN.\n");
        }
    }
}