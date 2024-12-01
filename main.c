#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "sales.h"

void displayMenu() {
    printf("\n==== Online Shopping System ====\n");
    printf("1. Add Product\n");
    printf("2. View Products\n");
    printf("3. Buy Product\n");
    printf("4. View Sales Report\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                buyProduct();
                break;
            case 4:
                viewSales();
                break;
            case 5:
                printf("Exiting the program. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
