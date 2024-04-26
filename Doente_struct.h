#ifndef DOENTE_H
#define DOENTE_H

#include <stdio.h>
#include "Data_struct.h"

#define CHARS_CC 14
#define DOENTE_NOME_SIZE 64
#define CC_SIZE 15

typedef struct Doente {
    int id;
    char name[DOENTE_NOME_SIZE];
    struct Data birthday;
    char cc[CHARS_CC];
    int tele;
    char email[DOENTE_NOME_SIZE];
} Doente;

/*
typedef struct nodeD{
    Doente doente;
    struct nodeD *next;
}nodeD;
*/
//typedef nodeD * listaD;

//listaD createListD();
struct Doente *createDoente();
void toFile_Doente(struct Doente *doente, FILE *fd);
void print_Doente(struct Doente *doente);
//int read_Doentes();



#endif