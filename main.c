#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int getPrice(char * PID){
    char line[1024];
    struct Product {
        char * PID;
        int price;
    } product;
    FILE * products;
    products = fopen("Products.csv", "r");
    while (fgets(line, 1024, products)) {
        char * token = strtok(line, ", ");
        product.PID = token;
        token = strtok(NULL, ", ");
        product.price = atoi(token);
        if (!strcmp(PID, product.PID)) {
            return product.price;
        }
    }
    return 0;
}

int addItem(FILE *bill){
    printf("Enter PID:");
    char PID[5];
    scanf("%s", PID);
    printf("Quantity:");
    int quantity;
    scanf("%d", &quantity);
    int pricePerItem = getPrice(PID);
    if (pricePerItem){
        int price = pricePerItem * quantity;
        fprintf(bill, "\n%s\t%d\t\t\t%d\t\t%d", PID, quantity, pricePerItem, price);
        return price;
    }
    printf("%s is not a valid PID", PID);
    return 0;
}

void printInvoice(FILE * bill, int total){
    fprintf(bill, "\n\nTotal\t%d", total);
    fclose(bill);
}

void makeInvoice(){
    bool isPrinted = false;
    FILE * bill;
    int total = 0;
    bill = fopen("bill.txt", "w");
    fprintf(bill, "\t\tINVOICE\nPID\t\tQuantity\tPricePerItem\tPrice");
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
                isPrinted = true;
                printInvoice(bill, total);
                break;
            default:
                printf("\nInvalid Option");
                break;
        }
    }
}

int main() {
    printf("\t\tBilling System");
    while (true) {
        printf("\n[1] Make Invoice\n[2] Add New Products\n[0] Exit\nChoose an option:");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 0:
                exit(0);
            case 1:
                makeInvoice();
                break;
            case 2:
                //TODO: addProduct;
                break;
            default:
                printf("Invalid Option");
                break;
        }
    }
}
