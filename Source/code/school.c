/*
** Created by LENOVO on 05-Oct-24.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "school.h"

student School[1000];

static int student_number = 0;

void add_student(student student){
    School[student_number] = student;
    student_number++;
    store_students();
}

void delete_student(student* std){
    int i;
    i = (std - School);
    School[i] = School[student_number - 1];
    School[student_number - 1] = (student){0};
    student_number--;
}

int Name_compare(const void *a, const void *b){
    const student *std1 = (const student *)a;
    const student *std2 = (const student *)b;

    return strcmp(std1->Name, std2->Name);
}

int ID_compare(const void *a, const void *b){
    const student *std1 = (const student *)a;
    const student *std2 = (const student *)b;
    int ret;

    if(std1->ID > std2->ID){
        ret = 1;
    }else if(std1->ID < std2->ID){
        ret = -1;
    }else{
        ret = 0;
    }

    return ret;
}

int grades_compare(const void *a, const void *b){
    const student *std1 = (const student *)a;
    const student *std2 = (const student *)b;
    int ret;
    int avg_1 = ((std1->Math_grade) + (std1->English_grade) + (std1->Physics_grade)) / 3;
    int avg_2 = ((std2->Math_grade) + (std2->English_grade) + (std2->Physics_grade)) / 3;

    if(avg_1 > avg_2){
        ret = -1;
    }else if(avg_1 < avg_2){
        ret = 1;
    }else{
        ret = 0;
    }
    
    return ret;
}

void Array_Sort(int sort_type){
    switch(sort_type){
    case 0:
        qsort(School, student_number, sizeof(student), Name_compare);
        break;
    case 1:
        qsort(School, student_number, sizeof(student), ID_compare);
        break;
    default:
        qsort(School, student_number, sizeof(student), grades_compare);
        break;
    }

}


void display_student(student** std, int* stds_number, int sort_type){
    Array_Sort(sort_type);
    *std = School;
    *stds_number = student_number;
}

student* find_student_by_Name(char * Name){
    int i;
    for(i = 0; i < student_number; i++){
        if(_stricmp(School[i].Name, Name) == 0){
            return (School + i);
        }
    }
    return NULL;
}

student* find_student_by_ID(int ID){
    int i;
    for(i = 0; i < student_number; i++){
        if(School[i].ID == ID){
            return &School[i];
        }
    }
    return NULL;
}

int check_ID(int ID){
    int i;
    for(i = 0; i < student_number; i++){
        if(School[i].ID == ID){
            return 1;
        }
    }
    return 0;

}

void store_students(){
    FILE *file = fopen("Students.dat", "wb");
    fwrite(&School, sizeof(student), student_number, file);
    fclose(file);
}

int load_students(){
    FILE *file = fopen("Students.dat", "rb");

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET); 
    student_number = fileSize / sizeof(student);
    fread(School, sizeof(student), student_number, file);
    fclose(file);
}

int Log_in(char* Username, char* Password){
    int user_state;
    int password_state;
    int ret;
    int Loop_status = 1;

    while(Loop_status){
        user_state = !(_stricmp(Username, Staff_Username));
        password_state = !(strcmp(Password, Staff_Password));

        if(user_state && password_state){
            ret = Authorized;
            Loop_status = 0;
        }
        else{
            ret = NotAuthorized;
            Loop_status = 0;
        }
    }
    fflush(stdin);
    return ret;
}

