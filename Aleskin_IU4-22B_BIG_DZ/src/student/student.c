#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define STUDENTS_FILE_PATH "students.csv"

Student* students = NULL;
int numStudents = 0;

void loadStudents() {
    FILE* studentsFile = fopen(STUDENTS_FILE_PATH, "r");
    if (studentsFile == NULL) {
        printf("Failed to open the students file.\n");
        return;
    }

    char line[256];
    int studentCount = 0;

    while (fgets(line, sizeof(line), studentsFile) != NULL) {
        Student student;
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
               student.studentId, student.firstName, student.lastName, student.faculty, student.major);

        students = (Student*)realloc(students, (studentCount + 1) * sizeof(Student));
        students[studentCount] = student;
        studentCount++;
    }

    numStudents = studentCount;

    fclose(studentsFile);
}

void addStudent(const Student* student) {
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].studentId, student->studentId) == 0) {
            printf("A student with the same ID already exists.\n");
            return;
        }
    }

    students = (Student*)realloc(students, (numStudents + 1) * sizeof(Student));
    students[numStudents] = *student;
    numStudents++;

    printf("Student added successfully.\n");
}

void removeStudent(const char* studentId) {
    int index = -1;

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < numStudents - 1; i++) {
        students[i] = students[i + 1];
    }

    numStudents--;

    printf("Student removed successfully.\n");
}

void editStudent(const char* studentId) {
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            printf("Enter new first name: ");
            scanf("%s", students[i].firstName);

            printf("Enter new last name: ");
            scanf("%s", students[i].lastName);

            printf("Enter new faculty: ");
            scanf("%s", students[i].faculty);

            printf("Enter new major: ");
            scanf("%s", students[i].major);

            printf("Student information updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void viewStudent(const char* studentId) {
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            printf("Student ID: %s\n", students[i].studentId);
            printf("First Name: %s\n", students[i].firstName);
            printf("Last Name: %s\n", students[i].lastName);
            printf("Faculty: %s\n", students[i].faculty);
            printf("Major: %s\n", students[i].major);
            return;
        }
    }

    printf("Student not found.\n");
}

void searchStudents(const char* lastName) {
    int found = 0;

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Student ID: %s\n", students[i].studentId);
            printf("First Name: %s\n", students[i].firstName);
            printf("Last Name: %s\n", students[i].lastName);
            printf("Faculty: %s\n", students[i].faculty);
            printf("Major: %s\n", students[i].major);
            printf("-----------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No students found with the last name: %s\n", lastName);
    }
}
