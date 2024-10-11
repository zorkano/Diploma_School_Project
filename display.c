/*
 * Created by LENOVO on 05-Oct-24.
 */
#include <Windows.h>
#include "school.h"
#include "display.h"

char* menu[] = {
" ============================== ",
"|                              |",
"|                              |",
"|                              |",
" ============================== ",
"\0"    
};


/*
 *  Function to set console text and background color
 */
void Set_Console_Color(const int textColor, const int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Shift bgColor by 4 bits to set it as the background color 
    int ColorAttribute = textColor | (bgColor << 4);  

    SetConsoleTextAttribute(hConsole, ColorAttribute);
}

/*
 * return the console cursor color to the default
 * (white text on black background)
 */ 
void Reset_Console_Color() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
}

/* 
 * Function to move the console cursor to specific (x, y) position
 */
void Move_Cursor(const int x, const int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const COORD Coord = {x, y};
    SetConsoleCursorPosition(hConsole, Coord);
}

/*
 * Function to create a colored brder of a given width and height at (x, y)
 * X: Along the horizontal plane
 * Y: Along the vertical plane
 */
void Application_Border(const int x, const int y, const int width, const int height, int borderColor){
    system("cls");
    Set_Console_Color(borderColor, 0);
    //clear the console screen
    

    // Top border
    for (int i = 1; i < width - 1; i++) {
        Move_Cursor(x + i, y);
        printf("\u2580");
    }

    // Side borders
    for (int i = 0; i < height; i++) {
        // Left border
        Move_Cursor(x, y + i);   
        printf("\u2588");

        // Right border
        Move_Cursor(x + width - 1, y + i);  
        printf("\u2588");
    }

    // Bottom border
    for (int i = 1; i < width - 1; i++) {
        Move_Cursor(x + i, y + height - 1);
        printf("\u2584");
    }
    Reset_Console_Color();  // Reset colors back to default
}

/*
 * Helper function to navigate the menus
 * (X,Y) horizontal and vertical positions respectivly
 * Color to highlight the choice
 */
void Choice_Navigation(int x, int y, int color) {
    int i, j;

    // Set the console color for the highlight
    Set_Console_Color(color, color);

    // Move the cursor to the top-left corner of the menu item
    Move_Cursor(x, y);

    // Draw a rectangular block for the highlight
    for (i = 0; i < MENU_HEIGHT; i++) {
        for (j = 0; j < MENU_WIDTH -1; j++) {
            // Move cursor to the correct position for each character
            Move_Cursor(x + j, y + i);
            // Print a solid block to fill the area
            printf("\u2588");
        }
    }

    // Reset the console color back to default after drawing the highlight
    Reset_Console_Color();
}

/*
 * Funcion to print ascii art on coordinates of console
 */
void Print_Ascii(int x, int y, char** s, int Message_Color){
    int i;
    Set_Console_Color(4, 0);
    for(i = 0; s[i] != "\0"; i++){
        Move_Cursor(x, y++);
        printf("%s", s[i]);
    }
    Reset_Console_Color();
}

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

/*
 * Function for the UI of the Log in menu
 * @param state: status of the login function
 */
int Log_In_Menu(int* state){
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


void Find_Student_Menu(int* state){
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
}

void Display_Student_Menu(int* state){
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
}

void Edit_Student_Menu(int* state){
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
}

void Add_Student_Menu(int* state){
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
}

void Delete_Student_Menu(int* state){
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
}

void Developer_Info_Menu(int* state){
    system("cls");
    Application_Border(0, 0, BORDER_WIDTH, BORDER_HEIGHT, BACKGROUND_WHITE);
}

/*
 * Function to draw the UI of the Main menu
 */
void Main_Menu_UI(){
    // system("chcp 65001");
    system("cls");

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

/*
 * Function to navigate the main menu
 */
int Start(int* state){
    int Current_Choice = LOG_IN_UI;

    Main_Menu_UI();
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