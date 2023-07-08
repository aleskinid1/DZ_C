#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char studentId[10];
    char firstName[50];
    char lastName[50];
    char faculty[50];
    char major[100];
} Student;

void loadStudents();
void addStudent(const Student* student);
void removeStudent(const char* studentId);
void editStudent(const char* studentId);
void viewStudent(const char* studentId);
void searchStudents(const char* lastName);
void handleStudentManagement();

#endif /* STUDENT_H */
