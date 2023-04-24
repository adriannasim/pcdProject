#include "header.h"

void memberModule(char username[21]);
void viewInfo(char username[21]);
void chgDet(int count, int line);
void chgPsw(char username[21]);
void purchase(char username[21]);
void pHistory(char username[21]);
void viewRef(char username[21]);

void memberLogin() {
    Login input, compare;
    mDetails reg;
    FILE* flogin, * fdetails;
    int choice;

    printf("\n WELCOME TO TWAY MLM MEMBER LOGIN PAGE.\n");
    while (1) {
        printf(" \nLogin or Register: \n");
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

void memberModule(char username[21]) {
    int option;
    
    while (1) {
        printf("\n Please choose your option: \n");
        printf(" 1. View info\n");
        printf(" 2. Make a purchase\n");
        printf(" 3. Purchase History\n");
        printf(" 4. View referral\n");
        printf(" 5. Log out\n");
        printf(" > ");
        scanf("%d", &option);
        rewind(stdin);
        switch (option) {
        case 1:
            viewInfo(username);
            break;
        case 2:
            purchase(username);
            break;
        case 3:
            pHistory(username);
            break;
        case 4:
            viewRef(username);
            break;
        case 5:
            printf(" LOGGED OUT.\n");;
            return;
        default:
            printf(" Invalid choice. Please enter again.\n");
        }
    }
}

void viewInfo(char username[21]) {
    int option, chg, count = 0, line = 0;
    mDetails viewDetails;
    FILE* fdetails = fopen("memberDetails.txt", "r"), *fchg;
    if (fdetails == NULL) {
        printf(" Error in opening file.\n");
        return;
    }
    while (fscanf(fdetails, "%[^|]|%[^|]|%c|%[^|]|%[^\n]\n", &viewDetails.lDetails.username, &viewDetails.name, &viewDetails.gender, &viewDetails.ic, &viewDetails.phoneNo) != EOF) {
        //get number of lines in the file for the size of the array
        count++;
        //show details of the logged in user
        if (strcmp(username, viewDetails.lDetails.username) == 0) {
            printf("\n MEMBER INFO:\n\n");
            printf(" %-24s%-24s%-10s%-16s%-12s\n", "USERNAME", "NAME", "GENDER", "IC", "PHONE NO.");
            printf(" %-24s%-24s%-10s%-16s%-12s\n", "========", "====", "======", "==", "=========");
            printf(" %-24s%-24s%-10c%-16s%-12s\n\n\n", username, viewDetails.name, viewDetails.gender, viewDetails.ic, viewDetails.phoneNo);
            //determine the row of which the member's username is located at
            line = count;
        }
    } 
    fclose(fdetails);
    while (1) {
        printf("\n 1. BACK\n");
        printf(" 2. EDIT DETAILS\n");
        printf(" 3. CHANGE PASSWORD\n");
        printf(" > ");
        scanf("%d", &option);
        rewind(stdin);
        switch (option) {
        case 1:
            return;
            break;
        case 2:
            chgDet(count, line, username);
            break;
        case 3:
            chgPsw(username);
            break;
        default:
            printf(" Invalid choice. Please enter again.\n");
        }
    }
}

void chgDet(int count, int line, char username[21]) {
    FILE* fdetails, *fchg;
    mDetails viewDetails, chgDetails, mArray[MAX_SIZE];
    int chg, loop = 0, cpy = 0;

    //store whole file into array for later changes
    fdetails = fopen("memberDetails.txt", "r");
    while (fscanf(fdetails, "%[^|]|%[^|]|%c|%[^|]|%[^\n]\n", &viewDetails.lDetails.username, &viewDetails.name, &viewDetails.gender, &viewDetails.ic, &viewDetails.phoneNo) != EOF) {
        strcpy(mArray[cpy].lDetails.username, viewDetails.lDetails.username);
        strcpy(mArray[cpy].name, viewDetails.name);
        mArray[cpy].gender = viewDetails.gender;
        strcpy(mArray[cpy].ic, viewDetails.ic);
        strcpy(mArray[cpy].phoneNo, viewDetails.phoneNo);
        //incase customer does not change any details
        if (strcmp(viewDetails.lDetails.username, username) == 0) {
            strcpy(chgDetails.name, viewDetails.name);
            chgDetails.gender = viewDetails.gender;
            strcpy(chgDetails.ic, viewDetails.ic);
            strcpy(chgDetails.phoneNo, viewDetails.phoneNo);
        }
        cpy++;
    }
    fclose(fdetails);
    while (1) {
        printf("\n CHOOSE OPTION TO CHANGE DETAILS\n");
        printf(" ===============================\n");
        printf(" 1. NAME\n");
        printf(" 2. GENDER\n");
        printf(" 3. IC\n");
        printf(" 4. PHONE NO.\n");
        printf(" 5. DONE\n");
        printf(" > ");
        scanf("%d", &chg);
        rewind(stdin);
        switch (chg) {
        case 1:
            printf(" Enter NAME: ");
            scanf("%[^\n]", &chgDetails.name);
            rewind(stdin);
            break;
        case 2:
            printf(" Enter GENDER (M or F): ");
            scanf("%c", &chgDetails.gender);
            rewind(stdin);
            chgDetails.gender = toupper(chgDetails.gender);
            if (chgDetails.gender != 'M' && chgDetails.gender != 'F') {
                printf(" Wrong input. Please try again.");
                chgDetails.gender = viewDetails.gender;
            }
            break;
        case 3:
            printf(" Enter IC: ");
            scanf("%[^\n]", &chgDetails.ic);
            rewind(stdin);
            break;
        case 4:
            printf(" Enter PHONE NO: ");
            scanf("%[^\n]", &chgDetails.phoneNo);
            rewind(stdin);
            break;
        case 5:
            //store changed details into the array
            for (int i = 0; i < count; i++) {
                if (i == line - 1) {
                    strcpy(mArray[i].lDetails.username, username);
                    strcpy(mArray[i].name, chgDetails.name);
                    mArray[i].gender = chgDetails.gender;
                    strcpy(mArray[i].ic, chgDetails.ic);
                    strcpy(mArray[i].phoneNo, chgDetails.phoneNo);
                }
            }
            //open file and insert whole array into file to change details
            fchg = fopen("memberDetails.txt", "w");
            if (fchg == NULL) {
                printf(" Error in opening file.\n");
                return;
            }
            for (int i = 0; i < count; i++) {
                fprintf(fchg, "%s|%s|%c|%s|%s\n", mArray[i].lDetails.username, mArray[i].name, mArray[i].gender, mArray[i].ic, mArray[i].phoneNo);
            }
            fclose(fchg);
            return;
            break;
        default:
            printf(" Invalid choice. Please enter again.\n");
        }
    }
}

void chgPsw(char username[21]) {
    char inputPsw[21], oldPsw[21], newPsw[21];
    int pLine, pCount = 0, cpy = 0;
    Login lDetails, lArray[MAX_SIZE];
    FILE* fchg, *fpsw, *fcpy;

    printf("\n CHANGE PASSWORD\n");
    printf(" ===============\n");
    //validate user identity
    printf(" Please enter current password.\n");
    printf(" > ");
    scanf("%[^\n]", &inputPsw);
    rewind(stdin);
    fpsw = fopen("memberLogin.txt", "r");
    while (fscanf(fpsw, "%[^|]|%[^\n]\n", &lDetails.username, &lDetails.password) != EOF) {
        //counting number of lines in the file for size of array
        pCount++;
        if (strcmp(username, lDetails.username) == 0) {
            pLine = pCount;
            if (strcmp(lDetails.password, inputPsw) != 0) {
                printf(" Wrong password. Please try again.\n");
                return;
            }
        }
    }
    fclose(fpsw);

    fcpy = fopen("memberLogin.txt", "r");
    while (fscanf(fcpy, "%[^|]|%[^\n]\n", &lDetails.username, &lDetails.password) != EOF) {
        //store whole file into array for later changes
        strcpy(lArray[cpy].username, lDetails.username);
        strcpy(lArray[cpy].password, lDetails.password);
        cpy++;
    }
    printf(" Please enter new password.\n");
    printf(" > ");
    scanf("%[^\n]", &newPsw);
    rewind(stdin);
    //store changed details into the array
    for (int i = 0; i < pCount; i++) {
        if (i == pLine - 1) {
            strcpy(lArray[i].password, newPsw);
        }
    }
    //open file and insert whole array into file to change details
    fchg = fopen("memberLogin.txt", "w");
    if (fchg == NULL) {
        printf(" Error in opening file.\n");
        return;
    }
    for (int i = 0; i < pCount; i++) {
        fprintf(fchg, "%s|%s\n", lArray[i].username, lArray[i].password);
    }
    fclose(fchg);
}

void purchase(char username[21]) {
    addSales(username);
}

void pHistory(char username[21]) {
    FILE* fhistory = fopen("sales.txt", "r");
    if (fhistory == NULL) {
        printf(" Error in opening file.\n");
        return;
    }
    SalesOrder pHistory;
    int count = 0;

    printf("\n VIEW PURCHASE HISTORY:\n\n");
    printf(" %-12s%-16s%-7s%-17s%-15s\n", "SALES ID", "PRODUCT CODE", "QTY", "PRODUCT PRICE", "TOTAL PRICE");
    printf(" %-12s%-16s%-7s%-17s%-15s\n", "========", "============", "===", "=============", "===========");
    while (fscanf(fhistory, "%[^|]|%[^|]|%[^|]|%d|%lf\n", &pHistory.username, &pHistory.orderID, &pHistory.code, &pHistory.qty, &pHistory.price) != EOF) {
        if (strcmp(pHistory.username, username) == 0) {
            printf(" %-12s%-16s%-7d%-17.2lf%-15.2lf\n", pHistory.orderID, pHistory.code, pHistory.qty, pHistory.price, (double)pHistory.qty* pHistory.price);
            count++;
        }
    }
    printf("\n ---------------------------\n");
    printf(" TOTAL OF %d RECORDS LISTED.\n\n", count);
}

void viewRef(char username[21]) {
    char referrer[21], referredUser[21], addRef[21];
    int no = 0, option;
    FILE* fref, *flogin, *fsales;
    Login check;
    SalesOrder com;

    printf("\n VIEW REFERRALS\n");
    printf(" ==============\n");

    while (1) {
        //view referrals menu
        printf("\n Please choose your option: \n");
        printf(" 1. Add referrer\n");
        printf(" 2. View referrals\n");
        printf(" 3. Exit\n");
        printf(" > ");
        scanf("%d", &option);
        rewind(stdin);
        switch (option) {
        case 1:
            //add referrer
            fref = fopen("referrals.txt", "a+");
            if (fref == NULL) {
                printf(" Error in opening file.\n");
                return;
            }
            //check if user has already referred to a user
            while (fscanf(fref, "%[^|]|%[^\n]\n", &referrer, &referredUser) != EOF) {
                if (strcmp(referredUser, username) == 0) {
                    printf(" You already have a referrer!\n");
                    return;
                }
            }
            //if user has no referrer:
            printf(" Please enter referral USERNAME:\n");
            printf(" > ");
            scanf("%[^\n]", &addRef);
            rewind(stdin);
            //check if entered username is in the system
            flogin = fopen("memberLogin.txt", "r");
            if (flogin == NULL) {
                printf(" Error in opening file.\n");
                return;
            }
            while (fscanf(flogin, "%[^|]|%[^\n]\n", &check.username, &check.password) != EOF) {
                //yes, username is in the system
                if (strcmp(addRef, check.username) == 0) {
                    fprintf(fref, "%s|%s\n", addRef, username);
                    printf(" Referral Added.\n");
                    fclose(fref);
                    return;
                }
            }
            //no username is not in the system
            printf(" Username is not in the system. Please try again.\n");
            fclose(fref);
            fclose(flogin);
            break;
        case 2:
            //view referrals
            fref = fopen("referrals.txt", "r");
            if (fref == NULL) {
                printf(" Error in opening file.\n");
                return;
            }
            char check;
            double totalCom = 0;

            printf("\n REFERRALS:\n\n");
            printf(" %-6s%-24s\n", "NO", "USERNAME");
            printf(" %-6s%-24s\n", "==", "========");
            while (fscanf(fref, "%[^|]|%[^\n]\n", &referrer, &referredUser) != EOF) {
                if (strcmp(username, referrer) == 0) {
                    no++;
                    printf(" %-6d%-24s\n", no, referredUser);
                }
            }
            fclose(fref);
            printf(" \n----------------------\n");
            while (1) {
                printf(" You have %d referrals. Check total received commission? (Y-Yes, N-No): \n", no);
                printf(" > ");
                scanf("%c", &check);
                rewind(stdin);
                if (toupper(check) == 'Y') {
                    fref = fopen("referrals.txt", "r");
                    fsales = fopen("sales.txt", "r");
                    while (fscanf(fref, "%[^|]|%[^\n]\n", &referrer, &referredUser) != EOF) {
                        while (fscanf(fsales, "%[^|]|%[^|]|%[^|]|%d|%lf\n", &com.username, &com.orderID, &com.code, &com.qty, &com.price) != EOF) {
                            if (strcmp(referredUser, com.username) == 0) {
                                totalCom = ((com.price* (double)com.qty) * 0.05);
                            }
                        }
                    }
                    fclose(fref);
                    fclose(fsales);
                    printf(" Your total commission is %.2lf \n\n", totalCom);
                    break;
                }
                else if (toupper(check) == 'N') {
                    break;
                }
                else {
                    printf(" Invalid input. Please enter again.\n\n");
                }
            }
            fclose(fref);
            break;
        case 3:
            //exit
            return;
            break;
        default:
            //invalid choice
            printf(" Invalid choice. Please enter again.\n");
        }
    }
}