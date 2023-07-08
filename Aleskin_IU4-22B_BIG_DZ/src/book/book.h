#ifndef BOOK_H
#define BOOK_H

typedef struct {
    char isbn[14];
    char authors[100];
    char title[100];
    int totalQuantity;
    int availableQuantity;
} Book;

void loadBooks();
void addBook(const Book* book);
void removeBook(const char* isbn);
void viewBook(const char* isbn);
void displayAllBooks();
void editBook(const char* isbn);
void loanBook(const char* isbn, const char* studentId);
void returnBook(const char* isbn, const char* studentId);
void handleBookManagement();

#endif /* BOOK_H */
