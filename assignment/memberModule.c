#include "header.h"
void viewInfo(char username[21]);


void memberModule(char username[21]) {
    int option;
    
    while (1) {
        printf("Please choose your option: \n");
        printf("1. View info\n");
        printf("2. Make a purchase\n");
        printf("3. Purchase History\n");
        printf("4. View referral\n");
        printf("> ");
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
        default:
            printf("Invalid choice. Please enter again.\n");
        }
    }
}

void viewInfo(char username[21]) {
    int option, chg;
    mDetails viewDetails, chgDetails;
    FILE* fdetails = fopen("memberDetails.txt", "a+");
    if (fdetails == NULL) {
        printf("Error in opening file.\n");
        return;
    }
    while (fscanf(fdetails, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", &viewDetails.lDetails.username, &viewDetails.name, &viewDetails.gender, &viewDetails.ic, &viewDetails.phoneNo) != EOF) {
        if (strcmp(username, viewDetails.lDetails.username) == 0) {
            printf("\nMEMBER INFO:\n\n");
            printf("%-24s%-24s%-10s%-16s%-12s\n", "USERNAME", "NAME", "GENDER", "IC", "PHONE NO.");
            printf("%-24s%-24s%-10s%-16s%-12s\n", "========", "====", "======", "==", "=========");
            printf("%-24s%-24s%-10c%-16s%-12s\n\n\n", username, viewDetails.name, viewDetails.gender, viewDetails.ic, viewDetails.phoneNo);
        }
    } 
    fclose(fdetails);
    while (1) {
        printf("1. BACK\n");
        printf("2. EDIT DETAILS\n");
        printf("3. CHANGE PASSWORD\n");
        printf("> ");
        scanf("%d", &option);
        rewind(stdin);
        switch (option) {
        case 1:
            return;
            break;
        case 2:
            //incase customer does not change any details
            strcpy(chgDetails.name, viewDetails.name);
            chgDetails.gender = viewDetails.gender;
            strcpy(chgDetails.ic, viewDetails.ic);
            strcpy(chgDetails.phoneNo, viewDetails.phoneNo);
            while (1) { 
                printf("\nCHOOSE OPTION TO CHANGE DETAILS\n");
                printf("===============================\n");
                printf("1. NAME\n");
                printf("2. GENDER\n");
                printf("3. IC\n");
                printf("4. PHONE NO.\n");
                printf("5. DONE\n");
                printf("> ");
                scanf("%d", &chg);
                rewind(stdin);
                switch (chg) {
                case 1:
                    printf("Enter NAME: ");
                    scanf("%[^\n]", &chgDetails.name);
                    rewind(stdin);
                    break;
                case 2:
                    printf("Enter GENDER (M or F): ");
                    scanf("%c", &chgDetails.gender);
                    rewind(stdin);
                    toupper(chgDetails.gender);
                    if (chgDetails.gender != 'M' || chgDetails.gender != 'F') {
                        printf("Wrong input. Please try again.");
                        chgDetails.gender = viewDetails.gender;
                    }
                    break;
                case 3:
                    printf("Enter IC: ");
                    scanf("%[^\n]", &chgDetails.ic);
                    rewind(stdin);
                    break;
                case 4:
                    printf("Enter PHONE NO: ");
                    scanf("%[^\n]", &chgDetails.phoneNo);
                    rewind(stdin);
                    break;
                case 5:
                    while (fscanf(fdetails, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", &viewDetails.lDetails.username, &viewDetails.name, &viewDetails.gender, &viewDetails.ic, &viewDetails.phoneNo) != EOF) {
                        if (viewDetails.lDetails.username)
                    }
                        fprintf
                    return;
                    break;
                default:
                    printf("Invalid choice. Please enter again.\n");
                }
            }
        case 3:
            chgPsw();
            break;
        default:
            printf("Invalid choice. Please enter again.\n");
        }
    }
}

//void purchase()

//void pHistory()

void viewRef(char username[21]) {
    char referrer[21], referredUser[21], addRef[21];
    int no = 0, option;
    FILE* fref, *flogin;
    Login check;

    printf("\nVIEW REFERRALS\n");
    printf("==============\n");

    while (1) {
        //view referrals menu
        printf("Please choose your option: \n");
        printf("1. Add referrer\n");
        printf("2. View referrals\n");
        printf("3. Exit\n");
        printf("> ");
        scanf("%d", &option);
        rewind(stdin);
        switch (option) {
        case 1:
            //add referrer
            fref = fopen("referrals.txt", "a+");
            if (fref == NULL) {
                printf("Error in opening file.\n");
                return;
            }
            //check if user has already referred to a user
            while (fscanf(fref, "%[^|]|%[^\n]\n", &referrer, &referredUser) != EOF) {
                if (strcmp(referredUser, username) == 0) {
                    printf("You already have a referrer!\n");
                    break;
                }
            }
            //if user has no referrer:
            printf("Please enter referral USERNAME:\n");
            printf("> ");
            scanf("%[^\n]", &addRef);
            rewind(stdin);
            //check if entered username is in the system
            flogin = fopen("memberLogin.txt", "r");
            if (flogin == NULL) {
                printf("Error in opening file.\n");
                return;
            }
            while (fscanf(flogin, "%[^|]|%[^\n]\n", &check.username, &check.password) != EOF) {
                //yes, username is in the system
                if (strcmp(addRef, check.username) == 0) {
                    fprintf(fref, "%s|%s\n", addRef, username);
                    printf("Referral Added.\n");
                    return;
                }
            }
            //no username is not in the system
            printf("Username is not in the system. Please try again.\n");
            fclose(fref);
            fclose(flogin);
            break;
        case 2:
            //view referrals
            fref = fopen("referrals.txt", "a");
            if (fref == NULL) {
                printf("Error in opening file.\n");
                return;
            }

            printf("\nREFERRALS:\n\n");
            printf("%-6s%-24s\n", "NO", "USERNAME");
            printf("%-6s%-24s\n", "==", "========");
            while (fscanf(fref, "%[^|]|%[^\n]\n", &referrer, &referredUser) != EOF) {
                if (strcmp(username, referrer) == 0) {
                    no++;
                    printf("%-6d%-24s\n", no, referredUser);
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
            printf("Invalid choice. Please enter again.\n");
        }
    }

    
}