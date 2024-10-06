/*
 * Created by LENOVO on 05-Oct-24.
 */

#include "school.h"
#include "display.h"

/*
 *  Function to set console text and background color
 */
void setConsoleColor(const int textColor, const int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Shift bgColor by 4 bits to set it as the background color 
    int ColorAttribute = textColor | (bgColor << 4);  

    SetConsoleTextAttribute(hConsole, ColorAttribute);
}

/*
 * return the console cursor color to the default
 * (white text on black background)
 */ 
void resetConsoleColor() {
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
void drawBorderRectangle(const int x, const int y, const int width, const int height, int borderColor){
    system("cls");
    setConsoleColor(borderColor, 0);
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
    resetConsoleColor();  // Reset colors back to default
}

/*
 * Funcion to print ascii art on coordinates of console
 */
void Print_Ascii(int x, int y, char** s, int Message_Color){
    int i;
    setConsoleColor(4, 0);
    for(i = 0; s[i] != "\0"; i++){
        Move_Cursor(x, y++);
        printf("%s", s[i]);
    }
    resetConsoleColor();
}

/*
 * Function draws the UI of the Main menu
 */
void Main_menu_UI() {
    drawBorderRectangle(0, 0, 150, 50, BACKGROUND_WHITE);

    Print_Ascii(32, 2, Welcome_messege, BACKGROUND_RED);

    Move_Cursor(45, 25);
    Print_Ascii(50, 25, menu, BACKGROUND_RED);
    Move_Cursor(55, 27);
    printf("Log In");
    Print_Ascii(50, 29, menu, BACKGROUND_RED);
    Move_Cursor(55, 31);
    printf("Programmer Info");

    Move_Cursor(51,35);
    printf("Made By\\ Seif Al-deen Mahmoud");
    Move_Cursor(55,36);
}

void Main_menu(){
    Main_menu_UI();


}


void Find_Student_menu() {
    drawBorderRectangle(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Display_Student_menu() {
    drawBorderRectangle(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Edit_Student_menu() {
    drawBorderRectangle(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Add_Student_menu() {
    drawBorderRectangle(0, 0, 200, 50, BACKGROUND_WHITE);
}

void Delete_Student_menu() {
    drawBorderRectangle(0, 0, 200, 50, BACKGROUND_WHITE);
}


void My_Info_menu() {
    drawBorderRectangle(0, 0, 200, 50, BACKGROUND_WHITE);
}




