#include "header.h"

void readDataFromFile(struct Shipment shipments[], int* numShipments);
void searchShipment(Shipment shipments[], int numShipments);
void addShipment(Shipment shipments[], int* numShipments);
void modifyShipment(Shipment shipments[], int numShipments);
void displayShipments(Shipment shipments[], int numShipments);
void editShipmentTrackingtrackingstatus(Shipment shipments[], int numShipments);
void shipmentshippingCostCalculationReport(Shipment shipments[], int numShipments);

int shippingModule()
{
    Shipment shipments[MAX_SHIPMENTS];
    int numShipments = 0;
    readDataFromFile(shipments, &numShipments);

    int choice;
    do {
        printf("\n-----------------------------------------------------------\n");
        printf("\t\tSHIPPING INFORMATION");
        printf("\n-----------------------------------------------------------\n");
        printf("1. Add Shipment\n");
        printf("2. Search Shipment\n");
        printf("3. Modify Shipment\n");
        printf("4. Display All Shipments\n");
        printf("5. Edit Shipment Tracking status\n");
        printf("6. Shipment Cost and weight Calculation Report\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addShipment(shipments, &numShipments);
            break;
        case 2:
            searchShipment(shipments, numShipments);
            break;
        case 3:
            modifyShipment(shipments, numShipments);
            break;
        case 4:
            displayShipments(shipments, numShipments);
            break;
        case 5:
            editShipmentTrackingtrackingstatus(shipments, numShipments);
            break;
        case 6:
            shipmentshippingCostCalculationReport(shipments, numShipments);
            break;
        case 0:
            printf("Exiting program");
            break;
        default:
            printf("Invalid choice\n");
            break;

        }
    } while (choice != 0);

    int writeDataToFile(shipments, numShipments);
}

void readDataFromFile(struct Shipment shipments[], int* numShipments) {
    FILE* fp = fopen("shipping.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    char senderName[20];
    char senderAddress[20];
    char trackingNumber[20];
    char receiverName[50];
    char receiverAddress[100];
    char trackingstatus[20];
    float shippingCost;
    float weight;

    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%f,%f\n", senderName, senderAddress, trackingNumber, receiverName, receiverAddress, trackingstatus, &shippingCost, & weight) == 6) {
        strcpy(shipments[*numShipments].trackingNumber, trackingNumber);
        strcpy(shipments[*numShipments].senderName, senderName);
        strcpy(shipments[*numShipments].senderAddress, senderAddress);
        strcpy(shipments[*numShipments].receiverName, receiverName);
        strcpy(shipments[*numShipments].receiverAddress, receiverAddress);
        strcpy(shipments[*numShipments].trackingstatus, trackingstatus);
        shipments[*numShipments].shippingCost = shippingCost;
        shipments[*numShipments].weight = weight;
        (*numShipments)++;
    }

    fclose(fp);
}

void searchShipment(Shipment shipments[], int numShipments) {
    char trackingNumber[20];
    printf("\nEnter tracking number to search for: ");
    scanf("%s", trackingNumber);

    for (int i = 0; i < numShipments; i++) {
        if (strcmp(shipments[i].trackingNumber, trackingNumber) == 0) {
            printf("\n\nTracking number: %s\nRecipient name: %s\nReceiver address: %s\ntracking status: %s\nshipping Cost(RM): %.2f\nWeight(KG): %.2f\n\n",
                shipments[i].trackingNumber, shipments[i].receiverName, shipments[i].receiverAddress,
                shipments[i].trackingstatus, shipments[i].shippingCost, shipments[i].weight);
            return;
        }
    }

    printf("\nShipment not found\n");
}

void addShipment(Shipment shipments[], int* numShipments) {
    if (*numShipments == 10) {
        printf("Cannot add more shipments\n");
        return;
    }

    printf("\n\nEnter tracking number: ");
    scanf("%s", shipments[*numShipments].trackingNumber);
    printf("Enter sender name: ");
    scanf("%s", shipments[*numShipments].senderName);
    printf("Enter sender address: ");
    scanf("%s", shipments[*numShipments].senderAddress);
    printf("Enter recipient name: ");
    scanf("%s", shipments[*numShipments].receiverName);
    printf("Enter delivery address: ");
    scanf("%s", shipments[*numShipments].receiverAddress);
    printf("Enter trackingstatus: ");
    scanf("%s", shipments[*numShipments].trackingstatus);
    printf("Enter shipping Cost: ");
    scanf("%f", &shipments[*numShipments].shippingCost);
    printf("Enter weight : ");
    scanf("%f", &shipments[*numShipments].weight);

    (*numShipments)++;
    printf("\nShipment added successfully\n\n");
}

void modifyShipment(Shipment shipments[], int numShipments) {
    char trackingNumber[20];
    printf("Enter tracking number of shipment to modify: ");
    scanf("%s", trackingNumber);

    for (int i = 0; i < numShipments; i++) {
        if (strcmp(shipments[i].trackingNumber, trackingNumber) == 0) {
            printf("Enter new recipient name: ");
            scanf("%s", shipments[i].receiverName);


            printf("Enter new delivery address: ");
            scanf("%s", shipments[i].receiverAddress);
            printf("Enter new trackingstatus: ");
            scanf("%s", shipments[i].trackingstatus);
            printf("Enter new shippingCost: ");
            scanf("%f", &shipments[i].shippingCost);
            printf("Enter new weight: ");
            scanf("%f", &shipments[i].weight);
            printf("Shipment modified successfully\n");
            return;
        }
    }
    printf("Shipment not found\n");
}


void displayShipments(Shipment shipments[], int numShipments)
{
    printf("%-20s%-20s%-20s%-30s%-30s%-20s%-20s%-30s\n", "\n\nTracking Number", "Sender Name", "Sender Address", "Recipient Name", "Delivery Address", "\tTracking status", "\tShipping Cost(RM)", "\tWeight(KG)");
    for (int i = 0; i < numShipments; i++) {
        printf("%-20s%-20s%-20s%-30s%-30s\t%-20s\t%-20.2f\t%-30.2f\n", shipments[i].trackingNumber, shipments[i].senderName,
            shipments[i].senderAddress, shipments[i].receiverName,shipments[i].receiverAddress, shipments[i].trackingstatus, 
            shipments[i].shippingCost, shipments[i].weight);
    }
}

void editShipmentTrackingtrackingstatus(Shipment shipments[], int numShipments) {
    char trackingNumber[20];
    printf("\nEnter tracking number of shipment to modify: ");
    scanf("%s", trackingNumber);
    for (int i = 0; i < numShipments; i++) {
        if (strcmp(shipments[i].trackingNumber, trackingNumber) == 0) {
            printf("Enter new trackingstatus: ");
            scanf("%s", shipments[i].trackingstatus);
            printf("Shipment tracking tracking status modified successfully\n");
            return;
        }
    }
    printf("\nShipment not found\n");
}

void shipmentshippingCostCalculationReport(Shipment shipments[], int numShipments) {
    float totalshippingCost = 0;
    float totalshipingweight = 0;
    int numDelivered = 0;
    int totalweight = 0;
    int numPending = 0;
    for (int i = 0; i < numShipments; i++) {
        if (strcmp(shipments[i].trackingstatus, "Delivered") == 0)
        {
            totalshippingCost += shipments[i].shippingCost;
            numDelivered++;

            totalshipingweight += shipments[i].weight;
           totalweight++;

            printf("Shipment %d has been delivered.\n", i + 1);
        }
        else {
            numPending++;
            printf("Shipment %d has not been delivered.\n", i + 1);
        }
    }

    printf("Number of delivered shipments: %d\n", numDelivered);
    printf("Number of pending shipments: %d\n", numPending);
    printf("Total Cost of delivered shipments: %.2f\n", totalshippingCost);
    printf("Total Weight of delivered shipments: %.2f\n", totalshipingweight);
}
