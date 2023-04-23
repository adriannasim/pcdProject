#include "header.h"

void main() {
    int login;

    while (1) {
        printf("         _______________________\n");
        printf("        |                       |\n");
        printf("        |       WELCOME TO      |\n");
        printf("        |          TWAY         |\n");
        printf("        |                       |\n");
        printf("        |_______________________|\n");
        printf("       /                        \\\n");
        printf("      /                          \\\n");
        printf("     /          _______           \\\n");
        printf("    /          /       \\           \\\n");
        printf("   /          /         \\           \\\n");
        printf("  /          /           \\           \\\n");
        printf(" |          /_____________\\          |\n");
        printf(" |         |               |         |\n");
        printf(" |         |               |         |\n");
        printf(" |         |               |         |\n");
        printf(" |         |               |         |\n");
        printf(" |_________|_______________|_________|\n");

        printf("\n WELCOME TO TWAY MLM SYSTEM.\n");
        printf(" Please choose MEMBER or STAFF login: \n");
        printf(" 1. Member\n");
        printf(" 2. Staff\n");
        printf(" 3. Exit\n");
        printf(" > ");
        scanf("%d", &login);
        rewind(stdin);
        if (login == 1) { 
            memberLogin();
        }
        else if (login == 2) {
            //staffLogin();
            printf(" stafflogin\n");
        }
        else if (login == 3) {
            printf(" System Shut Down.\n");
            exit(-1);
        }
        else {
            printf(" Invalid choice. Please enter again.\n");
        }
    }
}