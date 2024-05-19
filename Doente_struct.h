#ifndef DOENTE_H
#define DOENTE_H

#include <stdio.h>
#include "Data_struct.h"

#define BUFFER_SIZE 50
#define PARAMS_DOENTE 6
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
    struct nodeD *prev;
}nodeD;

typedef nodeD * listaD;

void toFile_Doente(Doente doente, FILE *fd);
int fromFile_Doente(listaD list);
int write_Doentes(listaD list);

listaD createListD();
int emptyListD(listaD list);
void destroyListD(listaD list);

int in_listDoente(listaD list, Doente d);
listaD searchDoente_byID(listaD list, int id);
listaD searchDoente_byName(listaD list, char *name);

int insertD(listaD list, Doente d);
int removeD(listaD list, int id);

void print_Doente(Doente doente);
void print_Doente2(Doente doente);
void print_Alpha(listaD list);




#endif