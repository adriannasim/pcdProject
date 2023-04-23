#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#pragma warning (disable: 4996)

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

#define MAX_SIZE 100