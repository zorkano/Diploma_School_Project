/*
 * Created by LENOVO on 05-Oct-24.
 */
#include <Windows.h>
#include "school.h"
#include "display.h"
extern student_num;

char* menu[] = {
" ============================== ",
"|                              |",
"|                              |",
"|                              |",
" ============================== ",
"\0"    
};


/**
 * @brief Set the console text and background color.
 * 
 * @param textColor The color of the text.
 * @param bgColor The color of the background.
 */
void Set_Console_Color(const int textColor, const int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Shift bgColor by 4 bits to set it as the background color 
    int ColorAttribute = textColor | (bgColor << 4);  
    SetConsoleTextAttribute(hConsole, ColorAttribute);
}

/**
 * @brief Reset the console text and background color to default (white text on black background).
 */
void Reset_Console_Color() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
}

/**
 * @brief Move the console cursor to a specific (x, y) position.
 * 
 * @param x The horizontal position.
 * @param y The vertical position.
 */
void Move_Cursor(const int x, const int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const COORD Coord = {x, y};
    SetConsoleCursorPosition(hConsole, Coord);
}

/**
 * @brief Create a colored border of a given width and height at (x, y).
 * 
 * @param x The horizontal position
 * @param y The vertical position 
 * @param width The width of the border
 * @param height The height of the border
 * @param borderColor The color of the border
 */
void Application_Border(const int x, const int y, const int width, const int height, int borderColor) {
    // Clear screen and set border color
    system("cls");
    Set_Console_Color(borderColor, 0);
    
    // Draw top border
    for (int i = MENU_PADDING; i < width - MENU_PADDING; i++) {
        Move_Cursor(x + i, y);
        printf(BORDER_TOP);
    }

    // Draw side borders
    for (int i = 0; i < height; i++) {
        // Left border
        Move_Cursor(x, y + i);   
        printf(BORDER_VERTICAL);
        // Right border
        Move_Cursor(x + width - 1, y + i);  
        printf(BORDER_VERTICAL);
    }

    // Draw bottom border
    for (int i = MENU_PADDING; i < width - MENU_PADDING; i++) {
        Move_Cursor(x + i, y + height - 1);
        printf(BORDER_BOTTOM);
    }

    Reset_Console_Color();  // Reset colors back to default
}

/**
 * @brief Helper function to navigate the menus by highlighting selection.
 * 
 * @param x The horizontal position of highlight
 * @param y The vertical position of highlight 
 * @param color The color to highlight the choice
 */
void Choice_Navigation(int x, int y, int color) {
    int i, j;

    // Set highlight color
    Set_Console_Color(color, color);

    // Draw highlight block
    for (i = 0; i < MENU_HEIGHT; i++) {
        for (j = 0; j < MENU_WIDTH - MENU_PADDING; j++) {
            Move_Cursor(x + j, y + i);
            printf(MENU_BLOCK); // Fill with solid blocks
        }
    }

    Reset_Console_Color(); 
}

/**
 * @brief Print ASCII art at specified console coordinates.
 * 
 * @param x The horizontal position to start printing
 * @param y The vertical position to start printing
 * @param s The ASCII art string array to print
 * @param Message_Color The color of the ASCII art
 */
void Print_Ascii(int x, int y, char** s, int Message_Color) {
    int i;
    
    // Set text color for ASCII art
    Set_Console_Color(4, 0);

    // Print each line of the ASCII art
    for(i = 0; s[i] != "\0"; i++) {
        Move_Cursor(x, y++);
        printf("%s", s[i]);
    }

    Reset_Console_Color();
}

/**
 * @brief encrypts the password the user enters and shows asterisks instead of the actual characters
 * 
 * @param password the array the password will be stored in
 * @param size size of the password array
 */
void Get_Password(char* password, int size) {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode, numRead;
    INPUT_RECORD inputRecord;
    int index = 0;


    while (1) {
        // Read input event
        ReadConsoleInput(hConsole, &inputRecord, 1, &numRead);

        // Check for key press event
        if(inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown){
            char ch = inputRecord.Event.KeyEvent.uChar.AsciiChar;

            // Handle Enter key
            if(ch == '\r'){
                password[index] = '\0';  // Null-terminate the string
                printf("\n");  // Move to the next line after input is complete
                break;
            }

            // Handle Backspace key
            if(ch == '\b' && index > 0){
                index--;  // Move back the index
                printf("\b \b");  // Erase the previous character from the console
            }

            // Handle printable characters
            else if(ch >= 32 && ch <= 126 && index < size - 1){
                password[index++] = ch;  // Store the character in the password

                printf("*");  // Print asterisk in place of the actual character
            }
        }
    }
}

/**
 * @brief draws the log-in menu and handles the user input
 * @param state: a pointer to the state tracker of the program.
 */
void Log_In_Menu(int* state){
    char* Log_In_Message[] = {
    "██╗      ██████╗  ██████╗     ██╗███╗   ██╗    ████████╗ ██████╗",
    "██║     ██╔═══██╗██╔════╝     ██║████╗  ██║    ╚══██╔══╝██╔═══██╗",
    "██║     ██║   ██║██║  ███╗    ██║██╔██╗ ██║       ██║   ██║   ██║",
    "██║     ██║   ██║██║   ██║    ██║██║╚██╗██║       ██║   ██║   ██║",
    "███████╗╚██████╔╝╚██████╔╝    ██║██║ ╚████║       ██║   ╚██████╔╝",
    "╚══════╝ ╚═════╝  ╚═════╝     ╚═╝╚═╝  ╚═══╝       ╚═╝    ╚═════╝",
    "███╗   ███╗██╗   ██╗    ███████╗ ██████╗██╗  ██╗ ██████╗  ██████╗ ██╗",
    "████╗ ████║╚██╗ ██╔╝    ██╔════╝██╔════╝██║  ██║██╔═══██╗██╔═══██╗██║",
    "██╔████╔██║ ╚████╔╝     ███████╗██║     ███████║██║   ██║██║   ██║██║",
    "██║╚██╔╝██║  ╚██╔╝      ╚════██║██║     ██╔══██║██║   ██║██║   ██║██║",
    "██║ ╚═╝ ██║   ██║       ███████║╚██████╗██║  ██║╚██████╔╝╚██████╔╝███████╗",
    "╚═╝     ╚═╝   ╚═╝       ╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝",
    "\0"
    };
    char Username[20];
    char Password[20];
    int i;
    
    system("cls");
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
    Print_Ascii(ASCII_ART_MASSEGE_X, ASCII_ART_MASSEGE_Y, Log_In_Message, BACKGROUND_RED);
    Print_Ascii(50, 25, menu, BACKGROUND_RED);
    Move_Cursor(30, 35);
    printf("Entering the credentials wrong 3 times will send you back to the main menu");
    
    Move_Cursor(51, 27);
    Set_Console_Color(0, BACKGROUND_WHITE);
    for(i = 0; i < MENU_WIDTH -1; i++){
        printf(".");
    }
    Reset_Console_Color();
    Move_Cursor(51, 27);
    printf("Username:");
    Print_Ascii(50, 29, menu, BACKGROUND_RED);
    Move_Cursor(51, 31);
    Set_Console_Color(0, BACKGROUND_WHITE);

    for(i = 0; i < MENU_WIDTH -1; i++){
        printf(".");
    }
    Reset_Console_Color();
    Move_Cursor(51, 31);
    printf("Password:");
    Set_Console_Color(0, BACKGROUND_WHITE);

    //Move to the location of the username
    fflush(stdin);
    Move_Cursor(60, 27);
    scanf("%s", &Username);
    fflush(stdin);
    //Move to the location of the password
    Move_Cursor(60, 31);
    Get_Password(Password, 20);
    *state = Log_in(Username, Password);
    Reset_Console_Color();
}

/**
 * @brief handels the addition of a new student and saves it to the database
 * 
 */
student Add_Student_viewer(){
    int i = 0,j = 0;
    int ID_Check;
    char ch;
    int flag = 1;
    int stat;
    student temp;

    Set_Console_Color(4, 0);

    for(j = 0; j < CARD_SIZE_X - 1; j++){
        Move_Cursor(CARD_POS_X + 1 + j, CARD_POS_Y);
        printf("=");
        Move_Cursor(CARD_POS_X + 1 + j, CARD_POS_Y + CARD_SIZE_Y);
        printf("=");
    }

    for(i = 0;i < CARD_SIZE_Y - 1; i++){
        Move_Cursor(CARD_POS_X, 11+i);
        printf("|");
        Move_Cursor(CARD_POS_X + CARD_SIZE_X, 11+i);
        printf("|");
    }

    Reset_Console_Color();

    Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 3);
    printf("Student Name: ");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 4);
    printf("First,Middle and last name only.");
    
    Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 7);
    printf("Student ID: ");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 8);
    printf("From 0 to 1000 and not used.");
       
    Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 11);
    printf("Student Age: ");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 12);
    printf("from 5 to 25");
        
    Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 15);
    printf("Math grade: ");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 16);
    printf("from 0 to 100");
    
    Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 19);
    printf("English grade: ");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 20);
    printf("from 0 to 100");
    
    Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 23);
    printf("Physics grade: ");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 24);
    printf("from 0 to 100");

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 3);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 3);
        printf("New Student Name:");
        j=0;
        while(1){
            ch = getc(stdin);
            if((ch == '\n') || (j == 49)){
                temp.Name[j] = '\0';
                flag = 0;
                break;
            }else if((ch == '\b') && (j > 0)){
                temp.Name[j-1] = 0;
                j--;
            }else if((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == 32)){
                temp.Name[j] = ch;
            }else{
                break;
            }
            j++;
        }
    }while(flag);
    
    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 7);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 7);
        printf("Student ID:");
        stat = scanf("%i", &temp.ID);
        if(stat){
            ID_Check = check_ID(temp.ID);
        }
    }while((temp.ID > 1000 || temp.ID < 0 || !(stat) || ID_Check));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 11);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 11);
        printf("Student Age: ");
        stat = scanf(" %d", &temp.Age);
    }while(temp.Age < 5 || temp.Age > 25 || !(stat));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 15);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 15);
        printf("Math grade: ");
        scanf(" %d", &temp.Math_grade);
    }while(temp.Math_grade < 0 || temp.Math_grade > 100 || !(stat));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 19);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 19);
        printf("English grade: ");
        scanf(" %d", &temp.English_grade);
    }while(temp.English_grade < 0 || temp.English_grade > 100 || !(stat));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 23);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 5, CARD_POS_Y + 23);
        printf("Physics grade: ");
        scanf(" %d", &temp.Physics_grade);
    }while(temp.Physics_grade < 0 || temp.Physics_grade > 100 || !(stat));

    add_student(temp);
}

/**
 * @brief handels the display of the student information and editing.
 * 
 * @param std pointer to the student to be displayed.
 */
void Edit_student_viewer(student * std){
    int i,j;
    char ch;
    int stat;
    int flag = 1;
    int ID_Check;
    student temp;


    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);

    Set_Console_Color(4, 0);

    for(j = 0; j < CARD_SIZE_X - 1; j++){
        Move_Cursor(CARD_POS_X + 6 + j, CARD_POS_Y);
        printf("=");
        Move_Cursor(CARD_POS_X + 6 + j, CARD_POS_Y + CARD_SIZE_Y);
        printf("=");
    }

    for(i = 0;i < CARD_SIZE_Y - 1; i++){
        Move_Cursor(CARD_POS_X + 5, 11+i);
        printf("|");
        Move_Cursor(CARD_POS_X + 5 + CARD_SIZE_X, 11+i);
        printf("|");
    }

    Reset_Console_Color();

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 3);
    printf("Current Student Name: %s", std->Name);
    
    fflush(stdin);
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 7);
    printf("CurrentStudent ID: %d", std->ID);
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 11);
    printf("Current Student Age: %d", std->Age);
        
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 15);
    printf("Current Math grade: %d", std->Math_grade);
    
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 19);
    printf("Current English grade: %d", std->English_grade);
    
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 22);
    printf("Current Physics grade: %d", std->Physics_grade);

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 4);
    printf("New Student Name:");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 5);
    printf("First,Middle and last name only.");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 8);
    printf("New Student ID:");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 9);
    printf("From 0 to 1000 and not used.");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 12);
    printf("New Student Age:");

    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 13);
    printf("from 5 to 25");
        
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 16);
    printf("New Math grade:");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 17);
    printf("from 0 to 100");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 20);
    printf("New English grade:");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 21);
    printf("from 0 to 100");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 24);
    printf("New Physics grade:");
    
    Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 25);
    printf("from 0 to 100");


    
    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 4);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 4);
        printf("New Student Name:");
        j=0;
        while(1){
            ch = getc(stdin);
            if((ch == '\n') || (j == 49)){
                temp.Name[j] = '\0';
                flag = 0;
                break;
            }else if((ch == '\b') && (j > 0)){
                temp.Name[j-1] = 0;
                j--;
            }else if((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == 32)){
                temp.Name[j] = ch;
            }else{
                break;
            }
            j++;
        }
    }while(flag);

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 8);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 8);
        printf("New Student ID:");
        stat = scanf(" %d", &temp.ID);
        ID_Check = check_ID(temp.ID);
    }while(((temp.ID > 1000 || temp.ID < 0 || ID_Check || !(stat)) && (temp.ID != std->ID)));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 12);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 12);
        printf("New Student Age: ");
        stat = scanf(" %d", &temp.Age);
    }while(temp.Age < 5 || temp.Age > 25 || !(stat));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 16);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 16);
        printf("New Math grade: ");
        stat = scanf(" %d", &temp.Math_grade);
    }while(temp.Math_grade < 0 || temp.Math_grade > 100 || !(stat));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + i ,CARD_POS_Y + 20);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 20);
        printf("New English grade: ");
        stat = scanf(" %d", &temp.English_grade);
    }while(temp.English_grade < 0 || temp.English_grade > 100 || !(stat));

    do{
        fflush(stdin);
        for(i = 10;i < CARD_SIZE_X - 1; i++){
            Move_Cursor(CARD_POS_X + 3 ,CARD_POS_Y + 24);
            printf(" ");
        }
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 24);
        printf("New Physics grade: ");
        stat = scanf(" %d", &temp.Physics_grade);
    }while(temp.Physics_grade < 0 || temp.Physics_grade > 100 || !(stat));

    *std = temp;
}

/**
 * @brief displays the student information.
 * 
 * @param std pointer to the student to be displayed.
 */
void Find_Student_viewer(student* std){
    int i,j;
    int Option_num = 0;
    char ch;
    char* options[] = {
        "Edit Student",
        "Delete Student",
        "Back"
    };

    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);

    Set_Console_Color(4, 0);

    for(j = 0; j < CARD_SIZE_X - 1; j++){
        Move_Cursor(CARD_POS_X + 6 + j, CARD_POS_Y);
        printf("=");
        Move_Cursor(CARD_POS_X + 6 + j, CARD_POS_Y + CARD_SIZE_Y);
        printf("=");
    }

    for(i = 0;i < CARD_SIZE_Y - 1; i++){
        Move_Cursor(CARD_POS_X + 5, 11+i);
        printf("|");
        Move_Cursor(CARD_POS_X + 5 + CARD_SIZE_X, 11+i);
        printf("|");
    }

    Reset_Console_Color();
    if(std){
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 3);
        printf("Student Name: %s", std->Name);
        
        fflush(stdin);
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 6);
        printf("Student ID: %d", std->ID);
        
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 9);
        printf("Student Age: %d", std->Age);
            
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 12);
        printf("Math grade: %d", std->Math_grade);
        
        
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 15);
        printf("English grade: %d", std->English_grade);
        
        
        Move_Cursor(CARD_POS_X + 10, CARD_POS_Y + 18);
        printf("Physics grade: %d", std->Physics_grade);

        for(i = 0; i < 3; i++){
            Print_Ascii(5, 19 + (4 * i), menu, BACKGROUND_BLACK);
            Move_Cursor(10, 21 + (4 * i));
            printf(options[i]);
        }

        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        DWORD oldmode;
        // Get the current input mode of the console
        GetConsoleMode(hInput, &oldmode);
        mode = oldmode;
        
        // Set console mode to disable line buffering
        SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
        
        Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_WHITE);
        Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
        Move_Cursor(10, 21 + (4 * Option_num));
        printf(options[Option_num]);
        
        while(TRUE){

            // Create an event record structure
            INPUT_RECORD inputRecord;
            DWORD eventsRead;

            // Read the key press event
            ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
            

            // Check if the event is a key press
            if(inputRecord.EventType == KEY_EVENT){
                WORD virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;

                // Check for arrow keys
                if(VK_UP == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_BLACK);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(options[Option_num]);
                    if(0 == Option_num){
                        Option_num = 2;
                    }else{
                        Option_num--;
                    }
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(options[Option_num]);
                }else if(VK_DOWN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_BLACK);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(options[Option_num]);
                    if(2 == Option_num){
                        Option_num = 0;  
                    }else{
                        Option_num++;
                    }
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(options[Option_num]);
                }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                    Reset_Console_Color();
                    if(0 == Option_num){
                        Edit_student_viewer(std);
                    }else if(1 == Option_num){
                        delete_student(std);
                    }
                    break;
                }
            }
        }
    }else{
        Move_Cursor(CARD_POS_X + 30, CARD_POS_Y + 3);
        printf("No Such Student\n");
        Move_Cursor(CARD_POS_X + 27, CARD_POS_Y + 4);
        printf("Press Enter to go back");
        ch = getc(stdin);
        while(ch != '\n'){}
    }


}

/**
 * @brief displays all students in the database.
 * 
 * @param sort_type the type of sorting to be used. (BY NAME, BY ID, BY DEGREE)
 *
 * 
 */
void Display_student_viewer(int sort_type){
    int i;
    int j;
    int flag = 0;
    int counter = 0;
    char* str[]= {
        "Student Name: ",
        "Student ID: ",
        "Student Age: ",
        "Math grade: ",
        "English grade: ",
        "Physics grade: "
    };
    int Current_student = 0;
    student*  std;
    int std_num;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    DWORD oldmode;

    display_student(&std, &std_num, sort_type);

    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
    

    Set_Console_Color(4, 0);

    for(j = 0; j < CARD_SIZE_X - 1; j++){
        Move_Cursor(CARD_POS_X - 10 + j, CARD_POS_Y);
        printf("=");
        Move_Cursor(CARD_POS_X - 10 + j, CARD_POS_Y + CARD_SIZE_Y);
        printf("=");
    }


    for(i = 0;i < CARD_SIZE_Y - 1; i++){
        Move_Cursor(CARD_POS_X - 11, 11+i);
        printf("|");
        Move_Cursor(CARD_POS_X - 11 + CARD_SIZE_X, 11+i);
        printf("|");
    }
    Reset_Console_Color();

    Move_Cursor(38, 42);
    printf("Use \xE2\x86\x90 and \xE2\x86\x92 keys to navigate, Enter to go back");
    
    for(i = 0; i < 6;i++){
        Move_Cursor(CARD_POS_X - 7, CARD_POS_Y + (4 * (i + 1)) - 2);
        printf(str[i]);
        switch(i){
            case 0:
            printf("%s",std[Current_student].Name);
            break;
            case 1:
            printf("%d",std[Current_student].ID);
            break;
            case 2:
            printf("%d",std[Current_student].Age);
            break;
            case 3:
            printf("%d",std[Current_student].Math_grade);
            break;
            case 4:
            printf("%d",std[Current_student].English_grade);
            break;
            case 5:
            printf("%d",std[Current_student].Physics_grade);
            break;
        }
    }


    // Get the current input mode of the console
    GetConsoleMode(hInput, &oldmode);
    mode = oldmode;
    
    // Set console mode to disable line buffering
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    
    while(TRUE){
        // Create an event record structure
        INPUT_RECORD inputRecord;
        DWORD eventsRead;

        // Read the key press event
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
        if(flag){
            Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
            

            Set_Console_Color(4, 0);

            for(j = 0; j < CARD_SIZE_X - 1; j++){
                Move_Cursor(CARD_POS_X - 10 + j, CARD_POS_Y);
                printf("=");
                Move_Cursor(CARD_POS_X - 10 + j, CARD_POS_Y + CARD_SIZE_Y);
                printf("=");
            }


            for(i = 0;i < CARD_SIZE_Y - 1; i++){
                Move_Cursor(CARD_POS_X - 11, 11+i);
                printf("|");
                Move_Cursor(CARD_POS_X - 11 + CARD_SIZE_X, 11+i);
                printf("|");
            }
            Reset_Console_Color();

            Move_Cursor(38, 42);
            printf("Use \xE2\x86\x90 and \xE2\x86\x92 keys to navigate, Enter to go back");
            
            for(i = 0; i < 6;i++){
                Move_Cursor(CARD_POS_X - 7, CARD_POS_Y + (4 * (i + 1)) - 2);
                printf(str[i]);
                switch(i){
                    case 0:
                    printf("%s",std[Current_student].Name);
                    break;
                    case 1:
                    printf("%d",std[Current_student].ID);
                    break;
                    case 2:
                    printf("%d",std[Current_student].Age);
                    break;
                    case 3:
                    printf("%d",std[Current_student].Math_grade);
                    break;
                    case 4:
                    printf("%d",std[Current_student].English_grade);
                    break;
                    case 5:
                    printf("%d",std[Current_student].Physics_grade);
                    break;
                }
            }
            flag = 0;
        }
    
        if(inputRecord.EventType == KEY_EVENT){
            WORD virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;
            if(VK_LEFT == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                if(Current_student == 0){
                    flag = 0;
                }else{
                    flag = 1;
                    Current_student--;
                }
            }else if(VK_RIGHT == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                if(Current_student == (std_num - 1)){
                    flag = 0;
                }else{
                    Current_student++;
                    flag = 1;
                }
            }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                break;
            }
            Sleep(100);
        }
    }
}

/**
 *  @brief Draws the UI of the options Menu.
 *  
 *  
 * 
 *  @param state a pointer to the state tracker of the program.
 */
void Options_menu(int* state){
    int i;
    int Current_Choice = ADD_STUDENT_UI;
    int Option_num = 0;
    char* Options[] = {
    "Add Student",
    "Display Students",
    "Find Student",
    "Back to previous"
    };
    char* Options_Message[] = {        
    " ██████╗ ██████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗",
    "██╔═══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝",
    "██║   ██║██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║███████╗",
    "██║   ██║██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║╚════██║",
    "╚██████╔╝██║        ██║   ██║╚██████╔╝██║ ╚████║███████║",
    " ╚═════╝ ╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝",
    "         ███╗   ███╗███████╗███╗   ██╗██╗   ██╗",
    "         ████╗ ████║██╔════╝████╗  ██║██║   ██║",
    "         ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║",
    "         ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║",
    "         ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝",
    "         ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝",
    "\0"
    };
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
    Print_Ascii(ASCII_ART_MASSEGE_X + 15, ASCII_ART_MASSEGE_Y, Options_Message, BACKGROUND_RED);

    for(i = 0; i < 4; i++){
        Print_Ascii(57, 26 + (4 * i), menu, BACKGROUND_BLACK);
        Move_Cursor(59, 28 + (4 * i));
        printf(Options[i]);
    }
    Choice_Navigation(58, 27 + (4 * Option_num), BACKGROUND_WHITE);
    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
    Move_Cursor(60, 28 + (4 * Option_num));
    printf(Options[Option_num]);
    
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    DWORD oldmode;
    // Get the current input mode of the console
    GetConsoleMode(hInput, &oldmode);
    mode = oldmode;
    
    // Set console mode to disable line buffering
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    
    while(TRUE){

        // Create an event record structure
        INPUT_RECORD inputRecord;
        DWORD eventsRead;

        // Read the key press event
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
        

        // Check if the event is a key press
        if(inputRecord.EventType == KEY_EVENT){
            WORD virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;

            // Check for arrow keys
            if(VK_UP == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                Choice_Navigation(58, 27 + (4 * Option_num), BACKGROUND_BLACK);
                Move_Cursor(59, 28 + (4 * Option_num));
                printf(Options[Option_num]);
                if(ADD_STUDENT_UI == Current_Choice){
                    Current_Choice = START_UI;
                    Option_num = 3;
                }else{
                    if(START_UI == Current_Choice){
                        Current_Choice = FIND_STUDENT_UI;
                    }
                    else{
                        Current_Choice--;
                    }
                    Option_num--;
                }
                Choice_Navigation(58, 27 + (4 * Option_num), BACKGROUND_WHITE);
                Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                Move_Cursor(60, 28 + (4 * Option_num));
                printf(Options[Option_num]);
            }else if(VK_DOWN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                Choice_Navigation(58, 27 + (4 * Option_num), BACKGROUND_BLACK);
                Move_Cursor(59, 28 + (4 * Option_num));
                printf(Options[Option_num]);
                if(START_UI == Current_Choice){
                    Current_Choice = ADD_STUDENT_UI;
                    Option_num = 0;  
                }else{
                    if(FIND_STUDENT_UI == Current_Choice){
                        Current_Choice = START_UI;
                    }else{
                        Current_Choice++;
                    }
                    Option_num++;
                }
                Choice_Navigation(58, 27 + (4 * Option_num), BACKGROUND_WHITE);
                Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                Move_Cursor(60, 28 + (4 * Option_num));
                printf(Options[Option_num]);
            }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                *state = Current_Choice;
                store_students();
                break;
            }
            Reset_Console_Color();
        }
    }
}

/**
 * @brief 
 * 
 * @param state a pointer to the state tracker of the program.
 */
void Find_Student_Menu(int* state){
    int Option_num = 0;
    int i;
    int ID;
    char ch;
    char Name[50];
    char* find_by[] = {
        "By name",
        "By ID",
        "Back"
    };
    
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);



    for(i = 0; i < 3; i++){
    Print_Ascii(50, 19 + (4 * i), menu, BACKGROUND_BLACK);
    Move_Cursor(55, 21 + (4 * i));
    printf(find_by[i]);
    }

    Choice_Navigation(51, 20 + (4 * Option_num), BACKGROUND_WHITE);
    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
    Move_Cursor(55, 21 + (4 * Option_num));
    printf(find_by[Option_num]);

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);;
    

    
    while(TRUE){

        // Create an event record structure
        INPUT_RECORD inputRecord;
        DWORD eventsRead;

        // Read the key press event
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
        

        // Check if the event is a key press
        if(inputRecord.EventType == KEY_EVENT){
            WORD virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;

            // Check for arrow keys
            if(VK_UP == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                Choice_Navigation(51, 20 + (4 * Option_num), BACKGROUND_BLACK);
                Move_Cursor(55, 21 + (4 * Option_num));
                printf(find_by[Option_num]);
                if(0 == Option_num){
                    Option_num = 2;
                }else{
                    Option_num--;
                }
                Choice_Navigation(51, 20 + (4 * Option_num), BACKGROUND_WHITE);
                Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                Move_Cursor(55, 21 + (4 * Option_num));
                printf(find_by[Option_num]);
            }else if(VK_DOWN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                Choice_Navigation(51, 20 + (4 * Option_num), BACKGROUND_BLACK);
                Move_Cursor(55, 21 + (4 * Option_num));
                printf(find_by[Option_num]);
                if(2 == Option_num){
                    Option_num = 0;  
                }else{
                    Option_num++;
                }
                Choice_Navigation(51, 20 + (4 * Option_num), BACKGROUND_WHITE);
                Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                Move_Cursor(55, 21 + (4 * Option_num));
                printf(find_by[Option_num]);
            }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                Print_Ascii(84, 19, menu, BACKGROUND_RED);
                Move_Cursor(85,21);
                fflush(stdin);
                if(0 == Option_num){
                    printf("Name: ");
                    for(i = 0; i < 50; i++){
                        ch = getc(stdin);
                        if(ch == '\n'){
                            Name[i] = '\0';
                            break;
                        }else if((ch == '\b') && (i > 0)){
                            Name[i-1] = 0;
                        }else{
                            Name[i] = ch;
                        }
                    }
                    Find_Student_viewer(find_student_by_Name(Name));
                }else if(1 == Option_num){
                    printf("ID: ");
                    scanf("%d", &ID);
                    fflush(stdin);
                    Find_Student_viewer(find_student_by_ID(ID));
                }
                *state = OPTIONS_UI;
                break;
            }
            Reset_Console_Color();
        }
    }
}

/**
 * @brief 
 * 
 * @param state a pointer to the state tracker of the program.
 */
void Display_Student_Menu(int* state){
    int i;
    int Option_num = 0;
    char* Options[] = {
        "Sort By Name",
        "Sort By ID",
        "Sort By Grades",
        "Back",
    }; 
    
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
    for(i = 0; i < 4; i++){
        Print_Ascii(5, 19 + (4 * i), menu, BACKGROUND_RED);
        Move_Cursor(10, 21 + (4 * i));
        printf(Options[i]);
    }

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        DWORD oldmode;
        // Get the current input mode of the console
        GetConsoleMode(hInput, &oldmode);
        mode = oldmode;
        
        // Set console mode to disable line buffering
        SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
        
        Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_WHITE);
        Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
        Move_Cursor(10, 21 + (4 * Option_num));
        printf(Options[Option_num]);
        
        while(TRUE){

            // Create an event record structure
            INPUT_RECORD inputRecord;
            DWORD eventsRead;

            // Read the key press event
            ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
            

            // Check if the event is a key press
            if(inputRecord.EventType == KEY_EVENT){
                WORD virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;

                // Check for arrow keys
                if(VK_UP == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_BLACK);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(Options[Option_num]);
                    if(0 == Option_num){
                        Option_num = 3;
                    }else{
                        Option_num--;
                    }
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(Options[Option_num]);
                }else if(VK_DOWN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_BLACK);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(Options[Option_num]);
                    if(3 == Option_num){
                        Option_num = 0;  
                    }else{
                        Option_num++;
                    }
                    Choice_Navigation(6, 20 + (4 * Option_num), BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(10, 21 + (4 * Option_num));
                    printf(Options[Option_num]);
                }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                    Reset_Console_Color();
                    if(Option_num != 3){
                        Display_student_viewer(Option_num);
                    }
                    *state = OPTIONS_UI;
                    break;
                }
            }
        }
    
}

/**
 * @brief 
 * 
 * @param state a pointer to the state tracker of the program.
 */
void Add_Student_Menu(int* state){ 
    int i;
    if(student_num == MAX_STUDENTS){
        Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
        Move_Cursor(50, 20);
        printf("No More Space for new students");
        Move_Cursor(50, 21);
        printf("Press Enter to go back");
        char ch;
        while(ch != '\n'){
            ch = getc(stdin);
        }
        *state = OPTIONS_UI;
    }
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);

    Add_Student_viewer();

    *state = OPTIONS_UI;
}

void Developer_Info_Menu(int* state){
    int i;
    int j;
    char ch;

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    DWORD oldmode;
    // Get the current input mode of the console
    GetConsoleMode(hInput, &oldmode);
    mode = oldmode;
    
    // Set console mode to disable line buffering
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
    

    Set_Console_Color(4, 0);

    for(j = 0; j < CARD_SIZE_X - 1; j++){
        Move_Cursor(CARD_POS_X - 10 + j, CARD_POS_Y);
        printf("=");
        Move_Cursor(CARD_POS_X - 10 + j, CARD_POS_Y + CARD_SIZE_Y);
        printf("=");
    }


    for(i = 0;i < CARD_SIZE_Y - 1; i++){
        Move_Cursor(CARD_POS_X - 11, 11+i);
        printf("|");
        Move_Cursor(CARD_POS_X - 11 + CARD_SIZE_X, 11+i);
        printf("|");
    }
    Reset_Console_Color();
    Move_Cursor(CARD_POS_X - 5, 13);
    printf("Developer Name : Seif aldeen Mahmoud");
    Move_Cursor(CARD_POS_X - 5, 17);
    printf("Age: 21");
    Move_Cursor(CARD_POS_X - 5, 21);
    printf("Mansoura University");
    Move_Cursor(CARD_POS_X - 5, 25);
    printf("Faculty of Engineering");
    Move_Cursor(CARD_POS_X - 5, 29);
    printf("CCE Level 300");
    while(ch != '\n'){
        ch = getc(stdin);
    }
    *state = START_UI;
}

/**
 * @brief 
 * 
 */
void Main_Menu_UI(){
    char* Welcome_messege[] = {
    "██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗",
    "██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗",
    "██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║",
    "██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║",
    "╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝",
    " ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝",
    "███╗   ███╗██╗   ██╗    ███████╗ ██████╗██╗  ██╗ ██████╗  ██████╗ ██╗",
    "████╗ ████║╚██╗ ██╔╝    ██╔════╝██╔════╝██║  ██║██╔═══██╗██╔═══██╗██║",
    "██╔████╔██║ ╚████╔╝     ███████╗██║     ███████║██║   ██║██║   ██║██║",
    "██║╚██╔╝██║  ╚██╔╝      ╚════██║██║     ██╔══██║██║   ██║██║   ██║██║",
    "██║ ╚═╝ ██║   ██║       ███████║╚██████╗██║  ██║╚██████╔╝╚██████╔╝███████╗",
    "╚═╝     ╚═╝   ╚═╝       ╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝",
    "\0"
    };

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);

    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);

    Print_Ascii(ASCII_ART_MASSEGE_X,
     ASCII_ART_MASSEGE_Y, Welcome_messege, BACKGROUND_RED);

    Print_Ascii(50, 25, menu, BACKGROUND_RED);
    Move_Cursor(62, 27);
    printf("Log In");
    Print_Ascii(50, 29, menu, BACKGROUND_RED);
    Move_Cursor(58, 31);
    printf("About Developer");

    Move_Cursor(51,35);
    printf("Made By\\ Seif Al-deen Mahmoud");
}

/**
 * @brief Draws the main application menu.
 * 
 * @param state a pointer to the state tracker of the program.
 */
void Start(int* state){
    int Current_Choice = LOG_IN_UI;

    Main_Menu_UI();
    load_students();
    Choice_Navigation(51, 26, BACKGROUND_WHITE);
    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
    Move_Cursor(62, 27);
    printf("Log In");
    Reset_Console_Color();
    Move_Cursor(0,51);


    
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    DWORD oldmode;
    // Get the current input mode of the console
    GetConsoleMode(hInput, &oldmode);
    mode = oldmode;
    
    // Set console mode to disable line buffering
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    
    while(TRUE){

        // Create an event record structure
        INPUT_RECORD inputRecord;
        DWORD eventsRead;

        // Read the key press event
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
        

        // Check if the event is a key press
        if(inputRecord.EventType == KEY_EVENT){
            WORD virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;

            // Check for arrow keys
            if(VK_UP == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                if(LOG_IN_UI == Current_Choice){
                    Choice_Navigation(51, 26, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Choice_Navigation(51, 30, BACKGROUND_WHITE);
                    Move_Cursor(58, 31);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    printf("About Developer");
                    Current_Choice = DEV_INFO_UI;
                }else if(DEV_INFO_UI == Current_Choice){
                    Choice_Navigation(51, 30, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(58, 31);
                    printf("About Developer");
                    Choice_Navigation(51, 26, BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Current_Choice = LOG_IN_UI;
                }
            }else if(VK_DOWN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                if(LOG_IN_UI == Current_Choice){
                    Choice_Navigation(51, 26, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Choice_Navigation(51, 30, BACKGROUND_WHITE);
                    Move_Cursor(58, 31);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    printf("About Developer");
                    Current_Choice = DEV_INFO_UI;
                }else if(DEV_INFO_UI == Current_Choice){
                    Choice_Navigation(51, 30, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(58, 31);
                    printf("About Developer");
                    Choice_Navigation(51, 26, BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Current_Choice = LOG_IN_UI;                    
                }
            }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                if(LOG_IN_UI == Current_Choice){
                    *state = LOG_IN_UI;
                }else{
                    *state = DEV_INFO_UI;
                }
                break;
            }
            Reset_Console_Color();
        }
    }
}