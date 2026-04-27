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
    int main_choice, menu_choice;

    while (1) {
        printf("\n--- Welcome ---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &main_choice);

        if (main_choice == 1) {

            if (login()) {

                time_t t;
                struct tm *tm_info;
                time(&t);
                tm_info = localtime(&t);
                sprintf(current_date, "%02d-%02d-%04d",
                        tm_info->tm_mday,
                        tm_info->tm_mon + 1,
                        tm_info->tm_year + 1900);
                sprintf(current_time, "%02d:%02d:%02d",
                        tm_info->tm_hour,
                        tm_info->tm_min,
                        tm_info->tm_sec);

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
                        printf("3. Show Customers\n");
                        printf("4. Create Rental\n");
                        printf("5. Cancel Rental\n");
                        printf("6. Return Vehicle\n");
                        printf("7. Show Rentals\n");
                        printf("8. Create Payment\n");
                        printf("9. Payment Details\n");
                        printf("0. Logout\n");
                    } else {
                        printf("1. Add Vehicle\n");
                        printf("2. Show Vehicles\n");
                        printf("3. Add Customer\n");
                        printf("4. Show Customers\n");
                        printf("5. Create Rental\n");
                        printf("6. Cancel Rental\n");
                        printf("7. Return Vehicle\n");
                        printf("8. Show Rentals\n");
                        printf("9. Add User\n");
                        printf("10. Show Users\n");
                        printf("11. Change Password\n");
                        printf("12. Update User Status\n");
                        printf("13. Create Payment\n");
                        printf("14. Show Payments\n");
                        printf("15. Payment Details\n");
                        printf("0. Logout\n");
                    }

                    printf("Enter your choice: ");
                    scanf("%d", &menu_choice);   

                    if (current_role == USER) {
                        switch (menu_choice) {
                            case 1: show_vehicles(); break;
                            case 2: add_customer(); break;
                            case 3: show_customers(); break;
                            case 4: create_rental(); break;
                            case 5: cancel_rental(); break;
                            case 6: return_vehicle(); break;
                            case 7: show_rentals(); break;
                            case 8: create_payment(); break;
                            case 9: payment_details(); break;

                            case 0:
                                printf("Logged out!\n");
                                break;

                            default:
                                printf("Invalid choice!\n");
                        }
                    } else {
                        switch (menu_choice) {
                            case 1: add_vehicle(); break;
                            case 2: show_vehicles(); break;
                            case 3: add_customer(); break;
                            case 4: show_customers(); break;
                            case 5: create_rental(); break;
                            case 6: cancel_rental(); break;
                            case 7: return_vehicle(); break;
                            case 8: show_rentals(); break;
                            case 9: add_user(); break;
                            case 10: show_users(); break;
                            case 11: change_password(); break;
                            case 12: update_user_status(); break;
                            case 13: create_payment(); break;
                            case 14: show_payments(); break;
                            case 15: payment_details(); break;

                            case 0:
                                printf("Logged out!\n");
                                break;

                            default:
                                printf("Invalid choice!\n");
                        }
                    }

                    if (menu_choice == 0) break;  // ✅ exit dashboard
                }

            } else {
                printf("Login failed!\n");
            }

        } else if (main_choice == 2) {
            add_user();

        } else if (main_choice == 0) {
            printf("Exiting...\n");
            break;

        } else {
            printf("Invalid choice!\n");
        }
    }
}