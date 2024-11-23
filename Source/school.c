/*
** Created by LENOVO on 05-Oct-24.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "school.h"

student School[MAX_STUDENTS];
int student_number = 0;

/**
 *
 * 
 * @brief Add a student to the school Array.
 * 
 * @param student The student to add.
 */
void add_student(student student){
    School[student_number] = student;
    student_number++;
    store_students();
}

/**
 * @brief Delete a student from the school Array.
 * 
 * @param std The student to delete.
 */
void delete_student(student* std){
    int i;
    i = (std - School);
    School[i] = School[student_number - 1];
    School[student_number - 1] = (student){0};
    student_number--;
}

/**
 * @brief Compare students by name.
 * 
 * @param a The first student.
 * @param b The second student.
 * @return int The comparison result.
 */
int Name_compare(const void *a, const void *b){
    const student *std1 = (const student *)a;
    const student *std2 = (const student *)b;
    return strcmp(std1->Name, std2->Name);
}

/**
 * @brief Compare students by ID.
 * 
 * @param a The first student.
 * @param b The second student.
 * @return int The comparison result.
 */
int ID_compare(const void *a, const void *b){
    const student *std1 = (const student *)a;
    const student *std2 = (const student *)b;
    int ret;
    if(std1->ID > std2->ID){
        ret = 1;
    } else {
        ret = -1;
    }
    return ret;
}

/**
 * @brief helper function to compare students by average of grades
 * 
 * @param a pointer to the first student
 * @param b pointer to the second student
 * @return the comparison result  -1 if the first student has a higher average, 1 if the second student has a higher average, 0 if they have the same average
 */
int grades_compare(const void *a, const void *b){
    const student *std1 = (const student *)a;
    const student *std2 = (const student *)b;
    int ret;
    float avg_1 = ((std1->Math_grade) + (std1->English_grade) + (std1->Physics_grade)) / 3;
    float avg_2 = ((std2->Math_grade) + (std2->English_grade) + (std2->Physics_grade)) / 3;

    if(avg_1 > avg_2){
        ret = -1;
    }else if(avg_1 < avg_2){
        ret = 1;
    }else{
        ret = 0;
    }
    return ret;
}

/**
 * @brief Sort the student array based on specified sort type.
 * 
 * @param sort_type The type of sorting (1 for Name, 2 for ID).
 */
void Array_Sort(int sort_type){
    if(sort_type == NAME_SORT){
        qsort(School, student_number, sizeof(student), Name_compare);
    }
    else if(sort_type == ID_SORT){
        qsort(School, student_number, sizeof(student), ID_compare);
    }
}

/**
 * @brief Display students.
 * 
 * @param std The array of students.
 * @param stds_number The number of students.
 * @param sort_type The type of sorting.
 */
void display_student(student** std, int* stds_number, int sort_type){
    Array_Sort(sort_type);
    *std = School;
    *stds_number = student_number;
}

/**
 * @brief Find a student by name.
 * 
 * @param Name The name of the student.
 * @return student* The student found.
 */
student* find_student_by_Name(char * Name){
    int i;
    for(i = 0; i < student_number; i++){
        if(_stricmp(School[i].Name, Name) == 0){
            return (School + i);
        }
    }
    return NULL;
}

/**
 * @brief Find a student by ID.
 * 
 * @param ID The ID of the student.
 * @return student* The student found.
 */
student* find_student_by_ID(int ID){
    int i;
    for(i = 0; i < student_number; i++){
        if(School[i].ID == ID){
            return &School[i];
        }
    }
    return NULL;
}

/**
 * @brief Check if a student ID exists.
 * 
 * @param ID The ID to check.
 * @return int 1 if the ID exists, 0 otherwise.
 */
int check_ID(int ID){
    int i;
    for(i = 0; i < student_number; i++){
        if(School[i].ID == ID){
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Store students to a file.
 */
void store_students(){
    FILE *file = fopen("students.dat", "wb");
    if (file != NULL) {
        fwrite(School, sizeof(student), student_number, file);
        fclose(file);
    }
}

/**
 * @brief Load students from a file.
 * 
 * @return int The number of students loaded.
 */
int load_students(){
    FILE *file = fopen("students.dat", "rb");
    if (file != NULL) {
        student_number = fread(School, sizeof(student), 1000, file);
        fclose(file);
    }
    return student_number;
}

/**
 * @brief Authenticate user login credentials.
 * 
 * @return int Returns 1 if login successful, 0 otherwise.
 */
int Log_in(){
    char Username[50];
    char Password[50];
    printf("Username: ");
    scanf("%s", Username);
    printf("Password: ");
    scanf("%s", Password);
    return 1;
}
