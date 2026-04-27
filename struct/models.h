#ifndef MODELS_H
#define MODELS_H
#define RENT_ACTIVE 1
#define RENT_RETURNED 2
#define RENT_CANCELLED 3
#define ADMIN 1
#define USER 2

int current_role;
int user_id;
char current_date[20];
char current_time[20];

// char custom_date[20];
int diff_days;


// Vehicle Information
struct users
{
    int id;
    char name[50];
    unsigned long password_hash;
    char phone[15];    
    char email[50];
    int role;
    int status;    
};
struct vehicle
{
    int id;
    char name[50];
    char type[20];    
    int price_per_day;   
    int available;  
    int user_id;  
    char created_at[20];  
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
    int user_id;    
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
    char rental_date[20];
    char return_date[20];
    int user_id;    
    char created_at[20];
    int status;

};


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
    char payment_date[20];
    int user_id;    
    enum payment_status status;
};

#endif