//
// Created by LENOVO on 05-Oct-24.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>

#define BACKGROUND_WHITE 15
#define BORDER_WIDTH 150
#define BORDER_HEIGHT 50
#define ASCII_ART_MASSEGE_X 32
#define ASCII_ART_MASSEGE_Y 2
#define BACKGROUND_BLACK 0
#define WELCOME_SIZE 12
#define MENU_WIDTH 31
#define MENU_HEIGHT 3

enum PROGRAM_UI{
    START_UI = 0,
    LOG_IN_UI = 10,
    DEV_INFO_UI,
    OPTIONS_UI = 2,
};


int Start(int* state);

int Log_In_Menu(int* state);

void Find_Student_Menu(int* state);

void Display_Student_Menu(int* state);

void Edit_Student_Menu(int* state);

void Add_Student_Menu(int* state);

void Delete_Student_Menu(int* state);

void Developer_Info_Menu(int* state);


#endif //DISPLAY_H
