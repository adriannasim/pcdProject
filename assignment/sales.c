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

void main() {
	// allow user to input selection
	char username[21];
	int option = 6;
	while (option != 0) {
		printf("============================================\n");
		printf("Main Menu\n");
		printf("1.Add Sales\n");
		printf("2.View Sales\n");
		printf("3.Edit Sales details\n");
		printf("4.Search Sales\n");
		printf("5.Generate Sales Report\n");
		printf("6.Delete Sales Record\n");
		printf("0.Exit\n");
		printf("============================================\n");
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
	int option = 4;
	char code[100];
	int found = 0, id = 0, codes = 0, qty = 0, pricet = 0;
	char tempID[5], tempCode[3];
	int tempQty;
	double tempPrice;
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
				printf("Search By: ");
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
				scanf("%s", &tempID);

				printf("%-20s%-20s%-20s%-20s\n", "Order ID", "Item Code", "Item Quantity", "Price");


				if (strcmp(order.orderID, tempID) == 0) {
					printf("%-20s%-20s%-20d%-20.2lf\n", order.orderID, order.code, order.qty, order.price);
					printf("___________________________________________________________________________\n");
					id++;
				}
			}
			if (id > 0) {
				printf("%d matches were found\n", id);
			}
			else {
				printf("0 Matches found. Please make sure format entered is correct\n");
			}
			break;
			case 2:
			{
				char tempCode[3];
				printf("\nPlease enter the item Code : ");
				scanf("%s", tempCode);

				printf("%-20s%-20s%-20s%-20s\n", "Order ID", "Item Code", "Item Quantity", "Price");

				int codes = 0; // initialize codes to 0
				FILE* rPtr = fopen("sales.txt", "r");
				if (rPtr == NULL) {
					printf("Error file open!\n");
					exit(-1);
				}

				SalesOrder order;
				while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID, order.code, &order.qty, &order.price) != EOF) {
					if (strcmp(order.code, tempCode) == 0) {
						printf("%-20s%-20s%-20d%-20.2lf\n", order.orderID, order.code, order.qty, order.price);
						printf("___________________________________________________________________________\n");
						codes++;
					}
				}
				fclose(rPtr);

				if (codes > 0) {
					printf("%d matches were found\n", codes);
				}
				else {
					printf("0 Matches found. Please make sure format entered is correct\n");
				}
			}
			break;
			case 3:
			{
				int tempQty;
				printf("\nPlease enter the item quantity : ");
				rewind(stdin);
				scanf("%d", &tempQty);
				printf("%-20s%-20s%-20s%-20s\n", "Order ID", "Item Code", "Item Quantity", "Price");
				while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID, order.code, &order.qty, &order.price) != EOF) {
					if (order.qty == tempQty) {
						printf("%-20s%-20s%-20d%-20.2lf\n", order.orderID, order.code, order.qty, order.price);
						printf("___________________________________________________________________________\n");
						qty++;
					}
				}
			}
			if (qty > 0) {
				printf("%d match were found\n", qty);
			}
			else {
				printf("0 Matches found.Please make sure format entered is correct\n");
			}
			break;
			case 4:
			{
				double tempPrice;
				printf("\nPlease enter the item Price : ");
				rewind(stdin);
				scanf("%lf", &tempPrice);
				printf("%-20s%-20s%-20s%-20s\n", "Order ID", "Item Code", "Item Quantity", "Price");

				rewind(rPtr); // move the file pointer back to the beginning of the file

				int pricet = 0; // initialize the count of matching records to zero
				while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID, order.code, &order.qty, &order.price) != EOF) {
					if (order.price == tempPrice) {
						printf("%-20s%-20s%-20d%-20.2lf\n", order.orderID, order.code, order.qty, order.price);
						printf("___________________________________________________________________________\n");
						pricet++;
					}
				}
				if (pricet > 0) {
					printf("%d match were found\n", pricet);
				}
				else {
					printf("0 Matches found.Please make sure format entered is correct\n");
				}
				break;
			}
			case 5:
				return;
				break;
			default:
				printf("Invalid input\n");
				break;
			}
		} while (option != 5);

	}		fclose(rPtr);
}
//generate sales report
void salesReport() {
	FILE* rPtr = fopen("sales.txt", "r");
	if (rPtr == NULL) {
		printf("Error file open!\n");
		exit(-1);
	}
	double total = 0.0;
	SalesOrder order;
	printf("_______________Sales Report_________________\n");
	printf("_____________________________________________\n");
	printf("Item Code\t\tQuantity\tPrice\tTotal sales\n");
	while (fscanf(rPtr, "%[^|]|%[^|]|%d|%lf\n", order.orderID,order.code, &order.qty, &order.price) != EOF) {
		// print the sales report
		order.tPrice = order.qty * order.price;
		total += order.tPrice;
		printf("%s\t\t\t%d\t\t%.lf\t%.2lf\n", order.code,order.qty,order.price,order.tPrice);
	}
	printf("\t\t\t\t\t\t__________\n");
	printf("\t\t\t\t\t\t%.2lf\n",total);
	printf("________________________________________________\n");	
	fclose(rPtr);
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