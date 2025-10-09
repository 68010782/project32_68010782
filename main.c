#include "donation.h"
#include <stdio.h>

int main() {
    int result = loadinfo("DonationInfo.csv");
    printf("%d records loaded from file.\n", result);
    menu();
    printf("Exiting program!\n");
    return 0;
}
