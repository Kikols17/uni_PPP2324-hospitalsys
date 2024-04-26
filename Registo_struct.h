#ifndef REGISTO_H
#define REGISTO_H

#include <stdio.h>

#include "Data_struct.h"


typedef struct Registo {
    int id;
    struct Data date;
    int tens_max;
    int tens_min;
    int weight;
    int height;
} Registo;

typedef struct node{
    Registo registo;
    struct nodeR * next;

}nodeR;

typedef nodeR * listaR;

Registo *createRegisto();
void toFile_Registo(struct Registo *registo, FILE *fd);


#endif