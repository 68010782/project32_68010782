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

int loadinfo(){
    FILE *file = fopen("DonationInfo_test.csv", "r"); //ไฟล์ไม่มีอยู่จริง
    if (file == NULL){
        printf("CANNOT OPEN FILE!!!\n");
        return 0;
    }
    
    record_count = 0;
    char line[200];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)){
        char *token = strtok(line, ",");
        if (token){
            strcpy(donations[record_count].DonorName, token);
        }
        token = strtok(NULL, ",");
        if (token) {
            donations[record_count].DonationAmount = atof(token);
        }
        token = strtok(NULL, ",");
        if (token){
            sscanf(token, "%d-%d-%d", &donations[record_count].Year, &donations[record_count].Month, &donations[record_count].Day);
        }
        token = strtok(NULL, "\n");
        if (token) {
            strcpy(donations[record_count].Purpose, token);
        }
        record_count++;
    }
    fclose(file);
    return record_count;
}

int main() {
    printf("\n===== Testing loadinfo() Function =====\n");
    //สร้างไฟล์ CSV ชั่วคราว
    FILE *file = fopen("DonationInfo_test.csv", "w");
    fprintf(file, "DonorName,DonationAmount,DonationDate,Purpose\n");
    fprintf(file, "Johny Suh,127.00,2026-08-21,Education\n");
    fprintf(file, "Jun Kim,25.50,2024-04-12,Healthcare\n");
    fclose(file);
    //happy
    int count = loadinfo();
    assert(count == 2);
    assert(strcmp(donations[0].DonorName, "Johny Suh") == 0);
    assert(donations[0].DonationAmount == 127.00);
    assert(donations[0].Year == 2026 && donations[0].Month == 8 && donations[0].Day == 21);
    assert(strcmp(donations[0].Purpose, "Education") == 0);

    assert(strcmp(donations[1].DonorName, "Jun Kim") == 0);
    assert(donations[1].DonationAmount == 25.50);
    assert(donations[1].Year == 2024 && donations[1].Month == 4 && donations[1].Day == 12);
    assert(strcmp(donations[1].Purpose, "Healthcare") == 0);
    //edge มีแค่header ไม่มีข้อมูล
    file = fopen("DonationInfo_test.csv", "w");
    fprintf(file, "DonorName,DonationAmount,DonationDate,Purpose\n");
    fclose(file);
    count = loadinfo();
    assert(count == 0);
    //errorไม่มีไฟล์
    remove("DonationInfo_test.csv");
    count = loadinfo();
    assert(count == 0);

    printf("All loadinfo() tests passed!\n");
    return 0;
}
