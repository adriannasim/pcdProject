#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#pragma warning (disable :4996)

void addSales(char username[21]);
void searchSales();
void editSales();
void viewSales();
void deleteSales();
void salesReport();
void commission();

typedef struct {
	char orderID[5];
	char code[3];
	int qty;
	double bprice,price, tPrice;
	char username[21];
	char uplineID[5];
	double comm;
}SalesOrder;

void salesModule() {
	// allow user to input selection
	char username[21];
	int option = 7;
	while (option != 0) {
		printf("Main Menu\n");
		printf("1.Add Sales\n");
		printf("2.View Sales\n");
		printf("3.Edit Sales details\n");
		printf("4.Search Sales\n");
		printf("5.Generate Sales Report\n");
		printf("6.Delete Sales Record\n");
		printf("7.Commission\n");
		printf("0.Exit\n");
		printf("Enter your selection : ");
		scanf("%d", &option);
		rewind(stdin);
		//check user selection and link to the module
		switch (option) {
		case 1:
			addSales(username);
			break;
		case 2:
			viewSales();
			break;
		case 3:
			editSales();
			break;
		case 4:
			searchSales();
			break;
		case 5:salesReport();
			break;
		case 6:deleteSales();
			break;
		case 7:commission();
			break;
		case 0:
			printf("Bye Bye\n");
			break;
		default:
			printf("Invalid input\n");
			break;
		}
	}
	system("pause");
}


void addSales(char username[21]) {
	FILE* wPtr;
	wPtr = fopen("sales.txt", "a+");
	if (wPtr == NULL) {
		printf("Error open file\n");
		exit(-1);
	}
	SalesOrder order;
	char con = 'Y';
	int valid = 1;
	printf("_____________________Add Sales_____________________\n");

	while (toupper(con) == 'Y') {
		// Prompt and validate order ID
		printf("Enter Order ID : ");
		do {
			scanf("%s",&order.orderID);
			rewind(stdin);
			if (strlen(order.orderID) != 4 || order.orderID[0] != 'S') {
				printf("Invalid Order ID format. Please enter a 4-character ID starting with 'S'.\nEnter Order ID : ");
				// handle the invalid input, such as asking the user to input again
			}
		} while (strlen(order.orderID) != 4 || order.orderID[0] != 'S');

		// Prompt and validate item code
		printf("Enter Item Code: ");
		do {
			scanf("%s", &order.code);
			rewind(stdin);
			if (strlen(order.code) != 2 || !isalpha(order.code[0]) || !isdigit(order.code[1])) {
				printf("Invalid item code! Please enter a 2-character code starting with a letter and ending with a number (e.g. A1, B2)\nEnter Item Code: ");
			}
		} while (strlen(order.code) != 2 || !isalpha(order.code[0]) || !isdigit(order.code[1]));

		// Prompt and validate quantity
		printf("Enter Quantity To Order: ");
		while (scanf("%d", &order.qty) != 1 || order.qty <= 0) {
			printf("Invalid quantity! Please enter a positive integer.\nEnter Quantity To Order: ");
			rewind(stdin);
		}

		// Prompt and validate price
		printf("Enter Price : ");
		while (scanf("%lf", &order.price) != 1 || order.price <= 0) {
			printf("Invalid price! Please enter a positive number.\nEnter Price : ");
			rewind(stdin);
		}

		// Write order to file and display success message
		fprintf(wPtr, "%s|%s|%d|%lf\n",order.orderID, order.code, order.qty, order.price);
		printf("Successfully added!\n ");

		// Prompt for continue or exit
		printf("Continue ? (Y - yes) (N - Exit to main menu)  > ");
		rewind(stdin);
		scanf("%c", &con);
	}
	fclose(wPtr);
}


void viewSales() {
	FILE* rPtr = fopen("sales.txt", "r");
	if (rPtr == NULL) {
		printf("Error file open!\n");
		exit(-1);
	}
	char id[100];
	int found = 0;
	SalesOrder order;
	while (fscanf(rPtr,"%[^|]|%[^|]|%d|%lf\n", order.orderID,order.code, &order.qty, &order.price) != EOF) {
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Item code \t\t: %s\n", order.code);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price(RM) \t\t: %.2lf\n", order.price);
			printf("________________________________________\n");
			found = 1;
	}

	fclose(rPtr);
}


void editSales() {
	FILE* rPtr, * wPtr;
	rPtr = fopen("sales.txt", "r+");
	wPtr = fopen("temp.txt", "w");
	if (rPtr == NULL || wPtr == NULL) {
		printf("Error file open!\n");
		exit(-1);
	}
	char id[100];
	int found = 0;
	SalesOrder order;
	printf("Enter Order ID to edit: ");
	scanf("%[^\n]", id);

	while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID,order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.orderID, id) == 0) {
			found = 1;
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Item code \t\t: %s\n", order.code);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price(RM) \t\t: %.2lf\n", order.price);
			printf("________________________________________\n");
			printf("Enter new details:\n");

			printf("Enter Item Code: ");
			rewind(stdin);
			scanf("%[^\n]",&order.code);

			printf("Enter Quantity To Order: ");
			scanf("%d", &order.qty);

			printf("Enter Price : ");
			scanf("%lf", &order.price);

			fprintf(wPtr, "%s|%s|%d|%lf\n", order.orderID,order.code, order.qty, order.price);
			printf("Sales order updated successfully!\n");
			printf("________________________________________\n");
		}
		else {
			fprintf(wPtr, "%s|%s|%d|%lf\n", order.orderID, order.code, order.qty, order.price);
		}
	}
	if (!found) {
		printf("No sales with ID %s found!\n", id);
	}
	fclose(rPtr);
	fclose(wPtr);
	remove("sales.txt");
	rename("temp.txt", "sales.txt");
}


void searchSales() {
	FILE* rPtr;
	rPtr = fopen("sales.txt", "r");
	if (rPtr == NULL) {
		printf("Error file open!\n");
		exit(-1);
	}
	int option;
	char code[100];
	int found = 0;
	int match = 0;
	char tempID[5], tempCode[5];
	SalesOrder order;
	while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID, order.code, &order.qty, &order.price) != EOF) {
		found++;
		do {
			printf("Please Select the number in which category you want to search by\n");
			printf("1. Order ID\n");
			printf("2. Code\n");
			printf("3. Quantity\n");
			printf("4. Price\n");
			printf("5. Return\n");
			do {
				printf("Search With: ");
				rewind(stdin);
				scanf("%d", &option);
				if (option < 1 || option >5) {
					printf("Invalid Input Entered !! Please select a number between 1-5 ONLY!\n");
				}
			} while (option < 1 || option >5);
			switch (option) {
			case 1:
			{
				char tempID[20];

				printf("\nPlease enter the order ID : ");
				scanf("%s", tempID); // no need to use %[^\n], just %s will do

				printf("%-20s%-20s%-20s%-20s\n", "Order ID", "Item Code", "Item Quantity", "Price");


				if (strcmp(order.orderID, tempID) == 0) {
					printf("%-20s%-20s%-20d%-20.2lf\n", order.orderID, order.code, order.qty, order.price);
					printf("___________________________________________________________________________\n");
					match++;
				}
			}
			if (match > 0) {
				printf("%d matches were found\n", match);
			}
			else {
				printf("0 Matches found. Please make sure format entered is correct\n");
			}
			break;

			case 2:
				printf("\n\nPlease enter the item Code : ");
				rewind(stdin);
				scanf("%s", &tempCode);
				printf("%-20s%-20s%-20s%-20s\n", "Order ID", "Item Code", "Item Quantity", "Price");
				printf("___________________________________________________________________________\n");
				for (int i = 0; i < found; i++) {
					if (strcmp(order.code, tempCode) == 0) {
						printf("%-20s%-20s%-20s%-20s", order.orderID, order.code, order.qty, order.price);
						match++;
					}
				}
				if (match > 0) {
					printf("%d match were found\n", match);
				}
				else {
					printf("0 Matches found.Please make sure format entered is correct\n");
				}
				break;
			}
		} while (option != 5);
		fclose(rPtr);
	}
}
//generate sales report
void salesReport() {
	FILE* rPtr = fopen("sales.txt", "r");
	if (rPtr == NULL) {
		printf("Error file open!\n");
		exit(-1);
	}

	SalesOrder order;
	double salesTotal[100] = { 0 }; // initialize all elements to zero
	while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID,order.code, &order.qty, &order.price) != EOF) {
		// print the sales report
		order.tPrice = order.qty * order.price;
		printf("_______________Sales Report_________________\n");
		printf("_____________________________________________\n");
		printf("Item Code\t\tTotal sales\n");
		printf("%s\t\t\t%.2lf\n", order.code, order.tPrice);
		printf("________________________________________________\n");
		fclose(rPtr);
	}
}

void deleteSales() {
	FILE* rPtr, * wPtr;
	char id[100];
	int found = 0;
	SalesOrder order;
	printf("Enter Order ID to delete: ");
	scanf("%s", id);
	rPtr = fopen("sales.txt", "r");
	wPtr = fopen("temp.txt", "w");
	if (rPtr == NULL || wPtr == NULL) {
		printf("Error file open!\n");
		exit(-1);
	}
	while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID,order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.orderID, id) == 0) {
			found = 1;
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Item code \t\t: %s\n", order.code);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price     \t\t: %lf\n", order.price);
			printf("________________________________________\n");
			printf("Sales order deleted successfully!\n");
		}
		else {
			fprintf(wPtr, "%s|%s|%d|%lf\n", order.orderID,order.code, order.qty, order.price);
		}
	}
	if (!found) {
		printf("No sales with Order ID %s found!\n", id);
	}
	fclose(rPtr);
	fclose(wPtr);
	remove("sales.txt");
	rename("temp.txt", "sales.txt");
}
void commission() {
	FILE* rPtr;
	rPtr = fopen("sales.txt", "r");
	if (rPtr == NULL) {
		printf("Error opening file!\n");
		exit(-1);
	}

	SalesOrder order;
	double total_comm = 0.0;
	char id[5];

	printf("Enter username : ");
	scanf("%s", id);

	printf("\n_________________________________________________________________\n");
	printf("   Order ID\t\tItem Code\tQty\tPrice(RM)\tCommission(RM)\n");
	printf("_________________________________________________________________\n");

	while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID, order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.uplineID, id) == 0) {
			order.bprice = order.price * order.qty;
			order.comm = 0.05 * order.bprice;
			total_comm += order.comm;

			printf("%10s\t\t%5s\t\t%3d\t%10.2lf\t%13.2lf\n", order.orderID, order.code, order.qty, order.price, order.comm);
		}
	}

	printf("_________________________________________________________________\n");
	printf("\t\t\t\t\tTotal Commission: RM %.2lf\n\n", total_comm);
	fclose(rPtr);
}

