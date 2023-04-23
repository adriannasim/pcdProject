#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#pragma warning (disable :4996)

void addSales();
void searchSales();
void editSales();
void viewSales();
void deleteSales();
void salesReport();

typedef struct {
	char orderID[4];
	char code[2];
	int qty;
	double bprice,price, tPrice;
	char memberID[5];
	char uplineID[5];
	double comm;
}SalesOrder;

void main() {
	// allow user to input selection
	int sel = 6;
	while (sel != 0) {
		printf("Main Menu\n");
		printf("1.Add Sales\n");
		printf("2.View Sales\n");
		printf("3.Edit Sales details\n");
		printf("4.Search Sales\n");
		printf("5.Generate Sales Report\n");
		printf("6.Delete Sales Record\n");
		printf("0.Exit\n");
		printf("Enter your selection : ");
		scanf("%d", &sel);
		rewind(stdin);
		//check user selection and link to the module
		switch (sel) {
		case 1:
			addSales();
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


void addSales() {
	FILE* wPtr;
	wPtr = fopen("sales.txt", "a+");
	if (wPtr == NULL) {
		printf("Error open file\n");
		exit(-1);
	}
	SalesOrder order;
	char con = 'Y';
	int valid = 1;
	printf("Add Sales\n");
	printf("=========\n");

	while (toupper(con) == 'Y') {
		printf("Enter Order ID :");
		scanf("%s", order.orderID);
		if (strlen(order.orderID) != 4 || order.orderID[0] != 'S') {
			printf("Invalid Order ID format. Please enter a 4-character ID starting with 'S'.\n");
			// handle the invalid input, such as asking the user to input again
		}
		printf("Enter Member ID : ");
		scanf("%s", order.memberID);

		printf("Enter Item Code: ");
		do {
			scanf("%s", order.code);
			if (strlen(order.code) != 2 || !isalpha(order.code[0]) || !isdigit(order.code[1])) {
				printf("Invalid item code! Please enter a 2-character code starting with a letter and ending with a number (e.g. A1, B2)\nEnter Item Code: ");
			}
		} while (strlen(order.code) != 2 || !isalpha(order.code[0]) || !isdigit(order.code[1]));

		printf("Enter Quantity To Order: ");
		scanf("%d", &order.qty);

		printf("Enter Price : ");
		scanf("%lf", &order.price);

		fprintf(wPtr, "%s|%s|%s|%d|%lf\n", order.orderID, order.memberID, order.code, order.qty, order.price);
		printf("Successfully added!\n ");

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
	printf("Enter member ID: ");
	scanf("%s", id);
	while (fscanf(rPtr,"%[^|]|%[^|]|%[^|]|%d|%lf\n", order.orderID, order.memberID, order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.memberID, id) == 0) {
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Member ID \t\t: %s\n", order.memberID);
			printf("Item code \t\t: %s\n", order.code);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price(RM) \t\t: %.2lf\n", order.price);
			printf("________________________________________\n");
			found = 1;
		}
	}
	if (!found) {
		printf("No sales with member ID %s found!\n", id);
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

	while (fscanf(rPtr, "%[^|]|%[^|]|%[^|]|%d|%lf\n", order.orderID, order.memberID, order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.orderID, id) == 0) {
			found = 1;
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Member ID \t\t: %s\n", order.memberID);
			printf("Item code \t\t: %s\n", order.code);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price(RM) \t\t: %.2lf\n", order.price);
			printf("________________________________________\n");
			printf("Enter new details:\n");

			printf("Enter Item Code: ");
			rewind(stdin);
			scanf("%[^\n]", order.code);

			printf("Enter Quantity To Order: ");
			scanf("%d", &order.qty);

			printf("Enter Price : ");
			scanf("%lf", &order.price);

			fprintf(wPtr, "%s|%s|%s|%d|%lf\n", order.orderID, order.memberID, order.code, order.qty, order.price);
			printf("Sales order updated successfully!\n");
		}
		else {
			fprintf(wPtr, "%s|%s|%s|%d|%lf\n", order.orderID, order.memberID, order.code, order.qty, order.price);
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
	char code[100];
	int found = 0;
	SalesOrder order;
	printf("Enter item code to search: ");
	scanf("%s", code);

	while (fscanf(rPtr, "%[^|]|%[^|]|%[^|]|%d|%lf\n", order.orderID, order.memberID, order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.code, code) == 0) {
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Member ID \t\t: %s\n", order.memberID);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price(RM) \t\t: %.2lf\n", order.price);
			printf("________________________________________\n");
			found = 1;
		}
	}
	if (!found) {
		printf("No sales with item code %s found!\n", code);
	}
	fclose(rPtr);
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
	while (fscanf(rPtr, "%[^|]|%[^|]|%[^|]|%d|%lf\n", order.orderID, order.memberID, order.code, &order.qty, &order.price) != EOF) {
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
	while (fscanf(rPtr, "%[^|]|%[^|]|%[^|]|%d|%lf\n", order.orderID, order.memberID, order.code, &order.qty, &order.price) != EOF) {
		if (strcmp(order.orderID, id) == 0) {
			found = 1;
			printf("________________________________________\n");
			printf("Order ID  \t\t: %s\n", order.orderID);
			printf("Member ID \t\t: %s\n", order.memberID);
			printf("Item code \t\t: %s\n", order.code);
			printf("Quantity  \t\t: %d\n", order.qty);
			printf("Price     \t\t: %lf\n", order.price);
			printf("________________________________________\n");
			printf("Sales order deleted successfully!\n");
		}
		else {
			fprintf(wPtr, "%s|%s|%s|%d|%lf\n", order.orderID, order.memberID, order.code, order.qty, order.price);
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
