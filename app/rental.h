#ifndef RENTAL_H
#define RENTAL_H
#include <stdio.h>
#include <string.h>
#include "../struct/models.h"
#include "vehicle.h"
#include "customer.h"
#include "payment.h"

#define MAX 100

struct rental rentals[MAX];
int rental_count = 0;
int last_rental_id = 0;;
void load_rentals() {
    FILE *fp;
    struct rental r;

    rental_count = 0;
    last_rental_id = 0;

    fp = fopen("data/rentals.dat", "rb");
    if (fp == NULL) return;

    while (fread(&r, sizeof(r), 1, fp)) {
        rental_count++;
        if (r.id > last_rental_id) {
            last_rental_id = r.id;
        }
    }
    fclose(fp);
}
void create_rental() {
    FILE *fp;
    struct rental r;
    struct payment p;
    struct vehicle *v;
    int c_index;

    if (rental_count >= MAX) {
        printf("Rental limit reached!\n");
        return;
    }

    r.id = last_rental_id + 1;

    printf("Enter Vehicle ID: ");
    scanf("%d", &r.vehicle_id);

    v = find_vehicle(r.vehicle_id);

    if (v == NULL || v->available == 0) {
        printf("Vehicle not available!\n");
        return;
    }

    printf("Enter Customer ID: ");
    scanf("%d", &r.customer_id);

    c_index = find_customer(r.customer_id);
    if (c_index == -1) {
        printf("Customer not found!\n");
        return;
    }

    printf("Enter Number of Days: ");
    scanf("%d", &r.days);

    printf("Enter Date (dd-mm-yyyy): ");
    scanf("%s", r.date);

    r.total_cost = r.days * v->price_per_day;
    printf("Total Cost: %d\n", r.total_cost);
    int payment_amount;
    printf("Payment Amount: \n");
    scanf("%d", &payment_amount);

    r.status = RENT_ACTIVE;


    fp = fopen("data/rentals.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }
    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);
    if (payment_amount > 0)
    {
       payment(r, payment_amount);
    }
    
    update_vehicle_status(r.vehicle_id, 0); 
    int due_amount = r.total_cost - payment_amount;
    printf("Rental created! ID: %d Total: %d\n", r.id, due_amount);
}
void show_rentals() {
    FILE *fp;
    struct rental r;

    fp = fopen("data/rentals.dat", "rb");
    if (fp == NULL) {
        printf("No rentals available!\n");
        return;
    }
    printf("\n--- Rental List ---\n");
    printf("--- Total Rentals: %d ---\n", rental_count);

    while (fread(&r, sizeof(r), 1, fp)) {
        printf("ID: %d\n", r.id);
        printf("Customer Name: %s\n", get_customer_name(r.customer_id));
        printf("Vehicle Name: %s\n", get_vehicle_name(r.vehicle_id));
        printf("Days: %d\n", r.days);
        printf("Total Cost: %d\n", r.total_cost);
        printf("Date: %s\n", r.date);
        printf("Status: %s\n", r.status == RENT_ACTIVE ? "Active" : (r.status == RENT_RETURNED ? "Returned" : "Cancelled"));
        printf("-------------------\n");
    }

    fclose(fp);
}


void return_vehicle() {
    FILE *fp;
    struct rental r;
    int rental_id;
    int found = 0;

    printf("Enter Rental ID: ");
    scanf("%d", &rental_id);

    fp = fopen("data/rentals.dat", "rb");
    if (fp == NULL) {
        printf("No rentals available!\n");
        return;
    }
    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == rental_id) {
            int paid = get_total_paid(rental_id);
            if (paid < r.total_cost) {
                printf("Payment pending! Please clear dues before returning.Total Due: %d\n", r.total_cost - paid);
                fclose(fp);
                return;
            }
            update_vehicle_status(r.vehicle_id, 1);
            printf("Vehicle returned successfully!\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Rental not found!\n");
    }
}
#endif
