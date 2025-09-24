#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Donation{
    char DonorName[100];
    float DonationAmount;
    char DonationDate[15];
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;

int loadinfo(){
    FILE *file = fopen("DonationInfo.csv", "r");
    if (file == NULL){
        printf("CANNOT OPEN FILE!!!");
        return 0;
    }
    
    record_count = 0;
    char line[200];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)){
        char *token = strtok(line, ",");
        if (token != NULL){
            strcpy(donations[record_count].DonorName, token);
        }
        
        token = strtok(NULL, ",");
        if (token != NULL){
            donations[record_count].DonationAmount = atof(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL){
            strcpy(donations[record_count].DonationDate, token);
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
        printf("\n=== Select Donation Purpose ===\n");
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

void savefile(){
    FILE *file = fopen("DonationInfo.csv", "w");
    if (file == NULL){
        printf("CANNOT OPEN FILE!!!");
    }

    fprintf(file, "DonorName,DonationAmount,DonationDate,Purpose\n");
    for (int i = 0; i < record_count; i++){
        fprintf(file, "%s,%.2f,%s,%s\n",
            donations[i].DonorName,
            donations[i].DonationAmount,
            donations[i].DonationDate,
            donations[i].Purpose);
    }
    fclose(file);
}

int add(){
    int purpose, result;

    printf("\n=== Adding Info ===\n");

    printf("Enter your name-surname: ");
    scanf(" %[^\n]", donations[record_count].DonorName);

    printf("Enter donatation amount: ");
    scanf("%f", &donations[record_count].DonationAmount);
    getchar();

    printf("Enter donation date (YYYY-MM-DD): ");
    scanf("%s", donations[record_count].DonationDate);
    getchar();

    PurPose(donations[record_count].Purpose);

    savefile();
    record_count++;
    printf("Donation added!\n");
    return 1;
}

int search(char keyword[]){
    int found_index[100];
    int found_count = 0;

    for (int i = 0; i < record_count; i++){
        if (strstr(donations[i].DonorName, keyword) != NULL || strstr(donations[i].Purpose, keyword) != NULL){
            printf("Found info: %s | %.2f | %s | %s\n",
            donations[i].DonorName,
            donations[i].DonationAmount,
            donations[i].DonationDate,
            donations[i].Purpose);

            found_index[found_count++] = i;
        }
    }

    if (found_count == 0){
        return -1;
    }
    else if (found_count == 1){
        return found_index[0];
    }
    else{
        int select;
        printf("Found %d records! Please select one!\n", found_count);
        printf("Enter a number (1 - %d): ", found_count);
        scanf("%d", &select);
        getchar();

        if (select >= 1 && select <= found_count){
            return found_index[select - 1];
        }
        else{
            printf("Invalide choice! Please try again!\n");
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
        printf("\n=== Update Menu ===\n");
        printf("1 Update Donor Name-Surname\n");
        printf("2 Update Donation Amount\n");
        printf("3 Update Donation Date\n");
        printf("4 Update Purpose\n");
        printf("5 Save & Exit\n");
        printf("Enter your update choice: ");
        scanf("%d", &upchoice);
        getchar();

        switch (upchoice)
        {
        case 1:
            printf("Enter New Name-Surname: ");
            scanf(" %[^\n]", donations[index].DonorName);
            break;
        case 2:
            printf("Enter New Donation Amount: ");
            scanf("%f", &donations[index].DonationAmount);
            break;
        case 3:
            printf("Enter New Donation Date: ");
            scanf("%s", donations[index].DonationDate);
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

    savefile();
    printf("Record updated!\n");
    return 1;
}

int delete(char keyword[]){
    int index = search(keyword);
    if (index == -1){
        return 0;
    }
    
    for (int i = index; i < record_count - 1; i++){
        donations[i] = donations[i+1];
    }
    record_count--;
    savefile();
    return 1;
}

int main(){
    int choice, result;
    char keyword[100];
    
    result = loadinfo();
    printf("%d records loaded from file.\n", result);

    do{
        printf("\n===== Donation Management =====\n");
        printf("1 Add Donation\n");
        printf("2 Search Donation\n");
        printf("3 Update Donation\n");
        printf("4 Delete Donation\n");
        printf("5 Save & Exit\n");
        printf("\nEnter your choice (only number): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            result = add();
            break;
        case 2:
            printf("\n=== Searching Info ===\n");
            printf("Enter name, surname or purpose: ");
            scanf(" %[^\n]", keyword);
            result = search(keyword);
            if (result == -1){
                printf("NOT FOUND!\n");
            }
            break;
        case 3:
            printf("\n=== Updating Info ===\n");
            printf("Enter name, surname or purpose to update: ");
            scanf(" %[^\n]", keyword);
            result = update(keyword);
            if (result){
                printf("Updated!\n");
            }
            else{
                printf("Update Failed!\n");
            }
            break;
        case 4:
            printf("\n=== Deleting Info ===\n");
            printf("Enter name to delete donation info: ");
            scanf(" %[^\n]", keyword);
            result = delete(keyword);
            if (result){
                printf("Deleted Info!\n");
            }
            else{
                printf("Delete failed!\n");
            }
            break;
        case 5:
            break;
        default:
            break;
        } 
    } while(choice != 5);
    return 0;
}