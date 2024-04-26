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

int toData_str(char *str, struct Data *date) {
    /* Writes char array "str" to struc Data "date"
     * returns 0 if success, -1 if incorrect format
     */
    char *year, *month, *day;
    char sep = '/';
    
    day = strtok(str, sep);
    month = strtok(str, sep);
    year = strtok(str, sep);

    if (day==NULL || month==NULL || year==NULL) {
        return -1;
    }

    date->day = atoi(day);
    date->month = atoi(month);
    date->year = atoi(year);

    return 0;
}

void toString_Data(struct Data *date, char *buff) {
    /* Convert "Data" to char array */
    sprintf(buff, "%d/%d/%d", date->day, date->month, date->year);
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