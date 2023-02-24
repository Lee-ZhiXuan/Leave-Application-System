#include <stdio.h>
#include <conio.h>
#include <Windows.h>


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
void staff_information();
void generate_report();
void edit_balance();
void add_staff();

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


//Admin role
void admin_menu() {
	char selection;
	do {
		system("cls"); title();
		red_bold();  printf("\n\n\t\t\t-=- Admin Role -=-"); clear();
		user_info();
		yellow_bold();  printf("\n\n\t\t\tLeave Menu"); clear();
		white_bold(); printf("\n\t1.\tApply leave");
		printf("\n\t2.\tCancel leave");
		printf("\n\t3.\tLeave status and information"); clear();
		yellow_bold();  printf("\n\n\t\t\tAdmin Menu"); clear();
		white_bold(); printf("\n\t4.\tAdd staff");
		printf("\n\t5.\tEdit leave balance");
		printf("\n\t6.\tStaff information");
		printf("\n\t7.\tGenerate monthly report");
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
		case '4':
			add_staff();
			break;
		case '5':
			edit_balance();
			break;
		case '6':
			staff_information();
			break;
		case '7':
			generate_report();
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
	} while (selection != 'e');
}


//Staff information lookup
void staff_information() {
	char info_lookup[MAX_SID_LEN];
	int i, lookup_select, flag = 0;
	system("cls"); title();
	yellow_bold();  printf("\n\n\t\t\tStaff information"); clear();
	printf("\n\n\tPlease enter a staff ID.");
	printf("\n\n\tStaff ID: ");
	scanf_s("%s", info_lookup, MAX_SID_LEN); while (getchar() != '\n');
	for (i = 0; i < STAFF_COUNT; i++) {
		if ((strcmp(staff[i].staff_id, info_lookup)) == 0) {
			lookup_select = i;
			flag = 1;

			//Staff info display
			yellow_bold();  printf("\n\n\t\t\tStaff Info"); clear();
			white_bold(); printf("\n\tUsername:\t%s", staff[lookup_select].username);
			printf("\n\tStaff ID:\t%s", staff[lookup_select].staff_id);
			switch (staff[lookup_select].perm_level) {
			case 1:
				printf("\n\tStaff rank:\tStaff");
				break;
			case 2:
				printf("\n\tStaff rank:\tSupervisor");
				break;
			case 3:
				printf("\n\tStaff rank:\tAdministrator");
				break;
			}
			switch (staff[lookup_select].dept) {
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
			printf("\n\tLeave balance:\t%d", staff[lookup_select].balance); clear();

			//Staff leave list display
			white_bold();  printf("\n\n\tNo.\tLeave Type\tLeave Date\tStatus"); clear();
			for (i = 0; i < staff[lookup_select].invbalance; i++) {
				printf("\n\t%d", i + 1);
				switch (staff[lookup_select].type[i]) {
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
				printf("\t%d-%d-%d", staff[lookup_select].day[i], staff[lookup_select].month[i], staff[lookup_select].year[i]);
				switch (staff[lookup_select].status[i]) {
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
			printf("\n\n\tPress enter to return to previous menu.");
			break;
		}
	}
	if (flag == 0) {
		red_bold(); printf("\n\tInvalid selection, please try again."); clear();
	}
	_getch();
}


//Generate monthly report
void generate_report() {
	char selection, dept_char[10];
	int year, month, dept_int;
	int i, j, count = 0;
	do {
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\tGenerate Report"); clear();
		printf("\n\n\tThis function will generate a monthly report txt file based on the\n\tyear and month you have entered, do you wish to continue?");
		white_bold(); printf("\n\ty.\tYes");
		printf("\n\n\tb.\tBack");
		printf("\n\te.\tExit"); clear();
		printf("\n\n\tSelection: ");
		scanf_s("%c", &selection); while (getchar() != '\n');
		switch (selection) {
		case 'y':
			printf("\n\n\tYear: ");
			scanf_s("%d", &year); while (getchar() != '\n');
			printf("\n\tMonth: ");
			scanf_s("%d", &month); while (getchar() != '\n');
			printf("\n\n\tPlease choose a department.");
			white_bold(); printf("\n\n\t1. Administrative");
			printf("\n\n\t2. Management");
			printf("\n\n\t3. Academic");
			printf("\n\n\t4. Technical"); clear();
			printf("\n\n\tSelection: ");
			scanf_s("%d", &dept_int); while (getchar() != '\n');
			switch (dept_int) {
			case 1:
				strcpy_s(dept_char, "admin");
				break;
			case 2:
				strcpy_s(dept_char, "manage");
				break;
			case 3:
				strcpy_s(dept_char, "acad");
				break;
			case 4:
				strcpy_s(dept_char, "tech");
				break;
			}

			//Generate text file
			char report_name[50];
			sprintf_s(report_name, "%d-%d_%s_monthly_report.txt", month, year, dept_char);
			FILE* report;
			fopen_s(&report, report_name, "w");
			if (report == NULL) {
				red_bold();  printf("\n\tFailed to generate file!"); clear();
				_getch();
			}

			//Insert report contents
			fprintf(report, "%d-%d monthly staff leave report.", month, year);
			fprintf(report, "\n\nNo.\tUsername\t\tStaff ID\t\tRank\t\tType\t\tDate\t\tStatus");
			for (i = 0; i < STAFF_COUNT; i++) {
				if (staff[i].dept == dept_int) {
					for (j = 0; j < staff[i].invbalance; j++) {
						if (staff[i].month[j] == month && staff[i].year[j] == year) {
							count++;
							fprintf(report, "\n%d\t%s\t\t%s", count, staff[i].username, staff[i].staff_id);
							switch (staff[i].perm_level) {
							case 1:
								fprintf(report, "\t\tStaff");
								break;
							case 2:
								fprintf(report, "\t\tSupervisor");
								break;
							case 3:
								fprintf(report, "\t\tAdministrator");
								break;
							}
							switch (staff[i].type[j]) {
							case 1:
								fprintf(report, "\t\tAnnual leave");
								break;
							case 2:
								fprintf(report, "\t\tCompassionate");
								break;
							case 3:
								fprintf(report, "\t\tEmergency leave");
								break;
							case 4:
								fprintf(report, "\t\tMaternity leave");
								break;
							case 5:
								fprintf(report, "\t\tMedical leave");
								break;
							}
							fprintf(report, "\t\t%d-%d-%d", staff[i].day[j], staff[i].month[j], staff[i].year[j]);
							switch (staff[i].status[j]) {
							case 1:
								fprintf(report, "\t\tPending");
								break;
							case 2:
								fprintf(report, "\t\tApproved");
								break;
							case 3:
								fprintf(report, "\t\tRejected");
								break;
							}
						}
					}
				}
			}
			green_bold(); printf("\n\n\tReport file successfully generated!"); clear();
			_getch();
			break;

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
			_getch();
			break;
		}
	} while (selection != 'e');
}


//Edit leave balance
void edit_balance() {
	char selection, edit_day, confirmation[5];
	int i, new_leave;
	do {
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\tEdit Balance"); clear();
		white_bold(); printf("\n\t1.\tEdit current leave balance");
		printf("\n\t2.\tStep 1 year");
		printf("\n\n\tb.\tBack");
		printf("\n\te.\tExit"); clear();
		printf("\n\n\tSelection: ");
		scanf_s("%c", &selection); while (getchar() != '\n');
		switch (selection) {
		case '1':
			system("cls"); title();
			yellow_bold();  printf("\n\n\t\tEdit current leave balance"); clear();
			printf("\n\n\tThis function adds or removes leave days from all\n\tstaff members.");
			white_bold(); printf("\n\n\t1.\tAdd 1 day");
			printf("\n\t2.\tRemove 1 day");
			printf("\n\n\tb.\tBack"); clear();
			printf("\n\n\tSelection: ");
			scanf_s("%c", &edit_day); while (getchar() != '\n');
			switch (edit_day) {
			case '1':
				for (i = 0; i < STAFF_COUNT; i++) {
					staff[i].balance++;
				}
				green_bold(); printf("\n\tAdded 1 day."); clear();
				_getch();
				return;
			case '2':
				for (i = 0; i < STAFF_COUNT; i++) {
					staff[i].balance--;
				}
				red_bold(); printf("\n\tRemoved 1 day."); clear();
				_getch();
				return;
			case 'b':
				return;
			default:
				red_bold(); printf("\n\tInvalid selection, please try again."); clear();
				_getch();
				return;
			}
		case '2':
			system("cls"); title();
			yellow_bold();  printf("\n\n\t\t\tStep 1 year"); clear();
			red_bold();  printf("\n\n\t\t\t[!] Warning [!]"); clear();
			white_bold();  printf("\n\n\tThis function will reset all leave balances and is to be\n\tused when a new year arrives. The following actions cannot\n\tbe reversed! Do you wish to continue?"); clear();
			printf("\n\n\tType out 'YES' to confirm.");
			printf("\n\n\tConfirmation: ");
			scanf_s("%s", &confirmation, 5); while (getchar() != '\n');
			if (strcmp(confirmation, "YES") == 0) {
				green_bold(); printf("\n\n\tConfirmation successful."); clear();
				printf("\n\n\tPlease enter the number of leave days for the new year.");
				printf("\n\n\tNumber of leave days: ");
				scanf_s("%d", &new_leave); while (getchar() != '\n');
				for (i = 0; i < STAFF_COUNT; i++) {
					staff[i].balance = new_leave;
				}
				green_bold();  printf("\n\n\tLeave balances updated."); clear();
				printf("\n\n\tPress enter to return to previous page.");
				_getch();
				break;
			}
			else {
				red_bold();  printf("\n\n\tAction cancelled. Press enter to return to previous page."); clear();
				_getch();
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
			_getch();
			break;
		}
	} while (selection != 'e');
}


//Add staff information
void add_staff() {
	char selection, confirmation[5], dept_selection, rank_selection;
	do {
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\t   Add Staff"); clear();
		red_bold();  printf("\n\n\t\t\t[!] Warning [!]"); clear();
		white_bold();  printf("\n\n\tThis action cannot be reversed, do you wish to proceed?");
		printf("\n\n\tb.\tBack");
		printf("\n\te.\tExit"); clear();
		printf("\n\n\tType out 'YES' to confirm.");
		printf("\n\n\tConfirmation: ");
		scanf_s("%s", &confirmation, 5); while (getchar() != '\n');
		if (strcmp(confirmation, "YES") == 0) {
			system("cls"); title();
			yellow_bold();  printf("\n\n\t\t\tAdd Staff"); clear();
			green_bold(); printf("\n\n\tConfirmation successful."); clear();

			//Add Staff information
			printf("\n\n\tPlease enter the new staff's information.");
			printf("\n\n\tUsername: ");
			scanf_s("%s", &staff[STAFF_COUNT].username, MAX_USERNAME_LEN); while (getchar() != '\n');
			printf("\n\n\tStaff ID: ");
			scanf_s("%s", &staff[STAFF_COUNT].staff_id, MAX_SID_LEN); while (getchar() != '\n');
			printf("\n\n\tPassword: ");
			scanf_s("%s", &staff[STAFF_COUNT].password, MAX_PASSWORD_LEN); while (getchar() != '\n');

			white_bold(); printf("\n\n\tDepartment");
			printf("\n\n\t1.\tAdministrative");
			printf("\n\t2.\tManagement");
			printf("\n\t3.\tAcademic");
			printf("\n\t4.\tTechnical");
			printf("\n\n\tSelection: ");
			scanf_s("%c", &dept_selection); while (getchar() != '\n');
			switch (dept_selection) {
			case '1':
				staff[STAFF_COUNT].dept = 1;
				break;
			case '2':
				staff[STAFF_COUNT].dept = 2;
				break;
			case '3':
				staff[STAFF_COUNT].dept = 3;
				break;
			case '4':
				staff[STAFF_COUNT].dept = 4;
				break;
			default:
				red_bold(); printf("\n\tInvalid selection, please try again."); clear();
				_getch();
				return;
			}

			white_bold(); printf("\n\n\tStaff Rank");
			printf("\n\n\t1.\tStaff");
			printf("\n\t2.\tSupervisor");
			printf("\n\t3.\tAdministrator");
			printf("\n\n\tSelection: ");
			scanf_s("%c", &rank_selection); while (getchar() != '\n');
			switch (rank_selection) {
			case '1':
				staff[STAFF_COUNT].perm_level = 1;
				break;
			case '2':
				staff[STAFF_COUNT].perm_level = 2;
				break;
			case '3':
				staff[STAFF_COUNT].perm_level = 3;
				break;
			default:
				red_bold(); printf("\n\tInvalid selection, please try again."); clear();
				_getch();
				return;
			}

			printf("\n\n\tLeave Balance: ");
			scanf_s("%d", &staff[STAFF_COUNT].balance); while (getchar() != '\n');
			staff[STAFF_COUNT].invbalance = 0;

			system("cls"); title();
			green_bold();  printf("\n\n\t\t\tStaff added."); clear();
			white_bold(); printf("\n\tUsername:\t%s", staff[STAFF_COUNT].username);
			printf("\n\tStaff ID:\t%s", staff[STAFF_COUNT].staff_id);
			switch (staff[STAFF_COUNT].perm_level) {
			case 1:
				printf("\n\tStaff rank:\tStaff");
				break;
			case 2:
				printf("\n\tStaff rank:\tSupervisor");
				break;
			case 3:
				printf("\n\tStaff rank:\tAdministrator");
				break;
			}
			switch (staff[STAFF_COUNT].dept) {
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
			STAFF_COUNT++;
			printf("\n\n\tPress enter to return to previous page.");
			_getch();
			break;
		}
		else {
			red_bold();  printf("\n\n\tAction cancelled. Press enter to return to previous page."); clear();
			_getch();
			break;
		}
	} while (selection != 'e');
}