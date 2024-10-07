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



int Log_In_Menu(){
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
    int state;
    int i;

    system("cls");
    Application_Border(0, 0, 150, 50, BACKGROUND_WHITE);

    Print_Ascii(32, 2, Log_In_Message, BACKGROUND_RED);
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
    Set_Console_Color(0, 37);
    printf("Test");
    
    state = Log_in();
    return 1;
}


void Find_Student_Menu() {
    Application_Border(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Display_Student_Menu() {
    Application_Border(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Edit_Student_Menu() {
    Application_Border(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Add_Student_Menu() {
    Application_Border(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Delete_Student_Menu() {
    Application_Border(0, 0, 200, 50, BACKGROUND_WHITE);
}


void Developer_Info_Menu() {
    system("cls");
    Application_Border(0, 0, 200, 50, BACKGROUND_WHITE);
}

/*
 * Function to draw the UI of the Main menu
 */
void Main_Menu_UI() {
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

    Application_Border(0, 0, 150, 50, BACKGROUND_WHITE);

    Print_Ascii(32, 2, Welcome_messege, BACKGROUND_RED);

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
int Start(){
    int status = 1;
    int Current_Choice = 1;

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
    
    while(status){

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
                if(1 == Current_Choice){
                    Choice_Navigation(51, 26, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Choice_Navigation(51, 30, BACKGROUND_WHITE);
                    Move_Cursor(58, 31);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    printf("About Developer");
                    Current_Choice = 2;
                }else if(2 == Current_Choice){
                    Choice_Navigation(51, 30, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(58, 31);
                    printf("About Developer");
                    Choice_Navigation(51, 26, BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Current_Choice = 1;
                }
            }else if(VK_DOWN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown) {
                if(1 == Current_Choice){
                    Choice_Navigation(51, 26, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Choice_Navigation(51, 30, BACKGROUND_WHITE);
                    Move_Cursor(58, 31);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    printf("About Developer");
                    Current_Choice = 2;
                }else if(2 == Current_Choice){
                    Choice_Navigation(51, 30, BACKGROUND_BLACK);
                    Set_Console_Color(BACKGROUND_WHITE, BACKGROUND_BLACK);
                    Move_Cursor(58, 31);
                    printf("About Developer");
                    Choice_Navigation(51, 26, BACKGROUND_WHITE);
                    Set_Console_Color(BACKGROUND_BLACK, BACKGROUND_WHITE);
                    Move_Cursor(62, 27);
                    printf("Log In");
                    Current_Choice = 1;                    
                }
            }else if(VK_RETURN == virtualKeyCode && inputRecord.Event.KeyEvent.bKeyDown){
                if(1 == Current_Choice){
                    Log_In_Menu();
                    
                }else{
                    Developer_Info_Menu();
                }
                status = 0;
            }
            
            Reset_Console_Color();
        }
    }
    return Current_Choice;
}