#include <stdio.h>
#include <string.h>
#include "models.h"

// user information
struct user current_user;
struct user users[100];
int user_count = 0;

// array and counters
struct vehicle vehicles[100];
int vehicle_count = 0;

struct customer customers[100];
int customer_count = 0;

struct rental rentals[100];
int rental_count = 0;

// ID generators
int next_vehicle_id = 1;
int next_customer_id = 1;
int next_rental_id = 1;

// Save Users to File
void save_users()
{
    FILE *fp = fopen("./users.dat", "wb");

    if (fp == NULL)
    {
        printf("File open error!\n");
        return;
    }

    // count save
    fwrite(&user_count, sizeof(int), 1, fp);

    // users array save
    fwrite(users, sizeof(struct user), user_count, fp);

    fclose(fp);
}

// Load Users from File
void load_users()
{
    FILE *fp = fopen("users.dat", "rb");

    if (fp == NULL)
    {
        user_count = 0;
        return;
    }

    // count read
    fread(&user_count, sizeof(int), 1, fp);

    // users array read
    fread(users, sizeof(struct user), user_count, fp);

    fclose(fp);
}

// Create User

void create_user()
{
    struct user u;

    printf("Enter New Username: ");
    scanf("%s", u.username);

    printf("Enter New Password: ");
    scanf("%s", u.password);

    users[user_count] = u;
    user_count++;

    save_users();

    printf("User created successfully!\n");
}

// Save Vehicles to File
void save_vehicles()
{
    FILE *fp = fopen("./vehicles.dat", "wb");

    if (fp == NULL)
    {
        printf("File open error!\n");
        return;
    }

    // count save
    fwrite(&vehicle_count, sizeof(int), 1, fp);

    // array save
    fwrite(vehicles, sizeof(struct vehicle), vehicle_count, fp);

    fclose(fp);
}

// Load Vehicles from File
void load_vehicles()
{
    FILE *fp = fopen("vehicles.dat", "rb");

    if (fp == NULL)
    {
        vehicle_count = 0;
        return;
    }

    // count read
    fread(&vehicle_count, sizeof(int), 1, fp);

    // array read
    fread(vehicles, sizeof(struct vehicle), vehicle_count, fp);

    fclose(fp);
}

// Add Vehicle
void add_vehicle()
{
    struct vehicle v;

    v.id = next_vehicle_id;
    next_vehicle_id++;

    // printf("Enter Vehicle ID: ");
    // scanf("%d", &v.id);
    printf("Enter Vehicle Name: ");
    scanf("%s", v.name);
    printf("Enter Vehicle Type: ");
    scanf("%s", v.type);
    printf("Enter Price per Day: ");
    scanf("%d", &v.price_per_day);

    v.available = 1;

    vehicles[vehicle_count] = v;
    vehicle_count++;

    save_vehicles();

    printf("Vehicle added successfully!\n");
}

// Show Vehicles
void show_vehicles()
{
    if (vehicle_count == 0)
    {
        printf("No vehicles available!\n");
        return;
    }

    printf("\n--- Vehicle List ---\n");
    for (int i = 0; i < vehicle_count; i++)
    {
        printf("ID: %d\n", vehicles[i].id);
        printf("Name: %s\n", vehicles[i].name);
        printf("Type: %s\n", vehicles[i].type);
        printf("Price per Day: %d\n", vehicles[i].price_per_day);
        printf("Status: %s\n", vehicles[i].available ? "Available" : "Rented");
        printf("-------------------\n");
    }
}

// Add Customer
void add_customer()
{
    struct customer c;

    c.id = next_customer_id;
    next_customer_id++;

    // printf("Enter Customer ID: ");
    // scanf("%d", &c.id);
    printf("Enter Customer Name: ");
    scanf("%s", c.name);
    printf("Enter Customer Phone: ");
    scanf("%s", c.phone);

    customers[customer_count] = c;
    customer_count++;

    printf("Customer added successfully!\n");
}

// Show Customers
void show_customer()
{
    if (customer_count == 0)
    {
        printf("No customers available!\n");
        return;
    }

    printf("\n--- Customer List ---\n");

    for (int i = 0; i < customer_count; i++)
    {
        printf("ID: %d\n", customers[i].id);
        printf("Name: %s\n", customers[i].name);
        printf("Phone: %s\n", customers[i].phone);
        printf("-------------------\n");
    }
}

// Find Vehicle Index by ID
int find_vehicle(int id)
{
    for (int i = 0; i < vehicle_count; i++)
    {
        if (vehicles[i].id == id)
            return i;
    }
    return -1;
}

// Find Customer Index by ID
int find_customer(int id)
{
    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].id == id)
            return i;
    }
    return -1;
}

// Create Rental
void create_rental()
{
    struct rental r;
    int v_index, c_index;

    r.id = next_rental_id;
    next_rental_id++;

    // printf("Enter Rental ID: ");
    // scanf("%d", &r.id);

    printf("Enter Vehicle ID: ");
    scanf("%d", &r.vehicle_id);
    v_index = find_vehicle(r.vehicle_id);

    if (v_index == -1)
    {
        printf("Vehicle not found!\n");
        return;
    }

    if (vehicles[v_index].available == 0)
    {
        printf("Vehicle already rented!\n");
        return;
    }

    printf("Enter Customer ID: ");
    scanf("%d", &r.customer_id);
    c_index = find_customer(r.customer_id);

    if (c_index == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("Enter Number of Days: ");
    scanf("%d", &r.days);

    r.total_cost = r.days * vehicles[v_index].price_per_day;
    rentals[rental_count] = r;
    rental_count++;

    // Update vehicle availability
    vehicles[v_index].available = 0;

    printf("Rental created successfully! Total Cost: %d\n", r.total_cost);
}

// Show Rentals
void show_rentals()
{
    if (rental_count == 0)
    {
        printf("No rentals found!\n");
        return;
    }

    printf("\n--- Rental List ---\n");

    for (int i = 0; i < rental_count; i++)
    {
        printf("Rental ID   : %d\n", rentals[i].id);
        printf("Vehicle ID  : %d\n", rentals[i].vehicle_id);
        printf("Customer ID : %d\n", rentals[i].customer_id);
        printf("Days        : %d\n", rentals[i].days);
        printf("Total Cost  : %d\n", rentals[i].total_cost);
        printf("----------------------\n");
    }
}

// Return Vehicle
void return_vehicle()
{
    int rental_id, v_index;
    printf("Enter Rental ID: ");
    scanf("%d", &rental_id);

    for (int i = 0; i < rental_count; i++)
    {
        if (rentals[i].id == rental_id)
        {
            v_index = find_vehicle(rentals[i].vehicle_id);
            vehicles[v_index].available = 1;
            printf("Vehicle returned successfully!\n");
            return;
        }
    }

    printf("Rental not found!\n");
}

// User Login
int login_user()
{
    char username[50], password[50];

    printf("===== LOGIN =====\n");

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
        {
            current_user = users[i];
            printf("Login Successful!\n");
            return 1;
        }
    }

    printf("Invalid Login!\n");
    return 0;
}

int main()
{
    // load vehicles from file
    load_vehicles();
    load_users();

    if (user_count == 0)
    {
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "1234");
        user_count = 1;
        save_users();
    }

    //  ONLY ONE LOGIN
    if (!login_user())
    {
        return 0;
    }

    int choice;

    while (1)
    {
        printf("\n--- Vehicle Rental System ---\n");
        printf("1. Add Vehicle\n");
        printf("2. Show Vehicles\n");
        printf("3. Add Customer\n");
        printf("4. Show Customer\n");
        printf("5. Create Rental\n");
        printf("6. Show Rentals\n");
        printf("7. Return Vehicle\n");
        printf("8. Create User\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_vehicle();
            break;
        case 2:
            show_vehicles();
            break;
        case 3:
            add_customer();
            break;
        case 4:
            show_customer();
            break;
        case 5:
            create_rental();
            break;
        case 6:
            show_rentals();
            break;
        case 7:
            return_vehicle();
            break;

        case 8:
            if (strcmp(current_user.username, "admin") == 0)
            {
                create_user();
            }
            else
            {
                printf("Only admin can create user!\n");
            }
            break;
        case 0:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}