#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "book/book.h"
#include "student/student.h"
#include "loan/loan.h"

void displayMainMenu() {
    printf("Main Menu\n");
    printf("1. Book Management\n");
    printf("2. Student Management\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void displayBookMenu() {
    printf("Book Menu\n");
    printf("1. Add a new book\n");
    printf("2. Remove a book\n");
    printf("3. View book information\n");
    printf("4. Display all books\n");
    printf("5. Edit book information\n");
    printf("6. Loan a book\n");
    printf("7. Return a book\n");
    printf("0. Return to Main Menu\n");
    printf("Enter your choice: ");
}

void displayStudentMenu() {
    printf("Student Menu\n");
    printf("1. Add a new student\n");
    printf("2. Remove a student\n");
    printf("3. Edit student information\n");
    printf("4. View student information\n");
    printf("5. Search students by last name\n");
    printf("0. Return to Main Menu\n");
    printf("Enter your choice: ");
}

int main() {
    char username[50];
    char password[50];
    int isLoggedIn = 0;

    while (!isLoggedIn) {
        printf("Login\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        isLoggedIn = authenticateUser(username, password);

        if (!isLoggedIn) {
            printf("Invalid credentials. Please try again.\n");
        }
    }

    int choice;
    int exitProgram = 0;

    while (!exitProgram) {
        displayMainMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                exitProgram = 1;
                printf("Exiting the program. Goodbye!\n");
                break;
            case 1:
                handleBookManagement();
                break;
            case 2:
                handleStudentManagement();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}