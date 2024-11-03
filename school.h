//
// Created by LENOVO on 05-Oct-24.
//

#ifndef SCHOOL_H
#define SCHOOL_H

typedef struct student{
    char Name[50];
    int ID;
    short Age;
    short Math_grade;
    short English_grade;
    short Physics_grade;
}student;

void add_student();

void delete_student(student* std);

int check_ID(int ID);

void display_student(student** std, int* const stds_number, int sort_type);

student* find_student_by_Name(char * Name);

student* find_student_by_ID(int ID);

void edit_student(student* std);

void store_students();

int load_students();

int Log_in();



#endif //SCHOOL_H
