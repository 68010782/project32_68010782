#include <assert.h>
#include <string.h>
#include <stdio.h>

struct Donation{
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

struct Donation donations[100];
int record_count = 0;

int delete_logic(int index){
    if (index < 0 || index >= record_count){
        return 0;
    }
    for (int i = index; i<record_count - 1; i++){
        donations[i] = donations[i+1];
    }
    record_count--;
    return 1;
}

int main(){
    printf("\n===== Testing delete_logic() =====\n");
    //ข้อมูลเทส
    strcpy(donations[0].DonorName, "Johny Suh");
    strcpy(donations[1].DonorName, "David Kim");
    strcpy(donations[2].DonorName, "Jun Kim");
    record_count = 3;
    //happy
    assert(delete_logic(1) == 1);
    assert(record_count == 2);
    assert(strcmp(donations[0].DonorName, "Johny Suh") == 0);
    assert(strcmp(donations[1].DonorName, "Jun Kim") == 0);
    //edge
    assert(delete_logic(0) == 1);
    assert(record_count == 1);
    assert(strcmp(donations[0].DonorName, "Jun Kim") == 0);
    //error
    assert(delete_logic(-1) == 0);
    assert(delete_logic(5) == 0); 
    assert(record_count == 1);

    printf("All delete_logic() tests passed!\n");
}