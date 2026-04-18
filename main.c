//===== Vehicle Rental System in C=====

#include <stdio.h>
#include <string.h>
#include "struct/models.h"
#include "app/user.h"
#include "app/vehicle.h"
#include "app/customer.h"
#include "app/rental.h"
#include "app/payment.h"



int main() {
    int choice;
    while (1) {
        printf("\n--- Welcome ---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (login()) {
                while (1) {
                    lastUserId();
                    lastVehicleId();
                    lastCustomerId();
                    load_rentals();
                    loadPayment();
                    printf("\n--- Vehicle Rental System ---\n");
                    printf("1. Add Vehicle\n");
                    printf("2. Show Vehicles\n");
                    printf("3. Add Customer\n");
                    printf("4. Show Customer\n");
                    printf("5. Create Rental\n");
                    printf("6. Return Vehicle\n");
                    printf("7. Show Rentals\n");
                    printf("8. Add User\n");
                    printf("9. Show Users\n");
                    printf("10. Change Password\n");
                    printf("11. Update User Status\n");
                    printf("12. Create Payment\n");
                    printf("13. Show Payments\n");
                    printf("14. Payment Details\n");
                    printf("0. Logout\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: add_vehicle(); break;
                        case 2: show_vehicles(); break;
                        case 3: add_customer(); break;
                        case 4: show_customers(); break;
                        case 5: create_rental(); break;
                        case 6: return_vehicle(); break;
                        case 7: show_rentals(); break;
                        case 8: add_user(); break;
                        case 9: show_users(); break;
                        case 10: change_password(); break;
                        case 11: update_user_status(); break;
                        case 12: create_payment(); break;
                        case 13: show_payments(); break;
                        case 14: payment_details(); break;
                        case 0:
                            printf("Logged out!\n");
                            break;
                        default:
                            printf("Invalid choice!\n");
                    }

                    if (choice == 0) break;
                }
            }
        } else if (choice == 2) {
            add_user();
        }else if (choice == 0) {
            printf("Exiting...\n");
            return 0;
        }else {
            printf("Invalid choice!\n");
        }
    }
}