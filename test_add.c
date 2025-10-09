#include <stdio.h>
#include <string.h>
#include <assert.h>

struct Donation{
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;

int add(char *name, float amount, int year, int month, int day, char *purpose){
    if (record_count >= 100){
        return 0;
    }
    if (strlen(name) == 0){
        return 0;
    }
    if (amount < 0){
        return 0;
    }
    if (year <= 0 || month > 12 || month <= 0 || day <= 0 || day > 31){
        return 0;
    }
    if (strlen(purpose) == 0){
        return 0;
    }

    strcpy(donations[record_count].DonorName, name);
    donations[record_count].DonationAmount = amount;
    donations[record_count].Year = year;
    donations[record_count].Month = month;
    donations[record_count].Day = day;
    strcpy(donations[record_count].Purpose, purpose);

    record_count++;
    return 1;
}

int main(){
    printf("\n===== Testing add() function =====\n");
    //happy path
    assert(add("Johny Suh",127.75,2025,12,11, "Education") == 1);

    //edge cases
    assert(add("F", 0,1,1,1,"T") == 1);
    assert(add("NameXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 9999999.99, 9999, 12,31,"B") == 1);

    //error cases
    assert(add("",100,2024,1,1, "Education") == 0);
    assert(add("Johny Suh", -10, 2024,1,1, "Education") == 0);
    assert(add("Johny Suh", 20,-2024,13,32,"Education") == 0);
    assert(add("Johny Suh", 20, 2024,1,1,"") == 0);

    printf("All add() tests passed!\n");
    return 0;
}
