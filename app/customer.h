#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>
#include <string.h>
#include "../struct/models.h"
#define MAX 100

struct customer customer[MAX];
int customer_count = 0;
int last_customer_id = 0;

void lastCustomerId() {
    FILE *fp;
    struct customer c;
    last_customer_id = 0; 
    customer_count = 0;
    fp = fopen("data/customers.dat", "rb");
    if (fp == NULL) {
        return;
    }
    while (fread(&c, sizeof(c), 1, fp)) {
        if (c.id > last_customer_id) {
            last_customer_id = c.id;
        }
        if (current_role == ADMIN || c.user_id == user_id ){
            customer_count++;
          
        }

    }
    fclose(fp);
}

void add_customer() {
    FILE *fp;
    struct customer c;
    if (customer_count >= MAX) {
        printf("Customer list full!\n");
        return;
    }
    printf("--- Add New Customer ---\n");

    c.id = last_customer_id + 1;

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Customer Phone: ");
    scanf("%s", c.phone);
    printf("Enter Customer Email: ");
    scanf("%s", c.email);
    printf("Enter Customer Address: ");
    scanf(" %[^\n]", c.address);
    c.status = 1;
    c.user_id = user_id;
    fp = fopen("data/customers.dat", "ab");
    if (fp == NULL) {
        printf("Error adding customer!\n");
        return;
    }
    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);
    last_customer_id = c.id;   
    customer_count++; 
    printf("Customer added successfully!______ID: %d\n", c.id);
}

void show_customers() {
    FILE *fp;
    struct customer c;

    fp = fopen("data/customers.dat", "rb");
    if (fp == NULL) {
        printf("No customers available!\n");
        return;
    }

    printf("\n================== CUSTOMER LIST ==================\n");

    printf("%-5s %-20s %-15s %-25s %-20s %-10s %-15s\n",
           "ID", "Name", "Phone", "Email", "Address", "Status","User");

    printf("------------------------------------------------------------------------------------------\n");

    while (fread(&c, sizeof(c), 1, fp)) {

        if (current_role == USER ? c.user_id == user_id : 1) {

            printf("%-5d %-20s %-15s %-25s %-20s %-10s %-15s\n",
                   c.id,
                   c.name,
                   c.phone,
                   c.email,
                   c.address,
                   c.status ? "Active" : "Inactive",
                    get_user_name(c.user_id)


            );
        }
    }

    printf("====================================================\n");

    fclose(fp);
}

int find_customer(int id) {
      FILE *fp;
    struct customer c;

    fp = fopen("data/customers.dat", "rb");
    if (fp == NULL) {
        return -1;
    }

    while (fread(&c, sizeof(c), 1, fp)) {
        int allowed = (current_role == ADMIN || c.user_id == user_id);

        if (allowed && c.id == id) {
            fclose(fp);
            return 1;  
        }

    }
    fclose(fp);
    return -1; 
}
char* get_customer_name(int id) {
    FILE *fp;
    static struct customer c;

    fp = fopen("data/customers.dat", "rb");
    if (fp == NULL) return "Unknown";

    while (fread(&c, sizeof(c), 1, fp)) {
        if (c.id == id) {
            fclose(fp);
            return c.name;
        }
    }

    fclose(fp);
    return "Unknown";
}

#endif