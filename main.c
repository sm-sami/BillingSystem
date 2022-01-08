#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int addItem(FILE *bill){
    printf("Enter PID:");
    char PID[5];
    scanf("%s", PID);
    printf("Quantity:");
    int quantity;
    scanf("%d", &quantity);
    int price = 50 * quantity;
    fprintf(bill, "\n%s\t%d\t\t\t%d", PID, quantity, price);
    return price;
}

void printInvoice(FILE *bill, int total){
    fprintf(bill, "\nTotal\t\t\t\t%d", total);
    fclose(bill);
}

void makeInvoice(){
    bool toPrint = false;
    FILE *bill;
    int total = 0;
    bill = fopen("bill.txt", "w");
    fprintf(bill, "\t\tINVOICE\nPID\t\tQuantity\tPrice");
    while (!toPrint) {
        printf("\n[1] Add Item\n[2] Print Bill\nChoose an option:");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 0:
                return;
            case 1:
                total += addItem(bill);
                break;
            case 2:
                toPrint = true;
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
