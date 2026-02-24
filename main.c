#include <stdio.h>
#include <string.h>
#include "models.h"

// array and counters
struct vehicle vehicles[100];
int vehicle_count = 0;

struct customer customers[100];
int customer_count = 0;

struct rental rentals[100];
int rental_count = 0;

// Add Vehicle
void add_vehicle() {
    struct vehicle v;

    printf("Enter Vehicle ID: ");
    scanf("%d", &v.id);
    printf("Enter Vehicle Name: ");
    scanf("%s", v.name);
    printf("Enter Vehicle Type: ");
    scanf("%s", v.type);
    printf("Enter Price per Day: ");
    scanf("%d", &v.price_per_day);

    v.available = 1;

    vehicles[vehicle_count] = v;
    vehicle_count++;

    printf("Vehicle added successfully!\n");
}

// Show Vehicles
void show_vehicles() {
    if (vehicle_count == 0) {
        printf("No vehicles available!\n");
        return;
    }

    printf("\n--- Vehicle List ---\n");
    for (int i = 0; i < vehicle_count; i++) {
        printf("ID: %d\n", vehicles[i].id);
        printf("Name: %s\n", vehicles[i].name);
        printf("Type: %s\n", vehicles[i].type);
        printf("Price per Day: %d\n", vehicles[i].price_per_day);
        printf("Status: %s\n", vehicles[i].available ? "Available" : "Rented");
        printf("-------------------\n");
    }
}

// Add Customer
void add_customer() {
    struct customer c;

    printf("Enter Customer ID: ");
    scanf("%d", &c.id);
    printf("Enter Customer Name: ");
    scanf("%s", c.name);
    printf("Enter Customer Phone: ");
    scanf("%s", c.phone);

    customers[customer_count] = c;
    customer_count++;

    printf("Customer added successfully!\n");
}

// Find Vehicle Index by ID
int find_vehicle(int id) {
    for (int i = 0; i < vehicle_count; i++) {
        if (vehicles[i].id == id)
            return i;
    }
    return -1;
}

// Find Customer Index by ID
int find_customer(int id) {
    for (int i = 0; i < customer_count; i++) {
        if (customers[i].id == id)
            return i;
    }
    return -1;
}

// Create Rental
void create_rental() {
    struct rental r;
    int v_index, c_index;

    printf("Enter Rental ID: ");
    scanf("%d", &r.id);

    printf("Enter Vehicle ID: ");
    scanf("%d", &r.vehicle_id);
    v_index = find_vehicle(r.vehicle_id);

    if (v_index == -1) {
        printf("Vehicle not found!\n");
        return;
    }

    if (vehicles[v_index].available == 0) {
        printf("Vehicle already rented!\n");
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

    r.total_cost = r.days * vehicles[v_index].price_per_day;
    rentals[rental_count] = r;
    rental_count++;

    // Update vehicle availability
    vehicles[v_index].available = 0;

    printf("Rental created successfully! Total Cost: %d\n", r.total_cost);
}

// Return Vehicle
void return_vehicle() {
    int rental_id, v_index;
    printf("Enter Rental ID: ");
    scanf("%d", &rental_id);

    for (int i = 0; i < rental_count; i++) {
        if (rentals[i].id == rental_id) {
            v_index = find_vehicle(rentals[i].vehicle_id);
            vehicles[v_index].available = 1;
            printf("Vehicle returned successfully!\n");
            return;
        }
    }

    printf("Rental not found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Vehicle Rental System ---\n");
        printf("1. Add Vehicle\n");
        printf("2. Show Vehicles\n");
        printf("3. Add Customer\n");
        printf("4. Create Rental\n");
        printf("5. Return Vehicle\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
                create_rental();
                break;
            case 5:
                return_vehicle();
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