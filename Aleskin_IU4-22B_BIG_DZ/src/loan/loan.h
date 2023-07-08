#ifndef LOAN_H
#define LOAN_H

typedef struct {
    char isbn[14];
    char studentId[10];
    char returnDate[11];
} Loan;

void loadLoans();
void loanBook(const char* isbn, const char* studentId);
void returnBook(const char* isbn, const char* studentId);
void displayStudentLoans(const char* studentId);
void displayBookLoans(const char* isbn);

#endif /* LOAN_H */
