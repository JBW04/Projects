#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CARS 100 // MAX NUMBER OF CARS
#define MAX_STR 50 // MAX LENGTH OF STRINGS
#define DISCOUNT 0.10 // 10% DISCOUNT

struct Car {
    char model[MAX_STR];
    int year;
    float price;
};

void addCar(struct Car cars[], int *count);
void viewCars(struct Car cars[], int count);
void searchCar(struct Car cars[], int count);
void sortCars(struct Car cars[], int count);
void buyCar(struct Car cars[], int *count);
void deleteCar(struct Car cars[], int *count);
void saveToFile(struct Car cars[], int count);
void loadFromFile(struct Car cars[], int *count);
float applyDiscount(float price, int age, int hasNASCard);

int main(void) {
    struct Car cars[MAX_CARS];
    int carCount = 0;
    int choice;

    do {
        printf("\n---- Car Sales Management ----\n");
        printf("1. Add Car\n");
        printf("2. View All Cars\n");
        printf("3. Search Car by Model\n");
        printf("4. Sort Cars by Price\n");
        printf("5. Buy a Car (Customer)\n");
        printf("6. Save Inventory To File\n");
        printf("7. Load Inventory From File\n");
        printf("8. Delete Car\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCar(cars, &carCount);
                break;
            case 2:
                viewCars(cars, carCount);
                break;
            case 3:
                searchCar(cars, carCount);
                break;
            case 4:
                sortCars(cars, carCount);
                printf("\nCars sorted by price.\n");
                break;
            case 5:
                buyCar(cars, &carCount);
                break;
            case 6:
                saveToFile(cars, carCount);
                printf("\nInventory saved to file.\n");
                break;
            case 7:
                loadFromFile(cars, &carCount);
                break;
            case 8:
                deleteCar(cars, &carCount);
                break;
            case 9:
                printf("\nExiting Program...\n");
                break;
            default:
                printf("\nInvalid choice, Try Again.\n");
        }

    } while (choice != 9);

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Clear the buffer
}

// This function is to add a car to the inventory
void addCar(struct Car cars[], int *count) {
    if (*count >= MAX_CARS) {
        printf("\nInventory is full you cannot add more cars.\n");
        return;
    }

    struct Car newCar;

    printf("\nEnter car model: ");
    if(scanf("%s", newCar.model) != 1) {
        printf("\ninvalid input for car model.\n");
        clearInputBuffer();
        return;
    }

    printf("\nEnter car year: ");
    if(scanf("%d", &newCar.year) != 1) {
        printf("\ninvalid input for car year.\n");
        clearInputBuffer();
        return;
    }
    printf("\nEnter car price: ");
    if(scanf("%f", &newCar.price) != 1) {
        printf("\ninvalid input for car price.\n");
        clearInputBuffer();
        return;
    }

    //Add the new car to the main inventory structure
    cars[*count] = newCar;
    (*count)++;
    printf("\nCar added successfully\n");

}


// This function views the inventory of the cars that are on sale
void viewCars(struct Car cars[], int count) {
    if (count == 0) {
        printf("\nNo cars in inventory\n");
        return;
    }

    printf("\n--- Car Inventory ---\n");
    for(int i = 0; i < count; i++) {
        printf("Car %d: Model: %s, Year: %d, Price: %0.2f\n", i + 1, cars[i].model, cars[i].year, cars[i].price);
    }
}

void searchCar(struct Car cars[], int count) {
    if (count == 0) {
        printf("\nNo cars in inventory");
        return;
    }

    char searchModel[MAX_STR];
    printf("\nEnter car model to search for: ");
    scanf("%s", searchModel);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(cars[i].model, searchModel) == 0) {
            printf("\nCar found: Model: %s, Year: %d, Price: %0.2f\n", cars[i].model, cars[i].year, cars[i].price);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nCar model '%s' not found in the inventory\n", searchModel);
        return;
    }


}

void sortCars(struct Car cars[], int count) {
    struct Car temp;

    if(count == 0) {
        printf("\nNo cars in inventory\n");
        return;
    }

    // this is a bubble sort algorithm where in the array index it bascially compares the 0 index with the 1 index
    // and if its > or < that determains if it should be swapped, and it does this multiple times till its in
    // highest to lowest order, then we make that temp structure inventory == to the cars structure
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (cars[j].price > cars[j + 1].price) {
                // this swap the cars
                temp = cars[j];
                cars[j] = cars[j+1];
                cars[j + 1] = temp;
            }
        }
    }
}

void buyCar(struct Car cars[], int *count) {
    if (*count == 0) {
        printf("\nNo cars available for purchase.\n");
        return;
    }

    int carIndex;
    int age, hasNASCard;

    viewCars(cars, *count);
    printf("Enter the car number you wish to buy: ");
    if(scanf("%d", &carIndex) != 1) {
        printf("\ninvalid input for car model.\n");
        clearInputBuffer();
        return;
    }

    if (carIndex < 1 || carIndex > *count) {
        printf("\nInvalid car selection.\n");
        return;
    }

    carIndex--;

    // this grabs the users age and checks if user has nascard
    printf("\nEnter your age: ");
    if(scanf("%d", &age) != 1) {
        printf("\ninvalid input for age.\n");
        clearInputBuffer();
        return;
    }
    printf("\nDo you have a NAS card? (1 for Yes, 0 for No): ");
    if(scanf("%d", &hasNASCard) != 1) {
        printf("\ninvalid input for NAS card.\n");
        clearInputBuffer();
        return;
    }

    //this applies the discount if it applies
    //cars[index].price gives the price of the car that's been selected from the inventory
    //age and hasNasCard is from the user input which gives the applyDiscount function the correct information to check the discount conditions
    float finalPrice = applyDiscount(cars[carIndex].price, age, hasNASCard);

    printf("The final price of the car after discount (if applicable) is: %.2f GBP\n", finalPrice);
    printf("\nDo you wish to proceed with the purchase? (1 for Yes, 0 for No): ");
    int confirmPurchase;
    scanf("%d", &confirmPurchase);

    if (confirmPurchase == 1) {
        printf("\nCongratulations! You have purchased the %s, for %0.2f GBP.\n", cars[carIndex].model, finalPrice);

        for (int i = carIndex; i < *count - 1; i++) {
            cars[i] = cars[i + 1];
        }
        (*count)--;
        printf("\nCar removed from inventory.\n");
    }else {
        printf("\nPurchase cancelled.\n");
    }
}

float applyDiscount(float price, int age, int hasNASCard) {
    if ((age > 18 && age <= 25) || hasNASCard == 1) {
        // applies the 10% discount if the conditions are met
        return price * 0.90;
    }
    // keeps original price if the conditions are not met
    return price;
}

void deleteCar(struct Car cars[], int *count) {
    if (*count == 0) {
        printf("\nNo cars in inventory to delete.\n");
        return;
    }

    char deleteModel[MAX_STR];
    printf("\nEnter the car model to delete: ");
    if (scanf("%s", deleteModel) != 1) {
        printf("Invalid input for car model.\n");
        clearInputBuffer();
        return;  // Return to menu on invalid input
    }

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(cars[i].model, deleteModel) == 0) {
            // Shift the cars in the array to delete the car
            for (int j = i; j < *count - 1; j++) {
                cars[j] = cars[j + 1];
            }
            (*count)--;  // Decrease the car count
            printf("\nCar model '%s' deleted from inventory.\n", deleteModel);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nCar model '%s' not found in the inventory.\n", deleteModel);
    }
}

void saveToFile(struct Car cars[], int count) {
    FILE *file = fopen("cars.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    // Write each car's details to the file
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %.2f\n", cars[i].model, cars[i].year, cars[i].price);
    }

    fclose(file);  // Close the file after writing
    printf("Inventory saved to file successfully.\n");
}

void loadFromFile(struct Car cars[], int *count) {
    FILE *file = fopen("cars.txt", "r");
    if (file == NULL) {
        printf("\nNo existing inventory file found. Starting with an empty inventory.\n");
        return;  // If the file doesn't exist, start with an empty inventory
    }
    *count = 0;
    while(fscanf(file, "%s %d %f", cars[*count].model, &cars[*count].year, &cars[*count].price) == 3) {
        (*count)++;
        if (*count >= MAX_CARS) {
            printf("\nMax car limit is reached");
            break;
        }
    }
    fclose(file);
    printf("\nInventory loaded from file successfully.\n");
}