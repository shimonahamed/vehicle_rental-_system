//===== Vehicle Rental System in C=====

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct/models.h"
#include "app/user.h"
#include "app/vehicle.h"
#include "app/customer.h"
#include "app/rental.h"
#include "app/payment.h"
#include "app/date_handler.h"



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
                 time_t t;
                struct tm *tm_info;
                time(&t);
                tm_info = localtime(&t);

                sprintf(current_date, "%02d-%02d-%04d",
                        tm_info->tm_mday,
                        tm_info->tm_mon + 1,
                        tm_info->tm_year + 1900);


                lastUserId();
                lastVehicleId();
                lastCustomerId();
                load_rentals();
                loadPayment();

                while (1) {

                    printf("\n--- Vehicle Rental System ---\n");

                    if (current_role == USER) {
                        printf("1. Show Vehicles\n");
                        printf("2. Add Customer\n");
                        printf("3. Show Customer\n");
                        printf("4. Create Rental\n");
                        printf("5. Return Vehicle\n");
                        printf("6. Show Rentals\n");
                        printf("7. Create Payment\n");
                        printf("8. Show Payments\n");
                        printf("9. Payment Details\n");
                    } else {
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
                    }

                    printf("0. Logout\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);

                    if (current_role == USER &&
                        (choice == 1 && 0 || choice == 8 || choice == 9 || choice == 10 || choice == 11)) {
                        printf("Access Denied!\n");
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            if (current_role == ADMIN) add_vehicle();
                            else show_vehicles();
                            break;

                        case 2:
                            if (current_role == ADMIN) show_vehicles();
                            else add_customer();
                            break;

                        case 3:
                            if (current_role == ADMIN) add_customer();
                            else show_customers();
                            break;

                        case 4:
                            if (current_role == ADMIN) show_customers();
                            else create_rental();
                            break;

                        case 5: create_rental(); break;
                        case 6: return_vehicle(); break;
                        case 7: show_rentals(); break;

                        case 8:
                            if (current_role == ADMIN) add_user();
                            else create_payment();
                            break;

                        case 9:
                            if (current_role == ADMIN) show_users();
                            else show_payments();
                            break;

                        case 10:
                            if (current_role == ADMIN) change_password();
                            else printf("Invalid choice!\n");
                            break;

                        case 11:
                            if (current_role == ADMIN) update_user_status();
                            else printf("Invalid choice!\n");
                            break;

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
        } 
        else if (choice == 2) {
            add_user();
        } 
        else if (choice == 0) {
            printf("Exiting...\n");
            return 0;
        } 
        else {
            printf("Invalid choice!\n");
        }
    }
}