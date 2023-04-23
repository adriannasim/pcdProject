#include "header.h"
void viewInfo(char username[21]);
void chgDet(int count, int line);
void chgPsw(char username[21]);
void viewRef(char username[21]);

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
            //purchase();
            break;
        case 3:
            //pHistory();
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
    int option, chg, count = 0, line;
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
            chgDet(count, line);
            break;
        case 3:
            chgPsw(username);
            break;
        default:
            printf(" Invalid choice. Please enter again.\n");
        }
    }
}

void chgDet(int count, int line) {
    FILE* fdetails, *fchg;
    mDetails viewDetails, chgDetails, mArray[MAX_SIZE];
    int chg;

    //store whole file into array for later changes
    fdetails = fopen("memberDetails.txt", "r");
    while (fscanf(fdetails, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", &viewDetails.lDetails.username, &viewDetails.name, &viewDetails.gender, &viewDetails.ic, &viewDetails.phoneNo) != EOF) {
        for (int i = 0; i < count; i++) {
            strcpy(mArray[i].lDetails.username, viewDetails.lDetails.username);
            strcpy(mArray[i].name, viewDetails.name);
            mArray[i].gender = viewDetails.gender;
            strcpy(mArray[i].ic, viewDetails.ic);
            strcpy(mArray[i].phoneNo, viewDetails.phoneNo);
        }
    }
    fclose(fdetails);
    //incase customer does not change any details
    strcpy(chgDetails.name, viewDetails.name);
    chgDetails.gender = viewDetails.gender;
    strcpy(chgDetails.ic, viewDetails.ic);
    strcpy(chgDetails.phoneNo, viewDetails.phoneNo);
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
    int pLine, pCount = 0;
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
        for (int i = 0; i < pCount; i++) {
            strcpy(lArray[i].username, lDetails.username);
            strcpy(lArray[i].password, lDetails.password);
        }
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

//void purchase()

//void pHistory()

void viewRef(char username[21]) {
    char referrer[21], referredUser[21], addRef[21];
    int no = 0, option;
    FILE* fref, *flogin;
    Login check;

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