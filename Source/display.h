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
#define CARD_SIZE_Y 30
#define CARD_SIZE_X 63
#define CARD_POS_X 40 
#define CARD_POS_Y 10

#define BORDER_VERTICAL   "\u2588"  
#define BORDER_TOP       "\u2580"   
#define BORDER_BOTTOM    "\u2584"   
#define MENU_BLOCK       "\u2588"   
#define MENU_PADDING     1


enum PROGRAM_UI{
    START_UI = 0,
    LOG_IN_UI = 10,
    DEV_INFO_UI,
    OPTIONS_UI = 20,
    ADD_STUDENT_UI=21,
    DISPLAY_STUDENT_UI = 22,
    FIND_STUDENT_UI = 23,
    FIND_BY_NAME = 230,
    FIND_BY_AGE,
    EDIT_STUDENT,
};


void Start(int* state);

void Log_In_Menu(int* state);

void Options_menu(int* state);

void Find_Student_Menu(int* state);

void Display_Student_Menu(int* state);

void Edit_Student_Menu(int* state);

void Add_Student_Menu(int* state);

void Developer_Info_Menu(int* state);


#endif //DISPLAY_H
