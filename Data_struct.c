#ifndef DATA_C
#define DATA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Data_struct.h"

struct Data *createData(int year, int month, int day) {
    /* Returns pointer to newly allocated Data struct
     * Also introduces the info "year", "month" and "day" into the struct
     *
     * Returns:
     *      -> NULL if malloc fails or if the date is invalid
     *      -> valid pointer to Data struct if success
     */
    if ( validate_data(day, month, year)!=0 ) {
        // invalid date
        return NULL;
    }
    struct Data *new_Data = malloc(sizeof(Data));
    if (new_Data == NULL) {
        // malloc failed, download more RAM at downloadmoreram.com
        return NULL;
    }

    new_Data->year = year;
    new_Data->month = month;
    new_Data->day = day;

    return new_Data;
}

struct Data *createEmptyData() {
    /* Returns pointer to newly allocated Data struct
     * Also introduces the info "year", "month" and "day" into the struct
     *
     * Returns:
     *      -> NULL if malloc fails or if the date is invalid
     *      -> valid pointer to Data struct if success
     */
    return createData(1, 1, 1);
};


int setData(struct Data *date, int year, int month, int day) {
    /* Introduces the info "year", "month" and "day" into the struct
     *
     * Returns:
     *      -> -1 date pointer is NULL
     *      -> 0 if success
     *      -> 1 if invalid date
     */
    if (date == NULL) {
        // invalid pointer
        return -1;
    }
    if ( validate_data(day, month, year)!=0 ) {
        // invalid date
        return 1;
    }

    date->year = year;
    date->month = month;
    date->day = day;

    return 0;
}

int destroyData(struct Data *date) {
    /* Frees the memory allocated for the Data struct */
    if (date == NULL) {
        // invalid pointer
        return -1;
    }
    free(date);
    return 0;
}


int validate_data(int day, int month, int year) {
    /* Given the day, month and year checks if the format is valid
     * Valid = 0  Unvalid = 1
     *
     * Returns:
     *     -> 0 if valid
     *     -> 1 if invalid month
     *     -> 2 if invalid day
     *     -> 3 if invalid year
     */

    if (month > 12 || month < 1){
        return 1;
    } else if (day < 1) {
        return 2;
    } else if (year < 0) {
        return 3;
    }

    switch (month){
        case (4):
        case (6):
        case (9):
        case (11):
            if (day > 30) return 2;
            break;
    
        case (2):
            if (year%4==0 && day > 29) return 2;
            if (year%4!=0 && day > 28) return 2;
            break;

        default:
            if (day > 31) return 2;
            break;
    }

    return 0;
}


int str_toData(char *str, Data *date) {
    /* Writes char array "str" to struc Data "date"
     * Returns:
     *      -> -2 if invalid format
     *      -> -1 if invalid pointers
     *      ->  0 if success
     *      ->  1 if invalid date
     */
    char *year, *month, *day;
    char sep[2] = "/";

    if (date==NULL || str==NULL) {
        return -1;
    }

    day = strtok(str, sep);
    month = strtok(NULL, sep);
    year = strtok(NULL, sep);

    if (day==NULL || month==NULL || year==NULL) {
        return -2;
    }

    date->day = atoi(day);
    date->month = atoi(month);
    date->year = atoi(year);

    if (validate_data(date->day, date->month, date->year)) return 1;

    return 0;
}

void data_toStr(Data *date, char *buff) {
    /* Convert "Data" to char array in format dd/mm/yy */
    sprintf(buff, "%d/%d/%d", date->day, date->month, date->year);
}


int Datacmp(struct Data *date1, struct Data *date2) {
    /* Compares date1 and date2
     * Returns:
     *      ->  1 if date1 is after
     *      ->  0 if equal
     *      -> -1 if date1 is before
     */
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

int Datacpy(struct Data *dest, struct Data *src) {
    /* Copies src to dest
     * Returns:
     *      ->  0 if success
     *      -> -1 if invalid pointers
     */
    if (dest == NULL || src == NULL) {
        return -1;
    }
    dest->day = src->day;
    dest->month = src->month;
    dest->year = src->year;
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