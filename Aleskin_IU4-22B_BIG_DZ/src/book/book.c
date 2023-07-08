#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

#define BOOKS_FILE_PATH "books.csv"

Book* books = NULL;
int numBooks = 0;

struct Book books[MAX_BOOKS];

void loadBooks() {
    FILE* booksFile = fopen(BOOKS_FILE_PATH, "r");
    if (booksFile == NULL) {
        printf("Failed to open the books file.\n");
        return;
    }

    char line[256];
    int bookCount = 0;

    while (fgets(line, sizeof(line), booksFile) != NULL) {
        Book book;
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d",
               book.isbn, book.authors, book.title, &book.totalQuantity, &book.availableQuantity);

        books = (Book*)realloc(books, (bookCount + 1) * sizeof(Book));
        books[bookCount] = book;
        bookCount++;
    }

    numBooks = bookCount;

    fclose(booksFile);
}

void addBook(const Book* book) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, book->isbn) == 0) {
            printf("A book with the same ISBN already exists.\n");
            return;
        }
    }

    books = (Book*)realloc(books, (numBooks + 1) * sizeof(Book));
    books[numBooks] = *book;
    numBooks++;

    printf("Book added successfully.\n");
}

void removeBook(const char* isbn) {
    int index = -1;

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    for (int i = index; i < numBooks - 1; i++) {
        books[i] = books[i + 1];
    }

    numBooks--;

    printf("Book removed successfully.\n");
}

void viewBook(const char* isbn) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            printf("ISBN: %s\n", books[i].isbn);
            printf("Authors: %s\n", books[i].authors);
            printf("Title: %s\n", books[i].title);
            printf("Total Quantity: %d\n", books[i].totalQuantity);
            printf("Available Quantity: %d\n", books[i].availableQuantity);
            return;
        }
    }

    printf("Book not found.\n");
}

void displayAllBooks() {
    printf("All Books:\n");
    printf("ISBN\tAuthors\t\tTitle\t\tTotal Quantity\tAvailable Quantity\n");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < numBooks; i++) {
        printf("%s\t%s\t%s\t%d\t\t%d\n", books[i].isbn, books[i].authors, books[i].title,
               books[i].totalQuantity, books[i].availableQuantity);
    }
}

void editBook(const char* isbn) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            printf("Enter new authors: ");
            scanf("%s", books[i].authors);

            printf("Enter new title: ");
            scanf("%s", books[i].title);

            printf("Enter new total quantity: ");
            scanf("%d", &books[i].totalQuantity);

            books[i].availableQuantity = books[i].totalQuantity;

            printf("Book information updated successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

void loanBook(const char* isbn, const char* studentId) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].availableQuantity > 0) {
                books[i].availableQuantity--;
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
