#ifndef DATA_H
#define DATA_H

#define DATA_STRING_SIZE 32

typedef struct Data {
    int year;
    int month;
    int day;
} Data;


struct Data *createData(int year, int month, int day);
void toString_Data(struct Data *date, char *buff);
Data str_toData(char *str);
int bigger_Data(struct Data *date1, struct Data *date2);

#endif