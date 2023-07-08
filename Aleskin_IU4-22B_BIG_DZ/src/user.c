#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define USERS_FILE_PATH "users.csv"

int authenticateUser(const char* username, const char* password) {
    FILE* usersFile = fopen(USERS_FILE_PATH, "r");
    if (usersFile == NULL) {
        printf("Failed to open the users file.\n");
        return 0;
    }

    char line[256];
    int isAuthenticated = 0;

    while (fgets(line, sizeof(line), usersFile) != NULL) {
        char* token = strtok(line, ",");
        char fileUsername[50];
        strcpy(fileUsername, token);

        token = strtok(NULL, ",");
        char filePassword[50];
        strcpy(filePassword, token);

        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            isAuthenticated = 1;
            break;
        }
    }

    fclose(usersFile);

    return isAuthenticated;
}
