#include <assert.h>
#include <stdio.h>
#include <string.h>

struct Donation{
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;

int search_index(const char keyword[]) {
    for (int i = 0; i < record_count; i++) {
        if (strstr(donations[i].DonorName, keyword) != NULL ||
            strstr(donations[i].Purpose, keyword) != NULL)
            return i;
    }
    return -1;
}

void add_test_donation(const char* name, float amount, int year, int month, int day, const char* purpose) {
    strcpy(donations[record_count].DonorName, name);
    donations[record_count].DonationAmount = amount;
    donations[record_count].Year = year;
    donations[record_count].Month = month;
    donations[record_count].Day = day;
    strcpy(donations[record_count].Purpose, purpose);
    record_count++;
}

int main() {
    printf("\n===== Testing search_index() Function =====\n");
    //ข้อมูลเทส
    add_test_donation("Johny Suh",127.75,2025,12,11, "Education");
    add_test_donation("David Kim", 1212.25, 2024,12,1, "Healthcare");
    add_test_donation("Kevin Yoon", 789.75,2025, 2, 6, "Charity");
    //happy
    assert(search_index("Johny Suh") == 0);
    assert(search_index("Healthcare") == 1);
    assert(search_index("Charity") == 2);
    //edge
    assert(search_index("John") == 0);
    assert(search_index("Kim") == 1);
    assert(search_index("david") == -1);
    assert(search_index("") == 0);
    //error
    assert(search_index("Nonexistent") == -1);
    assert(search_index("Random") == -1);

    printf("All search_index() tests passed!\n");
    return 0;
}
