#include <stdio.h>
#include <string.h>
#include <assert.h>

void PurPoseTest(int choice, const char *others, char *purpose) {
    switch (choice){
        case 1:
            strcpy(purpose,"Education");
            break;
        case 2:
            strcpy(purpose,"Healthcare");
            break;
        case 3:
            strcpy(purpose,"Religion");
            break;
        case 4:
            strcpy(purpose,"Charity");
            break;
        case 5:
            strcpy(purpose,"Environment");
            break;
        case 6:
            strcpy(purpose,"Disaster Relief");
            break;
        case 7:
            strcpy(purpose,others);
            break;
        default:
            strcpy(purpose,"Invalid");
            break;
    }
}

int main() {
    char purpose[100];
    //happy
    PurPoseTest(4,"",purpose);
    assert(strcmp(purpose,"Charity") == 0);
    //edge
    PurPoseTest(1,"",purpose);
    assert(strcmp(purpose,"Education") == 0);
    PurPoseTest(7,"Custom Purpose",purpose);
    assert(strcmp(purpose,"Custom Purpose") == 0);
    //error
    PurPoseTest(0,"",purpose);
    assert(strcmp(purpose,"Invalid") == 0);
    PurPoseTest(8,"",purpose);
    assert(strcmp(purpose,"Invalid") == 0);

    printf("All PurPose() tests passed!\n");
    return 0;
}
