#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define MAX 10

// Global array. The following array holds all of the student information.
char firstname[MAX][20];
char lastname[MAX][20];
int age[MAX];
char id [MAX][20];
float firstgrades[MAX][3];
float secondgrades[MAX][3];
float average[MAX][2] = {};
int totalstudents = 0;   
char gender[MAX][10] = {""};   
char status[MAX][10] = {};
char subjects[3][10] = {
    {"Math"},
    {"English"},
    {"Science"}
};

// Declaring the functions so that the computer can recognize their existence.
void separator();
void mainmenu();
void viewStudents();
void addStudent();
void searchStudent();
void computeGrades();

// The main flow of logic
int main() {
    while (1) {
        int choice;
        int validation;

        mainmenu();

        validation = 0;
        while (validation == 0) { // Will loop until the user entered a valid input.
            printf("\nEnter choice: ");
            if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) { // Checks if the user did not input a number, a number less than 1, or a number greater than 5
                while(getchar() != '\n'); // Clears the input buffer so that the scanf can be reused.
                mainmenu();
                printf("\n\nERROR : Invalid input. Enter a number from 1 to 5\n");
            }
            else {
                validation = 1; // After entering a valid input, initializes validation to exit the loop
            }
        }

        switch (choice) {
            case 1:
            addStudent();
            break;
            case 2:
            viewStudents();
            break;
            case 3:
            searchStudent();
            break;
            case 4:
            computeGrades();
            break;
            case 5:
            return 0;
            break;
        }
        printf("\n\n");
        system("pause");
    }
}

// A function to display the main menu.
void mainmenu() {
    system("cls");
    separator();
    printf("%-25s%-54s|\n", "|", "STUDENT RECORD MANAGEMENT SYSTEM");
    separator();
    printf("%-34s%-45s|\n", "|", "MAIN MENU");
    separator();
    printf("%-31s%-48s|\n", "|", "1. Add Students"); // 25 + 15 = 40
    printf("%-31s%-48s|\n", "|", "2. View Students");
    printf("%-31s%-48s|\n", "|", "3. Search Student");
    printf("%-31s%-48s|\n", "|", "4. Compute Average");
    printf("%-31s%-48s|\n", "|", "5. Exit");
    separator();
}

// A function that prints a separator line to visually divide sections of the menu or the interface.
void separator() {
    int i;
    printf("|");
    for (i = 0; i < 78; i++) {
        printf("*");
    }
    printf("|\n");
}

// A function to add a student and their information.
void addStudent() {
    system("cls");
    int i, j = 0;
    char checker;
    char checker2[10] = "";
    int validation;
    float firstsem;
    float secondsem;
    int validation2;

    if (totalstudents >= MAX) {
        printf("Student list is already full!\n");
        return;
    }

    printf("First name: ");
    scanf("%s", &firstname[totalstudents]);

    printf("Last name: ");
    scanf("%s", &lastname[totalstudents]);

    printf("Age: ");
    scanf("%d", &age[totalstudents]);   

    validation2 = 0;

    while (validation2 == 0) {
        printf("ID: ");
        scanf("%s", checker2);

        // Loop through all existing IDs to check if this one is taken
        for (i = 0; i < totalstudents; i++) {
            if (strcmp(checker2, id[i]) == 0) {
                validation2 = 1; // ID found, break out of the loop
                break; // Optional: exit the loop early once the ID is found
            }
        }

        // If ID is already taken, prompt the user again
        if (validation2 == 1) {
            printf("The ID %s is already taken.\n\n", checker2);
            validation2 = 0;
        }
        else {
            validation2 = 1;
            sprintf(id[totalstudents],"%s", checker2);
        }
    }

    validation = 0;

    while (validation == 0) {
        printf("Gender: (M = MALE | F = FEMALE)\n");
        checker = getch();
        if (checker == 'M' || checker == 'm') {
            sprintf(gender[totalstudents], "Male");
            validation = 1;
        }
        else if (checker == 'F' || checker == 'f') {
            sprintf(gender[totalstudents], "Female");
            validation = 1;
        }
        else {
            printf("Invalid input. Press the letter of your gender.\n");
        }
    }
    

    printf("First semester grades\n");
    for (i = 0; i < 3; i++) {
        printf("%s : ", subjects[i]);
        scanf("%f", &firstgrades[totalstudents][i]);
        firstsem += firstgrades[totalstudents][i];
    }


    printf("\n\nSecond semester grades\n");
    for (i = 0; i < 3; i++) {
        printf("%s : ", subjects[i]);
        scanf("%f", &secondgrades[totalstudents][i]);
        secondsem += secondgrades[totalstudents][i];
    }

    if ((average[totalstudents][1] = firstsem/3) > 74) {
        sprintf(status[totalstudents], "Passed");
    }
    else {
        sprintf(status[totalstudents], "Failed");
    }
    if ((average[totalstudents][2] = secondsem/3) >= 74) {
        sprintf(status[totalstudents], "Passed");
    }
    else {
        sprintf(status[totalstudents], "Failed");
    }
        
    // Increments the totalstudents to count how many students are there
    totalstudents++;
    printf("\n\nStudent added successfully!\n");
}

void viewStudents() {
    system("cls");

    if (totalstudents == 0) {
        printf("No data yet . . .\n\n");
        system("pause");
        return;
    }

    for (int i = 0; i < totalstudents; i++) {
        printf("Student No. %d . . .\n", i + 1);
        separator();
        printf("|First Name: %-20s ", firstname[i]);
        printf("|Last Name: %-20s ", lastname[i]);
        printf("|Age: %-5d |\n", age[i]);
        separator();
        printf("|ID: %-74s|\n", id[i]);
        separator();
        printf("\n\n");
    }
}

void searchStudent() {
    system("cls");
    char scanning[50] = "";
    int validation;
    int i, j;
    char choice;

    // Prompts the user to enter the unique id of a student.
    printf("ID of the student: ");
    scanf("%s", &scanning);

    for (i = 0; i < totalstudents; i++) {
        if (strcmp(scanning, id[i]) == 0) {
            validation = 1;
            break;
        }
    }

    if (validation == 0) {
        printf("There's no student with an id of %s.\n\n", scanning);
        return;
    }
    
    separator();
    printf("|First Name: %-20s ", firstname[i]);
    printf("|Last Name: %-20s ", lastname[i]);
    printf("|Age: %-5d |\n", age[i]);
    separator();
    printf("|%-10s%-30c%-38s|\n", " ", '|', "Grades");
    printf("| Subjects |*******************************************************************|\n");
    printf("|%-10s|%-33s|%-33s|\n", "", "First Semester", "Second Semester");
    printf("|**********|*********************************|*********************************|\n");
    for(j = 0; j < 3; j++) {
        printf("|%-10s|%13s%-20.2f|%13s%-20.2f|\n", subjects[j], "", firstgrades[i][j], "", secondgrades[i][j]); // Change the data type after.
    }
    separator();
    printf("|ID: %-74s|\n", id[i]);
    separator();
}

void computeGrades() {
    int validation;
    char scanning[50] = "";
    int i, j, k = 0;
    char fullname[50];
    system("cls");
    printf("ID of the student: ");
    scanf("%s", &scanning);

    for (i = 0; i < totalstudents; i++) {
        if (strcmp(scanning, id[i]) == 0) {
            validation = 1;
            break;
        }
        
    }

    if (validation == 0) {
        printf("There's no student with an id of %s.\n\n", scanning);
        return;
    }

    sprintf(fullname, "%s, %s", lastname[i], firstname[i]);

    separator();
    printf("| Student: %-34s| Gender: %-10s| Age: %-7d|\n", fullname, gender[i], age[i]);
    separator();
    printf("|%-10s|%-33s|%-33s|\n", "Subjects", "First Semester", "Second Semester");
    printf("|**********|*********************************|*********************************|\n");
    for(j = 0; j < 3; j++) {
        printf("|%-10s|%13s%-20.2f|%13s%-20.2f|\n", subjects[j], "", firstgrades[i][j], "", secondgrades[i][j]);
    }
    printf("|Average   |%13s%-20.2f|%13s%-20.2f|\n", "", average[i][1], "", average[i][2]);
    printf("|Status:   |%13s%-20s|%13s%-20s|\n", "", status[i], "", status[i]);

    separator();
    printf("|ID: %-74s|\n", id[i]);
    separator();
}