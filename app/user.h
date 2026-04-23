#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <string.h>
#include "../struct/models.h"
#define MAX 100

unsigned long hash_password(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 

    return hash;
}
struct users users[MAX];
int user_count = 0;
int last_user_id = 0;

void lastUserId() {
    FILE *fp;
    struct users u;
    last_user_id = 0; 
    user_count = 0;
    fp = fopen("data/users.dat", "rb");
    if (fp == NULL) {
        return;
    }
    while (fread(&u, sizeof(u), 1, fp)) {
      if (u.id > last_user_id) {
            last_user_id = u.id; // 🔥 max id track
        }
        user_count++;
    }
    fclose(fp);
}

void add_user() {
    struct users u;
    FILE *fp;
    char password[50];

    if (user_count >= MAX) {
        printf("User list full!\n");
        return;
    }
    if (current_role==ADMIN)
    {
    printf("--- Add New User ---\n");
    } else {
        printf("--- Registration ---\n");
    }
    
    u.id = last_user_id + 1;
    printf("Enter User Name: ");
    scanf(" %[^\n]", u.name);

    printf("Enter User Password: ");
    scanf("%s", password);
    u.password_hash = hash_password(password);

    printf("Enter User Phone: ");
    scanf("%s", u.phone);

    printf("Enter User Email: ");
    scanf("%s", u.email);
    u.status = 1;
      if (current_role == ADMIN) {
        printf("Enter Role (1=Admin, 2=User): ");
        scanf("%d", &u.role);
        if (u.role != 1 && u.role != 2) {
            printf("Invalid role! Defaulting to USER.\n");
            u.role = USER;
        }
    } else {
        u.role = USER;
    }

    fp = fopen("data/users.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }
    fwrite(&u, sizeof(u), 1, fp);
    fclose(fp);
    last_user_id = u.id;

    printf("User added successfully!\n");
}

void show_users() {
    FILE *fp;
    struct users u;

    fp = fopen("data/users.dat", "rb");
    if (fp == NULL) {
        printf("No users available!\n");
        return;
    }
    printf("\n--- User List ---\n");
    printf("--- Total Users: %d ---\n", user_count);

    while (fread(&u, sizeof(u), 1, fp)) {
        printf("ID: %d\n", u.id);
        printf("Name: %s\n", u.name);
        printf("Phone: %s\n", u.phone);
        printf("Email: %s\n", u.email);
        printf("Role: %s\n", u.role == ADMIN ? "Admin" : "User");

        printf("Status: %s\n", u.status ? "Active" : "Inactive");
        printf("-------------------\n");
    }

    fclose(fp);
}
void update_user_status() {
    FILE *fp, *temp;
    struct users u;
    int found = 0;
    fp = fopen("data/users.dat", "rb");
    temp = fopen("data/temp.dat", "wb");
    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }
    int id, status;
    printf("Enter User ID: ");
    scanf("%d", &id);
    printf("Enter New Status (1 for Active, 0 for Inactive): ");
    scanf("%d", &status);
    while (fread(&u, sizeof(u), 1, fp)) {
        if (u.id == id) {
            u.status = status;   
            found = 1;
        }
        fwrite(&u, sizeof(u), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data/users.dat");
    rename("data/temp.dat", "data/users.dat");

    if (found)
        printf("User status updated successfully!\n");
    else
        printf("User not found!\n");
}

int login() {
     FILE *fp = fopen("data/users.dat", "rb");
    struct users u;
    char username[50], password[50];
    unsigned long hash;

    if (fp == NULL) {
        printf("No users found!\n");
        return 0;
    }

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    hash = hash_password(password);

   while (fread(&u, sizeof(u), 1, fp)) {
        if (strcmp(u.name, username) == 0 && u.password_hash == hash) {
            if (u.status == 0) {
                printf("User is inactive!\n");
                fclose(fp);
                return 0;
            }
           
            current_role = u.role;

            printf("Login successful!\n");

            if(current_role == ADMIN)
                printf("Logged in as ADMIN\n");
            else
                printf("Logged in as USER\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid username or password!\n");
    return 0;
}
void change_password() {
    FILE *fp, *temp;
    struct users u;
    int found = 0;
    fp = fopen("data/users.dat", "rb");
    temp = fopen("data/temp.dat", "wb");
    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }
    int id;
    char new_password[50];
    printf("Enter User id: ");
    scanf("%d", &id);

    printf("Enter New Password: ");
    scanf("%s", new_password);
    unsigned long new_hash = hash_password(new_password);
    while (fread(&u, sizeof(u), 1, fp)) {
        if (u.id == id) {
            u.password_hash = new_hash;   
            found = 1;
        }
        fwrite(&u, sizeof(u), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data/users.dat");
    rename("data/temp.dat", "data/users.dat");

    if (found)
        printf("Password changed successfully!\n");
    else
        printf("User not found!\n");
}

#endif