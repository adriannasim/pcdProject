#include "header.h"

void staffModule(char staffID[5]);
void login();
void signup();
void recovery();
void manageStaff();
void addStaff();
void modifyStaff();
void searchStaff();
void viewStaff();
void deleteStaff();

void staffLogin() {
	int action = 0;
	printf("\n STAFF LOGIN MODULE\n\n");
	printf(" 1 - Login\n 2 - Sign Up (New User)\n 3 - Password Recovery\n 4 - Back\n\n");
	printf(" Select an action > ");
	scanf("%d", &action);
	rewind(stdin);
	while (action != 1 && action != 2 && action != 3 && action != 4) {
		printf(" Invalid action! Please re-enter > ");
		scanf("%d", &action);
		rewind(stdin);
	}
	switch (action) {
	case 1:
		login();
		break;
	case 2:
		signup();
		break;
	case 3:
		recovery();
		break;
	case 4:
		main();
		break;
	default:
		printf(" Invalid action! Please re-enter > ");
		scanf("%d", &action);
	}
}
void login() {
	StaffDetails login[100];
	Credential acc;
	char stop = 'Y', con;
	int lCount = 0;
	FILE* loginptr = fopen("staff.bin","rb");
	printf("\n -------------");
	printf("\n  STAFF LOGIN\n");
	printf(" -------------\n\n");
	while (fread(&login[lCount], sizeof(StaffDetails), 1, loginptr) != 0) {
		lCount++;
	} fclose(loginptr);
	while (toupper(stop) == 'Y') {
		printf(" Enter Staff ID : ");
		scanf("%s", &acc.staffID);
		rewind(stdin);
		for (int i = 0; i < lCount; i++) {
			if (strcmp(login[i].staffID, acc.staffID) == 0) {
				printf(" Enter Password : ");
				scanf("%s", &acc.pass.password);
				rewind(stdin);
				while (1) {
					if (strcmp(login[i].acc.password, acc.pass.password) == 0 || strcmp(ADMINPW, acc.pass.password) == 0) {
						printf("\n Login Successful\n Welcome %s!\n", login[i].name);
						staffModule(login[i].name);
					}
					else {
						printf(" Incorrect Password!\n");
						printf(" Recover Password? (Y - Yes) > ");
						scanf("%c", &con);
						if (toupper(con) == 'Y') {
							recovery();
						}
						else {
							printf(" Enter Password : ");
							scanf("%s", &acc.pass.password);
							rewind(stdin);
						}
					}
				}
			} else if (strcmp(ADMIN, acc.staffID) == 0) {
				printf(" Enter Password : ");
				scanf("%s", &acc.pass.password);
				rewind(stdin);
				while (1) {
					if (strcmp(login[i].acc.password, acc.pass.password) == 0 || strcmp(ADMINPW, acc.pass.password) == 0) {
						printf("\n Login Successful\n Welcome ADMIN!\n");
						staffModule("ADMIN");
					}
					else {
						printf(" Incorrect Password!\n");
					}
				}
			}
		}
		printf(" Staff ID does not exist!\n");
		printf(" Continue Log in? (N - No) > ");
		scanf("%c", &con);
		if (toupper(con) == 'N') {
			return;
		}
	}
}
void signup() {
	StaffDetails sign[100],view;
	int sCount = 0, found = 0;
	char con = 'Y';
	FILE* rptr = fopen("staff.bin", "rb");
	while (fread(&sign[sCount], sizeof(StaffDetails), 1, rptr) != 0) {
		sCount++;
	}
	fclose(rptr);
	printf("\n -------------------");
	printf("\n  NEW STAFF SIGN UP\n");
	printf(" -------------------\n\n");
	while (toupper(con) == 'Y') {
		printf(" Enter Staff ID                      : ");
		scanf("%s", &view.staffID);
		rewind(stdin);
		for (int i = 0; i < sCount; i++) {
			if (strcmp(sign[i].staffID, view.staffID) == 0) {
				found = 1;
				while (1) {
					printf(" Enter Password (Default = Staff ID) : ");
					scanf("%s", &view.acc.password);
					rewind(stdin);
					if (strcmp(sign[i].acc.password, view.acc.password) != 0) {
						printf(" NOTE: Default password = Staff ID\n");
					} else {
						break;
					}
				}
				printf(" Enter New Password (6 digits)       : ");
				while (1) {
					scanf("%6s", &view.acc.password);
					rewind(stdin);
					if (strlen(view.acc.password) != 6) {
						printf("\n Please enter a 6 digit password!\n");
						printf(" Enter New Password (6 digits)       : ");
					}
					else {
						break;
					}
				}
				printf(" Security Question\n");
				printf(" What is your favourite animal       : ");
				scanf("%[^\n]", &view.acc.pwRecovery);
				rewind(stdin);
				while (1) {
					printf("\n Your answer will be needed for password recovery and CANNOT be changed!\n");
					printf(" Confirm Answer? (Y - Yes) > ");
					scanf("%c", &con);
					rewind(stdin);
					if (toupper(con) == 'Y') {
						printf(" New User Sign In Completed!\n");
						strcpy(view.name, sign[i].name);
						strcpy(view.position, sign[i].position);
						strcpy(view.telno, sign[i].telno);
						sign[i] = view;
						FILE* wptr = fopen("staff.bin", "wb");
						for (int i = 0; i < sCount; i++) {
							fwrite(&sign[i], sizeof(StaffDetails), 1, wptr);
						}
						fclose(wptr);
						return;
						break;
					}
					else {
						printf(" Enter New Password (6 digits)       : ");
						scanf("%6s", &view.acc.password);
						rewind(stdin);
						printf(" What is your favourite animal       : ");
						scanf("%[^\n]", &view.acc.pwRecovery);
						rewind(stdin);
					}
				}
			}
		}
	} 
	if (!found) {
		printf(" Staff ID does not exist!\n");
	}
	found = 0;
	printf("\n Continue Signing Up? (N - No) > ");
	scanf("%c", &con);
	rewind(stdin);
	printf("\n");
	if (toupper(con) == 'N') {
		return;
	}
}

void recovery() {
	StaffDetails r[100], check;
	int rCount = 0;
	char con ='Y', sure;
	FILE* vptr = fopen("staff.bin","rb"), *wptr;;
	while (fread(&r[rCount], sizeof(StaffDetails), 1, vptr) != 0){
		rCount++;
	}
	fclose(vptr);
	printf("\n -------------------");
	printf("\n  PASSWORD RECOVERY\n");
	printf(" -------------------\n\n");
	while (toupper(con) != 'N') {
		printf(" Enter Staff ID : ");
		scanf("%s", &check.staffID);
		rewind(stdin);
		for (int i = 0; i < rCount; i++) {
			if (strcmp(r[i].staffID, &check.staffID) == 0) {
				printf(" Security Question\n");
				printf(" What is your favourite animal        : ");
				scanf("%[^\n]", &check.acc.pwRecovery);
				rewind(stdin);
				if (strcmp(r[i].acc.pwRecovery, &check.acc.pwRecovery) == 0) {
					printf(" Enter New Password (6 digits)        : ");
					scanf("%6s", &check.acc.password);
					rewind(stdin);
					while (1) {
						if (strlen(check.acc.password) != 6) {
							printf("\n Please enter a 6 digit password!\n");
							printf(" Enter New Password (6 digits)        : ");
							scanf("%6s", &check.acc.password);
							rewind(stdin);
						}
						else {
							printf(" Confirm password? (Y - Yes) > ");
							scanf("%c", &sure);
							if (toupper(sure) == 'Y') {
								printf("\n Password has been successfully modified!\n");
								strcpy(r[i].acc.password, check.acc.password);
								wptr = fopen("staff.bin", "wb");
								for (int j = 0; j < rCount; j++) {
									fwrite(&r[j], sizeof(StaffDetails), 1, wptr);
								}
								fclose(wptr);
								return;
							}
							else {
								printf(" Enter New Password (6 digits)        : ");
								scanf("%6s", &check.acc.password);
								rewind(stdin);
							}
						}
					}
					break;
				}
				else {
					printf("\n Your answer doesn't match! \n Please re-try or contact an admin to retrieve your password!\n\n");
					printf(" Continue to recover password? (N - No) > ");
					scanf("%c", &con);
					if (toupper(con) == 'N') {
						return;
					}
				}
			}
		}
	}
}

void staffModule(char staffID[5]) {
	int action = 0;
	printf("\n STAFF MODULE\n\n");
	printf(" 1 - Manage Staff\n 2 - Sales Module\n 3 - Stock Module\n 4 - Shipping Module\n 5 - Return to Main Menu\n\n");
	printf(" Select an action > ");
	scanf("%d", &action);
	rewind(stdin);
	while (action != 1 && action != 2 && action != 3 && action != 4 && action != 5 && action != 6) {
		printf(" Invalid action! Please re-enter > ");
		scanf("%d", &action);
		rewind(stdin);
	}
	switch (action) {
	case 1:
		manageStaff();
		break;
	case 2:
		salesModule(staffID);
		break;
	case 3:
		stockModule();
		break;
	case 4:
		shippingModule();
		break;
	case 5:
		staffLogin();
		break;
	default:
		printf("Please enter a valid action!\n");
	}
}

void manageStaff() {
	int action = 0;
	printf("\n STAFF MANAGEMENT\n\n");
	printf(" 1 - Add Staff\n 2 - Modify Staff\n 3 - Search Staff\n 4 - View Staff\n 5 - Delete Staff\n 6 - Back\n\n");
	printf(" Select an action > ");
	scanf("%d", &action);
	rewind(stdin);
	while (action != 1 && action != 2 && action != 3 && action != 4 && action != 5 && action != 6) {
		printf(" Invalid action! Please re-enter > ");
		scanf("%d", &action);
		rewind(stdin);
	}
	switch (action) {
	case 1:
		addStaff();
		break;
	case 2:
		modifyStaff();
		break;
	case 3:
		searchStaff();
		break;
	case 4:
		viewStaff();
		break;
	case 5: 
		deleteStaff();
		break;
	case 6:
		return;
		break;
	default:
		printf(" Invalid action! Please re-enter > ");
		scanf("%d", &action);
		break;
	}
}

void addStaff() {
	char stop;
	int records = 0;
	StaffDetails staff, validate;
	FILE *addptr, *vptr;
	addptr = fopen("staff.bin", "ab");
	vptr = fopen("staff.bin", "rb");
	if (addptr == NULL || vptr == NULL) {
		printf(" Error Open File\n");
		exit(-1);
	}
	printf("\n -----------");
	printf("\n  ADD STAFF\n");
	printf(" -----------\n");
	do {
		int valid = 0;
		while (!valid) {
			printf("\n Enter Staff ID (e.g A000)                          : ");
			scanf("%4s", staff.staffID);
			rewind(stdin);
			if (strlen(staff.staffID) == 4 && isalpha(staff.staffID[0]) && isdigit(staff.staffID[1]) && isdigit(staff.staffID[2]) && isdigit(staff.staffID[3])) {
				staff.staffID[0] = toupper(staff.staffID[0]);
				while (fread(&validate, sizeof(StaffDetails), 1, vptr) != 0) {
					if (strcmp(validate.staffID, staff.staffID) == 0) {
						printf(" Staff ID already exists! Please re-check. \n");
						printf("\n Continue to add staff? (N-No) > ");
						scanf("%c", &stop);
						rewind(stdin);
						if (toupper(stop) == 'N') {
							manageStaff();
						}
						else {
							printf("\n Enter Staff ID (e.g A000)                          : ");
							scanf("%4s", staff.staffID);
							rewind(stdin);
						}
					}
				}
				valid = 1;
			}
			else {
				printf(" Invalid Staff ID format! Please try again.\n");
			}
			rewind(vptr);
		}

		printf(" Enter Staff Name                                   : ");
		scanf("%[^\n]", &staff.name);
		rewind(stdin);
		printf(" Enter Staff Position                               : ");
		scanf("%[^\n]", &staff.position);
		rewind(stdin);
		printf(" Enter Staff Contact No. (e.g 012-3456789)          : ");
		scanf("%13s", &staff.telno);
		rewind(stdin);
		while (strnlen(staff.telno, 13) != 11 && strnlen(staff.telno, 13) != 12) {
			printf(" Invalid phone number size\n\n ");
			printf("Enter Staff Contact No.                            : ");
			scanf("%13s", &staff.telno);
			rewind(stdin);
		}
		strcpy(staff.acc.password, staff.staffID);
		strcpy(staff.acc.pwRecovery, "none");

		fwrite(&staff, sizeof(StaffDetails), 1, addptr);
		printf("\n Would you like to add another staff record? (N to stop) > ");
		scanf("%c", &stop);
		records++;
	} while (toupper(stop) != 'N');
	fclose(addptr);
	printf("\n %d record(s) have been added successfully!\n", records);
	manageStaff();
}

void modifyStaff() {
	StaffDetails s[20], view;
	int sCount = 0, editCount = 0, exist = 0;
	char sure, con = 'Y';
	FILE* viewptr = fopen("staff.bin", "rb");
	while (fread(&s[sCount], sizeof(StaffDetails), 1, viewptr) != 0) {
		sCount++;
	}
	fclose(viewptr);

	printf("\n --------------");
	printf("\n  MODIFY STAFF\n");
	printf(" --------------\n");
	while(toupper(con) == 'Y') {
		printf("\n Enter Staff ID to Modify : ");
		scanf("%s", &view.staffID);
		rewind(stdin);
		for (int i = 0; i < sCount; i++) {
			if (strcmp(view.staffID, s[i].staffID) == 0) {
				printf("\n Staff ID \t Staff Name \t\t Staff Position \t Staff Contact No. \t Staff Password \t Security Answer\n");
				printf(" ======== \t ========== \t\t ============== \t ================= \t ==============\t\t ===============\n");
				printf(" %-7s \t %-20s \t %-15s \t %-15s \t %-20s \t %-20s \n",s[i].staffID, s[i].name, s[i].position, s[i].telno, s[i].acc.password, s[i].acc.pwRecovery);
				printf("\n Staff ID              : %s\n", s[i].staffID);
				printf(" Staff Name            : ");
				scanf("%[^\n]", &view.name);
				rewind(stdin);
				printf(" Staff Position        : ");
				scanf("%[^\n]", &view.position);
				rewind(stdin);
				printf(" Staff Contact Number  : ");
				scanf("%[^\n]", &view.telno);
				rewind(stdin);
				while (strnlen(view.telno, 13) != 11 && strnlen(view.telno, 13) != 12) {
					printf(" Invalid phone number size\n ");
					printf("Staff Contact Number  : ");
					scanf("%13s", &view.telno);
					rewind(stdin);
				}
				strcpy(view.acc.password, s[i].acc.password);
				strcpy(view.acc.pwRecovery, s[i].acc.pwRecovery);
				printf(" Confirm modification (Y - Yes) > ");
				scanf("%c", &sure);
				rewind(stdin);
				if (toupper(sure) == 'Y') {
					printf("\n Modification complete!\n");
					s[i] = view;
					editCount++;
				}
				else {
					printf("\n Modification forfeited!\n");
					exist++;
				}
			}
		}
	
	if (editCount == 0 && exist == 0) {
		printf(" Staff ID not found!\n");
	}
	printf("\n Continue modifying? (N - No) > ");
	scanf("%c", &con);
	rewind(stdin);
	}
	printf("\n Total modifications made : %d \n", editCount);
	FILE* recordptr = fopen("staff.bin", "wb");
	for (int i = 0; i < sCount; i++) {
		fwrite(&s[i], sizeof(StaffDetails), 1, recordptr);
	}
	fclose(recordptr);
	manageStaff();
}

void searchStaff() {
	StaffDetails search, s[100];
	char stop = 'Y', con;
	int sCount = 0, exist = 0;
	FILE* searchptr;
	searchptr = fopen("staff.bin", "rb");
	if (searchptr == NULL) {
		printf("Error Open File\n");
		exit(-1);
	}
	while (fread(&s[sCount], sizeof(StaffDetails), 1, searchptr) != 0) {
		sCount++;
	}
	fclose(searchptr);
	printf("\n --------------");
	printf("\n  SEARCH STAFF\n");
	printf(" --------------\n");
	while (toupper(stop) == 'Y') {
		printf("\n Enter the Staff ID of the staff you would like to view : ");
		scanf("%s", &search.staffID);
		rewind(stdin);
		for (int i = 0; i < sCount; i++) {
			if (strcmp(search.staffID, s[i].staffID) == 0) {
				printf("\n Staff ID \t Staff Name \t\t Staff Position \t Staff Contact No. \t Staff Password \t Security Answer\n");
				printf(" ======== \t ========== \t\t ============== \t ================= \t ==============\t\t ===============\n");
				printf(" %-7s \t %-20s \t %-15s \t %-15s \t %-20s \t %-20s \n", s[i].staffID, s[i].name, s[i].position, s[i].telno, s[i].acc.password, s[i].acc.pwRecovery);
				exist++;
			}
		}	
		if (exist == 0) {
			printf(" Staff ID not found!\n");
		}
		printf("\n Continue to view staff? (N - No) > ");
		scanf("%s", &stop);
		rewind(stdin);
		if (toupper(stop) == 'N') {
			manageStaff();
		}
	}
	fclose(searchptr);
}
void viewStaff() {
	FILE* viewptr;
	viewptr = fopen("staff.bin", "rb");
	int record = 0;
	StaffDetails view;
	printf("\n ------------");
	printf("\n  VIEW STAFF\n");
	printf(" ------------\n");
	printf("\n Staff ID \t Staff Name \t\t Staff Position \t Staff Contact No. \t Staff Password \t Security Answer\n");
	printf(" ======== \t ========== \t\t ============== \t ================= \t ============== \t ===============\n");
	while (fread(&view, sizeof(StaffDetails), 1, viewptr) != 0) {
		printf(" %-7s \t %-20s \t %-15s \t %-15s \t %-20s \t %-20s \n", view.staffID, view.name, view.position, view.telno, view.acc.password, view.acc.pwRecovery);
		record++;
	}
	fclose(viewptr);
	printf("\n Total Staff Records Displayed : %d\n", record);
	manageStaff();
}

void deleteStaff() {
	StaffDetails staff[100], temp;
	int exist = 0, count = 0, sCount = 0;
	char con = 'Y', sure;
	FILE* vptr, * dltptr = fopen("temp.bin", "wb");
	if (dltptr == NULL) {
		printf("ERROR");
		exit(-1);
	}
	vptr = fopen("staff.bin", "rb");
	printf("\n --------------");
	printf("\n  DELETE STAFF\n");
	printf(" --------------\n");
	while (fread(&staff[sCount], sizeof(StaffDetails), 1, vptr) != 0) {
		sCount++;
	}
	fclose(vptr);
	printf("\n Staff ID \t Staff Name \t\t Staff Position \t Staff Contact No. \t Staff Password \t Security Answer\n");
	printf(" ======== \t ========== \t\t ============== \t ================= \t ============== \t ===============\n");
	for (int i = 0; i < sCount; i++) {
		printf(" %-7s \t %-20s \t %-15s \t %-15s \t %-20s \t %-20s \n", staff[i].staffID, staff[i].name, staff[i].position, staff[i].telno, staff[i].acc.password, staff[i].acc.pwRecovery);
		count++;	
	}
	printf("\n Total records displayed : %d\n\n", count);
	while (toupper(con) == 'Y') {
		printf(" Enter Staff ID to delete : ");
		scanf("%s", temp.staffID);
		rewind(stdin);
		for (int i = 0; i < sCount; i++) {
			if (strcmp(staff[i].staffID, temp.staffID) != 0) {
				fwrite(&staff[i], sizeof(StaffDetails), 1, dltptr);
			}
			else if (strcmp(staff[i].staffID, temp.staffID) == 0) {
				printf(" Confirm deletion of Staff ID %s? (Y - Yes) > ", temp.staffID);
				scanf("%c", &sure);
				rewind(stdin);
				exist++;
				if (toupper(sure) == 'Y') {
					printf(" Staff %s has been successfully deleted!\n", temp.staffID);
				}
				else {
					printf(" Deletion attempt unsuccessful!\n");
					return;
				}
			}
		}
		fclose(dltptr);
		remove("staff.bin");
		rename("temp.bin", "staff.bin");
		if(exist == 0) {
			printf(" Staff ID not found!\n");
		}
		printf("\n Continue deleting? (N - No) > ");
		scanf("%c", &con);
		rewind(stdin);
		printf("\n");
		if (toupper(con) == 'N') {
			manageStaff();
		}
	}
}