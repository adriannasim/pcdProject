//libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#pragma warning (disable: 4996)

//structures
typedef struct{
    char username[21];
    char password[21];
} Login;

typedef struct {
    Login lDetails;
    char name[21];
    char gender;
    char ic[13];
    char phoneNo[12];
} mDetails;

typedef struct {
	char orderID[5];
	char code[3];
	int qty;
	double price, tPrice;
	char username[21];
	char uplineID[5];
	double comm;
} SalesOrder;

typedef struct {
	char code[5], desc[50];
	double price;
	int qty, mlvl, rqty;
} record;

struct Shipment {
    char senderName[20];
    char senderAddress[20];
    char trackingNumber[20];
    char receiverName[50];
    char receiverAddress[100];
    char trackingstatus[20];
    float weight;
    float shippingCost;
};

typedef struct {
    char senderName[20];
    char senderAddress[20];
    char trackingNumber[20];
    char receiverName[50];
    char receiverAddress[100];
    char trackingstatus[20];
    float weight;
    float shippingCost;
} Shipment;

struct Stock {
    char code[3];
    char description[30];
    double price;
    int qtyInStock;
    int minLvl;
    int reorderQty;
};

//constants
#define MAX_SIZE 100
#define MAX_SHIPMENTS 100