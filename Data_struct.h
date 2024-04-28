#ifndef DATA_H
#define DATA_H

#define DATA_STRING_SIZE 32

typedef struct Data {
    int year;
    int month;
    int day;
} Data;


struct Data *createData(int year, int month, int day);
void data_toStr(Data date, char *buff);
int str_toData(char *str, Data *date);
int Datacmp(struct Data *date1, struct Data *date2);

#endif