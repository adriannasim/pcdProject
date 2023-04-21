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
            purchase();
            break;
        case 3:
            pHistory();
            break;
        case 4:
            viewRef();
            break;
        default:
            printf("Invalid choice. Please enter again.\n");
        }
    }
}

void viewInfo(char username[21]) {
    int option;
    mDetails viewDetails;
    FILE* flogin = fopen("memberLogin.txt", "r");
    FILE* fdetails = fopen("memberLogin.txt", "a");
    if (flogin == NULL || fdetails == NULL) {
        printf("Error in opening file.\n");
        return;
    }
    while (fscanf(fdetails, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", &viewDetails.lDetails.username, &viewDetails.name, &viewDetails.gender, &viewDetails.ic, &viewDetails.phoneNo) != EOF) {
        if (strcmp(username, viewDetails.lDetails.username) == 0) {
            printf("\nMEMBER INFO:\n\n");
            printf("%-24s%-24s%-10s%-16s%-12s\n", "USERNAME", "NAME", "GENDER", "IC", "PHONE NO.");
            printf("%-24s%-24s%-10s%-16s%-12s\n", "========", "====", "======", "==", "=========");
            printf("%-24s%-24s%-10c%-16s%-12s\n\n\n", username, viewDetails.name, viewDetails.gender, viewDetails.ic, viewDetails.phoneNo);
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
                    editDetails();
                    break;
                case 3:
                    chgPsw();
                    break;
                default:
                    printf("Invalid choice. Please enter again.\n");
                }
            }
        }
    }
}

//void purchase()

//void pHistory()

void viewRef() {

}