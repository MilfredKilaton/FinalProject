#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define MAX 100

// Global arrays for student information
char firstname[MAX][20];
char lastname[MAX][20];
int age[MAX];
char id[MAX][20];
float firstgrades[MAX][3];
float secondgrades[MAX][3];
float average[MAX][2];
char gender[MAX][10];
char status[MAX][2][10];
int totalstudents = 0;
void sortStudents(char sortKey);

char subjects[3][10] = {"Math", "English", "Science"};

// Declaring necessary functions
void separator();
void mainmenu();
void viewStudents();
void addStudent();
void searchStudent();
void computeGrades();
void noData();

// Declaring all of the highlight functions
void option1();
void option2();
void option3();
void option4();
void option5();
void Ioptions();
void Ioption1();
void Ioption2();
void Ioption3();
void Ioption4();

// Declaring all of the manipulate functions
void color(int textColor, int bgColor);
void gotoxy(int x, int y);
void setConsoleWidth(int width);
void printCenteredColored(char text[]);

// The main flow of function
int main() {
    setConsoleWidth(80); // Sets the width of the console to 80 characters.

    int enter, keys;
    int choice = 1;

    // These variables are
    int validation = 0;

    // The two call functions are to display and highlight the first choice of the main menu to inform the user that the default is the first choice.
    mainmenu();
    option1();

    // This part reads the value of the key that was pressed by the user. The following keys that are recognized are only ENTER key, UP arrow key, and DOWN arrow key.  
    while(1) {
        enter = getch();

        // Checks if the return type of 'enter = getch()' isn't 13 OR when the user pressed an extended key. Ergo, the arrow UP and DOWN keys.
        if (enter == 0 || enter == 0xE0) {
            keys = getch();

            // These increments and decrement the choice value to inform the following switch function on which option will be highlighted
            // It also limits the choice from 1 to 5
            switch(keys) {
                case 72: // UP
                    choice--;
                    if (choice < 1) choice = 5;
                    break;
                case 80: // DOWN
                    choice++;
                    if (choice > 5) choice = 1;
                    break;
            }

            // Re-display the main menu again to avoid seeing only the highlighted parts.
            mainmenu();

            // It'll depend on the variable choice on which call function to run.
            switch(choice) {
                // The following call functions are to highlight the options.
                case 1: option1(); break;
                case 2: option2(); break;
                case 3: option3(); break;
                case 4: option4(); break;
                case 5: option5(); break;
            }
        } else {
            // After the user pressed the ENTER key, it'll run depending on what is the value of the choice
            if(enter == 13) { // ENTER
                switch(choice) {
                    case 1: addStudent(); break;

                    case 2:
                    // When there's no student that have yet to be added, it'll call the noData function to inform the user
                    if (totalstudents < 1) {
                        noData(); 
                        break;
                    }

                    viewStudents();
                    break;

                    case 3:
                    if (totalstudents < 1) {
                        noData(); 
                        break;
                    }
                    searchStudent(); 
                    break;

                    case 4: 
                    if (totalstudents < 1) {
                        noData(); 
                        break;
                    }
                    computeGrades();
                    break;

                    case 5: return 0;
                }

                
                getch(); // Waits for the user to press any key before proceeding to display the main menu and clear the screen
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

    // There's no need to put return function since the whole program will end if user chose option 5.
}

// Function to display the main menu at the middle and to limit the colors to be just in the middle
void printCenteredColored(char text[]) {
    int width = 80;
    int len = strlen(text);
    int padding = (width - len) / 2;

    color(7, 0);
    for(int i = 0; i < padding; i++) printf(" ");

    color(0, 7);
    printf("%s\n", text);

    color(7, 0);
}

// Function to display the main menu
void mainmenu() {
    system("cls");

    int column = 25;
    int row = 10;
    int startY = (column - row) / 2;


    gotoxy(0, startY);
    printCenteredColored("|**************************************|");
    printCenteredColored("|    STUDENT RECORD MANAGEMENT SYSTEM  |");
    printCenteredColored("|**************************************|");
    printCenteredColored("|              MAIN MENU               |");
    printCenteredColored("|**************************************|");
    printCenteredColored("| 1. Add Students                      |");
    printCenteredColored("| 2. View Students                     |");
    printCenteredColored("| 3. Search Student                    |");
    printCenteredColored("| 4. Compute Average                   |");
    printCenteredColored("| 5. Exit                              |");
    printCenteredColored("|**************************************|");
    printCenteredColored("Press ENTER key to proceed.");
    printCenteredColored("Press arrow UP to scroll up.");
    printCenteredColored("Press arrow DOWN to scroll down.");
}


// Function to create a line
void separator() {
    printf("|");
    for (int i = 0; i < 78; i++) printf("*");
    printf("|\n");
}

// A function to add a student and their information.
void addStudent() {
    system("cls");
    int i, j = 0;
    char checker;
    char checker2[10] = "";
    int validation;
    float firstsem, secondsem;
    int validation2;
    float firstsum = 0, secondsum = 0;

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
    while(validation == 0) {
        printf("Gender (M/F)\n");
        checker = getch();

        if (checker == 'M'||checker== 'm') { 
            sprintf(gender[totalstudents],"Male"); 
            printf("Your choice is Male");
            validation=1; 
        }
        else if (checker == 'F'||checker == 'f') { 
            sprintf(gender[totalstudents],"Female"); 
            printf("Your choice is Female");
            validation=1; 
        }
        else {
            printf("Invalid input.\n"); 
        }
    }
    
    printf("\nFirst semester grades:\n");
    for(i = 0; i < 3; i++) {
        printf("%s: ", subjects[i]);
        scanf("%f", &firstgrades[totalstudents][i]);
        firstsum += firstgrades[totalstudents][i];
    }

    printf("\nSecond semester grades:\n");
    for(i=0 ; i < 3; i++) {
        printf("%s: ", subjects[i]);
        scanf("%f", &secondgrades[totalstudents][i]);
        secondsum += secondgrades[totalstudents][i];
    }

    average[totalstudents][0] = firstsum / 3;
    average[totalstudents][1] = secondsum / 3;

    if (average[totalstudents][0] > 74.5) {
        sprintf(status[totalstudents][0], "Passed");
    }
    else {
        sprintf(status[totalstudents][0], "Failed");
    }
    if (average[totalstudents][1] > 74.5) {
        sprintf(status[totalstudents][1], "Passed");
    }
    else {
       sprintf(status[totalstudents][1], "Failed");
    }
    // Increments the totalstudents to count how many students are there
    totalstudents++;
    printf("\n\nStudent added successfully!\n");
}


void viewStudents() {
    system("cls");
    int enter;
    int key;
    int choice;
    int sortBy;

    Ioptions();
    Ioption1();
                                    
    while (1) {
        enter = getch();

        if (enter == 0 || enter == 0xE0) {
            key = getch();
            switch (key) {
                case 75: // Left arrow key
                choice--;
                if (choice < 1) choice = 4; 
                break;
                case 77: // Right arrow key
                choice++;
                if (choice > 4) choice = 1;
                break;
            }
        
            Ioptions();
            switch (choice) {
                case 1: Ioption1(); break;
                case 2: Ioption2(); break;
                case 3: Ioption3(); break;
                case 4: Ioption4(); break;
            }
        }
        else {
            if (enter == 13 || enter == 0x0D) {
                    switch (choice) {
                    case 1:
                    sortBy = 'N';
                    break;
                                
                    case 2:
                    sortBy = 'I';
                    break;
                                
                    case 3:
                    sortBy = 'G';
                    break;
                    
                    case 4:
                    sortBy = 'A';
                    break;
                }
                break;
            }
        }
    }
    
    choice = 1;
    
    printf("\n");
    sortStudents(sortBy);
    for (int i = 0; i < totalstudents; i++) {
        printf("Student No. %d . . .\n", i + 1);
        separator();
        printf("|First Name: %-20s ", firstname[i]);
        printf("|Last Name: %-20s ", lastname[i]);
        printf("|Age: %-5d |\n", age[i]);
        separator();
        printf("|ID: %-28s |Gender: %-35s |\n", id[i], gender[i]);
        separator();
        printf("\n\n");
    }
}

void searchStudent() {
    system("cls");
    char scanning[50];
    int validation = 0;
    int i, j;
    char choice;

    // Prompts the user to enter the unique id of a student.
    printf("ID of the student: ");
    scanf("%s", &scanning);

    // Checks the ID if it exists
    for (i = 0; i < totalstudents; i++) {
        if (strcmp(scanning, id[i]) == 0) {
            validation = 1;
            break;
        }
    }

    // If there's no student with the same inputted ID, it'll exit the function and return to the main
    // This function will be ignored if the inputted ID does exist
    if (validation == 0) {
        printf("There's no student with an id of %s.\n\n", scanning);
        return;
    }
    
    separator();
    printf("|First Name: %-20s |Last Name: %-20s |Age: %-5d |\n", firstname[i], lastname[i], age[i]);
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
    int validation = 0;
    char scanning[50];
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

    // This function copies the string and combines them from lastname is firstname
    sprintf(fullname, "%s, %s", lastname[i], firstname[i]);

    separator();
    printf("| Student: %-34s| Gender: %-10s| Age: %-7d|\n", fullname, gender[i], age[i]);
    separator();

    printf("|%-10s|%-33s|%-33s|\n", "Subjects", "First Semester", "Second Semester");
    printf("|**********|*********************************|*********************************|\n");

    for(j = 0; j < 3; j++) {
        printf("|%-10s|%13s%-20.2f|%13s%-20.2f|\n", subjects[j], "", firstgrades[i][j], "", secondgrades[i][j]);
    }
    separator();
    printf("|Average   |%13s%-20.2f|%13s%-20.2f|\n", "", average[i][0], "", average[i][1]);
    separator();

    printf("|Status    |%13s%-20s|%13s%-20s|\n", "", status[i][0], "", status[i][1]);
    separator();

    printf("|ID: %-74s|\n", id[i]);
    separator();
}

// Function to sort students depending on the user's preference
void sortStudents(char sortKey) {
    int i, j, k;

    for (i = 0; i < totalstudents - 1; i++) {
        for (j = 0; j < totalstudents - i - 1; j++) {
            int shouldSwap = 0;

            // Determine if a swap is needed based on the sortKey
            if (sortKey == 'N') { // Sort by First Name (Ascending)
                if (strcmp(firstname[j], firstname[j + 1]) > 0) {
                    shouldSwap = 1;
                }

            } 
            else if (sortKey == 'I') { // Sort by ID (Ascending)
                if (strcmp(id[j], id[j + 1]) > 0) {
                    shouldSwap = 1;
                }

            } 
            else if (sortKey == 'A') { // Sort by Age (Ascending)
                if (age[j] > age[j + 1]) {
                    shouldSwap = 1;
                }

            } 
            else if (sortKey == 'G') { // Sort by Gender (Ascending)
                 if (strcmp(gender[j], gender[j + 1]) > 0) {
                    shouldSwap = 1;
                }

            }

            if (shouldSwap == 1) {       
                // Swap Integers (Age)
                int temp_age = age[j];
                age[j] = age[j + 1];
                age[j + 1] = temp_age;

                // Swap Strings (Names, ID, Gender)
                char temp_str[100]; // Use a large enough buffer for temp string swaps
                float temp_avg;
                float temp;

                // Swaps the information of the students by ascending
                sprintf(temp_str, firstname[j]);
                sprintf(firstname[j], firstname[j + 1]);
                sprintf(firstname[j + 1], temp_str);

                sprintf(temp_str, lastname[j]);
                sprintf(lastname[j], lastname[j + 1]);
                sprintf(lastname[j + 1], temp_str);

                sprintf(temp_str, id[j]);
                sprintf(id[j], id[j + 1]);
                sprintf(id[j + 1], temp_str);
                
                sprintf(temp_str, gender[j]);
                sprintf(gender[j], gender[j + 1]);
                sprintf(gender[j + 1], temp_str);

                // To swap the average
                for(k = 0 ; k < 2; k++) {
                    temp_avg = average[j][k];
                    average[j][k] = average[j + 1][k];
                    average[j + 1][k] = temp_avg;
                }           

                // To swap the status
                for(k = 0; k < 2; k++) {
                    sprintf(temp_str, status[j][k]);
                    sprintf(status[j][k], status[j + 1][k]);
                    sprintf(status[j + 1][k], temp_str);
                }

                // To swap first semester grades
                for (k = 0; k < 3; k++) {
                    temp_avg = firstgrades[j][k];
                    firstgrades[j][k] = firstgrades[j + 1][k];
                    firstgrades[j + 1][k] = temp_avg;
                }

                // To swap second semester grades
                for (k = 0; k < 3; k++) {
                    temp_avg = secondgrades[j][k];
                    secondgrades[j][k] = secondgrades[j + 1][k];
                    secondgrades[j + 1][k] = temp_avg;
                }
            }
        }
    }
}

// To manipulate the color of the text/background, the position of the cursor, or the width of the console.
void color(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void gotoxy(int x, int y) {
    COORD c; c.X=x; c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setConsoleWidth(int width) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);

    int height = csbi.dwSize.Y;

    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(h, bufferSize);


    SMALL_RECT windowSize = csbi.srWindow;
    windowSize.Right = windowSize.Left + width - 1;
    SetConsoleWindowInfo(h, TRUE, &windowSize);
}

// Following functions highlights the options.
void option1() { 
    gotoxy(20, 12); 
    color(7, 0); 
    printf("%-39s|",  "| 1. Add Students");
}
void option2() { 
    gotoxy(20, 13); 
    color(7, 0); 
    printf("%-39s|",  "| 2. View Students"); 
}
void option3() { 
    gotoxy(20, 14); 
    color(7, 0); 
    printf("%-39s|",  "| 3. Search Student"); 
}
void option4() { 
    gotoxy(20, 15); 
    color(7, 0); 
    printf("%-39s|",  "| 4. Compute Average"); 
}
void option5() { 
    gotoxy(20, 16); 
    color(7, 0); 
    printf("%-39s|",  "| 5. Exit"); 
}

/* 
(N = Name | I = ID | G = Gender | A = Age)
*/
void Ioptions() {
    system("cls");
    gotoxy(0, 0);
    printf("Sort by...");
    gotoxy(0, 1);
    printf("(N = Name | I = ID | G = Gender | A = Age)");
}
void Ioption1() {
    gotoxy(0, 1);
    color(0, 7);
    printf("(N = Name |");
    gotoxy(10, 1);
    color(7, 0);
}

void Ioption2() {
    gotoxy(10, 1);
    color(0, 7);
    printf("| I = ID |");
    gotoxy(19, 1);
    color(7, 0);
}

void Ioption3() {
    gotoxy(19, 1);
    color(0, 7);
    printf("| G = Gender |");
    gotoxy(32, 1);
    color(7, 0);
}

void Ioption4() {
    gotoxy(32, 1);
    color(0, 7);
    printf("| A = Age)");
    gotoxy(42, 1);
    color(7, 0);
}

// To inform the user that there's no data yet.
void noData() {
    system("cls");
    printf("There's no data yet...");
}