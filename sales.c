#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "sales.h"

#define PRODUCT_FILE "products.dat"
#define SALES_FILE "sales.dat"

typedef struct {
    int productId;
    int quantity;
    float totalPrice;
} Sale;

void buyProduct() {
    int id, quantity;
    FILE *productFile = fopen(PRODUCT_FILE, "rb+");
    FILE *salesFile = fopen(SALES_FILE, "ab");

    if (!productFile || !salesFile) {
        perror("Unable to open file");
        return;
    }

    printf("Enter Product ID to buy: ");
    scanf("%d", &id);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    Product product;
    int found = 0;

    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (product.id == id && product.quantity >= quantity) {
            found = 1;
            product.quantity -= quantity;

            fseek(productFile, -sizeof(Product), SEEK_CUR);
            fwrite(&product, sizeof(Product), 1, productFile);

            Sale sale = {id, quantity, quantity * product.price};
            fwrite(&sale, sizeof(Sale), 1, salesFile);

            printf("Purchase successful! Total: %.2f\n", sale.totalPrice);
            break;
        }
    }

    if (!found) {
        printf("Product not found or insufficient stock.\n");
    }

    fclose(productFile);
    fclose(salesFile);
}

void viewSales() {
    FILE *file = fopen(SALES_FILE, "rb");
    if (!file) {
        printf("No sales found.\n");
        return;
    }

    Sale sale;
    printf("\nSales Report:\n");
    printf("Product ID\tQuantity\tTotal Price\n");
    printf("-------------------------------------------------\n");

    while (fread(&sale, sizeof(Sale), 1, file)) {
        printf("%d\t\t%d\t\t%.2f\n", sale.productId, sale.quantity, sale.totalPrice);
    }

    fclose(file);
}
