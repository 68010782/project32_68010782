#include <assert.h>
#include <stdio.h>
#include <string.h>

struct Donation {
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;
//search
int search_index(const char keyword[]) {
    for (int i = 0; i < record_count; i++) {
        if (strstr(donations[i].DonorName, keyword) != NULL ||
            strstr(donations[i].Purpose, keyword) != NULL)
            return i;
    }
    return -1;
}

void add_test(const char* name, float amount, int year, int month, int day, const char* purpose) {
    strcpy(donations[record_count].DonorName, name);
    donations[record_count].DonationAmount = amount;
    donations[record_count].Year = year;
    donations[record_count].Month = month;
    donations[record_count].Day = day;
    strcpy(donations[record_count].Purpose, purpose);
    record_count++;
}

int update_index(int index, const char* newName, float newAmount, int newYear, int newMonth, int newDay, const char* newPurpose) {
    if (index < 0 || index >= record_count){
        return 0;
    }
    if (newName){
        strcpy(donations[index].DonorName, newName);
    }
    if (newAmount >= 0){
        donations[index].DonationAmount = newAmount;
    }
    if (newYear > 0){
        donations[index].Year = newYear;
    }
    if (newMonth > 0 && newMonth <= 12){
        donations[index].Month = newMonth;
    }
    if (newDay > 0 && newDay <= 31){
        donations[index].Day = newDay;
    }
    if (newPurpose){
        strcpy(donations[index].Purpose, newPurpose);
    }
    return 1;
}

int main() {
    printf("\n===== Testing update_index() Function =====\n");
    //ข้อมูลเทส
    add_test("Johny Suh",127.75,2025,12,11, "Education");
    add_test("Kevin Yoon", 789.75,2025, 2, 6, "Charity");
    //happy
    int idx = search_index("Johny Suh");
    assert(idx == 0);
    assert(update_index(idx, "Johny Dev", 127.00,2026,12,15, "Charity") == 1);
    assert(strcmp(donations[0].DonorName, "Johny Dev") == 0);
    assert(donations[0].DonationAmount == 127.00);
    assert(donations[0].Year == 2026 && donations[0].Month == 12 && donations[0].Day == 15);
    assert(strcmp(donations[0].Purpose, "Charity") == 0);
    //edge อัพเดตบางค่า ค่าอินพุตที่ไม่ถูกต้องจะไม่อัพเดต
    assert(update_index(idx, NULL, 200.0, -1, 20, 35, NULL) == 1);
    assert(donations[0].DonationAmount == 200.0);
    assert(strcmp(donations[0].DonorName, "Johny Dev") == 0);
    //error
    assert(update_index(100, "Fake", 10.0, 2021, 1, 1, "Test") == 0);

    printf("All update_index() tests passed!\n");
    return 0;
}
