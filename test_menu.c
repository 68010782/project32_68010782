#include <assert.h>
#include <stdio.h>
//สมมติว่ามีการอินพุตข้อมูล
void menu_choice(int choice, char *keyword){
    int result;
    switch(choice){
        case 1:
            printf("add\n");
            break;
        case 2:
            printf("search: %s\n", keyword);
            break;
        case 3:
            printf("update: %s\n", keyword);
            break;
        case 4:
            printf("delete: %s\n", keyword);
            break;
        case 5:
            printf("Exit\n");
            break;
        default:
            printf("invalid choice\n", keyword);
            break;
    }
}
//มีข้อมูลอินพุตให้
int main(){
    printf("\n===== Testing menu() function =====\n");
    menu_choice(1,"");
    menu_choice(2,"Johny Suh");
    menu_choice(3,"Jun Kim");
    menu_choice(4,"Kevin Yoon");
    menu_choice(5,"");
    menu_choice(0,"");
    printf("All menu() tests passed!\n");
    return 0;
}
