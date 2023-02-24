//Leave Application and Management System
//LEE ZHI XUAN (TP065525)
//Main file

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STAFF_COUNT 1000
#define MAX_USERNAME_LEN 50
#define MAX_SID_LEN 50
#define MAX_PASSWORD_LEN 50
#define DEFAULT_BALANCE 100
#define INV_BALANCE staff[staff_select].invbalance


//Function Prototypes
void login();
void title();
void main_menu();
void staff_menu();
void supervisor_menu();
void admin_menu();
void apply_leave();
bool dayValid(int, int, int);
void cancel_leave();
void leave_status();
void leave_list();
int time();
void user_info();

void write_info_file();
void read_info_file();
void read_leave_file();
void write_leave_file();

void clear();
void white();
void white_bold();
void red();
void red_bold();
void yellow();
void yellow_bold();
void green();
void green_bold();


//Global variable declaration
int STAFF_COUNT;

int staff_select;
int current_day;
int current_month;
int current_year;


//Main executor
int main() {
	read_info_file();
	read_leave_file();
	time();
	main_menu();
	return 0;
}


//Title screen function
void title() {
	white_bold();  printf("\n==================================================================");
	printf("\n\t APU - LEAVE APPLICATION AND MANAGEMENT SYSTEM");
	printf("\n=================================================================="); clear();
}


//Staff info strut
struct staff_details {
	char username[MAX_USERNAME_LEN], staff_id[MAX_SID_LEN], password[MAX_PASSWORD_LEN];
	int perm_level, balance, invbalance, dept;
	int type[DEFAULT_BALANCE], year[DEFAULT_BALANCE], month[DEFAULT_BALANCE], day[DEFAULT_BALANCE], status[DEFAULT_BALANCE];
};
struct staff_details staff[MAX_STAFF_COUNT];


//Login validity checker
bool loginValid(struct staff_details staff[MAX_STAFF_COUNT], char staff_id[], char password[]) {
	for (int i = 0; i < STAFF_COUNT; i++) {
		if (strcmp(staff[i].staff_id, staff_id) == 0 && strcmp(staff[i].password, password) == 0) {
			return true;
		}
	}
	return false;
}


//Main menu
void main_menu() {
	char selection;
	do {
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\tMain Menu"); clear();
		white_bold(); printf("\n\n\t1.\tLogin");
		printf("\n\te.\tExit");
		printf("\n\n\tSelection: "); clear();
		scanf_s("%c", &selection); while (getchar() != '\n');
		switch (selection) {
		case '1':
			login();
			break;
		case 'e':
			green_bold();  printf("\n\tExiting..."); clear();
			write_info_file();
			write_leave_file();
			_getch();
			exit(0);
		default:
			red_bold(); printf("\n\tInvalid selection, please try again."); clear();
			_getch();
			break;
		}
	} while (selection != 'e');
}


//Login menu
void login() {
	int login_attempts = 3, flag = 0, i;
	system("cls"); title(); 
	yellow_bold();  printf("\n\n\t\t\tLogin"); clear();
	do {
		char staff_id[MAX_SID_LEN], password[MAX_PASSWORD_LEN];

		//Input staff id
		printf("\n\n\tStaff ID: ");
		scanf_s("%s", staff_id, MAX_SID_LEN); while (getchar() != '\n');
		for (i = 0; i < STAFF_COUNT; i++) {
			if ((strcmp(staff[i].staff_id, staff_id)) == 0) {
				staff_select = i;
				break;
			}
		}

		//Input password
		printf("\n\tPassword: ");
		scanf_s("%s", password, MAX_PASSWORD_LEN); while (getchar() != '\n');

		//Validity checker
		if (loginValid(staff, staff_id, password)) {
			flag = 1;
			green();  printf("\n\n\tLogin successful."); clear();

			//Staff position separator
			switch (staff[staff_select].perm_level) {
			case 1:
				staff_menu();
				break;
			case 2:
				supervisor_menu();
				break;
			case 3:
				admin_menu();
				break;
			}
			break;
		}
		if (login_attempts > 1) {
			system("cls"); title(); 
			yellow_bold();  printf("\n\n\t\t\tLogin"); clear();
			red_bold(); printf("\n\n\tIncorrect staff ID or password, please try again.");
			printf("\n\tAttempts remaining : %d", login_attempts, --login_attempts); clear();
		}
		else {
			red_bold(); printf("\n\n\tIncorrect staff ID or password, no attempts left.\n\tExiting program..."); clear();
			_getch();
			exit(0);
		}
	} while (flag == 0);
	_getch();
}


//Import current system time
int time() {
	time_t t = time(NULL);
	struct tm tm;
	errno_t err = localtime_s(&tm, &t);
	if (err != 0) {
		red_bold();  printf("\n\tFailed to get local time!"); clear();
		_getch();
		return 1;
	}

	//Retrieve day, month, and year
	current_day = tm.tm_mday;
	current_month = tm.tm_mon + 1; //Month is 0-indexed, so add 1
	current_year = tm.tm_year + 1900; //Year starts from 1900, thus add 1900
	return 0;
}


//Print user info
void user_info() {
	yellow_bold();  printf("\n\n\t\t\tUser Info"); clear();
	white_bold(); printf("\n\tUsername:\t%s", staff[staff_select].username);
	printf("\n\tStaff ID:\t%s", staff[staff_select].staff_id);
	switch (staff[staff_select].perm_level) {
	case 1:
		printf("\n\tUser rank:\tStaff");
		break;
	case 2:
		printf("\n\tUser rank:\tSupervisor");
		break;
	case 3:
		printf("\n\tUser rank:\tAdministrator");
		break;
	}
	switch (staff[staff_select].dept) {
	case 1:
		printf("\n\tDepartment:\tAdministrative");
		break;
	case 2:
		printf("\n\tDepartment\tManagement");
		break;
	case 3:
		printf("\n\tDepartment\tAcademic");
		break;
	case 4:
		printf("\n\tDepartment\tTechnical");
		break;
	}
	printf("\n\tLeave balance:\t%d", staff[staff_select].balance); clear();
}


//Read staff info from text file
void read_info_file() {
	int i;
	FILE* staffinfo;
	fopen_s(&staffinfo, "staff_info.txt", "r");
	if (staffinfo == NULL) {
		red_bold();  printf("\n\tFailed to read from file!"); clear();
		_getch();
	}
	for (i = 0; !feof(staffinfo); i++) {
		fscanf_s(staffinfo, "%s %s %s %d %d %d %d", staff[i].username, sizeof(staff[i].username), staff[i].staff_id, sizeof(staff[i].staff_id),
			staff[i].password, sizeof(staff[i].password), &staff[i].perm_level, &staff[i].balance, &staff[i].invbalance, &staff[i].dept);
	}
	STAFF_COUNT = i - 1;
	fclose(staffinfo);
}


//Write staff info into text file
void write_info_file() {
	FILE* staffinfo;
	fopen_s(&staffinfo, "staff_info.txt", "w");
	if (staffinfo == NULL) {
		printf("Failed to open file for writing.\n");
		return;
	}
	for (int i = 0; i < STAFF_COUNT; i++) {
		fprintf(staffinfo, "%s %s %s %d %d %d %d\n",
			staff[i].username, staff[i].staff_id, staff[i].password,
			staff[i].perm_level, staff[i].balance, staff[i].invbalance, staff[i].dept);
	}
	fclose(staffinfo);
}


//Read leave info from text file
void read_leave_file() {
	int i, j;
	FILE* leaveinfo;
	fopen_s(&leaveinfo, "leave_info.txt", "r");
	if (leaveinfo == NULL) {
		red_bold();  printf("\n\tFailed to read from file!"); clear();
		_getch();
	}
	for (i = 0; i < STAFF_COUNT; i++) {
		for (j = 0; j < staff[i].invbalance; j++) {
			fscanf_s(leaveinfo, "%d %d-%d-%d %d", &staff[i].type[j], &staff[i].day[j], &staff[i].month[j], &staff[i].year[j], &staff[i].status[j]);
		}
	}
	fclose(leaveinfo);
}


//Write leave info into text file
void write_leave_file() {
	int i, j;
	FILE* leaveinfo;
	fopen_s(&leaveinfo, "leave_info.txt", "w");
	if (leaveinfo == NULL) {
		red_bold();  printf("\n\tFailed to read from file!"); clear();
		_getch();
	}
	for (i = 0; i < STAFF_COUNT; i++) {
		for (j = 0; j < staff[i].invbalance; j++) {
			fprintf(leaveinfo, "%d %d-%d-%d %d\n", staff[i].type[j], staff[i].day[j], staff[i].month[j], staff[i].year[j], staff[i].status[j]);
		}
	}
	fclose(leaveinfo);
}