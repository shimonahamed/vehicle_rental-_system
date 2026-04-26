#ifndef VEHICLE_H
#define VEHICLE_H
#include <stdio.h>
#include <string.h>
#include "../struct/models.h"
#define MAX 100

struct vehicle vehicles[MAX];
int vehicle_count = 0;
int last_vehicle_id = 0;

void lastVehicleId() {
    FILE *fp;
    struct vehicle v;
    vehicle_count = 0;     
    last_vehicle_id = 0;  

    fp = fopen("data/vehicles.dat", "rb");
    if (fp == NULL) return;

    while (fread(&v, sizeof(v), 1, fp)) {
          if (v.id > last_vehicle_id) {
                last_vehicle_id = v.id;
          }
        vehicle_count++;
    }

    fclose(fp);
}
void add_vehicle() {
    FILE *fp;
    struct vehicle v;
   if (vehicle_count >= MAX) {
        printf("Vehicle list full!\n");
        return;
    }
    printf("--- Add New Vehicle ---\n");

    v.id = last_vehicle_id + 1;

    printf("Enter Vehicle Name: ");
    scanf(" %[^\n]", v.name);

    printf("Enter Vehicle Type: ");
    scanf("%s", v.type);

    printf("Enter Price per Day: ");
    scanf("%d", &v.price_per_day);

    v.available = 1;
    v.status = 1;
    v.user_id[0] = user_id;
    strcpy(v.created_at, current_date);

    fp = fopen("data/vehicles.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fwrite(&v, sizeof(v), 1, fp);
    fclose(fp);
    last_vehicle_id = v.id;  
    vehicle_count++; 

    printf("Vehicle added successfully! ID: %d\n", v.id);
}

void show_vehicles() {

    FILE *fp;
    struct vehicle v;
    fp = fopen("data/vehicles.dat", "rb");
    if (fp == NULL) {
        printf("No vehicles available!\n");
        return;
    }
    printf("\n--- Vehicle List ---\n");
    printf("--- Total Vehicles: %d ---\n", vehicle_count);
    while (fread(&v,sizeof(v),1,fp)) {
        if (current_role == USER ? v.user_id == user_id : 1){
            printf("ID: %d\n", v.id);
            printf("Name: %s\n", v.name);
            printf("Type: %s\n", v.type);
            printf("Price per Day: %d\n", v.price_per_day);
            printf("Available Status: %s\n", v.available ? "Available" : "Rented");
            printf("Status: %s\n", v.status ? "Active" : "Inactive");
            printf("User Name: %s\n", get_user_name(v.user_id));
            printf("Created At: %s\n", v.created_at);
            printf("-------------------\n");
        }

    }
    fclose(fp);
}

struct vehicle* find_vehicle(int id) {
    FILE *fp;
    static struct vehicle v;

    fp = fopen("data/vehicles.dat", "rb");
    if (fp == NULL) return NULL;

    while (fread(&v, sizeof(v), 1, fp)) {
        if (v.id == id) {
            fclose(fp);
            return &v;
        }
    }

    fclose(fp);
    return NULL;
}

void update_vehicle_status(int id, int status) {
    FILE *fp, *temp;
    struct vehicle v;
    int found = 0;

    fp = fopen("data/vehicles.dat", "rb");
    temp = fopen("data/temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    while (fread(&v, sizeof(v), 1, fp)) {

        if (v.id == id) {
            v.available = status;
            found = 1;
        }

        fwrite(&v, sizeof(v), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data/vehicles.dat");
    rename("data/temp.dat", "data/vehicles.dat");

    if (!found)
        printf("Vehicle not found!\n");
}
char* get_vehicle_name(int id) {
    FILE *fp;
    static struct vehicle v;

    fp = fopen("data/vehicles.dat", "rb");
    if (fp == NULL) return "Unknown";

    while (fread(&v, sizeof(v), 1, fp)) {
        if (v.id == id) {
            fclose(fp);
            return v.name;
        }
    }

    fclose(fp);
    return "Unknown";
}
#endif
