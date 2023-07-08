#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loan.h"

#define LOANS_FILE_PATH "student_books.csv"

Loan* loans = NULL;
int numLoans = 0;

void loadLoans() {
    FILE* loansFile = fopen(LOANS_FILE_PATH, "r");
    if (loansFile == NULL) {
        printf("Failed to open the loans file.\n");
        return;
    }

    char line[256];
    int loanCount = 0;

    while (fgets(line, sizeof(line), loansFile) != NULL) {
        Loan loan;
        sscanf(line, "%[^,],%[^,],%[^\n]",
               loan.isbn, loan.studentId, loan.returnDate);

        loans = (Loan*)realloc(loans, (loanCount + 1) * sizeof(Loan));
        loans[loanCount] = loan;
        loanCount++;
    }

    numLoans = loanCount;

    fclose(loansFile);
}

void loanBook(const char* isbn, const char* studentId) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].availableQuantity > 0) {
                books[i].availableQuantity--;

                Loan loan;
                strcpy(loan.isbn, isbn);
                strcpy(loan.studentId, studentId);
                // Set the return date according to your implementation

                loans = (Loan*)realloc(loans, (numLoans + 1) * sizeof(Loan));
                loans[numLoans] = loan;
                numLoans++;

                printf("Book loaned successfully.\n");
            } else {
                printf("No available copies of the book.\n");
            }

            return;
        }
    }

    printf("Book not found.\n");
}

void returnBook(const char* isbn, const char* studentId) {
    int loanIndex = -1;

    for (int i = 0; i < numLoans; i++) {
        if (strcmp(loans[i].isbn, isbn) == 0 && strcmp(loans[i].studentId, studentId) == 0) {
            loanIndex = i;
            break;
        }
    }

    if (loanIndex == -1) {
        printf("No active loan found for the given book and student.\n");
        return;
    }

    for (int i = loanIndex; i < numLoans - 1; i++) {
        loans[i] = loans[i + 1];
    }

    numLoans--;

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].availableQuantity < books[i].totalQuantity) {
                books[i].availableQuantity++;
                printf("Book returned successfully.\n");
            } else {
                printf("All copies of the book are already returned.\n");
            }

            return;
        }
    }

    printf("Book not found.\n");
}

void displayStudentLoans(const char* studentId) {
    int found = 0;

    printf("Loans for Student ID: %s\n", studentId);
    printf("ISBN\tReturn Date\n");
    printf("--------------------\n");

    for (int i = 0; i < numLoans; i++) {
        if (strcmp(loans[i].studentId, studentId) == 0) {
            printf("%s\t%s\n", loans[i].isbn, loans[i].returnDate);
            found = 1;
        }
    }

    if (!found) {
        printf("No loans found for the student.\n");
    }
}

void displayBookLoans(const char* isbn) {
    int found = 0;

    printf("Loans for Book ISBN: %s\n", isbn);
    printf("Student ID\tReturn Date\n");
    printf("---------------------------\n");

    for (int i = 0; i < numLoans; i++) {
        if (strcmp(loans[i].isbn, isbn) == 0) {
            printf("%s\t%s\n", loans[i].studentId, loans[i].returnDate);
            found = 1;
        }
    }

    if (!found) {
        printf("No loans found for the book.\n");
    }
}
