#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>


#define MAX_STAFF_COUNT 1000
#define MAX_USERNAME_LEN 50
#define MAX_SID_LEN 50
#define MAX_PASSWORD_LEN 50
#define DEFAULT_BALANCE 100
#define INV_BALANCE staff[staff_select].invbalance


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
extern int STAFF_COUNT;

extern int staff_select;
extern int current_day;
extern int current_month;
extern int current_year;


//Global struct declaration
struct staff_details {
	char username[MAX_USERNAME_LEN], staff_id[MAX_SID_LEN], password[MAX_PASSWORD_LEN];
	int perm_level, balance, invbalance, dept;
	int type[DEFAULT_BALANCE], year[DEFAULT_BALANCE], month[DEFAULT_BALANCE], day[DEFAULT_BALANCE], status[DEFAULT_BALANCE];
};
extern struct staff_details staff[MAX_STAFF_COUNT];


//Staff role
void staff_menu() {
	char selection;
	do {
		system("cls"); title();
		red_bold();  printf("\n\n\t\t\t-=- Staff Role -=-"); clear();
		user_info();
		yellow_bold();  printf("\n\n\t\t\tLeave Menu"); clear();
		white_bold(); printf("\n\t1.\tApply leave");
		printf("\n\t2.\tCancel leave");
		printf("\n\t3.\tLeave status and information");
		printf("\n\n\tb.\tBack");
		printf("\n\te.\tExit"); clear();
		printf("\n\n\tSelection: "); 
		scanf_s("%c", &selection); while (getchar() != '\n');
		switch (selection) {
		case '1':
			apply_leave();
			break;
		case '2':
			cancel_leave();
			break;
		case '3':
			leave_status();
			break;
		case 'b':
			main_menu();
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
	} while (selection != 8);
}


//Apply leave function
void apply_leave() {
	int leave_type;
	char selection;
	char* ptrselect;
	do {
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\tLeave Application"); clear();
		printf("\n\tPlease select a leave type: ");
		printf("\n\tCurrent leave balance: %d", staff[staff_select].balance);

		//Check leave balance
		if (staff[staff_select].balance <= 0) {
			red_bold(); printf("\n\n\tNo leave balance remaining."); clear();
			printf("\n\tPress enter to continue.");
			while (getchar() != '\n');
			_getch();
			break;
		}
		else {

			//Leave type selection
			white_bold();  printf("\n\t1.\tAnnual leave");
			printf("\n\t2.\tCompassionate leave");
			printf("\n\t3.\tEmergency leave");
			printf("\n\t4.\tMaternity leave");
			printf("\n\t5.\tMedical leave");
			printf("\n\n\tb.\tBack");
			printf("\n\te.\tExit"); clear();
			printf("\n\n\tSelection: ");
			scanf_s("%c", &selection); while (getchar() != '\n');
			switch (selection) {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5': {

				//Leave date input
				int year, month, day, flag = 0;
				while (flag == 0) {
					system("cls"); title();
					yellow_bold();  printf("\n\n\t\t\tLeave Date"); clear();
					printf("\n\tPlease enter the date of your leave.");
					printf("\n\n\tYear: ");
					scanf_s("%d", &year); while (getchar() != '\n');
					printf("\n\tMonth: ");
					scanf_s("%d", &month); while (getchar() != '\n');
					printf("\n\tDay: ");
					scanf_s("%d", &day); while (getchar() != '\n');
					if (dayValid(year, month, day)) {

						//Assign selection character to an integer variable
						ptrselect = &selection;
						sscanf_s(ptrselect, "%d", &staff[staff_select].type[INV_BALANCE]);

						staff[staff_select].year[INV_BALANCE] = year;
						staff[staff_select].month[INV_BALANCE] = month;
						staff[staff_select].day[INV_BALANCE] = day;
						staff[staff_select].status[INV_BALANCE] = 1;

						//Leave info confirmation
						system("cls"); title();
						green_bold();  printf("\n\n\tApplication successful!"); white_bold();
						switch (staff[staff_select].type[INV_BALANCE]) {
						case 1:
							printf("\n\n\tLeave type:\tAnnual leave");
							break;
						case 2:
							printf("\n\n\tLeave type:\tCompassionate leave");
							break;
						case 3:
							printf("\n\n\tLeave type:\tEmergency leave");
							break;
						case 4:
							printf("\n\n\tLeave type:\tMaternity leave");
							break;
						case 5:
							printf("\n\n\tLeave type:\tMedical leave");
							break;
						}
						printf("\n\tLeave date:\t%d-%d-%d", staff[staff_select].day[INV_BALANCE], staff[staff_select].month[INV_BALANCE], staff[staff_select].year[INV_BALANCE]);
						printf("\n\tLeave status:"); yellow(); printf("\tPending approval"); clear();
						staff[staff_select].balance--; staff[staff_select].invbalance++;
						white_bold(); printf("\n\tBalance:\t%d days", staff[staff_select].balance); clear();
						printf("\n\n\tPress enter to continue.");
						flag = 1;
						_getch();
						break;
					}
					else {
						red_bold(); printf("\n\tInvalid date, please try again."); clear();
						_getch();
					}
				}
				break;
			}
			case 'b':
				return;
			case 'e':
				green_bold();  printf("\n\tExiting..."); clear();
				write_info_file();
				write_leave_file();
				_getch();
				exit(0);
			default:
				red_bold(); printf("\n\tInvalid selection, please try again."); clear();
				while (getchar() != '\n');
				_getch();
				break;
			}
		}
	} while (selection != 'e');
}


//Day validity checker
bool dayValid(int year, int month, int day) {
	int month_len[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year == current_year) {
		if (month > current_month && month <= 12) {
			if (day <= month_len[month]) {
				return true;
			}
		}
		else {
			if (month == current_month) {
				if (day <= month_len[month] && day > current_day) {
					return true;
				}
			}
		}
	}
	if (year > current_year) {
		if (month <= 12) {
			if (day <= month_len[month]) {
				return true;
			}
		}
	}
	return false;
}


//Cancel leave
void cancel_leave() {
	char selection;
	int int_select, select_move, check = 0;
	do {
		int flag = 1;
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\tLeave Status"); clear();
		printf("\n\n\tThe following is your list of leave applications and\n\ttheir statuses:");
		leave_list();
		white_bold();  printf("\n\n\tb.\tBack");
		printf("\n\te.\tExit"); clear();
		printf("\n\n\tSelect the leave you wish to delete.");
		printf("\n\n\tSelection: ");
		scanf_s("%c", &selection); while (getchar() != '\n');

		//Assign character selection to integer variables
		sscanf_s(&selection, "%d", &select_move);
		sscanf_s(&selection, "%d", &int_select);
		int_select--;

		//Date Validity checker
		if (select_move > 0 && select_move <= INV_BALANCE) {
			if (staff[staff_select].year[int_select] < current_year) {
				red_bold(); printf("\n\tDate has already passed."); clear();
				_getch();
				flag = 0;
			}
			else {
				if (staff[staff_select].month[int_select] < current_month && staff[staff_select].year[int_select] == current_year) {
					red_bold(); printf("\n\tDate has already passed."); clear();
					_getch();
					flag = 0;
				}
				else {
					if (staff[staff_select].day[int_select] <= current_day && staff[staff_select].month[int_select] == current_month && staff[staff_select].year[int_select] == current_year) {
						red_bold(); printf("\n\tDate has already passed."); clear();
						_getch();
						flag = 0;
					}
				}
			}

			//Removing leave
			if (flag == 1) {
				if (staff[staff_select].status[int_select] == 3) {
					check = 1;
				}
				staff[staff_select].type[int_select] = 0;
				staff[staff_select].year[int_select] = 0;
				staff[staff_select].month[int_select] = 0;
				staff[staff_select].day[int_select] = 0;
				staff[staff_select].status[int_select] = 0;
				for (int_select; int_select <= INV_BALANCE; int_select++, select_move++) {
					staff[staff_select].type[int_select] = staff[staff_select].type[select_move];
					staff[staff_select].year[int_select] = staff[staff_select].year[select_move];
					staff[staff_select].month[int_select] = staff[staff_select].month[select_move];
					staff[staff_select].day[int_select] = staff[staff_select].day[select_move];
					staff[staff_select].status[int_select] = staff[staff_select].status[select_move];
				}
				INV_BALANCE--;
				if (check == 0) {
					staff[staff_select].balance++;
				}
			}
		}

		else {
			if (selection =='b') {
				return;
			}
			else {
				if (selection == 'e') {
					green_bold();  printf("\n\tExiting..."); clear();
					write_info_file();
					write_leave_file();
					_getch();
					exit(0);
				}
				else {
					red_bold(); printf("\n\tInvalid selection, please try again."); clear();
					_getch();
				}
			}
		}
	} while (selection != 'e');
}


//Leave status
void leave_status() {
	system("cls"); title();
	yellow_bold();  printf("\n\n\t\tLeave Status and Information"); clear();
	printf("\n\n\tThe following is your list of leave applications and\n\ttheir statuses:");
	leave_list();
	white_bold(); printf("\n\tRemaining leave balance:\t%d days", staff[staff_select].balance); clear();
	printf("\n\n\tPress enter to return to previous menu.");
	_getch();
}


void leave_list() {
	int i;
	white_bold();  printf("\n\n\tNo.\tLeave Type\tLeave Date\tStatus"); clear();
	for (i = 0; i < INV_BALANCE; i++) {
		printf("\n\t%d", i + 1);
		switch (staff[staff_select].type[i]) {
		case 1:
			printf("\tAnnual leave");
			break;
		case 2:
			printf("\tCompassionate");
			break;
		case 3:
			printf("\tEmergency leave");
			break;
		case 4:
			printf("\tMaternity leave");
			break;
		case 5:
			printf("\tMedical leave");
			break;
		}
		printf("\t%d-%d-%d", staff[staff_select].day[i], staff[staff_select].month[i], staff[staff_select].year[i]);
		switch (staff[staff_select].status[i]) {
		case 1:
			yellow_bold();  printf("\tPending"); clear();
			break;
		case 2:
			green_bold();  printf("\tApproved"); clear();
			break;
		case 3:
			red_bold(); printf("\tRejected"); clear();
			break;
		}
	}
	printf("\n");
	return;
}
