/*
** Created by LENOVO on 05-Oct-24.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "school.h"


student_t school[1000];


void add_student(student_t* School_arr, int School_count){
    printf("");
}

void delete_student(student_t* School_arr, int School_count){

}

void display_student(student_t* School_arr, int School_count){

}

void find_student(student_t* School_arr, int School_count){

}

void store_student(student_t* School_arr, int School_count){

}

int load_students(student_t* School_arr){
    return 0;
}

int Log_in(char* Username, char* Password){
    int user_state;
    int password_state;
    int ret;
    int Loop_status = 1;

    while(Loop_status){
        user_state = !(strcmp(Username, Staff_Username));
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

