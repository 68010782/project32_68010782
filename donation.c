#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "donation.h"
#define DEFAULT_CSV "DonationInfo.csv"

struct Donation{
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;

int loadinfo(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("CANNOT OPEN FILE!!!");
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
        if (token){
            donations[record_count].DonationAmount = atof(token);
        }

        token = strtok(NULL, ",");
        if (token){
            sscanf(token, "%d-%d-%d", &donations[record_count].Year, &donations[record_count].Month, &donations[record_count].Day);
        }

        token = strtok(NULL, "\n");
        if (token != NULL){
            strcpy(donations[record_count].Purpose, token);
        }

        record_count++;
    }
    fclose(file);
    return record_count;
}

void PurPose(char *purpose){
    int purchoice;

    do{
        printf("\n===== Select Donation Purpose =====\n");
        printf("1 Education\n");
        printf("2 Healthcare\n");
        printf("3 Religion\n");
        printf("4 Charity\n");
        printf("5 Environment\n");
        printf("6 Disaster Relief\n");
        printf("7 Others\n");
        printf("\nEnter your purpose (only number): ");
        scanf("%d", &purchoice);
        getchar();

        switch (purchoice){
        case 1:
            strcpy(purpose, "Education");
            break;
        case 2:
            strcpy(purpose, "Healthcare");
            break;
        case 3:
            strcpy(purpose, "Religion");
            break;
        case 4:
            strcpy(purpose, "Charity");
            break;
        case 5:
            strcpy(purpose, "Environment");
            break;
        case 6:
            strcpy(purpose, "Disaster Relief");
            break;
        case 7:
            printf("Enter your purpose: ");
            scanf(" %[^\n]", purpose);
            break;
        default:
            printf("Please select a number between 1 - 7\n");
            purchoice = 0;
        }
    } while (purchoice < 1 || purchoice > 7);
}

void savefile(const char *filename){
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("CANNOT OPEN FILE!!!");
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
    fclose(file);
}

int add(){
    int purpose, result;

    printf("\n===== Adding Info =====\n");
    
    do{
        printf("Enter your name-surname: ");
        fgets(donations[record_count].DonorName, sizeof(donations[record_count].DonorName), stdin);
        donations[record_count].DonorName[strcspn(donations[record_count].DonorName, "\n")] = '\0';
        if (strlen(donations[record_count].DonorName) == 0){
            printf("Please enter your name-surname!\n");
        }
    }while(strlen(donations[record_count].DonorName) == 0);

    do{
        printf("Enter donatation amount (Baht): ");
        if(scanf("%f", &donations[record_count].DonationAmount) != 1 ){
            printf("Please enter a number!\n");
            while ((getchar() != '\n'));
            donations[record_count].DonationAmount = -1;
        }
        else if(donations[record_count].DonationAmount < 0){
            printf("Please enter positive number!\n");
        }
        while(getchar() != '\n');
    }while (donations[record_count].DonationAmount < 0);

    do{
        printf("Enter donation date (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &donations[record_count].Year, &donations[record_count].Month, &donations[record_count].Day) != 3){
            printf("Please enter valid date!\n");
            while ((getchar() != '\n'));
            donations[record_count].Year = donations[record_count].Month = donations[record_count].Day = -1;
        }
        else if (donations[record_count].Year <= 0 || donations[record_count].Month <= 0 || donations[record_count].Day <= 0 ){
            printf("Please enter positive number!\n");
        }
        else if (donations[record_count].Month > 12 || donations[record_count].Day > 31){
            printf("Please enter correct month/date!\n");
            donations[record_count].Year = donations[record_count].Month = donations[record_count].Day = -1;
        }
        while(getchar() != '\n');
    }while (donations[record_count].Year <=0 || donations[record_count].Month <= 0 || donations[record_count].Day <= 0);

    PurPose(donations[record_count].Purpose);
    record_count++;
    savefile(DEFAULT_CSV);
    printf("\nDonation added!\n");
    return 1;
}

int search(char keyword[]){
    int found_index[100];
    int found_count = 0;

    for (int i = 0; i < record_count; i++){
        if (strstr(donations[i].DonorName, keyword) != NULL || strstr(donations[i].Purpose, keyword) != NULL){
            printf("[%d] %s | %s\n", found_count + 1, donations[i].DonorName, donations[i].Purpose);
            found_index[found_count++] = i;
        }
    }

    if (found_count == 0){
        printf("No record found for keyword: %s\n", keyword);
        return -1;
    }
    else if (found_count == 1){
        int i = found_index[0];
        printf("\n===== Record Details =====\n");
        printf("Name-Surname: %s\n", donations[i].DonorName);
        printf("Amount: %.2f Baht\n", donations[i].DonationAmount);
        printf("Date: %04d-%02d-%02d\n", donations[i].Year, donations[i].Month, donations[i].Day);
        printf("Purpose: %s\n", donations[i].Purpose);
        return i;
    }
    else{
        int select;
        printf("Found %d records! Please select one to view details!\n", found_count);
        printf("Enter a number (1 - %d): ", found_count);
        if(scanf("%d", &select) != 1 || select <1 || select > found_count){
            printf("Invalid choice!\n");
            while(getchar() != '\n');
            return -1;
        }
        while(getchar() != '\n');

        if (select >= 1 && select <= found_count){
            int i = found_index[select - 1];
            printf("\n===== Record Details =====\n");
            printf("Name-Surname: %s\n", donations[i].DonorName);
            printf("Amount: %.2f Baht\n", donations[i].DonationAmount);
            printf("Date: %04d-%02d-%02d\n", donations[i].Year, donations[i].Month, donations[i].Day);
            printf("Purpose: %s\n", donations[i].Purpose);
            return i;
        }
        else{
            printf("Invalid choice! Please try again!\n");
            return -1;
        }
    }
}

int update(char keyword[]){
    int index = search(keyword);
    if (index == -1){
        printf("Record Not Found!");
        return 0;
    }

    int upchoice;

    do{
        printf("\n===== Update Menu =====\n");
        printf("1 Update Donor Name-Surname\n");
        printf("2 Update Donation Amount\n");
        printf("3 Update Donation Date\n");
        printf("4 Update Purpose\n");
        printf("5 Save & Exit\n");
        printf("Enter your update choice: ");
        if(scanf("%d", &upchoice) != 1){
            printf("Please enter a number between 1-5!\n");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');

        switch (upchoice)
        {
        case 1:
            do{
                printf("Enter New Name-Surname: ");
                fgets(donations[index].DonorName, sizeof(donations[index].DonorName), stdin);
                donations[index].DonorName[strcspn(donations[index].DonorName, "\n")] = '\0';
                if (strlen(donations[index].DonorName) == 0){
                    printf("Please enter your name-surname\n");
                }
            }while (strlen(donations[index].DonorName) == 0);
            break;
        case 2:
            do{
                while(getchar()!='\n');
                printf("Enter New Donation Amount (Baht): ");
                if(scanf("%f", &donations[index].DonationAmount) != 1){
                    printf("Please enter a number!\n");
                    while(getchar() != '\n');
                    donations[index].DonationAmount = -1;
                }
                else if (donations[index].DonationAmount < 0){
                    printf("Please enter positive amount!\n");
                }
                while(getchar() != '\n');
            }while(donations[index].DonationAmount < 0);
            break;
        case 3:
            do{
                while(getchar()!='\n');
                printf("Enter New Donation Date (YYYY-MM-DD): ");
                if(scanf("%d-%d-%d", &donations[index].Year, &donations[index].Month, &donations[index].Day) != 3){
                    printf("Please enter all date!\n");
                    while (getchar() != '\n');
                    donations[index].Year = donations[index].Month = donations[index].Day = -1; 
                }
                else if(donations[index].Year <= 0 || donations[index].Month <= 0 || donations[index].Day <= 0 || donations[index].Month > 12 || donations[index].Day > 31){
                    printf("Please enter valid date!\n");
                    donations[index].Year = donations[index].Month = donations[index].Day = -1; 
                }
                while(getchar() != '\n');
            }while ((donations[index].Year) <= 0);
            break;
        case 4:
            PurPose(donations[index].Purpose);
            break;
        case 5:
            printf("Save & Exit update menu\n");
            break;
        default:
            printf("Please select a number between 1 - 5\n");
        }
    } while(upchoice != 5);

    savefile(DEFAULT_CSV);
    printf("Record updated!\n");
    return 1;
}

int delete(char keyword[]){
    int index = search(keyword);
    if (index == -1){
        return 0;
    }
    
    char confirm;
    do{
        printf("Are you sure to delete this record? (Y/N): ");
        scanf("%c", &confirm);
        while(getchar() != '\n');

        if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n'){
            printf("Fails to delete! Please enter Y or N\n");
            confirm = 0;
        }
    }while(confirm==0);

    if (confirm == 'N' && confirm == 'n'){
            printf("Delete canceled\n");
            return 0;
        }

    for (int i = index; i < record_count - 1; i++){
        donations[i] = donations[i+1];
    }
    record_count--;
    savefile(DEFAULT_CSV);
    return 1;
}

void menu(){
    int choice, result;
    char keyword[100];

    do{
        printf("\n===== Donation Management =====\n");
        printf("1 Add Donation\n");
        printf("2 Search Donation\n");
        printf("3 Update Donation\n");
        printf("4 Delete Donation\n");
        printf("5 test_add\n");
        printf("6 test_search\n");
        printf("7 test_update\n");
        printf("8 test_delete\n");
        printf("9 test_loadinfo\n");
        printf("10 test_menu\n");
        printf("11 test_Purpose\n");
        printf("12 test_savefile\n");
        printf("13 test_e2e\n");
        printf("14 Save & Exit\n");
        printf("\nEnter your choice (1-14): ");
        if (scanf("%d", &choice) != 1){
            printf("Please enter a number between 1-14!\n");
            while (getchar()!='\n');
        }
        while (getchar()!='\n');

        switch (choice)
        {
        case 1:
            result = add();
            break;
        case 2:
            printf("\n===== Searching Info =====\n");
            printf("Enter name, surname or purpose: ");
            fgets(keyword,sizeof(keyword),stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            search(keyword);
            break;
        case 3:
            printf("\n===== Updating Info =====\n");
            printf("Enter name, surname or purpose to update: ");
            fgets(keyword,sizeof(keyword),stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            result = update(keyword);
            if (result){
                printf("Updated!\n");
            }
            else{
                printf("Update Failed!\n");
            }
            break;
        case 4:
            printf("\n===== Deleting Info =====\n");
            printf("Enter name to delete donation info: ");
            fgets(keyword,sizeof(keyword),stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            result = delete(keyword);
            if (result){
                printf("Deleted Info!\n");
            }
            else{
                printf("Delete failed!\n");
            }
            break;
        case 5:
            #ifdef _WIN32
                system("test_add.exe");
            #else
                system("./test_add");
            #endif
            break;

        case 6:
            #ifdef _WIN32
                system("test_search.exe");
            #else
                system("./test_search");
            #endif
            break;
        case 7:
            #ifdef _WIN32
                system("test_update.exe");
            #else
                system("./test_update");
            #endif
            break;
        case 8:
            #ifdef _WIN32
                system("test_delete.exe");
            #else
                system("./test_delete");
            #endif
            break;
        case 9:
            #ifdef _WIN32
                system("test_loadinfo.exe");
            #else
                system("./test_loadinfo");
            #endif
            break;
        case 10:
            #ifdef _WIN32
                system("test_menu.exe");
            #else
                system("./test_menu");
            #endif
            break;
        case 11:
            #ifdef _WIN32
                system("test_Purpose.exe");
            #else
                system("./test_Purpose");
            #endif
            break;
        case 12:
            #ifdef _WIN32
                system("test_savefile.exe");
            #else
                system("./test_savefile");
            #endif
            break;
        case 13:
            #ifdef _WIN32
                system("test_e2e.exe");
            #else
                system("./test_e2e");
            #endif
            break;
        case 14:
            break;
        default:
        printf("Please enter 1-14!\n");
            break;
        } 
    } while(choice != 14);
}
