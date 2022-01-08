#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
                //TODO: makeInvoice();
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
