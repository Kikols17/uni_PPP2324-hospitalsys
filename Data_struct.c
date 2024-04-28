#ifndef DATA_C
#define DATA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Data_struct.h"

struct Data *createData(int year, int month, int day) {
    /* Returns pointer to newly allocated Data struct
     * Also introduces the info "year", "month" and day into the struct
     */
    struct Data *new_Data = malloc(sizeof(Data));

    new_Data->year = year;
    new_Data->month = month;
    new_Data->day = day;

    return new_Data;
}

int validate_data(int day, int month, int year){
    // Given the day, month and year checks if the format is valid
    // Valid = 1  Unvalid = 0

    if (month > 12 || month < 1 || day < 1 || year < 1){
        return 0;
    }

    switch (month){
        case (4):
        case (6):
        case (9):
        case (11):
            if (day > 30) return 0;
            break;
    
        case (2):
            if (year%4==0 && day > 29) return 0;
            if (year%4!=0 && day > 28) return 0;
            break;

        default:
            if (day > 31) return 0;
            break;
    }

    return 1;
}


int str_toData(char *str, Data *date) {
    /* Writes char array "str" to struc Data "date"
     * returns 1 if success, 0 if incorrect format
     */
    char *year, *month, *day;
    char sep[2] = "/";

    day = strtok(str, sep);
    month = strtok(NULL, sep);
    year = strtok(NULL, sep);

    date->day = atoi(day);
    date->month = atoi(month);
    date->year = atoi(year);

    if (validate_data(date->day, date->month, date->year)) return 1;

    return 0;
}

void data_toStr(Data date, char *buff) {
    /* Convert "Data" to char array */
    sprintf(buff, "%d/%d/%d", date.day, date.month, date.year);
}









int Datacmp(struct Data *date1, struct Data *date2) {
    /* Compares date1 and date2, return 1 if date1 is after, return 0 if equal and return -1 if date1 is before */
    if (date1->year > date2->year) {
        return 1;
    } else if (date1->year < date2->year) {
        return -1;
    }

    if (date1->month > date2->month) {
        return 1;
    } else if (date1->month < date2->month) {
        return -1;
    }

    if (date1->day > date2->day) {
        return 1;
    } else if (date1->day < date2->day) {
        return -1;
    }

    // equal dates
    return 0;
}







/*
int main2() {
    / Test Case for "Data_struct" /
    struct Data *test_data = createData(2024, 12, 31);
    if (test_data!=NULL) {
        printf("\"test_data\" created successfully\n");
    } else {
        printf("error creating \"test_data\"\n");
        return -1;
    }
    toString_Data(test_data);
    fprintf(stdout, "TEST_DATA string:\n\texpected:\t31/12/2024\n\tgot:\t%s\n", test_data->str);
    return 0;
}
*/


#endif