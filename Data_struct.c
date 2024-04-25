#ifndef DATA_C
#define DATA_C

#include <stdio.h>
#include <stdlib.h>

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

#endif