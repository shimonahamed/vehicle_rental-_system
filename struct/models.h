#ifndef MODELS_H
#define MODELS_H
#define RENT_ACTIVE 1
#define RENT_RETURNED 2
#define RENT_CANCELLED 3

// Vehicle Information
struct users
{
    int id;
    char name[50];
    unsigned long password_hash;
    char phone[15];    
    char email[50];
    int status;    
};
// Vehicle Information
struct vehicle
{
    int id;
    char name[50];
    char type[20];    
    int price_per_day;   
    int available;    
    int status; 
};

// Customer Information
struct customer
{
    int id;
    char name[50];
    char phone[20];
    char email[50];
    char address[150];
    int status; 
};

// Rental Information
struct rental
{
    int id;
    int vehicle_id;
    int customer_id;
    int days;
    int daily_rate;
    int total_cost;
    char date[20];
    int status;

};

// Payment Information
enum payment_status {
    UNPAID,
    PARTIAL,
    PAID
};
struct payment
{
    int id;
    int rental_id;
    int customer_id;
    int vehicle_id;
    int total_amount;
    int payable_amount;
    int paid_amount;
    int due_amount;

    enum payment_status status;
};

#endif