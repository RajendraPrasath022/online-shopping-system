#include <stdio.h>
#include <string.h>
#include "product.h"

#define PRODUCT_FILE "products.dat"

void addProduct() {
    FILE *file = fopen(PRODUCT_FILE, "ab");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    Product product;
    printf("Enter Product ID: ");
    scanf("%d", &product.id);
    printf("Enter Product Name: ");
    scanf(" %[^\n]", product.name);
    printf("Enter Quantity: ");
    scanf("%d", &product.quantity);
    printf("Enter Price: ");
    scanf("%f", &product.price);

    fwrite(&product, sizeof(Product), 1, file);
    fclose(file);

    printf("Product added successfully!\n");
}

void viewProducts() {
    FILE *file = fopen(PRODUCT_FILE, "rb");
    if (!file) {
        printf("No products found.\n");
        return;
    }

    Product product;
    printf("\nAvailable Products:\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");

    while (fread(&product, sizeof(Product), 1, file)) {
        printf("%d\t%s\t\t%d\t\t%.2f\n", product.id, product.name, product.quantity, product.price);
    }

    fclose(file);
}
