#ifndef RENTAL_H
#define RENTAL_H
#include <stdio.h>
#include <string.h>
#include "../struct/models.h"
#include "vehicle.h"
#include "customer.h"
#include "payment.h"
#include "date_handler.h"
#include "user.h"

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
        if (r.id > last_rental_id) {
            last_rental_id = r.id;
        }
        if (current_role == ADMIN || r.user_id == user_id ){
            rental_count++;
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
    printf("--- Add New Rental ---\n");

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

        time_t t;
        time(&t); 

        printf("Rental Date (dd-mm-yyyy): %s\n", current_date);

        strcpy(r.created_at, current_time);
        strcpy(r.rental_date, current_date);
        time_t return_time = t + (r.days * 24 * 60 * 60);
        struct tm *return_tm = localtime(&return_time);
        char custom_date[20];
         date_handler(r.days, NULL, custom_date);
       
        strcpy(r.return_date, custom_date);
        printf("Return Date (dd-mm-yyyy): %s\n", r.return_date);

    r.total_cost = r.days * v->price_per_day;
    printf("Total Cost: %d\n", r.total_cost);
    int payment_amount;
    printf("Payment Amount: \n");
    scanf("%d", &payment_amount);

    r.status = RENT_ACTIVE;
    r.user_id = user_id;

    fp = fopen("data/rentals.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }
    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);
        last_rental_id = r.id;   
    if (payment_amount > 0)
    {
       payment(r, payment_amount);
    }
    
    update_vehicle_status(r.vehicle_id, 0); 
    int due_amount = r.total_cost - payment_amount;
    printf("Rental created! ID: %d Total Due: %d\n", r.id, due_amount);
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
    // printf("--- Total Rentals: %d ---\n", rental_count);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (current_role == ADMIN || r.user_id == user_id ){
        printf("ID: %d\n", r.id);
        printf("Customer Name: %s\n", get_customer_name(r.customer_id));
        printf("Vehicle ID: %d\n", r.vehicle_id);
        printf("Vehicle Name: %s\n", get_vehicle_name(r.vehicle_id));
        printf("Days: %d\n", r.days);
        printf("Total Cost: %d\n", r.total_cost);
        printf("Rental Date: %s\n", r.rental_date);
        printf("Return Date: %s\n", r.return_date);
        printf("Create Time: %s\n", r.created_at);
        printf("Status: %s\n", r.status == RENT_ACTIVE ? "Active" : (r.status == RENT_RETURNED ? "Returned" : "Cancelled"));
        printf("User Name: %s\n", get_user_name(r.user_id));
        printf("-------------------\n");
        }
    }

    fclose(fp);
}


void return_vehicle() {
    FILE *fp;
    struct rental r;
    int rental_id ,vehicle_id;
    int found = 0;

    printf("Enter Rental ID: ");
    scanf("%d", &rental_id);
    printf("Enter Vehicle ID: ");
    scanf("%d", &vehicle_id);

    fp = fopen("data/rentals.dat", "rb");
    if (fp == NULL) {
        printf("No rentals available!\n");
        return;
    }
    while (fread(&r, sizeof(r), 1, fp)) {
        int allowed = (current_role == ADMIN || r.user_id == user_id);
        if (allowed && r.id == rental_id && r.vehicle_id == vehicle_id) {
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

void cancel_rental() {
    FILE *fp, *temp;
    struct rental r;
    int rental_id, vehicle_id;
    int found = 0;

    printf("Enter Rental ID: ");
    scanf("%d", &rental_id);
    printf("Enter Vehicle ID: ");
    scanf("%d", &vehicle_id);

     fp = fopen("data/rentals.dat", "rb");
    temp = fopen("data/temp.dat", "wb");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    while (fread(&r, sizeof(r), 1, fp)) {

        int is_target = (r.id == rental_id && r.vehicle_id == vehicle_id);
        int allowed = (current_role == ADMIN || r.user_id == user_id);

        if (is_target && allowed) {

            int h1, m1, s1;
            int h2, m2, s2;

            sscanf(r.created_at, "%d:%d:%d", &h1, &m1, &s1);
            sscanf(current_time, "%d:%d:%d", &h2, &m2, &s2);

            int t1 = h1 * 3600 + m1 * 60 + s1;
            int t2 = h2 * 3600 + m2 * 60 + s2;

            if (t2 < t1) {
                t2 += 24 * 3600;
            }

            double diff_hours = (t2 - t1) / 3600.0;
            if (diff_hours > 6) {
                printf("Cancellation period expired!\n");
            } else {
                r.status = RENT_CANCELLED;
                found = 1;
            }
        }
         fwrite(&r, sizeof(r), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data/rentals.dat");
    rename("data/temp.dat", "data/rentals.dat");
    if (!found) {
        printf("Rental not found!\n");
    }else if (found) {
                 update_vehicle_status(r.vehicle_id, 1);
                printf("Rental cancelled successfully!\n");
    }
}


#endif
