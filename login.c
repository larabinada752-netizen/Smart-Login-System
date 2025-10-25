#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define DATA_FILE "users.txt"

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User users[MAX_USERS];
int userCount = 0;

// Function declarations
void loadUsers();
void saveUsers();
void registerUser();
void loginUser();
void changePassword();
int findUser(char username[]);

int main() {
    int choice;
    loadUsers();

    while (1) {
        printf("\n===== Smart Login System =====\n");
        printf("1. Register New User\n");
        printf("2. Login\n");
        printf("3. Change Password\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                changePassword();
                break;
            case 4:
                saveUsers();
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void loadUsers() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) return;

    while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) == 2) {
        userCount++;
    }

    fclose(file);
}

void saveUsers() {
    FILE *file = fopen(DATA_FILE, "w");
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }
    fclose(file);
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter new username: ");
    scanf("%s", username);

    if (findUser(username) != -1) {
        printf("Username already exists!\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", password);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    saveUsers();
    printf("User registered successfully!\n");
}

void loginUser() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int index = findUser(username);
    if (index == -1) {
        printf("User not found!\n");
        return;
    }

    if (strcmp(users[index].password, password) == 0) {
        printf("Login successful! Welcome, %s.\n", username);
    } else {
        printf("Incorrect password!\n");
    }
}

void changePassword() {
    char username[USERNAME_LEN];
    char oldPass[PASSWORD_LEN];
    char newPass[PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    int index = findUser(username);
    if (index == -1) {
        printf("User not found!\n");
        return;
    }

    printf("Enter old password: ");
    scanf("%s", oldPass);

    if (strcmp(users[index].password, oldPass) != 0) {
        printf("Incorrect old password!\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", newPass);
    strcpy(users[index].password, newPass);
    saveUsers();

    printf("Password changed successfully!\n");
}

int findUser(char username[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0)
            return i;
    }
    return -1;
}
