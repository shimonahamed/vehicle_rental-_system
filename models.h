#ifndef MODELS_H
#define MODELS_H

// User Information
struct user
{
    char username[50];
    char password[50];
};

// Vehicle Information
struct vehicle
{
    int id;
    char name[50];
    char type[20];
    int price_per_day;
    int available;
};

// Customer Information
struct customer
{
    int id;
    char name[50];
    char phone[20];
};

// Rental Information
struct rental
{
    int id;
    int vehicle_id;
    int customer_id;
    int days;
    int total_cost;
};

// Payment Information
struct payment
{
    int id;
    int rental_id;
    int amount;
    char status[20]; // paid / due
};

#endif