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
void option1();
void option2();
void option3();
void option4();
void option5();
void color(int textColor, int bgColor);
void gotoxy(int x, int y);

// The main flow of logic
int main() {
    int ch1, ch2;
    int choice = 1; 

    mainmenu();
    option1();

    while(1) {
        ch1 = getch();

        if (ch1 == 0 || ch1 == 0xE0) {
            ch2 = getch();

            switch(ch2) {
                case 72: // UP
                    choice--;
                    if (choice < 1) choice = 5;
                    break;
                case 80: // DOWN
                    choice++;
                    if (choice > 5) choice = 1;
                    break;
            }
            mainmenu();
            switch(choice) {
                case 1: option1(); break;
                case 2: option2(); break;
                case 3: option3(); break;
                case 4: option4(); break;
                case 5: option5(); break;
            }
            
        }

        else {
            if(ch1 == 13) { // ENTER
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
                    exit(0);
                }

                getch();
                mainmenu();
                switch(choice) {
                    case 1: option1(); break;
                    case 2: option2(); break;
                    case 3: option3(); break;
                    case 4: option4(); break;
                    case 5: option5(); break;
                }  
            }
        }
    }
    return 0;
}

// A function to display the main menu.
void mainmenu() {
    system("cls");
    color(7, 0);
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
    color(7, 1);
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

    // Prompts the user to ch1 the unique id of a student.
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

// Manipulates the color of either the text or the background.
void color(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

// Manipulates the position of the cursor.
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void option1() {
    gotoxy(0, 5);
    color(7, 1);
    printf("%-31s%-48s|", "|", "1. Add Students");
    color(7, 0);
}

void option2() {
    gotoxy(0, 6);
    color(7, 1);
    printf("%-31s%-48s|", "|", "2. View Students");
    color(7, 0);
}

void option3() {
    gotoxy(0, 7);
    color(7, 1);
    printf("%-31s%-48s|", "|", "3. Search Student");
    color(7, 0);
}

void option4() {
    gotoxy(0, 8);
    color(7, 1);
    printf("%-31s%-48s|", "|", "4. Compute Average");
    color(7, 0);
}

void option5() {
    gotoxy(0, 9);
    color(7, 1);
    printf("%-31s%-48s|", "|", "5. Exit");
    color(7, 0);
}