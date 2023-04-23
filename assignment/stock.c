#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#pragma warning (disable: 4996)

struct Stock {
    char code[3];
    char description[30];
    double price; 
    int qtyInStock;
    int minLvl;
    int reorderQty;
};

void stock_header();
void add_stock();
void view_stock();
void edit_stock();
void search_stock();
void delete_stock();
void low_stock_report();

void main() {
    int option;
    stock_header();
    do {
        printf("\n +--------------------------------------------------------+\n");
        printf(" |                        MAIN MENU                       |\n");
        printf(" +--------------------------------------------------------+\n");
        printf(" | 1. Add new stock                                       |\n");
        printf(" | 2. View stock list                                     |\n");
        printf(" | 3. Edit stock list                                     |\n");
        printf(" | 4. Search stock                                        |\n");
        printf(" | 5. Delete stock                                        |\n");
        printf(" | 6. Low Stock Report                                    |\n");
        printf(" | 7. Exit                                                |\n");
        printf(" +--------------------------------------------------------+\n");

        printf("\n Enter your choice ( 1-7 ) > ");
        scanf("%d", &option);
        rewind(stdin);

        switch (option) {
        case 1:
            add_stock();
            break;
        case 2:
            view_stock();
            break;
        case 3:
            edit_stock();
            break;
        case 4:
            search_stock();
            break;
        case 5:
            delete_stock();
            break;
        case 6:
            low_stock_report();
            break;
        case 7:
            printf("\n Exiting program...\n");
            break;
        default:
            printf("\n Invalid input. Please enter a number between 1 and 7.\n");
            break;
        }

        if (option != 7) {
            char choice;
            printf("\n Press any key to return to the main menu...");
            scanf(" %c", &choice);
        }
    } while (option != 7);
    printf("\n Thank you. Have a great day!\n");
    system("pause");
}

void stock_header() {
    printf("\n");
    printf("  ________________________________________________________\n");
    printf(" |                                                        |\n");
    printf(" |              STOCK INFORMATION MANAGEMENT              |\n");
    printf(" |________________________________________________________|\n");
}

void view_stock() {
    struct Stock stock;
    FILE* fp4;
    fp4 = fopen("stock.txt", "r");
    if (fp4 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    printf("\n ================================ Stock Inventory ===============================\n");
    printf(" | %-10s | %-30s | %-8s | %-3s | %-7s | %-3s |\n", "Item Code", "Item Description", "Price", "QTY", "MinLvl", "ROD");
    printf(" |------------|--------------------------------|----------|-----|---------|-----|\n");
    while (fscanf(fp4, "%[^,],%[^,],%lf,%d,%d,%d\n", stock.code, stock.description, &stock.price, &stock.qtyInStock, &stock.minLvl, &stock.reorderQty) != EOF) {
        printf(" | %-10s | %-30s | RM %-6.2lf| %-3d | %-7d | %-3d |\n", stock.code, stock.description, stock.price, stock.qtyInStock, stock.minLvl, stock.reorderQty);
    }
    printf(" ================================================================================\n");

    fclose(fp4);
}

void add_stock() {
    struct Stock stock;

    FILE* fp;
    fp = fopen("stock.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    int valid;
    char x;

    printf("\n");
    printf(" +----------------------------+\n");
    printf(" |       Add Stock Item       |\n");
    printf(" +----------------------------+\n");
    printf("\n");


    do {
        printf(" Item code         : ");
        scanf("%[^\n]", stock.code);
        rewind(stdin);
        for (int i = 0; i < strlen(stock.code); i++) {
            stock.code[i] = toupper(stock.code[i]);
        }

        printf(" Item description  : ");
        scanf("%[^\n]", stock.description);
        rewind(stdin);

        do {
            valid = 1;
            printf(" Item price (RM)   : ");
            scanf("%lf", &stock.price);
            rewind(stdin);
            if (stock.price <= 0) {
                printf(" Invalid item price. Please enter an item price greater than zero.\n");
                valid = 0;
            }
        } while (valid == 0);

        do {
            valid = 1;
            printf(" Quantity in stock : ");
            scanf("%d", &stock.qtyInStock);
            rewind(stdin);
            if (stock.qtyInStock < 0) {
                printf(" Invalid quantity. Please enter a quantity greater than or equal to zero.\n");
                valid = 0;
            }
        } while (valid == 0);

        do {
            valid = 1;
            printf(" Minimum level     : ");
            scanf("%d", &stock.minLvl);
            rewind(stdin);
            if (stock.minLvl <= 0) {
                printf(" Invalid minimum level. Please enter a minimum level greater than zero.\n");
                valid = 0;
            }
        } while (valid == 0);

        do {
            valid = 1;
            printf(" Reorder quantity  : ");
            scanf("%d", &stock.reorderQty);
            rewind(stdin);
            if (stock.reorderQty < 0) {
                printf(" Invalid reorder quantity. Please enter a reorder quantity greater than zero.\n");
                valid = 0;
            }
        } while (valid == 0);

        fprintf(fp, "%s,%s,%.2lf,%d,%d,%d\n", stock.code, stock.description, stock.price, stock.qtyInStock, stock.minLvl, stock.reorderQty);

        printf("\n Enter 'X' to stop or any other key to continue adding: ");
        scanf(" %c", &x);
        rewind(stdin);

    } while (toupper(x) != 'X');

    fclose(fp);

    printf("\n");
    printf(" +----------------------------+\n");
    printf(" |         Stock Added        |\n");
    printf(" +----------------------------+\n");
    printf("\n New stock list: ");
    view_stock();
}

void edit_stock() {
    struct Stock stock;
    struct Stock new_stock;
    FILE* fp2;
    FILE* fp3;
    char editCode[10];
    char x;
    int stockFound = 0;
    int valid;

    fp2 = fopen("stock.txt", "r");
    if (fp2 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    fp3 = fopen("editedStock.txt", "w");
    if (fp3 == NULL) {
        printf("Error creating file!\n");
        exit(-1);
    }
     
    printf("\n");
    printf(" +---------------------------------+\n");
    printf(" |         Edit Stock List         |\n");
    printf(" +---------------------------------+\n");
    printf("\n");
    view_stock();

    do {
        printf("\n Enter item code to edit: ");
        scanf("%s", editCode);
        rewind(stdin);
        for (int i = 0; i < strlen(editCode); i++) {
            editCode[i] = toupper(editCode[i]);
        }

        while (fscanf(fp2, "%9[^,],%19[^,],%lf,%d,%d,%d\n", stock.code, stock.description, &stock.price, &stock.qtyInStock, &stock.minLvl, &stock.reorderQty) == 6) {
            if (strcmp(stock.code, editCode) == 0) {
                stockFound = 1;

                printf("\n Stock found\n");
                printf(" ============\n");
                printf(" Item Description: %s\n", stock.description);
                printf(" Item Price: %.2lf\n", stock.price);   
                printf(" Quantity In Stock: %d\n", stock.qtyInStock);
                printf(" Minimum level: %d\n", stock.minLvl);
                printf(" Reorder quantity: %d\n", stock.reorderQty);

                printf("\n Enter new data\n");
                printf(" ==============\n");
                do {
                    valid = 1;
                    printf(" Item Price: ");
                    scanf("%lf", &new_stock.price);
                    rewind(stdin);
                    if (new_stock.price <= 0) {
                        printf(" Invalid item price. Please enter an item price greater than zero.\n");
                        valid = 0;
                    }
                } while (valid == 0);
                do {
                    valid = 1;
                    printf(" Quantity In Stock: ");
                    scanf("%d", &new_stock.qtyInStock);
                    rewind(stdin);
                    if (new_stock.qtyInStock < 0) {
                        printf(" Invalid quantity. Please enter a quantity greater than or equal to zero.\n");
                        valid = 0;
                    }
                } while (valid == 0);
                do {
                    valid = 1;
                    printf(" Minimum level: ");
                    scanf("%d", &new_stock.minLvl);
                    rewind(stdin);
                    if (stock.minLvl <= 0) {
                        printf(" Invalid minimum level. Please enter a minimum level greater than zero.\n");
                        valid = 0;
                    }
                } while (valid == 0);
                do{
                    valid = 1;
                    printf(" Reorder quantity: ");
                    scanf("%d", &new_stock.reorderQty);
                    rewind(stdin);
                    if (new_stock.reorderQty < 0) {
                        printf(" Invalid reorder quantity. Please enter a reorder quantity greater than zero.\n");
                        valid = 0;
                    }
                } while (valid == 0);

                fprintf(fp3, "%s,%s,%.2lf,%d,%d,%d\n", stock.code, stock.description, new_stock.price, new_stock.qtyInStock, new_stock.minLvl, new_stock.reorderQty);
            }
            else {
                fprintf(fp3, "%s,%s,%.2lf,%d,%d,%d\n", stock.code, stock.description, stock.price, stock.qtyInStock, stock.minLvl, stock.reorderQty);
            }
        }
        if (stockFound == 0) {
            printf("\n Error: No stock found with item code < %s >\n", editCode);
        }
        else {
            printf("\n Stock record updated successfully.\n");
        }

        printf("\n Enter 'X' to stop editing or any other key to continue: ");
        scanf(" %c", &x);
        rewind(stdin);

        printf("\n New stock list: ");
        view_stock();
    } while (toupper(x) != 'X');

    fclose(fp2);
    fclose(fp3);

    remove("stock.txt");
    rename("editedStock.txt", "stock.txt");
}

void search_stock() {
    struct Stock stock;

    FILE* fp5;
    fp5 = fopen("stock.txt", "r");
    if (fp5 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    printf("\n");
    printf(" +--------------------------------------------------------------+\n");
    printf(" |                      Search Stock Item                       |\n");
    printf(" +--------------------------------------------------------------+\n");

    char searchCode[10];
    int stockFound = 0;
    char choice = 'Y';
    do {
        printf("\n Enter item code to search: ");
        scanf("%s", searchCode);
        rewind(stdin);
        for (int i = 0; i < strlen(searchCode); i++) {
            searchCode[i] = toupper(searchCode[i]);
        }

        printf("\n Search Results >\n");
        printf(" ===============================================================================\n");
        printf("  %-10s | %-32s | %-8s | %-3s | %-7s | %-3s \n", "Item Code", "Item Description", "Price", "QTY", "MinLvl", "ROD");
        printf(" ===============================================================================\n");

        rewind(fp5);

        while (fscanf(fp5, "%[^,],%[^,],%lf,%d,%d,%d\n", stock.code, stock.description, &stock.price, &stock.qtyInStock, &stock.minLvl, &stock.reorderQty) != EOF) {
            if (strcmp(stock.code, searchCode) == 0) {
                printf("  %-10s | %-32s | %-8.2lf | %-3d | %-7d | %-3d \n", stock.code, stock.description, stock.price, stock.qtyInStock, stock.minLvl, stock.reorderQty);
                stockFound = 1;
                break;
            }
        }

        if (!stockFound) {
            printf("  Item not found.\n");
        }

        printf(" ===============================================================================\n");

        printf("\n Do you want to continue? ( Y-continue, other key-exit ) : ");
        scanf(" %c", &choice);
        rewind(stdin);
        choice = toupper(choice);
        stockFound = 0;
    } while (choice == 'Y');

    fclose(fp5);
}

void delete_stock() {
    struct Stock stock;

    FILE* fp6;
    fp6 = fopen("stock.txt", "r");
    if (fp6 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    FILE* fp7;
    fp7 = fopen("temp.txt", "w");
    if (fp7 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    char deleteCode[10];
    int stockDeleted = 0;
    char choice = 'Y';

    printf("\n");
    printf(" +----------------------------+\n");
    printf(" |      Delete Stock Item     |\n");
    printf(" +----------------------------+\n");

    do {
        view_stock();
        printf("\n Enter item code to delete: ");
        scanf("%s", deleteCode);
        rewind(stdin);
        for (int i = 0; i < strlen(deleteCode); i++) {
            deleteCode[i] = toupper(deleteCode[i]);
        }

        while (fscanf(fp6, "%[^,],%[^,],%lf,%d,%d,%d\n", stock.code, stock.description, &stock.price, &stock.qtyInStock, &stock.minLvl, &stock.reorderQty) != EOF) {
            if (strcmp(stock.code, deleteCode) == 0) {
                stockDeleted = 1;
                break;
            }
        }

        rewind(fp6);
        while (fscanf(fp6, "%[^,],%[^,],%lf,%d,%d,%d\n", stock.code, stock.description, &stock.price, &stock.qtyInStock, &stock.minLvl, &stock.reorderQty) != EOF) {
            if (strcmp(stock.code, deleteCode) != 0) {
                fprintf(fp7, "%s,%s,%.2lf,%d,%d,%d\n", stock.code, stock.description, stock.price, stock.qtyInStock, stock.minLvl, stock.reorderQty);
            }
        }

        if (!stockDeleted) {
            printf("\n Item not found.\n");
        }
        else {
            fclose(fp6);
            fclose(fp7);
            remove("stock.txt");
            rename("temp.txt", "stock.txt");
            printf("\n");
            printf(" +----------------------------+\n");
            printf(" |        Stock Deleted       |\n");
            printf(" +----------------------------+\n");
        }

        printf("\n Do you want to continue? ( Y-continue, other key-exit ): ");
        scanf(" %c", &choice);
        rewind(stdin);
        choice = toupper(choice);

        fp6 = fopen("stock.txt", "r");
        fp7 = fopen("temp.txt", "w");
        stockDeleted = 0;
    } while (choice == 'Y');

    fclose(fp6);
    fclose(fp7);

    printf("\n New stock list: ");
    view_stock();
}

void low_stock_report() {
    struct Stock stock;
    FILE* fp8;
    fp8 = fopen("stock.txt", "r");
    if (fp8 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    printf("\n");
    printf(" +-------------------- Low Stock Report ------------------+\n");
    printf(" |========================================================|\n");
    printf(" | %-10s | %-25s | %-13s |\n", "Item Code", "Item Description", "QTY in Stock");
    printf(" |------------|---------------------------|---------------|\n");
    while (fscanf(fp8, "%[^,],%[^,],%lf,%d,%d,%d\n", stock.code, stock.description, &stock.price, &stock.qtyInStock, &stock.minLvl, &stock.reorderQty) != EOF) {
        if (stock.qtyInStock < stock.minLvl) {
            printf(" | %-10s | %-25s | %13d |\n", stock.code, stock.description, stock.qtyInStock);
        }
    }
    printf(" |========================================================|\n");

    fclose(fp8);
}
