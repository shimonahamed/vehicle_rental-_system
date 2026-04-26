#ifndef PAYMENT_H
#define PAYMENT_H
#include <stdio.h>
#include <string.h>
#include "../struct/models.h"
#include "rental.h"
#include "payment.h"

int last_payment_id = 0;

void loadPayment(){
     FILE *fp;
    struct payment p;

    last_payment_id = 0;

    fp = fopen("data/payments.dat", "rb");
    if (fp == NULL) return;

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id > last_payment_id) {
            last_payment_id = p.id;
        }
        
    }
    fclose(fp);
}

void payment(struct rental r, int payment_amount) {
    struct payment p;
        p.id = last_payment_id + 1;
        p.rental_id = r.id;
        p.customer_id = r.customer_id;
        p.vehicle_id = r.vehicle_id;
        p.total_amount = r.total_cost;
        p.payable_amount = r.total_cost;
        p.paid_amount = payment_amount;
        p.due_amount = r.total_cost - payment_amount;

        if (p.due_amount == 0) {
            p.status = PAID;
        } else if (p.due_amount < r.total_cost) {
            p.status = PARTIAL;
        } else {
            p.status = UNPAID;
        }

        FILE *pfp = fopen("data/payments.dat", "ab");
        if (pfp != NULL) {
            fwrite(&p, sizeof(p), 1, pfp);
            fclose(pfp);
            last_payment_id = p.id;  
        }
}
int get_total_paid(int rental_id) {
    FILE *fp;
    struct payment p;
    int total_paid = 0;

    fp = fopen("data/payments.dat", "rb");
    if (fp == NULL) return 0;

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.rental_id == rental_id) {   
            total_paid += p.paid_amount;  
        }
    }

    fclose(fp);
    return total_paid;
}
struct rental* find_rental(int id) {
    FILE *fp;
    static struct rental r;

    fp = fopen("data/rentals.dat", "rb");
    if (fp == NULL) return NULL;

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            fclose(fp);
            return &r;
        }
    }

    fclose(fp);
    return NULL;
}
void create_payment() {
    FILE *fp;
    struct payment p;
    struct rental *r;   

    printf("Enter Rental ID: ");
    scanf("%d", &p.rental_id);

    r = find_rental(p.rental_id); 
    if (r == NULL) {
        printf("Rental not found!\n");
        return;
    }
    int already_paid = get_total_paid(r->id);

  int remaining = r->total_cost - already_paid;
    printf("Total Payable Amount: %d\n", r->total_cost);
    printf("Remaining Due: %d\n", remaining);

    printf("Enter Payment Amount: ");
    scanf("%d", &p.paid_amount);

    if (p.paid_amount > remaining)
    {
        printf("Payment amount exceeds the due amount!\n");
        return;
    }
    p.id = last_payment_id + 1;
    p.rental_id = r->id;
    p.customer_id = r->customer_id;
    p.vehicle_id = r->vehicle_id;
    p.total_amount = r->total_cost;
    p.payable_amount = r->total_cost;
    p.due_amount = p.payable_amount - p.paid_amount;
    strcpy(p.payment_date, current_date);
    p.user_id[0] = user_id;

    if (p.due_amount == 0) {
        p.status = PAID;
    } else if (p.paid_amount > 0) {
        p.status = PARTIAL;
    } else {
        p.status = UNPAID;
    }

    fp = fopen("data/payments.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    last_payment_id = p.id;  

    printf("Payment saved! ID: %d\n", p.id);
}

void show_payments() {
    FILE *fp;
    struct payment p;
    fp = fopen("data/payments.dat", "rb");
    if (fp == NULL) {
        printf("No payments available!\n");
        return;
    }
    printf("\n--- Payment List ---\n");
    while (fread(&p, sizeof(p), 1, fp)) {
    if (current_role == USER ? p.user_id == user_id : 1){
        printf(" ID: %d\n", p.id);
        printf("Rental ID: %d\n", p.rental_id);
        printf("Customer ID: %d\n", p.customer_id);
        printf("Vehicle ID: %d\n", p.vehicle_id);
        printf("Payable Amount: %d\n", p.payable_amount);
        printf("Paid Amount: %d\n", p.paid_amount);
        printf("Due Amount: %d\n", p.due_amount);
        printf("Status: %s\n", p.status == PAID ? "PAID" : (p.status == PARTIAL ? "PARTIAL" : "UNPAID"));
        printf("User Name: %s\n", get_user_name(p.user_id));
        printf("-------------------\n");
    }
    }
    fclose(fp);
}

void payment_details() {
    FILE *fp;
    struct rental r;
    int rental_id;

    printf("Enter Rental ID: ");
    scanf("%d", &rental_id);

    fp = fopen("data/rentals.dat", "rb");
    if (fp == NULL) {
        printf("No payments available!\n");
        return;
    }

    printf("\n--- Payment Details ---\n");

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == rental_id) {    
            int paid = get_total_paid(rental_id);
            printf("Rental ID: %d\n", r.id);
            printf("Customer Name: %s\n", get_customer_name(r.customer_id));
            printf("Vehicle Name: %s\n", get_vehicle_name(r.vehicle_id));
            printf("Payable Amount: %d\n", r.total_cost);
            printf("Paid Amount: %d\n", paid);
            printf("Due Amount: %d\n", r.total_cost - paid);
             printf("Status: %s\n", paid >= r.total_cost ? "PAID" : (paid > 0 ? "PARTIAL" : "UNPAID"));

            printf("-------------------\n");
        }
    }

    fclose(fp);
}

#endif