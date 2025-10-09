#ifndef DONATION_H
#define DONATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Donation {
    char DonorName[100];
    float DonationAmount;
    int Day, Month, Year;
    char Purpose[100];
};

extern struct Donation donations[100];
extern int record_count;

int loadinfo(const char *filename);
void savefile(const char *filename);
void PurPose(char *purpose);
int add();
int search(char keyword[]);
int update(char keyword[]);
int delete(char keyword[]);
void menu();

#endif
