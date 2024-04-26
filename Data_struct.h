#ifndef DATA_H
#define DATA_H

#define STRING_SIZE 32

typedef struct Data {
    int year;
    int month;
    int day;
    char str[STRING_SIZE];
} Data;


struct Data *createData(int year, int month, int day);
void toString_Data(struct Data *date);
int bigger_Data(struct Data *date1, struct Data *date2);

#endif