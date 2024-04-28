#ifndef DOENTE_H
#define DOENTE_H

#include <stdio.h>
#include "Data_struct.h"

#define CHARS_CC 15
#define DOENTE_NOME_SIZE 64

typedef struct Doente {
    int id;
    char name[DOENTE_NOME_SIZE];
    struct Data birthday;
    char cc[CHARS_CC];
    int tele;
    char email[DOENTE_NOME_SIZE];
} Doente;


typedef struct nodeD{
    Doente doente;
    struct nodeD *next;
}nodeD;

typedef nodeD * listaD;

// List Functions
listaD createListD();
void destroyListD(listaD list);

void print_Doente(Doente doente);
int write_Doentes(listaD list);
int read_Doentes(listaD list);



#endif