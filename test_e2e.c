#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "donation.h"
#define TEST_CSV "DonationInfo_teste2e.csv"

void create_test_csv() {
    FILE *file = fopen(TEST_CSV, "w");
    fprintf(file, "DonorName,DonationAmount,DonationDate,Purpose\n");
    fprintf(file, "Johny Suh,127.00,2024-05-10,Charity\n");
    fprintf(file, "Kevin Yoon,1212.50,2026-08-12,Education\n");
    fprintf(file, "Jun Kim,789.25,2025-07-01,Healthcare\n");
    fclose(file);
}

void test_end_to_end() {
    printf("\n===== E2E TEST START =====\n");

    //สร้างไฟล์
    create_test_csv();

    //โหลดข้อมูลจากไฟล์
    int count = loadinfo(TEST_CSV);
    assert(count == 3);
    assert(strcmp(donations[0].DonorName, "Johny Suh") == 0);
    assert(strcmp(donations[1].DonorName, "Kevin Yoon") == 0);
    assert(strcmp(donations[2].DonorName, "Jun Kim") == 0);
    printf("- loadinfo() passed\n");

    //เพิ่มข้อมูล
    strcpy(donations[record_count].DonorName, "Anton Lee");
    donations[record_count].DonationAmount = 3250;
    donations[record_count].Year = 2025;
    donations[record_count].Month = 3;
    donations[record_count].Day = 20;
    strcpy(donations[record_count].Purpose, "Disaster Relief");
    record_count++;
    savefile(TEST_CSV);
    printf("- add() & savefile() passed!\n");

    //ตรวจสอบว่าเพิ่มข้อมูลแล้ว
    loadinfo(TEST_CSV);
    assert(record_count == 4);
    assert(strcmp(donations[3].DonorName, "Anton Lee") == 0);
    printf("- Data persisted correctly after add!\n");

    //search หา Jun Kim
    int found = -1;
    for (int i = 0; i < record_count; i++) {
        if (strcmp(donations[i].DonorName, "Jun Kim") == 0)
            found = i;
    }
    assert(found != -1);
    printf("- search() simulation passed!\n");

    //อัปเดตข้อมูล Jun Kim
    strcpy(donations[found].Purpose, "Religion");
    savefile(TEST_CSV);
    loadinfo(TEST_CSV);
    int updated = -1;
    for (int i = 0; i < record_count; i++) {
        if (strcmp(donations[i].DonorName, "Jun Kim") == 0)
            updated = i;
    }
    assert(strcmp(donations[updated].Purpose, "Religion") == 0);
    printf("- update() simulation passed!\n");

    //ลบข้อมูล Johny Suh
    int del_index = -1;
    for (int i = 0; i < record_count; i++) {
        if (strcmp(donations[i].DonorName, "Johny Suh") == 0) {
            del_index = i;
            break;
        }
    }
    for (int i = del_index; i < record_count - 1; i++) {
        donations[i] = donations[i + 1];
    }
    record_count--;
    savefile(TEST_CSV);
    loadinfo(TEST_CSV);

    int still_exists = 0;
    for (int i = 0; i < record_count; i++) {
        if (strcmp(donations[i].DonorName, "Johny Suh") == 0)
            still_exists = 1;
    }
    assert(still_exists == 0);
    printf("- delete() simulation passed!\n");

    printf("===== ALL E2E TESTS PASSED =====\n");
}

int main() {
    test_end_to_end();
    return 0;
}
