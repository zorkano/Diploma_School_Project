//
// Created by LENOVO on 05-Oct-24.
//

#ifndef SCHOOL_H
#define SCHOOL_H
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

typedef struct{
    char name[50];
    char address[50];
    char phone[11];
    int age;
    int ID;
    int grade;
}student_t;





void add_student(student_t School_arr, int School_count);

void delete_student(student_t School_arr, int School_count);

void display_student(student_t School_arr, int School_count);

void find_student(student_t School_arr, int School_count);

void store_student(student_t School_arr, int School_count);

int load_students(student_t School_arr);

int Log_in();



#endif //SCHOOL_H
