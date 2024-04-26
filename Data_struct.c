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


void toString_Data(struct Data *date) {
    /* Convert "Data" to char array */
    sprintf(date->str, "%d/%d/%d", date->day, date->month, date->year);
}







#ifndef main
int main() {
    /* Test Case for "Data_struct" */
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
#endif


#endif