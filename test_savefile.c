#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Donation {
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;

void savefile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("CANNOT OPEN FILE!!!\n");
        return;
    }

    fprintf(file, "DonorName,DonationAmount,DonationDate,Purpose\n");
    for (int i = 0; i < record_count; i++){
        fprintf(file, "%s,%.2f,%04d-%02d-%02d,%s\n",
            donations[i].DonorName,
            donations[i].DonationAmount,
            donations[i].Year,
            donations[i].Month,
            donations[i].Day,
            donations[i].Purpose);
    }
    fflush(file);
    fclose(file);
}

int main() {
    printf("\n===== Testing savefile() Function =====\n");
    //happy
    record_count = 2;
    strcpy(donations[0].DonorName, "Johny Suh");
    donations[0].DonationAmount = 127.00;
    donations[0].Year = 2026; donations[0].Month = 8; donations[0].Day = 21;
    strcpy(donations[0].Purpose, "Education");

    strcpy(donations[1].DonorName, "Jun Kim");
    donations[1].DonationAmount = 25.50;
    donations[1].Year = 2024; donations[1].Month = 4; donations[1].Day = 12;
    strcpy(donations[1].Purpose, "Healthcare");

    savefile("DonationInfo_test.csv");
    printf("CSV file saved successfully!\n");

    //ตรวจสอบ
    FILE *file = fopen("DonationInfo_test.csv", "r");
    assert(file != NULL);
    char line[200];
    //ตรวจ header
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;
    assert(strcmp(line, "DonorName,DonationAmount,DonationDate,Purpose") == 0);
    //ตรวจข้อมูล
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;
    assert(strcmp(line, "Johny Suh,127.00,2026-08-21,Education") == 0);
    // ตรวจข้อมูล2
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;
    assert(strcmp(line, "Jun Kim,25.50,2024-04-12,Healthcare") == 0);

    fclose(file);

    //edge
    record_count = 0;
    savefile("DonationInfo_test.csv");
    file = fopen("DonationInfo_test.csv", "r");
    assert(file != NULL);
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;
    assert(strcmp(line, "DonorName,DonationAmount,DonationDate,Purpose") == 0);

    assert(fgets(line, sizeof(line), file) == NULL);
    fclose(file);

    printf("All savefile() tests passed!\n");
    return 0;
}
