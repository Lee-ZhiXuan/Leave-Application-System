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
void application_management();
void application_processing(int);
void date_lookup();

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


//Supervisor role
void supervisor_menu() {
	char selection;
	do {
		system("cls"); title();
		red_bold();  printf("\n\n\t\t\t-=- Supervisor Role -=-"); clear();
		user_info();
		yellow_bold();  printf("\n\n\t\t\tLeave Menu"); clear();
		white_bold(); printf("\n\t1.\tApply leave");
		printf("\n\t2.\tCancel leave");
		printf("\n\t3.\tLeave status and information"); clear();
		yellow_bold();  printf("\n\n\t\t\tSupervisor Menu"); clear();
		white_bold(); printf("\n\t4.\tApplication management");
		printf("\n\t5.\tDate lookup");
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
			application_management();
			break;
		case '5':
			date_lookup();
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


//Application management
void application_management() {
	char selection;
	char* ptrselect;
	int i, j, int_select;
	do {
		int count = 1;
		system("cls"); title();
		yellow_bold();  printf("\n\n\t\t\tApplication Management"); clear();
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
		printf("\n\n\tThe following is the list of pending leave applications\n\tfor your department:");
		white_bold();  printf("\n\n\tNo.\tUsername\tStaff ID\tLeave Date"); clear();
		for (i = 0; i < STAFF_COUNT; i++) {
			if (staff[i].dept == staff[staff_select].dept) {
				for (j = 0; j < staff[i].invbalance; j++) {
					if (staff[i].status[j] == 1) {
						printf("\n\t%d.", count);
						count++;
						printf("\t%s\t\t%s", staff[i].username, staff[i].staff_id);
						printf("\t\t%d-%d-%d", staff[i].day[j], staff[i].month[j], staff[i].year[j]);
					}
				}
			}
		}
		white_bold();  printf("\n\n\tb.\tBack");
		printf("\n\te.\tExit"); clear();
		printf("\n\n\tSelect the application you wish to process.");
		printf("\n\n\tSelection: ");
		scanf_s("%c", &selection); while (getchar() != '\n');

		//Assign character selection to integer variables
		ptrselect = &selection;
		sscanf_s(ptrselect, "%d", &int_select);
		int_select--;

		//Selection sorting
		if (int_select >= 0 && int_select < count - 1) {
			application_processing(int_select);
			int_select = -1;
		}

		else {
			if (selection == 'b') {
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


//Application processing menu
void application_processing(int int_select) {
	int i, j, count = 0, flag = 0;
	int i_select = -1, j_select = -1;
	char selection;
	system("cls"); title();
	for (i = 0; i < STAFF_COUNT; i++) {
		if (staff[i].dept == staff[staff_select].dept) {
			for (j = 0; j < staff[i].invbalance; j++) {
				if (staff[i].status[j] == 1) {
					if (count == int_select && flag == 0) {
						white_bold();  printf("\n\n\tUsername\tStaff ID\tLeave Date\tType"); clear();
						printf("\n\t%s\t\t%s", staff[i].username, staff[i].staff_id);
						printf("\t\t%d-%d-%d", staff[i].day[j], staff[i].month[j], staff[i].year[j]);
						switch (staff[i].type[j]) {
						case 1:
							printf("\tAnnual");
							break;
						case 2:
							printf("\tCompassionate");
							break;
						case 3:
							printf("\tEmergency");
							break;
						case 4:
							printf("\tMaternity");
							break;
						case 5:
							printf("\tMedical");
							break;
						}
						i_select = i;
						j_select = j;
						flag = 1;
					}
					count++;
				}
			}
		}
	}
	printf("\n\n\tChoose whether you wish to approve or reject the application.");
	white_bold();  printf("\n\n\t1."); clear();
	green_bold(); printf("\tApprove"); clear();
	white_bold();  printf("\n\t2."); clear();
	red_bold(); printf("\tReject"); clear();
	white_bold(); printf("\n\n\tb.\tBack"); clear();
	printf("\n\n\tSelection: ");
	scanf_s("%c", &selection); while (getchar() != '\n');
	switch (selection) {
	case '1':
		staff[i_select].status[j_select] = 2;
		break;
	case '2':
		staff[i_select].status[j_select] = 3;
		staff[i_select].balance++;
		break;
	case 'b':
		return;
	default:
		red_bold(); printf("\n\tInvalid selection."); clear();
		_getch();
		break;
	}
}


//Date lookup
void date_lookup() {
	int year, month, day, i, j, count = 1;
	system("cls"); title();
	yellow_bold();  printf("\n\n\t\t\tDate Lookup"); clear();
	printf("\n\n\tPlease enter a date you wish to view.");
	printf("\n\n\tYear: ");
	scanf_s("%d", &year); while (getchar() != '\n');
	printf("\n\tMonth: ");
	scanf_s("%d", &month); while (getchar() != '\n');
	printf("\n\tDay: ");
	scanf_s("%d", &day); while (getchar() != '\n');
	system("cls"); title();
	yellow_bold();  printf("\n\n\t\t\tLeave List"); clear();
	printf("\n\n\tThe following is the list of staff members on leave on the\n\tselected date for your department.");
	white_bold();  printf("\n\n\tNo.\tUsername\tStaff ID\tType\t\tStatus"); clear();
	for (i = 0; i < STAFF_COUNT; i++) {
		if (staff[i].dept == staff[staff_select].dept) {
			for (j = 0; j < staff[i].invbalance; j++) {
				if (staff[i].year[j] == year && staff[i].month[j] == month && staff[i].day[j] == day) {
					printf("\n\t%d.", count);
					count++;
					printf("\t%s\t\t%s", staff[i].username, staff[i].staff_id);
					switch (staff[i].type[j]) {
					case 1:
						printf("\t\tAnnual leave");
						break;
					case 2:
						printf("\t\tCompassionate");
						break;
					case 3:
						printf("\t\tEmergency leave");
						break;
					case 4:
						printf("\t\tMaternity leave");
						break;
					case 5:
						printf("\t\tMedical leave");
						break;
					}
					switch (staff[i].status[j]) {
					case 1:
						yellow_bold();  printf("\tPending"); clear();
						break;
					case 2:
						green_bold();  printf("\tApproved"); clear();
						break;
					case 3:
						red_bold();  printf("\tRejected"); clear();
						break;
					}
				}
			}
		}
	}
	printf("\n\n\tNumber of staff on leave: %d", --count);
	printf("\n\n\tPress enter to return to previous menu.");
	_getch();
}