#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Product {
    char * PID, * name;
    int pricePerItem;
};

struct Product getDetails(char * PID){
    struct Product product;
    char line[1024];
    FILE * products;
    products = fopen("Products.csv", "r");
    while (fgets(line, 1024, products)) {
        char * token = strtok(line, ", ");
        product.PID = token;
        token = strtok(NULL, ", ");
        product.name = token;
        token = strtok(line, ", ");
        product.pricePerItem = atoi(token);
        if (!strcmp(PID, product.PID)) {
            return product;
        }
    }
    product.pricePerItem = 0;
    product.name = "NOT FOUND";
    return product;
}

int addItem(FILE *bill){
    printf("Enter PID:");
    char PID[5];
    scanf("%s", PID);
    printf("Quantity:");
    int quantity;
    scanf("%d", &quantity);
    struct Product prodDetails = getDetails(PID);
    if (prodDetails.pricePerItem){
        int price = prodDetails.pricePerItem * quantity;
        fprintf(bill, "\n%s\t%s\t%d\t\t\t%d\t\t\t\t%d", PID, prodDetails.name, quantity, prodDetails.pricePerItem, price);
        return price;
    }
    printf("%s is not a valid PID", PID);
    return 0;
}

void printInvoice(FILE * bill, int total){
    fprintf(bill, "\n\nTotal\t%d", total);
    fprintf(bill, "\n==================END OF INVOICE==================");
    fclose(bill);
}

void makeInvoice(){
    bool isPrinted = false;
    FILE * bill;
    int total = 0;
    bill = fopen("bill.txt", "w");
    fprintf(bill, "\t\t\t\tINVOICE\nPID\t\tName\tQuantity\tPricePerItem\tPrice");
    while (!isPrinted) {
        printf("\n[1] Add Item\n[2] Print Bill\n[0] Cancel Bill\nChoose an option:");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 0:
                return;
            case 1:
                total += addItem(bill);
                break;
            case 2:
                printInvoice(bill, total);
                isPrinted = true;
                break;
            default:
                printf("\nInvalid Option");
                break;
        }
    }
}

int addProduct(){
    FILE * products;
    char line[1024];
    products = fopen("Products.csv", "r");
    struct Product product;
    printf("\nEnter PID:");
    scanf("%s", product.PID);
    while (fgets(line, 1024, products)) {
        char * token = strtok(line, ", ");
        char * PID = token;
        token = strtok(NULL, ", ");
        product.name = token;
        token = strtok(line, ", ");
        product.pricePerItem = atoi(token);
        if (!strcmp(PID, product.PID)) {
            return 0;
        }
    }
    fclose(products);
    printf("Enter Product Name:");
    scanf("%s", product.name);
    printf("Enter Price Per Item:");
    scanf("%d", &product.pricePerItem);
    products = fopen("Products.csv", "a");
    fprintf(products, "\n%s, %s, %d", product.PID, product.name, product.pricePerItem);
    fclose(products);
    return 1;
}

int main() {
    printf("\t\tBilling System");
    while (true) {
        printf("\n[1] Make Invoice\n[2] Add New Product\n[0] Exit\nChoose an option:");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 0:
                exit(0);
            case 1:
                makeInvoice();
                break;
            case 2:
                if (addProduct()) printf("Product Added Successfully");
                else printf("Unsuccessful, PID might already exists");
                break;
            default:
                printf("Invalid Option");
                break;
        }
    }
}
