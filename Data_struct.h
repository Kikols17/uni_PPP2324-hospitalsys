#ifndef DATA_H
#define DATA_H

typedef struct Data {
    int year;
    int month;
    int day;
} Data;


struct Data *createData();

#endif